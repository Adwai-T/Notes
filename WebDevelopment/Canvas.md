# Canvas

## Create Canvas in HTML

```html
<canvas id="tutorial" width="150" height="150">
  Fallback content here.
</canvas>
```

Getting the canvas to be handled by javascript. We will use the above canvas that we created in them and get it in javascript.

```js
var canvas = document.getElementById('tutorial');

if (canvas.getContext) {
  var ctx = canvas.getContext('2d');
  // drawing code here
} else {
  // canvas-unsupported code here
}
```

> Note : The canvas grid has it's origin(0,0) at the top left corner of the canvas and the bottom right corner of the screen becomes the end point of the canvas(Max-Width, Max-Height).

## Basic drawing

```javascript

//--- Using rectangle as a predefined shape
//Rectangles can be directly be drawn as rect(x, y, width, height)
function draw() {
  var canvas = document.getElementById('canvas');
  if (canvas.getContext) {
    var ctx = canvas.getContext('2d');

    //Draws a filled rectangle.
    ctx.fillRect(25, 25, 100, 100);
    //Draws a rectangular outline.
    ctx.clearRect(45, 45, 60, 60);
    //Clears the specified rectangular area, making it fully transparent.
    ctx.strokeRect(50, 50, 50, 50);
  }
}

//--- Using path to draw custom shapes
function draw() {
  var canvas = document.getElementById('canvas');
  if (canvas.getContext) {
    var ctx = canvas.getContext('2d');

    ctx.beginPath();
    //Moveto does not actually draw anything it just moves the drawing location to the point described.
    ctx.moveTo(75, 50);
    ctx.lineTo(100, 75);
    ctx.lineTo(100, 25);
    ctx.fill();
  }
}
```

## Curves and Archs

```javascript
//Note that arcs can be a part of the path.
//arc(x, y, radius, startAngle, endAngle, anticlockwise)
ctx.arc(90, 65, 5, 0, Math.PI * 2, true);
//---> 2 * PI denotes that it is full circle. It denotes the projected angle of the arch with the center

//--- Arcs
bezierCurveTo(cp1x, cp1y, cp2x, cp2y, x, y)
quadraticCurveTo(cp1x, cp1y, x, y)

//--- Example
function draw() {
  var canvas = document.getElementById('canvas');
  if (canvas.getContext) {
    var ctx = canvas.getContext('2d');

    // Quadratric curves example :  Quadratic Bezier curves
    ctx.beginPath();
    ctx.moveTo(75, 25);
    ctx.quadraticCurveTo(25, 25, 25, 62.5);
    ctx.quadraticCurveTo(25, 100, 50, 100);
    ctx.quadraticCurveTo(50, 120, 30, 125);
    ctx.quadraticCurveTo(60, 120, 65, 100);
    ctx.quadraticCurveTo(125, 100, 125, 62.5);
    ctx.quadraticCurveTo(125, 25, 75, 25);
    ctx.stroke();
  }
}

function draw() {
  var canvas = document.getElementById('canvas');
  if (canvas.getContext) {
    var ctx = canvas.getContext('2d');

    // Cubic curves example : Cubic Bezier curves
    ctx.beginPath();
    ctx.moveTo(75, 40);
    ctx.bezierCurveTo(75, 37, 70, 25, 50, 25);
    ctx.bezierCurveTo(20, 25, 20, 62.5, 20, 62.5);
    ctx.bezierCurveTo(20, 80, 40, 102, 75, 120);
    ctx.bezierCurveTo(110, 102, 130, 80, 130, 62.5);
    ctx.bezierCurveTo(130, 62.5, 130, 25, 100, 25);
    ctx.bezierCurveTo(85, 25, 75, 37, 75, 40);
    ctx.fill();
  }
}
```

## 2D Path Object

The Path2D object, available in recent versions of browsers, lets we cache or record these drawing commands. We are able to play back our paths quickly.

```javascript
new Path2D();     // empty path object
new Path2D(path); // copy from another Path2D object
new Path2D(d);    // path from SVG path data

//--- Example
function draw() {
  var canvas = document.getElementById('canvas');
  if (canvas.getContext) {
    var ctx = canvas.getContext('2d');

    var rectangle = new Path2D();
    rectangle.rect(10, 10, 50, 50);

    var circle = new Path2D();
    circle.arc(100, 35, 25, 0, 2 * Math.PI);

    ctx.stroke(rectangle);
    ctx.fill(circle);
  }
}
```

## Color and Transparency

