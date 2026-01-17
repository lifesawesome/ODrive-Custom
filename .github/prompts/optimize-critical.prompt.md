---
name: optimize-critical
description: 'Optimize critical path code for performance'
agent: edit
---
Analyze the selected code block, which is part of a critical real-time execution path.

1. Identify any potential performance bottlenecks (e.g., division, heavy trig functions, memory allocation).
2. Suggest 2-3 specific optimizations to reduce cycle count or memory usage.
3. Apply the changes if they are safe and don't reduce readability significantly.
4. **Strict rule**: No dynamic memory allocation (`new`, `malloc`, `std::vector` resizing) allowed.
