<!--
	Name: Eric Bachmeier
	Email: ebachme@uwo.ca
	Date: November 24, 2015
    
    File: index.php

    Description: This homepage gives the user two main options for the back end and 
    ticket desk staff
    1. Login as a back-end staff
    2. Login as a ticket desk worker for PSC
-->

<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>CS3319 - Databases - Assignment 3 - Homepage</title>
</head>
<body>
    <h1>Private Screening Company</h1>
    <form action="index.php" method="post">
	<button name="ref">REFRESH</button>&nbsp;&nbsp;&nbsp;By: Eric Bachmeier (<a href="mailto:ebachme@uwo.ca">ebachme@uwo.ca</a>)
	</form>
	<hr>
    <h2>Choose your role</h2>
    <form action="Maintenance.php" method="post">
        <input type="submit" value="Database Maintenance">
    </form>
    <br />
    <form action="TicketClerk.php" method="post">
        <input type="submit" value="Ticket Desk Clerk">
    </form>
</body>
</html>
