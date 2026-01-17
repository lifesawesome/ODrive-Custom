---
name: generate-doctest
description: Generate a unit test for MotorController initialization
agent: ask
---

Create a unit test using `doctest` for the `MotorController` class initialization logic found in [Firmware/MotorControl/](Firmware/MotorControl/).

The test should verify:
1. Default parameter initialization
2. Error handling during invalid configuration scenarios
3. Successful state transition after `initialize()` is called
