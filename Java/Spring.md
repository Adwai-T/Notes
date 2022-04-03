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

## Spring MVC

Model-View-Controller

[Spring MVC Official Docs](https://docs.spring.io/spring-framework/docs/current/reference/html/web.html)

Basic flow of MVC : WebBrowser -> Front Controller -> Controller -> View template -> Back to WebBrowser

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

### @Controller and @RequestMapping

The `@Controller` annotation inherits from the `@Component` and hence all Controllers are also Components that will get scanned automatically by Spring.

`@RequestMapping` is used on the methods to give the request that will activate the methods so that the request can be processed and an appropriate reply can be sent.

`@RequestMapping` can also Serves as a parent mapping for the controller if we put the annotion below the `@Controller` annotation.

For very simple applications this might not be necessary, this serves best when there are conflict of path between two controllers.

All request mapping on methods in the controller are relative to the controller's request mapping.

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
  String mesg = "Hello " + name + ", We hope you are having a wonderful day."

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

### @RequestParam

In the above example we use the `HttpServletRequest` to get the request directly. We then used the request to get and assign the form data that was send as a url parameter to a varaible that we could use.

With `@RequestParam` we can directly map the url paramter to a varaible and use it in the method.

```java
//The same methods as above but using @RequestParam
@RequestMapping("/processFormVersionTwo")
public String customMessage(@RequestParam("studentName") String name, Model model) {
  //Now we do that same as we did in the above example.
  String mesg = "Hello " + name + ", We hope you are having a wonderful day."
  model.addAttribute("message", mesg);
  return "successMessage"
}
```

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

We will use Hibernate Validation that is a package independent of Hibernate and is specialized only for Validation.

Hibernate validator 6.2 is based on Java EE and version later than that are based on Jakarta EE. So we want to make sure that our version of spring supports Jakarta EE or is based on Java EE.

We here will use Hibernate Validator 6.2.

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
