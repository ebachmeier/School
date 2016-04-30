<!--
	Name: Eric Bachmeier
	Email: ebachme@uwo.ca
	Date: November 25, 2015
    
    File: AddNewMovie.php

    Description: This file adds a new customer to the CUSTOMER table
-->

<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>CS3319 - Databases - Add Customer</title>
</head>
<body>
    <?php
    include 'connectdb.php';
    ?>
    <h1>PSC: Add a Customer</h1>
    <form><input type="button" value="BACK" onClick="history.go(-1);return true;"></form>
	<hr>
    <?php
    $firstname = $_POST["first"];
    $lastname = $_POST["last"];
    $sex = $_POST["gender"];
    $email = $_POST["email"];
     
        $query = 'INSERT INTO CUSTOMER
        (FirstName, LastName, Sex, EmailAddress)
        values("'
        . $firstname . '","' 
        . $lastname . '","' 
        . $sex . '","' 
        . $email . '")';
         
        if (!mysqli_query($connection, $query)) {
            die("Error: INSERT INTO CUSTOMER failed");
        } else {
            echo "The new customer was added.";
            echo "<table>
                    <tr>
                        <td>Name:&nbsp;</td>
                        <td>".$_POST['first']." " .$_POST['last']."</td>
                    </tr>
                    <tr>
                        <td>Gender:&nbsp;</td>
                        <td>".$_POST['gender']."</td>
                    </tr>
                    <tr>
                        <td>Email:&nbsp;</td>
                        <td>".$_POST['email']."</td>
                    </tr>
                  </table>";
        }
    mysqli_close($connection);
    
    include 'GetCustomers.php';
    ?>
</body>
</html>
