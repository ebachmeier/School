<!--
	Name: Eric Bachmeier
	Email: ebachme@uwo.ca
	Date: November 25, 2015
    
    File: DeleteShowing.php

    Description: This file allows the user to modify or delete an existing showtime
-->

<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>CS3319 - Databases - Delete / Modify a Showtime</title>
</head>
<body>
    <?php
    include 'connectdb.php';
    ?>
    <h1>PSC: Update / Delete a Showtime</h1>
    <form><input type="button" value="BACK" onClick="history.go(-1);return true;"></form>
    <hr>
    <?php
    
    $showingid = strlen($_POST["showing"]) > 0 ? mysqli_real_escape_string($connection, $_POST["showing"]) : NULL;
    $newtime = strlen($_POST["time"]) > 0 ? mysqli_real_escape_string($connection, $_POST["time"]) : NULL;
    
    $state = "deleted";
     
    if (strlen($showingid) > 0) {
    	// Delete the room on 0
    	if($_POST['submit'] == 1) {
    		$changeShow = "DELETE FROM SHOWING WHERE 
                    ShowingID='".$showingid."'";
    	}
    	// If update the new show time
    	else if($_POST['submit'] == 0 && strlen($newtime) > 0) {
    		$changeShow = "UPDATE SHOWING 
                    SET Time='".$newtime."'"
                    ." WHERE ShowingID='".$showingid."'";
        	$state = "updated";
    	}
    }
    else {
        echo 'There was no showing selected.<br>';
    }
    
    if (mysqli_query($connection, $changeShow)) {
        echo "The showing time has been " . $state . ".<br>";
    } else {
       	echo "The showing was not updated.";
        echo '<br>';
        echo "Double check your parameters please.";     
        echo mysqli_error($connection);
    }
    mysqli_close($connection);
    ?>
</body>
</html>
