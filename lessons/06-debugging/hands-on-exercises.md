# Section 6: Hands-On Debugging Exercises

**Duration:** 15 minutes  
**Format:** Individual practice  
**Goal:** Apply @terminal and /fix to debug real code issues

---

## Exercise Overview

You'll debug **3 bugs** in ODrive-style motor control code. Each uses different Copilot debugging techniques.

| Bug | Technique | Difficulty | Time |
|-----|-----------|------------|------|
| 1. Circular Buffer | /fix | ⭐⭐ Medium | 5 min |
| 2. Race Condition | /fix + context | ⭐⭐⭐ Advanced | 5 min |
| 3. Integer Overflow | /explain + /fix | ⭐⭐ Medium | 5 min |

---

## Setup

### Demo File
All three bugs are in a single pre-created file:
- **`src-ODrive/Firmware/MotorControl/demo_buggy.cpp`** - Contains all bugs for exercises

Open this file in VS Code before starting.

### Bug Locations in demo_buggy.cpp
| Bug | Class | Lines |
|-----|-------|-------|
| 1. Circular Buffer | `FaultLogger` | 31-38 |
| 2. Race Condition | `Encoder` | 65-81 |
| 3. Integer Overflow | `SpeedCalculator` | 104-111 |

### If demo_buggy.cpp Doesn't Exist

<details>
<summary>Click to expand full file contents — copy/paste to create the file</summary>

Create `src-ODrive/Firmware/MotorControl/demo_buggy.cpp` with this content:

```cpp
/**
 * @file demo_buggy.cpp
 * @brief Demo file for Section 6: Debugging with Copilot
 * 
 * This file contains intentional bugs for demonstration purposes.
 * DO NOT include in production builds!
 * 
 * Bugs included:
 * 1. Off-by-one error in circular buffer (log_fault)
 * 2. Race condition between ISR and main loop
 * 3. Integer overflow in RPM calculation
 */

#include <cstdint>
#include <cstdio>

//=============================================================================
// Bug 1: Off-By-One Error in Circular Buffer
//=============================================================================

#define FAULT_HISTORY_SIZE 10

class FaultLogger {
private:
    uint32_t fault_history_[FAULT_HISTORY_SIZE];
    size_t fault_idx_ = 0;

public:
    // BUG: Can you spot the off-by-one error?
    void log_fault(uint32_t error_code) {
        fault_history_[fault_idx_] = error_code;
        fault_idx_++;
        
        // BUG: Should this be > or >=?
        if (fault_idx_ > FAULT_HISTORY_SIZE) {
            fault_idx_ = 0;
        }
    }

    void print_faults() {
        printf("Fault History:\n");
        for (size_t i = 0; i < FAULT_HISTORY_SIZE; i++) {
            printf("  [%zu]: 0x%08X\n", i, fault_history_[i]);
        }
    }
    
    size_t get_index() const { return fault_idx_; }
};

//=============================================================================
// Bug 2: Race Condition (ISR vs Main Loop)
//=============================================================================

class Encoder {
private:
    int32_t count_ = 0;
    int32_t last_count_ = 0;
    float position_estimate_ = 0.0f;
    float velocity_estimate_ = 0.0f;
    int32_t cpr_ = 8192;  // Counts per revolution

public:
    // Called from 8 kHz interrupt
    void update_isr() {
        int32_t delta = 10;  // Simulated hardware read
        count_ += delta;
        last_count_ = count_ - delta;
        
        // RACE: Main loop reads these while ISR writes!
        position_estimate_ = (float)count_ / (float)cpr_;
        velocity_estimate_ = (float)delta / (float)cpr_ * 8000.0f;
    }

    // Called from main loop (1 kHz)
    float get_position() {
        return position_estimate_;  // RACE: ISR writes this!
    }

    float get_velocity() {
        return velocity_estimate_;  // RACE: ISR writes this!
    }
};

//=============================================================================
// Bug 3: Integer Overflow in Speed Calculation
//=============================================================================

class SpeedCalculator {
private:
    int32_t count_ = 0;
    int32_t last_count_ = 0;
    int32_t cpr_ = 8192;  // Counts per revolution

public:
    void set_counts(int32_t current, int32_t last) {
        count_ = current;
        last_count_ = last;
    }

    // BUG: Integer overflow at high speeds!
    float calculate_rpm() {
        int32_t delta_count = count_ - last_count_;
        int32_t delta_time_us = 125;  // 8 kHz = 125 μs

        // BUG: This intermediate calculation overflows int32_t at high speeds!
        // At 10,000 RPM: delta_count ≈ 1000
        // 1000 * 60 * 1000000 = 60,000,000,000 (exceeds int32_t max of 2,147,483,647)
        int32_t rpm = (delta_count * 60 * 1000000) / (cpr_ * delta_time_us);

        return (float)rpm;
    }
};

//=============================================================================
// Test Harness (for manual testing)
//=============================================================================

#ifdef DEMO_MAIN
int main() {
    printf("=== Bug 1: Off-By-One Error Demo ===\n");
    FaultLogger logger;
    
    // Log 15 faults - should wrap around safely
    for (int i = 0; i < 15; i++) {
        printf("Logging fault %d, index before: %zu\n", i, logger.get_index());
        logger.log_fault(0x1000 + i);
    }
    logger.print_faults();
    
    printf("\n=== Bug 3: Integer Overflow Demo ===\n");
    SpeedCalculator calc;
    
    // Low speed - should work
    calc.set_counts(100, 0);
    printf("Low speed (100 delta): %.1f RPM\n", calc.calculate_rpm());
    
    // High speed - will overflow!
    calc.set_counts(1000, 0);
    printf("High speed (1000 delta): %.1f RPM (OVERFLOW!)\n", calc.calculate_rpm());
    
    return 0;
}
#endif
```

