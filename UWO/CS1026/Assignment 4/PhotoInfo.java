/*
 * Assignment 4
 * 
 * Eric Bachmeier
 * 250738776
 * 
 * PhotoInfo class
 * 
 * This class models the information needed about a photo in order to
 * create a labelled photo. Each object has attributes of the photo
 * including: id, category, date, caption, and file name.
 */

public class PhotoInfo {
  
  /////////////// fields ///////////////
  private String id, category, caption, photoFile;
  private int year, month, day;
  private Picture photoPic;
  
  //////////// constructors ////////////
  // create a photo info object with ID, date, category, caption, and filename
  public PhotoInfo(String ident, int nday, int nmonth, int nyear, String cat,
                   String cap, String picFile) {
    id = ident;
    category = cat;
    year = nyear;
    month = nmonth;
    day = nday;
    caption = cap.replace('_',' '); // replace underscores with spaces in caption
    photoFile = picFile;
    // create original picture object from passed filename
    Picture picOriginal = new Picture(System.getProperty("user.dir") + "/myPhotos/" + picFile);
    // create photoPic with 80 blank pixels at bottom for caption region
    photoPic = new Picture(picOriginal.getWidth(), picOriginal.getHeight()+80);
    // copy original photo to photoPic
    photoPic.copyPictureTo(picOriginal, 0, 0);
    // get String for category, caption, and date
    String line1 = this.getCategory();
    String line2 = this.getCaption();
    String line3 = this.getDate();
    // use drawString to draw captions to photo, centered
    photoPic.drawString(line1, photoPic.getWidth()/2 - (line1.length()*7)/2, photoPic.getHeight()-55, 14);
    photoPic.drawString(line2, photoPic.getWidth()/2 - (line2.length()*7)/2, photoPic.getHeight()-36, 14);
    photoPic.drawString(line3, photoPic.getWidth()/2 - (line3.length()*6)/2, photoPic.getHeight()-17, 14);
  }
  
  ////////////// methods ///////////////
  // toString
  public String toString() {
    String s = caption + "(" + id + ", " + category + ", " + photoFile + ", " +
      month + "/" + day + "/" + year + ")";
    return s;
  }
  
  // accessors
  public String getId() {
    return id;
  }
  
  public String getCategory() {
    return category;
  }
  
  public int getYear() {
    return year;
  }
  
  public int getMonth() {
    return month;
  }
  
  public int getDay() {
    return day;
  }
    
  public String getDate() {
    String date =  month + "/" + day + "/" + year;
    return date;
  }
  
  public String getCaption() {
    return caption;
  }
  
  public String getPhotoFile() {
    return photoFile;
  }
  
  public Picture getPhotoPic() {
    return photoPic;
  }
  
  // mian method
  public static void main(String[] args) {
    // create a sample photo info object
    PhotoInfo picObj = new PhotoInfo("cat", 4, 7, 1998, "Pets", "Funny_cat",
                                   "granny_cat.jpg");
    // test getters and toString methods
    System.out.println(picObj.getId());
    System.out.println(picObj.getCategory());
    System.out.println(picObj.getDate());
    System.out.println(picObj.getCaption());
    System.out.println(picObj.getPhotoFile());
    System.out.println(picObj.toString());
    // test getting labelled photo and show it
    Picture labelledPic = new Picture(picObj.getPhotoPic());
    labelledPic.show();
  }
}

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    