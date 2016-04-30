<!--
	Name: Eric Bachmeier
	Email: ebachme@uwo.ca
	Date: November 29, 2015
    
    File: GetCustomers.php

    Description: This file gets and displays all of customer information from the database
-->

<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>CS3319 - Databases - Get Customers</title>
</head>
<body>
    <?php
    include 'connectdb.php';
    ?>
    <h1>PSC: Customers</h1>
    <form><input type="button" value="BACK" onClick="history.go(-1);return true;"></form>
    <hr>
    <?php
    $query = 'SELECT * FROM CUSTOMER';
    $result = mysqli_query($connection, $query);
    
    if (!$result) {
        die("Customer query failed");
    }
    
    echo "<table id='display'>";
    echo "<tr>
                <td><b>Customer ID&nbsp;&nbsp;&nbsp;</td>
                <td><b>First Name&nbsp;&nbsp;&nbsp;</td>
                <td><b>Last Name&nbsp;&nbsp;&nbsp;</td>
                <td><b>Sex&nbsp;&nbsp;&nbsp;</td>
                <td><b>Email&nbsp;&nbsp;&nbsp;</td>
             </tr>";
    
    while ($row = mysqli_fetch_assoc($result))
    {
        echo "<tr>";
        echo "<td>" . $row["CustomerID"] . "</td>";
        echo "<td>" . $row["FirstName"] . "</td>";
        echo "<td>" . $row["LastName"] . "</td>";
        echo "<td>" . $row["Sex"] . "</td>";
        echo "<td>" . $row["EmailAddress"] . "</td>";
        echo "</tr>";
    }
    echo "</table>";
    
    mysqli_free_result($result);
    mysqli_close($connection);
    ?>
</body>
</html>
