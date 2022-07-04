# Visual Studio Code

## Shortcuts

Open command palette `Win: F1` or `Ctrl+Shift+P`.

Beautify code On Windows `Shift + Alt + F` or `Ctrl + Shift + I` on Linux

## Tasks

We will look at a task to build a C++ file.

Tasks are stored in `.vscode\tasks.json`

> Flag `-g` while compiling is important if we want to debug. If not added the debugger will not stop at breakpoints and will complete the execution.

```json
{
  "tasks": [
    {
      "type": "cppbuild", //The task's type. For a custom task, this can either be shell or process
      "label": "C/C++: build", //Task label used in UI
      "command": "G:/CodeBlocks/MinGW/bin/g++.exe", //Actual command to execute
      "args": ["-g", "${file}", "-o", "${fileDirname}\\${fileBasenameNoExtension}.o"],
      //The args array specifies the command-line arguments that will be passed to g++
      "options": {
        "cwd": "${fileDirname}" //current working directory
      },
      "problemMatcher": ["$gcc"], //lint tool
      "group": {  //defines to which group the task belongs 
        "kind": "build",
        "isDefault": true
      },
      "detail": "C++ : Build"
    },
    {
      "type": "shell",
      "label": "C++: build run",
      "command": "${fileDirname}\\${fileBasenameNoExtension}.o",
      "dependsOrder": "sequence", //Sequence of task
      "dependsOn": [ //Runs the tasks defined in the array before this task is run.
        "C++: build"
      ],
      "detail": "C++ : Build and Run",
      "problemMatcher": [ //defines the pattern for the errors that are displayed in the terminal
        "$gcc"
      ]
    }
  ],
  "version": "2.0.0"
}

//-- type -> For custom tasks
//If shell is specified, the command is interpreted as a shell command 
//(for example: bash, cmd, or PowerShell).
//If process is specified, the command is interpreted as a process to execute.

//-- windows -> Any Windows specific properties. Will be used instead of default

//-- presentation ->  Defines how the task output is handled in the user interface.

//-- options: Override the defaults for cwd (current working directory),
//env (environment variables), or shell (default shell).
```

## Configurations

Configurations of vs code are stored in `.vscode/launch.json`.

Following is an example of configuration for dubugging C++ code.

We Use the above build task that we created to first build the file executable to the file we want to debug by compiling with our compiler.

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "g++.exe - Build and debug active file",
      "type": "cppdbg",
      "request": "launch",
      "program": "${fileDirname}\\${fileBasenameNoExtension}.o", //file to be executed to debug
      "args": [],
      "stopAtEntry": false, //No default breakpoint are created by vscode
      "cwd": "${fileDirname}", //current working directory
      "environment": [],
      "externalConsole": false, //will use internal console of vs code
      "MIMode": "gdb", //debugger
      "miDebuggerPath": "G:\\CodeBlocks\\MinGW\\bin\\gdb.exe", //debugger path
      "setupCommands": [
        {
          "description": "Enable pretty-printing for gdb",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        }
      ],
      "preLaunchTask": "C/C++: build"
    }
  ]
}
```
