---
name: modernize-cpp
description: 'Refactor selection to strictly follow C++17 standards'
agent: edit
---
Refactor the selected code to strictly follow C++17 standards and the project's coding practices.

Changes to apply:
1. Replace raw loops with range-based `for` loops or `<algorithm>` functions.
2. Use `auto` for iterators and complex types, but keep explicit types for primitives.
3. Replace `NULL` or `0` for pointers with `nullptr`.
4. Use `constexpr` for any compile-time constants.
5. Ensure `const` correctness for variables and methods that don't modify state.

Refer to `CPP_Coding_Practices.instructions.md` for style rules.
