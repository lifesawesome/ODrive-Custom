# Section 6 Demo Script: Debugging with Copilot

**Duration:** 25 minutes (for the three demos)  
**Presenter Notes:** This script provides exact steps and dialogue for live debugging demos

---

## Demo 1: @terminal for Build Errors (8 min)

### Setup
- Open VS Code with ODrive workspace
- Have `src-ODrive/Firmware/MotorControl/motor.cpp` open
- Terminal panel visible (View → Terminal)
- Clear Copilot chat history

### Demo Flow

**Presenter Says:**
> "Let's say I'm adding a new feature to motor.cpp and I introduce a build error. Watch how @terminal helps me debug it faster than traditional methods."

---

### Introduce the Bug

**Step 1: Make an intentional error**

Open `Firmware/MotorControl/motor.cpp` and find the `update()` method (around line 510-515).

**Add this buggy line:**
```cpp
// Inside Motor::update()
float current_limit = motor_current_limit;  // BUG: Wrong variable name!
```

**Presenter Says:**
> "I meant to access `motor_.config_.current_lim` but I typed `motor_current_limit` by mistake. Let's see what happens when I build."

---

**Step 2: Trigger the build error**

**In Terminal:**
```powershell
# If using Tup (ODrive default)
tup

# Or if using Make
make
```

**Expected Error:**
```
[ tup ] Compiling motor.cpp...
motor.cpp:514:30: error: 'motor_current_limit' was not declared in this scope
     float current_limit = motor_current_limit;
                           ^~~~~~~~~~~~~~~~~~~
[ tup ] Build failed
```

**Presenter Says:**
> "I got a compile error. Now, the traditional way would be to read this error, maybe Google 'was not declared in this scope', try to figure out what I meant... Let's use @terminal instead."

---

### Use @terminal to Diagnose

**Step 3: Ask @terminal**

**In Copilot Chat, type:**
```
@terminal can you tell me why this build is failing?
```

**Presenter Says:**
> "Notice I'm letting @terminal do all the heavy lifting!"

*[Wait for AI response]*

---

**Step 4: Review AI Response**

**Expected AI Response (approximate):**
```
The error indicates 'motor_current_limit' is not in scope. 

Looking at motor.hpp, the current limit is accessed through the config struct:

Correct syntax:
    float current_limit = motor_.config_.current_lim;

The motor configuration is in the motor_ member variable, within the config_
struct, and the field is named current_lim (not motor_current_limit).

You can find this defined in motor.hpp around line 45:
    struct Config {
        float current_lim = 10.0f;
        // ...
    };
```

**Presenter Says:**
> "Perfect! The AI not only told me the correct variable name, but also:
> - Explained the struct hierarchy (motor_.config_.current_lim)
> - Told me where it's defined (motor.hpp line 45)
> - Gave me the exact syntax to use
> 
> This is way faster than hunting through header files!"

---

**Step 5: Apply the Fix**

**In motor.cpp, change the line to:**
```cpp
float current_limit = motor_.config_.current_lim;  // Fixed!
```

**Rebuild:**
```powershell
tup
```

**Expected Output:**
```
[ tup ] Compiling motor.cpp...
[ tup ] Build successful
```

**Presenter Says:**
> "Fixed on the first try! @terminal saved me 5 minutes of hunting through code. 
>
> **Tip:** For complex multi-file issues, you can also use `@ODrive-Engineer` to analyze the codebase, or `@ODrive-QA` to invoke the build skill and verify the fix compiles correctly.
>
> Let's look at a more complex error."

---

### Linker Error (Bonus if time permits)

**Step 6: Introduce a linker error**

> **Important:** Simply adding a function declaration without implementation won't cause a linker error - the linker only looks for symbols that are actually *called*. We need to both declare AND call the function.

**In motor.hpp (around line 78), add a declaration after the existing method declarations:**
```cpp
    bool apply_config();
    bool setup();

    void trigger_linker_error_demo();  // ADD THIS LINE - Declaration only!

    void update_current_controller_gains();
```

**Then in motor.cpp, inside the `Motor::update()` function (around line 515), add a call to this function:**
```cpp
void Motor::update(uint32_t timestamp) {
    trigger_linker_error_demo();  // ADD THIS LINE - Call the unimplemented function!
    
    // ... rest of existing code
```

