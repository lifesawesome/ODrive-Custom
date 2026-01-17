---
name: odrive-qa-testing
description: QA testing skill for ODrive motor control firmware and software. Use when creating/debugging firmware tests (C++/doctest), Python tool tests (pytest), integration tests, motor control validation, encoder testing, calibration procedures, or analyzing test failures. Includes test rig setup, protocol testing (CAN/UART/USB), and hardware-in-loop testing.
---

# ODrive QA Testing Skill

This skill helps QA engineers test ODrive motor control firmware, Python tools, and integration scenarios for robotics applications.

## When to use this skill

Use this skill when you need to:
- Write or debug unit tests for firmware (C++ with doctest)
- Create Python tests for ODrive tools (pytest)
- Set up or configure hardware test rigs
- Test motor control algorithms (FOC, velocity, position control)
- Validate encoder functionality and calibration
- Test communication protocols (CAN, UART, USB, ASCII)
- Perform integration testing across firmware and PC tools
- Analyze test failures and debug test code
- Review code for testability and quality

## Project Structure

```
ODrive/
├── Firmware/
│   ├── MotorControl/        # Core motor control algorithms
│   ├── Tests/               # Firmware unit tests (doctest)
│   ├── communication/       # Protocol implementations
│   └── doctest/            # Test framework
├── tools/
│   ├── run_tests.py        # Main test runner
│   ├── test-rig-*.yaml     # Hardware test configurations
│   └── odrive/tests/       # Python tool tests
└── docs/
    ├── testing.rst         # Testing documentation
    └── developer-guide.rst # Developer guidelines
```

## Firmware Testing (C++)

### Creating Unit Tests

1. Create test file in `Firmware/Tests/` named `test_<component>.cpp`
2. Include the doctest framework and component header
3. Use `TEST_CASE` for test suites and `SUBCASE` for variations
4. Follow [coding standards](../../instructions/CPP_Coding_Practices.instructions.md)

**Example test structure:**

```cpp
#include "doctest.h"
#include "motor_controller.hpp"

TEST_CASE("Motor controller speed control") {
    MotorController motor;
    
    SUBCASE("sets target speed within limits") {
        REQUIRE(motor.setSpeed(1000.0f) == ErrorCode::Success);
        CHECK(motor.getTargetSpeed() == 1000.0f);
    }
    
    SUBCASE("rejects speed beyond limits") {
        REQUIRE(motor.setSpeed(50000.0f) == ErrorCode::OutOfRange);
    }
    
    SUBCASE("handles uninitialized state") {
        MotorController uninitMotor;
        REQUIRE(uninitMotor.setSpeed(100.0f) == ErrorCode::NotInitialized);
    }
}
```

### Running Firmware Tests

```bash
# Build and run all tests
cd Firmware
make test

# Run specific test file
make test TEST_FILTER="test_motor_controller"

# Run with coverage
make coverage
```

### Key Testing Areas

- **Motor Control**: FOC algorithms, current/velocity/position loops
- **Encoders**: Incremental, hall effect, SPI encoders
- **Calibration**: Motor parameters, encoder offset, current sensing
- **Safety**: Fault detection, over-current, over-voltage protection
- **Protocols**: CAN, UART, USB communication

## Python Tool Testing

### Creating Python Tests

1. Create test file in `tools/odrive/tests/` named `test_<feature>.py`
2. Use pytest fixtures for setup/teardown
3. Mock hardware dependencies (USB, serial)
4. Use parametrize for multiple scenarios

**Example test structure:**

```python
import pytest
from unittest.mock import Mock
from odrive import ODrive
from odrive.enums import *

@pytest.fixture
def mock_odrive():
    """Provide mocked ODrive instance"""
    odrive = Mock(spec=ODrive)
    odrive.axis0 = Mock()
    odrive.axis0.controller = Mock()
    return odrive

def test_velocity_control_mode(mock_odrive):
    """Test velocity control mode configuration"""
    mock_odrive.axis0.controller.config.control_mode = CONTROL_MODE_VELOCITY_CONTROL
    mock_odrive.axis0.controller.input_vel = 100.0
    
    assert mock_odrive.axis0.controller.config.control_mode == CONTROL_MODE_VELOCITY_CONTROL
    assert mock_odrive.axis0.controller.input_vel == pytest.approx(100.0)

@pytest.mark.parametrize("velocity,expected", [
    (0.0, 0.0),
    (100.0, 100.0),
    (-50.0, -50.0),
])
def test_velocity_setpoints(mock_odrive, velocity, expected):
    """Test various velocity setpoints"""
    mock_odrive.axis0.controller.input_vel = velocity
    assert mock_odrive.axis0.controller.input_vel == pytest.approx(expected)
```

### Running Python Tests

```bash
# Run all tests
python tools/run_tests.py

# Run specific test file
pytest tools/odrive/tests/test_controller.py -v

# Run with coverage
pytest --cov=odrive --cov-report=html

# Run integration tests only
pytest -m integration
```

## Integration Testing

### Test Rig Configuration

Test rigs are configured using YAML files in `tools/test-rig-*.yaml`:

```yaml
# test-rig-example.yaml
name: QA Test Rig
description: Standard configuration for QA testing

axes:
  - name: axis0
    motor:
      type: D5065_270KV
      pole_pairs: 7
      resistance: 0.05  # Ohms
      inductance: 0.00001  # H
    encoder:
      type: incremental
      cpr: 8192
    controller:
      vel_limit: 20.0  # turns/s
      current_limit: 60.0  # A

  - name: axis1
    motor:
      type: D6374_150KV
      pole_pairs: 7
    encoder:
      type: hall_effect
      cpr: 42
```

