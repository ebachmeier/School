<!--
    Name: Anoop Toor
    Email: atoor25@uwo.ca
    Date: November 24, 2015
    
    File: AddGoesto.php
    
    Description: This file provides an interface for the ticket desk staff to do
    the following:
    1. 
-->

<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>CS3319 - Databases - Add a Ticket</title>
</head>
<body>
    <?php
    include 'connectdb.php';
    ?>
    <h1>PSC: Add a Ticket</h1>
    <form><input type="button" value="BACK" onClick="history.go(-1);return true;"></form>
    <hr>
    <?php
    $customerid = $_POST["customer"];
    $showingid = $_POST["showing"];
    $price = $_POST["price"];
    $rating = 0;
    $addedTicket = true;

    if ($addedTicket) {
        // INSERT INTO SHOWING VALUES("333", "2015-02-11", "9:30", (SELECT MovieID FROM MOVIE WHERE Name="Star Wars"), 1);
            $query = 'INSERT INTO GOESTO
        (CustomerID, ShowingID, Price, Rating)
        values("'
        . $customerid . '","' 
        . $showingid . '","' 
        . $price . '","' 
        . $rating . '")';
        if (!mysqli_query($connection, $query)) {
            die("Error: INSERT INTO GOESTO failed. Did you already buy this ticket?");
        } else {
            echo "The new ticket was added (ID #" . $customerid . " " . $showingid . ")";
        }
    }
    mysqli_close($connection);
    ?>
</body>

