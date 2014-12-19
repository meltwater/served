#Request Routing

Served supports a range of useful syntaxes to assist in defining RESTful resource patterns. Once compiled by the Served multiplexer, a pattern can be considered an array of segments, where each segment is constructed from the pattern once split by the path separator "**/**" character.

Here is a breakdown of the various segment types.

###Static

This is the simplest type of segment. It is compiled from a static string, and matches only that exact string. The following pattern would compile into three static segments:

```
/first/second/third
```

This would only ever match a request path starting with: "**/first/second/third**"

###Variable

A variable segment is a RESTful resource parameter which can exist in any section of your pattern. It is defined between curly braces and can have an optional parameter name that will cause the variable to be parsed and captured in request.params under that name.

The syntax is as follows:

```
/{variable_name}
```

The following pattern would compile into two static segments followed by a variable segment at the end:

```
/first/second/{variable1}
```

This would match all of the following request paths:

```
/first/second/hello
/first/second/50
/first/second/file.jpg
```

Here, **variable1** would be placed in **req.params** with value, respectively: **hello**, **50** and **file.jpg**.

The variable name can be left blank and causes the variable segment essentially to act as a wildcard. The following pattern would match all of the same paths as before:

```
/first/second/{}
```

###Regex

A regex segment is a RESTful resource parameter that must satisfy a regular expression before being considered a match. It is defined similarly to a variable segment between two curly braces, but also requests a colon character to separate the variable name from the regular expression.

The syntax is as follows:

```
/{variable_name:regular_expression}
```

The following pattern would compile into two static segments followed by a regex segment at the end:

```
/first/second/{variable1:[0-9]+}
```

In this particular case the regular expression only matches numbers. Therefore, this pattern would match all of the following request paths:

```
/first/second/50
/first/second/445
/first/second/80
```

but none of the following:

```
/first/second/hello
/first/second/file.jpg
```

The rules of capturing variables is the same here as for variable segments.

###Empty

An empty segment is compiled from a trailing path separator. This is a special case where the segment will match any value or no value.

The following pattern would compile into two static segments followed by an empty segment:

```
/first/second/
```

This pattern would match any of the following request resources:

```
/first/second/
/first/second/foo
/first/second/foo.bar
/first/second/foo/bar
/first/second/foo/bar/baz
```

###Empty Regex

A regex segment where the regular expression itself is empty may be used to match complete or terminated paths (rather than path prefixes).

The following pattern would compile into two static segments followed by an empty regex segment:

```
/first/second/{and_nothing_else:}
```

In this particular case the regular expression only matches the empty string (or empty segment):

```
/first/second/
```

but none of the following:

```
/first/second/50
/first/second/hello
/first/second/hello/
/first/second/hello/dolly
/first/second/file.jpg
```
