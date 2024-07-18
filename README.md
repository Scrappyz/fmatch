# Fmatch
A lightweight header-only filepath globbing library in C++

## Installation
`Fmatch` is header only. Include the [header file](include/fmatch.hpp) into your project to use.

## Usage
### Matching
Use the `fmatch::match` function to match a string with a given pattern.
### Wildcard Characters
- `*`: Matches any number of characters, including none.
- `?`: Matches any one character.
- `**`: Matches all subdirectories.

### Examples
- `hello/*` matches `hello/world`, `hello/neighbour` but not `hello/world/neighbour`
- `hello/**` matches `hello/world`, `hello/neighbour` and `hello/world/neighbour`
- `h*o/w*d` matches `hello/world`
- `hell**bour` matches `hello/world`, `hello/neighbour` and `hello/world/neighbour`
- `hell*bour` matches none of `hello/world`, `hello/neighbour`, `hello/world/neighbour`
- `hello/*.*` matches `hello/test.txt`, `hello/main.cpp`, `hello/data.dat`
- `hello/world.???` matches `hello/world.txt`, `hello/world.dat`