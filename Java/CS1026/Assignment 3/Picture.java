import java.awt.*;
import java.awt.font.*;
import java.awt.geom.*;
import java.text.*;

/**
 * A class that represents a picture.  This class inherits from 
 * SimplePicture and allows the student to add functionality to
 * the Picture class.  
 * 
 * Copyright Georgia Institute of Technology 2004-2005
 * @author Barbara Ericson ericson@cc.gatech.edu
 */
public class Picture extends SimplePicture 
{
  ///////////////////// constructors //////////////////////////////////
  
  /**
   * Constructor that takes no arguments 
   */
  public Picture ()
  {
    /* not needed but use it to show students the implicit call to super()
     * child constructors always call a parent constructor 
     */
    super();  
  }
  
  /**
   * Constructor that takes a file name and creates the picture 
   * @param fileName the name of the file to create the picture from
   */
  public Picture(String fileName)
  {
    // let the parent class handle this fileName
    super(fileName);
  }
  
  /**
   * Constructor that takes the width and height
   * @param width the width of the desired picture
   * @param height the height of the desired picture
   */
  public Picture(int width, int height)
  {
    // let the parent class handle this width and height
    super(width,height);
  }
  
  /**
   * Constructor that takes a picture and creates a 
   * copy of that picture
   */
  public Picture(Picture copyPicture)
  {
    // let the parent class do the copy
    super(copyPicture);
  }
  
  ////////////////////// methods ///////////////////////////////////////
  
  /**
   * Method to return a string with information about this picture.
   * @return a string with information about the picture such as fileName,
   * height and width.
   */
  public String toString()
  {
    String output = "Picture, filename " + getFileName() + 
      " height " + getHeight() 
      + " width " + getWidth();
    return output;
    
  }
  
  public void mirrorVertical()
  {
    int mirrorPoint = this.getWidth()/2;
    Pixel leftPixel = null;
    Pixel rightPixel = null;
    
    // loop through the rows
    for (int y = 0; y < this.getHeight(); y++)
    {
      // loop from column 0 to just before the mirror point
      for (int x = 0; x < mirrorPoint; x++)
      {
        leftPixel = this.getPixel(x,y);
        rightPixel = this.getPixel(this.getWidth()-1-x,y);
        rightPixel.setColor(leftPixel.getColor());
      }
    }
  }
  
  public void mirrorVerticalRightToLeft()
  {
    int mirrorPoint = this.getWidth()/2;
    Pixel leftPixel = null;
    Pixel rightPixel = null;
    
    // loop through the rows
    for (int y = 0; y < this.getHeight(); y++)
    {
      // loop from column 0 to just before the mirror point
      for (int x = 0; x < mirrorPoint; x++)
      {
        leftPixel = this.getPixel(x,y);
        rightPixel = this.getPixel(this.getWidth()-1-x,y);
        leftPixel.setColor(rightPixel.getColor());
      }
    }
  }
  
 /**
  * Modified version of method from page 154 of the textbook for copying pictures
  */
 public void copyPictureTo(Picture sourcePicture, int xStart, int yStart)
 {
   Pixel sourcePixel = null;
   Pixel targetPixel = null;
   
   //loop through the columns
   try{
   for (int sourceX = 0, targetX = xStart;
        sourceX < sourcePicture.getWidth();
        sourceX++, targetX++)
   {
     //loop through the rows
     for (int sourceY = 0,
          targetY = yStart;
          sourceY < sourcePicture.getHeight();
          sourceY++, targetY++)
     {
       sourcePixel = sourcePicture.getPixel(sourceX,sourceY);
       targetPixel = this.getPixel(targetX,targetY);
       targetPixel.setColor(sourcePixel.getColor());
     } 
   }
  }catch(IndexOutOfBoundsException ex){System.out.println("Either xStart or yStart is out of bounds");System.exit(0);}
} 
 
/**
  * Modified version of copyPictureTo to copy all but white pixels
  */
 public void copyExceptWhite(Picture sourcePicture, int xStart, int yStart)
 {
   Pixel sourcePixel = null;
   Pixel targetPixel = null;
   
   //loop through the columns
   try{
   for (int sourceX = 0, targetX = xStart;
        sourceX < sourcePicture.getWidth();
        sourceX++, targetX++)
   {
     //loop through the rows
     for (int sourceY = 0,
          targetY = yStart;
          sourceY < sourcePicture.getHeight();
          sourceY++, targetY++)
     {
       sourcePixel = sourcePicture.getPixel(sourceX,sourceY);
       // Get color values of source pixel
       int red = sourcePixel.getRed();
       int green = sourcePixel.getGreen();
       int blue = sourcePixel.getBlue();
       // If all values are not white, copy pixel
       if (!(red == 255 && green == 255 && blue == 255))
       {
         targetPixel = this.getPixel(targetX,targetY);
         targetPixel.setColor(sourcePixel.getColor());
       }
     } 
   }
  }catch(IndexOutOfBoundsException ex){System.out.println("Either xStart or yStart is out of bounds");System.exit(0);}
} 
 
