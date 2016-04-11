<!--
	Name: Eric Bachmeier
	Email: ebachme@uwo.ca
	Date: November 24, 2015
    
    File: DeleteMovie.php

    Description: This file deletes a movie from the MOVIE table
-->

<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>CS3319 - Databases - Delete a Movie</title>
</head>
<body>
    <?php
    include 'connectdb.php';
    ?>
    <h1>PSC: Delete a Movie</h1>
    <form><input type="button" value="BACK" onClick="history.go(-1);return true;"></form>
    <hr>
    <?php
    $movieid = $_POST["id"];
    $moviename = $_POST["name"];
    $releaseyear = $_POST["year"];

    $findMovie = "SELECT * FROM MOVIE WHERE".
        " MovieID='". $movieid ."'". 
        " OR (Name='".$moviename."' AND ReleaseYear='".$releaseyear."')";

    $deleteMovie = "DELETE FROM MOVIE WHERE".
        " MovieID='". $movieid ."'". 
        " OR (Name='".$moviename."' AND ReleaseYear='".$releaseyear."')";
    
    $request = mysqli_query($connection,$findMovie);
    
    if ($request && mysqli_num_rows($request) > 0)
    {
        $mDel = mysqli_fetch_assoc($request);
        if (file_exists($mDel['Poster']) && !in_array($mDel['Poster'], 
            array("Posters/default.jpg")))
        {
        	// Delete the image
            unlink($mDel['Poster']);
        }
        $movieid = $mDel['MovieID'];
        $moviename = $mDel['Name'];
        $releaseyear = $mDel['ReleaseYear'];
        
        if (!mysqli_query($connection, $deleteMovie)) {
            echo '<br>Unable to delete ' . $moviename . ' (' . $releaseyear . ')';
        } else {
            echo '<br>' . $moviename . ' (' . $releaseyear . ') has been removed.';
        }
    } else {
        echo "<br>The movie was not removed.";
        echo '<br>';
        echo "Double check your parameters please.";
        echo '<br>';     
        echo mysqli_error($connection);
    }
    
    include 'GetMoviesID.php';
    ?>
</body>
</html>
