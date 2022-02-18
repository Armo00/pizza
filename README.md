# API-LP - A Less Painful Framework

It's just yet another C++ REST Framework, but it's aiming at making "write RESTful APIs with C++" a less painful journey full of pleasure. 😊

## What you've got?

Internally using Pistache, with API-LP you may just focus on your own business logic, yet still deliver a performant server application with safety and strong robustness. 🍻

Tired of the writing Python applications, but find writing REST APIs in C++ very painful? You are coming to the right place. 🤫

## Any concepts?

Basic concepts of this framework include `Endpoint` and `Handler`.

 * `Handler` defines how to handle and proccess a specific request.
 * `Endpoint` collects all `Handlers` together and serves them.

## How To Build?

Currently only Linux machines are required to build this project. If you don't have one, please consider setting up a virtual machine.

After cloning this project to somewhere on your Linux machine, you first need to have `cmake` and `ninja`, as well as the latest version of `clang` and `g++`. You will also need `python3` to install `conan`.

Assuming you are using Debian, you may do this to have the required packages installed:

```
 # apt-get install build-essentials cmake ninja clang-13 g++-11 python3 python3-pip
 $ pip install --user conan
```

After conan is installed, read `conanfile.ini` and `conanprofile.debug.ini`, and use `conan install` to install build dependencies.

After `conan install` is complete, use `cmake` and `ninja` to build.

```
 $ mkdir -p build && pushd build
 $ conan install ../conanfile.ini --profile ../conanprofile.debug.ini --build missing
 $ cmake -GNinja -DCMAKE_C_COMPILER=/usr/bin/clang-13 -DCMAKE_CXX_COMPILER=/usr/bin/clang++ ..
 $ ninja && popd
```

## What next?

 1. You copy-rename the `hello_world` folder in `endpoint`.
 2. You write your own business logic in your own `Handler` there.
 3. You add your `Handlers` to the `Endpoint`.
 5. You re-run the build command.
 6. You run your application on your server.

## Release Notes

 1. Currently, under `library/include` you should only put header files there, the `#include <foo/bar.h>` path would be strictly following the directory structure. Your `namespace` definitions should also follow the directory structure. We recommend you to put your supporting code and details under `library/include`.

 2. The `hello_world` endpoint is not technically a `Hello, World`, it's rather an example showing you how to use this framework to serve something.

 3. You may receive updates by (for now) merging "the latest commit from me" into "your local branch".

 4. This project would not be possible without the existence of Pistache. Do not forget to pay them a visit as well. 😊

 5. Since I'm currently the only person working on this project... If you used my framework and made changes under `library/include/own` and `library/include/external`, PR this change back to me, please! That would be appreciated. 😖