</details>

---

## Bug 1: Off-By-One in Circular Buffer (5 min)

### Background
The motor controller logs the last 10 faults in a circular buffer. Users report that sometimes the system crashes when logging the 11th fault.

### Buggy Code

**File:** `src-ODrive/Firmware/MotorControl/demo_buggy.cpp` — `FaultLogger` class (lines 24-48)

```cpp
#define FAULT_HISTORY_SIZE 10

class FaultLogger {
private:
    uint32_t fault_history_[FAULT_HISTORY_SIZE];
    size_t fault_idx_ = 0;

public:
    // BUG: Can you spot the off-by-one error?
    void log_fault(uint32_t error_code) {
        fault_history_[fault_idx_] = error_code;
        fault_idx_++;
        
        // BUG: Should this be > or >=?
        if (fault_idx_ > FAULT_HISTORY_SIZE) {
            fault_idx_ = 0;
        }
    }
};
```

### Your Task

**Step 1: Identify the Bug (2 min)**

1. Open `demo_buggy.cpp` and scroll to the `FaultLogger` class (line 24)
2. **Select lines 31-38** (the `log_fault` function)
3. Open **Copilot Chat** panel (`Ctrl+Alt+I`)
4. Type:
```
/fix the circular buffer boundary check
```

> **Note:** Use Chat mode (not inline `Ctrl+I`) to get detailed explanation of WHY it's wrong.

**Questions to answer:**
- What's wrong with `if (fault_idx_ > FAULT_HISTORY_SIZE)`?
- What should it be instead?
- Why does this cause a crash?

**Step 2: Apply the Fix (1 min)**

Change the code based on Copilot's suggestion.

**Step 3: Verify (2 min)**

Ask Copilot to generate a test:
```
@ODrive-QA Generate a unit test that logs 15 faults and verifies no crash
```

> **Note:** Using `@ODrive-QA` invokes the `cpp-testing` skill for test generation.

Run the test mentally or with a simple main():
```cpp
int main() {
    Motor motor;
    for (int i = 0; i < 15; i++) {
        motor.log_fault(0x1000 + i);
    }
    motor.print_faults();
    return 0;
}
```

### Success Criteria
- ✅ Understand why `>` is wrong and `>=` is correct
- ✅ Code handles wrapping correctly at index 9 → 0
- ✅ No buffer overflow when logging 15+ faults

### Solution

<details>
<summary>Click to reveal solution</summary>

**The Bug:**
```cpp
if (fault_idx_ > FAULT_HISTORY_SIZE) {  // BUG!
```

With `FAULT_HISTORY_SIZE = 10`, valid indices are 0-9.
- When `fault_idx_` reaches 10, it's NOT > 10, so it doesn't wrap
- Next iteration tries to access `fault_history_[10]` → Buffer overflow!

**The Fix:**
```cpp
if (fault_idx_ >= FAULT_HISTORY_SIZE) {  // CORRECT
    fault_idx_ = 0;
}
```

Now when `fault_idx_` reaches 10, it equals `FAULT_HISTORY_SIZE`, wraps to 0.

</details>

---

## Bug 2: Race Condition (5 min)

### Background
The encoder updates position estimates in an 8 kHz interrupt. The main control loop reads these estimates at 1 kHz. On an ARM Cortex-M4, float assignments are not atomic, leading to corrupted position readings.

