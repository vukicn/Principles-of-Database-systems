<h1> Main menu </h1>
<?php
//Start session
session_start();
// check data in database 
$_SESSION["host"] = $_POST["host"];
$_SESSION["user"] = $_POST["user"];
$_SESSION["password"] = $_POST["password"];
$_SESSION["dbName"] = $_POST["user"];


// build the connection ...
echo "Attempting to connect to DB server: $host ...";
$conn = mysqli_connect($_SESSION["host"], $_SESSION["user"],$_SESSION["password"], $_SESSION["dbName"]);

if (!$conn)
	// terminates execution. 
	die("Could not connect:".mysqli_connect_error());
else
	echo " connected!<br>";

// create table for recipes
$queryString = " create table if not exists Recipes (RecipeName char(50), Ingredient char(50), Quantity integer, primary key(RecipeName, Ingredient) )";
//sending query
$status = mysqli_query($conn, $queryString);

if (!$status)
    die("Error running query: " . mysqli_error($conn));

// create table for the inventory
$queryString = " create table if not exists Inventory (Ingredient char(50), Quantity integer, primary key(Ingredient))";
//sending query
$status = mysqli_query($conn, $queryString);

if (!$status)
    die("Error running query: " . mysqli_error($conn));
    
 // close the connection
mysqli_close($conn);

?>

<br>
<p> Here are more options you can do:</p>
<a href="create.html"> Create a recipe or add a ingredient to a recipe </a> <br>
<a href="list.html"> List a recipe's ingredients </a> <br>
<a href="buy.html"> Buy all recipe ingredients from the store </a> <br>
<a href="add.html"> Add ingredient to the inventory </a> <br>
