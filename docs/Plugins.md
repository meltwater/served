#Plugins

Served wants you to plug in. A Served plugin is a std::function of the signature:

```
void(served::response &, served::request &)
```

which is called for every single request. Since the request object in this signature is non const you are free to write plugins that modify the request object.

Served plugins can be set to run either before each request is sent to a registered handler, or afterwards. Plugins set to run after the registered handler will be run even if the handler throws an exception. The syntax for setting plugins is as follows:

```
// Register a plugin to run before a handler
mux.use_before(plugin);

// Register a plugin to run after a handler
mux.use_after(plugin);
```

An example use case for 'use\_before' could be setting a plugin that parses the query string of a URL and sets those variables in the 'params' object of the request for easy consumption by the chosen request handler. Served actually already does this for you.

A standard use case for 'use\_after' is setting a plugin that logs the request and the response, since it is run after the chosen request handler you can print exactly what the response code and body size is going to be. Served has already got a plugin that can do this, which can be found at: **served::plugins::access\_log**.
