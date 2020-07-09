## URL BreakDown :

`<protocol>://<login>:<password>@<host>:<port>/<path>?<request parameters>#<anchor>`


<protocol> is a way of exchanging data with a resource. You are probably most familiar with HTTP and HTTPS protocols, but there are others;

<login> and <password> are prefixes that transmit authentication data for some protocols, if necessary;

<host> is the domain name or IP address where the site is located. Domain is the name of the site, its address in the global network;

<port> is required for connection within the specified host. The official port for HTTP connections is 80, and the alternative is 8080, but it is possible to use any other ports too. The default setting for HTTPS is 443;

<path> indicates the exact address of a particular file or page;

<request parameters> are parameters transmitted to the server. Depending on request parameters, the site may slightly change its display. For example, it is possible to sort the items of a list in a different order;

<anchor> allows you to connect to a specific part of a web page or document.

## Six REST principles

Abiding by the following six important principles guarantees that you write a RESTful service:

Client-server interaction model. By separating the user interface from the data warehouse, we improve and simplify application operation.

Stateless. Each request from a client to a server must contain all necessary information and cannot rely on any state stored on the server side. According to REST, the
service does not store the results of the previous operation. Simply put, it works according to the "Asked, answered, forgotten" concept. 

Cacheable. A request-response pair can be marked as cached and stored on the user side. It is possible to draw an analogy to web page caching: if a page was downloaded once, it can be accessed without addressing the server again.

Uniform interface. REST architecture specifies that any REST service must be understandable without its developer. 

Layered system. A client cannot just tell whether it is connected directly to the end server or an intermediary along the way. 

Code on demand [Optional]. On request, the service must give executable code in the form of an applet or script to be executed on the client's side. In practice, it is very seldom used.

