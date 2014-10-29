# served

![Served Logo](served-logo.png)

## Overview

Served is a C++ library for building high performance RESTful web servers.

Served builds upon [Boost.ASIO](http://www.boost.org/) to provide a simple API for developers to create HTTP services in C++.

Features:
* [x] HTTP 1.1 compatible request parser
* [x] Middleware / plug-ins
* [x] Flexible handler API
* [x] Cross-platform compatible

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

### Getting Started

The most basic example of creating a server and handling a `HTTP GET` for the path `/hello`:
```cpp
#include <served/served.hpp>
#include <iostream>
#include <unistd.h>

int main(int argc, char const* argv[]) {
	// Create a multiplexer for handling requests
	served::multiplexer mux;

	// GET /hello
	mux.handle("/hello")
		.get([](served::response & res, const served::request & req) {
			res << "Hello world!";
		});

	// Create the server and run
	served::net::server server("127.0.0.1", "8080", mux);
	server.run(10);

	return (EXIT_SUCCESS);
}
```

To test the above example, you could run the following command from a terminal:
```bash
$ curl http://localhost:8080/hello -ivh
```

### Compile Options

Option                 | Purpose
---------------------- | -----------------------------------
SERVED_BUILD_SHARED    | Build shared library
SERVED_BUILD_STATIC    | Build static library
SERVED_BUILD_TESTS     | Build unit test suite
SERVED_BUILD_EXAMPLES  | Build bundled examples

## System Compatibility

OS           | Compiler      | Status
------------ | ------------- | -------------
Linux        | GCC 4.8       | Working
OSX          | Clang 3.5     | Working

## Contributing

Pull requests are welcome.

## Authors

* [@bigdatadev](https://github.com/bigdatadev)
* [@Jeffail](https://github.com/Jeffail)

## Copyright

See [LICENSE](LICENSE) document