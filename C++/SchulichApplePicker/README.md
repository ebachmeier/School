# Team Apple

>Western University - Computer Science

>CS3307a - Object-Oriented Design and Analysis

>2015-2016 Academic Year

**Current Stage:** Final Submission

## Team Members:

* Vanessa Synesael  

* Vince Sippola

* Jennifer Xin

* Jia (Jerry) Wu  

* Emily Yip  

* Robert Canton  

* Angus Poole  

* Eric Bachmeier 

* Jaisen Bynoe

## Project Description

This is a stand-alone app developed in C++ by Team Apple. The purpose of this desktop application is to process faculty data in the form of spreadsheets. 
The user can then select their parameters whether it be the time frame for the data or the type of publications or research to view. 
After the data is verified, it can be viewed in formatted charts and graphs.

## Getting ApplePicker

* [Windows Download](Project Code/AppleProject/release/AppleProject.exe?raw=true)

## Using the Program

* Simply double-click the executable file provided to run the program.
* Main window page automatically loads to the Load CSV page.
* On load csv page, select a csv file type and choose a file, or choose a recently uploaded file from the list on the left.
* Click on Verify to verify the csv data
* On Verify page, choose to fix the data or ignore the record completely. When all rows have been fixed or ignored, click Confirm.
* Area will be blank if all rows have been fixed/ignored. Click Analyze
* Select tab for csv that was uploaded to view information. Filter all data based on date, 
then futher filter data with other drop boxes for graphs.
* Click on Load button to load new data.

## Program Versions

v0.1 - 		Release Date Oct 26, 2015.
			Version implements the base requirements for the Publication CSV type only. 
			Stretch goal of data verification also implemented. 
			Login feature included in UI but does not authenticate user.

v0.2 - 		Release Date Nov 25, 2015.
			Version implements all the base requirements of the App, including handling Publication, Grant, Presentation and Teaching CSV typs. 
			Login feature removed; no longer implementing this as stretch goal.
			The application does not currently persist data between sessions or between screens.
			Stretch goal of data verification among all CSV types implemented.
			
v1.0 - 		Release Date Dec 9, 2015.

## Project Tools

For the development of this application we used Qt Creator for our cross-platform IDE. 

We used Git for version control and hosted the project on GitHub.

The build automation for this project is done through Qt as well.
