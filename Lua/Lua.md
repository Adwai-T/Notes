# Lua

## Basics

```lua
print("Hello World");

-- Comments

-- [[
    multiline Comments
]]

--- Variables are dynamically typed

name = 'Adwait'
io.write("Size of String : ", #name, "\n")
name = 4

-- Lua only has floating point number, so no integers, all are floats.
--Is the biggest number that can be stored in lua variables.
bigNum = 9223372036854775807 + 1
io.write("Big Number ", type(bigNum), "\n")

--Upto 13 digit of precision;

-- MultiLine string with whitespace
logString = [[
    The formating of this string will be preserved.
    This will be printed as is.
    Print and try.
]]

-- Concat strings
longString = longString .. name

-- Boolean
isAbleToRead = true

--All variables have a value of nil if they are not initialized. If a varible is not created and a operation is performed, the variable will be created there and a value of nil will be assigend to it there.

--String Formating
print(string.format("not true = %s", tostring(not true)))
--Will return not true = false

--String length also can be found as follows besides `#`
io.write("Name Length = ", string.len(name), "\n")

--Replacing words in a string.
string.gsub(stringInWhichToChange, "toReplace", "Replacement")

--Strings have index and each character and whitespace will have index.
io.write("Here is my name No : ", string.find(name, "Adwait"), "\n")
--Will return 0 as name has only one word that is Adwait.

