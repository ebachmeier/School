import java.awt.Color;
public class TestMethods
{
  public static void main (String[] args)
  {
    // Create picture1 object from a user selected test image
    String fileName = FileChooser.pickAFile();
    Picture picture1 = new Picture(fileName);
    // Show and invoke method 1
    picture1.explore();
    picture1.roundedBorder();
    picture1.explore();
    // Create picture2 object from a user selected test image
    String fileName2 = FileChooser.pickAFile();
    Picture picture2 = new Picture(fileName2);
    // Show and invoke method 2
    picture2.explore();
    picture2.nightVision();
    picture2.explore();
  }
}