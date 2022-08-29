# SpringDoc

> Refer [SpringDoc](https://springdoc.org/) for detailed getting started and setup.

Link Swagger UI : `http://server:port/context-path/swagger-ui.html`.

Link Api Documentation Request : `http://server:port/context-path/v3/api-docs`.

## Dependency

```xml
<dependency>
   <groupId>org.springdoc</groupId>
   <artifactId>springdoc-openapi-ui</artifactId>
   <version>1.6.11</version>
</dependency>
```

> It is important that `@RestController` is used as SpringDoc will not account `@Controller` to create documentation. Also `@RequestMapping` needs to be given a method, or use `GetMapping()`, `PostMapping()` like methods as there should not be ambiguity in the method being used for the request.

## Configuration

Require `( "/v3/api-docs**", "/v3/api-docs/**","/swagger-ui**", "/swagger-ui/**", "/swagger-resources/**")` paths to be withlisted in Spring Security.

```java
@Bean
public OpenAPI adwaitApiDoc() {
    return new OpenAPI()
            .info(new Info().title("adwait.in API")
                    .description("Api used by website adwait.in")
                    .version("1.0.0")
                    .license(new License().name("Apache 2.0").url("http://adwait.in")))
            .externalDocs(new ExternalDocumentation()
                    .description("Adwait Github Documentation")
                    .url("https://github.com/Adwai-T/Website-2.0-Spring"));
}

@Bean
public GroupedOpenApi publicApi() {
    return GroupedOpenApi.builder()
            .packagesToScan("in.adwait.website")
            .group("Public")
            .pathsToMatch("/**")
            .build();
}

@Bean
public GroupedOpenApi adminApi() {
    return GroupedOpenApi.builder()
            .group("Admin")
            .pathsToMatch("/admin/**")
            .build();
}
```

> `GroupedOpenApi` are shown in the top right drop down on documentation page and will group the request according to configuration.

### Properties Configuration

```properties
# swagger-ui custom path
springdoc.swagger-ui.path=/swagger-ui.html

# /api-docs endpoint custom path
springdoc.api-docs.path=/api-docs

# Disabling the swagger-ui
springdoc.swagger-ui.enabled=false

# Disabling the /v3/api-docs endpoint
springdoc.api-docs.enabled=false
```

## JavaDoc Support

For Details Check [Set up JavaDocs](https://springdoc.org/#javadoc-support)

```xml
 <!-- In combination with the springdoc-openapi-ui dependency -->
<dependency>
   <groupId>org.springdoc</groupId>
   <artifactId>springdoc-openapi-javadoc</artifactId>
   <version>1.6.11</version>
</dependency>
```
