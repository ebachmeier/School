<!--
    Name: Anoop Toor
    Email: atoor25@uwo.ca
    Date: November 24, 2015
    
    File: GetShowing.php
   
-->

<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>CS3319 - Databases - Get All Showtimes</title>
</head>
<body>
    <?php
    include 'connectdb.php';
    ?>
    <h1>PSC: Showtimes</h1>
    <form><input type="button" value="BACK" onClick="history.go(-1);return true;"></form>
	<hr>
    <?php

    $tempgenre = $_POST["genre"];
    $genre = strtok($tempgenre, "|");
    $movie = $_POST["movie"];
    $theatre = $_POST["theatre"];

    $startday = $_POST["startday"];
    $startmonth = $_POST["startmonth"];
    $startyear = $_POST["startyear"];
    $starttime = $_POST["starttime"];

    $endday = $_POST["endday"];
    $endmonth = $_POST["endmonth"];
    $endyear = $_POST["endyear"];
    $endtime = $_POST["endtime"];

    $startdate= "$startyear-$startmonth-$startday";
    $enddate= "$endyear-$endmonth-$endday"; 


    $query = 'SELECT DISTINCT *,COUNT(*) as count  FROM MOVIE, GENRE, SHOWING, THEATREROOM WHERE MOVIE.MovieID = GENRE.MovieID AND THEATREROOM.RoomNumber = SHOWING.RoomNumber AND SHOWING.MovieID = MOVIE.MovieID AND GENRE.Genre='."'". $genre ."'" . 'AND MOVIE.MovieID=' ."'".$movie. "'" . ' AND THEATREROOM.RoomNumber='. "'".$theatre."'". ' AND SHOWING.Date>=' ."'".$startdate."'" . ' AND SHOWING.Date<=' ."'".$enddate."'".' AND SHOWING.Time>=' ."'".$starttime."'". ' AND SHOWING.Time<=' ."'".$endtime."'". " GROUP BY MOVIE.MovieID, THEATREROOM.RoomNumber, SHOWING.ShowingID" ;
    $resMovie = mysqli_query($connection, $query);
    if (!$resMovie) {
        die("Show times query failed");
    }
    echo "<table id='display'>";
    echo "<tr>
                <td><b>Poster</td>
                <td><b>Movie</td>
                <td><b>Time and Location</td>
             </tr>";
    
    while ($rowMovie = mysqli_fetch_assoc($resMovie)) {
    	$res = mysqli_query($connection, 'SELECT * FROM SHOWING WHERE MovieID="'.$rowMovie['MovieID'].'"');



    	// If the movie has a one show time or more
    	if ($res &&  mysqli_num_rows($res) > 0) {
    		$times = mysqli_num_rows($res);	
        	echo "<tr>";
        	echo '<td rowspan="'.$times.'">';
        	if ($rowMovie["Poster"] != NULL && file_exists($rowMovie["Poster"])) {
            	echo '<img src="' . $rowMovie["Poster"] . '"height="360px" width="240px"></td>';
       		} else {
           		echo '<img src="Posters/default.jpg"height="360px" width="240px"></td>';
        	}
        	echo '<td rowspan="'.$times.'" valign="top">' . $rowMovie["Name"] . "&nbsp;&nbsp;&nbsp;&nbsp;</td>";
        	$x = 1;
        	while ($row = mysqli_fetch_assoc($res)) {
        		if ($x == 1) {
        			echo "<td valign=\"top\">" . $row["Time"] . " on " . $row["Date"] . " (Theatre Room ". $row["RoomNumber"] . ")</td>";
				echo "</tr>";
				if($row["capacity"] <= $row["count"]){
					echo "WARNING SOLD OUT ". $rowMovie["Name"] . " " . $row["Time"] . " on " . $row["Date"] . " (Theatre Room ". $row["RoomNumber"] .")" ;
				}
       				$x++;
        		}
        		else {
        			echo "<tr><td valign=\"top\">" . $row["Time"] . " on " . $row["Date"] . " (Theatre Room ". $row["RoomNumber"] . ")</td>";
       				echo "</tr>";
       			}
        	}
        }
        mysqli_free_result($res);
    }
    echo "</table>";
    mysqli_free_result($resMovie);
    mysqli_close($connection);
    ?>
</body>
</html>

