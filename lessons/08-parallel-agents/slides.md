# Section 8: Parallel Agents & Cloud Agents

**Presentation Slides**  
**Duration:** 20 minutes (2:30-2:50)  
**Format:** PowerPoint/Google Slides

---

## Slide 1: Title Slide
**Title:** Parallel Agents & Cloud Agents  
**Subtitle:** Orchestrating Multiple AI Experts  
**Time:** 2:30-2:50 (20 minutes)

---

## Part 1: Running Multiple Agents (8 min)

### Slide 2: Sequential vs Parallel
**Visual:** Timeline comparison

**Sequential (OLD):**
```
Task 1 ████████ (2 min)
Task 2         ████████ (2 min)
Task 3                 ████████ (2 min)
Total: 6 minutes
```

**Parallel (NEW):**
```
@ODrive-Engineer (firmware) ████████
@ODrive-Engineer (control)  ████████  (all running together!)
@ODrive-QA (testing)        ████████
Total: 2 minutes
```

**Impact:** 3x faster! ⚡

**Note:** Same agent, different task contexts!

---

### Slide 3: When to Use Parallel Agents
**Layout:** Two columns

**✅ Good Use Cases:**
- Independent tasks
- Cross-domain features
- Multi-file refactoring
- Research + implementation

**❌ Poor Use Cases:**
- Dependent tasks (Task B needs Task A)
- Same file edits (merge conflicts)
- Simple tasks (overhead not worth it)

---

### Slide 4: Parallel Agent Patterns
**Layout:** 3 pattern boxes

**Pattern 1: Domain Separation (Same Agent, Different Contexts)**
```
@ODrive-Engineer (control focus) → Algorithm
@ODrive-Engineer (firmware focus) → Implementation  
@ODrive-Engineer (hardware focus) → Electrical specs
@ODrive-QA (testing focus) → Test plan
```

**Pattern 2: Multi-Module**
```
@ODrive-Engineer → Module A
@ODrive-Engineer → Module B
@ODrive-Engineer → Module C
Regular Copilot → Python tools
```

**Pattern 3: Dev + QA Split**
```
@ODrive-Engineer → motor.cpp changes
@ODrive-Engineer → odrive_can.cpp changes
@ODrive-QA → Build verification
@ODrive-QA → Test generation
```

**Key:** Agents invoke skills automatically based on task!

---

### Slide 5: Coordination Strategy
**Visual:** Workflow diagram

```
Phase 1: Parallel Design (5 min)
  ├─ @ODrive-Engineer (control focus): Algorithm
  ├─ @ODrive-Engineer (hardware focus): Electrical specs
  └─ @ODrive-QA: Test planning
         ↓
Phase 2: Review & Align (5 min)
  └─ Identify integration points
         ↓
Phase 3: Parallel Implementation (10 min)
  └─ Each window implements their part
         ↓
Phase 4: Integration (5 min)
  └─ Combine and test via @ODrive-QA
```

**Note:** Same agent can handle multiple domains via different prompts!

---

## Part 2: Cloud/Background Agents (7 min)

### Slide 6: Local vs Cloud Agents
**Layout:** Comparison table

| Local Agents | Cloud Agents |
|--------------|--------------|
| Run in VS Code | Run on GitHub |
| Interactive | Asynchronous |
| You wait for response | Get notification |
| Real-time iteration | Background processing |

---

### Slide 7: Background Agent Use Cases
**Layout:** 4 boxes

1. **Code Review Automation**
   - PR opened → @ODrive-QA reviews → Comments
   - Invokes `cpp-testing` skill

2. **Continuous Refactoring**
   - Nightly: @ODrive-Engineer adds docs, modernizes code

3. **Build & Test Automation**
   - @ODrive-QA invokes `odrive-ops` skill

4. **Multi-Repo Updates**
   - Coordinated changes across repos

---

### Slide 8: Background Agent Workflow
**Visual:** Flow diagram

```
Developer ──→ Define Task
               ↓
       Cloud Agent ──→ Execute
               ↓
          Create PR
               ↓
       Team Review ──→ Approve?
               ↓           ↓
             YES          NO
               ↓           ↓
            Merge      Refine
```

**Key Point:** Always review agent-generated PRs!

---

### Slide 9: Benefits & Limitations
**Layout:** Two columns

**✅ Benefits:**
- Asynchronous work
- Large-scale tasks
- Scheduled execution
- Audit trail in PRs
- Team collaboration

**⚠️ Limitations:**
- Requires GitHub.com
- Less interactive
- Review required
- Rate limits
- Context size limits

---

## Part 3: Live Demo (5 min)

### Slide 10: Demo - Encoder Calibration
**Slide Type:** Demo announcement