### Buggy Code

**File:** `src-ODrive/Firmware/MotorControl/demo_buggy.cpp` — `Encoder` class (lines 65-81)

```cpp
class Encoder {
private:
    int32_t count_ = 0;
    int32_t last_count_ = 0;
    float position_estimate_ = 0.0f;
    float velocity_estimate_ = 0.0f;
    int32_t cpr_ = 8192;  // Counts per revolution

public:
    // Called from 8 kHz interrupt
    void update_isr() {
        int32_t delta = 10;  // Simulated hardware read
        count_ += delta;
        last_count_ = count_ - delta;
        
        // RACE: Main loop reads these while ISR writes!
        position_estimate_ = (float)count_ / (float)cpr_;
        velocity_estimate_ = (float)delta / (float)cpr_ * 8000.0f;
    }

    // Called from main loop (1 kHz)
    float get_position() {
        return position_estimate_;  // RACE: ISR writes this!
    }

    float get_velocity() {
        return velocity_estimate_;  // RACE: ISR writes this!
    }
};
```

### Your Task

**Step 1: Identify the Race (2 min)**

1. In `demo_buggy.cpp`, scroll to the `Encoder` class (line 55)
2. **Select lines 65-81** (both `update_isr()` and `get_position()`/`get_velocity()` functions)
3. Open **Copilot Chat** panel (`Ctrl+Alt+I`)
4. Type:
```
/fix thread safety issue between ISR and main loop

Context:
- ISR runs at 8 kHz (every 125 μs)
- Main loop at 1 kHz (every 1 ms)
- ARM Cortex-M4 (float not atomic)
- Need lowest overhead solution
```

> **Note:** Chat mode gives multiple solutions with trade-off analysis. Inline chat would just apply one fix.

**Questions to answer:**
- Why is this a race condition?
- What can go wrong when main loop reads during ISR write?
- Which Copilot suggestion has the lowest overhead?

> **Tip:** For complex race conditions spanning multiple files, use `@ODrive-Engineer` for deeper codebase analysis.

**Step 2: Evaluate Solutions (2 min)**

Copilot might suggest:
1. **Disable interrupts** during read
2. **Double buffering** (shadow copies)
3. **Atomic variables** (std::atomic<float>)
4. **Volatile** (NOT sufficient!)

Ask Copilot:
```
Which solution has lowest overhead for 8 kHz ISR on ARM Cortex-M4?
```

**Step 3: Apply the Fix (1 min)**

Implement the recommended solution.

### Success Criteria
- ✅ Understand why float read/write isn't atomic
- ✅ Know multiple solutions and their trade-offs
- ✅ Choose the lowest-overhead solution
- ✅ Explain when to use each approach

### Solution

<details>
<summary>Click to reveal solution</summary>

**The Race:**
On ARM Cortex-M4, float is 32-bit but load/store isn't guaranteed atomic:
```
Float write:  [byte0][byte1][byte2][byte3]
                 ↑ ISR interrupted here
Float read:   [OLD0][OLD1][NEW2][NEW3]  ← Corrupted!
```

**Solution 1: Disable Interrupts (Lowest Overhead - ~10 cycles)**
```cpp
float Encoder::get_position() {
    __disable_irq();
    float pos = position_estimate_;
    __enable_irq();
    return pos;
}

float Encoder::get_velocity() {
    __disable_irq();
    float vel = velocity_estimate_;
    __enable_irq();
    return vel;
}
```

**Solution 2: Double Buffering (More Complex)**
```cpp
class Encoder {
private:
    float position_shadow_ = 0.0f;
    float velocity_shadow_ = 0.0f;
    volatile bool ready_ = false;
    
public:
    void update_isr() {
        // ... calculate ...
        position_shadow_ = new_position;
        velocity_shadow_ = new_velocity;
        ready_ = true;
    }
    
    float get_position() {
        if (ready_) {
            position_estimate_ = position_shadow_;
            ready_ = false;
        }
        return position_estimate_;
    }
};
```

**Solution 3: Atomic (C++11, might not compile on all embedded)**
```cpp
std::atomic<float> position_estimate_;
std::atomic<float> velocity_estimate_;
```

**Recommended for embedded:** Solution 1 (interrupt disable) - simple, fast, predictable.

</details>

---

## Bug 3: Integer Overflow in Speed Calculation (5 min)

### Background
The encoder calculates motor RPM from tick counts. At low speeds it works fine, but at high speeds (>10,000 RPM), the displayed value jumps to huge numbers like 2 billion RPM.

### Buggy Code

