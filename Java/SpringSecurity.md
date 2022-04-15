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

## Spring Security Concept

### Authentication

It is proving to the system who the user is. This can be done providing something unique about the user, like an id, something that only that user can provide and no one else.

So for example we have a gmail account, so we tell gmail that this is my gmail id, but we also have to prove that this id belongs to us, we do that by providing a password.

The above type of authentication is called as **Knoweledge Based Authentication**. The proof in the case can be any unique identification like a password, pin, or an answer to a secret/personal question.

The biggest disadvantage of Knoweledge based authentication is that if our unique secret is stolen any person can impersonate us.

So there are other types of authentication like **Possession Based Authentication**. These include things like Phone/Text messages containing otp, of keycards and badges, or Access token device.

Some Apps will make use of both, which is called as **Multifactor Authentication**.

### Authorization

This is the security provider examining if we have access to do what we are trying to do.

For example access or update database entries, view certain pages, etc. This is mostly resolved in a binary yes or no operation, where either the user has permission to do what they want to do or they don't.

This process of making decision of what a user is allowed or not allowed to do is called as Authorization.

For Authorization we first need Authenication as this will tell who the user is and what are the privilages that the user has.

### Prinicipal

It is user that has been Authenticated or also can be said a user that is currently logged-in.

Once logged in the App remembers the user as principal, so that the user does not have to login fo every request.

### Granted Authority

The list of actions or privilages that are granted to a Authorized Principal is the Granted Authority.

For example a Normal user can view pages, that is his Granted Authority, and an admin can view pages as well as edit them, that will be his Granted Authority.

So we can say that Granted Authority are fine grain permission that a Principal has. Any Authorities not specified granted explicity are automatically not permissed as the default permission is denied.

### Role

Role represents a group of Granted Authorities.

Roles Are more coarse grain persmission then Granted Authority is.

In many cases the concept of Authorities and Role are used interchangably.

### Filters

As we know Spring and Spring Boot application are Servlet Application and filters are a very basic concept of Servlets.

Filters basically intercept every request that goes to different Servlets. Spring Secuity is using exactly this concept. It is itself a filter layer that accepts or denies requests.

## Getting Started

When we add Spring Security to the class path of the applicaiton Spring Security exibits some default behavious.

* Adds manadatory authentication for all request Urls.
* Adds Login form.
* Handles Login errors.
* Creates a user and sets a default password that is printed to console when app runs. The default user-name is user.

When are using Spring Secuity with spring boot we can add a user and passowrd to the application properties file which will be loaded automaically.

```properties
spring.security.user.name=user
spring.sercuity.user.password=password
```

## Configuring Spring Security

### AuthenticationManager

It manages the authentication in a Spring Security Application.

It has a method `authenticate()` that either authenticates or throws an exception.

We don't directly work with the `AuthenticationManager` but use a `AuthenticationManagerBuilder` to create the `AuthenticationManager` to configure what it should do.

To get a hold of the `AuthenticationManagerBuiler` we extends the class `WebSecurityConfigurerAdapter` that has a `configure(AuthenticationManagerBuilder)` that Spring Security calls to configure Security.

Once we extend the class Spring will call our configure method and pass the AuthentcaitonManagerBuilder that we can use to configure the AuthenticationManager.

`@EnableWebSecurity` Tells Spring Security that this is a Web Security configuration.

Spring Security expects that our password is not stored as plain text and hence it will enforce password encoding.

So we have to provide Spring Security with a bean of type `PasswordEncoder` that defines an encoder for our passwords.

Spring Security will be looking for this bean and automatically use it to encode passwords, so we just have to define this bean.

### Configure InMemory Authentication

```java
@EnableWebSecurity
public class SecurityConfiguration extends WebSecurityConfigurerAdapter {
  @Overrider
  protected void configure(AuthenticationManagerBuilder auth) throws Exception {
    //super.configure(auth); -- we dont want to call the default
    auth.inMemoryAuthentication()
      .withUser("user")
      .password("password")
      .roles("USER")
      .and() //And just returns the same object as we use the builder pattern here
      .withUser("user2")
      .password("password2")
      .roles("ADMIN");
  }

  @Bean
  public PasswordEncoder getPasswordEncoder() {
    return NoOpPasswordEncoder.getInstance();
  }
  //The above password encoder the we returned does not encode the password at all and we still have plain password String.
}
```

### Setup Authorization

Let in the following example we have three paths `/` that is accessible by all users, `/user` That is only accessible by authenticated users and `/admin` accessible by authenticated user with ADMIN roles.

```java
//---Same SecurityConfiguration class that we created above, we just add the following code
//WE have both the above configure method and this at the same time.
@Override
protected void configure(HttpSecurity http) throws Exception{
  http.authorizeRequests()
    .antMatcher("/admin").hasRole("ADMIN")
    .antMatcher("/user").hasAnyRole("USER", "ADMIN") //If we specify only user then admin will not be able to access /user
    .antMatcher("/").permitAll()
    .and().formLogin();
    //Use FormLogin to authenticate, default behaviour of Spring Security.
}
```

