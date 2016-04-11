<!--
	Name: Eric Bachmeier
	Email: ebachme@uwo.ca
	Date: November 24, 2015
    
    File: GetMovies.php

    Description: This file gets and displays all of the movies from the database in order
    of newest to oldest
-->

<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>CS3319 - Databases - Get Movies by ID</title>
</head>
<body>
    <?php
    include 'connectdb.php';
    ?>
    <h1>PSC: Movies by ID</h1>
    <form><input type="button" value="BACK" onClick="history.go(-1);return true;"></form>
    <hr>
    <?php
    $query = 'SELECT * FROM MOVIE ORDER BY MovieID DESC;';
    $result = mysqli_query($connection, $query);
    
    if (!$result) {
        die("Movie query failed");
    }
    
    echo "<table id='display'>";
    echo "<tr>
                <td>Poster</td>
                <td>Movie ID&nbsp;&nbsp;&nbsp;</td>
                <td>Name</td>
                <td>Release Year</td>
             </tr>";
    
    while ($row = mysqli_fetch_assoc($result))
    {
        echo "<tr>";
        echo '<td>';
        if ($row["Poster"] != NULL && file_exists($row["Poster"])) {
            echo '<img src="' . $row["Poster"] . '"height="360px" width="240px"></td>';
        } else {
            echo '<img src="Posters/default.jpg"height="360px" width="240px"></td>';
        }
        echo "<td>" . $row["MovieID"] . "</td>";
        echo "<td>" . $row["Name"] . "</td>";
        echo "<td>" . $row["ReleaseYear"] . "</td>";
        echo "</tr>";
    }
    echo "</table>";
    
    mysqli_free_result($result);
    mysqli_close($connection);
    ?>
</body>
</html>
