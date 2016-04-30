<!--
    Name: Anoop Toor
    Email: atoor25@uwo.ca
    Date: November 24, 2015
    
    File: UpdateRating.php
    
   
     
-->
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>CS3319 - Databases - Add Rating</title>
</head>
<body>
    <?php
    include 'connectdb.php';
    ?>
    <h1>PSC: Add Rating</h1>
    <form><input type="button" value="BACK" onClick="history.go(-1);return true;"></form>
	<hr>
    <?php
    $ticket = $_POST["goesto"];
    $customerid = strtok($ticket, "|");
    $showingid = strtok("|");
    $rating = $_POST["rating"];
    $query = "UPDATE GOESTO
                    SET Rating='".$rating."'"
                    ." WHERE ShowingID='".$showingid."'"." AND CustomerID='".$customerid."'";
    

        if (!mysqli_query($connection, $query)) {
            die("Error: ADDING RATING failed");
        }
	else{
	echo "Your Rating has been recorded";

	} 
    mysqli_close($connection);
    ?>
</body>
</html>
