<!--
	Name: Eric Bachmeier
	Email: ebachme@uwo.ca
	Date: November 25, 2015
    
    File: AddNewMovie.php

    Description: This file adds a new movie to the MOVIE table
-->

<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>CS3319 - Databases - Add a Movie</title>
</head>
<body>
    <?php
    include 'fileupload.php';
    include 'connectdb.php';
    ?>
    <h1>PSC: Add a Movie</h1>
    <form><input type="button" value="BACK" onClick="history.go(-1);return true;"></form>
	<hr>
    <?php
    $moviename = $_POST["name"];
    $releaseyear = $_POST["year"];
    
    $addedMovie = false;
    
    $findMovie = 'SELECT * FROM MOVIE WHERE'.
        ' Name="'. $moviename .'"'. 
        ' AND ReleaseYear="'.$releaseyear.'"';
    
    $result = mysqli_query($connection, $findMovie);
    
    if (!$result) {
        echo "There was an error in the MOVIE table";
    } else {
        if (mysqli_num_rows($result) > 0) {
            echo "That movie already exists in the database";
        }
        else {
        	$addedMovie = true;
        }
    }
    
    if ($addedMovie) {
        if ($moviePic == NULL || $moviePic == 'NULL') {
            $moviePic = 'Posters/default.jpg';
        }
        
        $query = 'INSERT INTO MOVIE
        (Name, ReleaseYear, Poster)
        values("'
        . $moviename . '","' 
        . $releaseyear . '","' 
        . $moviePic . '")';
         
        if (!mysqli_query($connection, $query)) {
            die("Error: INSERT INTO MOVIE failed");
        } else {
            echo "The new movie was added.";
            echo "<table>
                    <tr>
                        <td>Poster</td>
                        <td><img src='$moviePic' height='360' width='240'></td>
                    </tr>
                    <tr>
                        <td>Name:&nbsp;</td>
                        <td>".$_POST['name']."</td>
                    </tr>
                    <tr>
                        <td>Release Year:&nbsp;</td>
                        <td>".$_POST['year']."</td>
                    </tr>
                  </table>";
        }
    }
    mysqli_close($connection);
    
    include 'GetMoviesID.php';
    ?>
</body>
</html>
