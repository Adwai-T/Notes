# Spring Security

|Authentication | Authorization |
|---|---|
| Who are you? | What you can do? |

* Principal :  Person who has been authenticated.

* Granted Authority : Fine grain permission.

* Roles : Group of authorities. Corse grain permission.

## Configure Authentication in Spring Security

Authentication Manager : Does that authentication and has a method `authenticate()`.

We do not make our own Authentication Manager but use the builder pattern to configure manager.

AuthenticationManagerBuilder :

Our configuration class extends the `WebSecurityConfigurerAdapter` and then we overide the configer method and pass a `AuthenticationManagerBuilder` as the argument. Our configuration class also needs an annotation `@EnableWebSecurity` which will configure spring security for a web application.

Password should always be encoded and spring forces us to encode our password.

* Delegating Filter proxy

* When spring Security Authenticates the user it outputs a principal.

* Athentication can be looked as Data Transfer Object, it holds the credentials before authentication and principal after authentication.

* Providers : *Authentication Providers* is responsible for authentication. It has `authenticate()`.

An Application can have multiple Authentication Providers. To coordinate between these Spring gives us `AuthenticationManager`. `ProviderManager implements AuthenticationManager`.

`AuthenticationProviders` also have a method `supports()` that returns which type of anthentication is supported by that Provider. This method is called by `AuthenticationManager` to check if the Provider is the one it is looking for.

Every AuthenticationProvider that we use need to retrive data, and hence Spring has detached how data is retrived and delegated that responsibility to the `UserDetailsService`.

![Authentication Diagram In Spring Boot](../NotesImages/AuthenticationInSpringBoot.png)

## Authorization with JWT

