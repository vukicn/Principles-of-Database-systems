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
 
 // query that check if we have that receipe in database 
 $queryString = "SELECT Ingredient, Quantity FROM Recipes ".
     "WHERE Exists RecipeName =  \"$Rec\";"; 
 //sending query
 $status = mysqli_query($conn, $queryString);
 
 if (!$status){
     echo "We don't have recipe for $Rec in out inventory.";
     echo "<br>";
 }else{
 
     echo "Recipe for ".$Rec;
     
     //print table wirth ingredients and quantities
     echo "<table border=1>";
     echo "<tr> <th>Ingredient</th> <th>Quantity</th> </tr>";
     while($row = mysqli_fetch_assoc($status))
     {
         echo "<tr> <td>".$row["Ingredient"]."</td>".
             "<td>".$row["Quantity"]."</td> </tr>";
     }   
     echo "</table>";
 }
 // close the connection
 mysqli_close($conn);
 ?>
 <br>
<!-- link back -->
<a href="list.html"> Go back to list more recipe's ingredients </a> <br>
 