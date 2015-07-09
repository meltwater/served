#Plugins

Served wants you to plug in. A Served plugin is a std::function of the signature:

```cpp
void(served::response &, served::request &)
```

which is called for every single request. Since the request object in this signature is non const you are free to write plugins that modify the request object.

Served plugins can be set to run either before each request is sent to a registered handler, or afterwards. Plugins set to run after the registered handler will be run even if the handler throws an exception. The syntax for setting plugins is as follows:

```cpp
// Register a plugin to run before a handler
mux.use_before(plugin);

// Register a plugin to run after a handler
mux.use_after(plugin);
```

An example use case for 'use\_before' could be setting a plugin that parses the query string of a URL and sets those variables in the 'params' object of the request for easy consumption by the chosen request handler. Served actually already does this for you.

A standard use case for 'use\_after' is setting a plugin that logs the request and the response, since it is run after the chosen request handler you can print exactly what the response code and body size is going to be. Served has already got a plugin that can do this, which can be found at: **served::plugins::access\_log**.

## Handler wrapping plugins

Conventionally, if you were interested in wrapping a request handler with another function, you would use this syntax:

```cpp
mux.handle("/example").get(plugin(get_handler));
```

This becomes tedious quite quickly if you have a plugin that you want to apply for every handler, more so if you have multiple plugins. Served has a syntax for declaring wrapper functions that should be applied to every handler:

```cpp
mux.use_wrapped([](served::response & res, served::request & req, std::function<void()> next) {
	// Do some stuff here
	next();
	// More stuff here to further modify the response before it is dispatched
});
```
