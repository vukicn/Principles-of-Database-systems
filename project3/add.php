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
    die("Could not connect:".mysqli_connect_error());

$Ingr = $_POST["Ingredient"];
$Quan = $_POST["Quantity"];

//insert if doesn't have alredy same ingredint
$queryString = "INSERT INTO Inventory ".
    " VALUES ( \"$Ingr\", $Quan);";

//sending query
$status = mysqli_query($conn, $queryString);

if (!$status){
    
    if (!$conn)
      
     die("Could not connect:".mysqli_connect_error());
     //query update quantity for typed ingredint
     $queryString = " update Inventory set Quantity = Quantity + $Quan where Ingredient = \"$Ingr\" ";
     //sending query
     $status = mysqli_query($conn, $queryString);
     if (!$status){
        echo "Error performing insertion: " . mysqli_error($conn) ;
        echo "<br>";
     }else
        echo "Quantity of $Ingr modified!<br>";
        
}else
     echo "New ingredient $Ingr added!<br>";
    
    
    // close the connection 
     mysqli_close($conn);
    
?>

<!-- link back -->
<a href="add.html"> Go back   </a> <br>

