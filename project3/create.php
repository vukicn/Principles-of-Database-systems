<?php

//Start session
session_start();

// keep data in same session 
$host = $_SESSION["host"];
$user = $_SESSION["user"];
$pass = $_SESSION["password"];
$dbName = $_SESSION["user"];


// build the connection ...
$conn = mysqli_connect($host, $user, $pass, $dbName);

if (!$conn)
    // terminates execution.
    die("Could not connect:".mysqli_connect_error());
    
$Rec = $_POST["RecipeName"];
$Ingr = $_POST["Ingredient"];
$Quan = $_POST["Quantity"];

//query insert new recipe
$queryString = "INSERT INTO Recipes ".
    " VALUES ( \"$Rec\", \"$Ingr\", $Quan);";
//sending query
$status = mysqli_query($conn, $queryString);

if (!$status){
    echo "Error performing insertion: " . mysqli_error($conn) ;
    echo "<br>";
}else
    echo "Recipe $Rec added<br>";  
    // close the connection
    mysqli_close($conn);
?>
<br>
<!-- link back -->
<a href="create.html"> Go back to create a recipe or add ingredient to a recipe </a> <br>
