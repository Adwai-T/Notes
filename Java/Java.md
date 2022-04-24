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

### Closures

Enable to treat functionality as a method argument, or code as data.

A closure may be a special kind of object that combines 2 things: a function, and therefore the environment during which that function was created.

Closures can be passed to another function as a parameter.

A closure gives us access to the outer function from an inner function.

```java
public interface Process {
  void do(int i);
}

public class ClosureExample{

  public static void main(String[] args) {
    int a = 10;
    int b = 20;
    //--- Here we have an obvious question where does b
    //come from.
    //Java will remember b from the context from where we 
    //passed in the method and use the value from that context.
    //So it will use b=20 in this case.
    process1(a, i -> System.out.println(i+b));

    //We cannot change the value of b inside of the function though
    //as the function will consider the value as final in the function.
    //Following example does the same thing as above.
    public void process2(int i) {

      //if we try to change the value of b in this method it 
      //will give us an error.
      b=30;//gives error as it considers the value as final in this method.

      System.out.println(i+b);
    }
  }

  public static void process1(int a, Process p) {
    p.do(a);
  }
}
```

So in case of closures Java considers the variables as effectively final when the method is created, even thought we don't need to specify it explicitly.

Java will throw a compiler error if the value is changed.

### this Reference

Difference between inner class method and lambda expression.

When we use the `this` reference in a lambda, the lambda does not modify the this reference, that means the value of this reference inside of the lambda function is the same as that outside, where the lambda function is used.

In the Case of a anonymous inner class when we create the instance of the inner class the this value we will refere to that instance.

This is the major difference between Lambda expressions and Anonymous Inner class.

Lets Consider the Following Example.

With the innerClass the `this` keyword referes to the new inner clas instance that gets created and when we print it to the console we get a reference to that class instance.

```java
public interface Process{
  void do(int i);
}

public class MyClass{

  public void do (int i, Process p) {
    p.do(i);
  }

  public static void main(String[] args) {
    //Inner class
    MyClass myClass = new MyClass();
    myClass.do(1, new Process() {
      @Override
      public void do(int i) {
        System.out.println("Value : " + i);
        //This referes to the innerclass instance
        System.out.println(this);
      }
    });

    myClass.do(1, i -> {
      System.out.println("Value : " + i);
      // System.out.println(this);
      //The above this will create an error as this will be refered 
      //from a static method and we cannot use this in static context
    });
  }

  public void execute() {
    do(1, i -> {
      System.out.println("Value : " + i);
      //this referes to the MyClass Instance
      System.out.println(this);
    });
  }
}
```

### Method References

> Consumner is an inteface that helps us create Lambda expressions.

```java
public class MyClass{
  public static void main(String[] args) {

    //-------1
    //Method that call method where both don't have parameters
    Thread t = new Thread(()->printMessage());
    t.start();

    //Method Reference for above expression
    //-- Also called Pass-through
    Thread t1 = new Thread(MyClass::printMessage);
    t1.start();

    //---------2
    //In this case we have a instance method that takes in 1 argument.
    print("Printed From Print Method", System.out::prinln);
    //the second argument acts similar to p->System.out.println(p)

  }

  public static void printMessage() {
    System.out.println("Hello");
  }

  public void print(String s, Consumer<String> consumer) {
    consumer.accept(s);
  }

}
```

### foreach Iteration

```java
public class MyClass{
  public static void main(String[] args) {
     List<String> animals = new Arrays.asList(
       "Dog",
       "Cat",
       "Elephant",
       "Tiger",
       "Lion"
     );

    //forEach takes a Consumer as an argumnet.
    animals.forEach(a -> System.out.println(a));
    //or we can use method reference
    animal.forEach(System.out::println);
  }
}
```

### Streams

A Squence of elements supporting sequential and parallel aggregate operations.

We can think about streams like a assembly line. When we are making cars the cars move and people stay in their place. This makes so that one car moves to every person once. So the work on the car is done by each person working in one circle of the assembly line.

This is what steams help us do, they help us work on each element in the data set at once so we dont have to loop over them again to do some other thing.

> As of Java 8 all collections come with a stream operation.

```java
//Example 1
public class MyClass{
  public static void main(String[] args) {
    List<String> animals = new Arrays.asList(
      "Dog",
      "Cat",
      "Elephant",
      "Tiger",
      "Lion"
    );

    animals.stream()
      .filter(p -> p.startsWith("C"))
      .forEach(System.out::println)
    //filter(Predicate)
  }
}
```

There are Different types of Operations.

* Intermediate Operations

map,
filter,
sort

* Terminal Operations

collect,
forEach,
reduce
