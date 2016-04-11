<!--
	Name: Eric Bachmeier
	Email: ebachme@uwo.ca
	Date: November 25, 2015
    
    File: AddGenre.php

    Description: This file allows the user to add a genre to existing movies
-->

<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>CS3319 - Databases - Add Genre</title>
</head>
<body>
    <?php
    include 'connectdb.php';
    ?>
    <h1>PSC: Add a Genre</h1>
    <form><input type="button" value="BACK" onClick="history.go(-1);return true;"></form>
	<hr>
    <?php
    $moviesList = $_POST["movie"];
    $genre = $_POST["genre"];
    
    $addedGenre = false;
    $N = count($moviesList);
 
    for($i = 0; $i < $N; $i++) {
     	$findMovie = 'SELECT * FROM MOVIE WHERE'.
        ' MovieID="'. $moviesList[$i] .'"';
    
    $result = mysqli_query($connection, $findMovie);
    
    if (!$result) {
        echo "There was an error in the MOVIE table";
    } else {
        	$addedGenre = true;
    }
    if ($addedGenre) {
        $query = 'INSERT INTO GENRE
        (MovieID, Genre)
        values("'
        . $moviesList[$i] . '","' 
        . $genre . '")';
         
        if (!mysqli_query($connection, $query)) {
            die("Error: Inserting genre into movie " . $moviesList[$i] . " failed");
        }
    }
    }
    echo "The genre was added to " . $N . " movie(s)";
    mysqli_close($connection);
    ?>
</body>
</html>
