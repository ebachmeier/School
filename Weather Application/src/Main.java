import java.awt.EventQueue;
import java.io.File;
import java.util.Arrays;

/**
 * Class for launching the weather application
 * 
 * @author Eric Bachmeier
 * 
 */
public class Main {
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				// if no settings exist, create defaults
				if (!(new File("settings.dat").exists())) {

					// string array of my locations
					String[] startingCityListHTML = new String[50];
					Arrays.fill(startingCityListHTML, "(empty)");
					startingCityListHTML[0] = "<html>London<br>CA";
					startingCityListHTML[1] = "<html>Toronto<br>CA";
					startingCityListHTML[2] = "<html>Windsor<br>CA";
					startingCityListHTML[3] = "<html>Quebec<br>CA";
					startingCityListHTML[4] = "<html>Calgary<br>CA";
					startingCityListHTML[5] = "<html>London<br>UK";
					startingCityListHTML[6] = "<html>New York<br>US";
					startingCityListHTML[7] = "<html>Paris<br>FR";

					// string array of my locations
					String[] startingCityListComma = new String[50];
					Arrays.fill(startingCityListComma, "(empty)");
					startingCityListComma[0] = "London,CA";
					startingCityListComma[1] = "Toronto,CA";
					startingCityListComma[2] = "Windsor,CA";
					startingCityListComma[3] = "Quebec,CA";
					startingCityListComma[4] = "Calgary,CA";
					startingCityListComma[5] = "London,UK";
					startingCityListComma[6] = "New York,US";
					startingCityListComma[7] = "Paris,FR";

					int num = 8;
					int startIndex = 0;

					// string array of elements to hide(N) or show(Y)
					String[] elementsArray = new String[6];
					Arrays.fill(elementsArray, "Y");
	
					Settings initial = new Settings(startingCityListHTML, startingCityListComma, "c", startingCityListComma[startIndex], startIndex, num, elementsArray);

					Settings.instance = initial;
					// settings have already been set by user, load them now
				} else {
					try {
						StoreData.loadSettings();
					} catch (Exception ex) {
						System.out.println("Error storing user settings");
					}
				}

				/*
				 * LOCALONLY_SingletonTest1 Test1 = new
				 * LOCALONLY_SingletonTest1(); LOCALONLY_SingletonTest2 Test2 =
				 * new LOCALONLY_SingletonTest2();
				 * 
				 * Test1.firstSet(); Test2.firstGet(); Test2.secondSet();
				 * Test1.secondGet();
				 */

				// launch initial search page for weather app
				MyLocationsInterface MLI = new MyLocationsInterface();
				MLI.setVisible(true);
			}
		});
	}
}