# Threads

Process : It is an instance of the program running

A Process can have multipe Threads and has its own memory.

## Concurrency With Treads

In this we do multipe task of different type simultaneously using threads.

## Parallelism

In this we split a task in to multipe smaller task and run them on different threads so the task is completed faster than running it on single thread.

`Thread thread = Thread.currentThread(); // the current thread`

Information about the main thread and other thread work similarly

```java

public class MainThreadDemo {
    public static void main(String[] args) {
        Thread t = Thread.currentThread(); // main thread

        System.out.println("Name: " + t.getName());
        System.out.println("ID: " + t.getId());
        System.out.println("Alive: " + t.isAlive());
        System.out.println("Priority: " + t.getPriority()); // MAX = 10 MIN = 1
        System.out.println("Daemon: " + t.isDaemon());

        t.setName("my-thread");
        System.out.println("New name: " + t.getName());
    }
}

```

A daemon thread (comes from UNIX terminology) is a low priority thread that runs in the background to perform tasks such as garbage collection and so on. JVM does not wait for daemon threads before exiting while it waits for non-daemon threads.

## Creating Thread in Java : Two different approaches

- Extend Thread and override run method:

```java
class HelloThread extends Thread {

    @Override
    public void run() {
        String helloMsg = String.format("Hello, i'm %s", getName());
        System.out.println(helloMsg);
    }
}
```

- Implement Runnable and Override run :

```java
class HelloRunnable implements Runnable {

    @Override
    public void run() {
        String threadName = Thread.currentThread().getName();
        String helloMsg = String.format("Hello, i'm %s", threadName);
        System.out.println(helloMsg);
    }
}
```

- Creating threads from above code

```java

Thread t1 = new HelloThread(); // a subclass of Thread

Thread t2 = new Thread(new HelloRunnable()); // passing runnable

```

- With Lambda Expression

```java
Thread t3 = new Thread(() -> {
    System.out.println(String.format("Hello, i'm %s", Thread.currentThread().getName()));
});
```

### Use `t.start()` to start the thread

> Note : If you try to start a thread more than once, the start throws IllegalThreadStateException.

## Thread Management

- _Make thread Sleep_

- We could use the regular `Thread.sleep();` static method or.
- we could use `TimeUnit.MILLISECONDS.sleep(2000)`

- _Thread.join()_

```java
public class JoiningExample {
    public static void main(String []args) throws InterruptedException {
        Thread worker = new Worker();
        worker.start(); // start the worker

        Thread.sleep(100L);
        System.out.println("Do something useful");

        worker.join(3000L);  // waiting for the worker
        System.out.println("The program stopped");

        //IN the above join statement the main thread wait to execute after the join method until the
        //Execution of the worker Thread is done.
    }
}
```

**In multi Thread programs if threads other than the main thread has an exception, the exception is thrown and still the program will complete successfully, but if there is an error in the main thread the other threads will compelete but the program will exit with an error code.**

## Shared Data in between Treads

Threads that belong to the same process share the common memory (that is called Heap). They may communicate by using shared data in memory. To be able to access the same data from multiple threads, each thread must have a reference to this data (by an object).

NOTE : Atomic operations are those that finish in one step. Like read an integer. In some platforms reading a long or a 64 bit double might not be an atomic operation.

- Visibility between Threads :
  The variables might not always be visible to threads that work on the same varible due to optimization of either JVM or the system itself, and also due to caching of variables in the memory for faster performance. Thus we use the `volatile` keywork to make the varaible be visible and make the all threads see the changes that happen on the varaible. Also these variables are not cached for oprimization.

Note : volatile also makes writting doubles and longs atomic.

- Thread Synchronization :
  The monitor is a special mechanism to control concurrent access to an object. In Java, each object and class has an associated implicit monitor. A thread can acquire a monitor, then other threads cannot acquire this monitor at the same time. They will wait until the owner (the thread that acquired the monitor) releases it.

Thus, a thread can be locked by the monitor of an object and wait for its release. This mechanism allows programmers to protect critical sections from being accessed by multiple threads concurrently.

`synchronized` : can be used on classes, methods as well as on blocks of code. Following is example of synchronized on block of codes in a class and methods.

```java

class SomeClass {

    public static void staticMethod() {

        // unsynchronized code

        synchronized (SomeClass.class) { // synchronization on the class
            // synchronized code
        }
    }

    public void instanceMethod() {

        // unsynchronized code

        synchronized (this) { // synchronization on this instance
            // synchronized code
        }
    }
}
```