**But don't add the implementation of `trigger_linker_error_demo()` in motor.cpp**

**Rebuild:**
```powershell
tup
```

**Expected Error:**
```
undefined reference to `Motor::trigger_linker_error_demo()'
```

**Presenter Says:**
> "Notice we had to CALL the function, not just declare it. The linker only complains about missing symbols that are actually used in the code."

**In Copilot Chat:**
```
@terminal shows linker error: undefined reference to Motor::trigger_linker_error_demo()

The function is declared in motor.hpp and called in motor.cpp but I'm getting a linker error. What's wrong?
```

**Expected AI Response:**
```
Linker error indicates the function is declared and called, but not defined.

You have the declaration in motor.hpp:
    void trigger_linker_error_demo();

And a call in motor.cpp:
    trigger_linker_error_demo();

But the implementation is missing from motor.cpp.

Add this to motor.cpp:
    void Motor::trigger_linker_error_demo() {
        // Implementation here
    }

Or if you don't need this function, remove both the declaration from motor.hpp
and the call from motor.cpp.
```

**Presenter Says:**
> "Again, @terminal immediately identified the issue: declaration and call without implementation. This would have taken me several minutes to debug manually."

---

## Demo 2: /fix for Bug Resolution (8 min)

### Setup
- Open the pre-created demo file: `src-ODrive/Firmware/MotorControl/demo_buggy.cpp`
- This file contains three intentional bugs for demonstration
- No build required - we're demonstrating /fix on logic bugs

### Demo Flow

**Presenter Says:**
> "Now let's look at logic bugs - not compile errors, but code that compiles but doesn't work correctly. The /fix command is perfect for this."

---

### Off-By-One Error

**Step 1: Open the demo file**

Open `src-ODrive/Firmware/MotorControl/demo_buggy.cpp` and scroll to the `FaultLogger` class (around line 24).

**The buggy code (lines 31-38):**
```cpp
// BUG: Can you spot the off-by-one error?
void log_fault(uint32_t error_code) {
    fault_history_[fault_idx_] = error_code;
    fault_idx_++;
    
    // BUG: Should this be > or >=?
    if (fault_idx_ > FAULT_HISTORY_SIZE) {
        fault_idx_ = 0;
    }
}
```

**Presenter Says:**
> "This is a circular buffer for logging motor faults. The last 10 faults are kept in an array. But there's a subtle bug here. Can you spot it?"

*[Pause for audience]*

> "The bug is in the boundary check. Let me use /fix to find it."

---

**Step 2: Use /fix in Chat**

1. **Select lines 31-38** (the entire `log_fault` function)
2. Open **Inline Chat** panel (`Ctrl+I`) first
3. Type: 
```
/fix the circular buffer boundary check
```
4. look at the fix and then disgard changes
5. Open **Copilot Chat** panel (`Ctrl+Alt+I`)
6. Type: 
```
/fix the circular buffer boundary check
```
7. Note the difference in details here, chat can give you explainations


> **Note:** Use Chat mode (not inline `Ctrl+I`) to get the detailed explanation. Inline chat gives a quick fix but less explanation.

**Presenter Says:**
> "I've selected the function and asked /fix to check the circular buffer logic. Notice I'm being specific about what to fix. I'm using Chat mode because it gives us a detailed explanation - great for learning!"

*[Wait for AI response]*

---

**Step 3: Review the fix**

**Expected AI Response:**
```
Off-by-one error detected on line 6.

Issue: 
With FAULT_HISTORY_SIZE = 10, valid array indices are 0-9.
The condition 'fault_idx_ > FAULT_HISTORY_SIZE' (> 10) means the index
wraps at 11, causing buffer overflow at index 10.

Fix:
    if (fault_idx_ >= FAULT_HISTORY_SIZE) {
        fault_idx_ = 0;
    }

