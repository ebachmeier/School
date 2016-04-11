<!--
    File: connectdb.php

    Description:  This file connects to the sql database built for this assignment
-->

<?php
$dbhost = "localhost";
$dbuser = "root";
$dbpass = "cs3319";
$dbname = "ebachmedb";

$connection = mysqli_connect($dbhost, $dbuser,$dbpass,$dbname);

if (mysqli_connect_errno()) { die("Error: " . mysqli_connect_error());
}
?>