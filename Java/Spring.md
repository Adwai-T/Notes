# Java Spring

## Spring Development Process

1. Configure Spring Beans.
2. Create a Spring Container.
3. Retrieve Beans from Spring Container.

## Configuring Spring Container

* XML Configuration

* Java Annotation

* Java Source Code

Spring Container is generally known as `Application Context`.

Specialized implementation of Application Context :

* ClassPathXmlApplicationContext : XML configuration file. Is legacy, but many old apps might use them.

* AnnotationConfigApplicationContext

* GenericWebApplicationContext

When Java objects are created by the `Spring Container`, then Spring refers to them as `Spring Beans`.

## XML Configuration

Example of ClassPathXmlApplicationContext

### Define a bean

```xml
<!--applicaionContext.xml-->
<beans>
  <!--There is a lot of boiler plate code, copy from starter files.-->
  <!--Other beans-->

  <!--id - is an alias-->
  <!--class - should be specified as a fully qualified class name of implementation class-->
  <bean id="myBean" 
  class="in.adwait.springdemo.myBeanClass">
  </bean>
</beans>
```

### Create a Spring Container

```java
//Create a spring container
ClassPathXmlApplicationContext context = new ClassPathXmlApplicationContext("applicationContext.xml");

//retrieve bean from spring container
//myBean relates to the id that we specified in the xml configuration file that we created.
MyBean bean = context.getBean("myBean", MyBeanInterface.class)

//getMessage is a method of the MyBeanInterface
System.out.println(bean.getMessage());

context.close();
```

## XML Component Scan for Configuring Container

We will use spring annotations scan for our component but we will still use xml to configure our container.

`<context:component-scan base-package="in.adwait.springdemo">`

This is the second way of configuring our Spring container.

## Java Annotation

Why Spring Annotations ?

1. XML configuration can be verbose.
2. Annotations minimizes the XML configuration needed.
3. Spring will scan our java class for special annotaions.
4. Automatically registers the bean with spring container.

### @Component

```java
//---MyBeanInterface.java
public interface MyBeanInterface{
  public String getMessage();
}

//---MyBean.java
//We can use @Component as so without a explicit bean id.
//If we do not specify a bean id spring will generate a defualt name for our bean that will be the name of the class starting with lowercase first character.
//So for below example it will be 'myBean' by default.
@Component("myBeanId")
public class MyBean implements MyBeanInterface{
  @Override
  public String getMessage(){
    return "This is message from the MyBean class";
  }
}

//---Main.java
public class Main{
  public static void main(String [] args) {

    //Read the below xml configuration file to enable component scanning.
    ClassPathXmlAppliationContext context = new ClassPathXSmlApplicationContext("applicationContext.xml");

    //getBean() can have only id, but here we specify the type of bean to make it more type safe.
    MyBean myBean = context.getBean("myBeanId", MyBeanInterface.class);

    System.out.println(myBean.getMessage);

    context.close();
  }
}
```

We here are still going to use xml in this example to enable component scanning in our base package.

```xml
<!--applicationContext.xml-->
<!--Other code here.-->

<beans>
<!--Other code here.-->

  <!--This will enable component scanning in the package given-->
  <context:component-scan base-package="in.adwait.springdemo" />
</beans>

```

## Java Container Configuration

We in modern Spring application prefer to use pure java to configure our Spring application. We in this third and final method will not use XML.

Instead of using `ClassPathXmlApplicationContext` we will be using `AnnotationConfigApplicaionContext`.

```java
@Configuration
@ComponentScan("in.adwait.springdemo")
public class MyConfigurationClass{

}

public interface MyBeanInterface{
  public String getMessage();
}

public class MyBean implements MyBeanInterface{

  public MyBean() { }

  public String getMessage() {
    return "Message From MyBean";
  }
} 

public class Main{

  public static void main(String [] args) {
    //create our annotation context
    AnnotationConfigApplicationContext context = new AnnotationCofigApplicationContext(MyConfigurationClass.class);

    //get bean
    MyBean bean = context.getBean("myBean", MyBeanInterface.class);

    //Use Our bean
    System.out.println(bean.getMessage());

    //Close context
    context.close();
  }
}
```

## Bean Scope

### Singleton

1. Spring container creates only on instance of the bean, by default.
2. It is cached in memory.
3. All request for the bean will return a Shared reference to the same bean.

We can specify explicitely the scope of a bean to be singleton as `<bean id="..." class"..." scope="singleton">`

If we want dont want to use xml configuration and are using java annotations we could use `@Scope("singleton")` over the class to make it a singleton bean.

### Other bean Scopes

|scope|Description|
|:---:|:---------|
|singleton|Create a single instance of bean.(Default Scope)|
|prototype|Create a new bean instance for each container request|
|request|Scoped to an HTTP web request. Only used for web applicaitions|
|session|Scoped to an HTTP web session.|
|global-session|Scoped to a global HTTP web session|

