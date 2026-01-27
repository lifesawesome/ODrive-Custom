# Section 6: Debugging with GitHub Copilot

**Presentation Slides**  
**Duration:** 45 minutes (11:40-12:25)  
**Format:** PowerPoint/Google Slides

---

## Slide 1: Title Slide
**Title:** Debugging with GitHub Copilot  
**Subtitle:** From Build Errors to Logic Bugs  
**Time:** 11:40-12:25 (45 minutes)

---

## Part 1: Introduction to AI-Assisted Debugging (3 min)

### Slide 2: The Debugging Reality
**Visual:** Pie chart of developer time

```
Developer Time Breakdown:
├─ 40% Debugging 🐛
├─ 25% Writing Code ✍️
├─ 20% Code Review 👀
├─ 10% Meetings 💬
└─ 5% Other 📊
```

**Key Point:** "Almost half your time is debugging. Let's make it faster!"

---

### Slide 3: Traditional vs AI-Assisted Debugging
**Layout:** Two-column comparison

| Traditional Debugging | With Copilot |
|----------------------|--------------|
| Read cryptic error | @terminal explains it |
| Google StackOverflow | Ask Copilot inline |
| Trial & error fixes | /fix suggests solution |
| Manual log analysis | AI pattern detection |
| Hunt across files | @ODrive-Engineer finds root cause |
| Hours to find bug | Minutes to solution |

**Speaker Notes:** "Copilot doesn't replace thinking - it accelerates it. Use agents for complex multi-file bugs."

---

## Part 2: @terminal for Build Errors (10 min)

### Slide 4: What is @terminal?
**Visual:** Screenshot mockup

```
@terminal shows error: undefined reference to 'Motor::init()'

[Copilot analyzes...]

"This linker error means Motor::init() is declared 
but not defined. Check:
1. Is motor.cpp included in build?
2. Is function definition missing?"
```

**Key Point:** Context-aware error explanation

---

### Slide 5: Common Build Errors
**Layout:** Table with examples

| Error Type | Example | @terminal Can Help |
|-----------|---------|-------------------|
| **Syntax** | Missing semicolon | ✅ Instant fix |
| **Linker** | Undefined reference | ✅ Find missing definition |
| **Include** | No such file | ✅ Suggest correct path |
| **Template** | Instantiation failed | ✅ Explain template error |
| **Type** | Cannot convert X to Y | ✅ Suggest cast/fix |

---

### Slide 6: @terminal Workflow
**Visual:** Flow diagram

```
1. Build fails ──→ Error in Terminal
         ↓
2. Type: @terminal shows error: [paste]
         ↓
3. Copilot explains root cause
         ↓
4. Suggests fix with context
         ↓
5. Apply fix ──→ Build succeeds ✅
```

**Time saved:** 10-30 minutes per error!

---

### Slide 7: Pro Tips for @terminal
**Layout:** Numbered list

1. **Include full error** - Don't truncate
   ```
   @terminal shows error: 
   [paste entire error block including line numbers]
   ```

2. **Add context** - What you were trying to do
   ```
   Context: Adding new CAN message handler
   ```

3. **Platform matters** - Mention your toolchain
   ```
   Platform: ARM GCC 10.3, STM32F405
   ```

4. **Ask for alternatives** - If first fix doesn't work
   ```
   That didn't work. Other approaches?
   ```

5. **Use agents for complex issues** - Multi-file analysis
   ```
   @ODrive-Engineer analyze this linker error across the codebase
   ```

---

### Slide 8: Demo 1 Announcement
**Slide Type:** Demo announcement

**Text:**
> 🎬 **LIVE DEMO: @terminal in Action**
> 
> **Scenario:** Compiler & Linker Errors
> 
> We'll break the build and use @terminal to:
> 1. Fix syntax error (missing semicolon)
> 2. Resolve linker error (undefined reference)
> 3. Fix template instantiation error
> 
> **Bonus:** Use `@ODrive-QA` to invoke build skill for verification
> 
> See: `demo-script.md` Demo 1
> 
> **Time:** 8 minutes

**Speaker Notes:** Switch to VS Code for live demo

---

## Part 3: /fix for Logic Bugs (10 min)

### Slide 9: What is /fix?
**Visual:** Before/after code example

**File:** `demo_buggy.cpp` — FaultLogger class

**Before:**
```cpp
void log_fault(uint32_t error) {
    fault_history_[fault_idx_] = error;
    fault_idx_++;
    if (fault_idx_ > FAULT_HISTORY_SIZE) {  // BUG!
        fault_idx_ = 0;
    }
}
```

**After /fix (in Chat mode):**
```cpp
// Select function → Chat: /fix boundary check
if (fault_idx_ >= FAULT_HISTORY_SIZE) {  // FIXED!
    fault_idx_ = 0;
}
```

