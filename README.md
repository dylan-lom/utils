# djl-utils

*nix-style utilities

## Goals

* A collection of simple, well-documented CLI tools that follow *nix conventions
* Minimal external dependencies, statically compilable
* Standalone applications -- if only one tool is required the source code for
  that tool alone need be distributed.

**NOTICE** (2021-04-24): The project is still at a very early stage and these
goals have not yet been achieved, as they were not the *original* goals of the
project (eg. compilation/build process currently produces a .deb file)

## Tools

* **confirm**: Prompt user for confirmation and report response via exit code
* **countdown**: Start a countdown timer
* **line**: Extract line(s) from stdin
* **stopwatch**: Start a stopwatch timer
* **suptime**: System uptime in terms of seconds, minutes, hours or days
* **timestamp**: Current date-timestamps in common formats
* **truthy**: Test if input is true-adjacent

