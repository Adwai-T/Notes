# HTML and HTML 5

## Introduction to HTML 5 Elements

These tags give a discriptive structure to our HTML making the HTML code easier to read, and also help with Search Engine Optimization(SEO) and accessibility.

```html
<!DOCTYPE html>

<main>
    <p>
    Helps search engines and other developers find the main content of the page.
    There can be other child elements nested inside the main element.
    </p>
</main>

<!-- Following are some examples of the other HTML 5-->
<header>
</header>

<nav>
</nav>

<video>

<article>
</article>

<section>
</section>

<footer>
</footer>

<!-- Adding image to the page-->
<img src="https://www.linktoimage/image.jpg" alt="Alternate text to display when the image cannot be loaded.">

<!-- Adding an anchor tag to link to external pages-->
<a href="https://freecodecamp.org" target="_blank">This links to freecodecamp.org</a>
<!--target="_blank will open the link in a new tab-->

<!--Link to Interanl Sections of Page with Anchor Elements-->
<a href="#main">Main</a>
<main id="main">This is main element</main>
<!--`#` With id name of the element that we need to go to is used to create the link-->

<!--Create a Bulleted Unordered List-->
<ul>
    <li>milk</ul>
    <li>Cheese</ul>
</ul>

<!--Create an Ordered List-->
<ol>
    <li>Garfield</li>
    <li>Sylvester</li>
</ol>

<!--Creating a web Form-->
<form action="/submit-cat-photo">
  <input type="text" placeholder="cat photo URL" required>
  <button type="submit">this button submits the form</button>

  <!--Create Radio button pairs-->
  <!--Radio buttons can be nested within its own label element. This way it will automatically associate the button with the label.

  All related radio buttons should have the same name attribute to create a radio button group, this will make only one of them selectable at any time.

  It is considered best practice to set a for attribute on the label element, with a value that matches the value of the id attribute of the input element. This allows assistive technologies to create a linked relationship between the label and the child input element.
  -->
  <label for="indoor">
    <input id="indoor" value="indoor" type="radio" name="indoor-outdoor">Indoor
  </label>

  <!--Create a set of Check Boxes-->
  <!--Checkbox and Radiobutton are very same in how they need to be added and hence the rules remain same-->

  <label for="loving">
    <input id="loving" value="Loving" type="checkbox" name="personality" checked> Loving
  </label>

  <!--The value attribute is the value that gets send when the form is submitted.
  The checked property is used to create the radiobutton or checkboxes that are checked by default-->

</form>
```

### Create in-page link

```html
<h1 id="heading1">This is a heading</h1>

<!-- code here -->

<a href="#heading1">Link to above heading</a>
```

## Intermediate HTML

### Metadata : the `<meta>` element

- `<meta charset="utf-8">` : This element simply specifies the document's character encoding.

- Adding an author and description

```html
<meta name="author" content="Chris Mills" />
<meta
  name="description"
  content="The MDN Web Docs Learning Area aims to provide
complete beginners to the Web with all they need to know to get
started with developing web sites and applications."
/>
```

> `_Open Graph Data_` is a metadata protocol that facebook invented to provide rich metadata for websites.

```html
<meta
  property="og:image"
  content="https://developer.cdn.mozilla.net/static/img/opengraph-logo.dc4e08e2f6af.png"
/>
<meta
  property="og:description"
  content="The Mozilla Developer Network (MDN) provides
information about Open Web technologies including HTML, CSS, and APIs for both Web sites
and HTML5 Apps. It also documents Mozilla products, like Firefox OS."
/>
<meta property="og:title" content="Mozilla Developer Network" />
```

- Adding custom icons to your site :

```html
<link rel="shortcut icon" href="favicon.ico" type="image/x-icon" />
```

Saving it in the same directory as the site's index page saved in .ico format.

- Applying CSS and JavaScript to HTML :

```html
<link rel="stylesheet" href="my-css-file.css" />

<script src="my-js-file.js" defer></script>
```

- Setting the primary language of the document : `<html lang="en-US">` or `<p>Japanese example: <span lang="ja">ご飯が熱い。</span>.</p>`

### Text Formating Fundamentals

The following tags are recognized by screen reader and they are used to change how the words are spoken, hence they should not just be used for their view property.

- Emphasis :

`<p>I am <em>glad</em> you weren't <em>late</em>.</p>`

Browsers style this as italic by default, but you shouldn't use this tag purely to get italic styling. To do that, you'd use a `<span>` element and some CSS, or perhaps an `<i>`element (see below).

Strong importance :

`<p>This liquid is <strong>highly toxic</strong>.</p>`

- Presentational elements `<b>`, `<i>`, and `u` dont effect semantics.

- Description lists

The browser default styles will display description lists with the descriptions indented somewhat from the terms.

```html
<dl>
  <dt>soliloquy</dt>
  <dd>
    In drama, where a character speaks to themselves, representing their inner
    thoughts or feelings and in the process relaying them to the audience (but
    not to other characters.)
  </dd>
  <dt>monologue</dt>
  <dd>
    In drama, where a character speaks their thoughts out loud to share them
    with the audience and any other characters present.
  </dd>
  <dt>aside</dt>
  <dd>
    In drama, where a character shares a comment only with the audience for
    humorous or dramatic effect. This is usually a feeling, thought, or piece of
    additional background information.
  </dd>
</dl>
```

- Abbreviations : `<p>We use <abbr title="Hypertext Markup Language">HTML</abbr> to structure our web documents.</p>`

- Superscript `<sup>` and subscript `<sub>`

- Marking up time and dates : `<time datetime="2016-01-20">20 January 2016</time>`

- BreakLine `<br>`

- PreFormatted Text : `<pre>` preserves the text formating and white space and will show the text as is.

## Security In HTML5

**innerHTML** might be used to insert text into a webpage. There is a potential for this to become a attack vector on a site.

Using innerHTML might also fail security reviews, for example in chrome or mozilla extensions.

> HTML5 specifies that a `<script>` tag inserted with innerHTML should not execute.

The **setHTML()** method of the Element interface is used to parse and sanitize a string of HTML and then insert it into the DOM as a subtree of the element. It should be used instead of `Element.innerHTML` for inserting untrusted strings of HTML into an element.

Use `setHTML(input, sanitizer)`.

```js
const unsanitized_string = "abc <script>alert(1)</script> def"; // Unsanitized string of HTML
const sanitizer = new Sanitizer(); // Default sanitizer;

// Get the Element with id "target" and set it with the sanitized string.
document.getElementById("target").setHTML(unsanitized_string, sanitizer);
// Result (as a string): "abc  def"
```

## Editable Div

We can make the content of a div editable by adding `contenteditable` property to the div element.

```html
<div id="textarea" contenteditable>I look like textarea</div>
```

## Adding text from File directly

We can directly add text from a `.txt` file to a html element by using the `<object>` element.

```html
<div><object data="file.txt"></object></div>
```
