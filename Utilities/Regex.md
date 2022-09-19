# Regular Expression

## Character Classes

`\, ., \cX, \d, \D, \f, \n, \r, \s, \S, \t, \v, \w, \W, \0, \xhh, \uhhhh, \uhhhhh, [\b]` - Are all the possible character classes.

`\w` represets any character, and `\W` can be anything that is not a character.

Sames goes for `\d` being a digit and `\D` being anything other than a digit. `\s` represents a white space and `\S` being anything other than a white space.

> When using newline `\n` in a regex, try to use `\s` instead as in some cases it might not match even if the regular expression is correct.

`.` Represnts any character other than line break. Ex. `e.t` will match eat. As `.` is a special character, when `.` is to be matched it needs to be esacped with `\.`. This is to be done for all reserved characters used in reges like `*`, `!`, `()`, `{}` and `\`.

> Note: To match this character literally, escape it with itself. In other words to search for `\` use `\\` in the regex.

## Assertions

`^, $, x(?=y), x(?!y), (?<=y)x, (?<!y)x, \b, \B` - Are all the possible assertions.

> `^` represents the start of the line/string and `$` the end of line/string based on the selection mode.

## Groups and Ranges

`(x), (?:x), (?<Name>x), x|y, [xyz], [^xyz], \Number` - Are all types of grouping methods.

`R[au]n` matches for any one of the character in the barckets. So will match both Run and Ran but not Raun.

`[A-I]at` matches one character in the range from a to i and will match Cat, Hat, Bat but will not match Mat or Nat.

`[^x]` matches one character that is not x.

`[^a-d] matches one character that is not in the range from a to d.

> `^` represnt start of a string/line (depending on multiline mode) when used at the begining of regex, if used in square brackets represents negation.

## Quantifiers

`*, +, ?, x{n}, x{n,}, x{n,m}` - Are qualifiers.

Use of Qualifiers

`+` Match one or more.
`x{n}` Match exactly n number of x. Ex. `\S{2}` will match 2 non white spaces.
`x{n,}` Match n or more of x. Ex. `\w{3,}` match 3 or more characters.
`x{n,m}` Match n to m number of x. Ex. `\w{2, 7}` match 2 to 7 number of characters.
`x*` Match zero or more of x. Ex. `\w*` match zero or more characters.
`x?` Match once or none of x. Ex. `words?` matches if s is present or even when it is absent.

> `*` and `+` are always greedy, that is they will try to match the maximum that they can match. To Make them lazy use `?` after these qualifiers like `\w+?`. Same goes for `x{n,m}` also is greedy and will match maximum x's.

## Capture groups and OR operator

Capture groups allow to get a part of the match as a separate item in the result array.

`(...)` represents a capture group. Ex. `(cat | dog)`. where `|` is a logical OR operator and will match either cat or dog.

`(?:...)` represent non capture groups. They are matched but are not part of the result array.

`(?<Name>...)` represets a named capture group. The name will be used in the result. The `<>` are necessary.

## Regex in Javascript

In javascript regex are also objects.

These regex are used with `exec()` and `test()` methods of the regex and with the `match()`, `matchAll()`, `replace()`, `replaceAll()`, `search()`, `split()` methods of Strings.

> Great site for checking live regex and learning [https://regex101.com/](https://regex101.com/).

There are two ways regular expressions can be created.

```js
const regex_1 = /st\w{4}/gm

const regex_2 = new RegExp('st\\w{4}', 'gm');

const regex_3 = mew RegExp(/st\w{4}/, 'gm');

//We use this methods when the regex is not initailly know and get at compile time, or we get the regex from user input

//-- These regex can be used with string methods
const searchInThisString = 'This is a string';

let resultArray = regex_2.exec(searchInThisString);
//-- or
let resultArray2 = searchInThisString.match(regex_2);
//-- or
let resultArray3 = searchInThisString.matchAll(regex_2);

//-- There are other methods such as
// regex.test() returns true or false.
// string.search(regex) returns the index.
// string.replace(regex, stringToReplaceWith) or string.replaceAll(regex, stringToreplaceWith).
// string.split(regex) split string into an array.
```
