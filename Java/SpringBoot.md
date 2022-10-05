# Spring Boot

Spring Boot takes an opinionated approach to developing application with the Spring framework. It provides starters that can be used to get us started and productive with very little to no setup.

Spring Boot Auto configures our Spring Application based on the dependencies that we have added to our project.

The entry point into a Spring Boot application is through a class annotated with `@SpringBootApplication`.

`@SpringBootApplication` is a combination of `@EnableAutoConfiguration`, `@ComponentScan` and `@SpringBootConfiguration`.

- `@EnableAutoConfiguration` : Is the annotation of Spring Boot that as discused above is what tell Spring Boot to automatically configure the project according to the dependencies that are add to the project.
- `@ComponentScan` : Enables component scanning so that beans can be create by Spring framework.
- `@SpringBootConfiguration` : It indicates that the class provides application configuration. It is the primary source for configuration in the application.

## Getting Started

It is highly recommened to use the [Spring Initializer](https://start.spring.io/) to create the project with the dependencies that are needed. More dependencies can be added later.

The initializer will get us started with a build system like maven or gradle what ever we choose and a directory structure.

We can then import the project into our ide and resolve the dependencies by downloading them with maven or gradle repositories.

## Jackson

Jackson is used by spring while we create a Rest Api. We see some useful short guide on using Jackson with SpringBoot.

> Serialization : Convert a object to JSON String
> Desrialization : Convert a json string into CustomObject

### Seralization Annotations

- `@JsonGetter` : Marks a method as a getter method. Is an alternative to `@JsonProperty` for getters.

```java
public class Student {
    public int id;
    private String name;

    @JsonGetter("name")
    public String getName() {
        return name;
    }
}
```

- `@JsonAnyGetter` : The @JsonAnyGetter annotation allows the flexibility of using a Map field as standard properties. Similar to `@JsonAnySetter`.

```java
//The Object definition :
public class Student {
    public String name;
    private Map<String, String> studentDetails;

    @JsonAnyGetter
    public Map<String, String> getStudentDetails() {
        return studentDetails;
    }
}
//All the key-value pairs in the map will be added to the Json String created.
```

- `@JsonPropertyOrder` : Orders the json as specified.

```java
@JsonPropertyOrder({ "name", "id" })
public class MyBean {
    public int id;
    public String name;
}
```

`@JsonPropertyOrder(alphabetic=true)` could also be used to arrange alphabetically.

- `@JsonRawValue` : instruct Jackson to serialize a property exactly as is.

- `@JsonRootName` : Wraps entire json created into the root that we specify.

```java
@JsonRootName(value = "user")
public class UserWithRoot {
    public int id;
    public String name;
}
```

```json
{
  "User": {
    "id": 1,
    "name": "John"
  }
}
```

### Deserialization Annotation

- `@JsonCreator` : We can use the `@JsonCreator` annotation to tune the constructor/factory used in deserialization. It's very useful when we need to deserialize some JSON that doesn't exactly match the target entity we need to get.

```json
{
  "id": 1,
  "name": "adwait"
}
```

```java
public class Student {
    public int id;
    public String studentName;

    @JsonCreator
    public Student(
      @JsonProperty("id") int id,
      @JsonProperty("name") String studentName) {
        this.id = id;
        this.studentName = studentName;
    }
}
```

- `@JsonAnySetter` : On deserialization, the properties from JSON will simply be added to the map.

```json
{
  "name": "adwait",
  "key1": "val1",
  "key2": "val2"
}
```

```java
public class Student {
    public String name;
    private Map<String, String> details;

    @JsonAnySetter
    public void addDetails(String key, String value) {
        details.put(key, value);
    }
}
```

- `@JsonSetter` : Marks the method as a setter method. Is similar to `@JsonGetter`.

- `@JsonAlias` : defines one or more alternative names for a property during deserialization. `@JsonAlias({ "fName", "f_name" })` Marked over property.

### Property Inclusion Annotations

- `@JsonIgnoreProperties` : Is a class-level annotation that marks a property or a list of properties that Jackson will ignore.

```java
@JsonIgnoreProperties({ "id" })
public class BeanWithIgnore {
    public int id;
    public String name;
}
```

- `@JsonIgnore` : Is used to mark a property to be ignored at the field level.

- `@JsonIgnoreType` : Marks all properties of an annotated type to be ignored.

- `@JsonInclude` : To exclude properties with empty/null/default values.

```java
@JsonInclude(Include.NON_NULL)
public class MyBean {
    public int id;
    public String name;
}
```

- `@JsonFormat(shape = JsonFormat.Shape.STRING)` OR `@JsonFormat(shape = JsonFormat.Shape.STRING, pattern= "yyyy-MM-dd")`

- `@JsonProperty("date")` : Specify custom name for the property.

```java
@JsonProperty("date")
@JsonFormat(shape = JsonFormat.Shape.STRING, pattern="yyyy-MM-dd")
private Calendar someDate;
```

```json
{
  "fieldOne": "Some text",
  "date": "2019-02-26"
}
```

- `@JsonProperty(access = JsonProperty.Access.WRITE_ONLY)`

- Or the above acan be achieved by `@JsonIgnore`

```java
class User {

    // More fields here
    @JsonIgnore
    private String password;

    @JsonIgnore
    public String getPassword() {
        return password;
    }

    @JsonProperty
    public void setPassword(final String password) {
        this.password = password;
    }
}
```

- `@JsonUnwrapped` : unwrapped/flattened when serialized/deserialized.

```java
public class UnwrappedUser {
    public int id;

    @JsonUnwrapped
    public Name name;

    public static class Name {
        public String firstName;
        public String lastName;
    }
}
```

```json
{
  "id": 1,
  "firstName": "John",
  "lastName": "Doe"
}
```

Some Rules for Serialization and Deseralization

- Restricting seralizing and deseralizing : (Does not work : The getter and setters are important for some reason to start the project)
- If getters and setters are not set for the properties of a class, only the properties with public access modifiers are seralized and deseralized.
- If getters are set, only those properties will be seralized and deseralized, when all properties are private. Or the above rule will apply for all properties that have public access modifier.
- If a property is private and has a setter it will be considered for deseralizing and not seralizing.

> For more : [Jackson-Annotations](https://www.baeldung.com/jackson-annotations)

## Spring Data JPA

We will be using PostgreSql for this.

```properties
spring.datasource.url=jdbc:postgresql://localhost:5432/postgres
spring.datasource.username=postgres
spring.datasource.password=wait
spring.jpa.properties.hibernate.dialect = org.hibernate.dialect.PostgreSQLDialect
spring.jpa.hibernate.ddl-auto=update
spring.jpa.hibernate.show-sql=true
```

```java
//--- User Entity
import javax.persistence.*;

@Entity
@Getter @Setter
@NoArgsConstructor
@ToString
@Table(name = "users")
public class User {

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private long id;

    @Column(name = "username")
    private String name;
    @Column(name = "age")
    private int age;
    @Column(name = "active")
    private boolean active;

    public User(String name, int age, boolean active) {
        this.name = name;
        this.age = age;
        this.active = active;
    }
}


//--- Create a repository File
//Spring data jap will automatically create a bean with implementations for the methods
public interface UserRepository extends CrudRepository<User, Integer> {
    List<User> findByName(String name);
    User findById(long id);
}

//--- Use in Application
@SpringBootApplication
public class WebsiteApplication {

  private static final Logger log = LoggerFactory.getLogger(WebsiteApplication.class);

  @Autowired
  private UserRepository repository;

  public static void main(String[] args) {
    SpringApplication.run(WebsiteApplication.class, args);
  }

  @Bean
  public CommandLineRunner test() {
    return (args -> {
      //--save new users
      repository.save(new User("Adwait", 28, true));
      repository.save(new User("Vikas", 23, true));
      repository.save(new User("Sandipan", 24, true));

      log.info("<-----All users---->");
      for(User user : repository.findAll()){
        log.info(user.getName());
      }

      //find and update existing user
      User adwait = repository.findById(1);
      adwait.setAge(28);
      repository.save(adwait);

    });
  }
}
```

## Using Environment Variables

In the application.properties file we could use environment variables.

Environment variables without default value : `api.key=${API_KEY}`

Environment variables with default value : `api.key=${API_KEY:123abc}`

`@Value("${message.default.welcome}")`
Can be used in our java program to get the values of the set environment variable.

It also helps us to set a default value if this variable was not found.
`@Value("${message.default.welcome:SomeDefaultValue}")`

If our properties have some common context like the same prefix, we can use the `@ConfigurationProperties` annotation which will map these properties to Java objects:

```java
/*
* @Configuration will tell Spring to create a bean of this class.
* @ConfigurationProperties will initialize the fields with corresponding property names.
*/
@Configuration
@ConfigurationProperties(prefix = "message.default")
public class MessageProperties {

    private String welcome;
    private String goodbye;

    // Getters and Setters
}

//We can now use this bean anywhere in our project
@Autowired
private MessageProperties messageProperties;
```

### @Value

`@Value` annotation is used to read the environment in the java code.

> @Value("${property_key_name}")

```java
import org.springframework.beans.factory.annotation.Value;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class DemoApplication {
   @Value("${spring.application.name}")
   private String name;
   public static void main(String[] args) {
      SpringApplication.run(DemoApplication.class, args);
   }
   @RequestMapping(value = "/")
   public String name() {
      return name;
   }
}
```

## Using Spring Profiles

Following files can be defined for different environments:

1. application-dev.properties
2. application-qa.properties
3. application-prod.properties

To change between these environments we have to set the environment variable: `--spring.profiles.active="dev"` while we run the program like so : `java -jar app.jar --name="Spring"`.

> Note : application.properties is always loaded, irrespective of the spring.profiles.active value. If there is the same key-value present both in application.properties and `application-<environment>`.properties, the latter will override the former.
> While Using IntelliJ IDE we can set the environment variables in Run -> Edit Configuration -> EnvironmentVariables while we run the program with IntelliJ.

### Active Profile

We could either use multiple application.properties file or one yaml file to store properties for different profiles.

- Using application.properties file.

To activate a given profile we could use :

`--spring-profile-active=prod`

- Use a single yaml file and add all properties to the file :

```yaml
spring:
  application:
    name: demoservice
server:
  port: 8080

---
spring:
  profiles: dev
  application:
    name: demoservice
server:
  port: 9090

---
spring:
  profiles: prod
  application:
    name: demoservice
server:
  port: 4431
```

The command to activate a given profile still remains the same :

`--spring-profile-active=prod`

## Cross Origin Resource Sharing : CORS Support

Cross-Origin Resource Sharing (CORS) is a security concept that allows restricting the resources implemented in web browsers. It prevents the JavaScript code producing or consuming the requests against different origin.

For example, your web application is running on 8080 port and by using JavaScript you are trying to consuming RESTful web services from 9090 port. Under such situations, you will face the Cross-Origin Resource Sharing security issue on your web browsers.

Two requirements are needed to handle this issue −

- RESTful web services should support the Cross-Origin Resource Sharing.

- RESTful web service application should allow accessing the API(s) from the 8080 port.\*

### Global CORS configuration

```java
//other imports above, does not have all imports added only relevant imports.
import org.springframework.web.cors.CorsConfiguration;
import org.springframework.web.cors.UrlBasedCorsConfigurationSource;
import org.springframework.web.filter.CorsFilter;

@EnableWebSecurity
public class WebSecurityConfig extends WebSecurityConfigurerAdapter {

    @Override
    protected void configure(HttpSecurity http) throws Exception {
        http.cors().and()
            //other config
    }

    @Bean
    CorsConfigurationSource corsConfigurationSource() {
      CorsConfiguration config = new CorsConfiguration();
      config.setAllowCredentials(true); //Not needed can be skipped
      config.addAllowedOrigin("https://domain1.com");
      config.addAllowedHeader("*"); //allows all headers
      //If allowed methods are not added, the default methods allowed are "GET" and "HEAD".
      config.addAllowedMethod("*"); //allow all methods eg "POST", "GET", "DELETE" ...
      UrlBasedCorsConfigurationSource source = new UrlBasedCorsConfigurationSource();
      source.registerCorsConfiguration("/**", config);//For all mappings
      return source;
   }
}
```

For more info and other more specific configuration of CORS :

> [CORS with Spring](https://howtodoinjava.com/spring5/webmvc/spring-mvc-cors-configuration/#global-cors)
> .
> [DOCUMENTATION](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/web/cors/CorsConfiguration.html#addAllowedMethod-java.lang.String-)
> .
> [DOCS Example](https://docs.spring.io/spring-framework/docs/4.3.x/spring-framework-reference/html/cors.html)

## Swagger2

Swagger2 is an open source project used to generate the REST API documents for RESTful web services. It provides a user interface to access our RESTful web services via the web browser.

```xml
<dependency>
   <groupId>io.springfox</groupId>
   <artifactId>springfox-swagger2</artifactId>
   <version>2.7.0</version>
</dependency>
<dependency>
   <groupId>io.springfox</groupId>
   <artifactId>springfox-swagger-ui</artifactId>
   <version>2.7.0</version>
</dependency>
```

```java
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import springfox.documentation.swagger2.annotations.EnableSwagger2;

@SpringBootApplication
@EnableSwagger2
public class SwaggerDemoApplication {
    public static void main(String[] args) {
      SpringApplication.run(SwaggerDemoApplication.class, args);
    }
    @Bean
    public Docket productApi() {
      return new Docket(DocumentationType.SWAGGER_2).select()
         .apis(RequestHandlerSelectors.basePackage("com.tutorialspoint.swaggerdemo")).build();
   }

}
```

> We can find the documentation at : [Swagger generated Doc Url at port 8080](http://localhost:8080/swagger-ui.html)

## Validation

Validating domain objects in Spring boot

Dependency : Starting from Spring Boot 2.3 we need to explicitly add the dependency.

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-validation</artifactId>
</dependency>
```

For Gradle

> implementation('org.springframework.boot:spring-boot-starter-validation')

Spring Boot supports seamless integration with custom validators, the de-facto standard for performing validation is Hibernate Validator, the Bean Validation framework's reference implementation.

> List of all annotations : [Hibernate Validation all annotation List](https://docs.jboss.org/hibernate/beanvalidation/spec/2.0/api/javax/validation/constraints/package-summary.html)

### Validate Request Body

In POST and PUT requests, it’s common to pass a JSON payload within the request body. Spring automatically maps the incoming JSON to a Java object. Now, we want to check if the incoming Java object meets our requirements.

Object to map json to :

```java
class Input {

  @Min(1)
  @Max(10)
  private int numberBetweenOneAndTen;

  @Pattern(regexp = "^[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}$")
  private String ipAddress;

  // ...
}
```

Controller class:

```java
@RestController
class ValidateRequestBodyController {

  @PostMapping("/validateBody")
  ResponseEntity<String> validateBody(@Valid @RequestBody Input input) {
    return ResponseEntity.ok("valid");
  }

}
```

If the validation fails, it will trigger a `MethodArgumentNotValidException`. By default, Spring will translate this exception to a HTTP status 400 (Bad Request).

### Validating Request Parameter and Path Variables

Validating path variables and request parameters works a little differently.

We’re not validating complex Java objects in this case, since path variables and request parameters are primitive types like int or their counterpart objects like Integer or String.

Instead of annotating a class field like above, we’re adding a constraint annotation (in this case `@Min`) directly to the method parameter in the Spring controller

```java
@RestController
@Validated
class ValidateParametersController {

  @GetMapping("/validatePathVariable/{id}")
  ResponseEntity<String> validatePathVariable(
      @PathVariable("id") @Min(5) int id) {
    return ResponseEntity.ok("valid");
  }

  @GetMapping("/validateRequestParameter")
  ResponseEntity<String> validateRequestParameter(
      @RequestParam("param") @Min(5) int param) {
    return ResponseEntity.ok("valid");
  }

   //If we want to return a HTTP status 400 instead we can add a custom exception handler to our contoller:
   @ExceptionHandler(ConstraintViolationException.class)
   @ResponseStatus(HttpStatus.BAD_REQUEST)
   ResponseEntity<String> handleConstraintViolationException(ConstraintViolationException e) {
    return new ResponseEntity<>("not valid due to validation error: " + e.getMessage(), HttpStatus.BAD_REQUEST);
  }
}
```

In contrast to request body validation a failed validation will trigger a `ConstraintViolationException`. Spring does not register a default exception handler for this exception, so it will by default cause a response with HTTP status 500 (Internal Server Error).

### Validating Input to a Spring Service Method

Instead of (or additionally to) validating input on the controller level, we can also validate the input to any Spring components. In order to to this, we use a combination of the @Validated and @Valid annotations:

```java
@Service
@Validated
class ValidatingService{
    void validateInput(@Valid Input input){
      // do something
    }
}
```

Again, the @Validated annotation is only evaluated on class level, so don’t put it on a method in this use case.

### Validating JPA Entities

The last line of defense for validation is the persistence layer. By default, Spring Data uses Hibernate underneath, which supports Bean Validation out of the box.

> We usually don't want to do validation as late as in the persistence layer because it means that the business code above has worked with potentially invalid objects which may lead to unforeseen errors.

```java
@Entity
public class Input {

  @Id
  @GeneratedValue
  private Long id;

  @Min(1)
  @Max(10)
  private int numberBetweenOneAndTen;

  @Pattern(regexp = "^[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}$")
  private String ipAddress;

  // ...

}
```

We create a Spring Data repository that provides us with methods to persist and query for Input objects:

```java
public interface ValidatingRepository extends CrudRepository<Input, Long> {}
```

By default, any time we use the repository to store an Input object whose constraint annotations are violated, we’ll get a `ConstraintViolationException`.

```java
@ExtendWith(SpringExtension.class)
@DataJpaTest
class ValidatingRepositoryTest {

  @Autowired
  private ValidatingRepository repository;

  @Autowired
  private EntityManager entityManager;

  @Test
  void whenInputIsInvalid_thenThrowsException() {
    Input input = invalidInput();

    assertThrows(ConstraintViolationException.class, () -> {
      repository.save(input);
      entityManager.flush();
    });
  }

}
```

### Implementing a Custom Validator

In the Input class from above, we used a regular expression to validate that a String is a valid IP address. However, the regular expression is not complete: it allows octets with values greater than 255 (i.e. “111.111.111.333” would be considered valid).

Let’s fix this by implementing a validator that implements this check in Java instead of with a regular expression (yes, I know that we could just use a more complex regular expression to achieve the same result, but we like to implement validations in Java, don’t we?).

We Create the custom constraint annotation IpAddress.

```java
@Target({ FIELD })
@Retention(RUNTIME)
@Constraint(validatedBy = IpAddressValidator.class)
@Documented
public @interface IpAddress {

  String message() default "{IpAddress.invalid}";

  Class<?>[] groups() default { };

  Class<? extends Payload>[] payload() default { };

}
```

```java
class IpAddressValidator implements ConstraintValidator<IpAddress, String> {

  @Override
  public boolean isValid(String value, ConstraintValidatorContext context) {
    Pattern pattern =
      Pattern.compile("^([0-9]{1,3})\\.([0-9]{1,3})\\.([0-9]{1,3})\\.([0-9]{1,3})$");
    Matcher matcher = pattern.matcher(value);
    try {
      if (!matcher.matches()) {
        return false;
      } else {
        for (int i = 1; i <= 4; i++) {
          int octet = Integer.valueOf(matcher.group(i));
          if (octet > 255) {
            return false;
          }
        }
        return true;
      }
    } catch (Exception e) {
      return false;
    }
  }
}
```

We can now use the @IpAddress annotation just like any other constraint annotation:

```java
class InputWithCustomValidator {

  @IpAddress
  private String ipAddress;

  // ...

}
```

> For even more much more on validators and validation : [Bean Validation with Spring-Boot](https://reflectoring.io/bean-validation-with-spring-boot/#using-validation-groups-to-validate-objects-differently-for-different-use-cases)

## Exception Handling With Spring

- Handling a particular Type of Exception - Controller Level :

```java
private static final String NOT_FOUND_MESSAGE = "Flight not found for number";

@ExceptionHandler(IndexOutOfBoundsException.class)
@ResponseStatus(HttpStatus.NOT_FOUND, reason = NOT_FOUND_MESSAGE)
public HashMap<String, String> handleIndexOutOfBoundsException(Exception e) {
    HashMap<String, String> response = new HashMap<>();
    response.put("message", NOT_FOUND_MESSAGE);
    response.put("error", e.getClass().getSimpleName());
    return response;
}
```

In this the `@ResponseStatus` Sets the response status to be displayed.

- Global Exception Handler

```java
@RestControllerAdvice//The annotation signifies that the class be used as the global exception handler class.
@ResponseStatus(HttpStatus.NOT_FOUND, reason = NOT_FOUND_MESSAGE)//Sends the status code with the response entity.
public class ControllerExceptionHandler {

    private static final String NOT_FOUND_MESSAGE = "Information not found for number";

    @ExceptionHandler(IndexOutOfBoundsException.class)
    public HashMap<String, String> handleIndexOutOfBoundsException(Exception e) {
        HashMap<String, String> response = new HashMap<>();
        response.put("message", NOT_FOUND_MESSAGE);
        response.put("error", e.getClass().getSimpleName());
        return response;
    }
}
```

- Throw an Exception at any place :

```java
@RestController
public class AirportController {

    private List<AirportInfo> airportInfoList = new ArrayList<>();
    private static final String SERVICE_WARNING_MESSAGE = "Berlin Schönefeld is closed for service today";

    public AirportController() {
        airportInfoList.add(new AirportInfo("Kilimanjaro Arusha", "ARK", "HTAR"));
        airportInfoList.add(new AirportInfo("Berlin Schönefeld", "TXL", "EDDT"));
        airportInfoList.add(new AirportInfo("Delhi Indira Gandhi", "DEL", "VIDP"));
        airportInfoList.add(new AirportInfo("Tokio Haneda", "HND", "RJTT"));
    }

    @GetMapping("airports/{id}")
    public AirportInfo getAirportInfo(@PathVariable int id) {
        AirportInfo airportInfo = airportInfoList.get(id);
        //For this case we respond with an exception.
        if (Objects.equals(airportInfo.getName(), "Berlin Schönefeld")) {
            throw new ResponseStatusException(HttpStatus.BAD_REQUEST, SERVICE_WARNING_MESSAGE);
        }
        return airportInfo;
    }

}
```

- When we have a global and a Controller level we can give prefernece to which handles the exception by giving `@Order(Ordered.HIGHEST_PRECEDENCE)` to the handler that we want to handle the exception.

- Creating Custom Exceptions :

The exception class

```java
@ResponseStatus(code = HttpStatus.BAD_REQUEST)
class FlightNotFoundException extends RuntimeException {}
```

```java
@GetMapping("flights/{id}")
public FlightInfo getFlightInfo(@PathVariable int id) {
    if (id > flightInfoList.size()) {
        throw new FlightNotFoundException("Flight not found for id =" + id);
    }
    return flightInfoList.get(id);
}
```

- Conclusion

Here you have learned different ways of handling exceptions. You can make it:

- Globally with @RestControllerAdvice;
- On controller level with @ExceptionHandler;
- In the most flexible way by throwing ResponseStatusException at any place you want.
- You can also set the order of handlers with the @Order annotation to control the system of them.

## Cross Origin Requests

When our spring Application is hosted on a different domain than that of our frontend application, the browser will send a [PreFlightRequest](https://developer.mozilla.org/en-US/docs/Glossary/Preflight_request) which our Spring Boot Backend rejects as it is a Cross Domain Request and we get an error in our Front End Project.

Consider the following example where we use HttpClient in Angular application to send a request to our Spring Application.

```error
Access to XMLHttpRequest at 'https://spring.boot.backend.link/something' from origin 'http://localhost:4200' has been blocked by CORS policy: Response to preflight request doesn't pass access control check: No 'Access-Control-Allow-Origin' header is present on the requested resource.
```

We can solve this Problem by allowing request from particualar defined domain. We use the `@CrossOrigin(origins = "http://FrontEndHostUrl.com")` annotation over the `@RequestMapping` annotation that we have set for our controller.

[Guide On spring.io Website](https://spring.io/guides/gs/rest-service-cors/)

If we want to temporarily allow our frontend to be able to connect with our backend locally we can set up a ProxyServer with our development server.

For Angular we can solve it as show [here](https://medium.com/better-programming/setup-a-proxy-for-api-calls-for-your-angular-cli-app-6566c02a8c4d). Or for a short tutorial refer to the angular notes [here](https://github.com/Adwai-T/Notes/blob/master/WebDevelopment/AngularCourceNotes.md) and search for Proxy Server.

> Please note this is only for `ng serve`, you can't use proxy in `ng build`.
> Note: the reason it's working via postman is postman doesn't send preflight requests while your browser does.

## Repository

There are repository interfaces that can be extended, which will allow spring boot to create a implementation of that repository for.

When these interfaces are extended, they come with a lot of pre-implemented methods, that can then be directly used and do not need to be added to the methods of that repository.

But if custom methods are needed, they can then be added to the interface, from which the framework will create an implementation.

> Check the documentation for the repositories to get a full list of all methods that are implemented by extending the repostories. Ex [MongoRepository Documentation](https://docs.spring.io/spring-data/mongodb/docs/current/api/org/springframework/data/mongodb/repository/MongoRepository.html), here all the Superinterfaces extended can also be found.

### MongoRepository

Say a Mongodb repository was need to be created, in that case, an interface can be created that extends `MongoRepository`. In this interface methods that are needed can be written and they will be implemented by the framework.

Most specialized repositorys like `Mongorepostory` already themselves extend `CrudRepository<T,ID>`, `PagingAndSortingRepository<T,ID>`, `QueryByExampleExecutor<T>`, `Repository<T,ID>` etc that provide implementation for different methods.

> [MongoRepository Documentation.](https://docs.spring.io/spring-data/mongodb/docs/current/api/org/springframework/data/mongodb/repository/MongoRepository.html)
