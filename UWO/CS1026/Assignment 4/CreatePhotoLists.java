/*
 * Assignment 4
 * 
 * Eric Bachmeier
 * 250738776
 * 
 * CreatePhotoLists class
 * 
 * This class contains the main method for user to create a directry of labelled
 * photos and list them sorted by dates.
 */

public class CreatePhotoLists {
  // main method to test methods in PhotoInfo and PhotoList
  public static void main (String[] args) {
    // prompt user for name of photo infarmation file
    String fileName = SimpleInput.getString("Enter the photo information filename: ");
    // promt user for directory to save photos to
    String directory = SimpleInput.getString("Enter the directory for storing the photos: ");
    // create a new photo list from fileName
    PhotoList myList = new PhotoList(fileName);
    // display the list of photos on screen
    myList.listPhotos();
    System.out.println(); // blank line
    // sort the photos
    myList.sortPhotosByDate();
     // show the labelled photos on the screen
    myList.showPhotos();
    // store the labelled photos to directory passed by user
    myList.storePhotos(directory);
  }
}