**Key Point:** Chat mode explains WHY, inline just applies fix

---

### Slide 10: When to Use /fix vs Agents
**Layout:** Decision tree

```
Code compiles? ──NO──→ Use @terminal
     │                 (or @ODrive-QA for build skill)
    YES
     ↓
Logic bug or
unexpected behavior? ──YES──→ Use /fix (single file)
     │                        or @ODrive-Engineer (multi-file)
    NO
     ↓
Performance issue? ──YES──→ Use /fix with context
     │
    NO
     ↓
Complex multi-file bug? ──YES──→ @ODrive-Engineer
     │
    NO
     ↓
Need tests for fix? ──YES──→ @ODrive-QA
```

---

### Slide 11: Common C++ Bugs /fix Catches
**Layout:** Grid of bug types

**Memory Issues:**
- Buffer overflows
- Uninitialized variables
- Memory leaks
- Use after free

**Logic Errors:**
- Off-by-one errors
- Wrong operators (>, >=)
- Missing edge cases
- Incorrect loop bounds

**Concurrency:**
- Race conditions
- Missing locks
- Non-atomic operations
- Deadlocks

**Embedded-Specific:**
- Integer overflow
- Float precision
- Interrupt safety
- Volatile missing

---

### Slide 12: /fix Best Practices
**Layout:** Do's and Don'ts

**✅ DO:**
- Select the buggy function/block
- Use **Chat mode** for detailed explanations
- Add platform constraints
- Describe expected behavior

**❌ DON'T:**
- Say "fix this" without context
- Use inline (`Ctrl+I`) when you need explanation
- Select entire file
- Blindly accept first suggestion

---

### Slide 13: /fix Workflow Example
**Visual:** Step-by-step with code

**Step 1:** Identify bug
```cpp
// Motor crashes at high speeds
int32_t rpm = (delta * 60 * 1000000) / (cpr * dt);
```

**Step 2:** Select code, use /fix with context
```
/fix integer overflow at high speeds

Context:
- ARM Cortex-M4
- delta can be up to 2000
- Need accuracy, not just casting
```

**Step 3:** Review suggestion
```cpp
// Copilot suggests:
float rpm = ((float)delta / (float)cpr) * (60.0f / dt_seconds);
```

**Step 4:** Apply and test ✅

---

### Slide 14: Demo 2 Announcement
**Slide Type:** Demo announcement

**Text:**
> 🎬 **LIVE DEMO: /fix for Logic Bugs**
> 
> **File:** `demo_buggy.cpp`
> 
> **Scenarios:**
> 1. Off-by-one error in circular buffer (FaultLogger class)
> 2. Race condition in encoder ISR (Encoder class)
> 
> Watch how /fix in **Chat mode**:
> - Identifies the root cause
> - Suggests multiple solutions
> - Explains trade-offs
> 
> **Also show:** `@ODrive-Engineer` for multi-file context
> 
> See: `demo-script.md` Demo 2
> 
> **Time:** 8 minutes

**Speaker Notes:** Switch to VS Code for live demo

---

## Part 4: Common Embedded C++ Debugging Patterns (10 min)

### Slide 15: Embedded Debugging Challenges
**Visual:** Challenge icons with explanations

```
⚡ Timing Issues
   - Race conditions in ISRs
   - Missed deadlines
   - Timing-dependent bugs

💾 Memory Constraints
   - Stack overflow
   - Static allocation only
   - Flash size limits

🔒 Safety Critical
   - MISRA C++ compliance
   - No exceptions
   - Fault tolerance

🔌 Hardware Dependencies
   - Register access
   - DMA timing
   - Peripheral conflicts
```

---

### Slide 16: Pattern 1 - Uninitialized Variables
**Layout:** Problem → Detection → Fix

**Problem:**
```cpp
class Encoder {
    int32_t count_;  // Uninitialized!
    int32_t last_count_;
public:
    Encoder() {
        // Constructor doesn't init members!
    }
};
```

**Detection:**
```
Select class → Type:
/fix uninitialized member variables
```

**Fix:**
```cpp
class Encoder {
    int32_t count_ = 0;  // Initialize at declaration
    int32_t last_count_ = 0;
public:
    Encoder() = default;
};
```

---

### Slide 17: Pattern 2 - Race Conditions
**Layout:** Problem → Detection → Fix

**Problem:**
```cpp
// ISR updates this
float position_estimate_;

// Main loop reads this - RACE!
float get_position() {
    return position_estimate_;
}
```

**Detection:**
```
Select both functions → Type:
/fix thread safety between ISR and main loop

Context: ARM Cortex-M4, 8 kHz ISR, float not atomic
```

**Fix:**
```cpp
float get_position() {
    __disable_irq();
    float pos = position_estimate_;
    __enable_irq();
    return pos;
}
```

---

