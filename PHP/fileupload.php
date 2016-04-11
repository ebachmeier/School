<?php
/*
 * Name: Eric Bachmeier
 * Email: ebachme@uwo.ca
 * Date: November 25, 2015
 *
 * File: fileupload.php
 *
 * Description: This file ensures the image file is the proper size and type. 
 * It stores it in a server folder called Posters.
 */

include ('folder.php');
$allowedExts = array("gif", "jpeg", "jpg", "png");
$temp = explode(".", $_FILES["file"]["name"]);
$extension = end($temp);
$extension = strtolower($extension);
$uPlace = dirname(__FILE__) . "/Posters";
$uploadFolder = new Folder;
$moviePic = "NULL";
if ((($_FILES["file"]["type"] == "image/gif")
    || ($_FILES["file"]["type"] == "image/jpeg")
    || ($_FILES["file"]["type"] == "image/jpg")
    || ($_FILES["file"]["type"] == "image/gif")
    || ($_FILES["file"]["type"] == "image/png"))
    && ($_FILES["file"]["size"] < 500000)
    && in_array($extension, $allowedExts)) {
    if ($_FILES["file"]["error"] > 0) {
        echo "Error: " . $_FILES["file"]["error"] . "<br>";
    } else {
        $uploadFolder->createFolder($uPlace);
        if (file_exists("Posters/" . $_FILES["file"]["name"])) {
            echo $_FILES["file"]["name"] . " already exists.";
            echo '<hr>';
            $moviePic = "NULL";
        } else {
            move_uploaded_file($_FILES["file"]["tmp_name"],"Posters/" . $_FILES["file"]["name"]);
            $moviePic = "Posters/" . $_FILES["file"]["name"];
        }
    }
}
else {
	$moviePic = "NULL";
}
?>