```javascript
ctx.fillStyle = 'orange';
ctx.fillStyle = '#FFA500';
ctx.fillStyle = 'rgb(255, 165, 0)';
ctx.fillStyle = 'rgba(255, 165, 0, 1)';

//Sets the style used when filling shapes.
fillStyle = color
//Sets the style for shapes' outlines.
strokeStyle = color

//--- Example
function draw() {
  var ctx = document.getElementById('canvas').getContext('2d');
  for (var i = 0; i < 6; i++) {
    for (var j = 0; j < 6; j++) {
      ctx.strokeStyle = 'rgb(0, ' + Math.floor(255 - 42.5 * i) + ', ' +
                       Math.floor(255 - 42.5 * j) + ')';
      ctx.beginPath();
      ctx.arc(12.5 + j * 25, 12.5 + i * 25, 10, 0, Math.PI * 2, true);
      ctx.stroke();
    }
  }
}
```

We can set the global transparency value by using `globalAlpha = transparencyValue`.

## Line styles

* `lineWidth = value` : Sets the width of lines drawn in the future.
  
* `lineCap = type` : Sets the appearance of the ends of lines. Types are : butt, round, square.

* `lineJoin = type` : Sets the appearance of the "corners" where lines meet. Types are round, bevel, miter.

* `miterLimit = value` : Establishes a limit on the miter when two lines join at a sharp angle, to let you control how thick the junction becomes.

* `getLineDash()` : Returns the current line dash pattern array containing an even number of non-negative numbers.

* `setLineDash(segments)` : Sets the current line dash pattern.

* `lineDashOffset = value` : Specifies where to start a dash array on a line.

## Gradients

* `createLinearGradient(x1, y1, x2, y2)` :
Creates a linear gradient object with a starting point of (x1, y1) and an end point of (x2, y2).
* `createRadialGradient(x1, y1, r1, x2, y2, r2)` :
Creates a radial gradient. The parameters represent two circles, one with its center at (x1, y1) and a radius of r1, and the other with its center at (x2, y2) with a radius of r2.
* `gradient.addColorStop(position, color)`
Creates a new color stop on the gradient object. The position is a number between 0.0 and 1.0 and defines the relative position of the color in the gradient, and the color argument must be a string representing a CSS `<color>`, indicating the color the gradient should reach at that offset into the transition.

## Patterns

```javascript
//---Example
function draw() {
  var ctx = document.getElementById('canvas').getContext('2d');

  // create new image object to use as pattern
  var img = new Image();
  img.src = 'https://mdn.mozillademos.org/files/222/Canvas_createpattern.png';
  img.onload = function() {

    // create pattern
    var ptrn = ctx.createPattern(img, 'repeat');
    ctx.fillStyle = ptrn;
    ctx.fillRect(0, 0, 150, 150);

  }
}
```

## Shadows

* `shadowOffsetX = float`
* `shadowOffsetY = float`
* `shadowBlur = float`
* `shadowColor = color`

```javascript
function draw() {
  var ctx = document.getElementById('canvas').getContext('2d');

  ctx.shadowOffsetX = 2;
  ctx.shadowOffsetY = 2;
  ctx.shadowBlur = 2;
  ctx.shadowColor = 'rgba(0, 0, 0, 0.5)';

  ctx.font = '20px Times New Roman';
  ctx.fillStyle = 'Black';
  ctx.fillText('Sample String', 5, 30);
}
```

## FillRules

By default is set to non zero winding rule. But optionally can be set to even odd rule.

For the below example lets consider we want to draw concentric circles we have to change color of fill every time, but in path we can set the fill rule to even odd and the contric circle, one will be filled and the other will not be.

```javascript
function draw() {
  var ctx = document.getElementById('canvas').getContext('2d');
  ctx.beginPath();
  ctx.arc(50, 50, 30, 0, Math.PI * 2, true);
  ctx.arc(50, 50, 15, 0, Math.PI * 2, true);
  ctx.fill('evenodd');
}
```

## Text

* `fillText(text, x, y [, maxWidth])` :
Fills a given text at the given (x,y) position. Optionally with a maximum width to draw.
* `strokeText(text, x, y [, maxWidth])` :
Strokes a given text at the given (x,y) position. Optionally with a maximum width to draw.

* `font = value` :
The current text style being used when drawing text. This string uses the same syntax as the CSS font property. The default font is 10px sans-serif.
* `textAlign = value` :
Text alignment setting. Possible values: start, end, left, right or center. The default value is start.
* `textBaseline = value` :
Baseline alignment setting. Possible values: top, hanging, middle, alphabetic, ideographic, bottom. The default value is alphabetic.
* `direction = value` :
Directionality. Possible values: ltr, rtl, inherit. The default value is inherit.
* `measureText()` :
Returns a TextMetrics object containing the width, in pixels, that the specified text will be when drawn in the current text style.

