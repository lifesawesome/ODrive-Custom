---
name: add-doxygen
description: 'Add Doxygen documentation to the selected code'
agent: edit
---
Generate comprehensive Doxygen comments for the selected C++ code.

Follow these specific guidelines:
1. Use `@brief` for a short summary.
2. Use `@param` for all function arguments, explaining valid ranges/units.
3. Use `@return` to describe return values and error codes.
4. Use `@note` for thread-safety or strict timing requirements.
5. If the selection is a class, document its thread-safety and usage pattern.

Example format:
```cpp
/**
 * @brief Calculates the field oriented control currents.
 * @param theta_e Electrical angle in radians [0, 2PI]
 * @return True if successful, false if inputs invalid
 */
```