**File:** `src-ODrive/Firmware/MotorControl/demo_buggy.cpp` — `SpeedCalculator` class (lines 104-111)

```cpp
class SpeedCalculator {
private:
    int32_t count_ = 0;
    int32_t last_count_ = 0;
    int32_t cpr_ = 8192;  // Counts per revolution

public:
    void set_counts(int32_t current, int32_t last) {
        count_ = current;
        last_count_ = last;
    }

    // BUG: Integer overflow at high speeds!
    float calculate_rpm() {
        int32_t delta_count = count_ - last_count_;
        int32_t delta_time_us = 125;  // 8 kHz = 125 μs

        // BUG: This intermediate calculation overflows int32_t at high speeds!
        // At 10,000 RPM: delta_count ≈ 1000
        // 1000 * 60 * 1000000 = 60,000,000,000 (exceeds int32_t max of 2,147,483,647)
        int32_t rpm = (delta_count * 60 * 1000000) / (cpr_ * delta_time_us);

        return (float)rpm;
    }
};
```

### Your Task

**Step 1: Understand the Bug (2 min)**

1. In `demo_buggy.cpp`, scroll to the `SpeedCalculator` class (line 92)
2. **Select lines 104-111** (the `calculate_rpm` function)
3. Open **Copilot Chat** panel (`Ctrl+Alt+I`)
4. Type:
```
/explain why this gives wrong values at high speeds
```

> **Note:** `/explain` in Chat mode provides detailed analysis with math breakdown.

**Questions to answer:**
- At what motor speed does overflow occur?
- What is the intermediate value that overflows?
- What's the max value of int32_t?

**Hint:** At 10,000 RPM, delta_count ≈ 1000 per 125 μs

**Step 2: Calculate Overflow Point (1 min)**

Ask Copilot:
```
Show me the math for when (delta_count * 60 * 1000000) overflows int32_t
```

**Step 3: Get the Fix (1 min)**

With the same code selected, type:
```
/fix use float math to avoid overflow
```

**Step 4: Verify with Test (1 min)**

Ask:
```
@ODrive-QA Generate a unit test for calculate_rpm that tests speeds from 100 to 50,000 RPM
```

> **Note:** `@ODrive-QA` will invoke the `cpp-testing` skill to create comprehensive test cases.

### Success Criteria
- ✅ Understand intermediate overflow concept
- ✅ Know int32_t max value (2,147,483,647)
- ✅ Fix by converting to float early
- ✅ More readable and accurate calculation

### Solution

<details>
<summary>Click to reveal solution</summary>

**The Overflow:**
```cpp
// At 10,000 RPM: delta_count ≈ 1000
int32_t rpm = (delta_count * 60 * 1000000) / (cpr_ * delta_time_us);
              ^^^^^^^^^^^^^^^^^^^^^^^^^
              1000 * 60 * 1000000 = 60,000,000,000
              
Max int32_t: 2,147,483,647
60 billion > 2.1 billion → OVERFLOW!
```

**The Fix:**
```cpp
float Encoder::calculate_rpm() {
    int32_t delta_count = count_ - last_count_;
    last_count_ = count_;
    
    float delta_time_s = 125e-6f;  // 125 μs = 0.000125 s
    
    // Convert to float early - no overflow
    float revolutions = (float)delta_count / (float)cpr_;
    float rps = revolutions / delta_time_s;  // Revolutions per second
    float rpm = rps * 60.0f;
    
    return rpm;
}
```

**Why This Works:**
- float range: ±3.4e38 (way more than we need)
- No integer division (more accurate)
- More readable (clear units)

**Bonus: Optimize Further**
```cpp
// Precompute constants
static constexpr float SCALE = 60.0f / (8192.0f * 125e-6f);  // = 58593.75

float calculate_rpm() {
    int32_t delta_count = count_ - last_count_;
    last_count_ = count_;
    return (float)delta_count * SCALE;
}
```

</details>

---

## Bonus Challenge (If Time Permits)

### Bug 4: Memory Leak in Configuration

**Buggy Code:**
```cpp
void load_motor_config(const char* filename) {
    MotorConfig* config = new MotorConfig();  // LEAK!
    
    // Load from file
    FILE* f = fopen(filename, "r");
    if (f) {
        fread(config, sizeof(MotorConfig), 1, f);
        fclose(f);
    }
    
    apply_motor_config(config);
    // config is never deleted!
}
```

**Task:**
1. Use `/fix memory leak`
2. Get embedded-friendly solution (no heap allocation)
3. Alternative: Use smart pointers if heap is required

---

## General Tips for All Exercises

