# djl-utils

*nix-style utilities

## Goals

* A collection of simple, self-explanitory CLI tools.
* Statically compilable (where applicable)
* Standalone applications -- if only one tool is required the source code for
  that tool alone need be distributed.

## Tools

* **confirm**: Prompt user for confirmation and report response via exit code
* **line**: Extract line(s) from stdin
* **suptime**: System uptime in terms of seconds, minutes, hours or days
* **timestamp**: Current date-timestamps in common formats
* **truthy**: Test if input is true-adjacent

## Embeddable utils

I hope to eventually rewrite these tools in posix sh(1). This removes
the need to compile this files and allows for the to be embedded in
other scripts if desired. I have started with confirm(1) but am unsure
if suptime(1) and timestamp(1) can realistically be rewritten.

The scripts which have been rewritten check what the environment `$0` is
set to, to determine whether they behave as a CLI utility or exposing a
shell functions.  In the case where `source` or `.` are used from another
shell script `$0` will be the name of the "calling" script (ie the one
"sourcing" the util).

I don't actually know if this is useful (yet)!

## Notes

I was originally using this to self-teach the basics of C. The code is
not "good" and likely has some bugs (sh code incl.).

