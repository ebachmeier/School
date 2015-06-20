public class TestMorphing
{
  public static void main (String[] args)
  {
    // set directory for pictures
    FileChooser.setMediaPath("/Users/Eric/Documents/UWO/COMPSCI 1026/Extras/mediasources-no-movies-7-30-06/intro-prog-java/mediasources/");
    // test 3 intermediate stages
    final int TEST_ONE = 3;
    // create picture objects from two user selected images
    String fileName = FileChooser.pickAFile();
    Picture picture1 = new Picture(fileName);
    String fileName2 = FileChooser.pickAFile();
    Picture picture2 = new Picture(fileName2);
    // check if pictures are same size
    if (picture1.getWidth() != picture2.getWidth() || picture1.getHeight() != picture2.getHeight())
      // error message if not the same size
      SimpleOutput.showInformation("Error. The two selected images are not the same size.");
    else{
      // show first picture
      picture1.show();
      // k variable is current stage
      for (int k = 1; k <= TEST_ONE; k++){
        // create new intermediate picture object
        Picture intermediate = new Picture(picture1.getWidth(),picture1.getHeight());
        // call morph method three times in this loop for test
        intermediate.morphStage(picture1, picture2, TEST_ONE, k);
        intermediate.show(); // show intermediate picture each time
        }
      // show final picture
        picture2.show();
    }
    
    // test 9 intermediate stages
    final int TEST_TWO = 9;
    // create picture objects from two user selected images
    String fileName3 = FileChooser.pickAFile();
    Picture picture3 = new Picture(fileName3);
    String fileName4 = FileChooser.pickAFile();
    Picture picture4 = new Picture(fileName4);
    // check if pictures are same size
    if (picture3.getWidth() != picture4.getWidth() || picture3.getHeight() != picture4.getHeight())
      // error message if not the same size
      SimpleOutput.showInformation("Error. The two selected images are not the same size.");
    else{
      // show first picture
      picture3.show();
      // k variable is current stage
      for (int k = 1; k <= TEST_TWO; k++){
        // create new intermediate picture object
        Picture intermediate = new Picture(picture3.getWidth(),picture3.getHeight());
        // call morph method nine times in this loop for test
        intermediate.morphStage(picture3, picture4, TEST_TWO, k);
        intermediate.show(); // show intermediate picture each time
        }
      // show final picture
        picture4.show();
    }
  }
}