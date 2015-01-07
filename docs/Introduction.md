#Served - An Introduction

Served is a C++ HTTP server library, designed primarily for quickly building RESTful service front ends for existing C++ projects. Served can be used to build any type of HTTP server, but any caveats you ought to familiarise yourself with before using Served shall be listed here:

##Caveat 1 - Handlers, order matters

A request is dispatched to the first matching pattern found in the order that they were defined, irrespective of all other patterns. Patterns will be considered a match if all their components are found in the request resource, therefore the pattern "**/**" will match all requests unless registered *after* any of your more specific patterns.

For example, given the following handler patterns registered in their respective order:

```
/first/handler
/second/handler
/second/handler/foo
/
```

And a request with the resource target:

```
/second/handler/foo/bar
```

The handler chosen will be the one registered with the pattern:

```
/second/handler
```

Since this is the first registered pattern that is fully matched within the request resource.

##Caveat 2 - Chunked encoding is missing

Currently, chunked encoding support is not implemented. This is on the TODO list.
