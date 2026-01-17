---
name: audit-todos
description: 'Scan workspace for TODOs and FIXMEs'
agent: agent
tools: ['grep_search']
---
Scan the entire `Firmware/` directory for comments containing "TODO" or "FIXME".

1. List all findings grouped by file.
2. For each, try to assess priority based on context (e.g., is it in a critical logic path?).
3. Suggest a GitHub issue title for the most critical group of TODOs.
