<!--
	Name: Eric Bachmeier
	Email: ebachme@uwo.ca
	Date: November 25, 2015
    
    File: AddRoom.php

    Description: This file allows the user to add a theatre room with capacity
-->

<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>CS3319 - Databases - Add a Room</title>
</head>
<body>
    <?php
    include 'connectdb.php';
    ?>
    <h1>PSC: Add a Room</h1>
    <form><input type="button" value="BACK" onClick="history.go(-1);return true;"></form>
	<hr>
    <?php
    $roomnumber = $_POST["roomnumber"];
    $capacity = $_POST["capacity"];
    
    $addedRoom = false;
    
    $findRoom = 'SELECT * FROM THEATREROOM WHERE'.
        ' RoomNumber="'. $roomnumber .'"';
    
    $result = mysqli_query($connection, $findRoom);
    
    if (!$result) {
        echo "There was an error in the THEATREROOM table";
    } else {
        if (mysqli_num_rows($result) > 0) {
            echo "That room already exists in the database";
        }
        else {
        	$addedRoom = true;
        }
    }
    
    if ($addedRoom) {
        
        $query = 'INSERT INTO THEATREROOM
        (RoomNumber, Capacity)
        values("'
        . $roomnumber . '","' 
        . $capacity . '")';
         
        if (!mysqli_query($connection, $query)) {
            die("Error: INSERT INTO THEATREROOM failed");
        } else {
            echo "The new room was added.";
            echo "<table>
                <tr>
                    <td>Room Number</td>
                    <td>" . " " .$_POST['roomnumber']. " (capacity " . $_POST['capacity']. ")</td>
                </tr>
                </table>";
        }
    }
    mysqli_close($connection);
    ?>
</body>
</html>