**Text:**
> 🎬 **LIVE DEMO: Parallel Agent Workflows**
> 
> Feature: Encoder Calibration
> 
> **Windows (Same Agents, Different Contexts):**
> 1. @ODrive-Engineer (hardware focus) → Electrical specs
> 2. @ODrive-Engineer (firmware focus) → Implementation
> 3. @ODrive-Engineer (control focus) → Control strategy
> 4. @ODrive-QA → Test plan (invokes cpp-testing skill)
> 
> **Watch:** All 4 windows working simultaneously!
> 
> **Key Insight:** Agents invoke skills automatically based on task.
> 
> See: `demo-script.md`

**Speaker Notes:** Execute the 5-minute demo

---

## Closing

### Slide 11: Key Takeaways
**Layout:** Summary bullets

**Section 8: Parallel Agents**
✅ 3x faster with parallel workflows  
✅ 6 agents available: `@ODrive-Engineer`, `@ODrive-QA`, `@ODrive-Ops`, `@ODrive-Reviewer`, `@ODrive-Toolchain`, `@ada-to-cpp-migrator`  
✅ Primary orchestrators: `@ODrive-Engineer` + `@ODrive-QA`  
✅ Same agent, different task contexts  
✅ Skills invoked automatically  
✅ Orchestration is the skill  
✅ Background agents for scale  

---

### Slide 12: Quick Exercise
**Text:**
> 🏋️ **5-Minute Exercise**
> 
> **Task:** CAN Bus Diagnostics
> 
> Use 3 parallel windows:
> - @ODrive-Engineer (hardware focus)
> - @ODrive-Engineer (firmware focus)  
> - @ODrive-QA (testing)
> 
> **Note:** Same agent handles multiple domains!
> 
> See: `hands-on-exercise.md`

---

### Slide 13: Q&A
**Layout:** Question prompts

**Common Questions:**
- How many windows can I run in parallel?
- What if agents give contradictory advice?
- Can I use the same agent in multiple windows?
  - **Yes!** Different task contexts, same agent.
- What other agents are available besides Engineer and QA?
  - `@ODrive-Ops` (CI/CD), `@ODrive-Reviewer` (code review), `@ODrive-Toolchain` (builds), `@ada-to-cpp-migrator`
- Do parallel agents cost more?
- Can I use this in air-gapped environments?

**Open Floor:** Any questions?

---

### Slide 14: Resources
**Layout:** Resource links

📚 **Materials:**
- Workshop Repo: [GitHub link]
- Prompt Library: `prompt-library.md`
- Demo Scripts: `demo-script.md`

📖 **Documentation:**
- GitHub Copilot Docs
- ODrive Documentation
- Custom Agent Guide

💬 **Support:**
- Workshop Slack: #copilot-workshop
- Email: [presenter email]

---

### Slide 15: Thank You
**Layout:** Closing slide

**Text:**
> 🎉 **Thank You!**
> 
> **Remember:**  
> You're not just coding anymore -  
> You're orchestrating AI experts!
> 
> **Next:** Break (2:50-3:00)
> **Then:** Day 1 Wrap-Up (3:00-3:15)

---

## Appendix: Backup Slides

### Backup Slide 1: Conflict Resolution
**When agents give contradictory advice:**

1. Review context provided to each
2. Ask for justification: "Why this approach?"
3. Use domain expert as tie-breaker
4. Consult team/documentation
5. Go with safest/simplest option

---

### Backup Slide 2: Cost Considerations
**Do parallel agents cost more?**

- Same total token usage
- Faster wall-clock time
- No "per-agent" fee
- Rate limits may apply
- Overall: More efficient!

---

## Slide Design Notes

### Visual Style
- **Clean, minimal** - Not too much text
- **Timeline diagrams** - Show speed improvements
- **Flow diagrams** - Illustrate workflows
- **Icons** - Use emojis or simple icons
- **Consistent colors** - Match Section 4 style

### Fonts
- **Titles:** 44pt, Bold
- **Body:** 24-28pt
- **Code:** 20pt, Monospace (Consolas, Monaco)

### Animation
- **Minimal** - Simple fade-ins
- **Timeline reveals** - Show sequential vs parallel
- **Avoid** - Transitions, spins, bounces

---

## Timing Breakdown

| Slide Range | Topic | Time |
|-------------|-------|------|
| 1-5 | Multiple Agents | 8 min |
| 6-9 | Cloud Agents | 7 min |
| 10-15 | Demo & Close | 5 min |
| **Total** | | **20 min** |

---

## Presenter Reminders

- ⏰ **Keep it tight** - 20 minutes goes fast!
- 🎤 **Emphasize speed** - Show the time savings
- 👀 **Demo is key** - Seeing 4 agents work is powerful
- 🖱️ **Have backup** - Pre-recorded if network fails
- ⏸️ **Save time for exercise** - 5 minutes hands-on
- 📱 **Phone on silent** - No interruptions

**Good luck! 🚀**
