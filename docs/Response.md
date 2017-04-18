# Response Object

Every registered handler gets access to a response object; this is used to construct your response to the client. For a detailed overview of the response object please refer to the header file at ./src/served/response.hpp.

## Setting headers

The header key is case-insensitive for the purposes of identifying a single header and setting a single value; however, the key itself as written here is exactly what will be sent to the client.

For example, after calling the following:

``` cpp
res.set_header("CONTENT-TYPE", "text/plain");
res.set_header("Content-type", "application/json");
```

The second value of "**application/json**" will override the previous value of "**text/plain**", and the response will contain the following header line:

```
Content-type: application/json
```
