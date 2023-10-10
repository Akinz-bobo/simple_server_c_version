#ifndef HTTPRequest_h
#define HTTPRequest_h
enum HTTPMethods 
{
    GET,
    POST,
    PUT,
    PATCH,
    HEAD,
    DELETE,
    CONNECT,
    OPTIONS,
    TRACE
};


struct HTTPRequest
{
    int Method;
    char *URI;
    float HTTPVersion;
};

struct HTTPRequest http_request_contructor ( char *request_string);



#endif // HTTPRequest_h