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

Simply put the Spring framework will create and manage all the instances and inject them where they are needed, it will also be responsible for managing the instances during their lifecycle.

So Spring does two primary functions

* Inversion Of Control : Create and manage objects.

* Dependency Injection : Inject object's dependencies.

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
    <!-- <bean class="com.baeldung.springbootxml.Pojo">
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

## Container Configuration With Java

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

## Dependency Injection

Object factory create an object for us according to our configuration and then provides us with the required object.

### Common types of injection

1. Constructor Injection
2. Setter Injection

## Depencency Injection With XML Configuration

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

## Dependency Injection With @Autowired Annotation

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

## @Qualifier

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

## @Value

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

> `@Bean` : We can use `@Bean` to make an existing third-party class available to your Spring framework application context.
> We use `@PropertiesSource` to specify class path for our properties files being used.

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
# creadentails.properties
foo.email=adwait@adwait.in
foo.name=Adwait
```

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
public static PropertySourcesPlaceholderConfigurer propertySourcePlaceHolderConfugurer() {
  return new PropertySourcePlaceHolderConfigurer();
}
```

* In Spring 4.3 and higher which we will use most of the times, we do not need the above code.

## @Bean

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

### Real-time Use cases for @Bean

We can use the `@Bean` annotation to make an existing third-party class available to our Spring Framework applicaiton context.

As we cannot go into a third party class an add `@Component` Spring will not be able to detect the class and creat beans for Dependency injection. So we manually make it avaiable with `@Bean`.
