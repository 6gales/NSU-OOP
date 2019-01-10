# Phrases
## First task introducing C++ and unittests
[Original task](https://avoronkov.gitlab.io/oop/2018.cpp/task1/)

## Build

```
$ cd build
$ cmake ..
$ make
```

## Run
## You can add different parametres(-n "number" || -m "number") before filename to specify length of phrase and repetition
```
$ ./phrases -
Don't stop me now!
Don't stop me now!

Don't stop (2)
stop me (2)
me now! (2)
```

## Test

```
$ ./unittest
===============================================================================
All tests passed (41 assertion in 10 test case)
```

(Catch C++ Test Framework can be found [here](https://github.com/philsquared/Catch))