Explanation:
- When fault_idx_ reaches 10, it equals FAULT_HISTORY_SIZE
- With '>', it doesn't wrap, and tries to access fault_history_[10]
- With '>=', it wraps at 10, keeping indices in range 0-9
```

**Presenter Says:**
> "Beautiful! Not only did /fix find the bug, it:
> 1. Identified it as an off-by-one error
> 2. Explained WHY it's wrong (would access index 10 in a 10-element array)
> 3. Provided the correct fix (>= instead of >)
> 4. Explained the logic
> 
> This is incredibly helpful for reviewing code!"

---

### Race Condition (Advanced)

**Step 4: Show threading bug**

**In the same file (`demo_buggy.cpp`), scroll to the `Encoder` class (around line 55).**

**The buggy code (lines 65-77):**
```cpp
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
```

**Presenter Says:**
> "This is trickier - a race condition. The ISR writes `position_estimate_` at 8 kHz while the main loop reads it at 1 kHz. On ARM, float assignment isn't atomic, so we can get corrupted reads."

---

**Step 5: Ask /fix for solutions**

1. **Select lines 65-81** (both `update_isr()` and `get_position()`/`get_velocity()` functions)
2. Open **Copilot Chat** panel (`Ctrl+Alt+I`)
3. Type:
```
/fix thread safety issue - ISR writes position_, main loop reads it

Context: 
- ISR runs at 8 kHz
- Main loop at 1 kHz
- ARM Cortex-M4 (float not atomic)
- Need lowest-overhead solution
```

> **Note:** Chat mode gives multiple solutions with trade-off analysis. Inline chat would just apply one fix.

**Presenter Says:**
> "I'm giving /fix important context: this is an interrupt vs. main loop race, ARM platform, and I need low overhead because this runs 8000 times per second."

*[Wait for AI response]*

---

**Step 6: Evaluate solutions**

**Expected AI Response:**
```
Race condition detected. Float writes in ISR can be interrupted, causing
main loop to read partial/corrupted values.

Solutions (ordered by overhead):

1. Disable interrupts briefly (lowest overhead):
   float Axis::get_position() {
       __disable_irq();
       float pos = encoder_.position_;
       __enable_irq();
       return pos;
   }

2. Use double buffering:
   void Encoder::update_isr() {
       shadow_position_ = (float)count_ / (float)cpr_;
       swap_flag_ = true;
   }
   float Axis::get_position() {
       if (swap_flag_) {
           position_ = shadow_position_;
           swap_flag_ = false;
       }
       return position_;
   }

3. Use std::atomic<float> (if available):
   std::atomic<float> position_;

Recommendation for 8 kHz ISR: Option 1 (interrupt disable) - only ~10 cycles.
```

**Presenter Says:**
> "Wow! /fix not only found the race condition, but gave me THREE solutions ranked by overhead, and recommended the best one for my use case. This is the level of help you get when you provide good context!
>
> **Pro Tip:** For bugs that span multiple files or need deeper codebase analysis, use `@ODrive-Engineer` instead of just `/fix`. The agent can search across files and invoke skills to help diagnose complex issues."

---

## Demo 3: Real-World Debug Session (9 min)

### Setup
- Continue using `demo_buggy.cpp` - scroll to the `SpeedCalculator` class (around line 92)
- This demonstrates the full /explain → /fix → test workflow

### Demo Flow

**Presenter Says:**
> "Let's do a realistic debugging session. I have a bug report: 'Motor RPM reading jumps to huge values at high speed.' Let me debug this with Copilot."

---

**Step 1: Show the buggy code**

**In `demo_buggy.cpp`, scroll to the `SpeedCalculator` class (line 92). The buggy code is lines 104-111:**

```cpp
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
```

**Presenter Says:**
> "This calculates motor RPM from encoder ticks. At low speeds it works fine, but at high speeds, we get crazy values like 2 billion RPM. Let me debug this with Copilot."

---

**Step 2: Ask for explanation**

1. **Select lines 104-111** (the `calculate_rpm` function)
2. Open **Copilot Chat** panel (`Ctrl+Alt+I`)
3. Type: 
```
/explain why this might give wrong values at high speeds
```
> **Note:** `/explain` works best in Chat mode for detailed analysis.

**Expected AI Response:**
```
Potential integer overflow in the calculation:

Line 6: (delta_count * 60 * 1000000)

