import org.json.JSONArray;
import org.json.JSONObject;
import org.json.JSONException;

/**
 * This class creates a LongTermForecast object to store weather data for
 * lultiple days, for uat least 5 days.
 * 
 * @author Eric Bachmeier
 * 
 */

public class LongTermForecast {

	/**
	 * Weather variable declarations
	 */
	private HttpClient client;
	private JSONObject j, jCity, day, main, skyObj;
	private JSONArray jArray, sky;
	private WeatherInfo[] daily;
	private WeatherInfo temp;
	
	// constant for number of days in the long term forecast
	private final static int DAYS = 5;

	/**
	 * Constructor for a LongTermForecast object containing all categories of
	 * weather for days worth of long term data
	 * 
	 * @param location
	 *            String containing the city in which to retrieve data for
	 */
	public LongTermForecast(String location) {

		try {
			// remove any possible whitespace in the location passed
			location.replaceAll("\\s", "");
			// create Http call for the city passes, long term data
			client = new HttpClient(location, "l");
			// create JSONObject for this data
			j = new JSONObject(client.getData());

			// "city" tag
			jCity = j.getJSONObject("city");
			daily = new WeatherInfo[DAYS+1];
			temp = new WeatherInfo();
			temp.setCity(jCity.getString("name"));
			temp.setCountry(jCity.getString("country"));
			daily[0] = temp;

			// list of forecast increments
			jArray = j.getJSONArray("list");
			// number of iterations of days 
			for (int x = 0; x < DAYS; x++) {
				day = jArray.getJSONObject(x);

				// "time increment dt" tag
				temp = new WeatherInfo();
				temp.setTime((long) day.getDouble("dt"));

				// "temperature" tag
				main = day.getJSONObject("temp");
				temp.setTemp(main.getDouble("day"));
				temp.setMinMax(main.getDouble("min"),
						main.getDouble("max"));

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
				// add the WeatherInfo object to the days array
				daily[x + 1] = temp;
			}
		} catch (JSONException ex) {
			ex.printStackTrace();
		}
	}

	/**
	 * Getter method to retrieve the array of WeatherInfo objects array created
	 * by the LongTermForecast object
	 * 
	 * @return WeatherInfo array of weather increments
	 */
	public WeatherInfo[] getDaily() {
		return daily;
	}
}