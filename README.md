# The lightweight ini env parser LIEP 

It allows you to use .ini files in your c++ projects (or defacto .env files if you prefer it that way)

It does not require any external c++ library 

## The structure of the project

* ``/lib/liep.h`` -> this is a file that you can use to link as a header to your c++ project
* ``/obj/liep.o`` -> this is an object file that you can use to compile your c++ project (after a compilation)
* ``/src/liep.cpp`` -> is the source code
* ``compile.bat`` -> a compilation script
* ``main.cpp`` -> tests that i have used during creating it
* ``test.ini`` -> a test .ini file with all functionalities
* ``main.o`` -> an object file of main.cpp (after a compilation)
* ``main.exe`` -> the compiled thing
* ``docs/`` -> just docs

## how to compile

### standalone

just use ``./compile.bat`` as it has all commands

### with your project

use ``liep.h`` as a header and ``liep.o`` as an object file during the final compilation.
You don't need to use other files.

# how to use?

[here are instructions](docs/index.md)

# license

[here](LICENSE)
