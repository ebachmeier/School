<!--
	Name: Eric Bachmeier
	Email: ebachme@uwo.ca
	Date: November 29, 2015
    
    File: GetGenres.php

    Description: This file gets and displays all of the genres in the database
-->

<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>CS3319 - Databases - Get Genres</title>
</head>
<body>
    <?php
    include 'connectdb.php';
    ?>
    <h1>PSC: Genres by Movie</h1>
    <form><input type="button" value="BACK" onClick="history.go(-1);return true;"></form>
    <hr>
    <?php
    $query = 'SELECT * FROM GENRE';
    $result = mysqli_query($connection, $query);
    
    if (!$result) {
        die("Genre query failed");
    }
    
    echo "<table id='display'>";
    echo "<tr>
                <td><b>Movie</td>
                <td><b>Genre</td>
             </tr>";
    
    while ($row = mysqli_fetch_assoc($result))
    {
        echo "<tr>";
        $resMovie = mysqli_query($connection, "SELECT * FROM MOVIE WHERE MovieID='" . $row['MovieID'] . "'");
        $rowMovie = mysqli_fetch_assoc($resMovie);
        echo "<td>" . $rowMovie["Name"] . "&nbsp;&nbsp;&nbsp;</td>";
        echo "<td>" . $row["Genre"] . "</td>";
        echo "</tr>";
    }
    echo "</table>";
    
    mysqli_free_result($result);
    mysqli_close($connection);
    ?>
</body>
</html>
