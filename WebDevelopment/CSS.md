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

https://developer.mozilla.org/en-US/docs/Web/CSS/Media_Queries/Using_media_queries
