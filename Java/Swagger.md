# Swagger

Swagger provides tools to :

1. Develop APIs
2. Interact with APIs
3. Document APIs

Why use swagger for documentation?

If the API is constantly updated, we will also keep up with updating the documentation for our user. This means that we will have to spend time every time to update the documentation. To automate this process we use swagger.

API documentation is the most popular use of swagger, although it has tools to help us develop and interact with our API.

## Adding Swagger To Spring Boot

### Get the swagger 2 Spring dependency.

We can add the maven dependency for SpringFox Swagger2 which will give us our documentation in the JSON format and then we can create a UI for it or we can add Springfox Swagger UI which will provide documentation with the UI.

> Both swagger2 and swagger2 UI can be added together to get both JSON documentation and UI documentation in our project.

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

> [Springfox Swagger2 UI MVNRepository](https://mvnrepository.com/artifact/io.springfox/springfox-swagger-ui).w

### Enabling Swagger in our code.

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
