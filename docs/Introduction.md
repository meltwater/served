#Served - An Introduction

Served is a C++ HTTP server library, designed primarily for quickly building RESTful service front ends for existing C++ projects. Little consideration has been made for use cases such as general file serving, in favour of focussing on explicit resource specification. Therefore, before using Served there are some caveats you ought to familiarise yourself with.

##Caveat 1 - Handler routing

Usage of any typical HTTP server begins with defining your resources and respective handlers. This usually involves listing endpoint patterns with method handlers, and the expected behaviour is that the handler chosen for any request is simply the "most specific" pattern that matches.

In Served, this is not the case. Instead, a request is only dispatched to a handler with an explicit pattern that exactly matches. The request is also dispatched to the first matching pattern found in the order that they were defined, irrespective of all other patterns.

With variable and regular expression pattern parameters you can still easily define patterns that exactly match a range of request paths. For example, the pattern:

/base/{var1}/{var2:[0-9]+}/{file}

Will exactly match the following requests:

/base/images/67/test.jpg
/base/html/456/index.html
/base/css/23478/style.css

And if you did not care about catching path segments as variables you can simplify the previous pattern to:

/base/{}/{:[0-9]+}/{}

Where '{}' essentially becomes a wildcard.

Working under these constraints makes the multiplexer implementation simpler. However, this approach would not be suitable for a file server unless the directory structure was simple and never changing, which is unlikely.
