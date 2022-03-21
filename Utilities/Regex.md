# Regular Expression

In javascript regex are also objects.

These regex are used with `exec()` and `test()` methods of the regex and with the `match()`, `matchAll()`, `replace()`, `replaceAll()`, `search()`, `split()` methods of Strings.

> Great site for checking live regex and learning [https://regex101.com/](https://regex101.com/).

## Create Regular Expressions

There are who ways regular expressions can be created.

```js
const regex_1 = /ab+c/

//--- call the RegExp object
const regex_2 = new RegExp('ab+c');
//We use this methods when the regex is not initailly know and get at compile time, or we get the regex from user input
```

## Character Classes

`\, ., \cX, \d, \D, \f, \n, \r, \s, \S, \t, \v, \w, \W, \0, \xhh, \uhhhh, \uhhhhh, [\b]` - Are all the possible character classes.

> Note: To match this character literally, escape it with itself. In other words to search for `\` use `/\\/`.

## Assertions

`^, $, x(?=y), x(?!y), (?<=y)x, (?<!y)x, \b, \B` - Are all the possible assertions.

## Groups and Ranges

`(x), (?:x), (?<Name>x), x|y, [xyz], [^xyz], \Number` - Are all types of grouping methods.

## Quantifiers

`*, +, ?, x{n}, x{n,}, x{n,m}`