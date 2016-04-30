<!--
    Name: Anoop Toor
    Email: atoor25@uwo.ca
    Date: November 24, 2015
    
    File: GetGenreCount.php
 
-->
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>CS3319 - Databases - Genre Info</title>
</head>
<body>
    <?php
    include 'connectdb.php';
    ?>
    <h1>PSC: Genre Info</h1>
    <form><input type="button" value="BACK" onClick="history.go(-1);return true;"></form>
        <hr>
    <?php
        $genre = $_POST["genr"];
        $query =  'SELECT COUNT(*) as count, SUM(Price) as sum  FROM GENRE, MOVIE, SHOWING, GOESTO WHERE MOVIE.MovieID = SHOWING.MovieID AND GOESTO.ShowingID = SHOWING.ShowingID AND GENRE.MovieID = MOVIE.MovieID AND GENRE.Genre="'.$genre.'"';

        $result = mysqli_query($connection, $query);
        if (!$result) {
           die("Error: Genre Info failed");
        }
        echo "<table id='display'>";
        echo "<tr>
                <td><b>Number of Movies &nbsp;&nbsp;&nbsp;</td>
                <td><b>Revenue &nbsp;&nbsp;&nbsp;</td>
             </tr>";
    while ($row = mysqli_fetch_assoc($result))
    {
        echo "<tr>";
        echo "<td>" . $row["count"] . "</td>";
        echo "<td>" . $row["sum"] . "</td>";
        echo "</tr>";
    }
    echo "</table>";
    mysqli_close($connection);
    ?>
</body>
</html>

