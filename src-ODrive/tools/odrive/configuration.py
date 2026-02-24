
import json
import os
import tempfile
import fibre.libfibre
import odrive
from odrive.utils import OperationAbortedException, yes_no_prompt

def obj_to_path(root, obj):
    """
    Returns the dot-separated attribute path of obj relative to root.

    Recursively searches the attributes of root to find the object and builds
    a string path such as "axis0.controller.config".

    Args:
        root: The root ODrive object to search from.
        obj: The target object to find within root.

    Returns:
        str or None: The dot-separated path string if found, or None if not found.
    """
    for k in dir(root):
        v = getattr(root, k)
        if not k.startswith('_') and isinstance(v, fibre.libfibre.RemoteObject):
            if v == obj:
                return k
            subpath = obj_to_path(v, obj)
            if not subpath is None:
                return k + "." + subpath
    return None

def get_dict(root, obj, is_config_object):
    """
    Recursively builds a dictionary representation of an ODrive object's configuration.

    Traverses the object tree and collects all config properties into a nested dict
    suitable for JSON serialization.

    Args:
        root: The root ODrive object (used for resolving object references to paths).
        obj: The current object to serialize.
        is_config_object (bool): If True, scalar properties on this object are included.
            Automatically set to True for sub-objects named 'config'.

    Returns:
        dict: A nested dictionary of configuration values.
    """
    result = {}

    for k in dir(obj):
        v = getattr(obj, k)
        if k.startswith('_') and k.endswith('_property') and is_config_object:
            v = v.read()
            if isinstance(v, fibre.libfibre.RemoteObject):
                v = obj_to_path(root, v)
            result[k[1:-9]] = v
        elif not k.startswith('_') and isinstance(v, fibre.libfibre.RemoteObject):
            sub_dict = get_dict(root, v, (k == 'config') or is_config_object)
            if sub_dict != {}:
                result[k] = sub_dict

    return result

def set_dict(obj, path, config_dict):
    """
    Applies a configuration dictionary to an ODrive object.

    Recursively writes values from config_dict to the matching properties on obj.
    Collects and returns a list of error messages for any properties that could
    not be restored (e.g., renamed or removed in a newer firmware version).

    Args:
        obj: The ODrive object to apply configuration to.
        path (str): Dot-separated path string for error reporting (use "" for the root).
        config_dict (dict): Dictionary of configuration values to apply.

    Returns:
        list[str]: A list of error message strings for any properties that failed to restore.
    """
    errors = []
    for (k,v) in config_dict.items():
        name = path + ("." if path != "" else "") + k
        if not k in dir(obj):
            errors.append("Could not restore {}: property not found on device".format(name))
            continue
        if isinstance(v, dict):
            errors += set_dict(getattr(obj, k), name, v)
        else:
            try:
                remote_attribute = getattr(obj, '_' + k + '_property')
                #if isinstance(v, str) and isinstance()
                remote_attribute.exchange(v)
            except Exception as ex:
                errors.append("Could not restore {}: {}".format(name, str(ex)))
    return errors

def get_temp_config_filename(device):
    """
    Returns the path to a temporary configuration file for the given ODrive device.

    The filename is derived from the device's serial number, ensuring that each
    device has a unique temporary config file in the system's temp directory.

    Args:
        device: The ODrive device object.

    Returns:
        str: The full path to the temporary configuration JSON file.
    """
    serial_number = odrive.get_serial_number_str_sync(device)
    safe_serial_number = ''.join(filter(str.isalnum, serial_number))
    return os.path.join(tempfile.gettempdir(), 'odrive-config-{}.json'.format(safe_serial_number))

def backup_config(device, filename, logger):
    """
    Exports the configuration of an ODrive to a JSON file.
    If no file name is provided, the file is placed into a
    temporary directory.
    """

    if filename is None:
        filename = get_temp_config_filename(device)

    logger.info("Saving configuration to {}...".format(filename))

    if os.path.exists(filename):
        if not yes_no_prompt("The file {} already exists. Do you want to override it?".format(filename), True):
            raise OperationAbortedException()

    data = get_dict(device, device, False)
    with open(filename, 'w') as file:
        json.dump(data, file)
    logger.info("Configuration saved.")

def restore_config(device, filename, logger):
    """
    Restores the configuration stored in a file 
    """

    if filename is None:
        filename = get_temp_config_filename(device)

    with open(filename) as file:
        data = json.load(file)

    logger.info("Restoring configuration from {}...".format(filename))
    errors = set_dict(device, "", data)

    for error in errors:
        logger.info(error)
    if errors:
        logger.warn("Some of the configuration could not be restored.")
    
    try:
        device.save_configuration()
    except fibre.libfibre.ObjectLostError:
        pass # Saving configuration makes the device reboot
    logger.info("Configuration restored.")