### Bean Life-Cycle Methods / Hooks

> Important : For modularity Java 9+  `javax.annotation` has been removed from its default classpath, so our ide will not be able to import the lifecycle hook annotations for us.
> [Download or add to maven/gradle 'Javax Annotation API'](https://mvnrepository.com/artifact/javax.annotation/javax.annotation-api) to use it in the project if needed to us the lifecycle hooks of the beans.

The methods specifed below can have any access type(`public`, `protected`, `private`). They can have a return  but the return can never be captured for use, so most commonly `void` is used. The methods should be no-arg.

> For `prototype` scoped beans, Spring does not call the destroy method. [More on why at spring reference.](https://docs.spring.io/spring/docs/current/spring-framework-reference/core.html#beans-factory-scopes-prototype)

In short : In contrast to the other scopes, Spring does not manage the complete lifecycle of a prototype bean.

So unless you know what you are doing and you are implementing custom code to release resources used by there prototype beans, and there is a good reason to use prototype scope in the first place dont use prototype scope.

* With XML configurations

```xml
<beans >
<!--When bean is initalized and destoried-->
  <bean 
    id"..." 
    class="..." 
    init-method="doOnBeanInit"
    destroy-method="doOnBeanDestroied">
  </bean>
</beans>
```

```java
public class MyBean{
  public MyBean() {}

  public void doOnBeanInit() {
    //On Bean Init lifecycle method
  }

  public void doOnBeanDestroied() {
    //On Bean Destroied method.
  }
}
```

* With Java Annotations

```java
@Component
public class MyBean{

  @PostConstruct
  public void doOnBeanInit(){

  }

  @PreDestroy
  public void doOnBeanDestroied(){

  }
}
```

## Dependency Injection

Object factory create an object for us according to our configuration and then provides us with the required object.

### Common types of injection

1. Constructor Injection
2. Setter Injection

### With XML Configuration

```xml
<!--Load the properties file that we will use below-->
<context:property-placeholder location="classpath:contact.properties" />

<bean id="myService"
  class="in.adwait.springdemo.MyService"
></bean>

<!--Contructor Injection-->
<bean id="myBean"
class="in.adwait.springdemo.MyBean">
  <contructor-arg ref="myService" /> <!--This will inject it into our constructor-->
</bean>

<!--Use either contructor injection or setter injection-->
<!--Setter Injection-->
<bean id="myBean"
class="in.adwait.springdemo.MyBean">
  <property name="myServiceVariableName" ref="myService" />
</bean>

<!--Spring in case of setter injection will look for the setMyServiceVariableName (Capatalize first letter of property name) and inject the bean into this setter.-->

<!--Injecting literal values in methods-->
<bean id="myBean"
class="in.adwait.springdemo.MyBean">
  <property name="myServiceVariableName" ref="myService" />

  <property name="emailAddress" value="${foo.email}" />

  <property name="name" value="Adwait">
</bean>
```

> `#` is used for comment in .properties files.

```properties
#contact.properties
foo.email=adwait@adwait.in
```

```java
//MyBeanInterface.java

public interface MyBeanInterface{
  public String getMessage();
}
```

```java
//MyBean.java
public class MyBean implements MyBeanInterface {

  private String emailAddress;
  private String name;
  private MyService service

  public MyBean(){}

//Use either contructor injection or setter injection according to the way the configuration file has been specified.

//Contructor injection
  public MyBean(MyService service) {
    this.service = service;
  }

//Setter Injection
  public void setMyService(MyService service) {
    this.service = service;
  }

  //Using the service
  //We assume that our service also has getMessage method. Nothing to do with the interface that this class implements.
  public String getMessage() {
    return service.getMessage();
  }

//Injecting literal values from xml configuration file.
  public void setEmailAddress(String emailAddress) {
    this.emailAddress = emailAddress;
  }
  
  public void setName(String name) {
    this.emailAddress = emailAddress;
  }

    public String getEmailAddress() {
    return emailAddress;
  }
  
  public String getName() {
    return emailAddress;
  }
}
```

### With @Autowired Annotation

We have an additional type of injection with the `@Autowired`, directly into a variable by annotating the variable with the annotation called as **Field Injection**

```java
public class MyBean{
  //---Field Injection
  @Autowired
  private MyService myService; //This will direclty inject the service when the instance is created.
  //This field method works by using refection.

  //Use Only one of the type of injection (Constructor / Setter).

  private MyService myService;

//---Constructor Injection
  @AutoWired
  public MyBean(MyService myService) {
    this.myService = myService;
  }

//---Setter Injection
  @Autowired
  public void setMyService(MyService myService) {
    this.myService = myService;
  }
}
```

> As of Spring Framework 4.3, an `@Autowired` annotation on such a constructor is no longer necessary if the target bean only defines one constructor to begin with. However, if several constructors are available, at least one must be annotated to teach the container which one to use.
> We can use any method name `@Autowired` to inject a dependecny. But it is not recommeded, using setter or constructor is recommended.

Which Injection should we use?

* First and most important is be consistent through out the project.

* Even thought most will recommend constructor injection in most places, we can use any we want as spring documentation suggests that all types of injection give the same functionality.

### @Qualifier

`@Qualifier` is used when there are multiple beans of the same type that are created and we want to specify which bean must be injected. If this is not specified spring will through `NoUniqueBeanException`, as it will not know which specific bean is need to be injected.

```java

//Specify a name for our bean
@Component("myService")
public class MyService{ 
  //... 
}

@Component
public class MyBean implements MyBeanService{

  //We specifie the specific bean with the bean id.
  //@Qualifier("bean id")
  @Autowired
  @Qualifier("myService")
  private MyBeanService myBeanService;
}
```

`@Qualifier` could be used with any of the type of injections. It need to be used with `@Autowired`.

> If the annotation's value doesn't indicate a bean name, an appropriate name will be built based on the short name of the class (with the first letter lower-cased). eg `MyService` -> `myService`.
> However, for the special case of when BOTH the first and second characters of the class name are upper case, then the name is NOT converted. eg `MYBeanService` -> `MYBeanService`.
>**Java Beans Introspector** is used behind the sence to generate default names for each bean.

* `@Qualifier` with field injection is easy as we just specify it on top of the variable. By it is different when we use it with a constructor as we can have many services that implement the same interface being injected into the construtor.

```java
@Component
public class MyBean{

//Both the following beans implement the MyserviceInterface interface.

 //This field expects MyService Bean to be injected.
 private MyServiceInterface myService;
 //This field expects MyBeanService Bean to be injected.
 private MyServiceInterface myBeanService;

  @Autowired
  public MyBean(@Qualifier("myService") MyServiceInterface myService, @Qualifier("myBeanService") MyServiceInterface myBeanService) {
    //...
  }
}
```

> [@Qualifier Documentation](https://docs.spring.io/spring/docs/current/spring-framework-reference/core.html#beans-autowired-annotation-qualifiers)

### @Value

We use `@Value` to inject Field variables from a `.properties` file.

```java
//The properties file and the configuration in the xml remains the same as we have done in the xml section above
//The xml file will only be used so that spring will know there exist such a file and variables from the file need to be used.

@Value("${foo.email}")
private String email;

@Value("${foo.name}")
private String name;
```

### With no xml

> `@Bean` : We can use `@Bean` to make an existing third-party class available to your Spring framework application context.
> We use `@PropertiesSource` to specify class path for our properties files being used.

```java
//This code is might not be perfect and may not run directly. This is to be used as reference only.

public interface MyBeanInterface{
  public String getMessage();
}

@Component
public class MyBean implements MyBeanInterface{

  @Value("${foo.email}")
  private String emailId;

  @Value("${foo.name}")
  private String name;

  private MyBeanService service;

  public MyBean(MyBeanService service) {
    this.service = service;
  }

  private String getMessage(){
    return service.getMessage();
  }

  private String getNameAndEmailString(){
    return name+" : "+ emailId;
  }
}

public interface MyBeanServiceInterface{
  public String getMessage();
}

public class MyBeanService{
  public String getMessage() {
    return "This is a message from Bean Service";
  }
}

@Configuration
@ComponentScan("in.adwait.springdemo")
@PropertiesSource("classpath:credentials.properties")
public class MyBeanConfiguration{

//Here we are manually defining the beans.
  @Bean
  public MyBeanServiceInterface myBeanService() {
    return new MyBeanService();
  }

  @Bean
  public MyBeanInterface myBean() {
    return new MyBean(myBeanService());
  }
}

public class Main{

  public static void main(String [] args) {
    AnnotationConfigApplicationContext context = new AppicationConfigApplicationContext("MyBeanConfiguration.class");

    MyBean bean = context.getBean("myBean", MyBeanInterface);

    System.out.println(bean.getMessage());

    System.out.println(bean.getNameAndEmailString());

    context.close();
  }
}
```

Properties file used above, `credentials.properties`.

```properties
foo.email=adwait@adwait.in
foo.name=Adwait
```

* While using Spring 4.2 and lower we will have to configure Spring manually to get spring to load our properties file. We can simply add the following code to our class marked with `@Configuration` annotaion.

```java
@Bean
public static PropertySourcesPlaceholderConfigurer propertySourcePlaceHolderConfugurer() {
  return new PropertySourcePlaceHolderConfigurer();
}
```

* In Spring 4.3 and higher which we will use most of the times, we do not need the above code.

## Spring MVC

Main Parts of Spring MVC :

* Front Controller : It is given to us by Spring MVC.
* Models
* Controllers
* View Template

### Configuring Spring MVC

```java

```
