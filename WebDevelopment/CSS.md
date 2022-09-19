# CSS

`<link rel="stylesheet" href="styles.css">`

## CSS Basics

```css
/*Select element and Add style to multiple elements.*/
p,
li {
  color: green;
}

/*Change default behaviour of elements in html*/
li {
  list-style-type: none;
}
```

## Unites that can be used to represent values

```css
/* Most common represents the number of pixels */
padding: 5px;

/* % relative to the dimension of the parent element */
width: 10%;

/* Replative to 1% of view port. It is percentage of the view width that the item will have */
width: 30vw;

/* Similar to vw, vh Represents 1% of height of view port. */
height: 50vh;

/* Above are the most widely used, there are other less commonly used like vmin, vmax relative to view port dimension, rem relating to relative font size of the root element  and many other absolute unites can also be used. */
```

### Adding a class

We use the `.` selector for selecting elements with their class name.

```html
<ul>
  <li>Item one</li>
  <li class="special">Item two</li>
  <li>Item <em>three</em></li>
</ul>
```

```css
/*Will be applied to all the classes with the name special*/
.special {
  color: orange;
  font-weight: bold;
}

/*Will be added only to the elements that are li's or span's*/
li.special,
span.special {
  color: orange;
  font-weight: bold;
}
```

### Styling things based on their location in a document

- Descendant combinator : For nested element selection. In below example select `<em>` inside `<li>`.

```css
li em {
  color: rebeccapurple;
}
```

- Adjacent sibling combinator :

```css
h1 + p {
  font-size: 200%;
}
```

### Styling things based on state

```css
a:link {
  color: pink;
}

a:visited {
  color: green;
}

a:hover {
  text-decoration: none;
}
```

### Combining selectors and combinators

```css
/* selects any <span> that is inside a <p>, which is inside an <article>  */
article p span {
  ...;
}

/* selects any <p> that comes directly after a <ul>, which comes directly after an <h1>  */
h1 + ul + p {
  ...;
}

body h1 + p .special {
  color: yellow;
  background-color: black;
  padding: 5px;
}
```

## Intermediate CSS

### Functions

```css
.outer {
  border: 5px solid black;
}

.box {
  padding: 10px;
  width: calc(90% - 30px);
  background-color: rebeccapurple;
  color: white;
}
/*Or*/
.box {
  margin: 30px;
  width: 100px;
  height: 100px;
  background-color: rebeccapurple;
  transform: rotate(0.8turn);
}
```

### @rules

- `@import 'styles2.css';` Imports one css into another.

- `@media` : Used to create media queries. Discussed later.

### Shorthands

```css
padding: 10px 15px 15px 5px;

padding-top: 10px;
padding-right: 15px;
padding-bottom: 15px;
padding-left: 5px;

background: red url(bg-graphic.png) 10px 10px repeat-x fixed;

background-color: red;
background-image: url(bg-graphic.png);
background-position: 10px 10px;
background-repeat: repeat-x;
background-attachment: fixed;
```

### Media Queries

[Using_media_queries](https://developer.mozilla.org/en-US/docs/Web/CSS/Media_Queries/Using_media_queries)

## UI Component Traversy Media Examples

```css
* {
  box-sizing: border-box; /*Set in most project main file to not be effected by margin and padding given by default by browser.*/
}
```

## Pre Formated Text

It is used to insert text that is preformated. The formating of the text does not change and thus all the indenting and white spaces are kept as is.

But sometimes we want the pre tag content to wrap for mobile content. We could use following code for this.

```css
pre {
  overflow-x: auto;
  white-space: pre-wrap;
  white-space: -moz-pre-wrap;
  white-space: -pre-wrap;
  white-space: -o-pre-wrap;
  word-wrap: break-word;
}
```

## Variables

Variables can be set in css so that they can be used repeatedly for consistency.

```css
/* Global varible */
:root {
  --red-color: red;
}

* {
  color: var(--red-color);
}

/* Local varibles */
.button-gradient {
  background: linear-gradient(
    var(--gradientAngle),
    var(--gradientStart),
    var(--gradientStop)
  );

  --gradientAngle: 60deg;
  --gradientStart: lightpink;
  --gradientStop: lightyellow;
}

.button-gradient:hover {
  --gradientAngle: 0deg;
}
```

We can add a varible to css through javascript as `document.documentElement.style.setProperty('--varName', 'propValue')`.

## Hide Scroll bars

```css
#parent {
  width: 100%;
  height: 100%;
  overflow: hidden;
}

#child {
  width: 100%;
  height: 100%;
  overflow-y: scroll;
  padding-right: 17px; /* Increase/decrease this value for cross-browser compatibility */
  box-sizing: content-box; /* So the width will be 100% + 17px */
}
```

Hide Scroll bar [Stackoverflow post](https://stackoverflow.com/questions/16670931/hide-scroll-bar-but-while-still-being-able-to-scroll).

## Responsive Web Design

```css
/*For all cases*/
header nav {
  display: block;
}

/* Visible only on screens smaller than 768px */
@media screen and (max-width: 768px) {
  header nav {
    display: none;
  }
}
/* For specific screen orientation */
@media screen and (orientation: landscape) {
  header nav {
    position: fixed;
    left: 0;
    width: 20vw;
  }
}
```

```html
<!-- Can also be used as specific element media query -->
<div *media="'(min-width: 768px)'">I am visible only on desktop</div>
<div *media="'(max-width: 767px)'">I am visible only on mobile</div>
```

## Translate and Translate3d

The use of translate3d pushes CSS animations into hardware acceleration.

So Even when we are trying to use translate in just 2 dimension it will gives us better performance to use translate3d.

`translate3d( tx, ty, tz )`.

```css
.translate3d_image {
  transform: translate3d(100px, 0, 0);
}

.moved {
  transform: perspective(500px) translate3d(10px, 0, 100px);
  background-color: pink;
}
```