 /**
  * This method removes the blue from any pixel with a blue value less than 128, 
  * otherwise it will give it a blue value of 255.
  */
 
public void blueExtremes()
  {
    Pixel[] pixelArray = this.getPixels();
    Pixel pixelObj = null;
    int index = 0;
    
    // loop though all the pixels
    while(index < pixelArray.length)
    {
      // get the current pixel
      pixelObj = pixelArray[index];
      
      // get the blue value
      int blue = pixelObj.getBlue();
      
      // if pixels blue value is less than 128, remove blue color
      if (blue < 128)
      {
        blue = 0;
      }
      // otherwise, give pixel a max blue value
      else
      {
        blue = 255;
      }
      // set the new blue value
      pixelObj.setBlue(blue);
        
      // increment the index
      index++;
    }
  }
 
 /**
   * Method to decrease the red value of a picture by 50%.
   */
  public void decreaseRed()
  {
    Pixel[] pixelArray = this.getPixels();
    Pixel pixelObj = null;
    int index = 0;
    int value = 0;
    
    // loop though all the pixels
    while(index < pixelArray.length)
    {
      // get the current pixel
      pixelObj = pixelArray[index];
      
      // get the red value
      value = pixelObj.getRed();
      
      // decrease the red value
      value = (int) (value * 0.5);
      
      // set the pixel's red value
      pixelObj.setRed(value);
      
      // increment the index
      index++;
    }
  }
  
  /**
   * Method to change the red value of a picture with a
   * passed parameter from the user.
   */
  public void changeRed(double howMuch)
  {
    Pixel[] pixelArray = this.getPixels();
    Pixel pixelObj = null;
    int value = 0;
    
    // loop though all the pixels
    for(int index = 0; index < pixelArray.length; index++)
    {
      // get the current pixel
      pixelObj = pixelArray[index];
      
      // get the red value
      value = pixelObj.getRed();
      
      // decrease the red value
      value = (int) (value * howMuch);
      
      // set the pixel's red value
      pixelObj.setRed(value);
    }
  }
  
  /**
   * Method to clear the blue from a picture using the pixels in a 
   * two-dimensional array.
   */
  public void clearBlue2()
  {
    Pixel pixelObj;
    // loop through the rows (y direction)
    for (int y = 0; y < this.getHeight(); y++)
    {
      // loop through the columns (x direction)
      for (int x = 0; x < this.getWidth(); x++)
      {
        // get pixel at the x and y location
        pixelObj = this.getPixel(x,y);
        
        // set its blue value to 0
        pixelObj.setBlue(0);
      }
    }
  }
 
  /**This method mirrors a picture on the diagonal from the
    * top left to the bottom right corners of a square, for a rectangle it will 
    * mirror the square portion of the left side, since a rectangle cant be mirrored perfectly.
    */
  
  public void mirrorDiagonal()
  {
    // set target and source pixel variables to null
    Pixel targetPixel = null;
    Pixel sourcePixel = null;
    
    // get the max value for y (from height)
    int maxY = this.getHeight()-1;
    
    // loop through the rows
    for (int y = 1; y <= maxY; y++)
    {
      // loop from column 0 to just before the mirror point
      for (int x = 0; x <= y-1; x++)
      {
        targetPixel = this.getPixel(x,y);
        sourcePixel = this.getPixel(y,x);
        targetPixel.setColor(sourcePixel.getColor());
      }
    }
  }

  
  /**This method mirrors a picture on the diagonal from the
    * top left to the bottom right fully
    */
  
