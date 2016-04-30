<!--
	Name: Eric Bachmeier
	Email: ebachme@uwo.ca
	Date: November 26, 2015
    
    File: AddShowtime.php

    Description: This file allows the user to add a theatre room with capacity
-->

<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>CS3319 - Databases - Add a Showtime</title>
</head>
<body>
    <?php
    include 'connectdb.php';
    ?>
    <h1>PSC: Add a Showtime</h1>
    <form><input type="button" value="BACK" onClick="history.go(-1);return true;"></form>
	<hr>
    <?php
    $movieid = $_POST["moviesList"];
    $month = $_POST["month"];
    $day = $_POST["day"];
    $year = $_POST["year"];
    $time = $_POST["time"];
    $roomnumber = $_POST["roomnumber"];
    
    $addedShow = false;
     
    if (strlen($year) == 4) {
        $addedShow = true;
    } 
    else if (strlen($year) == 2) {
    	$newyear = "19" . $year;
    	$year = $newyear;
    	$addedShow = true;
    } else {
    	die("Invalid year input");
    }
    
    if ($addedShow) {
        
        // INSERT INTO SHOWING VALUES("333", "2015-02-11", "9:30", (SELECT MovieID FROM MOVIE WHERE Name="Star Wars"), 1);
        $query = 'INSERT INTO SHOWING
        (Date, Time, MovieID, RoomNumber)
        values("' . $year . '-' . $month . '-' . $day . '","' 
        . $time . '","' . $movieid .'","' . $roomnumber . '")';
         
        if (!mysqli_query($connection, $query)) {
            die("Error: INSERT INTO SHOWING failed");
        } else {
            echo "The new showtime was added (ID #" . $movieid . ")";
        }
    }
    mysqli_close($connection);
    ?>
</body>
</html>
