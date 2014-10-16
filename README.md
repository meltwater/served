# served

![Served Logo](served-logo.png)

## Overview

Served is a C++ library for building high performance HTTP web servers using [Boost ASIO](http://www.boost.org/).

Features:
* [x] HTTP 1.1 compatible request parser.
* [x] Enhanced C++11 compatible API.

## Installation

### Requirements

* [Required] - [Boost 1.56](http://www.boost.org/)
* [Optional] - [Ragel](http://www.complang.org/ragel/)

### Building

```bash
$ git clone git@github.com:datasift/served.git
$ mkdir served.build && cd served.build
$ ccmake ../served && make -j8
```

### Compile Options

Option              | Purpose
------------------- | -----------------------------------
SERVED_BUILD_SHARED | Build shared library
SERVED_BUILD_STATIC | Build static library
SERVED_BUILD_TESTS  | Build unit test suite

## System Compatibility

OS           | Compiler      | Status
------------ | ------------- | -------------
Linux        | GCC 4.8       | Working

## Contributing

Pull requests are welcome.

## Authors

* [@bigdatadev](https://github.com/bigdatadev)
* [@Jeffail](https://github.com/Jeffail)

## Copyright

See [LICENSE](LICENSE) document