<!--
	Name: Eric Bachmeier
	Email: ebachme@uwo.ca
	Date: November 29, 2015
    
    File: DeleteGenre.php

    Description: This file allows the user to delete an existing genre
-->

<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>CS3319 - Databases - Delete Genre</title>
</head>
<body>
    <?php
    include 'connectdb.php';
    ?>
    <h1>PSC: Delete a Genre</h1>
    <form><input type="button" value="BACK" onClick="history.go(-1);return true;"></form>
    <hr>
    <?php
    $del_genre = strlen($_POST["genre"]) > 0 ? mysqli_real_escape_string($connection, $_POST["genre"]) : NULL;
    
    if (strlen($del_genre) > 0 && mysqli_query($connection, "SELECT * FROM GENRE WHERE GENRE='" . $del_genre . "'")) {
    	// Delete the genre
    		$deleteGenre = "DELETE FROM GENRE WHERE 
                    Genre='".$del_genre."'";
    }
    else {
        die('A valid genre was not chosen.');
    }
    
    if (mysqli_query($connection, $deleteGenre)) {
        echo "The genre has been deleted.<br>";
    } else {
       	echo "The genre was not deleted.";
        echo '<br>';
        echo "Double check your parameters please.";     
        echo mysqli_error($connection);
    }
    mysqli_close($connection);
    ?>
</body>
</html>
