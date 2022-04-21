# Java

## Abstract Classes

Primary differences between Abstract Classes and Interfaces.

* Class can extend only one Abstract Class but can implement any number of Interfaces.
* The variables declared in Interface are `final` and `static`. Where as they can be instance varible in abstract classes.

```java
public abstract class Bird{
  public String Name;
  public abstract boolean flies() { }
}
```

## Optional

A container object which may or may not contain a non-null value. If a value is present, `isPresent()` will return true and `get()` will return the value.

So `Optional<T>` will hold a object of type T.

[Optional Methods](https://docs.oracle.com/javase/8/docs/api/java/util/Optional.html)

## Variable Number of Arguments

We can have our methods take in variable number of arguments.

There are some rules that apply.

* All arguments are of the same type.
* They are treated as an arry within the method.
* They must be the last of the method.

```java
private static void printAll(String... messages) {
  for(String message: messages){
    System.out.println(message);
  }
} 
```

## Lambda

Lambda's were introduced in Java 8. They allow us to program with functional programming.

A function can be assigned to a variable and used by accessing the variable.

### Why

* Enable Functional Programming.
* Readable and consise code.
* Enable support for parrel processing.
* Easier to use API and libraries.

### Defining Lambda Function

The type of a Lambda declaration is an interface containing only one method.

The method in the interface represents the input paramters and the return of the lambda.

```java
public Interface LambdaWithTwoParamters{
  public int functionAdd(int a, int b);
}

//Definition
LambdaWithTwoParamters add = (int num1, int num2) -> {
  return num1 + num2;
}

//Use
int addition = add(2, 5);
```

### Lamdbda Expression vs Java 7 implmentation

```java
public class Greeter {

  public static void main(String[] args) {
    //--- Passing instance of class
    Greeter greeter = new Greeter();
    greeter.greet(new MorningGreeting());
    
    //--- Create InnerClass
    Greeting afternoonGreeting = new Greeting() {
      public void greet() {
        System.out.println("Good Afternoon");
      }
    };

    //--- Create Lambda Function
    Greeting eveningGreeting = () -> System.out.println("Good Evening");

    //--- Directly passing lambda as a argument
    //Here java inferens that the passed lambda is of type Greeting as the method it is passed to is expecting Greeting as argument.
    //This is type inference with lambda function and is what separates them from Inner Class.
    greeter.greet(()->System.out.println("Good Night"));

    //we can then pass the Greeting lambda and innerclass to the Greeter instance.
    greeter.greet(afternoonGreeting);
    greeter.greet(eveningGreeting);

    //We might feel that the lambda function are same as or are short cut to inner class but that is not the case.
  }
  public void greet(Greeting greeting){
    greeting.greet();
  }
}

public Interface Greeting{
  public void greet();
}

public class MorningGreeting implements Greeting{
  public void greet() {
    System.out.println("Good Morning");
  }
}
```

The Lambda function are a new addition with Java 8. The instance method and inner class are both methods that could be used in previous versions.

### Example Lamda Expressions

Some examples of Lambda.

In the following we are not defining the type of the lambdas with interfaces. We will directly use a name.

```java
//-- If we have only one line {} can be skipped.
greetingFunction = () -> System.our.println("Welcome to Lambdas."); 

//-- Inline Lambda
greet(()-> System.out.println("Good Morning."));

//-- Lambdas with parameters
doubleTheNumber = (int num) -> { return a*2 };
//can also be written as if the return is in one line.
doubleTheNumber2 = (int num) -> a*2;

//-- Two parameters
addFunction = (int a, int b) -> a+b;

//-- Multi line lambda
safeDivideFunction = (int a, int b) -> {
  if(b==0) return 0;
  return a/b;
};

//-- Inferring parameter type
Interface MyLamda{
  int stringLength(String string);
}
//In the case the type of s does not need to be specified and will be infered from interface used to declare the function.
MyLamda stringLengthCalculator = s -> s.length();
```

### Using Lambda with existing Java API

We can use lambda with several interfaces that are already a part of the java api, which have only one method in them.

A perfect example of this is the runnable interface.

```java
public class RunnableExample{
  public static void main(String[] args) {
    //-- Using an anonymous inner class
    Thread thread = new Thread(new Runnable() {
      public void run() {
        System.out.println("Thread 1 ran");
      }
    });
    thread.run();

    //-- Using lambda
    Thread thread2 = new Thread(()-> System.out.println("Lambda thread ran"));
    thread2.run();
  }
}
```

### Functional Interface

A Interface that has one Abstract method is called as a Functional Interface.

We specify abstract as in java 8+ we can have default implmentation for methods in the interface itself.

While we create a Interface which is meant to be used with lambda we can use the `@FunctionalInterface` annotation over the interface to enforce it.

```java
@FunctionalInterface
public interface Greeting {
  public void greet();
}
```