```javascript
//Examples

//StrokeText
function draw() {
  var ctx = document.getElementById('canvas').getContext('2d');
  ctx.font = '48px serif';
  ctx.strokeText('Hello world', 10, 50);
}

//BaseLine
ctx.font = '48px serif';
ctx.textBaseline = 'hanging';
ctx.strokeText('Hello world', 0, 100);

//Text Measurement
function draw() {
  var ctx = document.getElementById('canvas').getContext('2d');
  var text = ctx.measureText('foo'); // TextMetrics object
  text.width; // 16;
}
```

## Images

* `HTMLImageElement`
These are images created using the `Image()` constructor, as well as any `<img>` element.
* `SVGImageElement`
These are images embedded using the `<image>` element.
* `HTMLVideoElement`
Using an HTML `<video>` element as your image source grabs the current frame from the video and uses it as an image.
* `HTMLCanvasElement`
You can use another `<canvas>` element as your image source.

These sources are collectively referred to by the type `CanvasImageSource`.

Create Image :

`drawImage(image, x, y)` : Draws the `CanvasImageSource` specified by the image parameter at the coordinates (x, y).

`drawImage(image, x, y, width, height)` : Change image scale.

`drawImage(image, sx, sy, sWidth, sHeight, dx, dy, dWidth, dHeight)` :
Given an image, this function takes the area of the source image specified by the rectangle whose *top-left* corner is (sx, sy) and whose *width* and *height* are *sWidth* and *sHeight* and draws it into the canvas, placing it on the canvas at (dx, dy) and scaling it to the size specified by *dWidth* and *dHeight*.

```javascript
//The image needs to be loaded before the image can be drawn.
var img = new Image();   // Create new img element
img.addEventListener('load', function() {
  // execute drawImage statements here
}, false);
img.src = 'myImage.png'; // Set source path
```

Frames From a video can also be used as images, even if the video is not visible.

```javascript
function getMyVideo() {
  var canvas = document.getElementById('canvas');
  if (canvas.getContext) {
    var ctx = canvas.getContext('2d');

    return document.getElementById('myvideo');
  }
}
//This returns the HTMLVideoElement object for the video
```

Image Smoothing

* `ctx.mozImageSmoothingEnabled = false;`
* `ctx.webkitImageSmoothingEnabled = false;`
* `ctx.msImageSmoothingEnabled = false;`
* `ctx.imageSmoothingEnabled = false;`

Simple Example

```javascript
function draw() {
  var ctx = document.getElementById('canvas').getContext('2d');
  var img = new Image();
  img.onload = function() {
    ctx.drawImage(img, 0, 0);
    ctx.beginPath();
    ctx.moveTo(30, 96);
    ctx.lineTo(70, 66);
    ctx.lineTo(103, 76);
    ctx.lineTo(170, 15);
    ctx.stroke();
  };
  img.src = 'https://mdn.mozillademos.org/files/5395/backdrop.png';
}
```

## Saving and Restoring Canvas State

Each successive save and restore state is pushed and poped from a stack of states.

```javascript
function draw() {
  var ctx = document.getElementById('canvas').getContext('2d');

  ctx.fillRect(0, 0, 150, 150);   // Draw a rectangle with default settings
  ctx.save();                  // Save the default state

  ctx.fillStyle = '#09F';      // Make changes to the settings
  ctx.fillRect(15, 15, 120, 120); // Draw a rectangle with new settings

  ctx.save();                  // Save the current state
  ctx.fillStyle = '#FFF';      // Make changes to the settings
  ctx.globalAlpha = 0.5;
  ctx.fillRect(30, 30, 90, 90);   // Draw a rectangle with new settings

  ctx.restore();               // Restore previous state
  ctx.fillRect(45, 45, 60, 60);   // Draw a rectangle with restored settings

  ctx.restore();               // Restore original state
  ctx.fillRect(60, 60, 30, 30);   // Draw a rectangle with restored settings
}
```

It is Recommended that we save the original state of the canvas before we perform any transfroms on the canvas.

* Transfrom Canvas - `translate(x, y)`.

* Rotate Canvas - `rotate(angle)` Angle in radians.

* Scaling Canvas - `scale(x, y)` x and y are times increase. Original scale is 1.0.

```javascript
function draw() {
  var ctx = document.getElementById('canvas').getContext('2d');
  for (var i = 0; i < 3; i++) {
    for (var j = 0; j < 3; j++) {
      ctx.save();
      ctx.fillStyle = 'rgb(' + (51 * i) + ', ' + (255 - 51 * i) + ', 255)';
      ctx.translate(10 + j * 50, 10 + i * 50);
      ctx.fillRect(0, 0, 25, 25);
      ctx.restore();
    }
  }
}
```

* Using Transfromations : `transform(a, b, c, d, e, f)`

Multiplies the current transformation matrix with the matrix described by its arguments.

