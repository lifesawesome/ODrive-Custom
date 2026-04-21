# GitHub Copilot Hackathon for Embedded C++ Developers

## 🎯 Workshop Overview

| Detail | Description |
|--------|-------------|
| **Audience** | 100 C++/Embedded Developers (Intermediate to Advanced) |
| **Languages** | C++, C, Ada for embedded/RTOS development |
| **Editor** | VS Code with GitHub Copilot |
| **Schedule** | 8:00 AM - 3:00 PM (Both Days) |
| **Reference Repos** | [ODrive](https://github.com/odriverobotics/ODrive), [Marlin](https://github.com/MarlinFirmware/Marlin) |

---

**2-Day Workshop**

A hands-on hackathon teaching embedded C++ developers how to leverage GitHub Copilot for agentic development workflows. Migrate existing applications into agentic patterns for developer acceleration.

---

### Workshop Goals

- Apply agentic development patterns to real-world C++ codebases
- Modernize legacy embedded code using AI-assisted workflows

### We Will Not Cover

- Copilot usage statistics and satisfaction insights
- Customer success case studies
- Enterprise and organization administrator interfaces

## 🎓 Key Learning Outcomes

### Copilot Features

- Inline code completion and Chat modes (@workspace, @vscode)
- TODO: Model picking - premium requests.
- Context steering with copilot-instructions.md and prompt files
- Decomposition and iterative refinement for complex tasks
- Custom agents and skills for domain-specific workflows
- Debugging with @terminal and /fix commands
- CLI usage for automation and scripting
- Multi-agent patterns for parallel workstreams

### Embedded C++ Patterns

- Static allocation (no heap)
- No exceptions (error codes)
- Volatile correctness for hardware
- RAII resource management
- ISR-safe data structures

## 🚀 Quick Start

### Prerequisites

1. **VS Code** with the following extensions:
   - GitHub Copilot
   - GitHub Copilot Chat
   - C/C++ Extension Pack

2. **GitHub Copilot license** - Active subscription

3. **Terminal Access for installing CLI components**

4. **Source Control** -  access to hack repo.

---

## 🗂️ Repository Structure

```
ODriveHack/
├── .github/
│   ├── copilot-instructions.md    # Repo-level coding standards
├── lessons/
│   ├── 01-welcome-agenda/         # Day 1 agenda and objectives
│   ├── 02-basic features/         # Copilot modes and commands
│   ├── 03-planning/               # Steering documents
│   ├── 04-agentic-patterns/       # Context engineering
│   ├── 05-best-practices/         # C++ patterns with Copilot
│   ├── 06-debugging/              # AI-assisted debugging
│   ├── 07-copilot-cli/            # Command-line interface
│   ├── 08-parallel-agents/        # Multi-agent workflows
│   
├── src-ODrive/                    # ODrive firmware for exercises
└── README.md                      # This file
```
---


## 📚 Lesson Overview

### Day 1: GitHub Copilot for Embedded C/C++ Development

| # | Lesson | Duration | Topics |
|---|--------|----------|--------|
| 1 | [Welcome & Setup](lessons/01-welcome-agenda/agenda.md) | 40 min | Objectives, workspace setup, Copilot architecture |
| 2 | [Basic Features](lessons/02-basic%20features/readme.md) | 45 min | Chat modes, @workspace, /fix, /explain, inline chat |
| 3 | [Planning & Steering](lessons/03-planning/readme.md) | 60 min | spec driven development, copilot-instructions.md, prompt files, custom agents, skills |
| 4 | [Agentic Patterns](lessons/04-agentic-patterns/readme.md) | 45 min | Context engineering, decomposition, iterative refinement |
| 5 | [C++ Best Practices](lessons/05-best-practices/readme.md) | 50 min | RAII, templates, const correctness, embedded patterns |
| 6 | [Debugging](lessons/06-debugging/readme.md) | 45 min | @terminal, /fix, common C++ bugs |
| 7 | [Copilot CLI](lessons/07-copilot-cli/readme.md) | 45 min | Using the cli. |
| 8 | [Parallel Agents](lessons/08-parallel-agents/readme.md) | 20 min | Multi-agent workflows, cloud agents, offline considerations |

## Day 2: Hack Day - Modernize Your Projects

### Morning Session (8:00 AM - 12:00 PM)

#### 1. Hack Day Kickoff (8:00 - 8:30) — 30 min
| Sub-Topic | Focus | Time |
|-----------|-------|------|
| Day 2 Objectives & Rules | Hack format, judging criteria, prizes | 10 min |
| Project Selection Guidance | How to scope a half-day modernization effort | 10 min |
| Team Formation & Coach Intro | Self-organize into teams of 3-5, meet coaches | 10 min |

#### 2. Hack Sprint 1 (8:30 - 10:00) — 90 min
| Activity | Focus | Time |
|----------|-------|------|
| Project Setup | Teams configure workspace, create copilot-instructions.md, identify targets | 30 min |
| Active Hacking | Apply Day 1 techniques to real embedded projects | 60 min |

> Teams can choose general C++ modernization or embedded-specific challenges

**☕ Break (10:00 - 10:15) — 15 min**

#### 3. Hack Sprint 2 (10:15 - 11:45) — 90 min
| Activity | Focus | Time |
|----------|-------|------|
| Continued Hacking | Deep work on modernization tasks | 75 min |
| Mid-Sprint Check-In | Quick team status, blocker resolution with coaches | 15 min |

**🍽️ Lunch (11:45 - 12:30) — 45 min**

---

### Afternoon Session (12:30 PM - 3:00 PM)

#### 4. Hack Sprint 3 + Demo Prep (12:30 - 2:00) — 90 min
| Activity | Focus | Time |
|----------|-------|------|
| Final Hacking Push | Complete modernization, polish results | 60 min |
| Demo Preparation | Teams prepare 3-min presentations (before/after) | 30 min |

#### 5. Team Demonstrations (2:00 - 2:45) — 45 min
| Activity | Focus | Time |
|----------|-------|------|
| Team Demos | 3 min per team, showcase before/after | 35 min |
| Audience Q&A | Quick cross-team learning | 10 min |

> **Note:** With 100 developers in teams of 3-5, expect ~20-25 teams. Select top 10-12 for demos or run parallel demo tracks.

#### 6. Closing & Awards (2:45 - 3:00) — 15 min
| Sub-Topic | Focus | Time |
|-----------|-------|------|
| Judging & Awards | Best modernization, most creative, best use of Copilot | 5 min |
| Key Takeaways | Recap techniques, resources for continued learning | 5 min |
| Next Steps & Feedback | Support channels, quick feedback survey | 5 min |

---

## 📊 Day 2 Success Criteria

Teams should demonstrate:

- **Before/After comparison** - Original code vs. Copilot-assisted modernization
- **Agentic workflow** - Which steering docs, prompts, or agents were used
- **Quantifiable improvement** - Lines refactored, tests added, docs generated
- **Lessons learned** - Tips and insights for the broader team

---

### Recording
- ✅ Sessions can be recorded for playback (per customer request)
- Recommend recording Day 1 instructional content only
- Day 2 hack sessions typically not recorded (IP concerns)



## 📚 Additional Resources

### Microsoft Learn

- [Get Started with GitHub Copilot in VS Code](https://learn.microsoft.com/training/modules/get-started-github-copilot-visual-studio-code/)
- [GitHub Copilot Chat in VS Code](https://learn.microsoft.com/training/modules/use-github-copilot-chat-vs-code/)
- [C++ Development in VS Code](https://learn.microsoft.com/cpp/build/vscpp-step-0-installation)
- [GitHub Copilot CLI](https://learn.microsoft.com/training/modules/use-github-copilot-cli/)

### Reference Repositories

- [ODrive Firmware](https://github.com/odriverobotics/ODrive) - Motor control, embedded C++
- [Marlin Firmware](https://github.com/MarlinFirmware/Marlin) - 3D printer firmware

---

## 👥 Instructors

| Initials | Name |
|----------|------|
| TM | Tammy McClellan |
| TI | Tom Iverson |
| GB | Gaurav Bhardwaj |

---

## 📝 License

Workshop materials are provided for educational purposes. 
