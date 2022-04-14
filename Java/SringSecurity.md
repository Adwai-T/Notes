# Spring Security

We will understand the most common problems solved by spring security.

Comprehensive guide to [Spring Security](https://docs.spring.io/spring-security/reference/index.html).

## Spring Security Model

Spring Secutity Defines a framework for security, implemented using servlet filters in the background.

There are two methods of securing a web app one by using Declarative Security or by using Programmatic Security.

* Spring Security With Serverlet Filters
  
Serverlet Filters are used to pre-preocess and postprocess web requests.

Servlet filters can reoute web requests based on security logic.

Spring provides a bulk of secrity functionality using servlet.

* Spring Security Concepts

1. Atuhentication : Check user id and password with crednetials stored in the app/db.
2. Authorization : Check to see if user has an authorized role.

* Declarative Security

Define application's security constraints in configuration with a class annotated with `@Configuration` or with a xml file configuration.

This provides separation of concerns between security and Application code.

* Programmatic Security

Spring Security provides an API for custom application coding. Thus we can extend the basic security API provided by spring to write our own security logic.

This provides greate customization for specific app requirements.