Locks :
When we have a sycnhronized keywork in a class the monitor locks the thread and no other thread can make changes or enter the class.
We might have methods and varaibles that are completely independent and we might want two thread to enter and change them both in different threads. This can be achieved by creating mulitple lock objects.

```java
//The class has two additional fields that are the locks for separating monitors for each critical section.
class SomeClass {

    private int numberOfCallingMethod1 = 0;
    private int numberOfCallingMethod2 = 0;

    final Object lock1 = new Object(); // an object for locking
    final Object lock2 = new Object(); // another object for locking

    public void method1() {
        System.out.println("method1...");

        synchronized (lock1) {
            numberOfCallingMethod1++;
        }
    }

    public void method2() {
        System.out.println("method2...");

        synchronized (lock2) {
            numberOfCallingMethod2++;
        }
    }
}

/*
If we have an instance of the class, one thread may work inside the synchronized block of the first method and, at the same time, another thread may work inside the synchronized block of the second method.
*/
```

## Thread Interruptions

Thread Interruptions do not immediately stop a thread but notifies it to stop.

Depending on the current state of a thread, interruptions are handled differently. Invoking thread.interrupt() will cause InterruptedException if the thread is sleeping or joining another thread. Otherwise, the only thing that will happen is that the interrupted flag will be set to true.

```java
Thread thread = ...
thread.interrupt(); // interrupt this thread
```

If we want to stop a thread by interrupting it we can use some the following program :

```java

//This program is just one example on how it could be used.
public class CustomThread extends Thread {

    @Override
    public void run() {
        while (!isInterrupted()) {
            try {
                doAction();
                Thread.sleep(1000); // it may throw InterruptedException
            } catch (InterruptedException e) {
                System.out.println("sleeping was interrupted");
                break; // stop the loop
            }
        }
        System.out.printf("%s finished", getName());
    }

    private void doAction() {
        // something useful
    }
}
```

## State of Thread

The `Thread.state enum`
`NEW`: an instance of the class Thread has been created, but it has not yet started;
`RUNNABLE`: a thread is executing in JVM but it may be waiting for OS resources such as processor;
`BLOCKED`: a thread that is blocked waiting for a monitor lock (we will consider it later);
`WAITING`: a thread is waiting for another thread indefinitely long to perform a task (e.g. join without timeout);
`TIMED_WAITING`: a thread is waiting for another thread for a specified waiting time (e.g. sleep, join with timeout);
`TERMINATED` : a thread is terminated when run method completely executes itself or an uncaught exception occurs. Once a thread terminates it never gets back to its runnable state.

To get the current state of the thread we use `getState()`.

![ThreadLifeCycle](./NotesImages/ThreadLifeCycle.svg);

## Executor : ExecutorService

As the program grows it becomes harder to manage threads as they are very low level. It might lead to unreachable code in the future as the application grows.

Thus we use Thread-Executors with Executor Service ;

`ExecutorService executor = Executors.newFixedThreadPool(4);`

An executor has the submit method that accepts a Runnable task to be executed. Since Runnable is a functional interface, it is possible to use a lambda expression as a task.

As an example, here we submit a task that prints "Hello!" to the standard output.

`executor.submit(() -> System.out.println("Hello!"));`

## Stopping executors

An executor continues to work after the completion of a task since threads in the pool are waiting for new coming tasks. Your program will never stop while at least one executor still works.

There are two methods for stopping executors:

void shutdown() waits until all running task completes and prohibits submitting of new tasks;
List`<Runnable>` shutdownNow() immediately stops all running tasks and returns a list of the tasks that were awaiting execution.
Note that shutdown() does not block the current thread unlike join() of Thread. If you need to wait until the execution is complete, you can invoke awaitTermination(...) with the specified waiting time.

```java
ExecutorService executor = Executors.newFixedThreadPool(4);

// submitting tasks

executor.shutdown();

boolean terminated = executor.awaitTermination(60, TimeUnit.MILLISECONDS);

if (terminated) {
    System.out.println("The executor was successfully stopped");
} else {
    System.out.println("Timeout elapsed before termination");
}
```

Types of executors :

