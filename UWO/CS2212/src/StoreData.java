import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

/**
 * Class for storing the weather app settings to a text file
 * 
 * @author Eric Bachmeier, Marc Stahl
 * 
 */

public class StoreData {

	public static void storeSettings(Settings s) throws Exception {
		ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream(
				"settings.dat"));
		out.writeObject(s);
		out.close();
	}

	public static void loadSettings() throws Exception {
		Settings s = new Settings();
		ObjectInputStream in = new ObjectInputStream(new FileInputStream(
				"settings.dat"));
		s = (Settings) in.readObject();
		Settings.instance = s;
		//System.out.println(s.toString());
		in.close();
	}
}