  public void mirrorDiagonalFlip()
  {
    // set target and source pixel variables to null
    Pixel targetPixel = null;
    Pixel sourcePixel = null;
    Color tempColor;
    
    // get the max value for y (from height)
    int maxY = this.getHeight()-1;
    
    // loop through the rows
    for (int y = 1; y <= maxY; y++)
    {
      // loop from column 0 to just before the mirror point
      for (int x = 0; x <= y-1; x++)
      {
        targetPixel = this.getPixel(x,y);
        sourcePixel = this.getPixel(y,x);
        tempColor = targetPixel.getColor();
        targetPixel.setColor(sourcePixel.getColor());
        sourcePixel.setColor(tempColor);
      }
    }
  }
  
  /**This method adds a angled white border around the photo
    * to make it have a framed appearance
    */
  public void angleBorder()
  {
    // declare variables
    int midPoint = this.getHeight()/2;
    Pixel leftPixelTop = null;
    Pixel leftPixelBottom = null;
    Pixel rightPixelTop = null;
    Pixel rightPixelBottom = null;
    
    // loop through the columns from the left and right
    for (int x = 0; x <= this.getWidth()/2; x++)
    {
      // loop from column 0 to just before the mirror point
      for (int y = 0; y <= midPoint; y++)
      {
        // assign corner pixels
        leftPixelTop = this.getPixel(x,y);
        leftPixelBottom = this.getPixel(x, this.getHeight()-y-1);
        rightPixelTop = this.getPixel(this.getWidth()-x-1,y);
        rightPixelBottom = this.getPixel(this.getWidth()-x-1,this.getHeight()-y-1);
        // set pixels to white
        leftPixelTop.setColor(java.awt.Color.white);
        leftPixelBottom.setColor(java.awt.Color.white);
        rightPixelTop.setColor(java.awt.Color.white);
        rightPixelBottom.setColor(java.awt.Color.white);
      
      }
      // decrease midpoint for curved frame appearance
      midPoint = midPoint - 1;
    }
  } 

  /** This method increases all the green color values and
    * decreases red and blue values to make a night vision effect with added black 
    * pixels staggered every 3 pixels for added effect
    */
  public void nightVision()
  {
    Pixel[] pixelArray = this.getPixels();
    Pixel pixelObj = null;
    int index = 0;
    int value = 0;
    // loop through all the pixels and increase green
    while(index < pixelArray.length)
    {
      // get current pixel
      pixelObj = pixelArray[index];
      // increase green
      value = pixelObj.getGreen();
      value = value * 2;
      pixelObj.setGreen(value);
      // decrease red value
      value = pixelObj.getRed();
      value = value / 2;
      pixelObj.setRed(value);
      // decrease blue value
      value = pixelObj.getBlue();
      value = value / 2;
      pixelObj.setBlue(value);
      index = index + 1;
    }
    int count = 0;
    // loop through all the pixels and add black lines for night vision effect
    while(count < pixelArray.length)
    {
      // get current pixel
      pixelObj = pixelArray[count];
      // make current pixel black
      pixelObj.setColor(java.awt.Color.black);
      // skip 3 pixels for next staggered black pixel location
      count = count + 3;
    }
  }
  
  /**This method adds a rounded white border around the photo
    * to make it have a framed appearance on either rectangular or square pictures
    */
  public void roundedBorder()
  {
    // declare variables
    int width = this.getWidth();
    int height = this.getHeight();
    int midX = width / 2; // center of width
    int midY = height / 2; // center of height
    Pixel pixelObj = null;
    // loop through the rows
    for (int y = 0; y < height; y++){
      // loop through the columns
      for (int x = 0; x < width; x++){
        // if the coordinate is outside the elliptical region, set pixel color to white
        if (((Math.pow(x - midX, 2) / Math.pow(midX, 2)) + (Math.pow(y - midY, 2) / Math.pow(midY, 2))) > 1){
          // get pixel at coordinate
          pixelObj = getPixel(x,y);
          // set color to white
          pixelObj.setColor(java.awt.Color.white);
        }
      }
    }
  } 
  
