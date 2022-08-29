# Swagger

Swagger provides tools to :

1. Develop APIs
2. Interact with APIs
3. Document APIs

Why use swagger for documentation?

If the API is constantly updated, we will also keep up with updating the documentation for our user. This means that we will have to spend time every time to update the documentation. To automate this process we use swagger.

API documentation is the most popular use of swagger, although it has tools to help us develop and interact with our API.

## Adding Swagger To Spring Boot

> Before you add Swagger to your project, it has not been updated for a while and might not be updated further. So to future proof your project it is recommended to add a different documentation tools as [springdoc-openapi](https://springdoc.org/). I tried to recently add Swagger to my project and it is filled with unexpected problems that arise as it has not been updated as Spring Boot has developed.
> Swagger Still works fine if you want to use it.

### Get the swagger 2 Spring dependency

We can add the maven dependency for SpringFox Swagger2 which will give us our documentation in the JSON format and then we can create a UI for it or we can add Springfox Swagger UI which will provide documentation with the UI.

> Swagger UI need both the dependencies to be added.

```xml
<!-- JSON documentation -->
<dependency>
    <groupId>io.springfox</groupId>
    <artifactId>springfox-swagger2</artifactId>
    <version>3.0.0</version>
</dependency>

<!-- UI documentation -->
<dependency>
    <groupId>io.springfox</groupId>
    <artifactId>springfox-swagger-ui</artifactId>
    <version>3.0.0</version>
</dependency>
```

> [Springfox Swagger2 MVNRepository](https://mvnrepository.com/artifact/io.springfox/springfox-swagger2/3.0.0).
> [Springfox Swagger2 UI MVNRepository](https://mvnrepository.com/artifact/io.springfox/springfox-swagger-ui).

### Enabling Swagger in our code

The Following will enable swagger in its most basic form without configuration.

```java
@SpringBootApplication
@EnableSwagger2 //-- This will enable swagger in our project
public class SpringbootSwaggerApplication {
    //-- main method
    //-- Other code.
}
```

Now we can go to `http://localhost:8080/v2/api-docs` or send a get request with a tool like postman to get the JSON base documentation result.

Using swagger without configuration is not recommended thought as it contains all the endpoints that might not be useful to the user.

Configuring swagger gives users of our api a better experience with our documentation and give them information that they need in a format that we want.

If we have swagger UI enabled we can access it at `http://localhost:8080/swagger-ui.html`.

> When we have Swagger UI enabled we cannot have an API endpoint controller directly at the root as it might not allow swagger link to be accessed.

### Trouble Shooting documentationPluginsBootstrapper

This issue is caused by Spring Fox 3.0.0 not supporting new PathPattern Based Path Matching Strategy for Spring MVC which is now the new default from spring-boot 2.6.0.

Spring is using mvcmatchers by default which conflicts with swagger because it uses the antmatchers so we can solve this by the following methods.

* Downgrading Spring-Version will solve the issue but should not be done just to use swagger.
  
* Changing PathPattern matching back to AntPatternMatching in properites/yml file.

```properites
# In application.properties
spring.mvc.pathmatch.matching-strategy=ant_path_matcher
```

* Enable MVCmatchers in spring creating a configuration file for swagger to use.

```java
@EnableWebMvc
@EnableSwagger2
@Component
public class SwaggersConfigs {
}
```

* Migrate to [Spring Doc](https://springdoc.org/#migrating-from-springfox) as swagger did not have any updates for a long time.

#### Spring Security Access

Make sure that all the following paths are accessible while using swagger.

`( "/v2/api-docs", "/swagger-ui/**", "/swagger-resources/**")` if using swagger2.

`( "/v3/api-docs**", "/v3/api-docs/**","/swagger-ui**", "/swagger-ui/**", "/swagger-resources/**")`

if using [SpringDoc](https://springdoc.org/)

When spring security is enabled it will block all paths by default. Configure spring security to enable these Paths.

#### InternalResourceViewResolver Issue

If there are view resolution issues there might be a need to manually create a bean for the View Resolver in our Swagger Configuration.

```java
@Bean
public InternalResourceViewResolver defaultViewResolver() {
    return new InternalResourceViewResolver();
}
```

### Configure Swagger

Swagger by default provides a lot of unnecessary information like error endpoints, all the models even those that are provided by spring, etc when it is not configured. Configuring swagger for our project will help us provide users with the documnentation that they need and abstract what not needed.

Swagger is configured in spring by using a bean of type `Docket`.

```java
//Docket Bean
@Bean
public Docket swaggerConfiguration() {
    //Return a Docket instance
    return new Docket(DocuementationType.SWAGGER_2)
        .select()
        .path(PathSelectors.ant("/api/*"))//Endpoints to include on path.
        .apis(RequesthandlerSelectors.basePackage("in.adwait"))//only include documentation for this package.
        .build()
        .apiInfo(apiDetails());
}

//Add API information shown at the top
private ApiInfo apiDetails() {
    return new ApiInfo(
        "Website API",//name
        "Api used in the webiste adwait.in",//detail
        "2.0",//version
        "Restricted Use",
        new springfox.documentation.service.Contact("Adwait", "https://adwait.in", "adwait@adwait.in"),
        "API Licence",
        "https://adwait.in",
        Collections.emptyList());
}
```

The `Docket` instance is configured by using the builder pattern. We call methods on the instance that we need to configure and then we call `build()` method to finally build the instance.

### Adding details as annotations to APIs

Swagger will infer a lot of information about our API and endpoints. We can add more information by annotating our methods/endpoint controllers.

```java
@GetMapping("/{id}")
@ApiOperation(
    value="Find Contacts by ID",
    notes = " Provide an id to look up a specific contact",
    response = "Contact.class"
    )
public Contact getContact(
    @ApiParam(value="ID value for contact", required=true) @PathVariable String id
    ) {
    return contacts.get(id);
    
}


//For model
@ApiModel(description="Details about the contact")
public class Contact {
    
    @ApiModelProperty(notes="The unique id of the contact")
    private String id;

    @ApiModelProperty(notes="The person's name")
    private String name;

    @ApiModelProperty(notes="The person's phone number")
    private String phone;
}
```

## Spring REST Docs

There is an Alternative to Swagger specifically being designed for spring.

Swagger is great when we use it in moderation. When every model and every endpoint is being annotated with the swagger configuration annotations, it becomes very cluttered and the unreadable.

To solve this problem where in some cases the swagger annotations can have greater code than the logic/buisness code itself we might want to look towards Spring REST Docs as it takes the documentation part out of the actual code and into test code.

> [springdoc-openapi](https://springdoc.org/).
