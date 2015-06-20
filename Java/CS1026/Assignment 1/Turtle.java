
/**
 * Class that represents a turtle which is similar to a Logo turtle.
 * This class inherts from SimpleTurtle and is for students
 * to add methods to.
 *
 * Copyright Georgia Institute of Technology 2004
 * @author Barb Ericson ericson@cc.gatech.edu
 */
public class Turtle extends SimpleTurtle
{
  ////////////////// constructors ///////////////////////
  
  /** Constructor that takes the x and y and a picture to
   * draw on
   * @param x the starting x position
   * @param y the starting y position
   * @param picture the picture to draw on
   */
  public Turtle (int x, int y, Picture picture) 
  {
    // let the parent constructor handle it
    super(x,y,picture);
  }
  
  /** Constructor that takes the x and y and a model
   * display to draw it on
   * @param x the starting x position
   * @param y the starting y position
   * @param modelDisplayer the thing that displays the model
   */
  public Turtle (int x, int y, ModelDisplay modelDisplayer) 
  {
    // let the parent constructor handle it
    super(x,y,modelDisplayer);
  }
  
  /** Constructor that takes the model display
   * @param modelDisplay the thing that displays the model
   */
  public Turtle (ModelDisplay modelDisplay) 
  {
    // let the parent constructor handle it
    super(modelDisplay);
  }
  
  /**
   * Constructor that takes a picture to draw on
   * @param p the picture to draw on
   */
  public Turtle (Picture p)
  {
    // let the parent constructor handle it
    super(p);
  }  
  
  /////////////////// methods ///////////////////////
  
  public void drawSquare()
  {
    this.turnRight();
    this.forward(30);
    this.turnRight();
    this.forward(30);
    this.turnRight();
    this.forward(30);
    this.turnRight();
    this.forward(30);
  }
  
  // Method for drawing a square with parameter
  public void drawSquare(int width)
  {
    this.turnRight();
    this.forward(width);
    this.turnRight();
    this.forward(width);
    this.turnRight();
    this.forward(width);
    this.turnRight();
    this.forward(width);
  }
  
   // Method for drawing the letter V with parameter
  public void drawVee(int length)
  {
    this.turn(-30);
    this.forward(length);
    this.turn(180);
    this.forward(length);
    this.turn(-120);
    this.forward(length);
    this.turn(180);
    this.forward(length);
    this.turn(150);
  }
  
  // Method for drawing a rectangle
  public void drawRectangle(int width, int height)
  {
    this.turnRight();
    this.forward(width);
    this.turnRight();
    this.forward(height);
    this.turnRight();
    this.forward(width);
    this.turnRight();
    this.forward(height);
  }
  
  // Method for drawing an equilteral triangle with parameter
  public void drawEquilateral(int length)
  {
    this.turn(150);
    this.forward(length);
    this.turn(120);
    this.forward(length);
    this.turn(120);
    this.forward(length);
    this.turn(-30);
  }
  
  // Method for drawing a circle with parameter
  public void drawCircle(int size)
  {
    this.turnRight();
    for(int i=1; i<=120; i++)
    {
      this.forward(size);
      this.turn(3);
    }
    this.turnLeft();
  }
  
  // Method for drawing an isosceles triangle with base of 500 for roof
  public void drawTriangleBase500()
  {
    this.turn(120);
    this.forward(288);
    this.turn(150);
    this.forward(500);
    this.turn(150);
    this.forward(288);
    this.turn(-60);
  }
} // end of class Turtle, put all new methods before this