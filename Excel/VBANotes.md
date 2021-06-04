# VBA

Following code is vba. Just marked as java for better hightlighting

```javascript
//--- Comments
' This is a comment.     '
//

//--- Message Box
//MsgBox(prompt[,buttons][,title][,helpfile,context])
int a = MsgBox("Do you like blue color?",3,"Choose options")
//1 - vbOK - OK was clicked
//2 - vbCancel - Cancel was clicked
//3 - vbAbort - Abort was clicked
//4 - vbRetry - Retry was clicked
//5 - vbIgnore - Ignore was clicked
//6 - vbYes - Yes was clicked
//7 - vbNo - No was clicked 

//--- Input Box
//InputBox(prompt[,title][,default][,xpos][,ypos][,helpfile,context])
Length = InputBox("Enter Length ", "Enter a Number")

//--- Variable
//Dim <<variable_name>> As <<variable_type>>
//Types : 
//Numeric : Byte, Integer, Long, Single, Double, Currency, Decimal
//Non Numeric : String , Date, Boolean, Object, Variant
Dim num As Integer
num = 1234

Dim BirthDay As Date
BirthDay = DateValue("30 / 10 / 2020")

//--- Constants
//Const <<constant_name>> As <<constant_type>> = <<constant_value>>
Const MyInteger As Integer = 42 
Const myDate As Date = #2/2/2020# 
Const myDay As String = "Sunday"

//--- Operators
// '^' Exponential and all other basic mathematic operators work
// <> : Check unequality = : check equality and all other comparison operators work as they should

//Logical Operator
a<>0 AND b<>0 is False
a<>0 OR b<>0 is true
NOT(a<>0 OR b<>0) is false
(a<>0 XOR b<>0) is true

//Concatination Operator
//A 5 B 10
A + B will give 15
A & B will give 510
//For String they both + and &  work the same as concatinating strings

//--- Decisions Statements
//Switch
Select Case MyVar
  Case 1
     MsgBox "The Number is the Least Composite Number"
  Case 2
     MsgBox "The Number is the only Even Prime Number"
  Case 3
     MsgBox "The Number is the Least Odd Prime Number"
  Case Else
     MsgBox "Unknown Number"
End Select

//If with ElseIf
If x > y Then
   MsgBox "X is Greater than Y"
ElseIf y > x Then
   Msgbox "Y is Greater than X"
Else
   Msgbox "X and Y are EQUAL"
End If
//If can be nested

//--- Loop
//For Loop with Steps(Custom Increment)
Private Sub Constant_demo_Click()
  Dim a As Integer
  a = 10
  
  For i = 0 To a Step 2
     MsgBox "The value is i is : " & i
  Next
End Sub

//For Each
fruits = Array("apple", "orange", "cherries")
Dim fruitnames As Variant
For Each Item In fruits
  fruitnames = fruitnames & Item & Chr(10)
Next

//While
Dim Counter :  Counter = 10 
While Counter < 15
//do something here
Counter = Counter + 1
Wend

//Do While Loop 1
Do While i < 5
   i = i + 1
   msgbox "The value of i is : " & i
Loop

//Do While Loop 2
i = 10
  Do
    i = i + 1
    MsgBox "The value of i is : " & i
Loop While i < 3

//Do Until 1
i = 10
Do Until i>15
  i = i + 1
  msgbox ("The value of i is : " & i)
Loop

//Do Until 2
i = 10
Do 
  i = i + 1
  msgbox "The value of i is : " & i
Loop Until i<15

//Exit Loop
//Exit For
Exit For //Use if for the condition and use this to actually exit
//Exit Do
Exit Do //Exits Do while

//String Function
//https://www.tutorialspoint.com/vba/vba_strings.htm

//Date Functions
//https://www.tutorialspoint.com/vba/vba_date_time.htm

//--- Array
Dim arr1()
Dim arr2(5) //With Size
Dim arr3
arr3 = Array("apple","Orange","Grapes")

//Add and access value
arr(0) = "1"
arr(0) //Access value
arr(1) = "VBScript"  
arr(2) = 100 

//Multidimensional Array
Dim arr(2,3) as Variant
arr(0,0) = "Apple" 
arr(0,1) = "Orange"
arr(0,2) = "Grapes"

//--- User Defined Function
Function findArea(Length As Double, Optional Width As Variant)
   If IsMissing(Width) Then
      findArea = Length * Length
   Else
      findArea = Length * Width
   End If
End Function

//--- Sub Procedures
//They do not return values like function can
Sub Area(x As Double, y As Double)
   MsgBox x * y
End Sub
//Calling sub routines from functions
Function findArea(Length As Double, Width As Variant)
   area Length, Width
End Function

//--- With
//Using With to chain properties of a object
With MyObject 
 .Height = 100 ' Same as MyObject.Height = 100. 
 .Caption = "Hello World" ' Same as MyObject.Caption = "Hello World". 
 With .Font 
  .Color = Red ' Same as MyObject.Font.Color = Red. 
  .Bold = True ' Same as MyObject.Font.Bold = True. 
 End With
End With

//Select Range of Cells
ActiveSheet.Range(Cells(2, 3), Cells(10, 4)).Select
ActiveSheet.Range("C2:D10").Select
ActiveSheet.Range("C2", "D10").Select

//Some Methods and Arguments of theres methods
Activate           none
Cells              rowIndex, columnIndex
Application.Goto   reference, scroll
Offset             rowOffset, columnOffset
Range              cell1
                   cell1, cell2
Resize             rowSize, columnSize
Select             none
Sheets             index (or sheetName)
Workbooks          index (or bookName)
End                direction
CurrentRegion      none

//--- Selecting cells

//Important Note : Selection is just a part of the Range Object/Class. So all the methods of range apply to Selection

//Select last cell of Column of continous data
ActiveSheet.Range("a1").End(xlDown).Select
//Select Range of continous data
ActiveSheet.Range("a1", ActiveSheet.Range("a1").End(xlDown)).Select

//Select Entire Comlumn of non continous data
ActiveSheet.Range("a1",ActiveSheet.Range("a" & ActiveSheet.Rows.Count).End(xlUp)).Select

//Select Rectangular Rnage of cells
ActiveSheet.Range("a1").CurrentRegion.Select

//Get Selection Row number or column Number
Range("C5").Rows.Row //A1 is row 1 column 1 and so on are counted
Range("C5").Comlumns.Column

```
