# Streams

Sometimes your program should process data located outside it or save results to an external destination. Java provides an abstraction called stream that unifies work with disks, files, network locations and other resources.

## Input and output Streams

In some sense, a Java stream is similar to a real-world water stream which has a beginning (source) and an end (destination). Based on the same principles, IO streams can be categorized into two groups:

input stream that reads data from a source;
output stream that writes data to a specified destination.

![InputAndOutputStreamDiagram](./NotesImages/io-streams.png)

NOTE : System.out and System.in are also streams.

## Buffered Streams

Some streams use a temporary memory location. At first, such streams read or write data to a temporary location and then data is moved on to a source or destination from it. This temporary location is typically a byte or character array called buffer, and the whole process is called buffering. The reason why an intermediate memory location is introduced is that appealing to some sources or destinations takes substantial time interval. So buffering is a kind of optimization that minimizes the number of interactions with them.

## Output Streams

### Character streams

Character output streams allow writing text data: char or String.

Some of the most common Methods of the class are as follows :

1. void write(char[] cbuf)  writes a char array
2. void write(char[] cbuf, int off, int len) writes a portion of a char array
3. void write(int c) writes a single character
4. void write(String str) writes a string
5. void write(String str, int off, int len) writes a portion of a string
6. close(). To close the stream and prevent resource leakage.

After java 7 we can take an approch of try-with-resource that automatically closes a stream when done:

```java
try (CharArrayWriter contactWriter = new CharArrayWriter();
     FileWriter bc1 = new FileWriter("business_card_1.txt", true);
     FileWriter bc2 = new FileWriter("business_card_2.txt", true)) {

    contactWriter.write("Phone: 111-222-333; Address: Hyperskill Avenue, 7");
    contactWriter.writeTo(bc1);
    contactWriter.writeTo(bc2);

    char[] array = contactWriter.toCharArray(); // writer content as char[]
} catch (Exception e) {
    System.out.println("Something went wrong");
}
```

### Byte streams

We have similar methods as above character streams for writing byte Streams.

```java
byte[] data = new byte[] {'s', 't', 'r', 'e', 'a', 'm'};
try (OutputStream outputStream = new FileOutputStream("sample.txt", false)) {
    outputStream.write(data);
} catch(IOException e) {
    System.out.println("Something went wrong");
}
```

Byte Streams become very useful when working with files other than text based files such as pictures, audio, video and even pdf.

### Buffered streams

Output streams have 2 classes from the standard library which do buffering.

BufferedOutputStream is based on the buffering principle. It has only two constructors:

1. `BufferedOutputStream(OutputStream out)`
2. `BufferedOutputStream(OutputStream out, int size)`

Same works for BufferedWriter:

1. `BufferedWriter(Writer out)`
2. `BufferedWriter(Writer out, int size)`

These classes are intermediate output streams. They take an output stream as an input and do buffering before delegating to another stream. An additional parameter size is the size of the buffer. If you want to release all data from the buffer by writing it to a destination, you can use `flush()` method. It is usually called automatically when your buffer is full or before stream closing.

### Conclusion

The output stream is a way to write data to a destination. The destination is a target endpoint of data, that can be a file, a console or even a web socket. Streams are divided into byte and character ones. Byte output streams allow writing sequences of bytes. It is necessary for working with binary files. Character output streams are intended for writing text. Character output stream classes usually end with Writer, because they extend one abstract java.io.Writer class as a rule. Similarly, byte output streams end with OutputStream. Some streams use buffering under the hood. It is a widely used optimization that tries to minimize costly interaction with a destination.

## Input Streams

```java
FileReader reader = new FileReader("file.txt");

char first = (char) reader.read(); // i
char second = (char) reader.read(); // n

char[] others = new char[12];
int number = reader.read(others); // 10

reader.close();

// After performing the code, others contains  ['p', 'u', 't', ' ', 's', 't', 'r', 'e', 'a', 'm', '\u0000', '\u0000'].
```

Let's explain the result. The first 10 characters are filled as expected, starting from the third input letter. Then stream reached the end of the file and stopped reading, so the last two characters are not updated. As you should remember, when you create an empty array it is actually filled with default values, which are '\u0000' for char array. This is a reason why the last 2 elements of others are '\u0000'. The tricky thing here is that '\u0000' is interpreted as an empty symbol and not displayed at all, although technically it is present.

```java
//Another way of reading files is :

FileReader reader = new FileReader("file.txt");

int charAsNumber = reader.read();
while(charAsNumber != -1) {
    char character = (char) charAsNumber;
    System.out.print(character);
    charAsNumber = reader.read();
}
reader.close();

```

## More Byte streams

```java

byte[] bytes = new byte[5];
FileInputStream inputStream = new FileInputStream("file.txt");
int numberOfBytes = inputStream.read(bytes);
System.out.println(numberOfBytes); // 5
inputStream.close();
Now bytes contains ['i', 'n', 'p', 'u', 't'].


//---

// Byte by byte approach also works here:

FileInputStream inputstream = new FileInputStream("file.txt");
int currentByte = inputstream.read();
while (currentByte != -1) {
    System.out.print(currentByte);
    currentByte = inputstream.read();
}
inputstream.close();
```

### What type of stream should I use

Generally speaking, a computer understands only sequences of bytes. As long as any data is just a set of bytes, the byte input stream is a common way for reading any kind of data. For computers, characters are still combinations of bytes defined by charset specification. On the contrary, human beings are used to dealing with sequences of characters. Character input streams are aimed to read data which consists of characters. Under the hood, they still read bytes, but immediately encode bytes to characters. So if you need to read a text, use character input streams. Otherwise, for example, while reading audio, video, zip and etc., use byte input streams.

## Conclusion Input Streams

Input streams provide a way to read data from a source. The source is a data provider like a console or standard input, file, string, or even network connection. There are two types of sources: byte and character ones. Character input streams are intended for reading text only. Byte input streams allow reading sequences of raw bytes. Character input stream classes usually end with Reader. Similarly, byte input streams end with InputStream.
