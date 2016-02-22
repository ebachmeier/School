import org.json.JSONArray;
import org.json.JSONObject;
import org.json.JSONException;

/**
 * This class creates a ShortTermForecast object to store weather data for every
 * three hours in a day, for 24 hours.
 * 
 * @author Eric Bachmeier
 * 
 */

public class ShortTermForecast {

	/**
	 * Weather variable declarations
	 */
	private HttpClient client;
	private JSONObject j, jCity, day, main, skyObj;
	private JSONArray jArray, sky;
	private WeatherInfo[] hourly;
	private WeatherInfo temp;

	// constant for number of 3 hour increments in the short term forecast
	private final static int INC = 9;

	/**
	 * Constructor for a ShortTermForecast object containing all categories of
	 * weather for an hourly forecast
	 * 
	 * @param location
	 *            String containing the city in which to retrieve data for
	 */
	public ShortTermForecast(String location) {

		try {
			// create Http call for the city passes, short term data
			client = new HttpClient(location, "s");
			// create JSONObject for this data
			j = new JSONObject(client.getData());

			// "city" tag
			jCity = j.getJSONObject("city");
			hourly = new WeatherInfo[INC + 1];
			temp = new WeatherInfo();
			temp.setCity(jCity.getString("name"));
			temp.setCountry(jCity.getString("country"));
			hourly[0] = temp;

			// list of forecast increments
			jArray = j.getJSONArray("list");
			// number of 3 hour iterations
			for (int x = 0; x < INC; x++) {
				day = jArray.getJSONObject(x);

				// "time increment dt" tag
				temp = new WeatherInfo();
				temp.setTime((long) day.getDouble("dt"));

				// "temperature" tag
				main = day.getJSONObject("main");
				temp.setTemp(main.getDouble("temp"));
				temp.setMinMax(main.getDouble("temp_min"),
						main.getDouble("temp_max"));

				// "sky" condition tag
				sky = day.getJSONArray("weather");
				if (sky.length() > 0) {
					skyObj = sky.getJSONObject(0);
					temp.setSky(skyObj.getString("main"),
							skyObj.getString("description"));
					temp.setIconCode(skyObj.getString("icon"));
				} else {
					temp.setSky("--", "--");
					temp.setIconCode("--");
				}
				// add the WeatherInfo object to the hourly increment array
				hourly[x + 1] = temp;
			}
		} catch (JSONException ex) {
			System.out.println("Error retrieving shortterm forecast data for the selected location.");
		}
	}

	/**
	 * Getter method to retrieve the array of WeatherInfo objects array created
	 * by the ShortTermForecast object
	 * 
	 * @return WeatherInfo array of weather increments
	 */
	public WeatherInfo[] getHourly() {
		return hourly;
	}
}