1. An executor with a single thread : `Types of executors`
2. An executor with the growing pool : `ExecutorService executor = Executors.newCachedThreadPool();`
3. An executor that schedules a task : `ScheduledExecutorService executor = Executors.newSingleThreadScheduledExecutor();`
4. An excutor with fixed thread pool size : `ExecutorService executor = Executors.newFixedThreadPool(poolSize);`

```java
ScheduledExecutorService executor = Executors.newSingleThreadScheduledExecutor();
executor.scheduleAtFixedRate(() ->
        System.out.println(LocalTime.now() + ": Hello!"), 1000, 1000, TimeUnit.MILLISECONDS);
```

Exception handling :

```java
ExecutorService executor = Executors.newSingleThreadExecutor();
executor.submit(() -> {
    try {
        System.out.println(2 / 0);
    } catch (Exception e) {
        e.printStackTrace();
    }
});
```

## The Callable interface

Sometimes you need not only to execute a task in an executor but also to return a result of this task to the calling code. An executor supports another class of tasks named Callable that returns the result and may throw an exception.

```java
@FunctionalInterface
public interface Callable<V> {
    V call() throws Exception;
}

Callable<Integer> generator = () -> {
    TimeUnit.SECONDS.sleep(5);
    return 700000;
};
```

As you can see, it is a generic interface where the type parameter V determines the type of a result. Since it is a functional interface, we can use it together with lambda expressions and method references as well as implementing classes.

When we submit a Callable to executor service, it cannot return a result directly since the submit method does not wait until the task completes. Instead, an executor returns a special object called Future that wraps the actual result that may not even exist yet. This object represents the result of an asynchronous computation (task).

```java
ExecutorService executor = Executors.newSingleThreadExecutor();

Future<Integer> future = executor.submit(() -> {
    TimeUnit.SECONDS.sleep(5);
    return 700000;
};

//To get the actual result form the futrue we use :
int result = future.get();

int result = future.get(10, TimeUnit.SECONDS); // it blocks the current thread

//Cancel a task :
future1.cancel(true);  // try to cancel even if the task is executing now
future2.cancel(false); // try to cancel only if the task is not executing

System.out.println(future.isDone()); // most likely it is false
```

Example of Callbacks and Future in action :

```java
ExecutorService executor = Executors.newFixedThreadPool(4);

Future<Integer> future1 = executor.submit(() -> {
    TimeUnit.SECONDS.sleep(5);
    return 700000;
});

Future<Integer> future2 = executor.submit(() -> {
    TimeUnit.SECONDS.sleep(5);
    return 900000;
});

int result = future1.get() + future2.get(); // waiting for both results

System.out.println(result); // 1600000
```

Using invoke all to get futures form a list of tasks

```java

ExecutorService executor = Executors.newFixedThreadPool(4);
List<Callable<Integer>> callables =
        List.of(() -> 1000, () -> 2000, () -> 1500); // three "difficult" tasks

List<Future<Integer>> futures = executor.invokeAll(callables);
int sum = 0;
for (Future<Integer> future : futures) {
   sum += future.get(); // blocks on each future to get a result
}
System.out.println(sum);
```

## Summary of Threads Executors

Let's summarize the information about Callable and Future.

To get a result of an asynchronous task executed in ExecutorService you have to execute three steps:

create an object representing a Callable task;
submit the task in ExecutorService and obtain a Future;
invoke get to receive the actual result when you need it.
Using Future allows us not to block the current thread until we do want to receive a result of a task. It is also possible to start multiple tasks and then get all results to aggregate them in the current thread. In addition to making your program more responsive, it will speed up your calculations if your computer supports parallel execution of threads.

You may also use methods isDone, cancel and isCancelled of a future. But be careful with exception handling when using them.

## Classic collections and multithreading

1. Most of the classic collections like ArrayList, LinkedList, HashMap and others are non-synchronized and, as a consequence, they do not provide thread-safety;
2. There is a set of old collections like Vector, Stack, and Hashtable that are totally synchronized and thread-safe, but they have low performance;
3. When one thread is iterating over a standard collection and another thread tries to add a new element to it then we get a runtime exception called ConcurrentModificationException.

### Concurrent collections

To avoid all the problems associated with custom synchronization, Java Class Library provides alternative collection implementations that are adapted to be used in multithreaded applications and they are fully thread-safe. You may find them in the java.util.concurrent package that includes lists, queues, maps and other collections which make it easier to develop modern Java applications.

---

Done ...
