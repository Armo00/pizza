# "restapi-cxx" - Yet another C++ REST Framework

It's just yet another C++ REST Framework, but it's aiming at making "write RESTful APIs with C++"
a less painful journey full of pleasure. 😊

## How To Build

After cloning this project to somewhere on your build machine, read the `conanfile.ini` and
`conanprofile.debug.ini` to figure out how to use `conan install` to satisfy the requirements
by yourself.

Or do the followings instead if you are on Arch Linux: (but I still recommend you to read those
two forementioned files in case you need customization 🤫)

```
 $ mkdir -p build && pushd build
 $ conan install ../conanfile.ini --profile ../conanprofile.debug.ini --build missing
 $ cmake -GNinja -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ ..
 $ ninja && popd
```

# What next?

Locally fork this project, add stuffs under `library` and `endpoint` to suit your own unique needs.

Currently, under `library` you should only put header files in there, the `#include <foo/bar.h>`
would be strictly following the directory structure; while under `endpoint`, straight on create
a new folder and see how `hello_world` is composed. I'm sure you will get the point. (Yes,
of course you may also copy-rename the `hello_world` folder for a fresh starting point. 🤫)

You may also receive updates by (for now) merging "the latest commit from me" into
"your local branch".

PS: Since I'm currently the only person working on this project... If you used my framework and
made changes under `library/own` and `library/external`, PR this change back to me, please!
That would be appreciated. 😖
