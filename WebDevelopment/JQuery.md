# JQuery

jQuery is one of the many libraries for JavaScript. It is designed to simplify scripting done on the client side. jQuery's most recognizable characteristic is its dollar sign ($) syntax. With it, you can easily manipulate elements, create animations and handle input events.

```html
<!--use use (document).ready to run the script after the dom has already loaded-->
<script>
  $(document).ready(function(){

    //All jQuery functions start with a `$`.
    //Here we will select button to add function to the button.
    //This is just the selector the function of bounce animation will actually be appied bycss
    $("button").addClass("animated bounce");

    //Select a class with jQuery
    $(".text-primary").addClass("animated shake");

    //Select Target Element by id
    $("#target6").addClass("animated fadeOut")

    //Remove class from Elements
    $("button").removeClass("animated");

    //Change the CSS of an Element Using jQuery
    $("#target1").css("color", "blue");

    //Disable an Element Using jQuery
    $("button").prop("disabled", true);

    //Change Text Inside an Element Using jQuery
    $("h3").html("<em>jQuery Playground</em>");

    //Remove an element from dom
    $("#target1").remove();

    //Use appendTo to move elements with jQuery
    $("#target4").appendTo("#left-well");

    //Clone an Element Using jQuery
    $("#target2").clone().appendTo("#right-well");

    //Target the Parent of an Element Using jQuery
    $("#left-well").parent().css("background-color", "blue");

    //Target the Children of an Element Using jQuery
    $("#left-well").children().css("color", "blue");

    //Target a Specific Child of an Element using jQuery
    $(".target:nth-child(3)").addClass("animated bounce");
    //Give the third element in each well a bounce class

    //Target Even Element Using jQuery
    $(".target:odd").addClass("animated shake");

    //Use jQuery to Modify the Entire Page
    $("body").addClass("animated fadeOut");

  });
</script>
```
