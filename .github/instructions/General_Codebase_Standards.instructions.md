---
name: 'General Codebase Standards'
description: 'Universal standards for file encoding, comments, and safety applicable to all files.'
applyTo: '**'
---

# General Codebase Standards

## File Formatting
- **Encoding**: UTF-8 is mandatory for all text files.
- **Line Endings**: Use Unix-style (LF) line endings.
- **Trailing Whitespace**: Remove trailing whitespace from lines.
- **End of File**: Methodically ensure every file ends with a newline.

## Comments and Documentation
- **Language**: All code comments and documentation must be written in English.
- **TODOs**: formatting should follow `TODO(user): description` or `FIXME(issue-id): description`.
- **Commented Code**: Do not commit commented-out code. Delete it or gate it with a preprocessor/config flag if strictly necessary.

## Security & Safety
- **Secrets**: Absolutely no hardcoded secrets, tokens, or passwords in the source code.
- **PII**: Do not include Personally Identifiable Information in test data or comments.

## Naming Conventions
- **Cross-Platform**: File names should be case-insensitive unique (e.g., do not have `File.txt` and `file.txt` in the same folder).
- **Characters**: Use only alphanumeric characters, underscores (`_`), hyphens (`-`), and dots (`.`) in file names. Avoid spaces.
