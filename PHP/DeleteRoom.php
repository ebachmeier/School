<!--
	Name: Eric Bachmeier
	Email: ebachme@uwo.ca
	Date: November 25, 2015
    
    File: DeleteRoom.php

    Description: This file allows the user to modify or delete an existing room
-->

<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>CS3319 - Databases - Delete / Modify a Room</title>
</head>
<body>
    <?php
    include 'connectdb.php';
    ?>
    <h1>PSC: Update / Delete a Room</h1>
    <form><input type="button" value="BACK" onClick="history.go(-1);return true;"></form>
    <hr>
    <?php
    $from_room = strlen($_POST["roomnumber"]) > 0 ? mysqli_real_escape_string($connection, $_POST["roomnumber"]) : NULL;
    $to_cap = strlen($_POST["capacity"]) > 0 ? mysqli_real_escape_string($connection, $_POST["capacity"]) : NULL;
    $state = "deleted";
    if (strlen($from_room) > 0) {
    	// Delete the room on 0
    	if ($_POST['submit'] == 1) {
            $changeRoom = "DELETE THEATREROOM, SHOWING FROM THEATREROOM LEFT JOIN SHOWING USING (RoomNumber) WHERE RoomNumber='" . $from_room . "'";
    	}
    	// If update capacity
    	else if (strlen($to_cap) > 0 && $to_cap > 0 && $_POST['submit'] == 0) {
    		$changeRoom = "UPDATE THEATREROOM 
                    SET Capacity='".$to_cap."'"
                    ." WHERE RoomNumber='".$from_room."'";
        	$state = "updated";
    	}
    	else {
    		die('A room capacity needs to be chosen for update.');
    	}
    }
    else {
        die('Room was not chosen for update.');
    }
    
    if (mysqli_query($connection, $changeRoom)) {
        echo "The room has been " . $state . ".<br>";
    } else {
       	echo "The room was not updated.";
        echo '<br>';
        echo "Double check your parameters please.";     
        echo mysqli_error($connection);
    }
    mysqli_close($connection);
    ?>
</body>
</html>
