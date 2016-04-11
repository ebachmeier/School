<!--
	Name: Eric Bachmeier
	Email: ebachme@uwo.ca
	Date: November 24, 2015
    
    File: Maintenance.php
    
    Description: This file provides an interface for the database maintenance staff to do
    the following:
    1. Add, delete, and update movies including adding a 240 x 360 movie poster
    2. List all movies by year or alphabetically
    3. Add, delete, and modify genre info
    4. Add, delete, and modify the room number and capacity in the theatre
    5. Add, delete, and modify the movie showings
    6. List all the movie showings
    7. Add, delete, and modify the customer information
    8. List all the customers in the database
-->

<!DOCTYPE html>

<?php 
// Define your username and password 
$username = "PSCadmin"; 
$password = "password"; 

// If the username and password are not valid
if ($_POST['inUser'] != $username || $_POST['inPass'] != $password) { 
?>

<html>
<head>
    <meta charset="utf-8">
    <title>CS3319 - Databases - Assignment 3 - DB Login</title>
</head>
<body>
<h1>PSC: Login</h1>
<form action="index.php" method="post">
    <button name="home">HOME</button>
</form>
<hr>
<form name="form" method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
    <p>
        <label for="inUser">Username</label>
        <br />
        <input type="text" value="PSCadmin" placeholder="PSCadmin" name="inUser" />
    </p>

    <p>
        <label for="inPass">Password</label>
        <br />
        <input type="password" value="" name="inPass" autofocus/>
    </p>

    <p>
        <input type="submit" name="Submit" value="Login" />
    </p>
    <p>
    TA please use Password 'password' to login
    </p>
    
</form>
</body>
</html>

<?php 
} 
// If the username and password are valid
else { 
?>

<html>
<head>
    <meta charset="utf-8">
    <title>CS3319 - Databases - Assignment 3 - DB Maintenance</title>
</head>
<body>
    <?php
    include 'connectdb.php';
    ?>
    <h1>PSC: Database Maintenance</h1>
    <form action="index.php" method="post">
        <button name="home">HOME</button>
    </form>
    <hr>
    <h2>Movies</h2>
    <form action="GetMoviesYear.php" method="post">
        <button name="submit">Get Movies by Year</button>
    </form>
    <br />
    <form action="GetMoviesName.php" method="post">
        <button name="submit">Get Movies by Name</button>
    </form>
    <hr>
    
    <h2>Add a New Movie</h2>
    <form action="AddNewMovie.php" method="post" enctype="multipart/form-data">
        <table>
            <tr>
                <td>Movie Name</td>
                <td>
                    <input type="text" name="name"></td>
            </tr>
            <tr>
                <td>Year of Release</td>
                <td>
                    <input type="text" name="year"></td>
            </tr>
            <tr>
                <td>Movie Poster (optional)</td>
                <td>
                    <input type="file" name="file" id="file" accept="image/x-jpg, image/jpeg, image/png, image/gif"><br>
                </td>
            </tr>
        </table>
        <br>
        <input type="submit" name="AddNewMovie" value="Add Movie">
    </form>

    <hr>
    <h2>Delete a Movie</h2>
    <form action="DeleteMovie.php" method="post" enctype="multipart/form-data">
        <table>
            <tr>
                <td>Movie ID</td>
                <td>
                    <input type="text" name="id" value=""></td>
            </tr>
            <tr>
                <td>OR</td>
            </tr>
            <tr>
                <td>Movie Name</td>
                <td>
                    <input type="text" name="name" value=""></td>
            </tr>
            <tr>
                <td>Release Year</td>
                <td>
                    <input type="text" name="year" value=""></td>
            </tr>
        </table>
        <br />
        <input type="submit" name="DeleteMovie" value="Delete Movie">
    </form>

    <hr>
    <h2>Modify a Movie</h2>
    <form action="UpdateMovie.php" method="post" enctype="multipart/form-data">
        <table>
            <tr>
                <td>FROM:</td>
                <td>&nbsp;</td>
                <td>
            <select name="moviesList">
            <option value="">-- Select Movie (refresh to see all) --</option>
			<?php
				$query = "SELECT * FROM MOVIE";
				$result = mysqli_query($connection, $query);
				while ($row = mysqli_fetch_array($result)){
					echo "<option value=\"" . $row['MovieID'] . "\">" . $row['Name'] . " (" . $row['ReleaseYear'] . ")" . "</option>";
				}
			?>
			</select>
			</td>
            </tr>
            
            <tr>
                <td>TO:</td>
                <td>New Name</td>
                <td>
                    <input type="text" name="newname"></td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td>&nbsp;</td>
                <td>New Release</td>
                <td>
                    <input type="text" name="newyear"></td>
                <td>&nbsp;</td>
            </tr>
        </table>
        <br />
        <input type="submit" name="UpdateMovie" value="Update Movie">
    </form>

    <hr>
    <h2>Add a Theatre Room</h2>
    <form action="AddRoom.php" method="post" enctype="multipart/form-data">
        <table>
            <tr>
                <td>Room Number</td>
                <td>
            <select name="roomnumber">
            <option value="">-- Choose Room --</option>
			<?php
				$x = 1;
				while ($x < 21) {
					$query = 'SELECT * FROM THEATREROOM WHERE'.
        ' RoomNumber="'. $x .'"';
					$result = mysqli_query($connection, $query);
					if (mysqli_num_rows($result) < 1 || (!($result))) {
						echo "<option value=\"" . $x . "\">" . "Room " . $x . "</option>";
					}
					$x++;
				}
			?>
			</select>
			</td>
            </tr>
            <tr>
                <td>Room Capacity</td>
                <td>
                    <input type='number' size='10' step="5" id='capacity' name='capacity' value='0' /></td>
            </tr>
        </table>
        <br />
        <input type="submit" name="AddRoom" value="Add Room">
    </form>

    <hr>
    <h2>Modify / Delete Room</h2>
    <form action="DeleteRoom.php" method="post" enctype="multipart/form-data">
        <table>
            <tr>
                <td>Room Number</td>
                <td>
            <select name="roomnumber">
            <option value="">-- Choose Room --</option>
			<?php
				$query = "SELECT * FROM THEATREROOM";
				$result = mysqli_query($connection, $query);
				while ($row = mysqli_fetch_array($result)){
					echo "<option value=\"" . $row['RoomNumber'] . "\">"  . "Room " . $row['RoomNumber'] . " (current cap. " . $row['Capacity'] . ")</option>";
				}
			?>
			</select>
			</td>
            </tr>
            
            
            <tr>
                <td>New Capacity</td>
                <td>
                    <input type='number' size='10' step="5" id='capacity' name='capacity' value='0' /></td>
            </tr>
        </table>
        <br>
        <table>
            <tr>
                <td>
                    <button type="submit" name="submit" value="0">Update Room</button></td>
                <td>
                    <button type="submit" name="submit" value="1">Delete Room</button></td>
            </tr>
        </table>
    </form>
    
    <hr>
    <h2>Show Times</h2>
    <form action="GetShowtimes.php" method="post">
        <button name="submit">Show All Showtimes</button>
    </form>

    <hr>
    <h2>Add Showtime</h2>
    <form action="AddShowtime.php" method="post" enctype="multipart/form-data">
        <table>
            <tr>
                <td>Movie</td>
                <td>
            <select name="moviesList">
            <option value="">-- Select Movie --</option>
			<?php
				$query = "SELECT * FROM MOVIE";
				$result = mysqli_query($connection, $query);
				while ($row = mysqli_fetch_array($result)){
					echo "<option value=\"" . $row['MovieID'] . "\">" . $row['Name'] . " (" . $row['ReleaseYear'] . ")" . "</option>";
				}
			?>
			</select>
			</td>
            </tr>
            
            <tr>
                <td>Date</td>
                <td>
                    <select name="month">
                    <option value="">-- Month --</option>
                    <option value="01">January</option>
                    <option value="02">February</option>
                    <option value="03">March</option>
                    <option value="04">April</option>
        			<option value="05">May</option>
                    <option value="06">June</option>
                    <option value="07">July</option>
                    <option value="08">August</option>
                    <option value="09">September</option>
                    <option value="10">October</option>
                    <option value="11">November</option>
                    <option value="12">December</option>
                    </td>
            </tr>
            
            <tr>
            <td>&nbsp;</td>
             <td>
                <input type="number" min="1" max ="31" value="1" name="day"></td>
            </tr>
            
            <tr>
             <td>&nbsp;</td>
             <td>
                <input type="text" onfocus="if(this.value == 'Year') { this.value = ''; }" value="Year" name="year"></td>
            </tr>
            
             <tr>
                <td>Time</td>
                <td>
                    <select name="time">
                     <option value="06:00:00">6:00 PM</option>
                    <option value="06:30:00">6:30 PM</option>
                    <option value="07:00:00">7:00 PM</option>
                    <option value="07:30:00">7:30 PM</option>
                    <option value="08:00:00">8:00 PM</option>
                    <option value="08:30:00">8:30 PM</option>
                    <option value="09:00:00">9:00 PM</option>
                    <option value="09:30:00">9:30 PM</option>
                    <option value="10:00:00">10:00 PM</option>
                    <option value="10:30:00">10:30 PM</option>
                    <option value="11:00:00">11:00 PM</option>
                    <option value="11:30:00">11:30 PM</option>
                    </td>
            </tr>
            
            <tr>
                <td>Room Number</td>
                <td>
            <select name="roomnumber">
            <option value="">-- Choose Room --</option>
			<?php
				$query = "SELECT * FROM THEATREROOM";
				$result = mysqli_query($connection, $query);
				while ($row = mysqli_fetch_array($result)){
					echo "<option value=\"" . $row['RoomNumber'] . "\">"  . "Room " . $row['RoomNumber'] . " (current cap. " . $row['Capacity'] . ")</option>";
				}
			?>
			</select>
			</td>
            </tr>
        
        </table>
        <br />
        <input type="submit" name="AddShowtime" value="Add Showtime">
    </form>

    <hr>
    <h2>Modify or Delete Showtime</h2>
    <form action="DeleteShowing.php" method="post" enctype="multipart/form-data">
        <table>
            <tr>
                <td>Showing</td>
                <td>
            <select name="showing">
            <option value="">-- Choose Showtime --</option>
			<?php
				$query = "SELECT * FROM SHOWING";
				$result = mysqli_query($connection, $query);
				while ($row = mysqli_fetch_array($result)){
					$moviecur = mysqli_query($connection, 'SELECT * FROM MOVIE WHERE MovieID=' . $row['MovieID']);
					$rowMovie = mysqli_fetch_array($moviecur);
					echo "<option value=\"" . $row['ShowingID'] . "\">" . $rowMovie['Name'] . " (" . $rowMovie['ReleaseYear'] . ") " . $row['Time'] .
					" on " . $row['Date'] . "</option>";
				}
			?>
			</select>
			</td>
            </tr>
    
            <tr>
                <td>New Start Time</td>
                <td>
                    <select name="time">
                     <option value="06:00:00">6:00 PM</option>
                    <option value="06:30:00">6:30 PM</option>
                    <option value="07:00:00">7:00 PM</option>
                    <option value="07:30:00">7:30 PM</option>
                    <option value="08:00:00">8:00 PM</option>
                    <option value="08:30:00">8:30 PM</option>
                    <option value="09:00:00">9:00 PM</option>
                    <option value="09:30:00">9:30 PM</option>
                    <option value="10:00:00">10:00 PM</option>
                    <option value="10:30:00">10:30 PM</option>
                    <option value="11:00:00">11:00 PM</option>
                    <option value="11:30:00">11:30 PM</option>
                    </td>
            </tr>
        </table>
       <br>
        <table>
            <tr>
                <td>
                    <button type="submit" name="submit" value="0">Update the Movie Time</button></td>
                <td>
                    <button type="submit" name="submit" value="1">Delete Showing</button></td>
            </tr>
        </table>
    </form>
    <hr>
    
     <h2>Genres</h2>
    <form action="GetGenres.php" method="post">
        <button name="submit">Get All Genres</button>
    </form>
    <hr>
    
     <h2>Add Genre</h2>
    <form action="AddGenre.php" method="post" enctype="multipart/form-data">
        <table>
        
        <tr>
                <td>Select Movie(s)</td>
                <td>
			<?php
				$query = "SELECT * FROM MOVIE";
				$result = mysqli_query($connection, $query);
				while ($row = mysqli_fetch_array($result)){
					echo "<input type=\"checkbox\" name=\"movie[]\" value=\"" . $row['MovieID'] . "\">" . $row['Name'] . " (" . $row['ReleaseYear'] . ")<br>";
				}
			?>
			</select>
		</td>
        </tr>
    	
    	<tr>
            <td>Genre Name</td>
             <td>
                <input type="text" name="genre"></td>
            </tr>
    
    	</table>
        <br />
        <input type="submit" name="AddGenre" value="Add Genre">
    </form>
    <hr>
    
    <h2>Delete Genre</h2>
    <form action="DeleteGenre.php" method="post" enctype="multipart/form-data">
        <table>
            <tr>
                <td>Choose Genre</td>
                <td>
                    <input type="text" name="genre"></td>
            </tr>
        </table>
        <br>
        <input type="submit" name="DeleteGenre" value="Delete Genre">
    </form>
    <hr>
    
    <h2>Customers</h2>
    <form action="GetCustomers.php" method="post">
        <button name="submit">Get All Customers</button>
    </form>
    <hr>
    
    <h2>Add a New Customer</h2>
    <form action="AddCustomer.php" method="post" enctype="multipart/form-data">
        <table>
            <tr>
                <td>First Name</td>
                <td>
                    <input type="text" name="first"></td>
            </tr>
            <tr>
                <td>Last Name</td>
                <td>
                    <input type="text" name="last"></td>
            </tr>
           <tr>
                <td>Gender</td>
                <td>
                    <input type="radio" name="gender" value="M">&nbsp;Male&nbsp;&nbsp;&nbsp;<input type="radio" name="gender" value="F">&nbsp;Female</td>
            </tr>
             <tr>
                <td>Email</td>
                <td>
                    <input type="text" name="email"></td>
            </tr>
        </table>
        <br>
        <input type="submit" name="AddCustomer" value="Add Customer">
    </form>
    
    <hr>
    
    <h2>Delete a Customer</h2>
    <form action="DeleteCustomer.php" method="post" enctype="multipart/form-data">
        <table>
            <tr>
                <td>Customer ID</td>
                <td>
                    <input type="text" name="id" value=""></td>
            </tr>
            <tr>
                <td>OR</td>
            </tr>
            <tr>
                <td>First Name</td>
                <td>
                    <input type="text" name="first" value=""></td>
            </tr>
            <tr>
                <td>Last Name</td>
                <td>
                    <input type="text" name="last" value=""></td>
            </tr>
        </table>
        <br />
        <input type="submit" name="DeleteCustomer" value="Delete Customer">
    </form>
    
    <hr>
    
    <h2>Modify a Customer</h2>
    <form action="UpdateCustomer.php" method="post" enctype="multipart/form-data">
        <table>
            <tr>
                <td>FROM:</td>
                <td>&nbsp;</td>
                <td>
            <select name="customer">
            <option value="">-- Select Customer --</option>
			<?php
				$query = "SELECT * FROM CUSTOMER";
				$result = mysqli_query($connection, $query);
				while ($row = mysqli_fetch_array($result)){
					echo "<option value=\"" . $row['CustomerID'] . "\">" . $row['FirstName'] . " " . $row['LastName'] . ", " . $row['Sex'] . " (" . $row['EmailAddress'] . ")</option>";
				}
			?>
			</select>
			</td>
            </tr>
            
            <tr>
                <td>TO:</td>
                <td>First Name</td>
                <td>
                    <input type="text" name="first" value=""></td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td>&nbsp;</td>
                <td>Last Name</td>
                <td>
                    <input type="text" name="last" value=""></td>
                <td>&nbsp;</td>
            </tr>
             <tr>
             <td>&nbsp;</td>
                <td>Gender</td>
                <td>
                    <input type="radio" name="gender" value="M">&nbsp;Male&nbsp;&nbsp;&nbsp;<input type="radio" name="gender" value="F">&nbsp;Female</td>
            <td>&nbsp;</td>
            </tr>
            <tr>
                <td>&nbsp;</td>
                <td>Email</td>
                <td>
                    <input type="text" name="email" value=""></td>
                <td>&nbsp;</td>
            </tr>
        </table>
        <br />
        <input type="submit" name="UpdateCustomer" value="Update Customer">
    </form>

	<hr>
     
    &nbsp;By: Eric Bachmeier (<a href="mailto:ebachme@uwo.ca">ebachme@uwo.ca</a>)

    <?php
    mysqli_close($connection);
    ?>
</body>
</html>

<?php 
} 
?>