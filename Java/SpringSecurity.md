# Spring Security

We will understand the most common problems solved by spring security.

Comprehensive guide to [Spring Security](https://docs.spring.io/spring-security/reference/index.html).

## Spring Security Model

Spring Secutity Defines a framework for security, implemented using servlet filters in the background.

There are two methods of securing a web app one by using Declarative Security or by using Programmatic Security.

- Spring Security With Serverlet Filters

Serverlet Filters are used to pre-preocess and postprocess web requests.

Servlet filters can reoute web requests based on security logic.

Spring provides a bulk of secrity functionality using servlet.

- Spring Security Concepts

1. Atuhentication : Check user id and password with crednetials stored in the app/db.
2. Authorization : Check to see if user has an authorized role.

- Declarative Security

Define application's security constraints in configuration with a class annotated with `@Configuration` or with a xml file configuration.

This provides separation of concerns between security and Application code.

- Programmatic Security

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

- Adds manadatory authentication for all request Urls.
- Adds Login form.
- Handles Login errors.
- Creates a user and sets a default password that is printed to console when app runs. The default user-name is user.

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

For Authentication Spring Security takes credentials as input and when done, the authentication return a `Principal`.

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

Spring Security does not provide a out of the box implementation for JPA as it did for for JDBC.

So we provide the `AuthenticationProvider` with `UserDetails` by implementing a `UserDetailsService` ourself. The UserDetailsService returns a `User` Object that the AuthenticationProvider will authenticate. We have seen how this works in the working section.

So our UserDetailsService implementation will use our JPA service to communicate with the database to get the user details by using the username provided by AuthenticationProvider.

Once we have userdetails we create the UserDetails object from it and return it to the AuthenticationProvider.

> Note : The UserDetailsService can be implemented needs to return the UserDetails Object, how it finds and creates the object is completely up to us. In the case we use JPA but we can find and get details from Any Source.
> Spring Security will call the `loadUserByUsername(String s)` method to get the UserDetails, so we override it an code our implementation in it.

```java
@Autowired
private UserDetailsService userDetailsService;

@Override
protected void configure(AuthenticationManagerBuilder auth) throws Exception {
  auth.userDetailsService(userDetailsService)
}
```

### General Implementation for any Datasource

```java
// --- This is a General Implemetation That we can use for any DataSource

@Service
public class MyUserDetailsService implements UserDetailsService {
  @Override
  public UserDetails loadUserByUsername(String s) throws UsernameNotFoundException{
    return new MyUserDetails(s);
  }
}

public class MyUserDetails implements UserDetails{
  //We implement all the method of the interface as needed.

  //-- creating A Role with GrantedAuthority
  @Override
  public Collection<? extends GrantedAuthority> getAuthorities() {
    return Arrays.asList(new SimpleGrantedAuthority("ROLE_USER"));
  }
}
```

### JPA specific Implementation

For the Database we have a sql database with instance name springsecurity, having a table named users with column id, username, password, role, and active.

```java
//--- Create JPA Entity javax.persistence.Entity
@Entity
@Table(name="User")
public class User{
  @Id
  @GeneratedValue(strategy=GenerationType.AUTO)
  private String userName;
  private String password;
  private String active;
  private String roles;

  //Constructors, Getters and Setters
}

//--- Create Repository
public interface UserRepository extends JpaRepository<User, Integer>{
  //We just provide the interface and the methods are automatically implemeted by the framework.
  Optional<User> findByUserName(String userName);
}

@Service
public class MyUserDetailsService implements UserDetailsService{
  @Autowired
  private UserRepository repository;

  @Overrider
  public UserDetails loadUserByUsername(String userName) throws UsernameNotFoundException {
    Optional<User> user = repository.findUserByUserName(userName);

    user.orElseThrow(()-> new UsernameNotFoundException("Not found: " + userName));

    return user.map(MyUserDetails::new).get();
  }
}

public class MyUserDetails implements UserDetails {
  private String userName;
  private String password;
  private boolean active;
  private List<GrantedAuthority> authorities;
  public MyUserDetails(User user){
    this.userName = user.getUserName();
    this.password = user.getPassword();
    this.active = user.isActive();
    //Int the db we have ROLES string separated by ,
    this.authorities = Arrays.stream(user.getRoles().split(","))
      .map(SimpleGrantedAuthority::new)
      .collect(Collector.toList());
  }
  //The we use the above values to override the methods in the UserDetails interface.
}

//--- Finally we have to also enable JpaRepostories
@SpringBootApplication
@EnableJpaRepositories(basePackageClasses=UserRepository.class)
public class SpringSecurityJpaApplication {
  //... main
}
```

We also need to configure our Datasource. If we are using SpringBoot we can add the configure the datasource in the application.properties file and spring will auto configure the database for us.

```properties
spring.datasource.url=jdbc:mysql://localhost:3305/springsecurity
spring.datsource.username=root
spring.datasource.password=password
# Tells hibernate to now wipe the database at start but just update and use the same.
spring.jpa.hibernate.ddl-auto=update
spring.jpa.properites.hibernate.dialect=org.hiberante.dialect.MySQL5Dialect
```

## Authentication With LDAP

LDAP is Lightweight Directory Access Protocol.

It is protocol for accessing and maintaining distributed directory information services over an Internet Protocol network.

It is often used to store organizational information, often with a hierarchical structure.

We need some dependencies that will help us use ldap with spring.

- com.unboundedid - unboundedid-ldapsdk : Opensource in memory implementation of ldap used for testing.
- org.springframework.ldap - spring-ldap-core : ldap interaction with spring.
- org.springframework.security - spring-security-ldap : Help spring security with ldap.

The full code for the [Authentication with LDAP](https://spring.io/guides/gs/authenticating-ldap/).

```java
@Override
public void configure(AuthenticationManagerBuilder auth) throws Exception {
  auth
    .ldapAuthentication()
      .userDnPatterns("uid={0},ou=people")
      .groupSearchBase("ou=groups")
      .contextSource()
        .url("ldap://localhost:8389/dc=springframework,dc=org")
        .and()
      .passwordCompare()
        .passwordEncoder(new BCryptPasswordEncoder())
        .passwordAttribute("userPassword");
}
```

## JWT

JWT is mostly used for Authorization. It can be used in place of Session tokens.

HTTP is a stateless protocol, hence to maintain a session we need Session tokens.

### Understanding Session

When we authenticate the server saves the Authenticated user in session store on the server and returns a reference token to this session back to the user. This is the session token.

This reference token is send back every time with the requests that a authenticated user makes as cookies.

The request containing the session token will be used by server to check authorization and thus there is not need to Authenticate again for the duration of session.

The session store stores all the authenticated user with live sessions and use the session token reference to check Authorization.

### Problems with Session

Sessions assume that the whole web app is a monolit and runs on the same server.

But Modern web apps are often split into several instance with a load balancer. This means that the subsequent request might not be send to the same server that initailly Authenticated the user and saved session information and returned session token.

To solve this there are two techinque that are employed.

- Sicky Sessions : The Load balancer will remember which client is handled by which server initailly and the route all subsequent request to the same server. But this has the obvious disadvantage that increases the work done by Load Balancer.

- Shared Session Store : Shared Session store like redish can be used between all the web app instances to store the session. This has the disadvantage that it creates a single point of failure, if session store goes down, all session also go down.

### JWT vs Session Tokens

Session Tokens are Reference token as they are a reference to the Authenticated user stored in the session store on the server.

JWT are Value Tokens that is they themselves contain all the information about the Authorization.

As JWT contain all the information about the authorization, the server does not need to maintain any store of authenticated users.

This makes the server stateless. The Application completely relies on the Client to maintain session.

Stateful services have an important advantage over stateless service, they can react differently to the same input based on the history of the session.

### Structure Of JWT

JWT consist of three Parts `Header.Payload.Signature`.

The Header contains details about encryption of the signature, the Payload containes authorization details about the Authenticated user and the secret key is a key that server calculates from a secret that is stored on the server and the payload.

The Header and Payload are encoded with Base64 encoder and are visible directly as JSON when decoded with Base64 decoder.

When a JWT is send to server for Authorization the server uses the payload and a secret key to calculate the Signature again and then matches them to check the validity of the Signature.

Thus any changes to the payload will invalidate the signature.

As playload is not encrypted, sensitive information about Authenticated user like password, birthday, etc must not be stored in it.

### Drawbacks of JWT

As the server does not hold any state regarding a authenticated user if the JWT is stolen the user can be impersonated for the time the JWT is valid.

There is no way invalidate the key for the server as well by the user. The only way that a key can be invalidate is putting it into a blacklist. That is the server will have to maintain and check this blacklist for stolen key and block the request.

In the case of session keys the server has control over the session and the key can be invalidated any time. Also session keys become invalid once that session ends.

A Common way of using JWT authorization is through the process of using **Oauth**. Oauth has ways of protecting from JWT keys from being stolen.

### JWT Authorization With Spring Security

We Will use the [auth0/java-jwt](https://github.com/auth0/java-jwt) to create and verify jwts, but this can be achieved with any library of your preference.

```xml
<dependency>
    <groupId>com.auth0</groupId>
    <artifactId>java-jwt</artifactId>
    <version>3.19.1</version>
</dependency>
```

```java
//---Implementation of below classes will depend on the source of users we use, that is the database.
//It is not specific to JWT.
//-UserRepository is the interface implmented automatically by Spring to retrive user from Database.
//-User class that Models user from our database.
//-SimpleUserDetailsService implements UserDetailsService
//-SimpleUserDetials implements UserDetails

//--- To provide and configure UserDetails for Spring Security to use please look at the sections.

//---Models and other Contoller methods
//-AuthRequest [username, password] and AuthResponse [username, jwt] are models
//-ErrorResponse [code, message] is model for general error response.

//---First we create a utility class that will help us create and verify JWTs
@Service
public class JwtService {
  //Externalize these variables by using properties file as we don't want them to be visible when we push code to remote repositories like github. It also makes it easier to manage them.
  private String provider="Adwait";
  private String secret="SecretForAlgorithm";

  private Algorithm algorithm;

  public String generate(User user) {
    if(algorithm == null) algorithm = Algorithm.HMAC256(secret);
    // We can add any number of custom claims to the map
    Map<String, Object> payload = new HashMap<>();

    String token = JWT.create()
            .withIssuer(provider)
            .withIssuedAt(new Date())
            .withExpiresAt(new Date(System.currentTimeMillis() + 36000000))//10hrs
            .withSubject(user.getUsername())
            .withAudience(user.getAuthority())
            .withPayload(payload)
            .sign(algorithm);
    return token;
  }

  public DecodedJWT verify(String jwt) throws JWTVerificationException {
    if(algorithm == null) algorithm = Algorithm.HMAC256(secret);

    JWTVerifier verifier = JWT.require(algorithm).withIssuer(provider).build();
    DecodedJWT decodedJWT = verifier.verify(jwt);
    return decodedJWT;
  }
}

//--- We then create a auth method in controller to handle creating and sending the jwt
@Controller
@RequestMapping(value = "auth")
public class AuthenticationController {

  @Autowired
  private AuthenticationManager authenticationManager;
  @Autowired
  private JwtService jwtService;
  @Autowired
  private SimpleUserDetailsService userDetailsService;

  @PostMapping("")
  public ResponseEntity<AuthResponse> auth(
          @RequestBody AuthRequest requestBody)
          throws BadCredentialsException {

    //If Authentication fails throws BadCredentialsException which will be handled below.
    authenticationManager.authenticate(
            new UsernamePasswordAuthenticationToken(
                    requestBody.getUsername(), requestBody.getPassword()
            )
    );

    String jwt = jwtService.generate(userDetailsService.getUser());

    return ResponseEntity
              .status(HttpStatus.OK)
              .body(new AuthResponse(requestBody.getUsername(), jwt));
  }

  @ExceptionHandler(BadCredentialsException.class)
  public ResponseEntity<ErrorResponse> badCredentialsExceptionHandler() {
      return ResponseEntity
              .status(HttpStatus.NOT_FOUND)
              .body(new ErrorResponse(404, "Username or Password incorrect."));
  }
}

//--- We also need a filter that will process each request and check for authorization.

//OncePerRequestFilter does exactly that it runs once for every request that the server recieves.
@Component
public class JwtFilter extends OncePerRequestFilter {

  @Autowired
  public SimpleUserDetailsService userService;
  @Autowired
  public JwtService jwtService;
  @Override
  protected void doFilterInternal(
          HttpServletRequest request,
          HttpServletResponse response,
          FilterChain filterChain)
          throws ServletException, IOException {

    if (request.getHeader("Authorization") != null) {
      try {
        //If jwt verification fails it throws JWTVerificationException and no user is set in the SecurityContext.
        DecodedJWT jwt = jwtService.verify(request.getHeader("Authorization"));

        //-- We check if there is already a authenticated user in the context.
        //If there is none we will do what Spring security would have done automatically for a authenticated user.
        //We will set the authenticated user in the SpringSecrity context so that Spring can check its authorization.
        if (SecurityContextHolder.getContext().getAuthentication() == null) {
          UserDetails userDetails = userService.loadUserByUsername(jwt.getSubject());
          UsernamePasswordAuthenticationToken authToken =
                  new UsernamePasswordAuthenticationToken(
                          userDetails, null, userDetails.getAuthorities());
          authToken.setDetails(new WebAuthenticationDetailsSource().buildDetails(request));

          SecurityContextHolder.getContext().setAuthentication(authToken);
        }
      } catch (JWTVerificationException exp) {
        System.out.println("JWT Could not be verified while setting context in filter.");
      }
    }
    //We will again hand over the filter chain back to Spring.
    filterChain.doFilter(request, response);
  }
}

//--- Finally We add the filter to the Security Configuration
//--- We also tell Spring Security to not create and manage sessions
//---
@EnableWebSecurity
public class SecurityConfiguration extends WebSecurityConfigurerAdapter {
  @Autowired
  private JwtFilter jwtFilter;
  @Autowired
  private SimpleUserDetailsService simpleUserDetailsService;

  //The following configure method is an example of a log thing that can be configured in the HttpSecurity.
  //We add the jwt filter that we created here. It is to be run before UsernamePasswordAuthenticationFilter.
  //This lets us manually set the Authenticated user in Spring Secruity Context.
  @Override
  protected void configure(HttpSecurity http) throws Exception {
      http.csrf().disable()
            .authorizeRequests()
            .antMatchers("/auth").permitAll()
            .antMatchers("/admin").hasAnyAuthority("ADMIN")
            .antMatchers("/member").hasAnyAuthority("ADMIN", "MEMBER")
            .antMatchers("/user").hasAnyAuthority("ADMIN", "MEMBER", "USER")
            .anyRequest().authenticated()
            .and()
            .sessionManagement().sessionCreationPolicy(SessionCreationPolicy.STATELESS)
            .and()
            .addFilterBefore(jwtFilter, UsernamePasswordAuthenticationFilter.class);
  }

  @Override
  protected void configure(AuthenticationManagerBuilder auth) throws Exception {
      auth.userDetailsService(simpleUserDetailsService);
  }

  //We make the AuthenticationManager from the above configure method available for use.
  @Override
  @Bean
  public AuthenticationManager authenticationManagerBean() throws Exception {
      return super.authenticationManagerBean();
  }
  //We create a bean that will be used for encrypting password.
  //NoOpPasswordEncoder will not encrypt the password and keep it as plain text.
  //Not to be used in production
  @Bean
  public PasswordEncoder getPasswordEncoder() {
      return NoOpPasswordEncoder.getInstance();
  }
}
```

## OAuth

OAuth was created for authorization between services. This is called as Access Delegation.

The current Version is `OAuth 2.0`.

The OAuth Flow is the steps taken by OAuth for authorization.

### Terminologies

Lets say we have a service that want to use a file stored by our user on his google drive.

So we want our service to access another service that is googles drive.

#### Resource

Also sometimes refered to as Portected Resource. This is the thing that is sought by our service from another service. This resource is protected by the other service

In the above example the file on google drive of our user is the Resource and is protected by google drive so only the user has access to it.

#### Resource Owner

The Owner of the protected resource that can give access to the resource is the Resource Owner.

In the case of the example the user that owns the google drive will be able to control access to the files on the drive and hence he is the Resource Owner.

#### Resource Server

The server that holds the protected resource.

In the case of example the google drive is the resource server.

The Resource server has the responsibilty for security, this is deligated by the resource server to the Authorization server.

In the case of example above google is the Authorization service that google drive uses.

#### Client

The Application making protected resource request on behalf of the resource owner with its authorization.

In the case our service that want to access the file will be the client.

#### Authorization Server

The server issuing access token to the client.
