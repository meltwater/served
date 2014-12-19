Multiplexer Object
==================

The multiplexer object allows you to register HTTP request handlers for pattern based resources. Here is an overview of the object...

## .handle(const std::string & pattern, const std::string & summary = "")
###### Registers a new resource pattern, returns a methods_handler object for declaring handlers.

Examples of valid handle patterns can be found in Routing.md. The summary argument is optional and should contain a short summary of the endpoint resource; this is then used when generating human-readable lists of the available endoints.

The returned **methods_handler** object can then be used to register a handler for each HTTP method of interest.

### methods_handler object
###### Used to register handlers per request method.

#### .get(served::served_req_handler handler)
###### Registers a handler for any GET requests.

#### .post(served::served_req_handler handler)
###### Registers a handler for any POST requests.

#### .head(served::served_req_handler handler)
###### Registers a handler for any HEAD requests.

#### .put(served::served_req_handler handler)
###### Registers a handler for any PUT requests.

#### .del(served::served_req_handler handler)
###### Registers a handler for any DEL requests.

#### .method(const served::method method, served::served_req_handler handler)
###### Registers a handler for a specific HTTP method.

Calls to the methods_handler object can be daisy-chained.

Example:

``` cpp
mux.handle("/foo/bar")
	.get(get_handler)
	.post(post_handler)
	.del(del_handler);
```

## .use_before(served_plugin_req_handler plugin)
###### Register a plugin to be called for each request before the handler.

More info about plugins can be found in Plugins.md

## .use_after(served_plugin_req_handler plugin)
###### Register a plugin to be called for each request after the handler.

More info about plugins can be found in Plugins.md

## .get_endpoint_list()
###### Returns a full list of registered endpoints as a served_endpoint_list object.

## .get_endpoint_list_handler_YAML()
###### Returns a request handler that when called will write a full summary of registered endpoints in YAML format.

Example:

``` cpp
multiplexer mux;
mux.handle("/endpoints").get(mux.get_endpoint_list_handler_YAML());
```

## Handler order of precedence

When defining handlers for your multiplexer it's important to consider the order of precedence each handler will have for a request. In Served, when a request is received, each handler is checked for a match in the order that they were defined; the first matching handler is always the handler that is chosen.

## Overriding a pattern handler

You may, whilst defining your handlers, overwrite a previously defined pattern with a new handler. When this happens the new handler will *not* be given the same position as the old handler. Instead, the old handler is removed entirely and the new handler takes the last position in the handler stack.

For example, given the following handler definitions:

```
handle("/foo/bar").get(foo);
handle("/foo").get(foo2);
handle("/foo/bar").get(foo3);
```

Internally, this will be simplified by the multiplexer to become:

```
handle("/foo").get(foo2);
handle("/foo/bar").get(foo3);
```
