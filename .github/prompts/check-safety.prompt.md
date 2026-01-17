---
name: check-safety
description: 'Perform a safety check on a specific module'
agent: agent
tools: ['read_file', 'file_search']
---
I want you to perform a safety analysis on a specific module file provided by the user (or the active file).

Check for:
1. **Race Conditions**: Shared variables accessed without locks/interrupt protection.
2. **Null Dereferences**: Pointers used without checking.
3. **Floating Point Safety**: Division by zero or likely NaN propagation.
4. **Deadlocks**: Potential lock ordering issues.

Output a Markdown report with a "Risk Level" (Low/Medium/High) for each finding.
