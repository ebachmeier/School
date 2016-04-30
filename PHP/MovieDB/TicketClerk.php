<!--
	Name: Anoop Toor & Eric Bachmeier
	Email: ebachme@uwo.ca
	Date: November 24, 2015
    
    File: TicketClerk.php
    
    Description: This file provides an interface for the ticket desk staff to do
    the following:
    1. 
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
    <title>CS3319 - Databases - Assignment 3 - Ticket Desk Login</title>
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
    <title>CS3319 - Databases - Assignment 3 - Ticket Desk Clerk</title>
</head>
<body>
    <?php
    include 'connectdb.php';
    ?>
    <h1>PSC: Ticket Desk</h1>
    <form action="index.php" method="post">
        <button name="home">HOME</button>
    </form>
    <hr>
    <h2>Buy Tickets</h2>	
    <form action="AddGoesto.php" method="post">
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
			<br>
			<span>Price:    </span><input type="text" name="price">
			</br>

        		<button name="submit">Purchase Tickets</button>
			</br>


    </form> 
   <hr>
   <h2>Add Rating</h2>
       <form action="UpdateRating.php" method="post">
         <select name="goesto">
            <option value="">-- Select Ticket(CustomerID, ShowingID, Price, Rating) --</option>
                        <?php
                                $query = "SELECT * FROM GOESTO WHERE RATING = 0";
                                $result = mysqli_query($connection, $query);
                                while ($row = mysqli_fetch_array($result)){
                                        echo "<option value=\"" . $row['CustomerID'] . "|" . $row['ShowingID'] . "\">" . $row['CustomerID'] . ", " . $row['ShowingID'] . ", " . $row['Price'] . ", " . $row['Rating'] . "</option>";

                                }
                        ?>
        </select>
        <select name="rating">
            <option value="">-- Select Select Rating --</option>
           		 <option value='1'">One Star</option>
                         <option value='2'>Two Star</option>
                         <option value='3'>Three Star</option>
                         <option value='4'>Four Star</option>
                         <option value='5'>Five Star</option>

        </select>
	<br>
		<button name="submit">Add Rating</button>
	</br>
    </form>
   </hr>
   <hr>
 	<h2>Get Showings</h2>
       <form action="GetShowing.php"  method="post">
	<select name = "genre">
	<option value="">-- Select Genre --</option>
                        <?php
                                $query = "SELECT DISTINCT Genre FROM GENRE";
                                $result = mysqli_query($connection, $query);
                                while ($row = mysqli_fetch_array($result)){
					echo "<option value=\"" . $row['Genre'] .  "\">" . $row['Genre'] . "</option>";

                                }
                        ?>

        </select>
	<select name= "movie">
	<option value="">-- Select Movie --</option>
		<?php
				$query = "SELECT * FROM MOVIE";
				$result = mysqli_query($connection, $query);
				while ($row = mysqli_fetch_array($result)){
					echo "<option value=\"" . $row['MovieID'] . "\">" . $row['Name'] . " " . $row['ReleaseYear'] . "</option>";
				}
			?>
	</select>
	<select name= "theatre">
        <option value="">-- Select Theatre(Capacity, Room Number) --</option>
                <?php
                                $query = "SELECT * FROM THEATREROOM";
                                $result = mysqli_query($connection, $query);
                                while ($row = mysqli_fetch_array($result)){
                                        echo "<option value=\"" . $row['RoomNumber'] . "\">" . $row['RoomNumber'] . " " . $row['Capacity'] . "</option>";
                                }
                        ?>
        </select>
	<br>
        <tr>
                <td>Start Date:</td>
                <td>
                    <select name="startmonth">
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
                <input type="number" min="1" max ="31" value="1" name="startday"></td>
            </tr>

            <tr>
             <td>&nbsp;</td>
             <td>
                <input type="text" onfocus="if(this.value == 'Year') { this.value = ''; }" value="Start Year" name="startyear"></td>
            </tr>

             <tr>
                <td>Time</td>
                <td>
                    <select name="starttime">
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
	</select>
	</br>
	<tr>
                <td>End Date  :</td>
                <td>
                    <select name="endmonth">
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
                <input type="number" min="1" max ="31" value="1" name="endday"></td>
            </tr>

            <tr>
             <td>&nbsp;</td>
             <td>
                <input type="text" onfocus="if(this.value == 'Year') { this.value = ''; }" value="End Year" name="endyear"></td>
            </tr>

             <tr>
                <td>Time</td>
                <td>
                    <select name="endtime">
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
		    </select>
                    </td>
            </tr>

		<br>
		<button name="submit">Get Showing</button>

   </form>



   </hr>
   <hr>
    <h2>Get Movies a Customer has viewed</h2>
    <form action="GetCustomerView.php" method="post">
         <select name="cust">
            <option value="">-- Select Customer --</option>
                        <?php
                                $query = "SELECT * FROM CUSTOMER";
                                $result = mysqli_query($connection, $query);
                                while ($row = mysqli_fetch_array($result)){
                                        echo "<option value=\"" . $row['CustomerID'] . "\">" . $row['FirstName'] . " " . $row['LastName'] . ", " . $row['Sex'] . " (" . $row['EmailAddress'] . ")</option>";
                                }
                        ?>
        </select>

        <br>

            <button name="submit">Get Movie List</button>
        </br>


  </form>
   <hr>
   <h2>Get a Customer profile</h2>
    <form action="GetCustomerProfile.php" method="post">
         <select name="custo">
            <option value="">-- Select Customer --</option>
                        <?php
                                $query = "SELECT * FROM CUSTOMER";
                                $result = mysqli_query($connection, $query);
                                while ($row = mysqli_fetch_array($result)){
                                        echo "<option value=\"" . $row['CustomerID'] . "\">" . $row['FirstName'] . " " . $row['LastName'] . ", " . $row['Sex'] . " (" . $row['EmailAddress'] . ")</option>";
                                }
                        ?>
        </select>

        <br>

            <button name="submit">Get Profile</button>
        </br>

  </hr>
  </form> 
  <hr>
        <h2>Get Genre Count<h2>
         <form action="GetGenreCount.php"  method="post">
        <select name = "genr">
        <option value="">-- Select Genre --</option>
                        <?php
                                $query = "SELECT DISTINCT Genre FROM GENRE";
                                $result = mysqli_query($connection, $query);
                                while ($row = mysqli_fetch_array($result)){
                                        echo "<option value=\"" . $row['Genre'] . "\">" . $row['Genre'] . "</option>";

                                }
                        ?>

        </select>
        <br>

            <button name="submit">Get Genre Count</button>
        </br>



  </form>
  </hr>
  <hr>
	<h2>Get List of Four Star + Movies </h2>
	<form action="GetMovieGood.php" method"post">
	<button name="submit"> Get Good Movies</button>
	</form>



 </hr>

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