### Slide 18: Pattern 3 - Integer Overflow
**Layout:** Problem → Detection → Fix

**Problem:**
```cpp
int32_t rpm = (delta * 60 * 1000000) / (cpr * dt);
//            ^^^^^^^^^^^^^^^^^^^^^ Overflows!
```

**Detection:**
```
Select calculation → Type:
/explain why this gives wrong values at high speeds
```

**Fix:**
```cpp
float rpm = ((float)delta / (float)cpr) * (60.0f / dt_s);
//         Convert to float early - no overflow
```

---

### Slide 19: Pattern 4 - Buffer Overflows
**Layout:** Problem → Detection → Fix

**Problem:**
```cpp
char buffer[64];
sprintf(buffer, "Motor %d: %s", id, long_error_message);
//      ^^^^^^ No bounds checking!
```

**Detection:**
```
Select sprintf → Type:
/fix buffer overflow risk

Context: Embedded system, no heap, safety critical
```

**Fix:**
```cpp
char buffer[64];
snprintf(buffer, sizeof(buffer), "Motor %d: %.30s", id, long_error_message);
//       ^^^^^ Bounds-safe, truncates if needed
```

---

### Slide 20: Pattern 5 - Volatile Missing
**Layout:** Problem → Detection → Fix

**Problem:**
```cpp
uint32_t* const GPIOA_ODR = (uint32_t*)0x40020014;

void toggle_pin() {
    *GPIOA_ODR |= (1 << 5);  // Compiler might optimize this away!
}
```

**Detection:**
```
Select GPIO access → Type:
/fix compiler optimization removing hardware access

Context: Memory-mapped registers, ARM Cortex-M4
```

**Fix:**
```cpp
volatile uint32_t* const GPIOA_ODR = (volatile uint32_t*)0x40020014;
//       ^^^^^^^^ Prevents compiler optimization
```

---

### Slide 21: Pattern 6 - Const Correctness
**Layout:** Problem → Detection → Fix

**Problem:**
```cpp
class Motor {
    float get_position() {  // Should be const!
        return position_;
    }
};

void log_motor(const Motor& motor) {
    float pos = motor.get_position();  // ERROR: discards const
}
```

**Detection:**
```
Select function → Type:
/fix const correctness
```

**Fix:**
```cpp
float get_position() const {  // Now const-correct
    return position_;
}
```

---

### Slide 22: Demo 3 Announcement
**Slide Type:** Demo announcement

**Text:**
> 🎬 **LIVE DEMO: Full Debug Workflow**
> 
> **File:** `demo_buggy.cpp` — SpeedCalculator class
> 
> **Scenario:** Integer overflow in RPM calculation
> 
> Complete workflow (all in **Chat mode**):
> 1. Use /explain to understand bug
> 2. Use /fix to get solution
> 3. Use @terminal to verify compilation
> 4. Use @ODrive-QA to generate unit test
> 
> See: `demo-script.md` Demo 3
> 
> **Time:** 9 minutes

**Speaker Notes:** Switch to VS Code for live demo

---

## Part 5: Hands-On Exercises (15 min)

### Slide 23: Debugging Exercises
**Layout:** Exercise list

**Fix 3 bugs in `demo_buggy.cpp` in 15 minutes:**

1. **⭐⭐ Circular Buffer (5 min)** — FaultLogger class
   - Off-by-one boundary check (lines 31-38)
   - Use /fix in Chat mode

2. **⭐⭐⭐ Race Condition (5 min)** — Encoder class
   - ISR writes, main loop reads (lines 65-81)
   - Evaluate multiple solutions

3. **⭐⭐ Integer Overflow (5 min)** — SpeedCalculator class
   - RPM calculation overflow (lines 104-111)
   - Use /explain then /fix

**Files:** `demo_buggy.cpp` + `hands-on-exercises.md`

---

### Slide 24: Exercise Tips
**Layout:** Tips box

💡 **Tips:**
- Read the bug description first
- Try to spot the bug yourself
- Then use Copilot to verify/fix
- Understand WHY it's a bug
- Apply the fix and test
- Ask Copilot to generate unit tests

**Remember:** Goal is learning, not speed!

---

## Closing (2 min)

### Slide 25: Debugging Workflow Summary
**Visual:** Complete workflow diagram

```
1. Identify Problem
   ├─ Build error → @terminal (or @ODrive-QA)
   └─ Logic bug → /fix (or @ODrive-Engineer)
         ↓
2. Understand Root Cause
   └─ Use /explain if unclear
   └─ Use @ODrive-Engineer for multi-file analysis
         ↓
3. Get Solution
   └─ Provide context + constraints
         ↓
4. Review & Apply
   └─ Check for safety/correctness
         ↓
5. Verify Fix
   └─ @ODrive-QA → Build + unit tests
```

---

### Slide 26: Key Takeaways
**Layout:** Summary bullets