`.antMatchers("/", "static/css", "static/js").permitAll` : will permit access to the static resources and the home page as we might want to give permission to all to visit the home page and decorate it with css and javascript.

`.antMatchers("/**")` : will match all paths.

> Note : We go from the most restricted to the least restricted url in Spring Security HttpSecurity Configuration using antMatchers.

If we put the least restrictive matchers at the top it is going to match all the requests and will never go to the more restrictive stuff defined.

## Working Of Spring Secuity Authentication

### Delegating Filter Proxy

Spring Security use servlet filters to intercept all requests.

These filters have the oportunity of manapulating all request and even stop certain request from reaching the servlet.

There is usually a one to one mapping between a url and one servlet method.

But filter can be applied to a wide range of urls.

In the case of Web application Spring Security creates these filter by mapping the requests to its own filters called as Delegating filter proxy.

Delegating Filter Proxy does not handle the filtering itself rather it delegates the specific task to specific filter created by Spring Security. One of these filters is for authentication, other for authorization. There are many such filter that are set by spring security.

### Authentication Process

For Authentication Spring Security takes credentials as input and  when done, the authentication return a `Principal`.

When Spring Secuirty Perfroms authentication It keeps track of both the input credentials and returned Principal in an Object called `Authentication` which is an internal Spring Security Interface.

We can think of Authentication as a DataTransfer object for authentication.

### Providers

An AuthenticationProvider is responsible for doing the actual Authentcation.

It has a method called `authenticate()`.

> Authentication Object containing Credentials -> AuthenticationProvider.authenticate() -> Authentication Object containing Principal.

A given App can have multiple AuthenticationProviders.

Thus each Authentication Provider needs to specify what kind of authentication it can support. This is returned by the method `supports()` of the AuthenticationProvider.

Given the credentials the provider needs to retrive the user from an identity store and the verify if user is valid. This is same for any type of provider.

As the part of retrieving data about user is common for all types of providers, Spring Security has extracted this part and delegated it to a `UserDetailsService`. It has a method called as `loadUserByUserName()`.

The UserDetailsService returns a `UserDetails` Object needed by the provider for authentication, once authenticated, mostly the same `UserDetails` object is returned as the Principal in the Authentication object.

### ProviderManager

Say we have authentication with Login form, also with google also with github. All of them will be AuthenticationProvider for our applicaiton.

We can manage all these AuthenticationProviders with a ProviderManager.

In Spring Security case the `AuthenticationManager` helps us with all the AuthenticationProvider.

AuthenticationManager has its own `authenticate()` method that is called to check for appropriate AuthenticationProvider.

The AuthenticationManager check which AuthenticationProvider can authenticate a request by checking the supported authentication type and deligates the authentication process to the provider by calling its `authenticate()` method.

### After Authentication

After a successful authentication the AuthenticationManager returns the Authentication with the principal to the filters and the Authentication is stored in the ThreadLocal.

One of the other Delegating filter creates and manages a session for the Authenticaion with the Principal and thus we don't have to authenticate with every subsequent request.

This filter will be responsible for the processing subsequest request and adding the Authenticate to ThreadLocal so that it is available for the framework.

Underlying all authentication work the same which ever authenticaion type we use.

## JDBC Authentication Configuration

### H2 Database

In the first example we will use an inmemory H2 database and let spring create a default shema for our database for the user. We will also populate the database with some user for testing.

```java
//As we have provided Spring Boot with a h2 dependency, it will automatically create a DataSource bean for H2 db and autowire it here.
@Autowired
private DataSource dataSource

@Overrider
protected void configurer(AuthenticationManagerBuilder auth) throws Exception{
  auth.jdbcAuthentication().dataSource(dataSource)
      .withDefaultSchema()
      .withUser(
        User.withuserName("user").password("pass").roles("USER")
      )
      .withUser(
        User.withuserName("admin").password("pass").roles("ADMIN")
      );
}
```

The following configuration shows the default be behaviour of Spring Security when we use the default shema and use `withDefaultSchema()` to get the users, password and role.

This is run automatically and we do not need to specify this code if we are using the default schema. We can however change this code if we are using a custom schema.

```java
auth.jdbcAuthentication()
  .dataSource(dataSource)
  .userByUserNameQuery("select username,password,enable from users where username=?")
  .authoritiesByUsernameQuery("select username,authority from authorities where username=?");
```

### SQL Database

The Datasource is configured and passed to the AuthenticationManagerBuilder.

We configure the Datasource separatly and Autowire it, this gives us flexibility of changing database with minimum changes to the AuthenticationManager Configuration.

The simplest way to configure a Datasource in a Spring Boot application is to add the details for connecting to our database in the application.properties file as Spring Boot while loading the file will also automatically configure the datasource for us and inject it into the Spring Security Configuration class.

But if we are using Spring and Spring Security without Spring Boot we would have to configure the Datasoure manually.

We have configured the Datasource in the Spring Part.

```properties
spring.datasource.url=
spring.datsource.username=
spring.datasource.password=
```

## JPA Authentication Configuration

