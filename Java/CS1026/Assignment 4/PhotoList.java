/*
 * Assignment 4
 * 
 * Eric Bachmeier
 * 250738776
 * 
 * PhotoList class
 * 
 * This class models a list of photos and the information can be read from a
 * text file to create a list object. Each object is created from a passed
 * file name. The class includes methods to list, show, store, and sort photos.
 */

import java.util.*;
import java.io.*;
public class PhotoList {
  
  /////////////// fields ///////////////
  private PhotoInfo[] photoArray;
  private int numPhoto = 0;
  
  //////////// constructors ////////////
  // create a photo list object from passed file name
  public PhotoList(String fileName) {
    SimpleReader reader = new SimpleReader(System.getProperty("user.dir") + "/" + fileName);
    // put lines from text file into array
    String [] lineArray = reader.readFile();
    numPhoto = reader.getFileLength();
    // create blank PhotoInfo object array
    photoArray = new PhotoInfo[numPhoto];
    for (int i = 0; i < numPhoto; i++) {
      StringTokenizer tokenizer = new StringTokenizer(lineArray[i]);
      // use String tokenizer to separate the string by spaces for attributes
      String identifier = tokenizer.nextToken();
      int day = Integer.valueOf(tokenizer.nextToken());
      int month = Integer.valueOf(tokenizer.nextToken());
      int year = Integer.valueOf(tokenizer.nextToken());
      String category = tokenizer.nextToken();
      String caption = tokenizer.nextToken();
      String picFileName = tokenizer.nextToken();
      // make a new PhotoInfo object for photo from line in lineArray
      photoArray[i] = new PhotoInfo(identifier, day, month, year, category,
                                       caption, picFileName);
    }
  
  }
  
  ////////////// methods ///////////////
  // method to list the photos on the screen
  public void listPhotos() {
    for (int i = 0; i < numPhoto; i++) {
      // print each line using toString method
      System.out.println(photoArray[i].toString());
    }
  }
  
  // method to show the photos to the screen from photoArray
  public void showPhotos() {
    for (int i = 0; i < numPhoto; i++) {
      Picture labelledPic = new Picture(photoArray[i].getPhotoPic());
      labelledPic.show();
    }
  }
     
  // method to store the photos in a direcotry passed by the user
  public void storePhotos(String directory) {
    // check if directory passed ends with slash
    char end = directory.charAt(directory.length() - 1);
    if (end != '/' || end != '\\')
      // add slash if there isn't one
      directory = directory + "/";
    // check if directory exists
    File directoryFile = new File(directory);
    if (!directoryFile.exists())
      // create directory if it doesn't exist
      directoryFile.mkdirs();
    for (int i = 0; i < numPhoto; i++) {
      Picture labelledPic = new Picture(photoArray[i].getPhotoPic());
      // create custom file saveName from category and Id
      String saveName = photoArray[i].getId() + "_" + photoArray[i].getCategory() + ".jpg";
      // write the photo to that directory
      labelledPic.write(directory + saveName); 
    }
  }
  
  // method to sort the photos by date
  public void sortPhotosByDate() {
    int n; // number of items inserted
    int i;
    // sort photos by year first using insertion sorting
    for (n = 1; n < numPhoto; n++) {
      PhotoInfo key = photoArray[n];
      int keyYear = key.getYear();
      for (i = n - 1; (i >= 0) && (photoArray[i].getYear() < keyYear); i--) {
        photoArray[i+1] = photoArray[i];
      }
      photoArray[i+1] = key;
    }
    // sort photos by month, ensuring still sorted by year
    for (n = 1; n < numPhoto; n++) {
      PhotoInfo key = photoArray[n];
      int keyYear = key.getYear();
      int keyMonth = key.getMonth();
      for (i = n - 1; (i >= 0) && (photoArray[i].getYear() == keyYear) &&
           (photoArray[i].getMonth() < keyMonth); i--) {
        photoArray[i+1] = photoArray[i];
      }
      photoArray[i+1] = key;
    }
    // sort photos by day, ensuring still sorted by month and year
    for (n = 1; n < numPhoto; n++) {
      PhotoInfo key = photoArray[n];
      int keyYear = key.getYear();
      int keyMonth = key.getMonth();
      int keyDay = key.getDay();
      for (i = n - 1; (i >= 0) && (photoArray[i].getYear() == keyYear) && 
           (photoArray[i].getMonth() == keyMonth) &&
           (photoArray[i].getDay() < keyDay); i--) {
        photoArray[i+1] = photoArray[i];
      }
      photoArray[i+1] = key;
    }
    // list photos to screen showing they are sorted
    System.out.println("/////////////// Sorted Photos ///////////////");
    for (int v = 0; v < numPhoto; v++) {
      System.out.println(photoArray[v]);
    }
  }
}

    
 