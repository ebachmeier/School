
/*
 * Assignment 2
 * 
 * Eric Bachmeier
 * 250738776
 * ebachme@uwo.ca
 * 
 * Program that makes a collage out of images, by modifying the original image with methods
 * created in the Picture class. The original image will be smaller and in the center, with
 * the four modified images surrounding it.
 */

public class MakeCollage
{
  public static void main (String[]args)
  {
    // Create blank picture called collage
    Picture collage = new Picture (932,700);
    // Show the blank canvas
    collage.show();
    
    // Get the current directory for everything in current folder
    String directory = (System.getProperty("user.dir") + "/");
    // Set the media path to load pictures from
    FileChooser.setMediaPath(directory);
    
    // Choose the original picture and load it to fileName
    String fileName = FileChooser.getMediaPath("newYorkPic.jpg");
    // Create pictureLarge from fileName
    Picture pictureLarge = new Picture(fileName);
    // Create smaller pictureObj to be displayed as original photo
    Picture pictureObj = pictureLarge.getPictureWithHeight(200);
    
    // Create 4 pictures to modify from same file
    Picture picture1 = new Picture(fileName);
    Picture picture2 = new Picture(fileName);
    Picture picture3 = new Picture(fileName);
    Picture picture4 = new Picture(fileName);
    
    // Invoke my first method on picture1
    picture1.roundedBorder();
    // Copy picture1 to upper left corner of collage
    collage.copyPictureTo(picture1,0,0);
    
    // Invoke my second method on picture2
    picture2.nightVision();
    // Copy picture2 to upper right corner of collage
    collage.copyPictureTo(picture2,466,0);
    
    // Invoke third method (from lab BONUS) on picture3
    picture3.mirrorDiagonal();
    // Copy picture3 to bottom left corner of collage
    collage.copyPictureTo(picture3,0,350);
    
    // Invoke my fourth method on picture4
    picture4.angleBorder();
    // Copy picture4 to bottom right corner of collage
    collage.copyPictureTo(picture4,466,350);
   
    // Copy smaller orignal photo to center of collage
    collage.copyPictureTo(pictureObj,333,250);
    
    // Save the collage image to same directory
    collage.write(directory + "myCollage.jpg");
    
    // Update collage to show to screen
    collage.repaint();
  }
}
    