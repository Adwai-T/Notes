# Java

## Pillars of Java

- Inheritance.
- Polymorphism.
- Encapsulation.
- Abstraction.

## Abstract Classes

Primary differences between Abstract Classes and Interfaces.

- Class can extend only one Abstract Class but can implement any number of Interfaces.
- The variables declared in Interface are `final` and `static`. Where as they can be instance varible in abstract classes.

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

- All arguments are of the same type.
- They are treated as an arry within the method.
- They must be the last of the method.

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

- Enable Functional Programming.
- Readable and consise code.
- Enable support for parrel processing.
- Easier to use API and libraries.

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

- Intermediate Operations

map,
filter,
sort

- Terminal Operations

collect,
forEach,
reduce

## Records

Records are used to do exactly what they say, create an imutable object record, where no fields in it can be changed once it is created.

While creating a record java will give us a default constructor that will set all the final values in the record but we could also create our own constructor with all the fields of the record if we need to do any post processing or validation.

```java
public record Student(String name, int rollNumber) {}

//The above record is same as the following class
public class Student{
  private final String name;
  private final String rollNumber;

  public Student(String name, String rollNumber){
    this.name = name;
    this.rollNumber = rollNumber;
  }

  //It also gives us a default toStrings method that prints all the fields in a readable manner.

  //It also gives us a equals method that returns equal/true when all the fields in the both the
  //given records are equal.
}

//--- Compact constructors
//They are unique to records and might be used when we want to override the default constructor or records.
public record Student(String name, int rollNumber) {
  //It does not take any parameters
  public Student{
    if(name == "") throw new IllegalArgumentException("Name cannot be empty.");
  }
  //We also do not need to set the fields. They are set automatically.
}

//We can have final static fields in the record but cannot declare instance fields later
public record Student(String name, int rollNumber) {
  private static final String SCHOOLNAME = "SSPMS";
  private String className;// Will give an error. Is not allowed.
}
```

> Records cannot extend any other class, but they can implement interfaces.
>
> Records also cannot have any nonstatic instance fields that are not declared above with the record definition.

## Generics

Generics means parameterized types.

Using Generics, it is possible to create classes that work with different data types.

Generics shift the burden of type safety from you to the compiler. Type safety is enforced at compile time making the code much safe at runtime.

> Generics cannot be used with primitives.

```java
//---Generics in Collections in Java
//We have already used generics, when we used java collections like List.
private List<String> strings = new ArrayList<>();
//This list is now a list of strings.

//We can create a List of objects
private List<Object> objects = new ArrayList<>();
//And we can add any type of objects.
objects.add("Orange");
object.add(new Integer(10));
object.add(new Dog("Tom"));
//But this presents a major problem as the object is not type safe.
//It might throw exception while runtime.

//--- Thus we use generics to make it more type safe.
//In the above example we still used generics to make the list,
//but what is shows is they should be specific.


//--- Bounded Generics
public interface Animal{
  public String name;
  public void eat();
}
public interface Quadruped{
  public void walk();
}

public class Dog implements Animal, Quadruped{
  public String name;
  public Dog(String name) {
    this.name = name;
  }
  public void eat(){
    System.out.println(name + " is eating dog treats.");
  }
  public void walk(){
    System.out.println(name + " is walking.");
  }
}

public class Cat implements Animal, Quadruped{
  public String name;
  public Cat(String name) {
    this.name = name;
  }
  public void eat(){
    System.out.println(name + " is drinking milk.");
  }
  public void walk(){
    System.out.println(name + " is walking.");
  }
}
//When we create a bounded generic even if we want to bound
//T to be Animal and Quadruped, we still use extends and use
//& to connect them.
public class Play<T extends Animal & Quadruped> {
  public T animal;
  public Play(T animal) {
    this.animal = animal;
  }
  //as we know that T bounded, it is an animal and quadruped,
  //we can call the methods of the interface and know that
  //They exist.
  public void play() {
    animal.eat();
    animal.walk();
  }
}

public class Main{
  public static void main(String[] args){
    Dog spike = new Dog("Spike");
    Play play = new Play(spike);
    play.play();

    Cat tom = new Cat("Tom");
    Play play = new Play(tom);
    play.play();
  }
}
```

> When using bounded generics, there can only be one class in the bounds and any number of interfaces, also the class name must be the first in the bound connected with interfaces with `&`.

### Multiple Generics

Our classes can also have multiple generics so that we can use multiple types of variables for our methods.

```java
public class Print<T, V> {
  public T string;
  public  V integer;

  public <T, V> T printAndReturn(T s, V i) {
    System.out.println(s);
    System.out.println(i);

    return s;
  }
}
```

### Wildcards in Generics

Lets consider, we want to create a method that takes in a List which containes some kind of object.

So we use `List<Object>` to create the list of objects. But when we try to pass a `List<Integer>` or `List<String>` to the method the method will give an error as a List of object is not the same as List of String or Integers, even thought String and Integer both extend object.

We can solve this problem by using wild card.

```java
private static void printList(List<?> objects) {
  System.out.println(objects)
}

//Now we can pass list that contains any object.
List<String> strings = new ArrayList<>();
List<Integer> ints = new ArrayList<>();
printList()

// --- We can make the wild car specific by bounding it
private static void printList(List<? extends Animal> animals) {
  System.out.println(animals)
}

//Now we can pass in a list of any animals
List<Cat> cats = new ArrayList<>();
printList(cats);
```

## Reflections

### Disadvantages of Reflection

As reflection works at runtime, it cannot be optimized by the compiler at compile time. Which makes reflection code slower.

When to use Reflection?

Only use Reflection for the things that cannot be done without it. For anything that can be achieved in the normal java way, use the normal java way of doing it.

Using normal java code without reflection keeps the code robust, less prone to errors that are hard to debug and allows for better optimization at compile time.
