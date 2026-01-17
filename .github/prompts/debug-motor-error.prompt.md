---
name: debug-motor-error
description: Analyze how motor errors are reported and handled
agent: ask
---

I'm seeing a 'Motor Error' in the logs. How does the error reporting mechanism work in [Firmware/MotorControl/](Firmware/MotorControl/)?
Please explain:
1. Where error enums are defined
2. How errors are propagated from low-level drivers to the main loop
3. How errors are exposed to the communication interface
