<?php
/*
 * Name: Eric Bachmeier
 * Email: ebachme@uwo.ca
 * Date: November 25, 2015
 *
 * File: folder.php
 *
 * Description: This class creates the folder on the server called Posters to store images
 */
 
class Folder {
  function createFolder($name) {
    if(is_dir($name)) {
      return false; 
      }
    else {
      mkdir($name, 0777);
      $error = error_get_last();
      echo $error['message'];
      return false;
    }
  }
}
?>