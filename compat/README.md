# Compatability patches

This directory contains some pre-prepared patches mainly for cross-platform
compatability reasons. The patches are formatted in a way such that applying
them will not break existing build targets (ie. macro checks are done), so if
you are shipping a util that needs cross-platform support you can pre-apply
any relevant patches and ship the patched source-code.

## Included patches

* **confirm.getline.diff**: adds a basic `getline` implementation
* **confirm.fflush.diff**: fflush(3) on stdout before reading from stdin,
  needed on Windows + MinGW terminal where prompt is otherwise printed after
  reading user input

