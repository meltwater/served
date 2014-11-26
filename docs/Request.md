#Request Object

Every registered handler gets access to a const request object, this is for obtaining any relevant information about the request and the client. Here is an overview of the object...

## .method()
###### Returns the HTTP method of the request

The result is of the type **served::method**.

## .url()
###### Returns a URL object of the request

The result is of the type **served::uri**.

#### url().URI()
###### Returns the path and query section of the url as a string

E.g. **"/foo/bar?baz=5"** for **"/foor/bar?baz=5#test"**

#### url().path()
###### Returns just the path section of the url as a string

E.g. **"/foo/bar"** for **"/foor/bar?baz=5#test"**

#### url().query()
###### Returns just the query section of the url as a string

E.g. **"baz=5"** for **"/foor/bar?baz=5#test"**

#### url().fragment()
###### Returns the fragment section of the url as a string

E.g. **"test"** for **"/foor/bar?baz=5#test"**

## .HTTP_version()
###### Returns the HTTP version string of the request

E.g. **"HTTP/1.1"**

## .header(std::string const& key)
###### Returns the value of the header "key", or an empty string if it doesn't exist

The argument **key** is case insensitive.

## .body()
###### Returns the body of the request as a string.
