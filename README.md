<img align="left" style="width:230px" src="https://github.com/numpad/cup/blob/master/resources/logo.png" width="288px">

**cup is a simple preprocessor to enjoy c programming.**

inspired by the few and far between improvements modern programming languages provide over c, cup aims to introduce a small set of sane language features and bring c99 to the 2000's!

*NOTE: cup is an experimental c language preprocessor and should probably never be used for more than fun and maybe learning purposes.*

---

<br>


features
--------
- [x] **optional parentheses** for `if`, `while` and `do-while`
- [ ] range-based **for-loop** syntax
- [ ] powerful **code generation**
- [ ] modern **#include** syntax with light **namespacing**
- [ ] `defer` statement (or `scoped` qualifier?)
- [ ] basic facilities for **struct member initialization**
- [ ] **enum safety** additions
- [ ] full **compliance** with c syntax


example
-------
this is a very basic example of the cup language additions:

```c
// clean includes
#include stdio.h, math.h

// default initializers
struct document {
  char *path = NULL;
  int size = 0;
};

int main(int argc, char **argv) {
  // defer call until going out of scope.
  int *mem = malloc(128);
  defer free(mem);

  // optional parentheses
  if argc != 1 {
    return 1;
  }

  // for-loop ranges
  for i in 1..argc {
    printf("%s\n", argv[i]);
  }

  return 0;
}

```

building and usage
------------------
building cup requires `make` and a c99 compliant compiler.

to build cup, run `make`.  
to use cup on a source file, run `cup input.cup`. this writes c code to _stdout_.  

license
-------

> The MIT License (MIT)
> 
> Copyright © 2024 Christian Schäl
> 
> Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
> 
> The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
> 
> THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

