# 🐚Minishell

> A Unix shell recreation project developed at School 42.

## 🧠 Objective

The **Minishell** project is designed to build a simple shell from scratch, gaining a deep understanding of how a real Unix shell works. The program interprets user input, executes commands, manages processes, and handles redirections, pipes, environment variables, and more.

---

## ✅ Features

- Execution of simple and compound commands
- Support for multiple **pipes** (`|`)
- Redirection support:
  - Input (`<`)
  - Output (`>`)
  - Append (`>>`)
  - Heredoc (`<<`)
- Built-in commands implemented:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Environment variable handling (`$VAR`)
- Variable expansion (`$?`, `~`, etc.)
- Works even with minimal or empty `PATH`
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
- Memory management (no leaks, no "still reachable")

---

## 🛠️ How to Compile

```bash
  - make
  - make v (To use valgrind)
  - env -i ./minishell (To use without enviroment VARS)
  - make re (To recompile)
  - make fclean (To clean everything)
