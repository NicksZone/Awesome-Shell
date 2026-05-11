# NikasShell

NikasShell is a custom Unix-like shell written in C as a personal systems programming project.
It currently supports a basic interactive shell loop, built-in commands, and execution of custom external commands compiled into the `bin/` directory.

## Project Status

This project is **ongoing** and actively being developed.
I am continuously adding new features, improving command behavior, and refining the shell architecture.

## Current Features

- Interactive prompt that shows the current working directory
- Built-in commands:
  - `cd`
  - `help`
  - `exit`
- External command execution from local `bin/` (via `fork` + `execv`)
- Custom command binaries:
  - `ls` (basic directory listing)
  - `cat` (file content viewing, line numbering, and simple redirection-style output)
- Basic tokenization/parsing groundwork for future pipe support

## Project Structure

- `shell/` - core shell logic (loop, parser, executor, builtins, prompt)
- `commands/` - custom command implementations compiled as standalone binaries
- `bin/` - generated executables (`lsh`, `ls`, `cat`)
- `Makefile` - build rules for shell and command binaries

## Build

```bash
make
```

## Run

```bash
./bin/lsh
```

## Clean Build Artifacts

```bash
make clean
```

## Notes

- This is a learning-focused project, so some components are intentionally evolving.
- Pipe handling and additional shell features are planned as development continues.