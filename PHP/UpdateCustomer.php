<!--
	Name: Eric Bachmeier
	Email: ebachme@uwo.ca
	Date: November 29, 2015
    
    File: UpdateMovie.php

    Description: This file allows the user to update the information for an existing customer
-->

<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>CS3319 - Databases - Modify a Customer</title>
</head>
<body>
    <?php
    include 'connectdb.php';
    ?>
    <h1>PSC: Update a Customer</h1>
    <form><input type="button" value="BACK" onClick="history.go(-1);return true;"></form>
    <hr>
    <?php
    $from_id = strlen($_POST["customer"]) > 0 ? mysqli_real_escape_string($connection, $_POST["customer"]) : NULL;
    $to_first = strlen($_POST["first"]) > 0 ? mysqli_real_escape_string($connection, $_POST["first"]) : NULL;
    $to_last = strlen($_POST["last"]) > 0 ? mysqli_real_escape_string($connection, $_POST["last"]) : NULL;
    $to_gender = strlen($_POST["gender"]) > 0 ? mysqli_real_escape_string($connection, $_POST["gender"]) : NULL;
    $to_email = strlen($_POST["email"]) > 0 ? mysqli_real_escape_string($connection, $_POST["email"]) : NULL;
    
    if (strlen($from_id) > 0) {
    	if (strlen($to_first) > 0) {
    		$changeCust = "UPDATE CUSTOMER 
                    SET FirstName='".$to_first."' WHERE CustomerID='".$from_id."'";
                    mysqli_query($connection, $changeCust);  
        			echo mysqli_error($connection);
        }
        if (strlen($to_last) > 0) {
    		$changeCust = "UPDATE CUSTOMER 
                    SET LastName='".$to_last."' WHERE CustomerID='".$from_id."'";
                    mysqli_query($connection, $changeCust);  
        			echo mysqli_error($connection);
        }
        if (strlen($to_gender) > 0) {
    		$changeCust = "UPDATE CUSTOMER 
                    SET Sex='".$to_gender."' WHERE CustomerID='".$from_id."'";
                    mysqli_query($connection, $changeCust);  
        			echo mysqli_error($connection);
        }
        if (strlen($to_email) > 0) {
    		$changeCust = "UPDATE CUSTOMER 
                    SET EmailAddress='".$to_email."' WHERE CustomerID='".$from_id."'";
                    mysqli_query($connection, $changeCust);  
        			echo mysqli_error($connection);
        }
    	echo "The customer has been updated.<br>";
    }
    else {
        echo 'Customer was not chosen for update.<br>';
    }
    
    include 'GetCustomers.php';

    ?>
</body>
</html>
