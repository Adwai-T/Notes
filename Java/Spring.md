# Java Spring

## Setting Up Development Enviroment

Install an IDE [Eclipse](https://www.eclipse.org/downloads/) or [IntelliJ IDEA](https://www.jetbrains.com/idea/download/#section=windows)

Install [Tomcat server](https://tomcat.apache.org/download-90.cgi).

By default when Tomcat is installed as a full package(Select the type of install -> Tomcat -> Service Startup), tomcat will start as a service.

During installation we can also configure the tomcat server to set the port that tomcat serve will start(default at 8080), windows service name can be set and user and password for the server can also be set.

Once installed, we can visit `localhost:8080`, it will show a welcome page for tomcat. We can also configure the tomcat server from here.

As previously mentioned, tomcat was installed as a service for windows and we can find it in `services`. From here we can stop, start and restart the server.

## Inversion of Control

The approach of externalizing/outsourcing the construction and management of objects.

Inversion Of Control : Create and manage objects by a container or a framework.

Benefits are Decouples the execution and implementation, easier to switch between implementations, modularity, easier testing.

Simply put the Spring framework will create and manage all the instances and inject them where they are needed, it will also be responsible for managing the instances during their lifecycle.

### Dependency Injection

It is a pattern we use to implement IoC.

In the Spring framework, the interface `ApplicationContext` represents the IoC container. The Spring container is responsible for instantiating, configuring and assembling objects known as beans, as well as managing their life cycles.

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

## XML Configuration For Spring Containers

Example of ClassPathXmlApplicationContext

### Define a bean

```xml
<!--This is the basic xml configuration file that is need so that spring can know about the the schema of the configuration and interpret it correctly-->
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xmlns:context="http://www.springframework.org/schema/context"
    xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd
    http://www.springframework.org/schema/context http://www.springframework.org/schema/context/spring-context.xsd">
    
    <!--Example Bean-->
    <!-- <bean class="in.adwait.MyBeanClass">
        <property name="field" value="sample-value"></property>
    </bean> -->
</beans>
```

We will use the above file every time we have to define a xml configuration for our container.

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

Spring will recursively scan for components starting at the base package and scan all subpackages, that is all the folders inside of the main package mentioned.

This will scan for all the `@Component` annotation in the package specified in the xml configuration to create beans from the class.

This is the second way of configuring our Spring container.

The third methods is using only java and not using any xml configuration. We use java annotations to do that.

## Java Annotation

Java Anotations are used to provide metadata to the compiler but do not effect the execution of compiled program.

Why Spring Annotations ?

1. XML configuration can be verbose.
2. Annotations minimizes the XML configuration needed.
3. Spring will scan our java class for special annotaions.
4. Automatically registers the bean with spring container.

## @Component

Spring Framework automatically detects classes annotated with `@Component` during Component Scan.

We can specify specific name for the bean created form the component but by default it is the same as the class name with lowercase starting character.

`@Repository`, `@Service`, `@Configuration`, and `@Controller` are all meta-annotations of `@Component`, and are automatically picked up by Spring component scan.

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

  <!--This will enable component scanning in the package given and all the subpackages inside of this given package.-->
  <context:component-scan base-package="in.adwait.springdemo" />
</beans>

```

## Container Configuration With Java

We in modern Spring application prefer to use pure java to configure our Spring application. In this third and final method will not use XML.

### @ComponentScan

Configures which packages to scan for classes with annotation configuration.

We can specify the base package names directly with one of the `basePackages` or value arguments where value is an alias for `basePackages`. We can also specify `basePackageClasses` which point to the classes in the base package. Both are arrays and can have multiple packages and classes respectively.

Also multiple `@ComponentScan` can be annotated on the same class as Spring leverages Java8's repeating annotation feature. Thus we can have both `basePackageClasses` and `basePackages` on the same class.

Alternately we can also use `@ComponentScans({...})` to specify multiple `@ComponentScan` inside.

Instead of using `ClassPathXmlApplicationContext` we will be using `AnnotationConfigApplicaionContext`.

```java
public interface MyBeanInterface{
  public String getMessage();
}

@Component
public class MyBean implements MyBeanInterface{
  public MyBean() { }
  public String getMessage() {
    return "Message From MyBean";
  }
}

public class BeanWithOutAnnotation{
  private String message;
  //Constructors, getters and setters.
}

//All the classes marked with @Component and are inside in.adwait.springdemo directory will be available as beans in the context.
@Configuration
@ComponentScan("in.adwait.springdemo")
public class MyConfigurationClass{
  //We will create and return the bean that has no @Component Annotation so that it can be used in the application.
  @Bean(name="myBeanWithoutAnnotation")
  public BeanWithOutAnnotation getBeanWithOutAnnotation() {
    BeanWithOutAnnotation bean = new BeanWithOutAnnotation();
    bean.message = "This bean was created in configuration class";
    return bean;
  }
  //We do not need to create beans with @Component, they are automatically created by Spring.
}

public class Main{

  public static void main(String [] args) {
    //create our annotation context
    AnnotationConfigApplicationContext context = new AnnotationCofigApplicationContext(MyConfigurationClass.class);

    //get bean
    MyBean bean = context.getBean("myBean", MyBeanInterface.class);
    //Use Our bean
    System.out.println(bean.getMessage());

    //get the bean that we created
    BeanWithOutAnnotation bean2 = context.getBean("myBeanWithoutAnnotation", BeanWithOutAnnotation.class);
    //Use bean;
    System.out.println(bean2.getMessage());

    //Close context
    context.close();
  }
}
```

> Note :  The `@ComponentScan` methods will tell Spring to scan for component in the given package. Spring Will revursively scan for components starting at the base package and also can all the sub packages.

## Bean Scope

### Singleton

Singleton is default scope for all the beans created by spring unless specified other wise. Thus it is the most important scope to understand when using spring.

1. Spring container creates only on instance of the bean, by default.
2. It is cached in memory.
3. All request for the bean will return a Shared reference to the same bean.

We can specify explicitely the scope of a bean to be singleton as `<bean id="..." class"..." scope="singleton">`

If we want dont want to use xml configuration and are using java annotations we could use `@Scope("singleton")` over the class to make it a singleton bean.

### Prototype

The Prototype creates a new instance of the classes every time they are needed. Thus multiple instance of the same class are injected.

Use Prototype scope for a bean using XML configuration

```xml
<bean id="myBean"
  class="in.adwait.springdemo.myPrototypeBean"
  scope="prototype"
></bean>
```

Using Annotations to define the scope

```java
@Component
@Scope("prototype")
public class MyBeanClass implements MyBeanInterface{

  //The bean created from this class will be a prototype scoped bean. Thus a new bean will be created every time request is made.
}
```

It is not recommended to use prototype scope for a bean unless in very sepcific requirenments.

### Other bean Scopes

|scope|Description|
|:---:|:---------|
|singleton|Create a single instance of bean.(Default Scope)|
|prototype|Create a new bean instance for each container request|
|request|Scoped to an HTTP web request. Only used for web applicaitions|
|session|Scoped to an HTTP web session.|
|global-session|Scoped to a global HTTP web session|
|websocket|Scoped to a websocket|

### Bean Life-Cycle Methods / Hooks

Container Start -> Bean Instantiated -> Dependencies Injection -> Internal Spring Processing -> Our Custom Init Methods -> Bean is Ready For use -> Container is shut down -> Our custom Destroy method -> End

Bean Lifecycle Methods/Hooks are used to custom code during bean initialization `init-method`. We an use this to call custom business logic methods or setting up handles to resources such as databases or sockets or file systems.

We can also use hooks or lifecycle methods when the beans are destroied `destroy-method`.

The methods specifed below can have any access type(`public`, `protected`, `private`). They can have a return  but the return can never be captured for use, so most commonly `void` is used. The methods should be no-arg.

* With XML configurations

```xml
<!--beanlifeCycle-applicationContext.xml-->
<beans >
<!--When bean is initalized and destoried-->
  <bean 
    id"myBean" 
    class="in.adwait.springDemo.MyBean" 
    init-method="doOnBeanInit"
    destroy-method="doOnBeanDestroied">
  </bean>
</beans>
```

```java
public class MyBean{
  public MyBean() {}

  public void printMessage(String message) {
    System.out.println(message);
  }

  public void doOnBeanInit() {
    //On Bean Init lifecycle method
  }

  public void doOnBeanDestroied() {
    //On Bean Destroied method.
  }
}

//--- Demo App Main class
public class Main{
  public static void main(String[] args) {
    ClassPathXmlApplicationContext context = new ClassPathXmlContext("beanlifeCycle-applicationContext.xml");

    MyBean myBean = context.getBean("myBean", MyBean.class);
    myBean.printMessage("Hello From MyBean");

    context.close();
  }
}
```

> For `prototype` scoped beans, Spring does not call the destroy method. [More on why at spring reference.](https://docs.spring.io/spring/docs/current/spring-framework-reference/core.html#beans-factory-scopes-prototype)

In short : In contrast to the other scopes, Spring does not manage the complete lifecycle of a prototype bean.

So unless you know what you are doing and you are implementing custom code to release resources used by there prototype beans, and there is a good reason to use prototype scope in the first place dont use prototype scope.

* With Java Annotations

> Important : For modularity Java 9+  `javax.annotation` has been removed from its default classpath, so our ide will not be able to import the lifecycle hook annotations for us.
> [Download or add to maven/gradle 'Javax Annotation API'](https://mvnrepository.com/artifact/javax.annotation/javax.annotation-api) to use it in the project if needed to us the lifecycle hooks of the beans.

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

## DI With XML Configuration

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
  <!--Setter Injection-->
  <property name="myServiceVariableName" ref="myService" />

  <!-- Inject literal value-->
  <!--Spring will call the setEmailAddress and setName methods of the class mentioned above.-->
  <property name="emailAddress" value="adwait@adwait.in" />
  <property name="name" value="Adwait" />
</bean>

<!--Reference Values from Properties File `contant.properties below-->
<!--As above we have declared the values direclty when we configure the bean, but we can also reference the values form the properties file. The Injection remains the same as above-->
<bean id="myBean"
class="in.adwait.springdemo.MyBean">

  <property name= "emailAddress" value="${foo.email}" />
  <property name="name" value="${foo.name}" />
</bean>
```

Referenceing values from properties file using xml configuration.

We first have to Load the properties file in the Spring configuration. In `applicationContext.xml` add `<context:property-placeholder Location="classpath:sport.properties"/>` so that Spring can find the properties file. All such properties file that we want to reference values from have to be first declared the in context file.

> `#` is used for comment in .properties files.

```properties
# contact.properties
foo.email=adwait@adwait.in
foo.name=Adwait
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
    this.name = name;
  }

  public String getEmailAddress() {
    return emailAddress;
  }
  
  public String getName() {
    return emailAddress;
  }
}
```

## DI With @Autowired

We can use `@Autowired` Annotation for constrution as well as setter injection by adding the annotation over the constructor or setter.

We have an additional type of injection with the `@Autowired`, directly into a variable by annotating the variable with the annotation called as **Field Injection**

We can also use `@Autowired` Over methods for dependency injection directly into that methods, but this is not recommended.

```java
public class MyBean{
  //---Field Injection
  @Autowired
  private MyService myService; //This will direclty inject the service when the instance is created.
  //This field method works by using reflection.

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
> We can use any method name `@Autowired` to inject a dependecny. But methods injection is not recommeded, using setter or constructor injection is recommended.

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

## Dependency Injection Without Xml

> `@Bean` : We can use `@Bean` to make an existing third-party class available to our Spring framework application context.
.
> We use `@PropertySource` to specify class path for our properties files being used.

```java
//This code is not be perfect and may not run directly. This is to be used as reference only.

public interface MyBeanInterface{
  public String getMessage();
}

@Component
public class MyBean implements MyBeanInterface{

  //--- Getting value From yml or properties files
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
@PropertySource("classpath:credentials.properties")
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
# creadentails.properties
foo.email=adwait@adwait.in
foo.name=Adwait
```

> The `classpath` is the path that the Java runtime environment searches for classes and other resource files.
>
> While using spring boot with maven `resources/` is the classpath where we put our properties files and use as we did above.
>
> We could create directories in the classpath and refer to them to get resources `@PropertySource("classpath:properties/credentials.properties")`
>
> `classpath` is always relative to the classpath root. If you put a `/` at the start of the path, it is silently removed.

If we want to use Spring version 4.2 or lower, it cannot directly access the properties file and we need to specify a special bean for the functionality. The following code registers the required bean to the Spring context.

```java
// add support to resolve ${...} properties
@Bean
public static PropertySourcesPlaceholderConfigurer
                propertySourcesPlaceHolderConfigurer() {

  return new PropertySourcesPlaceholderConfigurer();
}
```

* While using Spring 4.2 and lower we will have to configure Spring manually to get spring to load our properties file. We can simply add the following code to our class marked with `@Configuration` annotaion.

```java
@Bean
public static PropertySourcesPlaceholderConfigurer propertySourcePlaceHolderConfigurer() {
  return new PropertySourcePlaceHolderConfigurer();
}
```

* In Spring 4.3 and higher which we will use most of the times, we do not need the above code.

### @Bean

The `@Bean` annotation tells Spring that we are creating a bean component manually.

Creating a Bean.

```java
@Bean 
public MyBeanInterface myBeanId() {
  MyBean mybean = new MyBean();
  return myBean;
}

/*
* Breaking the code down.
* 1. The Bean annotation tells the Spring that we want it to create a  bean manually.
* 2. The method name in the case myBeanId determines the bean id. The use of MyBeanInterface as the return type helps spring find the dependencies that implement the MyBeanInterface and inject the bean there automatically.
* 3. We manaully create the instance of the class we want.
* 4. We return this instance, so Spring can then inject it where needed.
*/
```

So in the above method every call to the method `myBeanId()` will be intercepted by the Spring Container because of the `@Bean` annotation.

If this is the first time the method is called then the methods will execute as normal and the instance will be stored/registered in the Spring container(applicaionContext) for any further use effectively setting a flag.

Any further call to the method will not execute the method instead Spring will use the instance stored in the Container and inject it as needed.

#### Real-time Use cases for @Bean

We can use the `@Bean` annotation to make an existing third-party class available to our Spring Framework applicaiton context.

As we cannot go into a third party class an add `@Component` Spring will not be able to detect the class and creat beans for Dependency injection. So we manually make it avaiable with `@Bean`.

### @Primary

We use the `@Qualifier` to select bean that will be injected, but we cannot use it when we create the bean during configurartion.

`@Primary` is used to specify the primary bean that will have higher preference of injection if a qualifier is not specified during Autowiring.

```java
@Configuration
public class MyBeanConfiguration{
  @Bean
  @Primary
  public Vehicle getCar() {
    return new Car();
  }

  @Bean()
  public Vehicle getBus() {
    return new Bus();
  }
}

//Both Car and Bus return a type of Vehicle, so whenever we use have to inject into a Vehicle interface declaration the Car bean will be injected as that is marked as primary.
```

### @Order

`@Order` is primarly used in AOP with ApsectJ but can also be used to get beans in an order.

```java
public interface Person{
  public int getStartAge();
}

@Component
@Order(Ordered.LOWEST_PRECEDENCE)
public class Adult implements Person{
  public int getStartAge(){
    return 18;
  }
}
@Component
@Order(2)
public class Teen implements Person{
  public int getStartAge(){
    return 13;
  }
}
@Component
@Order(1)
public class Child implements Person{
  public int getStartAge(){
    return 0;
  }
}

// --- we can then get them as list in some class
@Autowired
private List<Person> person;

//We can access them as which are in the order that we had set them
person.get(0).getStartAge() //-> 0
person.get(1).getStartAge() //-> 13
person.get(2).getStartAge() //-> 18
```

## Advance DI

* We can also Inject Collection From Java.utils by defining them as beans.

### Factory Beans

Spring beans container manages two types of beans, ordinary beans that are used directly and FactoryBean that themselves can create Objects, that are managed by the framework.

FactoryBean is a interface that can be implemented to create a bean that creates objects that are managed by spring container.

```java
//--- This is the FactoryBean interface 
public interface FactoryBean<T> {
  //Returns an object produced by the factory, that will be used by the Spring Contianer
  T getObject() throws Exception;
  //Returns the type of object that this FactoryBean produces.
  Class<?> getObjectType();
  //Denotes if the object produced by this FactoryBean is a singleton
  boolean isSingleton();
}

public class Vehicle{
  private int id;

  //Constructors, Getters, Setters.
}

//Create FactoryBean class
public class VehicleFactory implements FactoryBean<Vehicle> {
  private int factoryId;
  private int vehicleId;

      @Override
    public Tool getObject() throws Exception {
        return new Vehicle(vehicleId);
    }

    @Override
    public Class<?> getObjectType() {
        return Vehicle.class;
    }

    @Override
    public boolean isSingleton() {
        return false;
    }
}

@Configuration
public class BeanConfigurationClass{
  @Bean(name="vehicle")
  public VehicleFactory getVehicleFactory() {
    VehicleFactory factory = new VehicleFactory();
    factory.setFactoryId(10);
    factory.setVehicleId(10);
    return factory;
  }

  @Bean
  public Vehicle vehicle() throws Exception{
    return getVehicleFactory.getObject();
  }
}

//The we can use 
@Autowired
private Vehicle vehicle;
//Will inject the vehicle object from above.
```

### @Lazy

By default, Spring creates all singleton beans eagerly at the startup/bootstrapping of the application context. This prevents any errors at runtime as all beans are already created and avaiable.

But if we want we can use `@Lazy` to create bean on request and not at the start of the application context.

When we put `@Lazy` annotation over the `@Configuration` class, it indicates that all the methods with `@Bean` annotation should be loaded lazily.

```java
@Lazy
@Component
public class City {
    public City() {
        System.out.println("City bean initialized");
    }
}
//@Lazy in both classes is necessary
public class Region {

    @Lazy
    @Autowired
    private City city;

    public Region() {
        System.out.println("Region bean initialized");
    }

    public City getCityInstance() {
        return city;
    }
}
//City bean will only be created when we call the getCityInstance method.
```

### Inject values From Config Files

External Configuration Data can be stored in a YAML file or Properties.

Spring supports YAML documents as an alternative to properties and uses SnakeYAML under the hood to parse them.

A YAML file provides a concise way to store hierarchical configuration data, that is very readable.

We can simply put an `application.properties` file in our `src/main/resources` directory, and it will be auto-detected.

#### @PropertySource

We have previously used `@PropertySource` to load and use values from `.properties` file that are supported by Spring out of the box.

```java
@Configuration
@PropertySource("classpath:credentials.properties")
public class PropertiesWithJavaConfig {
    @Value("${user.name:defaultUserName}")
    private String name;
    @Value("${user.password}")
    private String password;
}

//Using PlaceHolders
@PropertySource({ "classpath:persistence-${envTarget:mysql}.properties"})
//:mysql is the default value and envTarget is the key of enviroment varaible.

//Multiple property locations
@PropertySource("classpath:creadentials.properties"),
@PropertySource("classpath:persistence-${envTarget:mysql}.properties")
public class PropertiesWithJavaConfig{}
//OR
@PropertySources({
    @PropertySource("classpath:creadentials.properties"),
    @PropertySource("classpath:persistence-${envTarget:mysql}.properties")
})
public class PropertiesWithJavaConfig{}

// --- WE can also use the Enviroment Api to get the properties
@Autowired
private Environment env;

dataSource.setUrl(env.getProperty("jdbc.url"));
```

By default `@PropertySource` does not support or load yaml files. We can define a custom `PropertySourceFactory` so that we can load and use yaml files.

As of Spring 4.3, `@PropertySource` comes with the factory attribute. We can make use of it to provide our custom implementation of the `PropertySourceFactory`, which will handle the YAML file processing.

```java
public class YamlPropertySourceFactory implements PropertySourceFactory {

    @Override
    public PropertySource<?> createPropertySource(String name, EncodedResource encodedResource) 
      throws IOException {
        YamlPropertiesFactoryBean factory = new YamlPropertiesFactoryBean();
        factory.setResources(encodedResource.getResource());

        Properties properties = factory.getObject();

        return new PropertiesPropertySource(encodedResource.getResource().getFilename(), properties);
    }
}

@Configuration
@ConfigurationProperties(prefix = "yaml")
@PropertySource(value = "classpath:foo.yml", factory = YamlPropertySourceFactory.class)
public class YamlFooProperties {

    private String name;

    private List<String> aliases;

    // standard getter and setters
}
```

```yaml
yaml:
  name: foo
  aliases:
    - abc
    - xyz
```

### Exceptions

#### UnsatisfiedDependencyException

UnsatisfiedDependencyException gets thrown when, as the name suggests, some bean or property dependency isn't satisfied.

This may happen when spring tries to resolve a mandatory dependency and is unable.

#### NoSuchBeanDefinitionException

This is a common exception thrown by the BeanFactory when trying to resolve a bean that simply isn't defined in the Spring Context.

## Advance Spring

### @Profile

Allowing us to map our beans to different profiles.

```java
//Bean is active/created only when dev profile is active.
@Component
@Profile("dev")
public class DevDatasourceConfig{}

//Bean is active/create only when dev profile is not active, or any other profile is active.
@Component
@Profile("!dev")
public class DevDatasourceConfig{}

//--- Setting profile to be active Programmatically
//--   via WebApplicationInitializer
@Configuration
public class MyWebApplicationInitializer implements WebApplicationInitializer {
    @Override
    public void onStartup(ServletContext servletContext) throws ServletException {
 
        servletContext.setInitParameter(
          "spring.profiles.active", "dev");
    }
}

//-- via ConfigurableEnvironment
@Autowired
private ConfigurableEnvironment env;

env.setActiveProfiles("someProfile");
```

We can also set the profile in Maven `pom.xml` file and `application.properites` file.

### @DependsOn

Initialize other beans before the annotated one. Mostly this annotation is not needed.

```java
@DependsOn("engine")
class Car implements Vehicle {}

@Bean
@DependsOn("fuel")
Engine engine() {
    return new Engine();
}
```

## Spring MVC

Model-View-Controller

[Spring MVC Official Docs](https://docs.spring.io/spring-framework/docs/current/reference/html/web.html)

Basic flow of MVC : WebBrowser -> Front Controller -> Controller -> View template -> Back to WebBrowser

Responsibilities of FrontView Controller

* Intercepts incoming requests
* Converts the payload of the request to the internal structure of the data
* Sends the data to Model for further processing
* Gets processed data from the Model and advances that data to the View for rendering

The `DispatcherServlet` acts as the main controller to route requests to their intended destination

Components of a Spring MVC Application

* A set of web pages to layout UI components.

* A collection of Spring beans (controllers, services, etc).

* Spring configurations.

**Spring MVC Front Controller**: It is also known as Dispatcher Servlet. It is a part of the Spring Framework and is already implemented.

**Container** contains the buisness Logic and handles the requests, stores/retrieves data from database or other webservices and place data in Models.

**Model** Containes our data. We place our data in the model. This data can be any Java Object or Collection.

**View Template** Spring is very flexible in the use of third party view template.

When we want to create a new Spring MVC project we select `web project` in the IDE such as Ecplise or Intellij, this will get us started with folder structure suited for web applications.

### Configuring Spring MVC with XML

While using Spring MVC we would want to serve pages that need to be created. There might also be static resources that need to be stored and used.

Lets say in this case we store all this in a package named `WebContent`. `WebContent` will have two main folders `META-INF` that will store meta data for the web and `WEB-INF` which will store all the configuration files that we create below. It will also contain the servlet dependencies.

When servelet dependencies or jar files are placed inside of the `WEB_INF` they do not need to be add to class path, they are automatically added.

Spring MVC configuration with xml is done with the help of two files `web.xml` and `spring-mvc-demo-serverlet`. They are added to the `WEB_INF` folder.

Configuring with xml is the old methods and so we will not go into unnecessary details about the configuration with xml.

The base code for the above files is as given in following starter files.

```xml
<!-- web.xml -->
<?xml version="1.0" encoding="UTF-8"?>
<web-app xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
  xmlns="http://xmlns.jcp.org/xml/ns/javaee"
  xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
  id="WebApp_ID" version="3.1">

  <display-name>spring-mvc-demo</display-name>
  <absolute-ordering />
  <!-- Spring MVC Configs -->

  <!-- Step 1: Configure Spring MVC Dispatcher Servlet -->
  <servlet>
    <servlet-name>dispatcher</servlet-name>
    <servlet-class>org.springframework.web.servlet.DispatcherServlet</servlet-class>
    <init-param>
    <param-name>contextConfigLocation</param-name>
    <param-value>/WEB-INF/spring-mvc-demo-servlet.xml</param-value>
    </init-param>
    <load-on-startup>1</load-on-startup>
  </servlet>

  <!-- Step 2: Set up URL mapping for Spring MVC Dispatcher Servlet -->
  <servlet-mapping>
    <servlet-name>dispatcher</servlet-name>
    <url-pattern>/</url-pattern>
  </servlet-mapping>

</web-app>

<!-- spring-mvc-demo-serverlet.xml -->
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
  xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" 
  xmlns:context="http://www.springframework.org/schema/context"
  xmlns:mvc="http://www.springframework.org/schema/mvc"
  xsi:schemaLocation="
    http://www.springframework.org/schema/beans
      http://www.springframework.org/schema/beans/spring-beans.xsd
      http://www.springframework.org/schema/context
      http://www.springframework.org/schema/context/spring-context.xsd
      http://www.springframework.org/schema/mvc
        http://www.springframework.org/schema/mvc/spring-mvc.xsd">

  <!-- Step 3: Add support for component scanning -->
  <context:component-scan base-package="com.luv2code.springdemo" />

  <!-- Step 4: Add support for conversion, formatting and validation support -->
  <mvc:annotation-driven/>

  <!-- Step 5: Define Spring MVC view resolver -->
  <bean
  class="org.springframework.web.servlet.view.InternalResourceViewResolver">
    <property name="prefix" value="/WEB-INF/view/" />
    <property name="suffix" value=".jsp" />
  </bean>

</beans>
```

### Configuring Spring MVC with Java Code

#### @EnableWebMVC

Provides similar Support to `<mvc:annotation-driven />` in XML.

It also adds support for validation, formatting and conversion.

It also processes `@Controller` classes and `@RequestMapping` etc methods.

#### Configuration Code

Spring MVC provides support for web app initailization, that detects our code automatically. The class `AbstractAnnotationConfigDispatcherServletInitializer` is used to initialize the servlet container.

So we extend the base class and then override all required methods and then specify servlet mapping and location of our app config.

```java
//--- Replaces spring-mvc-demo-servlet.xml
@Configuration
@EnableWebMvc
@ComponentScan(basePackage="in.adwait.project")
public class AppConfig{
  @Bean
  public ViewResolver viewResolver(){
    InternalResourceViewResolver viewResolver = new InternalResourseViewResolver();

    //This will help spring to map to the view-page like /WEB-INF/view/login.jsp.
    //So when we provide login viewResolver will automatically link to the page.
    viewResolver.setPrefix("/WEB-INF/view/");
    viewResolver.setSuffiex(".jsp");

    return viewResolver;
  }
}
//--- We could `implements WebMvcConfigurer` to further configure the contoller by overriding required method.

//--- Replace web.xml
import org.springframework.web.servlet.support.AbstractAnnotationConfigDispatcherServletInitializer;

public class SpringMvcDispatcherServletInitialzer extends AbstractAnnotationConfigDispatcherServletInitializer () {
  @Override
  protected Class<?>[] getRootConfigClasses() {
    return null;
  }

  @Override
  protected Class<?>[] getServletConfigClasses() {
    return new Class[]( AppConfig.class );
  }

  @Override
  protected String[] getServletMappings() {
    return new String[] { "/" };
  }
}
```

> With **Spring Boot**, we can set up frontend using Thymeleaf or JSP's without using `ViewResolver`. By adding `spring-boot-starter-thymeleaf` dependency to our `pom.xml`, Thymeleaf gets enabled, and no extra configuration is necessary.

Now we have configured our server the same way as we had done with the above xml configuration.

If we are using maven, the maven will complain about missing web.xml file.

```xml
<!-- pom.xml -->
<!-- As we are not using the web.xml file and using java configuration instead maven will complain that it is missing. -->
<!-- We make use of a maven plugin to address that. -->
<pluginManagement>
  <plugins>
    <plugin>
      <!-- Coordinates for maven-war-plugin -->
      <groupId>org.apache.maven.plugin</group>
      <artifactId>maven-war-plugin</artifactId>
      <version>3.2.0</version>
      <!-- responsible for collecting all artifact dependencies, classes and resources of the web application and packaging them into a web application archive -->
    </plugin>
  </plugins>
</pluginManagement>
```

### @Controller and @RequestMapping

The `@Controller` annotation inherits from the `@Component` and hence all Controllers are also Components that will get scanned automatically by Spring.

`@RequestMapping` is used on the methods to give the request that will activate the methods so that the request can be processed and an appropriate reply can be sent.

Marks request handler methods.

Properties used to configure `@RequestMapping` are path/name/value, params, headers, consumes, producesn method.

```java
@RequestMapping(
  value = "/ex/foos/{id}", //can have path variables 
  headers = { "key1=val1", "Accept=application/json" }, //What the method expects
  method = GET, //Or it could also be method = RequestMethod.GET
  produces = {"application/json", "application/xml" } //what this method will produce
)

//-- Request Mapping, fallback for all requests
@RequestMapping(value = "*", method = RequestMethod.GET) //For all get methods

//-- Multiple requests
@RequestMapping(
  value = { "school/student/id", "college/student/id" }, 
  method = GET)

//-- Multiple Methods
@RequestMapping(
  value = "school/student/{id}", 
  method = { RequestMethod.PUT, RequestMethod.POST }
)
```

#### Aliases for @RequestMapping

* @GetMapping
* @PostMapping
* @PutMapping
* @DeleteMapping
* @PatchMapping

#### @RequestMapping on Class

`@RequestMapping` can also Serves as a parent mapping for the controller if we put the annotion below the `@Controller` annotation.

For very simple applications this might not be necessary, this serves best when there are conflict of path between two controllers.

All request mapping on methods in the controller are relative to the controller's request mapping.

#### Serving Page

As we have set up the server configuration to serve pages, the following request mapping will serve the `.jsp` pages in the resources that we have created.

```java
@Controller
public class HomeController {
  
  @RequestMapping("/")
  public String showPage() {
    return "homePage"; //This is the name of the page that is returned.
  }

  //--- Lets say we want to show form and get data.
  @RequestMapping("/shoFrom")
  public String showFrom() {
    return "showForm";
  }

  @RequestMapping("/processForm")
  public String processFormData() {
    return "successMessage";
  }
}
```

```jsp
<!-- homePage.jsp -->
<html>
  <head><title>Home</title>Home Page</head>
  <body><a href="/showFrom"> Fill out a Form</a></body>
</html>

<!-- showFrom.jsp-->
<html>
  <body>
    <form action="processForm" method="GET"> 
      <input type="text" name="studentName" placeholder ="Student Name"/>
      <input type="submit" />
    </form>
  </body>
</html>

<!-- successMessage.jsp -->
<html>
  <body> 
    From Submitted Successfully. <br>
    <!--Below we read the data from the above form-->
    Student Name Submitted is ${param.studentName}
  </body>
</html>
```

### Model

Models are used to store data for the given request.

We have already defined the `.jsp` pages above and we will use the same here. The `.jps` pages include the form from which data will be retrieved and stored in the model.

```java
//---In the above example we just took the data and displayed it, in this example we will process the data and add it to Model
@RequestMapping("/processFromVersionTwo")
public String customMessage(HttpServletRequest request, Model model) {
  //HttpServletRequest is just the normal request that we get from the browser.

  //Model is just a container that can hold our data.

  // Read the request parameters from the Html Form
  String name = request.getParameter("studentName");

  //Create custom Message with the name
  String mesg = "Hello " + name + ", We hope you are having a wonderful day.";

  //Add the message to the Model
  model.addAttribute("message", mesg);
  /*
   * Model holds values as key value pair.
   * Above "message" string is passed as a key and the mesg variable is passed as value. 
   * We can add as many attributes to the model as we want, also Model varaible can have any name.
  */
  return "successMessage" //Page returned
}
```

As discussed above Model holds data for us. We can use this data in the page that is returned my the request method.

```jsp
<!-- In the form we need to change the request as we have changed the name of the request in the controller -->
<form action="processFromVersionTwo" method="GET"> 

<!-- successMessage.jsp -->
<html>
  <body>
    There's a Message for you. ${message}
    <!--We use the key from the model to get the value-->
  </body>
</html>
```

We can also add maps to the Model with `mergeAttributes(map)`

```java
Map<String, String> map = new HashMap<>();
map.put("user1", "Ram");
map.put("user2", "Lakshman");
model.addAttribute("message", "Welcome");
model.mergeAttributes(map);
```

#### ModelMap

Like Model, ModelMap can also be used to pass values to the view.

ModelMap gives us the ability of passing  a collection of values and treat it as if it was a map.

```java
@GetMapping("/welcome")
public String passModelMap(ModelMap map) {
    map.addAttribute("welcomeMessage", "welcome");
    map.addAttribute("user", "Parul");
    return "index";
}
```

#### ModelAndView

```java
@GetMapping("/student")
public ModelAndView modelAndView() {
    ModelAndView modelAndView = new ModelAndView("index");
    modelAndView.addObject("message", "Welcome");
    modelAndView.addObject("user", "Adwait");
    return modelAndView;
}
//WE can then use model veiw as we used Model and ModelMap
```

### @RequestParam

In the above example we use the `HttpServletRequest` to get the request directly. We then used the request to get and assign the form data that was send as a url parameter to a varaible that we could use.

With `@RequestParam` we can directly map the url paramter to a varaible and use it in the method.

Accessing HTTP request parameters like `localhost:8080:/processFormVersionTwo?studentName=adwait`.

```java
//The same methods as above but using @RequestParam
@RequestMapping("/processFormVersionTwo")
public String customMessage(@RequestParam("studentName") String name, Model model) {
  //Now we do that same as we did in the above example.
  String mesg = "Hello " + name + ", We hope you are having a wonderful day."
  model.addAttribute("message", mesg);
  return "successMessage"
}

//-- Set Defualt value, or if the value is required
@RequestParam(name="studentName", defaultValue = "Adwait", required=false) String name
//-- Mapping All parameters 
@RequestParam Map<String,String> allParams
//-- Mapping multi-value parameter like /?id=1,2,3 or ?id=1&id=2&id=3
@RequestParam List<String> id
```

### @RequestBody

Maps Body of the HTTP request to an object.

The deserialization is automatic and depends on the content type of the request.

```java
@PostMapping("/save")
void saveStudent(@RequestBody Student student) {
    // ...
}
//By default the @RequestBody must correspond to the JSON sent from the client.
```

### PathVariable

Method argument is bound to a URI template variable.

```java
@RequestMapping("/{id}")
Student getStudent(@PathVariable("id") int id) {
    // ...
}

//---Multiple Path variables
@RequestMapping(value="/{school}/students/{id}")
public Student getStudent(
  @PathVariable String school, 
  @PathVarible("id") int studentId
){
  //...
}

//We can also specify if it is not required
@PathVariable(required = false) long id
```

Similarly we can also access `@CookieValue` and `@RequestHeader`.

### @ResponseBody

Spring treats the result of the method as the response itself.

If we annotate a `@Controller` class with this annotation, all request handler methods will use it.

```java
//--- This will sent ths String that is returned as the response body.
@ResponseBody
@RequestMapping("/welcome")
String welcomeMessage() {
    return "Welcome To My Website!";
}

//--- If the method on which response body is placed is a class, the reponse body will be a json.
public class Student{
  private int id;
  private String name;
  private int age;
  //Constructor, Getters, and Setters
}
//Method
@PostMapping("/response")
public Student studentDetails(@RequestParam int id){
  //Get student from db with the id. But here we will just send a new student.
  return new Student(id, "Mary", 13);
}
//--- This will seralize the class Student and send as JSON.
```

We can change the response type of the `ResponseBody` by explicitly stating how the response body needs to be formatted.

`@PostMapping(value = "/content", produces = MediaType.APPLICATION_JSON_VALUE)`, or we can use `application/json` directly. And there are other media types such as `APPLICATION_XML_VALUE`, that also could be used.

### @ResponseStatus and @ExceptionHandler

`@ResponseStatus` specify the desired HTTP status of the response.

`@ExceptionHandler` we can declare a custom error handler method. Spring calls this method when a request handler method throws any of the specified exceptions.

```java
@ExceptionHandler(IllegalArgumentException.class)
@ResponseStatus(HttpStatus.BAD_REQUEST)
void onIllegalArgumentException(IllegalArgumentException exception) {
    // ...
}
```

### @RestController

The `@RestController` combines `@Controller` and `@ResponseBody`.

```java
@RestController
@RequestMapping("students")
public class SimpleBookRestController {
  //In any methods in the class we do not need To annotate with @ResponseBody
  @GetMapping("/{id}", produces = "application/json")
  public Student getStudent(@PathVariable int id) {
      return findStudentById(id); //Returns a Student instance/object
  }
}
```

### @ModelAttribute

Aaccess elements that are already in the model of an MVC `@Controller`.

### @CrossOrigin

Enables cross-domain communication.

### Form Tags and Data Binding

Spring MVC provides us with Form Tags that can be used with our regular HTML in the `.jsp` files that will help us with data binding. Data binding helps in automatically setting, retrieving data from a Java Object or Bean.

To Reference Spring MVC Form Tags we use `<%@ taglib prefix="form" uri="http://www.springframework.org/tags/form" %>`.

There are many form tags provided by MVC that we can find [here](https://docs.spring.io/spring-framework/docs/5.0.2.RELEASE/spring-framework-reference/web.html#mvc-view-jsp-tags).

* Text Input

In the Spring Controller we have to add a model attribute, this is a bean that will hold form data for the data binding.

```java
public class Student{
  private String firstName;
  private String lastname;
  //getter and setters for both firstName and lastName
}

//--- Inside the contoller class
//This is the request that will serve the Form that the user can see and fill.
@RequestMapping("/showForm")
public String showForm(Model model) {
  //Here we give the key the same name as what our form's modelAttribute will use. It is important for databinding that they have the same name.
  model.addAttribute("student", new Student());

  return "student-form";
}

//Handling the submitted data in controller
@RequestMapping("/processForm")
public String processForm(@ModelAttribute("student") Student student) {
  //log input data
  System.out.println("Student Name: " + student.firstName + " " + student.lastName);

  return "student-confirmation";
}
```

```jsp
<!--student-from.jsp-->
<%@ taglib prefix="form" uri="http://www.springframework.org/tags/forms" %>

<html><body>
  <form:form action="processForm" modelAttribute="student">
    <!--Following input will call the getFirstName() of the student  instance when the form is loaded -->
    <!--When the form is submitted this will call the setFirstName  (valueInputByUser) of the student instance.-->
    First Name: <form:input path="firstName" />
    <br>
    Last Name: <form:input path="lastName" />
    <br>
    <input type="submit" value="Submit" />
  </form:form>
</body></html>

<!--student-confiramtion.jsp-->
<html>
  <body>
    The student with Name : ${student.firstName} ${student.lastName} has been confirmed.
    <!--We have to understand here that student used above to get firstName and lastName comes from the model and we use the key("student") to reference the student's value-->
  </body>
</html>
```

* Drop Down Lists

```jsp
<form:select path="country">
  <!--Value and label can be different Strings-->
  <form:option value="Brazil" label="Brazil" />
  <form:option value="Russia" label="Russia" />
  <form:option value="India" label="India" />
  <form:option value="China" label="China" />
  <form:option value="South Africa" label="South Africa" />
</from:select>
```

```java
//--- In Student class
private String country;
//getter and setter for country
```

So now we can reference the country selected as we did with all the other attributes of student as `${student.country}` in `.jsp` file and with `@ModelAttribute("student") Student student` in the java code.

WE might not wnat to hard code the values of the countries available in the form in the jsp file itelf. For this we can use a `Map` and provide the form with the values from that Map.

```java
//We create a map of values for countries that we want to make avaiable
public class Student{

  private String firstName;
  private String lastName;
  private LinkedHashMap<String, String> countries; 

  public Student() {
    countries = new LinkedHashMap<>();

    countries.put("BR", "Brazil");
    countries.put("RU", "Russia");
    countries.put("IN", "India");
    countries.put("CN", "China");
    countries.put("ZA", "South Africa");
  }
  //Getteres and Setters for all private properties
}
```

```jsp
<!--So when the form is loaded this will call the getCounties() method to load in the values-->
<form:select path="country">
  <form:options items="${student.countries}" />
</form:select>
```

* Radio Button

```jsp
Java <form:radiobutton path="language" value="Java">
JavaScript <form:radiobutton path="language" value="JavaScript">
C# <form:radiobutton path="language" value="CSharp">
C++ <form:radiobutton path="language" value="Cplusplus">
```

So in the student class we just add a language property and the radio button will bind with that language property and can be accessed from there.

Similar to `select` tag we can populate the `radiobuttons` from Java class. We create a similar `Map` as we created for select and the use the values in our `.jsp` file.

`<form:radiobuttons path="language" items="${student.languages}" />

* Check Boxes

As check boxes can be used to select multiple options it retruns a collection of data. So this collection is in the form of String array in the Java controller.

```jsp
Which of the following operating system can you use?

Linux <form:checkbox path="operatingSystems" value="linux" />
Mac <form:checkbox path="operatingSystems" value="Mac" />
Windows <form:checkbox path="operatingSystems" value="Windows" />

<!--Output.jsp-->
<!--We need to loop over the result hence we get the functionality from the following link to jstl - core -->
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>

<html>
  <body>
    Operating System :
      <ul>
        <c:forEach var="temp" items="${student.operatingSystems}" >
        <li> ${temp} </li>
        </c:forEach>
      </ul>
  </body>
</html>
```

```java
public class Student{
  //--all other properties
  private String[] operatingSystems;

  //Getters and setters for all properties
}
```

### Spring MVC Validation

When we get data from a from we ideally want to check if the data that we recieved is what we expected from the user. For example where we expected and email, it conforms to what an email noramlly is or date of birth is less than the current date etc.

This is where Spring MVC Validation help us.

Java's Standard Bean Validation API is only a specification and is vendor independent and hence portable, thus we need to select a vendor that will provide us with the Validator implementation.

We will use [Hibernate Validation](https://hibernate.org/validator/) that is a package independent of Hibernate and is specialized only for Validation.

Hibernate validator 6.2 is based on Java EE and version later than that are based on Jakarta EE. So we want to make sure that our version of spring supports Jakarta EE or is based on Java EE.

We here will use [Hibernate Validator 6.2](https://hibernate.org/validator/releases/6.2/).

* Required Fields Validation

```java

public class Customer{

  private String firstName;

  @NotNull(message="is Required")
  @Size(min=1, message="is Required")
  private String lastName;
  //The user can still provide just whitespace and the validation will pass. We can solve this issue with @InitBinder and WebDataBinder to preprocess all Strings comming into request and trim them off whitespaces with the SpringTrimmerEditor. But this has a catch, Every time the request is made this method is called, that might show the application. So it is better to do the trimming in the front end and validate it when the request is made in the backend.
}

//--- Controller Class
//The @Valid will tell Spring to perform validation on the model customer and the result of the validation will be placed inside of the BindingResult.
@RequestMapping("/processForm")
public String processForm(@Valid @ModelAttribute("customer") Customer customer, BindingResult bindingResult){
  if(bindingResult.hasError()) {
    return "customer-form"; //return to form
  }
  else {
    return "customer-confirmation"; //Show success page
  }
}
```

> Note that The `BindingResult` must come immediately after the `@ModelAttribute` else this will not work as desired. If they are passed at any other point, the validation will be completely ignored by spring.

```jsp
<style>
  .error{
    color:"red";
  }
</style>

<form:form action="processFrom" modelAttribute="customer">
  First Name : <form:input path="firstName" />
  <br>
  Last Name : <form:input path="lasttName" />
  <!--The errors tag shows when there are errors and will display the message that we had set with the validator annotation in the Customer class-->
  <form:errors path="lastName" cssClass="errors" />
  <!--In the above we define give the form tag a css class named 'error'. we define the style for the class above.-->
  <br>
  <form:input type="submit" value="Submit" />
```

* Number Range Validation

This will help us validate whether a number is between minimum and maximum value.

All the other use of the validator in the controller and the views remain the same as we have seen for the required validation.

```java
public class Student{

  @Min(value=6, message="Age Must be greater than or equal to 6years")
  @Max(value=20, message="Age Must be less than or equal to 20years")
  private int age;

  //Getters And Setters

  //If we want to make the above field required and we simply add the @NotNull annotation above the field, it will give us an error when the user does not enter the number.

  //Spring in the background will try to convert and empty string into a primitive int and it will fail, thus giving us an error that String cannot be converted to int.

  //To Solve this we just use the Integer class to define the field type
  @NotNull(message="Required")
  @Min(value=6, message="Age Must be greater than or equal to 6years")
  @Max(value=20, message="Age Must be less than or equal to 20years")
  private Integer age;
  //So now when there is an empty String it will be converted to Null and thus will add the message to the BindingResult.
}
```

We Still have not handled error if the user enters a non integer value. We can handle the error using spring error handling and assigning a custom message whenever the String to number conversion fails on the above field.

We first create a new folder name `resources` in the `src` directory. In this folder we create a file `messages.properties`. The name of the folders and files and the location of this file is important as Spring will automatically look for these files while it is trying to handle the Validation error.

```properties
# messages.properties

typeMismatch.student.age=Please Enter a Number
```

The formate in the properties file is *error-code + . + object-name + . + field*.

We also now need to make spring aware of the file that we have created and create a bean so that Spring can use these messages

```xml
<!--Inside WEB-INF/spring-mvc-demo-servlet.xml-->
<bean id="messageSource" class="org.springframework.context.ResourceBundleMessagesSource">
  <property name"basenames" value="resources/messages" />
</bean>
```

We can even generalize the messages for just the error-code or error-code and object-name. We can check the possible error code by logging the `BindingResult` to the console and checking the possible error code.

For more information on [error code resolve](http://docs.spring.io/spring/docs/current/javadoc-api/org/springframework/validation/DefaultMessageCodesResolver.html).

* Using Regular Expression for Validation

We use the `@Pattern(regexp="", message="")` to Validate data with regular expression.

```java
public class Student{
  //Other properties

  @Pattern(regexp="^[\S|\D]\S*@\S*\.(?:(?:com)|(?:in)|(?:org))$", message="Not a valid email id")
  private String eamilId;
}

//There are no flages used as we are checing fields and the regex is used to match the complete field, if the complete field is not matched, the validation will fail.
```

### Custom Form Validation

First We need to create a custom annotation. We create a custom annotation in Java by using `@interface`, this is not limited to Spring, but is a part of Java itself.

We are creating an annotation that will add a check if the String that is returned by method or a value of the property being populated starts with 'NES'.

And the Annotation will look like `@PrefixCheck(value="NES", message="Must start with NES") private String schoolCourseName;`

So *PrefixCheck* will be the name of the class, that defines the Annotation.

```java
//-@Constraint: Defines the class that will hold the buisness logic for the annotation
//-@Target: Defines where the annotation can be used, in this case over a method or a varible/property.
//-@Retention:Defines how long the annotation should be held. In this case we give it RUNTIME so the annotation will be held in the byte code that is compiled and will be used during runtime.
@Constraint(validatedBy=ClassContainingBuisnessLogic.class)
@Target({ElementType.METHOD, ElementType.FIELD})
@Retention(RetentionPolicy.RUNTIME)
public @interface PrefixCheck {

  //Here we define the default values according to our limited need but they can be any according to the need and function of annotation.
  //Not defining the value directly makes the annotaion more flexible.
  public String value() default "NES";

  public String message() default "Must start with NES";

  public Class<?>[] groups() default {};//Here we are not using any grouping

  public Class<? extends Payload>[] payload() default {}; //In this case we are also not using any payloads that give additional information/details about the validation failure(severity, error code, etc).
}

import javax.validation.ConstraintValidator;
import javax.validation.ConstraintValidatorContext;

//The ConstraintValidator has generic filled with our annotation name and the string data that we are trying to validate.
public class ClassContainingBuisnessLogic implements ConstraintValidator<PrefixCheck, String> {
  private String coursePrefix;

  @Override
  public void initialize(PrefixCheck prefixCheck) {
    coursePrefix = prefixCheck.value();
  }

  @Override
  public boolean inValid(String theStringToBeChecked, ConstraintValidatorContext constraintValidatorContext) {
    boolean result;

    if(theStringToBeChecked != null) {
      result = theStringToBeChecked.startsWith(coursePrefix);
    }

    else result = true;

    return result;
  }
}
```

### Access Static resources in Spring MVC

Any Static resource is processed as a URL Mapping in Spring MVC. We can configure Spring to reference to static resources.

We first create a folder in the Webcontent folder where we have `WEB-INF` and `META-INF` folder and name it `resources`. It can be named as we wish such as `assets`.

Using XML config. we make Spring MVC aware of this folder from where we want static resources to be served.

`<mvc:resources mapping="/resources/**" location="/resources/"></mvc:resources>`

Now Spring MVC is aware of the static resources in the resource folder and all its subfolders.

Now we can access the resources and assets from the folder by referencing them in the `.jsp` files.

`<img src="${pageContext.request.contextPath}/resources/images/img.png">`

 `<link rel="stylesheet" type="text/css" href="${pageContext.request.contextPath}/resources/css/index.css">`

`<script src="${pageContext.request.contextPath}/resources/js/index.js"></script>`

We need to use `${pageContext.request.contextPath}` to acccess the correct root directory for our web application.

We can add the folder we want to serve static resources from by using java configuration.

```java
@Configuration
@EnableWebMvc
public class MvcConfig implements WebMvcConfigurer {
    @Override
    public void addResourceHandlers(ResourceHandlerRegistry registry) {
        registry
          .addResourceHandler("/resources/**")
          .addResourceLocations("/resources/");
    }
}
```

## Hibernate

Hibernate is a Object relational mapping tool used to provide a framwork for mapping object oriented domain model with a relational database. It is developled by Red Hat.

Hibernate uses JDBC(Java Database Connectivity) in the background to communicate with the database in the background.

Hibernate is an implementation of the JPA specification. JPA is a API specification while Hibernate is a framework that implements JPA specifications.

### Basic concepts

#### Session

[Session](https://docs.jboss.org/jbossas/javadoc/7.1.2.Final/org/hibernate/Session.html) : Hibernate session is an interface that defines the main runtime interface between Java application and Hibernate. The central API class abstracting the notion of persistence service.

The lifecycle of a Session is bounded by the beginning and end of a logical transaction. (Long transactions might span several database transactions.)

The main function of the Session is to offer create, read and delete operations for instances of mapped entity classes. Instances may exist in one of three states.

* transient: never persistent, not associated with any Session
* persistent: associated with a unique Session
* detached: previously persistent, not associated with any Session

#### SessionFactory

The main contract here is the creation of `Session` instances. Usually an application has a single `SessionFactory` instance.

The internal state of a SessionFactory is immutable. This internal state includes all of the metadata about Object/Relational Mapping.

[SessionFactory official Docs.](https://docs.jboss.org/jbossas/javadoc/7.1.2.Final/org/hibernate/SessionFactory.html)

### Setting up Hibernate

First we need to download [Hibernate](https://hibernate.org/orm/).

We will also need the driver/connector from the database we want to connect to with hibernate.

Say we want to connect with My-SQL database we will download the connector/driver from [MYSQL Connectors](https://www.mysql.com/products/connector/).

Similarly there are drivers for [Postgresql](https://jdbc.postgresql.org/download.html).

We then add all the jar files provided by the connector/drivers and the required files from the hibernate to the class path of our project. We could also add the same to maven if we are using maven.

Once we have the database of our choice running we can test our connection with the database with the following simple program. We will use MySql in the following example but any database should work the same.

```java
public class TestJDBC {
  public static void main(String[] args) {
    String jdbcURL = "jdbc:mysql://localhost:3306/students_tracker?useSSL=false";// We give the link a parameter so that MySQL does not give us a warning.

    String user = "student";
    String pass = "student_password";

    try{
      System.out.println("Connecting to database\n");

      Connection myConn = DriverManager.getConnection(jdbcURL, user, pass);

      System.out.println("Connection Successful");
    }catch(Exception exp) {
      exp.printStackTrace();
    }
  }
}
//If the program executes successfully without any errors that means that we have successfully established a connection with our database using hibernate and jdbc.
```

### Hibernate Configuration With XML

We will place the hibernate configuration file `hibernate.cfg.xml` in the src folder of the project.

The following is a example of the xml configuration for hibernate to communicate with a sql data base.

```xml
<!DOCTYPE hibernate-configuration PUBLIC 
  "-//Hibernate/Hibernate Configuration DTD 3.0//EN"
  "http://www.hibernate.org/dtd/hibernate-configuration-3.0.dtd"
>

<hibernate-configuration>
  <session-factory>

    <!-- JDBC Database connection settings -->
    <property name="connection.driver.class">com.mysql.jdbc.Driver</property>
    <property name="connection.url">jdbc:mysql://localhost:3306/students_tracker?useSSL=false</property>
    <property name="connection.username">students</property>
    <property name="connection.password">students_password</property>

    <!-- JDBC connection pool settings using build in test pool -->
    <property name="connection.pool.size">1</property>

    <!-- Select our SQL dialect -->
    <property name="dialect">org.hibernate.dialect.MySQLDialect</property>

    <!-- Echo the SQL to stdout -->
    <property name="show-sql">true</property>

    <!-- Set the current session context -->
    <property name="current_session_context_class">thread</property>
  </session-factory>
</hibernate-configuration>
```

* Usage

```java
SessionFactory factory = new Configuration()
                            .configure("hibernate.cfg.xml") //this is the default filename and if we are using the default name we do not need tospecify this.
                            .addAnnotatedClass(Student.class)
                            .buildSessionFactory();

Session session = factory.getCurrentSession();
```

Users using java 9 and higher will encounter a error as recent version of java have removed `java.xml.bind` from their default classpath.

### Hibernate Configuration With Java

The small java based setup we had in the above Setting up Hibernate works fine, but if we want more control over the configuration like we had with the Xml based configuration we can use the following

```java
@Configuration
@EnableTransactionManagement
public class HibernateConfiguration{

  @Bean
  public LocalSessionFactoryBean sessionFactory() {
    LocalSessionFactoryBean sessionFactory = new LocalSessionfactoryBean();
    sessionFactory.setDataSource(dataSource());
    sessionFactory.setPackageToScan({"in.adwait.project.hibernate.model"});
    sessionFactory.setHibernateProperites(hibernateProperties());

    return sessionFactory;
  }

  @Bean
  public DataSource dataSource() {
    BasicDataSource dataSource = new BasicDataSource();
    dataSource.setDriverClassName("com.mysql.jdbc.Driver");
    dataSource.setUrl("jdbc:mysql://localhost:3306/students_tracker?useSSL=false");
    dataSource.setUserName("students");
    dataSource.setPassword("students_password");
    dataSource.setMaxActive(1);//Set max poolsize- max active connection
    
    return dataSource;
  }

  @Bean
  public PlatformTranasactionManager hibernateTransactionManager() {
    HibernateTransactionManager transactionManager = new HiberanteTranasactionManager();
    transactionManager.setSessionFactory(sessionFactory().getObject());

    return transactionManager;
  }

  private final Properties hibernateProperties() {
    Properties hiberanteProperties = new Properties();
    hiberanteProperties.setProperty("hibernate.dialect", "org.hibernate.dialect.MySQLDialect");
    hiberanteProperties.setProperty("hibernate.show_sql", "true");

    return hibernateProperties;
  }
}
```

* Usage

```java
@Autowired
private SessionFactory factory;

Session session = factory.getCurrentSession();
```

#### @EnableTransactionManagement

Enables Spring's annotation-driven transaction management capability, similar to the support found in Spring's `<tx:*>` XML namespace. To be used on @Configuration classes to configure traditional, imperative transaction management or reactive transaction management.

For more details official docs on [@EnableTransactionManagement](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/transaction/annotation/EnableTransactionManagement.html)

#### LocalSessionFactoryBean

[LocalSessionFactoryBean](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/orm/hibernate5/LocalSessionFactoryBean.html) implements `FactoryBean<SessionFactory>` thus it creates a Hibernate SessionFactory.

This is the usual way to set up a shared Hibernate SessionFactory in a Spring application context; the SessionFactory can then be passed to data access objects via dependency injection.

#### DataSource And BasicDataSource

A factory for connections to the physical data source that this DataSource object represents.

Basic implementation of `javax.sql.DataSource` that is configured via JavaBeans properties.

[DataSource](https://docs.oracle.com/javase/1.5.0/docs/api/javax/sql/DataSource.html).

[BasicDataSource](https://commons.apache.org/proper/commons-dbcp/api-1.2.2/org/apache/commons/dbcp/BasicDataSource.html)

#### PlatformTransactionManager and HibernateTransactionManager

This is the central interface in Spring's imperative transaction infrastructure. Applications can use this directly, but it is not primarily meant as an API.

JdbcTransactionManager, JpaTransactionManager, HibernateTransactionManager are different implementations of the PlatformTransactionManager.

* HibernateTransactionManager

`PlatformTransactionManager` implementation for a single Hibernate SessionFactory. `SessionFactory.getCurrentSession()` gives us the session that we use to communicate with db.

It is transaction manager is appropriate for applications that use a single Hibernate SessionFactory for transactional data access, but it also supports direct DataSource access within a transaction (i.e. plain JDBC code working with the same DataSource). This allows for mixing services which access Hibernate and services which use plain JDBC (without being aware of Hibernate)

[PlatformTransactionManager](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/transaction/PlatformTransactionManager.html).

[HibernateTransactionManager](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/orm/hibernate5/HibernateTransactionManager.html).

### Hibernate Annotaion

We will use annotations to create entity classes that will help us map our java objects to the tables in the batabase.

We use JPA annotation instead of Hibernates own annotation as it is recommended by the hibernate team as best pactice.

JPA is a standard specifcation and hibernate is an implementation of the JPA specification.

Hibernate implements all JPA annotations.

#### Entity LifeCycle

There are different states that an entity can be in or go through during its lifecycle based on the operations being performed.

* Detach : It is not associated with a hibernate session.
* Merge : If instance is detached from session, then merge will reattach it to the session.
* Persist : Transitions new instance to managed state, that is when commit/flush is done save it to the database.
* Remove : Transition managed entity to be removed when next commit is done.
* Refresh : Reload/sync object with data from db.

We need to understand this to understand the cascade type that we will use in the mapping section of hibernate.

#### Example of Simple Entity class

```java
//We want to import the Table and Entity from Javax.persistence. This gives us the standard interface that hibernate implements
@Entity
@Table(name="student")
public class Student {
  //The @Id is used to denote that this property holds a unique id.
  @Id
  @GeneratedValue(strategy=GenerationType.IDENTITY)
  //We don't always have to specify a generate Value. Most databases have a preferred way of generating a unique identity. WE can leverage that to generate the id.
  @Column(name="id")
  private int id;
  //The name represents the name of the property in the database. They can be different or same. If they are the same in class and table we do not need to specify the name for the column, hibernate will infer it from the property name of class.
  @Column(name="first_name")
  private String firstName;

  //Similarly for all entries columns in the database table.

  //We create a no arg argument. This is for hibernate. We can have any number of constructor that we might need.
  public Student() {

  }
  //Getter and Setters for all fields as they all are private.
}
```

### Hibernate CRUD

There are two key components of hibernate that we use to communicate with our database.

* SessionFactory : Reads the hibernate config file, creates session objects. It is created only once and thus is called as a heavy weight object.

* Session : It wraps a JDBC connection and is a short lived object that is it will be used for a method and destoried. It is used to save and retrieve objects. It is created and retrieved from SessionFactory.

In the following all examples we use the xml configuration to set up the `SessionFactory`.

For Java based configuration as we have done above we can just get the factory through autowiring as we have already created a bean of `LocalSessionFactory`.

```java
public static void main(String[] args) {
  SessionFactory factory = new Configuration()
                              .configure("hibernate.cfg.xml") //this is the default file name and if we are using the default name we do not need to specify this.
                              .addAnnotatedClass(Student.class)
                              .buildSessionFactory();

  Session session = factory.getCurrentSession();

  try{
    //--- Save to database
    Student student = new Student("Adwait", "S", "adwait@adwait.in");
    session.beginTransaction();
    session.save(student);
    session.getTransaction().commit();

    //--- Reading object from database table. 
    session = factory.getCurrentSession();
    session.beginTransaction();
    //Finding students id. AS we have already commited to the database the database would have generate the ide that we can retrieve as
    Integer id  = student.getId();
    //If we provide a primary key that does not exist then the returned object will be null.
    Student student2 = session.get(Student.class, student.getId());
    session.getTransaction().commit();

    //--- Query objects with hibernate.
    //Hibernate has its own query language that is very similar to SQL.
    session.beginTransaction();
    //- Query all students in database
    List<Student> students = session.createQuery("from Student").getResultList();
    //- Query Students with last name Bing or first name Joey
    List<Student> student = session.createQuery("from Student s where s.lastName='Bing' OR s.firstName='Joey'").getResultList();
    //- Qery students whoes eamil ends with adwait.in
    List<Student> students = session.createQuery("from Student s where s.email LIKE %adwait.in").getResultList();
    for (Student student : students) {
      System.out.println(student);
    }
    session.getTransaction.commit();

    //--- Update Database
    //- Edit data for one student.
    int studentID = 1;
    Session session = factory.getCurrentSession();
    session.beginTransaction();
    Student student = session.get(Student.class, studentID);
    student.setFirstName("Monica");//Here we make the change in memory, it will update database on commit.
    session.getTransaction().commit();
    //- Edit data for multiple students
    session = factory.getCurrentSession();
    session.beginTranscation();
    session.createQuery("update Student set age='10'").executeUpdate(); 
    session.getTransaction().commit();
    //Assuming that there is a property age for all students, all the students age will now be set to 10. We can have more specific queries.

    //--- Delete
    //- Delete one Student
    int studentID = 1;
    Session session = factory.getCurrentSession();
    session.beginTransaction();
    Student student = session.get(Student.class, studentID);
    student.delete(student);
    session.getTransaction().commit();
    //- Delete student or students with query
    //All other code as above queries
    session.createQuery("delete from Student where id=2").executeUpdate();
    //executeUpdate method is a general method and is used for all updates to database with queries.
  }finally {
    session.close();//We close the session manually here as if there are exception during the execution the session might not close and thus there might be session leaks.
    factory.close();
  }
}
```

Transaction : A transaction generally represents any change in a database. A database transcation symbolizes a unit of work performed within a database management system against a database treated in a coherent and reliable way independent of other transactions.

A transcation is a single unit of logic or work, sometimes made up of multiple operations. Lets take an example of a bank, we transfer money from one account to other, so we retrieve balance amount of both accounts, then substract amount from one account and add it to the other account, the save the values to the database. This will be considered as one transaction.

Database transaction must be

* Atomic : It must either be complete entirely or have no effect otherwise.
* Consistent : They should conform to the existing constrains of the database.
* Isolated : It must not effect other transactions.
* Durable : It must get written to persistent storage.

`session.beginTransaction` is used to start a transaction, where as `session.getTransaction().commit()` is used to make the changes to the database, before we do commit, all the changes that we made in that session are still in the memory and have no effect on the database itself.

> The `list()` method used before hibernate 5.2 is depricated in higher version and now we use `getResultList()` instead like in the following example. Change `session.createQuery("from Students").list()` to `session.createQuery("from Student").getResultList()`.

### Hibernate Mappings

Important Terminology

* Primary Key : Identify a unique row in a table.

* Foreign Key : It links tables together and is a field in one table that refers to primary key in another table.

> Whoever owns the foreign key column gets the `@JoinColumn` annotation, and the other side of the relationship is called the non-owning side.

Main purpose is to preserve relationship between tables also called *Referential Integrity*. It prevents operations that would destroy reationship.

It ensures only valid data is inserted into the foreign key column.

* Cascade :  We can cascade the same operations to the related tables that are linked with mapping. For example we delete a user then we might also want to delete all the comments that were made by that user. This will be known as CASCADE DELETE. We might not want cascade all the time.

* Fetch Type :
Eager will retrieve everthing.
Lazy will retieve data on request.

* Uni-Directional And Bidirectional Mapping : We can have a user and his comments that will have a unidirectional mapping or User is Friend with other user will have a bidirectional mapping.

#### One To One Mapping

One To One Cascade Types

* PERSIST : If entity persisted, related entity will also be persisted. Similarly for all other following cascade types.
* REMOVE
* REFRESH
* DETACH
* MERGE
* ALL

By default no operations are cascaded.

Following example is for a Uni-Directional mapping of Student to Guardian.

```java
//--- Configuring cascade
@Entity
@Table(name="Students")
public class Student {
  @Id
  @GenerateValue(strategy=GenerationType.IDENTITY)
  @Column(name="id")
  private int id;

  //- The name of the column is that which is shown in this table and not the name that is shown in the table that this column links to.
  @OneToOne(cascade=CascadeType.ALL)
  @JoinColumn(name="guardian_id", referencedColumnName="id")
  private Guardian guardian;

  @Column(name="name")
  private String name;

  public Student() {}
  public Student(String name) {
    this.name = name;
  }

  //Other properties, getters and setters
}

@Entity
@Table(name="Guardians")
public class Guardian {
  @Id
  @GenerateValue(strategy=GenerationType.IDENTITY)
  @Column(name="id")
  private int id;

  @Column(name="first_name")
  private String firstName;

  public Guardian() {}

  public Guardian(String firstName) {
    this.firstName = firstName;
  }
  //Getters and setters
}

//We could fine configure mappings to use particular cascades
@OneToOne(cascade={CascadeType.DETACH, CascadeType.MERGE, CascadeType.Persist})

//--- Persisting an entry
public static void main(String[] args) {

  SessionFactory factory = new Configuration().
                            configure("hibernate.cfg.xml")
                            .addAnnotatedClass(Student.class)
                            addAnnotatedClass(Guardian.class)
                            .buildSessionFactory();

  Session session = factory.getCurrentSession();

  Student student = new Student("Adwait");
  Guardian guardian = new Guardian("Jane");
  student.setGuardian(guardian);

  session.beginTransaction();
  session.save(student);
  session.getTransaction().commit();

  session.close();
  factory.close();
  //We should be using try catch to handle exceptions
}
//As the cascade type is set to all in the above example the student as well as the guardian will be saved to the database.
```

We will make changes to the above code and make convert the above example into a Bidirectional mapping.
Only the code below will be changed, all other code remain the same. Also the structure of the database remains the same as was created for the unidirectional mapping.

```java
//We already have the Student class mapped to guardians id column
public class Student{
  @OneToOne(cascade=CascadeType.ALL)
  @JoinColumn(name="guardian_id", referencedColumnName="id")
  private Guardian guardian;
}

public class Guardian{
  @OneToOne(mappedBy="guardian")
  private Student student;
}

/*
 mappedBy tells Hibernate to look at the guardian property in the Student class, use the infromation from the Student class @JoinColumn and help find the associated Student.
*/

//We can also use cascade types with mappedBy.
@OneToOne(mappedBy="guardian", cascade=CascadeType.ALL)
//In this case we might not want to have all operations cascade and thus we could state the required cascade types as we discussed above.

public static void main(String[] args) {
  //all other code as before
  int id = 2;
  Guardian guardian = session.get(Guardian.class, id);

  //Now we can get the student from the guardian.
  Student student = guardian.getStudent();
}
```

Say we want to delete a guardian but not her student. We will then have to change the cascade type.

```java

//-- Guardian class
@(mappedBy="guardian", cascade={CascadeType.DETACH, CascadeType.MERGE, CascadeType.PERSIST, CascadeType.REFRESH})
private Student student;

//-- inside main
int id = 2;
Guardian guardian = session.get(Guardian.class, id);
//Before we can delete a guardian we will have to break the bidirectinal link between the guardian and the student else we will have errors.
guardian.getStudent().setGuardian(null);
session.delete(guardian);
//This commit will update the student and delete guardian from the database.
session.getTransaction().commit();
```

#### @JoinColumn

Official Docs On [@JoinColumn](https://docs.oracle.com/javaee/7/api/javax/persistence/JoinColumn.html#name)

When we use the `@JoinColumn` and give it a name, the table in which the foreign key column is found depends upon the context.

* If the join is for a OneToOne or ManyToOne mapping using a foreign key mapping strategy, the foreign key column is in the table of the sourse entity.
* If the join is for a unidirectional OneToMany mapping using foreign key mapping strategy, the foreign key is in the table of the target entity.
* If the join is for a ManyToMany mapping or for a OneToOne or bidirectional ManyToOne/OneToMany mapping using a join table, the foreign key is in a join table.

#### Many To One Mapping

One to Many mapping is used when we have to map many objects to one object.

* In the following example we will have a course and all its reviews. So If can get from the course all its review and when a course is deleted all the reviews are deleted with the course.

```java
//--- Unidirectional Mapping
@Entity
@Table(name="reviews")
public class Review{
  @Id
  @GenerateValue(strategy=GenerateType.IDENTITY)
  private int id;

  @Column(name="comment")
  private String comment;
}

@Entity
@Table(name="course")
public class Course{
  //other properties

  @OneToMany(cascade=CascadeType.ALL)
  @JoinColumn(name="course_id")
  private List<Review> reviews;
  
  //Constructor

  public void add(Review review) {
    if(review == null) {
      reviews = new ArrayList<>();
    }
    reviews.add(review);
  }

  //Getters and Setters
}
```

* In the following example we will have a teacher and all the courses that that teacher teaches.

```java
//--- Bidirectional mapping
@Entity
@Table(name="teachers")
public class Teacher{

  @Id
  @GeneratedValue(strategy=GenerationType.IDENTITY)
  @Column(name="id")
  private int id;

  @Column(name="name")
  private String name;

  @OnetoMany(mappedBy="teacher", cascade={CascadeType.PERSIST, CascadeType.MERGE, CascadeType.DETACH, CascadeType.REFRESH})
  private List<Course> courses;

  //Constructors

  //Convenience methods for bidirectional relationship
  public void add(Course course) {
    if(courses == null) {
      courses = new ArrayList<>();
    }
    //We will set this teacher as the teacher for this course
    course.setTeacher(this);
    courses.add(course);
  }

  //Getters and Setters
}

@Entity
@Table(name="courses")
public class Course{

  @Id
  @GeneratedValue(strategy=GenerationType.IDENTITY)
  @Column(name="id")
  private int id;

  @Column(name="title")
  private String title;

  @ManyToOne(cascade={CascadeType.PERSIST, CascadeType.MERGE, CascadeType.DETACH, CascadeType.REFRESH})
  @JoinColumn(name="teacher_id")
  private Teacher teacher;

  //Constructor, getter/setter
}

//-- Inside main
//Update the hibernate.cfg.xml to point to the right database connection url.
public static void main(String[] args) {
  SessionFactory factory = new Configuration()
                            .configure("hibernate.cfg.xml")
                            .addAnnotatedClass(Teacher.class)
                            .addAnootatedClass(Course.class)
                            .buildSessionFactory();
  
  Session session = factory.getCurrentSession();

  try{
    //-- Create and save Teacher
    session.beginTransaction();
    Teacher teacher = new Teacher("Rupali");
    session.save(teacher);
    session.getTransaction().commit();

    //-- Create and add course to teacher
    session = factory.getCurrentSession();
    session.beginTranscation();
    int id = 1;
    //We find the teacher in the database that we have already saved.
    Teacher savedTeacher = session.get(Teacher.class, id);
    Course course = new Course("Linear Algebra");
    Course course2 = new Course("Geometry");
    //We add the course to the teacher that was saved.
    savedTeacher.add(course);
    savedTeacher.add(course2);
    //We save the courses to the database
    session.save(course);
    session.save(course2);
    session.getTransaction().commit();

    //-- Get courses for a teacher
    session = factory.getCurrentSession();
    session.beginTransaction();
    id = 1;
    Teacher teacher = session.get(Teacher.class, id);
    List<Courses> course = teacher.getCourses();
    session.getTransaction().commit();

    //-- Delete a course
    //Because of the cascading set teacher will not be deleted.
    session = factory.getCurrentSession();
    session.beginTransaction();
    int courseId = 1;
    Course course = session.get(Course.class, courseId);
    session.delete(course);
    session.getTransaction(course);
    session.getTransaction().commit();
  }finally{
    session.close();
    factory.close();
  }
}
```

#### Eager Vs Lazy Loading With Hibernate Mapping

Eager Loading : Will retrieve/load all dependent entities in the first request for the main entity.

Lazy Loading : Will wait until dependent entities are requested to load them.

Thus when the number of dependent is very high we prefer lazy loading, and thus save the time for the first load.

When the dependent entities are few and we want to work on the dependent entities we will use Eager loading.

Default Fetch Types are applied if we do not specify the FetchType with with our mappings.

* OneToOne : FetchType.EAGER
* OneToMany : FetchType.LAZY
* ManyToOne : FetchType.EAGER
* ManyToMany : FetchType.LAZY

Let take the example of Teacher and Course thought by that Teacher.

```java
@Entity
@Table(name="Teachers")
public class Teacher{
  //all other properties

  @OneToMany(fetch=FetchType.LAZY, mappedBy="teacher")
  private List<Course> courses;

  //...
}
```

Lazy loading needs that the session be kept open to fetch the data as needed. If the session is closed, hibernate will throw an exception `LazyInitializationException`.

The first solution is to fetch all the required data before the session closes.

Or, Lazy Loading with Hibernate Query after the session is closed.

```java
//We can also use Hibernate queries to retrieve data
int id  = 1;

//import from org.hibernate.query.Query
Query<Teacher> query = session.createQuery("select i from Teacher i JOIN FETCH i.courses where i.id=:teacherId", Teacher.class);

//Set the parameter for the query that we have created above will map to id=:teacherId.
query.setParameter("teacherId", id);

//execute Query
Teacher teacher = teacher.getSingleResult();

System.out.println(teacher);


//-- WE can also open a new session and lazy load data at a later point
session = factory.getCurrentSession();
session.beginTransaction();
//get course of a given teacher
Query<Course> query = session.createQuery("select c from Course where c.teacher.id=:teacherId", Course.class)

query.setParameter("teacherId", id);
List<Course> courses = query.getResultList();
```

#### Many To Many Mapping

When we map two entities in a many to many relation we need to create a new table called as the JoinTable that will keep track of the relation.

A Join Table has foreign keys for each table to define the mapping relationship.

In the following students we have students and the courses that the students are taking.

Create a Join Table for Students and Courses.

```sql
CREATE TABLE `course_student` (
  `course_id` int(1) NOT NULL
  `student_id` int(1) NOT NULL

  PRIMARY KEY (`course_id`, `student_id`),
  
  CONSTRAINT `FK_COURSE`
  FOREIGN KEY (`course_id`)
  REFERENCES `course` (`id`),

  CONSTRAINT `FK_STUDENT`
  FOREIGN KEY (`student_id`)
  REFERENCES `student` (`id`),
)
```

Create And store the Entities to the database.

```java
@Entity
@Table(name="courses")
public class Course {
  //other properties

  //We can have the fetch and cascade with the relation
  @ManyToMany
  @JoinTable(
    name="course_student",
    joinColumns=@JoinColumn(name="course_id"),
    inverseJoinColumns=@JoinColumn(name="student_id")
  )
  private List<Student> students;

  //Constructors, Getters and Setters
}

@Entity
@Table(name="students")
public class Student {
  //other properties

  @ManyToMany
  @JoinTable(
    name="course_student",
    joinColumns=@JoinColumn(name="student_id"),
    inverseJoinColumns=@JoinColumn(name="course_id")
  )
  private List<Course> course;

  //Constructors, Getters and Setters
}

//All the operation code for save, update and delete remains the same as we had in any other relation mapping.
```

## Aspect Oriented Programming

Aspect-oriented programming (AOP) is a programming paradigm that aims to increase modularity by allowing the separation of cross-cutting concerns. It does so by adding behavior to existing code (an advice) without modifying the code itself, instead separately specifying which code is modified via a "pointcut" specification, such as "log all function calls when the function's name begins with 'set'". This allows behaviors that are not central to the business logic (such as logging) to be added to a program without cluttering the code core to the functionality.

AOP includes programming methods and tools that support the modularization of concerns at the level of the source code, while aspect-oriented software development refers to a whole engineering discipline.

### Introduction Theory

#### Benifits of AOP

* Code For Apect is defined in a single class, which prevents scattering and promotes code reuse and easier to change.
* Buisness code in our application is clean, which reduces complexity and only applies to the buisness functionality.
* Aspects can be selectively applied to parts of the app based on the need only by changing the configuration and keeping the buisness code unchanged.

#### AOP Use Cases

* Security, transactions, logging.
* Audit logging - who, what, where when.
* Exception handling and notification to relevant authority
* API management and analytics. How many times called, load, top users.

#### Disadvantages of AOP

* Too many aspects can make app flow hard to follow.
* Minor performance cost for aspect execution.

#### AOP Terminology

* Aspect : Module of code for cross cutting concern(logging, security, etc).
* Advice : What action is taken and when it should be applied.
* Join Point : When to apply code during program execution.
* Pointcut : A predicate expression for where advice should be applied.
* Weaving : Linking aspects with other application types or objects to create an advised object

#### Advice Types

* Before Advice : Run before the method.
* After finally advice : Run after the method(finally).
* After returning advice : Run after the method(sucessful execution).
* After throwing advice : Run after method(if exeception thrown).
* Around advice : Run before and after method.

#### Weaving

* Connecting aspects to target object to create an adviced object.
* Different types of weaving are Compile time, load-time or runtime
* Run-Time Weaving is slow as it happens at runtime.

#### AOP Frameworks

* AspectJ
* Spring AOP

Spring AOP

* Spring provides AOp support out of the box.
* Key components that use AOP in spring are Security, transactions, caching, etc.
* Spring AOP uses run-time weaving of aspects.
MainApp -> AOP proxy -> Logging or/and Secutity Aspect -> Target Object.

Advantages of Spring AOP over AspectJ

* Simpler to use and is a light implementation of AOP.
* Uses Proxy Pattern
* Can migrate to AspectJ when using @Aspect annotation

Disadvantages of Spring AOP over AspectJ

* Only supports method-level join points.
* Can only apply aspects to beans created by Spring App context.
* Minor performance cost for aspect execution as it uses run-time weaving.

AspectJ

* It is the original AOP framework, released in 2001.
* Provides complete support for AOP.
* Rich support for join points and code weaving.
* Join Point : Method level, constructor, field.
* Code weaving : Compile-time, post compile-time and load-time.

Advantages of AspectJ over Spring AOP

* Support all join points.
* Works with any POJO not just beans from app context.
* Faster performance compared to Spring AOP.
* Complete AOP support.

Disadvantages of AspectJ over Spring AOP

* Compile-time weaving requires extra comilation steps.
* AspectJ pointcut syntax can become complex.

### Setting Up AOP

We need to add AspectJ jar files even though we will be using Spring AOP as Spring still uses some of the annotation and classes from AspectJ.

### @Before Advice Type

The code from the aspect will run before the method.

Main App <-> AOP proxy -> Logging/Security Aspect -> Target Object.

Most Common Uses

* Logging, Security, Transcations.
* Audit Logging.
* API Management.

```java

@Aspect
@Component
public class LoggingAspect {

  @Before("execution(public void addAccount())")
  public void beforeAddAccount() {
    System.out.println("\n Logging => A new Account is going to be added");
  }
}

@Component
public class AccountDAO {
  public void addAccount() {
    System.out.println()
  }
}

@Configuration
@EnableAspectJAutoProxy
@ComponentScan("in.adwait.project")
public class MainConfiguration{

}

public class Main{

  public static void main(String[] args) {
    AnnotationConfigAppicationContext context = new AnnotationConfigurationContext(MainConfifuration.class);

    AccountDAO account = new AccountDAO();
    account.addAccount();

    context.close();
  }
}
```

### AOP PointCut Expressions

Pointcut is a predicate expression for where advice should be applied.

Spring AOP uses AspectJ's pointcut expression language.

#### Execution PointCut Expressions

`execution(modifiers-pattern? return-type-pattern declaring-type-pattern method-name-pattern(param-pattern) throws-pattern?)`

Following are examples of PointCut Expression for execution.

* `@Before("execution(public void in.adwait.project.Account.addAccount())")` : Match only `addAccount()` method in Account class.
* `@Before("execution(public void addAccount())")` : Match any `addAccount()` method in any class.
* `@Before("execution(public void add*())")` : Match methods starting with add in any class.
* `@Before("execution(* processCard*())")` : Modifiers are optional hence we dont have to list it, we can use * for optional patterns.
* `@Before("execution(public * processCard*())")` : Match method that has a public modifier with any return type and processCard as the start of the method name in any class.
* `@Before("execution(void processCard*())")` : Match method that has any modifier, and a return type of void in any class, starting with processCard.

#### Parameter Patterns

For Param-pattern WildCards

* `()` : matches a method with no arguments
* `(*)` : matches a method with one argument of any type.
* `(..)` : matches a method with 0 or more arguments of any type.

Match on method Parameter examples.

* `@Before("execution(* addAccount(in.adwait.project.Account))")` : In the method we specify a fully qualified class path for the argument type.
* `@Before("execution(* addAccount(in.adwait.project.Account, ..))")` : matches with method with name addAccount having a Account as argument and any number of other arguments.
* `@Before("execution(void in.adwait.project.dao.*.*(..))")` : Match any method in our DAO package(in.adwait.project.dao). The first * represents any class and the second any mwthod in the class.

#### Declaring PointCut Expression

We can use the pointcut expression by add them to each method separately or we could also declare them as a varible and use them from there.

Benefits of Pointcut Declarations over using them directly.

* Easily resuse.
* Easy Update in one location.
* Can also share and combine pointcut expression.

```java
@Aspect
@Component
public class LoggingAspect{
  @Pointcut("execution(* in.adwait.project.dao.*.*(..))")
  private void forDaoPackage(){} //This method name will be used as name for the pointcut declaration.

  //Now that we have declared the pointcut we can use this as many times as we want.

  //Using the above declaration of pointcut
  @Before("forDaoPackage()")
  public void beforeAddAccountAdvice() {
    //code for before advice here.
  }
}

//--- We can also declare the pointcut expression in a different class and use it.
@Aspect
@Component
public class PointCutExpressions{
  @Pointcut("execution(* in.adwait.project.dao.*.getter(..))")
  private void gettersInDaoPackage() {}
}

@Aspect
@Component
public class LoggingAspect{
  //While using pointcut expression from any other class we have to specify the fully qualified path for the class and the name of the pointcut.
  @Before("in.adwait.project.PointCutExpressions.gettersInDaoPackage()")
  public void beforeGetterMethods() {
    //code executed before any getter method in dao package.
  }
}
```

Combining pointcut Expression.

The Advice type work like a if statement when we pass in multiple pointcut expressions. The advice is execute only when the pointcut expressions together return true.

Following are the Operators that can be used in combination to define our pointcut combination.

* `@Before("expressionOne() && expressionTwo()")
* `@Before("expressionOne() || expressionTwo()")
* `@Before("expressionOne() && !expressionTwo()")
* `@Before("expressionOne() && (expressionTwo() || expressionThree())")

We can also declare a combination of pointcut expression as a single pointcut expression and then use it.

```java
//Select only getters in the package
@Pointcut("execution(* in.adwait.project.dao.*.get*(..))")
private void getters() {}
//Select only setters in the package
@Pointcut("execution(* in.adwait.project.dao.*.set*(..))")
private void setters() {}
//Select all methods in the package
@Pointcut("execution(* in.adwait.project.dao.*.*(..))")
private void fromDaoPackage() {}

//Combine the above pointcuts to get all methods that are not getters or setters.
@Pointcut("fromDaoPackage() && !(getters() || setters())")
private void fromDaoPackageExceptGettersAndSetters() {}
```

### Ordering Aspects

The Spring AOP does not have any order by which it will run different Advice.

To Control order we would have to place advices in separate aspects. The we can control the order of the aspects using `@Order` annotation. This will guarantee the order of when aspects are applied.

* The lower the number of Order the higher the preference.
* Negative Numbers are allowed
* Numbers do not have be consecutive.
* If two aspect have the same number, for them both the order will be random, but they will still run in order as compared to others.

In the following example we have three Advices that will run on the same method and we want to order them. So we create three different Aspects for the three Advices and mark them with `@Order`.

```java
@Aspect
@Component
@Order(1)
public class CloudLogAspect{

}

@Aspect
@Component
@Order(2)
public class LoggingAspect{

}

@Aspect
@Component
@Order(3)
public class AnalyticsAspect{

}

//So in the case CloudLogAspect will be executed first, then LoggingAspect and then AnalyticsAspect will be run last.
```

### JoinPoints

We will use the JoinPoints to access the method parameters for which we are using Advices, so that we could use the data from the arguments.

We can access the method Signature as well as method arguments.

```java
//--- class
@Component
public class AccountDAO() {
  public void addAccount(Account account) {
    System.log.println("The account was added.");
  }
}

@Before("...")
public void beforeAddAccountAdvice(JointPoint joinPoint) {
  //--- display method signature
  MethodSignature sign = (MethodSignature) jointPoint;
  System.out.println("Method: " + sign);
  //Output : Method: void in.adwait.project.dao.AccountDAO.addAccount(Account account)

  //--- display method arguments, in th case the argument is Account.
  Object[] args = joinPoint.getArgs();
  for(Object arg: args) {
    System.out.println(arg);

    if(arg instanceof Account) {
      Account account = (Account) arg;
      System.out.println("Account Details of account added : " + account);
      //Now here we can get the argument being passed and use it as we would like.
    }
  }
}
```

### @AfterReturning

`@AfterReturning` Advice type is run after the method successfully executes.

```java
// In the AccountDAO class say we have findAccount method that returns a list of Account that it found

@Aspect
@Component
public class AccountAspect{
  @AfterReturning(pointcut="execution(* in.adwait.project.AccountDAO.findAccount(..))", returning="result")
  public void afterReturningFindAccountAdvice(JointPoint joinPoint,  List<Account> result) {
    //The returning String and the name of used in the above arguments must be the same. It is not related to the name of the return in the actual method that the Advice targets.
    
    System.out.println(result);
    //The result contains what ever is returned by the targeted method.
  }
}
```

### @AfterThrowing

`@AfterThrowing` Advice is used to intercept if the method execution fails at some point and throws an exception.

```java
//The name given to throwing should be same as that used in argument of the method defining the advice.
@AfterThrowing(pointcut= "execution(* findAccount())", throwing="exception")
public void afterThrwoingFindAccountAdvice(JoinPoint joinPoint, Throwable exception) {
  System.out.println("Exception in the findAccount method logged from @AfterThrowing Advice");
  System.out.println(exception);
}
//--- In the above case the exeception is still propogated to the main program. We just can peek into the exception with the @AfterThrowing.

//--- If we want to stop the exception from propogating then we use the @Around advice.
```

### @After

The `@After` Advice executes after the method as completed execution and is executed irrespective of whether the method successfully completed or threw an exception.

So it works similar to a finally block in java.

If we have `@After` and `@AfterThrowing` advice for matching for the same method, the `@After` will run after `@AfterThrowing`. This change was made in version 5.2.7 and all versions after that implment the same.

`@After` Advice does not have access to the exception being thrown and hence it should not depend on whether the method was successful or it failed.

```java

@After("execution(* in.adwait.project.AccountDAO.findAccount(..))")
public void finallyAfterFindAccountAdvice(JoinPoint joinPoint) {
  //Do after the method is excuted.
}
```

### @Around

The `@Around` Advice runs before and after the target object. It is like a combineation of the `@Before` and `@After` Advices but gives more fine grain control over the process.

With `@Around` Advice we get a reference to a 'Proceding Joint Point', which is a handle to the target method used to execute the target method.

```java
//Here we will calculate the time for execution of the get method that in the services package for all classes.
@Around(execute("* in.adwait.porject.services.*.get*())")
public Object afterGetService(ProceedingJoinPoint proceedingJoinPoint) throws Throwable {
  long begin = System.currentTimeMillis();

  //The proceedingJoinPoint gives us a handle to the method that we use to run the method.
  Object result = proceedingJoinPoint.proceed();

  long end = System.currentTimeMillis();
  long duration = end-begin;

  System.out.println("Duration : " + duration);

  return result;
}
```

> Note : Spring uses the logger output stream to print the logs while the System.out.println uses the Standard output stream to print the data to console.
> Sometimes this leads to inconsistent prints to console. To resolve this we can change our code to use the logger output stream.
> `private Logger logger = Logger.getLogger(getClass().getName());` The we can use it to log by using `logger.info("Print to console");` or `logger.warning("This is a warning message")`. Also logger will only print String so we need to call the `toString()` method for objects.

#### Handling Exception

While we execute the method in the Advice we can handle the exception so that the exception is not propogated to the main app or we can rethrow the exception to be handled in the main program.

```java
@Around("execution(* in.adwait.project.*.get*(..))")
public Object afterGetFortune(ProceedingJoinPoint proceedingJoinPoint) throws Throwable {
  Object result = null;

  try{
    result = proceedingJoinPoint.proceed();
  }
  catch(Exception exce) {
    System.out.println("Exception Handled in @Around Advice" + exec);
    result = "Exception Handled";

    //-- optionally we can rethrow the exception if we want to the exception to be propogated to the main app.
    throw exec;
    //In the case that the exception is thrown the result will never be returned and the method will terminate here and let the main app handle this exection, but the logging can still be done from here.
  }
  return result;
}
```