**Section 6: Debugging**
✅ @terminal for build errors → Fast fixes  
✅ /fix for logic bugs → Context-aware solutions  
✅ @ODrive-Engineer for multi-file bugs → Orchestrated analysis  
✅ @ODrive-QA for build & test → Invokes skills automatically  
✅ Embedded patterns → Race conditions, overflows, atomicity  
✅ Always review → AI accelerates, you validate  

**Quote:** "Copilot finds bugs in seconds, not hours"

---

### Slide 27: Beyond This Workshop
**Layout:** Resource list

**Keep Practicing:**
- Enable all compiler warnings (`-Wall -Wextra`)
- Use static analyzers (cppcheck, clang-tidy)
- Ask Copilot to explain warnings
- Generate buggy code for practice

**Resources:**
- Prompt library: `prompt-library.md`
- Common patterns: `hands-on-exercises.md`
- ODrive real bugs: GitHub Issues

---

### Slide 28: Q&A
**Layout:** Question prompts

**Common Questions:**
- What if Copilot suggests the wrong fix?
- Can I use this for safety-critical code?
- How do I debug Copilot's generated code?
- Does /fix work with non-C++ languages?

**Open Floor:** Any questions?

---

### Slide 29: Break Announcement
**Layout:** Simple text

**Text:**
> ☕ **Lunch Break**
> 
> **Time:** 12:25 - 1:15 (50 minutes)
> 
> **After Lunch:**
> Testing & Validation with Copilot
> 
> **Don't forget:**
> Save your exercise code!

---

## Appendix: Backup Slides

### Backup Slide 1: When Copilot Gets It Wrong
**What to do:**

1. **Add more context**
   - Platform, constraints, expected behavior

2. **Try rephrasing**
   - "Fix race condition" → "Make thread-safe for ARM Cortex-M4 ISR"

3. **Reference examples**
   - "Follow pattern in motor.cpp:145-160"

4. **Break into smaller pieces**
   - Debug one aspect at a time

5. **Use as learning tool**
   - Ask "Why did this fail?"

---

### Backup Slide 2: Safety-Critical Code
**Using Copilot for safety-critical systems:**

**✅ Safe Uses:**
- Explain errors
- Suggest approaches
- Generate unit tests
- Find potential issues
- Code review assistance

**⚠️ Always Verify:**
- Run static analysis
- Manual code review
- Extensive testing
- Follow MISRA guidelines
- Document decisions

**Rule:** AI suggests, humans verify!

---

### Backup Slide 3: Debugging Commands Reference
**Quick reference card:**

| Command | Use Case | Example |
|---------|----------|---------|
| `@terminal` | Build errors | `@terminal shows error: [paste]` |
| `/fix` | Logic bugs (single file) | `/fix buffer overflow` |
| `/explain` | Understand code | `/explain why this crashes` |
| `/tests` | Generate tests | `/tests for this function` |
| `@workspace` | Find patterns | `@workspace how are ISRs handled?` |
| `@ODrive-Engineer` | Multi-file bugs | `@ODrive-Engineer analyze this crash` |
| `@ODrive-QA` | Build & test | `@ODrive-QA verify fix compiles` |

---

## Slide Design Notes

### Visual Style
- **Clean, technical** - Code-heavy slides
- **Before/after** - Show bug → fix clearly
- **Color coding** - Red for bugs, green for fixes
- **Icons** - 🐛 for bugs, ✅ for fixes
- **Consistent** - Match Sections 4 & 8 style

### Fonts
- **Titles:** 44pt, Bold
- **Body:** 24-28pt
- **Code:** 18-20pt, Monospace (Consolas, Monaco)
- **Errors:** Red text for emphasis

### Animation
- **Minimal** - Simple reveals
- **Bug highlighting** - Fade in the problematic line
- **Avoid** - Distracting transitions

---

## Timing Breakdown

| Slide Range | Topic | Time |
|-------------|-------|------|
| 1-3 | Introduction | 3 min |
| 4-8 | @terminal + Demo | 10 min |
| 9-14 | /fix + Demo | 10 min |
| 15-22 | Patterns + Demo | 10 min |
| 23-24 | Hands-On | 15 min |
| 25-29 | Wrap-Up | 2 min |
| **Total** | | **45 min** |

---

## Presenter Reminders

- ⏰ **Time management** - 3 demos take time, practice!
- 🎤 **Live demos** - Have backup if network fails
- 👀 **Show errors first** - Then show Copilot fix
- 🖱️ **Git branches** - Use `demo/section6-bugs` branch
- ⏸️ **Pause for questions** - Debugging is complex
- 📱 **Phone on silent** - No interruptions
- 💾 **Git stash ready** - Easy reset between demos

**Pro Tip:** Practice the git branch switching workflow!

**Good luck! 🚀**
