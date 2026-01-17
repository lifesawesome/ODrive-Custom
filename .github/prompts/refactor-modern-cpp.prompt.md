---
name: refactor-modern-cpp
description: Identify C++17 refactoring opportunities in MotorControl
agent: ask
model: GPT-4o (copilot)
---

Refactor [Firmware/MotorControl/](Firmware/MotorControl/) code to use modern C++17 features following the guidelines in [CPP_Coding_Practices.instructions.md](.github/instructions/CPP_Coding_Practices.instructions.md).

Specifically look for:
1. Replaces `macros` with `constexpr`
2. Uses of `std::optional` instead of error codes/magic values
3. Opportunities for structured binding
