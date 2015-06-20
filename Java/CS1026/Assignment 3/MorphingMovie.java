public class MorphingMovie
{
  public static void main (String[] args)
  {
    // set directory for pictures
    FileChooser.setMediaPath("/Users/Eric/Documents/UWO/COMPSCI 1026/Extras/mediasources-no-movies-7-30-06/intro-prog-java/mediasources/");
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
      // promt user for number of intermediate stages
      int stages = SimpleInput.getIntNumber("Enter the number of intermediate stages: ");
      // prompt user for movie one save directory
      String directory = SimpleInput.getString("Enter the directory to save the first movie: ");
      // create picture array for all original and intermediate pictures with length stages + 2 original pictures
      Picture[] picArray = new Picture[stages+2];
      // store start and ending pictures in array
      picArray[0] = picture1;
      picArray[stages+1] = picture2;
      for (int k = 1; k <= stages; k++){
        // create new intermediate picture object
        Picture intermediate = new Picture(picture1.getWidth(),picture1.getHeight());
        // call morph method for each stage
        intermediate.morphStage(picture1, picture2, stages, k);
        // store intermediate picture in array
        picArray[k] = intermediate;
      }
      // play first movie 20fps
      FrameSequencer frameForward = new FrameSequencer(directory);
      for (int i = 0; i < picArray.length; i++){
        frameForward.addFrame(picArray[i]);
      }
      MoviePlayer firstMovie = new MoviePlayer(directory);
      firstMovie.playMovie(20);
      
      // prompt user for movie two save directory
      String directory2 = SimpleInput.getString("Enter the directory to save the second movie: ");
      // play second movie 20fps
      FrameSequencer frameBackward = new FrameSequencer(directory2);
      for (int i = 0; i < picArray.length; i++){
        frameBackward.addFrame(picArray[i]);
      }
      // adding pictures to second movie directory backwards
      for (int i = picArray.length-1; i >= 0; i--){
        frameBackward.addFrame(picArray[i]);
      }
      MoviePlayer secondMovie = new MoviePlayer(directory2);
      secondMovie.playMovie(20);
    }
  }
}