--string also has functions like string.lower(string), string.upper(string)
```

## Mathematical Operations

Common Mathematical operations are as in other languages. + - / *.

% operator, 5.2 % 3, will give 2 and not 2.2.

> Note : In lua i++, ++i, --i or i-- operations are not allowed. Also i += num like shorthands also are not supported by lua.

There are all the common maths funtions that we expect from present in lua, like floor, ceil, max, min, pow, sqrt and many more. Example use `math.pow(8, 2)`.

Random Numbers
`io.write("math.random() : " math.random(), "\n)`
`io.write("math.random() : " math.random(10), "\n)` from 1 to 10
`io.write("math.random() : " math.random(5, 100), "\n)` from 5 to 10

Setting a seed value for random number
`math.randomseed(os.time())`

Getting value of pi upto 10digit of precision.
`print(string.format("Pi = %.10f", math.pi))`

## Operators

Relational Operators : > < >= <= == ~=.

> Note : The not equal to is ~= unlike many other programming languages.

Logical Operators : and or not

## Conditional Statements

* If statements :

```lua
age = 13

if age < 16 then
    io.wirte("You can go to school", "\n")
    local localVar = 10
    --local keyword makes so that the variable it encapsulated for the if statement and will not be found outside of the if statement.
elseif (age <= 16) and (age < 18) then
    io.write("You can drive", "/n")
else
    io.write("You can vote", "/n")
end --end is important
```

> Note : There is no ternary operator in Lua. But we can make our own hacky ternary operator like `adult = age > 18 and true or false`
> There is also no `switch` in Lua.

## Looping

* While

```lua
i = 1

while (i <= 10) do
    io.write(i)
    i = i + 1

    if(i == 8) then break end

end

print("\n")
```

> Note : In lua there is no `continue` statement.

* Repeat

This is very similar to do while loop in other programming languages.

```lua
repeat
    io.write("Enter your guess : ")

    guess = io.read()

until tonumber(guess) == 15
```

* for

```lua
for i = 1, 10
    io.write(i)
end

months = {"January", "feb", "march", "April", "AndSoOn" }

--Looping over months
for key, value in pairs(months) do
    io.write(value, "")
end
```

## Tables

They take the place of all data stores in other programming languages.

```lua
aTable = {}

for i = 1, 10 do
    aTable[i] = i
end

io.write("First : ", aTable[1], "\n")

io.write("Number of Items : ", #aTable, "\n")

--This will insert value 0 at index 1 not replace the value at index 1
--That means all value will be moved down in the table
table.insert(aTable, 1, 0)
io.write("First : ", aTable[1], "\n")

print (table.concat(aTable, ", " ))
--Prints a string value and of all key values separated by a ,

table.remove(aTable, 1)
--Remove value at index

--Multidimensional Table
aMultiTable = {}

for i = 0, 9 do
    aMultiTable[i] = {}

    for j = 0, 9 do
        aMultiTable[i][j] = tostring(i) .. tostring(j)
    end
end

io.write("Table[0][0] : ", aMultiTable[0][0], "\n")
```

* Meta-Table

Governs how operations are performed on the table

```lua
aTable = {}

for x = 1, 10 do
    aTable[x] = x
end

mt = {
    --__sub __mul __lt __le and many other
    --There are two underscrolls
    __add = function(table1, table2)
    sumTable = {}

    for y = 1, #table1 do
        if(table1[y] ~= nil) and (table2[y] ~= nil) then
            sumTable[y] = table1[y] + table2[y]
        else
            sumTable[y] = 0
        end
    end

    return sumTable
end,

    __eq = function(table1, table2)
        return table1.value == table2.value
    end
}

--This is where we set the meta table from above to our table
setmetatable(aTable, mt)

--Use the metatable __eq function to check for equality
print(aTable == aTable)

addTable = {}

--Use metatable add function defined above to add tables
addTable = aTable + aTable
```

## Functions

```lua
function getSum(num1, num2)
    return num1 + num2
end

print(string.format("5 + 2  = %d", getSum(5, 2)))

function splitStr(theString)
    stringTable = {}

    local i = 1

    for word in string.gmatch(theString, "[^%s]+") do
        stringTable[i] = word
        i= i + 1
    end
    --Here we return multiple different value from a function
    return stringTable, i

--Here we use the multiple return values from the function and store them in different variables.
splitStrgTable, numOfStr = splitStr("The Turtle")

for j = 1, numOfStr do
    print(string.format("%d : %s", j, splitStrTable[j]), "/n")
end

--There is always a nil at the end of the table that is created so we can use numOfStr-1 to not print the nil.

--Getting unknown number of parameters
function getSumMore(...)
    local sum = 0

    for k, v in pairs{...} do
        sum = sum + v
    end
    return sum
end

io.write("Sum", getSumMore(1, 2, 3, 4), "\n")

--Store function in a varible
doubleIt = function(x) return x * 2 end

print(doubleIt(4))

--Closure
function outerFunc()
    local i = 0

    return function()
        i = i + 1
        return i
    end
end

getI = outerFunc()

print(getI()) -- Will print 1
print(getI()) --Will print 2
--So the values in a closure will be stored and will effect the value that value that we get in subsequent calls.
```

> Note : In Lua functions can return multiple values.

## Co-Routine

Co-Routines are like threads in other languages but important thing to not is that they cannot be run in parallel.

```lua
co = coroutine.create(function()
    for i = 1, 10, 1 do
        print(i)
        print(coroutine.status(co))
        if i == 5 then coroutine.yield() end
    end
end
)

print(coroutine.status(co))

coroutine.resume(co)

print(coroutine.status(co))

co2 = coroutine.create(function()
    for i = 101, 110, 1 do
        print(i)
    end
end)

coroutine.resume(co2)

coroutine.resume(co)

print(coroutine.status(co))
```

## File IO

Different Ways to work with files

* r : ReadOnly (default)
* w : Overwrite or create a new file
* a : Append or create a new File
* r+ : Read and write existing file
* w+ : Overwrite read or create a file
* a+ : Append read or create file

```lua
file io.open("test.lua", "w+")

file:write("This will be written to the file\n")
file:write("Some more text\n")

file:seek("set", 0)

print(file:read("*a"))

file:close()

--Append to the end of the file. We open the file again.
file = io.open("text.lua", "+a")

file:write("Even Even more text\n")

file:seek("set", 0)

print(file:read("*a"))

file:close()
```

## Module

Module name and file name should be the same.

```lua
local convert = {}

function convert.ftToCm(feet)
    return feet + 30.48
end

return convert
```

Using the module that we created in the above code

```lua
convertModule = require("convert")

print(string.format("%.3f cm)", convertModule.ftToCm(12))
```

## OOP

Lua does not natively support object oriented programming very well.

```lua
Animal = { height = 0, weight = 0, name = "No Name", sound = "No sound" }

function Animan:new (height, weight, name, sound)
    setmetatable({}, Animal)

    self.height = height
    self.weight = weight
    self.sound = sound
    self.name = name

    return self
end

function Animal:toString()
    --here we want all the value from animal. Wieght in printed for example
    animalStr = string.format("%s weighs", self.weight)
    return animalStr
end

--Create the object from our Animal Table
spot = Animal:new(10, 15, "Spot", "wood")

print(spot.weight)

print(spot:toString())

-- Inheritance
Cat = Animal:new()
--now cat has all the functions from the Animal Table

--We can then override the function and add new properties to cat
```
