<!--
    Name: Anoop Toor
    Email: atoor25@uwo.ca
    Date: November 24, 2015
    
    File: AddGoesto.php
    

-->
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>CS3319 - Databases - Customer View</title>
</head>
<body>
    <?php
    include 'connectdb.php';
    ?>
    <h1>PSC: Genre Info</h1>
    <form><input type="button" value="BACK" onClick="history.go(-1);return true;"></form>
        <hr>
    <?php
        $query = "SELECT Name, ReleaseYear, Average FROM (SELECT Name, ReleaseYear, AVG(Rating) as Average FROM MOVIE, SHOWING, GOESTO WHERE MOVIE.MovieID = SHOWING.MovieID AND GOESTO.ShowingID = SHOWING.ShowingID GROUP BY NAME) as TEMP  WHERE TEMP.Average >= 4";
        $result = mysqli_query($connection, $query);
        if (!$result) {
           die("Error: Customer View failed");
        }
        echo "<table id='display'>";
        echo "<tr>
                <td><b>Movie Name&nbsp;&nbsp;&nbsp;</td>
                <td><b>Year &nbsp;&nbsp;&nbsp;</td>
                <td><b>Rating &nbsp;&nbsp;&nbsp;</td>
             </tr>";
    while ($row = mysqli_fetch_assoc($result))
    {
        echo "<tr>";
        echo "<td>" . $row["Name"] . "</td>";
        echo "<td>" . $row["ReleaseYear"] . "</td>";
        echo "<td>" . $row["Average"] . "</td>";
        echo "</tr>";
    }
    echo "</table>";
    mysqli_close($connection);
    ?>
</body>
</html>

