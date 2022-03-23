# CSS

`<link rel="stylesheet" href="styles.css">`

## CSS Basics

```css
/*Select element and Add style to multiple elements.*/
p, li {
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
padding : 5px;

/* % relative to the dimension of the parent element */
width : 10%;

/* Replative to 1% of view port. It is percentage of the view width that the item will have */
width : 30vw;

/* Similar to vw, vh Represents 1% of height of view port. */
height : 50vh;

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

* Descendant combinator : For nested element selection. In below example select `<em>` inside `<li>`.

```css
li em {
  color: rebeccapurple;
}
```

* Adjacent sibling combinator :

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
article p span { ... }

/* selects any <p> that comes directly after a <ul>, which comes directly after an <h1>  */
h1 + ul + p { ... }

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
  transform: rotate(0.8turn)
}
```

### @rules

* `@import 'styles2.css';` Imports one css into another.

* `@media` : Used to create media queries. Discussed later.

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

---

## UI Component Traversy Media Examples

```css

* {
  box-sizing: border-box;/*Set in most project main file to not be effected by margin and padding given by default by browser.*/
}
```

* `vh` : is a unit like pixel and used to represent the view area.

* object-fit:cover; (Is like background size for background images)

* gap : px % ; set gap between elements in container.

---

## Free code Camp Cheat Sheet

* Text :

text-align : justify, right, center, left(default)
text-decoration: underline, line-through
font-style: italic
background-color : rgba(), hsl(), linear-gradient(gradient_direction, color 1, color 2, color 3, ...), repeating-linear-gradient(), url()

font-weight : bold
Note:
Set the font-weight of the h1 tag to 800.
Set the font-weight of the h2 tag to 600.
Set the font-weight of the h3 tag to 500.
Set the font-weight of the h4 tag to 400.
Set the font-weight of the h5 tag to 300.
Set the font-weight of the h6 tag to 200.

font-size : 27 pixels
Note:
Set the font-size of the h1 tag to 68px.
Set the font-size of the h2 tag to 52px.
Set the font-size of the h3 tag to 40px.
Set the font-size of the h4 tag to 32px.
Set the font-size of the h5 tag to 21px.
Set the font-size of the h6 tag to 14px.

text-transform : lowercase, uppercase, capitalize, initial, inherit, none

line-height: 25px;

* Containers :

width, height,

transform: scale()-(Transform/change size of element by scale), skewX(-32deg)-(makes the element tilt like \\ this at the given degree), same skewY(20 deg)

box-shadow: offset-x, offset-y, blur-radius, spread-radius, color;

border-radius: 50%-(This will make it a circle)

position: relative(move element relative to its parent), absolute(fix the postion of the element relative to its parent),
fixed(Fix the postion of an element relative to browser window, example nav bar), sticky;

float: left, right;

z-index: (Gives how the elements are stacked over one another, higher number will be stacked above lower numbers.)

opacity : 1 to 0 values

margin: auto,

background-color:

.className::after {}, .className::before{}

* anchor :

a:hover

* Animations:

```css
#anim {
  animation-name: colorful;
  animation-duration: 3s;
}

@keyframes colorful {
  0% {
    background-color: blue;
  }
  100% {
    background-color: yellow;
  }
}
```

animation-fill-mode: forwards; (If we use this with button:hover and some animation like shown above the animation will keep playing until we have our mouse is on the button that we keep hovering. It should be put with the hover and not in the @keyframes)

animation-iteration-count: 3; (By default the animations will work continously for as much time as set, with this there will be limited amount of iterations)

animation-duration: sec (Time in which one iteration of the animations in completed)

animation-timing-function: linear, ease-out, cubic-bezier(0.25, 0.25, 0.75, 0.75); (determines in how how the animation cycle progresses) --> for a more natural and soft movement use => animation-timing-function: cubic-bezier(0.311, 0.441, 0.444, 1.649);

## CSS Flex Box

* Containers :

*display* : flex; (Sets the container to be a Flex box container)

*flex-direction* : (default)row, column-reverse, row-reverse, column;

*justify-content* : center, flex-start(default), flex-end, space-between, space-around, space-evenly; (Adjust elements in a horizontal space)

*align-items*: flex-start, flex-end, stretch, center, baseline; (Adjust elements in a vertical container)

*flex-wrap*: nowrap, wrap, wrap-reverse; (extra items move into a new row or column.)

*flex-shrink*: (px, em, %, auto, etc.) numeric value in the ratio at which the items should shrink. (Items shrink when the width of the parent container is smaller than the combined widths of all the flex items within it.)
(The flex-shrink property takes numbers as values. The higher the number, the more it will shrink compared to the other items in the container. For example, if one item has a flex-shrink value of 1 and the other has a flex-shrink value of 3, the one with the value of 3 will shrink three times as much as the other.)

flex-grow: controls the size of items when the parent container expands.(works with similar rule as above flex-shrink)

flex-grow, flex-shrink, and flex-basis : flex: 1 0 10px(can be auto); (respectively)

order : Takes number and can have negative values. Order elements according to numbers.

align-self: Same properties as align-items. Set align of individual item then setting them all at once in the parent. Any alignment set in the parent will be overriden.

## CSS grid

display: grid;

grid-template-columns: 50px 50px; set size of each of the element in the grid;
grid-template-columns: auto 50px 10% 2fr 1fr;(Note that there is no comman separating the value just a whitespace)

grid-column-gap: 10px;

grid-row-gap: 10px;

grid-gap: 10px 20px;

grid-column: 1 / 3;(Is a shorthand property for grid-column-start and grid-column-end)

grid-row: (works same as above grid-column)

justify-self: start, center, end; (Align horizontally)

align-self: start, center, end;(Align vertically)

grid-template-areas:
  "header header header"
  "advert content content"
  "footer footer footer";

(.) Can be used to denote an empty space.

grid-area: header, footer;

item1 { grid-area: 1/1/2/4; }

Use repeat function : grid-template-columns: repeat(2, 1fr 50px) 20px; =>same as => grid-template-columns: 1fr 50px 1fr 50px 20px;

grid-template-columns: 100px minmax(50px, 200px);

auto-fill: auto-fit;

```css
@media (min-width: 300px){
  .container{
    grid-template-columns: auto 1fr;
    grid-template-rows: auto 1fr auto;
    grid-template-areas:
      "advert header"
      "advert content"
      "advert footer";
  }
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
  --red-color : red;
}

* {
  color : var(--red-color);
}

/* Local varibles */ 
.button-gradient {
  background: linear-gradient(var(--gradientAngle), var(--gradientStart),var(--gradientStop));

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
#parent{
    width: 100%;
    height: 100%;
    overflow: hidden;
}

#child{
    width: 100%;
    height: 100%;
    overflow-y: scroll;
    padding-right: 17px; /* Increase/decrease this value for cross-browser compatibility */
    box-sizing: content-box; /* So the width will be 100% + 17px */
}
```

Hide Scroll bar [Stackoverflow post](https://stackoverflow.com/questions/16670931/hide-scroll-bar-but-while-still-being-able-to-scroll).
