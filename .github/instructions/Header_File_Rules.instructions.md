---
name: 'Header File Rules'
description: 'Guidelines for C++ header files: includes, pragmas, and structure.'
applyTo: '**/*.{h,hpp}'
---

# Header File Rules

## Include Guards
- Use `#pragma once` at the very top of every header file.
- Do not use old-style `#ifndef HEADER_NAME_H` guards.

## Includes
- **"Include What You Use" (IWYU)**: Only include headers necessary for the declarations in the file.
- Use generic forward declarations where possible to minimize include dependencies.

```cpp
// ✅ GOOD
#pragma once

#include <iosfwd>  // Forward decls for iostream
class Motor;       // Forward decl

class Controller {
    Motor* motor_; // Pointer allows forward decl
};

// ❌ BAD
#include <iostream> // Heavy include
#include "Motor.hpp" // Full include when pointer would suffice
```

## Namespace Pollution
- **NEVER** use `using namespace std;` or any other `using namespace` in a header file global scope.
- It forces that namespace on every file that includes that header.

## Inline Implementation
- Keep implementation out of headers unless:
    - It is a template.
    - It is a `constexpr` function.
    - It is a trivial getter/setter (1-2 lines).

```cpp
class Encoder {
public:
    // Trivial getter - OK in header
    int get_cpr() const { return cpr_; }

    // Complex logic - Move to .cpp
    void calibrate(); 

private:
    int cpr_;
};
```