If delta_count = 1000 (typical at high speed):
    1000 * 60 * 1000000 = 60,000,000,000

This exceeds int32_t max value (2,147,483,647), causing overflow.

The result wraps around to a negative or incorrect value, then gets
divided by (cpr_ * delta_time_us), producing garbage.
```

**Presenter Says:**
> "Aha! Integer overflow. The intermediate calculation exceeds 2 billion. Let me ask for a fix."

---

**Step 3: Get the fix**

**With the same code still selected, type:**
```
/fix integer overflow - use float math
```

**Expected AI Response:**
```
Fix: Convert to float before multiplication to avoid overflow.

Corrected code:
    float Encoder::calculate_rpm() {
        int32_t delta_count = count_ - last_count_;
        float delta_time_s = 125e-6f;  // 125 μs in seconds
        
        // Convert to float early
        float revolutions = (float)delta_count / (float)cpr_;
        float rps = revolutions / delta_time_s;
        float rpm = rps * 60.0f;
        
        return rpm;
    }

Benefits:
- No overflow (float range: ±3.4e38)
- More readable
- More accurate (no integer division)
```

**Presenter Says:**
> "Perfect fix! By converting to float early, we avoid overflow and get more accurate results. Let me apply this."

---

**Step 4: Test the fix**

**Apply the code changes**

**Presenter Says:**
> "Now I'd rebuild and test on hardware. But let me also ask Copilot for a unit test to prevent regression."

First select @ODrive-QA in chat.

**Type:**
```
Generate a unit test for calculate_rpm that tests high speed values to catch integer overflow
```

> **Note:** Using `@ODrive-QA` invokes the `cpp-testing` skill which is specialized for test generation.

**Expected AI Response:**
```cpp
#include "doctest.h"
#include "encoder.hpp"

