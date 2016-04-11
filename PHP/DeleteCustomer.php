<!--
	Name: Eric Bachmeier
	Email: ebachme@uwo.ca
	Date: November 29, 2015
    
    File: DeleteCustomer.php

    Description: This file allows the user to delete a customer from the database
-->

<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>CS3319 - Databases - Delete Customer</title>
</head>
<body>
 <?php
    include 'connectdb.php';
    ?>
    <h1>PSC: Delete a Customer</h1>
    <form><input type="button" value="BACK" onClick="history.go(-1);return true;"></form>
    <hr>
   <?php
    $customerid = $_POST["id"];
    $firstname = $_POST["first"];
    $lastname = $_POST["last"];

    $findCust = "SELECT * FROM CUSTOMER WHERE".
        " CustomerID='". $customerid ."'". 
        " OR (FirstName='".$firstname."' AND LastName='".$lastname."')";

    $deleteCust  = "DELETE GOESTO, CUSTOMER FROM CUSTOMER LEFT JOIN GOESTO USING (CustomerID) WHERE CustomerID='". $customerid ."'". 
        " OR (FirstName='".$firstname."' AND LastName='".$lastname."')";
    
    $request = mysqli_query($connection, $findCust);
    
    if ($request && mysqli_num_rows($request) > 0)
    {
        $mDel = mysqli_fetch_assoc($request);
        $customerid = $mDel['CustomerID'];
        $firstname = $mDel['FirstName'];
        $lastname = $mDel['LastName'];
        
        if (!mysqli_query($connection, $deleteCust)) {
            echo '<br>Unable to delete ' . $firstname . ' ' . $lastname;
        } else {
            echo '<br>' . $firstname . ' ' . $lastname . ' has been removed.';
        }
    } else {
        echo "<br>The customer was not removed.";
        echo '<br>';
        echo "Double check your parameters please.";
        echo '<br>';     
        echo mysqli_error($connection);
    }
    
    include 'GetCustomers.php';
    ?>
</body>
</html>