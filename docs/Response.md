#Response Object

Every registered handler gets access to a response object, this is used to construct your response to the client. Here is an overview of the object...

## .set_header(const std::string & header, const std::string & value)
###### Sets a header to a value, overriding any previous value.

The header key is case insensitive here for the purposes of identifying a single header and setting a single value, however, the key itself as written here is exactly what will be sent to the client.

For example, after calling the following:

``` cpp
res.set_header("CONTENT-TYPE", "text/plain");
res.set_header("Content-type", "application/json");
```

The second value of "**application/json**" will override the previous value of "**text/plain**", and the response will contain the following header line:

```
Content-type: application/json
```

## .set_status(int status_code)
###### Sets the status code of the response

By default this value will be **200** (**OK**).

## .set_body(const std::string & body)
###### Sets the response body to the provided content.

This will override any previous content set to the response body.

Example:

``` cpp
res.set_body("hello world.\nyou got served.");
```

## operator <<
###### Appends data to the response body.

Piped data will be appended to the response body.

Example:

``` cpp
res << "hello world." << "\n";
res << "you got served.";
```

## served::response::stock_reply(int status_code, response & res)
###### Configures a response object to be a generic response for a particular status code

This is a short hand way of setting the responses status code and body for a particular response.

Example:

``` cpp
served::response::stock_reply(served::status_4XX::BAD_REQUEST, res);
```
