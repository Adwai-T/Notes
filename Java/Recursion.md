# Recursion

Recursion is when a function calls itself until some base condition is met and then returns value to its previous call.

```java
public class Recusion{

  public static void recursion(int value) {
    //Stopping case also called base case
    if(value == 5) return;

    return recursion(someValue + 1);
  }

  public static void main(String[] args) {
    recursion(1);
    //This will keep executing till the value becomes 5.
  }
}
```

## Pros and Cons

Pros :

- Bridges gap between elegance and complexity.
- Reduces the need for complex loops and auxiliary data structures.
- Can reduce time complexity easily with memoization.
- Works really well with recursive structures like trees and graphs.

Cons :

- Slowness due to cpu overhead.
- Can lead to stack overflow exceptions.
- Can become complex if poorly constructed.

## Simple Example

Lets create a program that will print something a given number of times.

```java
public static void print(String text, int count) {
  System.out.println(text);

  if(count <= 1) return;

  print(text, count--);
}
```
