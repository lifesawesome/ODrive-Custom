---
name: 'Python Coding Standards'
description: 'Python coding standards, PEP 8 compliance, and testing guidelines for ODrive tools.'
applyTo: '**/*.py'
---

# Python Coding Standards

## General Guidelines
- **Standard**: Follow [PEP 8](https://peps.python.org/pep-0008/) for all layout and validation.
- **Formatter**: Code should be formatted using `black` or `autopep8`.
- **Linter**: Use `flake8` or `pylint` to catch errors.

## Naming Conventions
- **Modules/Packages**: `lowercase_with_underscores`
- **Classes**: `PascalCase`
- **Functions/Methods**: `snake_case`
- **Variables**: `snake_case`
- **Constants**: `UPPER_CASE_WITH_UNDERSCORES`
- **Private Members**: `_leading_underscore`

```python
# ✅ GOOD
class MotorInterface:
    MAX_VOLTAGE = 24.0

    def __init__(self):
        self._internal_state = 0

    def get_voltage(self) -> float:
        return self.MAX_VOLTAGE

# ❌ BAD
class motorInterface:
    maxVoltage = 24.0
    
    def GetVoltage(self):
        pass
```

## Type Hinting
- Use type hints for all function arguments and return values.
- Use `typing.Optional`, `typing.List`, etc., for complex types (or standard collection types in Python 3.9+).

```python
from typing import List, Optional

def configure_axis(axis_id: int, config: dict) -> bool:
    values: List[float] = []
    return True
```

## Docstrings
- Use **Google Style** docstrings.
- Document all public classes and functions.
- Include `Args:`, `Returns:`, and `Raises:` sections.

```python
def set_velocity(velocity: float) -> None:
    """Sets the target velocity for the motor.

    Args:
        velocity (float): Target velocity in turns/s.

    Raises:
        ValueError: If velocity is outside safe limits.
    """
    if abs(velocity) > 1000:
        raise ValueError("Velocity too high")
```

## Error Handling
- Use specific exceptions (e.g., `ValueError`, `IOError`) rather than bare `Exception`.
- Use `try/finally` or `with` statements for resource management (files, serial ports).

## Operations with Hardware
- When communicating with ODrive devices via USB/Serial, handle timeouts gracefully.
- Use the `odrive` library abstraction layers rather than raw serial commands where possible.