### Debugging Workflow
```
1. Read the bug description
   ↓
2. Look at the code and try to spot the bug
   ↓
3. Use /explain or /fix to get AI help
   ↓
4. Understand the root cause
   ↓
5. Apply the fix
   ↓
6. Ask for unit test
   ↓
7. Verify fix works
```

### Using Copilot Effectively

**For Compile Errors:**
```
@terminal shows error: [paste error]
Context: [what you were trying to do]
```

**For Logic Bugs (Single File):**
```
/fix [description of problem]
Context: [constraints, platform, timing]
```

**For Complex Multi-File Bugs:**
```
@ODrive-Engineer analyze this bug:
[description]
Context: [files involved, expected vs actual behavior]
```

**For Understanding:**
```
/explain why [specific behavior]
```

**For Testing & Build Verification:**
```
@ODrive-QA Generate a unit test that would catch this bug
@ODrive-QA Verify the fix compiles correctly
```

> **Note:** `@ODrive-QA` invokes the `cpp-testing` and `odrive-toolchain` skills for builds and tests.

### Context is Key

Always provide:
- **Platform:** ARM Cortex-M4, x86, etc.
- **Timing:** ISR frequency, loop rate
- **Constraints:** No heap, MISRA C++, real-time
- **Expected behavior:** What should happen

---

## Presenter Notes

### Time Management
- **5 min per bug** is tight but achievable
- Announce "2 minutes remaining" for each bug
- It's OK if participants don't finish all 3
- Goal is learning the workflow, not completing everything

### Circulating Tips

**Look for:**
- Participants not using /fix or @terminal → Show them
- Participants getting wrong answers → Help refine prompts
- Participants stuck → Point to the step-by-step guide

**Common Issues:**

**"Copilot's answer doesn't make sense"**
→ Add more context about platform/constraints

**"I don't know which bug to start with"**
→ Start with Bug 1 (easiest), then Bug 3, then Bug 2 (hardest)

**"My code doesn't compile"**
→ Use `@terminal` to debug the compile error!
→ Or use `@ODrive-QA` to invoke build skill for verification

**"Bug spans multiple files"**
→ Use `@ODrive-Engineer` for multi-file analysis instead of `/fix`

### Debrief Questions (After Exercise)

**Ask the group:**
> "Who fixed Bug 1 (circular buffer)? [show of hands]"
> "Who fixed Bug 2 (race condition)? [show of hands]"
> "Who fixed Bug 3 (integer overflow)? [show of hands]"

> "Which bug was hardest? Why?"

> "How did Copilot help compared to traditional debugging?"

> "What debugging scenarios in your work could benefit from this?"

---

## Solutions Summary

### Quick Reference

| Bug | Line | Issue | Fix |
|-----|------|-------|-----|
| 1. Circular Buffer | `if (fault_idx_ > SIZE)` | Should be `>=` | Change to `>=` |
| 2. Race Condition | ISR writes, main reads | Float not atomic | Disable interrupts |
| 3. Integer Overflow | `delta * 60 * 1000000` | Exceeds int32_t | Convert to float early |

### Full Solutions Available

See `solutions/section6-debugging/` folder for:
- `fixed_motor.cpp` - Bug 1 fix
- `fixed_encoder.cpp` - Bugs 2 & 3 fixes
- `tests.cpp` - Unit tests for all fixes

---

## Key Takeaways

After this exercise, you should be able to:
- ✅ Use @terminal for build errors
- ✅ Use /fix for single-file logic bugs
- ✅ Use `@ODrive-Engineer` for complex multi-file bugs
- ✅ Use `@ODrive-QA` for test generation and build verification
- ✅ Provide effective context to Copilot
- ✅ Evaluate multiple fix suggestions
- ✅ Generate tests to verify fixes
- ✅ Debug embedded systems issues (race conditions, overflows)

**Remember:** Copilot is a tool to accelerate debugging, not replace thinking. Always understand the fix before applying it!

---

## Additional Practice

Want more debugging practice after the workshop?

### Resources
- Enable all compiler warnings: `-Wall -Wextra -Wpedantic`
- Try `cppcheck` or `clang-tidy` and ask Copilot to explain warnings
- Debug real ODrive issues from GitHub Issues

### Practice Scenarios
1. **Null pointer bugs** - Add null checks
2. **Const correctness** - Fix const propagation
3. **Move semantics** - Fix inefficient copies
4. **Template errors** - Debug template instantiation
5. **Linker errors** - Fix missing symbols

Ask Copilot to generate buggy code for practice:
```
Generate buggy C++ code with [type of bug] that I can practice debugging
```

**Good luck! 🚀**
