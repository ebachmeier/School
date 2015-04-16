
/*
 * Eric Bachmeier
 * 250738776
 * ebachme@uwo.ca
 * 
 * Program that draws a house, tree, and dog house using methods from the Turtle class.
 */

import java.awt.Color;
public class TurtleArt
{
  public static void main (String[]args)
  {
    // Create colors
    Color brown = new Color(139,69,19);
    Color grassGreen = new Color(0,153,51);
    Color black = new Color(0,0,0);
    Color blue = new Color(0,0,255);
    Color grey = new Color(210,210,210);
    Color red = new Color(255,0,0);
    // Create new world with dimensions 1280 x 720 px
    World worldObj = new World(1280,720);
    // Create a new turtle in world1 at (0,670)
    Turtle turtle1 = new Turtle(0,670,worldObj);
    // Draw grass across bottom 100 px of world1
    turtle1.setPenWidth(100);
    turtle1.setPenColor(grassGreen);
    turtle1.turnRight();
    turtle1.forward(1280);
    turtle1.penUp();
    // Draw tree with 260 px tall trunk
    turtle1.moveTo(120,640);
    turtle1.turnLeft();
    turtle1.setPenWidth(30);
    turtle1.setPenColor(brown);
    turtle1.penDown();
    turtle1.forward(260);
    turtle1.penUp();
    turtle1.forward(145);
    turtle1.penDown();
    turtle1.setPenColor(grassGreen);
    turtle1.setPenWidth(100);
    turtle1.drawCircle(3);
    turtle1.penUp();
    // Draw house 500 x 300 px with roof
    turtle1.moveTo(350,320);
    turtle1.setPenColor(black);
    turtle1.setPenWidth(5);
    turtle1.penDown();
    turtle1.drawRectangle(500,300);
    turtle1.penUp();
    turtle1.moveTo(600,177);
    turtle1.penDown();
    turtle1.drawTriangleBase500();
    turtle1.penUp();
    // Draw door
    turtle1.moveTo(700,445);
    turtle1.penDown();
    turtle1.setPenColor(blue);
    turtle1.drawRectangle(75,175);
    turtle1.moveTo(739,380);
    turtle1.drawEquilateral(75);
    turtle1.penUp();
    turtle1.moveTo(760,550);
    turtle1.penDown();
    // Door knob
    turtle1.drawSquare(5);
    turtle1.penUp();
    // Draw two square windows 50 x 50 px
    turtle1.moveTo(430,450);
    turtle1.setPenWidth(30);
    turtle1.penDown();
    turtle1.drawRectangle(75,25);
    turtle1.penUp();
    turtle1.moveTo(417,437);
    turtle1.setPenWidth(7);
    turtle1.setPenColor(grey);
    turtle1.penDown();
    turtle1.drawSquare(50);
    turtle1.penUp();
    turtle1.moveTo(468,437);
    turtle1.penDown();
    turtle1.drawSquare(50);
    turtle1.penUp();
    // Draw dog house beside main house 100 x 100 px square with roof
    turtle1.moveTo(1000,520);
    turtle1.penDown();
    turtle1.setPenColor(red);
    turtle1.setPenWidth(13);
    turtle1.drawSquare(100);
    turtle1.penUp();
    turtle1.moveTo(1051,435);
    turtle1.penDown();
    turtle1.drawEquilateral(96);
    turtle1.penUp();
    // Hide and reutrn the turtle to top-left corner in final figure
    turtle1.moveTo(0,0);
    turtle1.hide();  
  }
}