* a (m11) : Horizontal scaling.
* b (m12) : Horizontal skewing.
* c (m21) : Vertical skewing.
* d (m22) : Vertical scaling.
* e (dx) : Horizontal moving.
* f (dy) : Vertical moving.

`setTransform(a, b, c, d, e, f)` :
Resets the current transform to the identity matrix, and then invokes the transform() method with the same arguments. This basically undoes the current transformation, then sets the specified transform, all in one step.
`resetTransform()` :
Resets the current transform to the identity matrix. This is the same as calling: ctx.setTransform(1, 0, 0, 1, 0, 0);

```javascript
function draw() {
  var ctx = document.getElementById('canvas').getContext('2d');

  var sin = Math.sin(Math.PI / 6);
  var cos = Math.cos(Math.PI / 6);
  ctx.translate(100, 100);
  var c = 0;
  for (var i = 0; i <= 12; i++) {
    c = Math.floor(255 / 12 * i);
    ctx.fillStyle = 'rgb(' + c + ', ' + c + ', ' + c + ')';
    ctx.fillRect(0, 0, 100, 10);
    ctx.transform(cos, sin, -sin, cos, 0, 0);
  }
  
  ctx.setTransform(-1, 0, 0, 1, 100, 100);
  ctx.fillStyle = 'rgba(255, 128, 255, 0.5)';
  ctx.fillRect(0, 50, 100, 100);
}
```

## Composting and Clipping

[Composting and Clipping is explained with images at Mozilla.org website.](https://developer.mozilla.org/en-US/docs/Web/API/Canvas_API/Tutorial/Compositing)

We use `clip()` instead of `closePath()` to close a path and turn it into a clipping path instead of stroking or filling the path.

## Animations

`window.setInterval()`, `window.setTimeout()`, and `window.requestAnimationFrame()` functions can be used to call a specific function over a set period of time.

If you don't want any user interaction you can use the setInterval() function which repeatedly executes the supplied code. If we wanted to make a game, we could use keyboard or mouse events to control the animation and use setTimeout(). By setting EventListeners, we catch any user interaction and execute our animation functions.

```javascript
//Basic Example
var sun = new Image();
var moon = new Image();
var earth = new Image();
function init() {
  sun.src = 'https://mdn.mozillademos.org/files/1456/Canvas_sun.png';
  moon.src = 'https://mdn.mozillademos.org/files/1443/Canvas_moon.png';
  earth.src = 'https://mdn.mozillademos.org/files/1429/Canvas_earth.png';
  window.requestAnimationFrame(draw);
}

function draw() {
  var ctx = document.getElementById('canvas').getContext('2d');

  ctx.globalCompositeOperation = 'destination-over';
  ctx.clearRect(0, 0, 300, 300); // clear canvas

  ctx.fillStyle = 'rgba(0, 0, 0, 0.4)';
  ctx.strokeStyle = 'rgba(0, 153, 255, 0.4)';
  ctx.save();
  ctx.translate(150, 150);

  // Earth
  var time = new Date();
  ctx.rotate(((2 * Math.PI) / 60) * time.getSeconds() + ((2 * Math.PI) / 60000) * time.getMilliseconds());
  ctx.translate(105, 0);
  ctx.fillRect(0, -12, 40, 24); // Shadow
  ctx.drawImage(earth, -12, -12);

  // Moon
  ctx.save();
  ctx.rotate(((2 * Math.PI) / 6) * time.getSeconds() + ((2 * Math.PI) / 6000) * time.getMilliseconds());
  ctx.translate(0, 28.5);
  ctx.drawImage(moon, -3.5, -3.5);
  ctx.restore();

  ctx.restore();
  
  ctx.beginPath();
  ctx.arc(150, 150, 105, 0, Math.PI * 2, false); // Earth orbit
  ctx.stroke();

  ctx.drawImage(sun, 0, 0, 300, 300);

  window.requestAnimationFrame(draw);
}

init();
```

## Perfromace Improvement

### Separate Static and dynamic entities

Static Entities can be loaded onto a different offscreen canvas and then rendered and changed only when wanted. This will prevent unnecessary update of static entities every loop.

```javascript
myCanvas.offscreenCanvas = document.createElement('canvas');
myCanvas.offscreenCanvas.width = myCanvas.width;
myCanvas.offscreenCanvas.height = myCanvas.height;

myCanvas.getContext('2d').drawImage(myCanvas.offScreenCanvas, 0, 0);
```

### Using multiple canvas

As above we could also use multiple canvas to handle different things.

For example a drawing canvas can have tools on top layer, the canvas itself on one and the background that mostly is static.

### Transparency

Avoid as much as possible.

Transparency of canvas can be set to false if not needed. `var ctx = canvas.getContext('2d', { alpha: false });`.
