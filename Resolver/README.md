
# Resolver (Task #3)
## Templates and alghorithm of resolving dependencies
[Original task](https://avoronkov.gitlab.io/oop/2018.cpp/task3/)
## Build
```
$ cd build
$ cmake ..
$ make
```

## To use Resolver you should have libs.txt and targets.txt or you can write two text file names in particular order
## To show that Resolver works correctly with all type of versions I added versions for std::string and double in CMakeLists.txt but you can test any other type that can be converted from std::string and supports comparisson operators
```
$ ./resolver
$ ./strResolver libsInString.txt targetsInString.txt
$ ./doubleResolver libsInDouble.txt targetsInDouble.txt
```
## Test

```
$ ./unittest
===============================================================================
All tests passed (253 assertations in 41 test cases)
```

(Catch C++ Test Framework can be found [here](https://github.com/philsquared/Catch))