### Running Integration Tests

```bash
# Specify test rig configuration
python tools/run_tests.py --test-rig=tools/test-rig-qa.yaml

# Run specific integration test
python tools/run_tests.py --test=multi_axis_coordination
```

## Protocol Testing

### CAN Protocol Testing

```python
# Example: Test CAN message encoding/decoding
def test_can_velocity_command():
    """Test CAN velocity command message"""
    msg = encode_can_message(MSG_SET_VELOCITY, axis=0, velocity=100.0)
    assert msg.arbitration_id == 0x00D  # Velocity command ID
    assert decode_float(msg.data[0:4]) == pytest.approx(100.0)
```

### ASCII Protocol Testing

```python
def test_ascii_protocol_commands(mock_serial):
    """Test ASCII protocol command parsing"""
    # Read velocity
    mock_serial.write(b"r axis0.encoder.vel_estimate\n")
    response = mock_serial.readline()
    assert float(response) >= 0
    
    # Set velocity
    mock_serial.write(b"v 0 100.0\n")
    assert mock_serial.readline() == b"OK\n"
```

## Test Failure Analysis

When a test fails, follow this process:

1. **Reproduce Reliably**
   - Run test multiple times to confirm consistency
   - Check if failure is intermittent (flaky test)

2. **Isolate the Issue**
   - Run only the failing test
   - Add debug output to narrow down failure point
   - Check recent code changes that might affect the test

3. **Analyze Root Cause**
   ```bash
   # Enable verbose output
   pytest -vv --tb=long
   
   # Run with debugger
   pytest --pdb
   ```

4. **Document and Fix**
   - Document reproduction steps
   - Create minimal failing test case
   - Fix issue and verify all related tests pass

## Quality Checklist

Before submitting code, verify:

- [ ] All new functions have unit tests
- [ ] Test names clearly describe what they test
- [ ] Edge cases are covered (null, zero, max values)
- [ ] Error handling paths are tested
- [ ] No test interdependencies (tests run in any order)
- [ ] Tests complete in reasonable time (<1s for unit tests)
- [ ] Mock hardware dependencies appropriately
- [ ] Test documentation explains setup and expected behavior
- [ ] Code follows [ODrive C++ standards](../../instructions/CPP_Coding_Practices.instructions.md)

## Code Review Focus

When reviewing code for testability:

- **Single Responsibility**: Each class/function does one thing
- **Dependency Injection**: Pass dependencies rather than hardcoding
- **Error Handling**: All error cases have tests
- **Thread Safety**: Concurrent access is properly synchronized
- **Resource Management**: No memory leaks, proper cleanup
- **Documentation**: Clear pre/post conditions

## Common Testing Patterns

### Mocking Hardware Interfaces

```cpp
// Mock encoder interface for testing
class MockEncoder : public EncoderInterface {
public:
    MOCK_METHOD(int32_t, getPosition, (), (override));
    MOCK_METHOD(float, getVelocity, (), (override));
    MOCK_METHOD(bool, initialize, (), (override));
};

TEST_CASE("Motor uses encoder feedback") {
    MockEncoder encoder;
    EXPECT_CALL(encoder, getVelocity()).WillOnce(Return(100.0f));
    
    MotorController motor(&encoder);
    motor.update();
    // Verify motor responds to encoder feedback
}
```

### Testing Calibration Procedures

```python
def test_motor_calibration():
    """Test complete motor calibration procedure"""
    odrive = setup_test_odrive()
    
    # Start calibration
    odrive.axis0.requested_state = AXIS_STATE_MOTOR_CALIBRATION
    
    # Wait for completion
    while odrive.axis0.current_state != AXIS_STATE_IDLE:
        time.sleep(0.1)
    
    # Verify calibration succeeded
    assert odrive.axis0.motor.is_calibrated
    assert odrive.axis0.motor.config.phase_resistance > 0
    assert odrive.axis0.motor.config.phase_inductance > 0
```

## Tools and Commands

### Coverage Analysis

```bash
# C++ coverage
cd Firmware
make coverage
# Open htmlcov/index.html

# Python coverage  
pytest --cov=odrive --cov-report=html
# Open htmlcov/index.html
```

### Debugging Tests

```bash
# GDB for firmware tests
gdb Firmware/build/tests
(gdb) run
(gdb) bt  # Backtrace on failure

# Python debugger
pytest --pdb  # Drop into debugger on failure
pytest -k test_name --pdb  # Debug specific test
```

## Best Practices

1. **Test Isolation**: Each test should be independent
2. **Fast Execution**: Unit tests should run in milliseconds
3. **Clear Assertions**: Use descriptive assertion messages
4. **Avoid Flakiness**: Don't rely on timing or external state
5. **Test Behavior**: Test what code does, not how it does it
6. **Readable Tests**: Tests document expected behavior
7. **Continuous Testing**: Run tests frequently during development

## Resources

- [ODrive Testing Documentation](../../../docs/testing.rst)
- [Developer Guide](../../../docs/developer-guide.rst)
- [C++ Coding Standards](../../instructions/CPP_Coding_Practices.instructions.md)
- [Existing Tests](../../../Firmware/Tests/)
- [Python Test Suite](../../../tools/odrive/tests/)

---

*This skill is maintained by the QA team. Update as new testing techniques and tools are introduced.*
