# C-Shell for Linux and Windows

This project is a simple command-line shell implemented in C++. It supports basic shell commands and is designed to work on both Linux and Windows platforms. The primary goal of this project is to get comfortable with basic C++ development.

## Features

- Supports basic shell commands like `cd`, `pwd`, `echo`, and `type`.
- Cross-platform compatibility (Linux and Windows).

## Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/C-shell-for-linux-and-windows.git
   ```
2. Navigate to the project directory:
   ```sh
   cd C-shell-for-linux-and-windows
   ```

## Building and Running

### On Linux

1. Compile the source code:
   ```sh
   g++ -o shell src/main.cpp
   ```
2. Run the shell:
   ```sh
   ./shell
   ```

### On Windows

1. Compile the source code using a compiler like MinGW:
   ```sh
   g++ -o shell.exe src/main.cpp
   ```
2. Run the shell:
   ```sh
   shell.exe
   ```

## Usage

Once the shell is running, you can use the following commands:

- `cd <directory>`: Change the current directory.
- `pwd`: Print the current working directory.
- `echo <message>`: Print the message to the console.
- `type <file>`: Display the contents of a file.
- `exit 0`: Exit the shell.

Enjoy using your custom C++ shell!