TEST_CASE("Encoder RPM calculation at high speed") {
    Encoder encoder;
    encoder.config_.cpr = 8192;
    
    SUBCASE("Low speed - 100 RPM") {
        encoder.count_ = 0;
        encoder.last_count_ = -14;  // 100 RPM @ 8kHz
        float rpm = encoder.calculate_rpm();
        CHECK(rpm == doctest::Approx(100.0f).epsilon(0.01));
    }
    
    SUBCASE("High speed - 10000 RPM") {
        encoder.count_ = 0;
        encoder.last_count_ = -1365;  // 10000 RPM @ 8kHz
        float rpm = encoder.calculate_rpm();
        CHECK(rpm == doctest::Approx(10000.0f).epsilon(0.01));
    }
    
    SUBCASE("Very high speed - 50000 RPM (overflow risk)") {
        encoder.count_ = 0;
        encoder.last_count_ = -6827;  // 50000 RPM @ 8kHz
        float rpm = encoder.calculate_rpm();
        CHECK(rpm == doctest::Approx(50000.0f).epsilon(0.01));
        CHECK(rpm > 0);  // Ensure no overflow to negative
    }
}
```

**Presenter Says:**
> "Excellent! `@ODrive-QA` generated a unit test that specifically checks high-speed values where overflow would occur. This ensures the bug stays fixed. The agent invoked the `cpp-testing` skill to create comprehensive tests."

---

**Step 5: Wrap up**

**Presenter Says:**
> "So in about 5 minutes, we:
> 1. Used /explain to understand the root cause (integer overflow)
> 2. Used /fix to get a corrected implementation
> 3. Used `@ODrive-QA` to generate a unit test to prevent regression
> 
> Without Copilot, this would have taken 20-30 minutes of debugging, math, and test writing. That's the power of AI-assisted debugging!
>
> **Remember:** For simple bugs, `/fix` and `@terminal` are fastest. For complex multi-file bugs, use `@ODrive-Engineer`. For build verification and tests, use `@ODrive-QA`."

---

## Demo Tips for Presenters

### Before the Demo

**Preparation:**
- [ ] Test all three demos in advance
- [ ] Have buggy code ready (don't make up errors on the fly)
- [ ] Verify @terminal and /fix work in your environment
- [ ] Verify agents available (`@ODrive-Engineer`, `@ODrive-QA`)
- [ ] Have backup screenshots if network fails
- [ ] Time yourself - should fit in 25 minutes total

**Code Setup:**
- Either modify ODrive files temporarily, OR
- Create separate demo files with bugs pre-inserted
- Have a way to quickly undo changes (Git stash, backup files)

### During the Demo

**Pacing:**
- Demo 1: 8 minutes - @terminal (build errors)
- Demo 2: 8 minutes - /fix (logic bugs)
- Demo 3: 9 minutes - Full workflow (realistic debugging)

**Engagement:**
- Pause after showing bugs: "Can you spot the error?"
- Explain your thought process: "I'm adding context because..."
- Show failures: "Sometimes the first answer isn't perfect - that's OK!"

**Narration:**
- Explain WHAT you're typing
- Explain WHY you're including context
- Explain HOW the AI response helps

### If Something Goes Wrong

**Network issues:**
> "I have a screenshot of the expected response..." [Show backup]

**AI gives bad response:**
> "This is why we always review! Let me refine the prompt..." [Iterate]

**Demo code doesn't compile as expected:**
> "Let me show you a prepared example instead..." [Switch to backup]

**Running behind on time:**
> "I'll skip the bonus linker error demo and move to /fix..."

---

## Audience Engagement

### Questions to Ask

**After Demo 1 (@terminal):**
> "Who has spent more than 10 minutes debugging a cryptic compiler error? [Show of hands]  
> @terminal could have solved it in 30 seconds!"

**After Demo 2 (/fix):**
> "What other types of bugs would you like /fix to help with?"
> [Take 1-2 examples from audience]

**After Demo 3 (Full workflow):**
> "What bugs in your codebase could you debug with this workflow?"

### Expected Audience Questions

**Q: "Does /fix work for all bugs?"**
A: "No - it's best for clear logic errors in a single file. Complex architectural problems or bugs spanning multiple files benefit from `@ODrive-Engineer` which can search the codebase. But /fix handles 80% of common bugs really well."

**Q: "When should I use @ODrive-Engineer vs /fix?"**
A: "Use `/fix` for quick, single-file bugs. Use `@ODrive-Engineer` when you need codebase-wide analysis or don't know where the bug is. Use `@ODrive-QA` when you need build verification or test generation."

**Q: "What if the AI fix is wrong?"**
A: "Always review! AI can miss edge cases. But even a wrong suggestion often points you in the right direction. Iterate with more context."

**Q: "Can it debug hardware issues?"**
A: "Not directly - but if you describe symptoms ('motor stutters at 2000 RPM'), AI can suggest software causes (control loop timing, filtering, etc.)."

**Q: "Does this work with other languages?"**
A: "Yes! Python, JavaScript, Java, etc. The concepts are the same. C++ is actually one of the best-supported languages."

---

## Timing Breakdown

| Demo | Target Time | Buffer |
|------|-------------|--------|
| Demo 1: @terminal | 8 min | +2 min |
| Demo 2: /fix | 8 min | +2 min |
| Demo 3: Full workflow | 9 min | None |
| **Total** | **25 min** | **+4 min** |

Use buffer time for audience questions or if a demo runs long.

---

## Post-Demo Transition

**After all demos, say:**
> "Now it's your turn! In the hands-on exercise, you'll debug 3 real bugs in ODrive motor control code using @terminal and /fix. You'll have 15 minutes. The bugs are:
> 1. Off-by-one in circular buffer
> 2. Race condition between ISR and main loop
> 3. Integer overflow in speed calculation
>
> For complex bugs, remember you can also use `@ODrive-Engineer` for multi-file analysis and `@ODrive-QA` for test generation.
> 
> Each has step-by-step guidance in the hands-on-exercises.md file. Let's get started!"

[Transition to hands-on exercise]

---

## Backup Materials

### Screenshots to Prepare

Take screenshots of:
1. Each bug being introduced
2. The compile/build errors
3. The @terminal conversation
4. The /fix suggestions
5. The fixed code

Label: `demo6-step1.png`, `demo6-step2.png`, etc.

### Demo Video

Record a full run-through (25 min) as backup:
- Screen capture with narration
- Show all three demos
- Upload to accessible location

---

**You're ready to present! Good luck! 🚀**