  /**
   * Method to count all non-white pixels in an image.
   */
  public int countNonWhitePixels()
  {
  Pixel pixelObj = null;
  int counter = 0;
  // loop through the columns (x direction)
  for (int x = 0; x < this.getWidth(); x++)
  {
    // loop through the rows (y direction)
    for (int y = 0; y < this.getHeight(); y++)
    {
      // get pixel at the x and y location
      pixelObj = this.getPixel(x,y);
      
      if (!(pixelObj.getRed() == 255 && pixelObj.getGreen() == 255
              && pixelObj.getBlue() == 255))
        counter = counter + 1;
    }
  }
  return counter;
}
  
/**
   * Method to count all white pixels in an image.
   */
  
  public int countWhitePixels()
  {
  Pixel pixelObj = null;
  int counter = 0;
  // loop through the columns (x direction)
  for (int x = 0; x < this.getWidth(); x++)
  {
    // loop through the rows (y direction)
    for (int y = 0; y < this.getHeight(); y++)
    {
      // get pixel at the x and y location
      pixelObj = this.getPixel(x,y);
      
      if (pixelObj.getRed() == 255 && pixelObj.getGreen() == 255
              && pixelObj.getBlue() == 255)
        counter = counter + 1;
    }
  }
  return counter;
}
  
/**
 * This method counts the number of non-white pixels in an image using an
 * alternative method.
 */
  
  public int countNonWhitePixels2()
  {
    return (this.getHeight() * this.getWidth()) - this.countWhitePixels();
  }
  
  /**
   * This method compares the sizes of two different pictures.
   */
  
  public boolean equalPictureSize (Picture otherPicture)
  {
    if (this.getHeight() == otherPicture.getHeight()
          && this.getWidth() == otherPicture.getWidth())
      return true;
    else
      return false;
  }
  
  /**
   * This method copies the left half of a picture onto another.
   */
  
  public void copyLeftHalf(Picture sourcePicture, int xStart, int yStart)
  {
   Pixel sourcePixel = null;
   Pixel targetPixel = null;
   
   //loop through the columns
   try{
   for (int sourceX = 0, targetX = xStart;
        sourceX < (sourcePicture.getWidth()/2);
        sourceX++, targetX++)
   {
     //loop through the rows
     for (int sourceY = 0,
          targetY = yStart;
          sourceY < sourcePicture.getHeight();
          sourceY++, targetY++)
     {
       sourcePixel = sourcePicture.getPixel(sourceX,sourceY);
       targetPixel = this.getPixel(targetX,targetY);
       targetPixel.setColor(sourcePixel.getColor());
     } 
   }
  }catch(IndexOutOfBoundsException ex){System.out.println("Either xStart or yStart is out of bounds");System.exit(0);}
} 
  
  /**
   * This method morphs a picture to form into another picture using
   * a given formula to determine pixel colour.
   */
  
  public void morphStage(Picture startPicture, Picture endPicture, int numStages, int k){
    // declare null pixel objects
    Pixel startPixel = null;
    Pixel endPixel = null;
    Pixel targetPixel;
    // loop through the rows
    for (int y = 0; y < this.getHeight(); y++){
      // loop through columns
      for (int x = 0; x < this.getWidth(); x++){
        // get pixels start and end
        startPixel = startPicture.getPixel(x,y);
        endPixel = endPicture.getPixel(x,y);
        // get intermediate pixel
        targetPixel = this.getPixel(x,y);
        // calculate new colours from formula
        int redValue = startPixel.getRed() + ((endPixel.getRed() - startPixel.getRed()) / (numStages + 1)) * k;
        int greenValue = startPixel.getGreen() + ((endPixel.getGreen() - startPixel.getGreen()) / (numStages + 1)) * k;
        int blueValue = startPixel.getBlue() + ((endPixel.getBlue() - startPixel.getBlue()) / (numStages + 1)) * k;
        // set target colours
        targetPixel.setRed(redValue);
        targetPixel.setGreen(greenValue);
        targetPixel.setBlue(blueValue);
      }
    }
  }

} // end of class Picture, put all new methods before this
 