# Lesson 6: Debugging with GitHub Copilot

**Session Duration:** 45 minutes  
**Audience:** Embedded/C++ Developers (Intermediate to Advanced)  
**Environment:** Windows, VS Code  
**Extensions:** GitHub Copilot  
**Source Control:** GitHub/Bitbucket

---

## Overview

Debugging is where developers spend 30-50% of their time. This lesson teaches you how to leverage GitHub Copilot to dramatically reduce debugging overhead—from cryptic compiler errors to subtle race conditions.

**What You'll Learn:**
- Using `@terminal` to interpret and fix build/compiler errors instantly
- Using `/fix` to resolve logic bugs, race conditions, and memory issues
- Debugging the 5 most common embedded C++ bugs
- When to use agents (`@ODrive-Engineer`, `@ODrive-QA`) for complex debugging

**Key Tools:**
- **`@terminal`** - Build and compile error diagnosis
- **`/fix`** - Logic bug correction on selected code
- **`/explain`** - Understanding suspicious code
- **`@ODrive-Engineer`** - Complex multi-file debugging
- **`@ODrive-QA`** - Build verification and test generation

---

## Table of Contents

- [Overview](#overview)
- [Prerequisites](#prerequisites)
- [Available Agents and Skills](#available-agents-and-skills)
- [Why Debugging with Copilot Matters](#why-debugging-with-copilot-matters)
- [Learning Path](#learning-path)
- [@terminal for Build Errors](#1-terminal-for-build-errors-10-min)
- [/fix for Bug Resolution](#2-fix-for-bug-resolution-10-min)
- [Common C++ Debugging](#3-common-c-debugging-10-min)
- [Guided Debug Session](#4-guided-debug-session-15-min)
- [Practice Exercises](#practice-exercises)
- [Quick Reference](#quick-reference-debugging-tools)
- [Troubleshooting](#troubleshooting)
- [Additional Resources](#additional-resources)
- [Frequently Asked Questions](#frequently-asked-questions)
- [Summary: Key Takeaways](#summary-key-takeaways)

---

## Prerequisites

Before starting this session, ensure you have:

- **Completed C++ Best Practices** - Understanding of modern C++ patterns and embedded constraints
- **Visual Studio Code** with GitHub Copilot extensions installed and enabled
- **Active Copilot subscription** with access to all features
- **ODrive workspace** - Access to the ODrive firmware codebase for debugging exercises
- **Build environment** - Ability to compile firmware (tup/make configured)

### Verify Your Setup

1. **Test terminal access:**
   - Open integrated terminal: `Ctrl+`` (Control + backtick) or **View → Terminal**
   - Run a build command: `tup` or `make`
   - Verify you can see compiler output

2. **Test @terminal in chat:**
   - Open Chat view (Ctrl+Alt+I)
   - Type `@terminal` and verify it's recognized
   - Confirm terminal output is accessible to Copilot

3. **Test /fix command:**
   - Select any code snippet
   - Type `/fix` in chat
   - Verify command is recognized

---

## Available Agents and Skills

This repository includes several custom agents and skills that enhance debugging capabilities. Understanding when to use each agent is key to efficient debugging.

### Custom Agents

| Agent | Invocation | Purpose | Best For |
|-------|------------|---------|----------|
| **ODrive Engineer** | `@ODrive-Engineer` | Primary orchestrator for development tasks | Multi-file bugs, firmware development, complex analysis |
| **ODrive QA** | `@ODrive-QA` | Testing & QA orchestrator | Test generation, build verification, coverage analysis |
| **ODrive Reviewer** | `@ODrive-Reviewer` | Code review specialist | Style, safety, embedded best practices |
| **ODrive Toolchain** | `@ODrive-Toolchain` | Build & test operations | Building firmware, running tests, symbol search |
| **ODrive Ops** | `@ODrive-Ops` | CI/CD workflows | Release management, GitHub Actions |
| **Ada to C++ Migrator** | `@ada-to-cpp-migrator` | Language migration specialist | Migrating Ada code to Modern C++ |

### Available Skills

Skills are specialized capabilities that agents can invoke:

| Skill | Description | Status |
|-------|-------------|--------|
| **cpp-testing** | Unit test generation with doctest framework | ✅ Production |
| **odrive-toolchain** | Build firmware, run tests, symbol search | ✅ Production |
| **odrive-ops** | CI/CD workflows, releases, deployment | ✅ Production |
| **control-algorithms** | PID controllers, observers, control transformations | 🚧 Planned |
| **foc-tuning** | Automated FOC parameter tuning | 🚧 Planned |
| **sensorless-control** | Sliding mode observers, PLL, back-EMF estimation | 🚧 Planned |
| **pcb-review** | PCB schematic/layout review | 🚧 Planned |
| **signal-integrity** | Impedance calculation, EMI analysis | 🚧 Planned |
| **ada-cpp-migration** | Ada to Modern C++ migration patterns | ✅ Production |

### When to Use Which Agent

```
Build/compile error? ──→ @terminal (quick fix)
                    └─→ @ODrive-Toolchain (complex build issues)

Single-file logic bug? ──→ /fix (inline correction)

Multi-file bug? ──→ @ODrive-Engineer (orchestrated analysis)

Need tests? ──→ @ODrive-QA (test generation)

Code review? ──→ @ODrive-Reviewer (style & safety check)

CI/CD issue? ──→ @ODrive-Ops (workflow management)
```

---

## Why Debugging with Copilot Matters

Debugging is where developers spend 30-50% of their time. AI-assisted debugging can dramatically reduce this overhead.

### Benefits of Copilot-Assisted Debugging

1. **Faster Error Resolution**
   - AI interprets cryptic compiler errors instantly
   - Context-aware suggestions based on your codebase
   - Fix it right the first time, not after multiple Google searches

2. **Domain-Specific Insights**
   - Understands embedded constraints (no heap, ISR safety)
   - Recognizes common patterns in motor control code
   - Suggests fixes appropriate for real-time systems

3. **Learning Accelerator**
   - Explains WHY bugs occur, not just how to fix them
   - Teaches you to recognize patterns for next time
   - Builds debugging intuition faster

4. **Systematic Approach**
   - Guides you through debugging workflows
   - Suggests related areas to check
   - Helps verify fixes are complete

---

## Learning Path

This lesson covers four key debugging techniques. Work through them sequentially or jump to specific topics as needed.

| Topic | What You'll Learn | Estimated Time |
|-------|-------------------|----------------|
| @terminal for Build Errors | Compiler/linker error interpretation | 10 min |
| /fix for Bug Resolution | Logic bugs, race conditions, memory issues | 10 min |
| Common C++ Debugging | 5 most common embedded C++ bugs | 10 min |
| Guided Debug Session | Fix 3 bugs in motor control code | 15 min |

---

## 1. @terminal for Build Errors (10 min)

### Why @terminal is Powerful
**🎯 Copilot Modes: Chat**

**Files to demonstrate:**
- [src-ODrive/Firmware/MotorControl/motor.cpp](../../src-ODrive/Firmware/MotorControl/motor.cpp) - Common error source (for @terminal demos)

**Traditional Debugging:**
- Read cryptic compiler errors
- Google the error message
- Try to understand the root cause
- Make a guess at the fix
- Compile again... repeat

**With @terminal:**
- AI reads the error in context
- AI understands your codebase
- AI suggests specific fixes
- AI explains WHY the error occurred
- Fix it right the first time

### When to Use @terminal

✅ **Excellent for:**
- Compiler errors (syntax, type mismatches)
- Linker errors (undefined references, duplicate symbols)
- Build system issues (Make, CMake, Tup)
- Tool chain problems (missing dependencies)
- Warning messages you don't understand

❌ **Not ideal for:**
- Runtime logic errors (use /fix on the code instead)
- Performance profiling (need specialized tools)
- Memory leaks (use valgrind, then ask AI to interpret)

### @terminal Workflow
**🎯 Copilot Mode: Chat**

**Step 1: Trigger the error**
```powershell
# Run your build command
make -j4
# Or for ODrive:
tup
```

**Step 2: Copy error to Copilot Chat**

**💬 Chat Mode Prompt:**
```
@terminal shows this error: [paste error]

Can you explain what's wrong and suggest a fix?
```

**Step 3: Get context-aware explanation**
AI analyzes:
- The error message
- Your workspace files
- Recent changes
- Common patterns

**Step 4: Apply the fix**
AI suggests specific file changes with line numbers

### Common Compiler Error Types

#### 1. **Type Mismatch Errors**

**Example Error:**
```
motor.cpp:145:23: error: cannot convert 'float*' to 'const float&'
    update_current_control(phase_current);
                          ^~~~~~~~~~~~~
```

**💬 Chat Mode Prompt:**
```
@terminal shows type error on motor.cpp:145. 
Can you explain why phase_current can't convert and suggest the fix?
```

**AI Response:**
- Identifies function signature mismatch
- Shows the expected type
- Suggests: dereference pointer or change function signature

#### 2. **Undefined Reference (Linker Errors)**

**Example Error:**
```
undefined reference to `Encoder::update_pll_gains(float, float)'
```

**💬 Chat Mode Prompt:**
```
@terminal shows linker error for Encoder::update_pll_gains.
The declaration exists in encoder.hpp but linker can't find it.
What's wrong?
```

**AI Response:**
- Checks if function is defined in encoder.cpp
- Verifies function signature matches declaration
- Checks if encoder.cpp is included in build
- Suggests: add missing implementation or fix signature

#### 3. **Template Instantiation Errors**

**Example Error:**
```
template_controller.hpp:87:12: error: no matching function for call to 'min(unsigned int, int)'
    size_t len = std::min(buffer_size, count);
                 ^~~~~~~~
```

**💬 Chat Mode Prompt:**
```
@terminal shows template error with std::min. 
Types don't match (unsigned int vs int).
What's the best fix for embedded C++?
```

**AI Response:**
- Explains implicit conversion issues
- Suggests explicit cast or type consistency
- Recommends embedded-safe approach (no exceptions)

#### 4. **Missing Header / Include Errors**

**Example Error:**
```
axis.cpp:23:5: error: 'uint32_t' does not name a type
    uint32_t control_deadline_;
    ^~~~~~~~
```

**💬 Chat Mode Prompt:**
```
@terminal shows 'uint32_t' not recognized in axis.cpp.
Which header is missing?
```

**AI Response:**
- Identifies missing `#include <cstdint>` or `<stdint.h>`
- Checks existing includes
- Suggests proper header to add

### Demo Example: ODrive Build Error
**🎯 Copilot Mode: Chat**

**Scenario:** You're modifying motor.cpp and introduce a build error

**Error Message:**
```
[ tup ] motor.cpp:514:error: 'motor_current_limit' was not declared in this scope
[ tup ] Build failed
```

**💬 Chat Mode Prompt:**
```
@terminal shows compile error: 'motor_current_limit' not declared in motor.cpp:514

Context: I'm in the update() method trying to limit phase current.
What's the correct variable name and where is it defined?
```

**Expected AI Response:**
```
The error indicates 'motor_current_limit' is not in scope. Looking at motor.hpp,
the correct member variable is:

    motor_.config_.current_lim

Not 'motor_current_limit'. The current limit is accessed through the config struct.

Fix in motor.cpp line 514:
    float Iq_limit = motor_.config_.current_lim;

The config struct is defined in motor.hpp around line 45.
```

### Best Practices

**1. Provide Context**
```
Good: "@terminal shows error at motor.cpp:514. 
       I'm trying to access the current limit configuration."

Bad:  "@terminal fix this"
```

**2. Include the Full Error**
```
Good: [paste entire error including file, line, and message]

Bad:  "I got an error about uint32_t"
```

**3. Mention What You Were Doing**
```
"@terminal error after adding thermal monitoring to motor.cpp.
 I included thermistor.hpp but getting undefined reference."
```

**4. Ask for Explanation + Fix**
```
"@terminal can you explain this linker error AND suggest the fix?"
```

---

## 2. /fix for Bug Resolution (10 min)

### What is /fix?
**🎯 Copilot Modes: Chat (recommended) + Inline**

**Demo file:**
- [src-ODrive/Firmware/MotorControl/demo_buggy.cpp](../../src-ODrive/Firmware/MotorControl/demo_buggy.cpp) - Pre-created bugs for exercises

The `/fix` command is a **code-focused debugging assistant** that:
- Analyzes your code for bugs
- Suggests specific fixes
- Explains the root cause
- Can be applied directly to your code

### Chat vs Inline Mode

| Mode | Shortcut | Best For |
|------|----------|----------|
| **Chat** | `Ctrl+Alt+I` | Detailed explanations, multiple solutions, learning |
| **Inline** | `Ctrl+I` | Quick fixes, simple bugs, just apply the fix |

> **Tip:** For demos and learning, use **Chat mode** to see the full explanation.

### /fix vs @terminal

| @terminal | /fix |
|-----------|------|
| Build/compile errors | Logic bugs in code |
| Tool chain issues | Runtime errors |
| Linker problems | Algorithm mistakes |
| Error message interpretation | Code improvement |
| **Works on terminal output** | **Works on code selection** |

### /fix Workflow
**🎯 Copilot Mode: Chat (for detailed explanations)**

**Step 1: Select the buggy code**
- Highlight the function or block with the bug
- Or position cursor on the error line

**Step 2: Invoke /fix in Chat**
- Open Chat panel (`Ctrl+Alt+I`)
- Type `/fix` with description
- Or select code → Right-click → "Fix using Copilot"

> **Note:** Inline chat (`Ctrl+I`) gives quick fixes but less explanation. Use Chat mode for learning.

**Step 3: Review the suggestion**
- AI shows the fix with explanation
- You can accept, reject, or iterate

**Step 4: Test the fix**
- Apply the change
- Rebuild and test
- Iterate if needed

### Common Bug Types /fix Handles

#### 1. **Off-by-One Errors**

**File:** `demo_buggy.cpp` — FaultLogger class (lines 31-38)

**Buggy Code:**
```cpp
// Circular buffer implementation
void FaultLogger::log_fault(uint32_t error_code) {
    fault_history_[fault_idx_] = error_code;
    fault_idx_++;
    if (fault_idx_ > FAULT_HISTORY_SIZE) {  // BUG!
        fault_idx_ = 0;
    }
}
```

**💬 Chat Mode Prompt (Select code + /fix):**
```
/fix the circular buffer boundary check
```

**AI Response:**
```
Off-by-one error detected. The condition should be '>=' not '>'.

With FAULT_HISTORY_SIZE = 10, valid indices are 0-9.
Current code: fault_idx_ > 10 means it wraps at 11, causing buffer overflow.

Fix:
    if (fault_idx_ >= FAULT_HISTORY_SIZE) {
        fault_idx_ = 0;
    }
```

#### 2. **Null Pointer Dereference**

**Buggy Code:**
```cpp
void Axis::update_watchdog() {
    if (config_.watchdog_timeout > 0) {
        watchdog_timer_->reset();  // CRASH if watchdog_timer_ is nullptr!
    }
}
```

**💬 Chat Mode Prompt (Select code + /fix):**
```
/fix potential null pointer crash
```

**AI Response:**
```
Null pointer dereference risk. watchdog_timer_ might be nullptr
if watchdog is not enabled.

Fix:
    if (config_.watchdog_timeout > 0 && watchdog_timer_) {
        watchdog_timer_->reset();
    }

Or initialize watchdog_timer_ in constructor to avoid nullptr.
```

#### 3. **Race Conditions (Thread Safety)**

**File:** `demo_buggy.cpp` — Encoder class (lines 65-81)

**Buggy Code:**
```cpp
// Called from 8 kHz interrupt
void Encoder::update_isr() {
    int32_t delta = 10;
    count_ += delta;
    // RACE: Main loop reads these while ISR writes!
    position_estimate_ = (float)count_ / (float)cpr_;
    velocity_estimate_ = (float)delta / (float)cpr_ * 8000.0f;
}

// Called from main loop (1 kHz)
float Encoder::get_position() {
    return position_estimate_;  // RACE: ISR writes this!
}
```

**💬 Chat Mode Prompt (Select code + /fix):**
```
/fix thread safety issue between ISR and main loop

Context:
- ISR runs at 8 kHz
- Main loop at 1 kHz
- ARM Cortex-M4 (float not atomic)
- Need lowest-overhead solution
```

**AI Response:**
```
Race condition: ISR writes position_estimate_ while main loop reads it.
On ARM Cortex-M4, float is 32-bit but assignment isn't atomic.

Fixes:
1. Use atomic operations:
   std::atomic<float> position_estimate_;

2. Or disable interrupts during read:
   __disable_irq();
   float pos = position_estimate_;
   __enable_irq();

3. Or use a lock-free queue to pass data from ISR to main.

Recommendation for embedded: Option 2 (interrupt disable) is fastest.
```

#### 4. **Memory Leaks**

**Buggy Code:**
```cpp
void setup_can_filters() {
    CAN_FilterTypeDef* filter = new CAN_FilterTypeDef();  // LEAK!
    filter->FilterIdHigh = 0x123;
    HAL_CAN_ConfigFilter(&hcan, filter);
    // filter is never deleted!
}
```

**💬 Chat Mode Prompt (Select code + /fix):**
```
/fix memory leak
```

**AI Response:**
```
Memory leak: 'filter' is allocated with 'new' but never deleted.

However, for embedded systems, dynamic allocation is discouraged.

Better fix (no heap allocation):
    CAN_FilterTypeDef filter;  // Stack allocation
    filter.FilterIdHigh = 0x123;
    HAL_CAN_ConfigFilter(&hcan, &filter);
    // Automatically freed when function exits

If heap is required:
    std::unique_ptr<CAN_FilterTypeDef> filter = 
        std::make_unique<CAN_FilterTypeDef>();
```

#### 5. **Integer Overflow**

**File:** `demo_buggy.cpp` — SpeedCalculator class (lines 104-111)

**Buggy Code:**
```cpp
// BUG: Integer overflow at high speeds!
float SpeedCalculator::calculate_rpm() {
    int32_t delta_count = count_ - last_count_;
    int32_t delta_time_us = 125;  // 8 kHz = 125 μs

    // BUG: This intermediate calculation overflows int32_t at high speeds!
    // At 10,000 RPM: delta_count ≈ 1000
    // 1000 * 60 * 1000000 = 60,000,000,000 (exceeds int32_t max)
    int32_t rpm = (delta_count * 60 * 1000000) / (cpr_ * delta_time_us);

    return (float)rpm;
}
```

**💬 Chat Mode Prompt (Select code + /fix):**
```
/explain why this gives wrong values at high speeds
```

Then:
```
/fix use float math to avoid overflow
```

**AI Response:**
```
Integer overflow in the calculation:

At 10,000 RPM with delta_count = 1000:
    1000 * 60 * 1000000 = 60,000,000,000
    
This exceeds int32_t max value (2,147,483,647), causing overflow.

Fix - convert to float early:
    float calculate_rpm() {
        float delta_count = (float)(count_ - last_count_);
        float delta_time_s = 125e-6f;  // 125 μs in seconds
        float revolutions = delta_count / (float)cpr_;
        float rpm = (revolutions / delta_time_s) * 60.0f;
        return rpm;
    }
```

### /fix with Embedded Systems Context
**🎯 Copilot Mode: Chat**

When using `/fix` for embedded code, add context:

**💬 Chat Mode Prompt:**
```
/fix this interrupt handler

Context:
- Runs at 8 kHz (125μs period)
- Must complete in <50μs
- No heap allocation allowed
- MISRA C++ compliant
- ARM Cortex-M4 target
```

AI will provide fixes that respect these constraints!

---

## 3. Common C++ Debugging (10 min)

### The 5 Most Common C++ Bugs
**🎯 Copilot Modes: Chat + Agent**

> **Note:** For these common bugs, standard `/fix` and `@terminal` usually suffice. Use `@ODrive-Engineer` when you need deeper codebase analysis or when the bug spans multiple files.

**Demo file:**
- [src-ODrive/Firmware/MotorControl/demo_buggy.cpp](../../src-ODrive/Firmware/MotorControl/demo_buggy.cpp) - Pre-created bugs for exercises

#### 1. **Uninitialized Variables**

**Problem:**
```cpp
void Motor::calibrate() {
    float offset;  // Uninitialized!
    if (some_condition) {
        offset = measure_offset();
    }
    apply_calibration(offset);  // BUG: offset might be garbage
}
```

**How to Debug:**
```
Select code → /fix uninitialized variable
```

**Fix:**
```cpp
float offset = 0.0f;  // Always initialize!
```

**Copilot Tip:** Enable compiler warnings: `-Wuninitialized`

#### 2. **Buffer Overflows**

**Problem:**
```cpp
char message[32];
sprintf(message, "Axis %d: Position %.6f, Velocity %.6f", 
        axis_id, position, velocity);  // Might overflow!
```

**How to Debug:**
```
Select code → /fix buffer overflow risk
```

**Fix:**
```cpp
snprintf(message, sizeof(message), 
         "Axis %d: Pos %.3f, Vel %.3f", 
         axis_id, position, velocity);
```

**Copilot Tip:** Ask for `snprintf` replacements automatically

#### 3. **Dangling Pointers**

**Problem:**
```cpp
Motor* motor = &axis->motor_;
delete axis;  // Oops!
motor->update();  // CRASH: dangling pointer
```

**How to Debug:**
```
Select code → /fix dangling pointer after delete
```

**Fix:**
```cpp
// Option 1: Don't delete until done
motor->update();
delete axis;

// Option 2: Use smart pointers
std::unique_ptr<Axis> axis = std::make_unique<Axis>();
Motor* motor = &axis->motor_;
motor->update();
// axis deleted automatically, no dangling pointer risk
```

#### 4. **Const Correctness**

**Problem:**
```cpp
float Motor::get_temperature() {  // Should be const!
    return thermistor_.read();  // But read() isn't const either!
}

// Can't call on const motor:
void display(const Motor& motor) {
    float temp = motor.get_temperature();  // ERROR!
}
```

**How to Debug:**
```
Select code → /fix const correctness
```

**Fix:**
```cpp
float Motor::get_temperature() const {  // Add const
    return thermistor_.read();
}

// Also fix Thermistor::read():
float Thermistor::read() const {
    return last_reading_;  // Read from cached value
}
```

#### 5. **Volatile Misuse**

**Problem:**
```cpp
// Hardware register
volatile uint32_t* DMA_STATUS = (uint32_t*)0x40020400;

// BUG: Compiler might optimize away repeated reads!
while (*DMA_STATUS & DMA_BUSY) {
    // Wait...
}
```

**How to Debug:**
```
Select code → /fix volatile usage for hardware register
```

**Fix:**
```cpp
// Already correct IF DMA_STATUS is volatile
// But check the actual register definition:

// Good:
#define DMA1_SR  (*(volatile uint32_t*)0x40020400)

// Better (type-safe):
struct DMA_Regs {
    volatile uint32_t SR;   // Status register
    volatile uint32_t CR;   // Control register
};
DMA_Regs* const dma1 = (DMA_Regs*)0x40020000;

while (dma1->SR & DMA_BUSY) {
    // Compiler cannot optimize away volatile read
}
```

### Debugging Strategy with Copilot
**🎯 Copilot Modes: Chat + Agent**

> **Tip:** For complex debugging involving multiple files or domain expertise, use `@ODrive-Engineer` for firmware issues or `@ODrive-QA` for test-related debugging. The agents can invoke specialized skills like `cpp-testing` to build and verify fixes.

**Step 1: Reproduce the Bug**
- Can you trigger it consistently?
- What are the preconditions?

**Step 2: Isolate the Problem**

**🤖 Agent Mode Prompt:**
```
@workspace find all places where motor_current_limit is written
```

Or for more context-aware search:
```
@ODrive-Engineer Find all writes to motor_current_limit and explain the data flow
```

**Step 3: Examine Suspicious Code**

**💬 Chat Mode Prompt:**
```
Select function → "/explain why this might crash"
```

**Step 4: Apply Fix**

**💬 Chat Mode Prompt:**
```
Select code → "/fix the race condition"
```

**Step 5: Verify Fix**

**💬 Chat Mode Prompt:**
```
"Generate a unit test for this fix"
```

---

## 4. Guided Debug Session (15 min)

This guided session walks through debugging three real-world embedded bugs. Follow along to see the debugging techniques in action.

### Exercise: Fix Bugs in ODrive Motor Control
**🎯 Copilot Modes: Chat + Inline**

**Scenario:** You've inherited buggy motor control code with 3 known issues. Use Copilot to find and fix them!

**File to work with:**
- [src-ODrive/Firmware/MotorControl/demo_buggy.cpp](../../src-ODrive/Firmware/MotorControl/demo_buggy.cpp) - Contains all 3 bugs (FaultLogger, Encoder, SpeedCalculator classes)

---

### Bug 1: Off-By-One in Fault History (5 min)

**File:** `motor.cpp` (hypothetical buggy version)

**Buggy Code:**
```cpp
void Motor::log_current_fault() {
    if (current_faults_ > 0) {
        fault_history_[fault_write_idx_] = get_active_error();
        fault_write_idx_++;
        
        // BUG: Should this be > or >=?
        if (fault_write_idx_ > FAULT_HISTORY_SIZE) {
            fault_write_idx_ = 0;
        }
    }
}
```

**Your Task:**

**Step 1:** Identify the bug using Copilot
```
Select the function → Type in chat:
"/explain what's wrong with this circular buffer logic"
```

**Step 2:** Get the fix
```
"/fix the off-by-one error"
```

**Step 3:** Understand WHY it's wrong
```
"Why is >= correct but > is wrong for array bounds?"
```

**Expected Fix:**
```cpp
if (fault_write_idx_ >= FAULT_HISTORY_SIZE) {
    fault_write_idx_ = 0;
}
```

---

### Bug 2: Race Condition in Position Estimate (5 min)

**File:** `demo_buggy.cpp` — Encoder class (lines 55-82)

**Buggy Code:**
```cpp
// Called from 8 kHz interrupt
void Encoder::update() {
    count_ += get_delta();
    position_estimate_ = (float)count_ / (float)cpr_;  // RACE!
    velocity_estimate_ = calculate_velocity();          // RACE!
}

// Called from main loop (1 kHz)
void Axis::control_loop() {
    float pos = encoder_.position_estimate_;  // RACE!
    float vel = encoder_.velocity_estimate_;  // RACE!
    // Use pos and vel for control...
}
```

**Your Task:**

**Step 1:** Identify the race condition
```
Select both functions → Type:
"/fix thread safety between ISR and main loop"
```

**Step 2:** Evaluate proposed solutions
Copilot might suggest:
- Atomics
- Interrupt disabling
- Double buffering
- Volatile (not sufficient!)

**Step 3:** Choose the best for embedded
```
"Which fix has the lowest overhead for ARM Cortex-M4?"
```

**Expected Fix:**
```cpp
// Option 1: Disable interrupts briefly
void Axis::control_loop() {
    float pos, vel;
    __disable_irq();
    pos = encoder_.position_estimate_;
    vel = encoder_.velocity_estimate_;
    __enable_irq();
    // Use pos and vel...
}

// Option 2: Double buffering (copy in ISR)
void Encoder::update() {
    // ISR updates shadow copies
    shadow_position_ = (float)count_ / (float)cpr_;
    shadow_velocity_ = calculate_velocity();
    ready_flag_ = true;
}

void Encoder::get_estimates(float* pos, float* vel) {
    if (ready_flag_) {
        *pos = shadow_position_;
        *vel = shadow_velocity_;
        ready_flag_ = false;
    }
}
```

---

### Bug 3: Integer Overflow in Speed Calculation (5 min)

**File:** `demo_buggy.cpp` — SpeedCalculator class (lines 104-111)

**Buggy Code:**
```cpp
float SpeedCalculator::calculate_rpm() {
    int32_t delta_count = count_ - last_count_;
    int32_t delta_time_us = 125;  // 8 kHz
    
    // BUG: Intermediate overflow!
    // 1000 * 60 * 1000000 = 60 billion (exceeds int32_t max)
    int32_t rpm = (delta_count * 60 * 1000000) / (cpr_ * delta_time_us);
    
    return (float)rpm;
}
```

**Your Task:**

**Step 1:** Use Copilot Chat to detect overflow
1. Open `demo_buggy.cpp`, scroll to SpeedCalculator class (line 92)
2. Select lines 104-111 (the `calculate_rpm` function)
3. Open Chat (`Ctrl+Alt+I`) and type:
```
/explain why this gives wrong values at high speeds
```

**Step 2:** Understand the problem
```
Show me the math for when (delta_count * 60 * 1000000) overflows int32_t
```

**Step 3:** Apply the fix
```
"/fix use float math to avoid overflow"
```

**Expected Fix:**
```cpp
float Encoder::calculate_rpm() {
    int32_t delta_count = count_ - last_count_;
    float delta_time_s = 125e-6f;  // 125 μs in seconds
    
    // Convert to float early to avoid overflow
    float revolutions = (float)delta_count / (float)cpr_;
    float rps = revolutions / delta_time_s;
    float rpm = rps * 60.0f;
    
    return rpm;
}
```

---

## Practice Exercises

These exercises help you build debugging skills with Copilot. Try them on your own with the ODrive codebase.

### Exercise 1: @terminal for Build Errors

**Goal:** Use @terminal to diagnose and fix compiler errors.

**Scenario:** You've introduced a typo in motor.cpp and need to fix it.

**Steps:**

1. **Introduce an error** in `src-ODrive/Firmware/MotorControl/motor.cpp`:
   ```cpp
   // Change this:
   motor_.config_.current_lim
   // To this (typo):
   motor_.config_.current_limit  // Wrong name!
   ```

2. **Build the project:**
   ```powershell
   tup
   # Or: make
   ```

3. **Copy the error to Copilot Chat:**
   ```
   @terminal shows: motor.cpp:234:error: 'current_limit' is not a member of 'MotorConfig'
   
   I'm trying to access the motor current limit. What's the correct variable name?
   ```

4. **Apply the fix** suggested by Copilot.

5. **Rebuild to verify** the error is resolved.

**Expected Outcome:**
Copilot identifies that the correct member is `current_lim`, not `current_limit`, and suggests the fix.

**Key Learning:** Always include context about what you were trying to do, not just the error message.

---

### Exercise 2: /fix for Off-By-One Bug

**Goal:** Use /fix to correct a common circular buffer bug.

**Buggy Code:**
```cpp
void Motor::log_fault(Error error) {
    fault_history_[fault_index_] = error;
    fault_index_++;
    if (fault_index_ > FAULT_HISTORY_SIZE) {  // BUG!
        fault_index_ = 0;
    }
}
```

**Steps:**

1. **Select the buggy code** in your editor.

2. **Ask Copilot to fix it:**
   ```
   /fix this circular buffer logic - check the bounds condition
   ```

3. **Review the explanation:**
   - Why is `>` wrong?
   - Why is `>=` correct?

4. **Ask for deeper understanding:**
   ```
   "If FAULT_HISTORY_SIZE is 10, what indices are valid? Why does > 10 cause problems?"
   ```

**Expected Fix:**
```cpp
if (fault_index_ >= FAULT_HISTORY_SIZE) {
    fault_index_ = 0;
}
```

**Explanation:** With `FAULT_HISTORY_SIZE = 10`, valid indices are 0-9. Using `> 10` means the buffer wraps at index 11, causing a buffer overflow. Using `>= 10` correctly wraps at index 10.

---

### Exercise 3: /fix for Race Condition

**Goal:** Identify and fix ISR/main loop race conditions.

**Buggy Code:**
```cpp
// Called from 8 kHz interrupt
void Encoder::update() {
    position_estimate_ = (float)count_ / (float)cpr_;
}

// Called from main loop (1 kHz)
float Axis::get_position() {
    return encoder_.position_estimate_;  // RACE!
}
```

**Steps:**

1. **Select both functions** in your editor.

2. **Ask Copilot to fix thread safety:**
   ```
   /fix thread safety issue between ISR and main loop
   
   Context:
   - ARM Cortex-M4 target
   - Lowest overhead solution preferred
   - Cannot use mutexes in ISR
   ```

3. **Evaluate the proposed solutions:**
   Copilot might suggest:
   - Atomic operations
   - Interrupt disabling
   - Double buffering
   - (volatile alone is NOT sufficient!)

4. **Choose the best for embedded:**
   ```
   "Which solution has lowest overhead for ARM Cortex-M4?"
   ```

**Expected Fix (interrupt disable):**
```cpp
float Axis::get_position() {
    __disable_irq();
    float pos = encoder_.position_estimate_;
    __enable_irq();
    return pos;
}
```

**Why This Works:** On ARM Cortex-M4, disabling interrupts briefly (a few cycles) is cheaper than atomics or mutexes, and guarantees consistent reads.

---

### Exercise 4: /fix for Integer Overflow

**Goal:** Detect and fix integer overflow in calculations.

**Buggy Code:**
```cpp
float Encoder::calculate_rpm() {
    int32_t delta_count = count_ - last_count_;
    int32_t delta_time_us = 125;  // 8 kHz = 125 μs
    
    // BUG: Intermediate overflow!
    int32_t rpm = (delta_count * 60 * 1000000) / (cpr_ * delta_time_us);
    return (float)rpm;
}
```

**Steps:**

1. **Select the function** and ask Copilot:
   ```
   /fix potential integer overflow in RPM calculation
   ```

2. **Understand the math:**
   ```
   "Show me when delta_count * 60 * 1000000 overflows int32_t"
   ```
   
   Answer: `INT32_MAX / 60000000 = ~35`, so any delta > 35 counts causes overflow!

3. **Apply the fix:**

**Expected Fix:**
```cpp
float Encoder::calculate_rpm() {
    int32_t delta_count = count_ - last_count_;
    float delta_time_s = 125e-6f;  // 125 μs in seconds
    
    // Convert to float EARLY to avoid overflow
    float revolutions = static_cast<float>(delta_count) / static_cast<float>(cpr_);
    float rps = revolutions / delta_time_s;
    return rps * 60.0f;
}
```

**Key Learning:** Always cast to float BEFORE multiplication when dealing with large intermediate values.

---

### Exercise 5: Multi-File Debugging with @ODrive-Engineer

**Goal:** Use the agent for bugs that span multiple files.

**Scenario:** Motor oscillates at startup but you're not sure which file contains the bug.

**Steps:**

1. **Describe the symptom to the agent:**
   ```
   @ODrive-Engineer The motor oscillates during startup calibration.
   
   Symptoms:
   - Oscillation frequency ~50Hz
   - Happens only during encoder calibration
   - Motor runs fine after calibration completes
   
   Files that might be involved:
   - src-ODrive/Firmware/MotorControl/encoder.cpp
   - src-ODrive/Firmware/MotorControl/axis.cpp
   - src-ODrive/Firmware/MotorControl/motor.cpp
   
   Can you analyze the calibration sequence and identify potential causes?
   ```

2. **Follow the agent's analysis** - it will search across files.

3. **Ask for verification:**
   ```
   @ODrive-QA After I apply this fix, how can I verify it worked?
   ```

**Key Learning:** Use `@ODrive-Engineer` when bugs span multiple files or require codebase-wide understanding. Use `@ODrive-QA` to verify fixes and generate tests.

---

## Quick Reference: Debugging Tools

### Tool Comparison

| Tool | Use Case | Input | Output |
|------|----------|-------|--------|
| `@terminal` | Build/compile errors | Terminal output | Diagnosis + fix |
| `/fix` | Logic bugs | Selected code | Code correction |
| `/explain` | Understanding code | Selected code | Explanation |
| `@workspace` | Finding code | Search query | File locations |
| `@ODrive-Engineer` | Complex multi-file bugs | Description + context | Analysis + orchestrated fix |
| `@ODrive-QA` | Test failures, build issues | Test output + context | Diagnosis + test suggestions |

### @terminal Prompts

| Scenario | Prompt Template |
|----------|-----------------|
| Type mismatch | `@terminal shows type error on [file]:[line]. Explain and suggest fix.` |
| Undefined reference | `@terminal linker error for [symbol]. Declaration in [header] but linker can't find it.` |
| Missing header | `@terminal shows '[type]' not recognized. Which header is missing?` |
| Template error | `@terminal template error with [function]. Types don't match. Best fix for embedded?` |

### /fix Prompts

| Bug Type | Prompt Template |
|----------|-----------------|
| Off-by-one | `/fix this circular buffer logic` |
| Null pointer | `/fix potential null pointer crash` |
| Race condition | `/fix thread safety between ISR and main loop` |
| Memory leak | `/fix memory leak` |
| Integer overflow | `/fix potential integer overflow` |

### Debugging Workflow

```
1. Reproduce the bug
   ↓
2. @workspace: Find related code
   (or @ODrive-Engineer for deeper analysis)
   ↓
3. /explain: Understand the logic
   ↓
4. /fix: Get suggested fix
   ↓
5. @terminal: If build fails
   (or @ODrive-QA to invoke build skill)
   ↓
6. Test the fix
   ↓
7. @ODrive-QA: Generate regression test
```

---

## Troubleshooting

| Issue | Possible Cause | Debug Tips |
|-------|----------------|------------|
| @terminal not recognizing errors | Terminal output not captured | Copy/paste error directly into chat |
| /fix suggests wrong fix | Insufficient context | Add constraints: "embedded, no heap, ISR-safe" |
| Fix doesn't compile | AI missed type or signature | Provide more surrounding code context |
| Race condition fix too slow | Used mutex in ISR | Ask for "lowest overhead fix for Cortex-M4" |
| Overflow fix changes behavior | Float precision differs | Specify precision requirements in prompt |
| AI suggests heap allocation | Didn't specify embedded | Add "static allocation only, no new/malloc" |
| Need multi-file analysis | Bug spans multiple modules | Use `@ODrive-Engineer` for orchestrated debugging |
| Build verification needed | Want to test fix compiles | Use `@ODrive-QA` to invoke build skill |

### Common Mistakes to Avoid

1. **Vague prompts:** Always include file, line, and what you're trying to do
2. **Accepting blindly:** Review every fix before applying
3. **Skipping rebuild:** Always rebuild after applying fixes
4. **Missing constraints:** Specify embedded requirements (no exceptions, static alloc)
5. **Not iterating:** If first fix is wrong, provide more context and try again

---

## Additional Resources

### Official Documentation

- [GitHub Copilot Chat Documentation](https://docs.github.com/en/copilot/github-copilot-chat)
- [VS Code Debugging](https://code.visualstudio.com/docs/editor/debugging)
- [C++ Debugging in VS Code](https://code.visualstudio.com/docs/cpp/cpp-debug)

### ODrive Reference Files

- [src-ODrive/Firmware/MotorControl/motor.cpp](../../src-ODrive/Firmware/MotorControl/motor.cpp) - Motor implementation
- [src-ODrive/Firmware/MotorControl/demo_buggy.cpp](../../src-ODrive/Firmware/MotorControl/demo_buggy.cpp) - Demo bugs for exercises
- [src-ODrive/Firmware/MotorControl/axis.cpp](../../src-ODrive/Firmware/MotorControl/axis.cpp) - State machine

### Further Practice

- Enable all compiler warnings: `-Wall -Wextra -Wpedantic`
- Use static analysis: `cppcheck`, `clang-tidy`
- Ask Copilot to explain warning messages

---

## Frequently Asked Questions

### When should I use @terminal vs /fix?

| Use `@terminal` for: | Use `/fix` for: |
|---------------------|-----------------|
| Build/compile errors | Logic bugs in code |
| Linker errors | Runtime behavior issues |
| Tool chain problems | Algorithm mistakes |
| Warning messages | Code improvement |
| **Input: Terminal output** | **Input: Selected code** |

**Rule of thumb:** If the error came from the terminal, use `@terminal`. If the bug is in the code logic, use `/fix`.

### When should I use @ODrive-Engineer vs /fix?

| Use `/fix` when: | Use `@ODrive-Engineer` when: |
|------------------|------------------------------|
| Bug is in one file | Bug spans multiple files |
| Clear, localized issue | Need codebase-wide search |
| Quick fix needed | Need deep analysis |
| Simple logic error | Complex architectural issue |

**Example:** Off-by-one in a loop → `/fix`. Motor oscillation involving encoder + axis + motor files → `@ODrive-Engineer`.

### Does /fix work for all bugs?

No. `/fix` is best for:
- ✅ Clear logical errors (off-by-one, null checks)
- ✅ Type mismatches
- ✅ Simple race conditions
- ✅ Memory issues with obvious patterns

Less effective for:
- ❌ Complex architectural problems
- ❌ Bugs requiring runtime context
- ❌ Issues requiring domain expertise
- ❌ Performance problems

For complex issues, use `@ODrive-Engineer` to get deeper analysis.

### Can Copilot debug hardware issues?

**Partially.** Copilot can help if you describe the symptoms:

```
"Motor stutters at high speed" 
→ AI suggests checking control loop timing, PWM frequency

"ADC readings are noisy"
→ AI suggests checking sampling rate, filtering, grounding

"CAN bus errors under load"
→ AI suggests checking termination, baud rate, buffer sizes
```

**But** Copilot cannot debug physical hardware faults (blown components, wiring issues, etc.).

### What if the fix doesn't work?

1. **Iterate with more context:**
   ```
   "That fix didn't work. The error now is: [new error].
   Additional context: [what you learned]"
   ```

2. **Ask for alternatives:**
   ```
   "What other ways could I fix this race condition?"
   ```

3. **Add constraints:**
   ```
   "Fix this but the solution must be interrupt-safe and use no heap"
   ```

4. **Break it down:**
   ```
   "Let's debug this step by step. First, explain what this function does."
   ```

### Should I trust AI fixes blindly?

**NO!** Always:
1. ✅ **Review** - Read and understand the fix
2. ✅ **Test** - Rebuild and verify behavior
3. ✅ **Verify constraints** - Check it respects your requirements (no heap, ISR-safe, etc.)
4. ✅ **Consider edge cases** - AI might miss unusual scenarios
5. ✅ **Ask for explanation** - "Why does this fix work?"

**Remember:** You're responsible for the code, not the AI.

### How do I add embedded constraints to prompts?

Always include constraints relevant to your environment:

```
/fix this function

Constraints:
- ARM Cortex-M4 target
- No heap allocation (static only)
- Must complete in < 50μs
- MISRA C++ compliant
- ISR-safe (no blocking)
```

This helps Copilot generate appropriate fixes for embedded systems.

### Can I use Copilot for debugging without custom agents?

Yes! The core tools work without custom agents:
- `@terminal` - Works with any terminal output
- `/fix` - Works on any code selection
- `/explain` - Works on any code selection
- `@workspace` - Works on any workspace

Custom agents (`@ODrive-Engineer`, `@ODrive-QA`) add domain expertise and can invoke specialized skills, but aren't required for basic debugging.

---

## Summary: Key Takeaways

1. **`@terminal`** - Interprets build errors in context; give it the full error message
2. **`/fix`** - Fixes logic bugs; select the code first
3. **`@ODrive-Engineer`** - For complex, multi-file debugging
4. **`@ODrive-QA`** - For build verification and test generation
5. **Context is crucial** - Tell AI what you're trying to do, not just the error
6. **Add constraints** - Specify embedded requirements (no heap, ISR-safe, etc.)
7. **Iterate** - First fix might not be perfect; provide more context
8. **Always review** - Understand the fix before accepting
9. **Test thoroughly** - Rebuild and verify after every fix
10. **Learn from it** - Ask AI to explain WHY the bug occurred

**The Debugging Workflow:**
```
1. @terminal for build errors
   ↓
2. /fix for logic bugs  
   ↓
3. @ODrive-Engineer for complex issues
   ↓
4. @ODrive-QA to verify fixes
   ↓
5. Test and iterate
```

**Remember:** Copilot is a debugging accelerator, not a replacement for understanding your code!

---

*GitHub Copilot Hackathon - Debugging with Copilot Guide*

*Last Updated: January 2026*
