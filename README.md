[![Copier](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/copier-org/copier/master/img/badge/badge-grayscale-inverted-border-orange.json)](https://github.com/copier-org/copier)

# mbm

## CMake

The project has been initialized with a [CMakeLists.txt](CMakeLists.txt)-based
configuration for building with CMake:

```shell
# change into the build directory
cd build/cmake

# generate the build files
cmake ../..

# build the project
make

# install the project to <repo>/build/cmake/dist
make install

# run the program to see if it works
./dist/bin/exe
```

Should output something like:

```text
-- test compile definitions
   DEBUG compile definition has been defined.

-- test wether math library was linked
   sqrt(144) = 12.000000

-- test c2x / c23 features
   0 1 2 3 4

-- test own library
   divide(2, 3) = 0
   multiply(2, 3) = 6

-- test external library
   add(2, 3) = 5
   subtract(2, 3) = -1
```

## Testing

The tests require that [Criterion](https://github.com/Snaipe/Criterion) is installed on the system, e.g. with

```shell
sudo apt install libcriterion-dev
```

Run the tests with

```shell
./dist/bin/test_mbm -j1 --verbose
```
## Code::Blocks

Use [Code::Blocks IDE](https://www.codeblocks.org/) to open [.codeblocks/project.cbp](.codeblocks/project.cbp). 

## `clang-format`

The file `.clang-format` contains an initial configuration for (automatic) formatting with [clang-format](https://clang.llvm.org/docs/ClangFormat.html). Run the formatter with e.g.:

```shell
# dry run on main.c
clang-format -Werror --dry-run main.c

# format in place all *.c and *.h files under ./src
clang-format -i `find ./src -type f -name '*.[c|h]'`
```

## Acknowledgements

_This project was generated using [Copier](https://pypi.org/project/copier)._
