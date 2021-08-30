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

$Recipe = $_POST["RecipeName"];

// Start transaction
$queryString = " start transaction ";
//sending query
$status = mysqli_query($conn, $queryString);

//query to show all ingredients and quanity for certain recipe
$queryString = "select Ingredient, Quantity from Recipes".
    " where RecipeName = \"$Recipe\" ";

//sending query
$status = mysqli_query($conn, $queryString);

if (!$status){
    die("Error running query: " . mysqli_error($conn));
}

$true=0;
while($row = mysqli_fetch_assoc($status))
{
    $Ingr=$row["Ingredient"];
    $Quan=$row["Quantity"];
    
    //query that find ingredints for typed recipe
    $queryString = "select * from Inventory ".  
        "where Ingredient = \"$Ingr\"";  
    //sending query
    $status = mysqli_query($conn, $queryString);
    
    if (!$status)
        die("Error running query: " . mysqli_error($conn));
    
    $row= mysqli_fetch_assoc($status);
    
    $quantity1 = $row["Quantity"];
    
    if($Quan > $quantity1)
    {
        $true=1;
    }
    {
        //query modify data after complited transaction
        $queryString = "update Inventory SET Quantity=Quantity-$Quan ".
            "where Ingredient = \"$Ingr\" AND Quantity>=$Quan ";
        //sending query
        $status = mysqli_query($conn, $queryString);
    }
}

if($true==1)
{
    //query to rollback
    $queryString ="rollback";
    //sending query
    $status=mysqli_query($conn, $queryString);
    echo "Translaction failed. There are not enough ingredients for $Recipe in the inventory. <br>";
}
else
{
    //query to commit
    $queryString ="commit";
    //sending query
    $status=mysqli_query($conn, $queryString);
    echo "Transaction completed! You have all necessary ingredients for $Recipe. <br> ";
}

    // close the connection 
    mysqli_close($conn);
    
?>

<!-- link back -->
<a href="buy.html"> Go back to buy another igredients  </a> <br>
