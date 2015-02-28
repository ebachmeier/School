import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

/**
 * Class for retrieveing weather info from openweathermap by requesting the JSON
 * formatted information.
 * 
 * @author Eric Bachmeier
 * 
 */
public class HttpClient {

	/*
	 * Attributes of HttpClient class
	 */
	private String data;
	private String u;

	// base url for weather data requests
	private static String baseCall = "http://api.openweathermap.org/data/2.5/weather?q=";

	// base url for short term forecast requests
	private static String baseForecast = "http://api.openweathermap.org/data/2.5/forecast?q=";

	// base url for long term forecast requests
	private static String longForecast = "http://api.openweathermap.org/data/2.5/forecast/daily?q=";

	/**
	 * HttpClient constructor which retrieves the weather data from
	 * openweathermap api
	 * 
	 * @param location
	 *            String of the city in which to retrieve data for
	 * @param t
	 *            String for type of weather call to precede with (c, s, l)
	 *            current, short, or long
	 */
	public HttpClient(String location, String t) {

		HttpURLConnection connect = null;
		InputStream in = null;

		// set u to proper link base for appropriate weather call
		if (t == "c")
			u = baseCall + location;
		else if (t == "s")
			u = baseForecast + location;
		else
			u = longForecast + location + "&cnt=5";

		try {
			// connect to the url
			connect = (HttpURLConnection) (new URL(u)).openConnection();
			connect.setRequestMethod("GET");
			connect.setDoInput(true);
			connect.setDoOutput(true);
			connect.connect();

			// reading from the http response
			StringBuffer buffer = new StringBuffer();
			in = connect.getInputStream();
			BufferedReader read = new BufferedReader(new InputStreamReader(in));
			String line = null;
			// keep appending lines until there are no more
			while ((line = read.readLine()) != null) {
				buffer.append(line + "\r\n"); // carriage return and new line
			}

			// close input stream and connection
			in.close();
			connect.disconnect();
			// set data to the buffered string for later use
			this.data = buffer.toString();
		} catch (MalformedURLException ex) {
			ex.printStackTrace();
		} catch (IOException ex) {
			ex.printStackTrace();
		} finally {
			try {
				in.close();
			} catch (Throwable msg) {
			}
		}
	}

	/**
	 * Getter method to retrieve the data from the Http request
	 * 
	 * @return data String of weather information from openweathermap call
	 */
	public String getData() {
		return data;
	}
}