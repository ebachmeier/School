<!--
	Name: Eric Bachmeier
	Email: ebachme@uwo.ca
	Date: November 25, 2015
    
    File: UpdateMovie.php

    Description: This file allows the user to update the information for an existing movie
-->

<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>CS3319 - Databases - Modify a Movie</title>
</head>
<body>
    <?php
    include 'connectdb.php';
    ?>
    <h1>PSC: Update a Movie</h1>
    <form><input type="button" value="BACK" onClick="history.go(-1);return true;"></form>
    <hr>
    <?php
    $from_id = strlen($_POST["moviesList"]) > 0 ? mysqli_real_escape_string($connection, $_POST["moviesList"]) : NULL;
    $to_name = strlen($_POST["newname"]) > 0 ? mysqli_real_escape_string($connection, $_POST["newname"]) : NULL;
    $to_year  = strlen($_POST["newyear"]) > 0 ? mysqli_real_escape_string($connection, $_POST["newyear"]) : NULL;
    
    if (strlen($from_id) > 0) {
    	if (strlen($to_name) > 0 && strlen($to_year) > 0) {
    		$changeMov = "UPDATE MOVIE 
                    SET Name='".$to_name."', ReleaseYear='".$to_year."'"
                    ." WHERE MovieID='".$from_id."'";
    	}
    	// If only the new name field was filled out
    	else if (strlen($to_name) > 0 && (!(strlen($to_year) > 0))) {
    		$changeMov = "UPDATE MOVIE 
                    SET Name='".$to_name."'"
                    ." WHERE MovieID='".$from_id."'";
    	}
    	// If only the new year field was filled out
    	else if (strlen($to_year) > 0 && (!(strlen($to_name) > 0))) {
    		$changeMov = "UPDATE MOVIE 
                    SET ReleaseYear='".$to_year."'"
                    ." WHERE MovieID='".$from_id."'";
    	}
    }
    else {
        echo 'Movie was not chosen for update.<br>';
    }
    
    if (mysqli_query($connection, $changeMov)) {
        echo "The movie has been updated.<br>";
    } else {
       	echo "The movie was not updated.";
        echo '<br>';
        echo "Double check your parameters please.";     
        echo mysqli_error($connection);
    }
    
    $verify = "SELECT * FROM MOVIE
                   WHERE MovieID='$from_id'";
    
    // Check the update 
    $result = mysqli_query($connection, $verify);
    if (!$result) {
        echo "Update Error in MOVIE table";
    } 
    mysqli_close($connection);
    ?>
</body>
</html>
