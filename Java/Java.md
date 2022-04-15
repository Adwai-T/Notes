# Java

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
