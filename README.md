Served
======

![Served Logo](served-logo.png)

[![Build Status](https://travis-ci.org/bowlofstew/served.png)](https://travis-ci.org/bowlofstew/served)

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
$ cmake ../served && make
```

Or, using [bazel](https://bazel.build/):

```bash
$ git clone git@github.com:datasift/served.git
$ cd served
$ bazel build :served
$ bazel test :served-test
```

### Getting Started

The most basic example of creating a server and handling a `HTTP GET` for the path `/hello`:
```cpp
#include <served/served.hpp>

int main(int argc, char const* argv[]) {
	// Create a multiplexer for handling requests
	served::multiplexer mux;

	// GET /hello
	mux.handle("/hello")
		.get([](served::response & res, const served::request & req) {
			res << "Hello world!";
		});

	// Create the server and run with 10 handler threads.
	served::net::server server("127.0.0.1", "8080", mux);
	server.run(10);

	return (EXIT_SUCCESS);
}
```

To test the above example, you could run the following command from a terminal:
```bash
$ curl http://localhost:8080/hello -ivh
```

You can also use named path variables for REST parameters:
```cpp
mux.handle("/users/{id}")
	.get([](served::response & res, const served::request & req) {
		res << "User: " << req.params["id"];
	});
```

To test the above example, you could run the following command from a terminal:
```bash
$ curl http://localhost:8080/users/dave -ivh
```

If you need to be more specific, you can specify a pattern to use to validate
the parameter:
```cpp
mux.handle("/users/{id:\\d+}")
	.get([](served::response & res, const served::request & req) {
		res << "id: " << req.params["id"];
	});
```

To test the above example, you could run the following command from a terminal:
```bash
$ curl http://localhost:8080/users/1 -ivh
```

Method handlers can have arbitrary complexity:
```cpp
mux.handle("/users/{id:\\d+}/{property}/{value:[a-zA-Z]+")
	.get([](served::response & res, const served::request & req) {
		// handler logic
	});
```

If you want to automatically log requests, you could use a plugin (or make your
own):
```cpp
#include <served/plugins.hpp>
// ...
mux.use_after(served::plugin::access_log);
```

You can also access the other elements of the request, including headers and
components of the URI:
```cpp
mux.handle("/posts/{id:\\d+}")
	.post([](served::response & res, const served::request & req) {
		if (req.header("Content-Type") != "application/json") {
			served::response::stock_reply(400, res);
			return;
		}
		res << req.url().fragment();
	});
```

### Compile Options

Option                 | Purpose
---------------------- | -----------------------------------
SERVED_BUILD_SHARED    | Build shared library
SERVED_BUILD_STATIC    | Build static library
SERVED_BUILD_TESTS     | Build unit test suite
SERVED_BUILD_EXAMPLES  | Build bundled examples
SERVED_BUILD_DEB       | Build DEB package (note: you must also have dpkg installed)
SERVED_BUILD_RPM       | Build RPM package (note: you must also have rpmbuild installed)

## System Compatibility

OS           | Compiler      | Status
------------ | ------------- | -------------
Linux        | GCC 4.8       | Working
OSX          | Clang 3.5     | Working

## TODO

- Chunked encoding support

## Contributing

Pull requests are welcome.

## Authors

* [@bigdatadev](https://github.com/bigdatadev)
* [@Jeffail](https://github.com/Jeffail)

## Copyright

See [LICENSE.md](LICENSE.md) document
