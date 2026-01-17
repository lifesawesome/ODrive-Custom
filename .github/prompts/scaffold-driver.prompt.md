---
name: scaffold-driver
description: 'Create a new hardware driver structure'
agent: agent
tools: ['file_search', 'read_file', 'write_file']
---
Create a scaffold for a new hardware driver in the `Firmware/Drivers` directory.
Ask the user for the **Driver Name** (e.g., `DRV8301`).

1. Create `Firmware/Drivers/<driver_name>.hpp` and `Firmware/Drivers/<driver_name>.cpp`.
2. The header must include:
   - Include guards (`#pragma once`).
   - A class definition inheriting from a generic interface if applicable.
   - Separate `public`, `protected`, and `private` sections.
3. The CPP file must include:
   - Implementation of a basic `init()` and `update()` method.
   - Valid `#include` of the header.

Use the `CPP_Coding_Practices.instructions.md` to ensure correct naming conventions (PascalCase classes, snake_case files).
