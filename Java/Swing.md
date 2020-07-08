# Swing

Refer to the class swingtesting/AGui.java to check the basics of Swing.

## MultiThreading in Swing Application

We should always keep our front end on a differnet thread than the backend of the application so that it does not freeze when the user click to do some heavy tasks.

## Types of threads used in Swing

There are three types of threads that will be used in Swing Applications:

1. Initial threads start the application by calling the main method. A normal Swing application has only one initial thread.
2. The event dispatch thread is responsible for the event handling codes. Also, It's a good practice to call all the Swing methods in this thread to avoid any unpredictable behavior.
3. Worker threads should be used to execute background services.

The great thing about Java Swing is that you don't need to create these threads explicitly by yourself. Swing Framework or Runtime provides it for you. All you have to do is to utilize the options available to you to provide your clients with a pleasant experience.

## Initial Threads

## Event Dispatch Threads

## Worker/Background Threads

```java
final JLabel updateLabel;
class SwingWorkerExample extends SwingWorker<String, Object> {
    @Override
    public String doInBackground() {
        // long running task
        Thread.sleep(500);
        return textToUpdateLabel();
    }

    @Override
    protected void done() {
        try {
            updateLabel.setText(get());
        } catch (Exception ignoreForNow) {
        }
    }
}
(new SwingWorkerExample()).execute();
```
