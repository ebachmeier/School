import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import org.json.JSONObject;
import org.json.JSONArray;
import org.json.JSONException;
import java.util.Date;
import java.util.TimeZone;
import java.text.SimpleDateFormat;
import java.lang.Math;

public class WeatherInfo {

	// base url for weather data requests
	private static String baseCall = "http://api.openweathermap.org/data/2.5/weather?q=";
	// WeatherInfo object variables
	private double longitude, latitude, temp, pressure, humidity, min, max,
			speedWind, degreesWind;
	private int weatherId, clouds, cod, locId;
	private String country, main, description, iconCode, base, city, response;
	private JSONObject j, jCoord, jSys, jWeatherObj, jMain, jWind, jClouds;
	private JSONArray jWeather;
	private Date rise, set, up;
	private SimpleDateFormat r, s, u;
	private long sunrise, sunset, dt;

	// degree symbol
	final String DEGREE = "\u00b0";

	/**
	 * Constructor for a WeatherInfo object containing all categories of weather
	 * 
	 * @param j
	 *            String containing the weather info in JSON format
	 */
	public WeatherInfo(String location) {

		try {
			response = getWeather(location);
			j = new JSONObject(response);

			// "coord" tag
			jCoord = j.getJSONObject("coord");
			this.longitude = jCoord.getDouble("lon");
			this.latitude = jCoord.getDouble("lat");

			// "sys" tag
			jSys = j.getJSONObject("sys");
			this.country = jSys.getString("country");
			this.sunrise = jSys.getInt("sunrise");
			this.sunset = jSys.getInt("sunset");

			// "weather" tag
			jWeather = j.getJSONArray("weather");
			if (jWeather.length() > 0) {
				jWeatherObj = jWeather.getJSONObject(0);
				this.weatherId = jWeatherObj.getInt("id");
				this.main = jWeatherObj.getString("main");
				this.description = jWeatherObj.getString("description");
				this.iconCode = jWeatherObj.getString("icon");
			} else {
				this.weatherId = 0;
				this.main = "--";
				this.description = "--";
				this.iconCode = "--";
			}

			// "base" tag
			this.base = j.getString("base");

			// "main" tag
			jMain = j.getJSONObject("main");
			this.temp = jMain.getDouble("temp");
			this.pressure = jMain.getDouble("pressure");
			this.humidity = jMain.getDouble("humidity");
			this.min = jMain.getDouble("temp_min");
			this.max = jMain.getDouble("temp_max");

			// "wind" tag
			jWind = j.getJSONObject("wind");
			this.speedWind = jWind.getDouble("speed");
			this.degreesWind = jWind.getDouble("deg");

			// "clouds" tag
			jClouds = j.getJSONObject("clouds");
			this.clouds = jClouds.getInt("all");

			// "dt" tag
			this.dt = j.getInt("dt");

			// "id" tag
			this.locId = j.getInt("id");

			// "name" tag
			this.city = j.getString("name");

			// "cod" tag
			this.cod = j.getInt("cod");

		} catch (JSONException ex) {
			ex.printStackTrace();
		}
	}

	/**
	 * Constructor for a WeatherInfo object containing all categories of weather
	 * for a weather forecast
	 * 
	 * @param j
	 *            String containing the weather info in JSON format
	 * @param days
	 *            the number of days for the length of the forecast
	 */
	public WeatherInfo(String response, int days) {

		// gather forecast data for the 5 days
		// going to have to try and catch JSONException

	}

	/**
	 * Method for retrieving the weather data from the http response
	 * 
	 * @param location
	 *            of the city desired
	 * @return String of the http response
	 */
	public static String getWeather(String location) {

		HttpURLConnection c = null;
		InputStream in = null;

		try {
			c = (HttpURLConnection) (new URL(baseCall + location))
					.openConnection();
			c.setRequestMethod("GET");
			c.setDoInput(true);
			c.setDoOutput(true);
			c.connect();

			// reading from the http response
			StringBuffer buffer = new StringBuffer();
			in = c.getInputStream();
			BufferedReader read = new BufferedReader(new InputStreamReader(in));
			String line = null;
			while ((line = read.readLine()) != null) {
				buffer.append(line + "\r\n"); // carriage return and new line
			}

			in.close();
			c.disconnect();
			return buffer.toString();
		}

		catch (MalformedURLException ex) {
			ex.printStackTrace();
		} catch (IOException ex) {
			ex.printStackTrace();
		}

		finally {
			try {
				in.close();
			} catch (Throwable msg) {
			}
		}
		return null;
	}

	/**
	 * toString method to print the weather information neatly and organized
	 * 
	 * @return formatted String
	 */
	public String toString() {
		return "----- Coordinates\n      longitude: " + longitude
				+ "\n      latitude: " + latitude + "\n\n"
				+ "----- System\n      country: " + country
				+ "\n      sunrise: " + sunrise + "\n      sunset: " + sunset
				+ "\n\n" + "----- Weather\n      weather id: " + weatherId
				+ "\n      main: " + main + "\n      description: "
				+ description + "\n      iconCode: " + iconCode + "\n\n"
				+ "----- Base\n      " + base + "\n\n"
				+ "----- Main Weather Info\n      temperature: " + temp
				+ "\n      humidity: " + humidity + "\n      pressure: "
				+ pressure + "\n      min: " + min + "\n      max: " + max
				+ "\n\n" + "----- Wind\n      speed: " + speedWind
				+ "\n      degrees: " + degreesWind + "\n\n"
				+ "----- Clouds\n      all: " + clouds + "\n\n"
				+ "----- Dt\n      " + dt + "\n\n" + "----- Id\n      " + locId
				+ "\n\n" + "----- Name/City\n      " + city + "\n\n"
				+ "----- Cod\n      " + cod + "\n\n";
	}

	public String getCoordinates() {
		return "(" + latitude + ", " + longitude + ")";
	}

	public String getLocation() {
		return city + ", " + country;
	}

	public String getSunrise() {
		rise = new Date(sunrise * 1000L);
		r = new SimpleDateFormat("hh:mm a");
		r.setTimeZone(TimeZone.getTimeZone("GMT-5"));
		return r.format(rise);
	}

	public String getSunset() {
		set = new Date(sunset * 1000L);
		s = new SimpleDateFormat("hh:mm a");
		s.setTimeZone(TimeZone.getTimeZone("GMT-5"));
		return s.format(set);
	}

	public String getGroup() {
		return main + "(" + description + ")";
	}

	public String getIconId() {
		return iconCode;
	}

	public int getWeatherId() {
		return weatherId;
	}

	public String getWeatherBase() {
		return base;
	}

	public String getTemperatureC() {
		return (Math.round((temp - 273.2) * 10.0) / 10.0) + DEGREE + "C";
	}

	public String getTemperatureF() {
		return (Math.round((((temp - 273.2) * 1.8) + 32) * 10.0) / 10.0)
				+ DEGREE + "F";
	}

	public String getHumidity() {
		return humidity + " %";
	}

	public String getPressure() {
		return pressure + " hpa";
	}

	public String getMinC() {
		return (Math.round((min - 273.2) * 10.0) / 10.0) + DEGREE + "C";
	}

	public String getMinF() {
		return (Math.round((((min - 273.2) * 1.8) + 32) * 10.0) / 10.0)
				+ DEGREE + "F";
	}

	public String getMaxC() {
		return (Math.round((max - 273.2) * 10.0) / 10.0) + DEGREE + "C";
	}

	public String getMaxF() {
		return (Math.round((((max - 273.2) * 1.8) + 32) * 10.0) / 10.0)
				+ DEGREE + "F";
	}

	public String getSpeed() {
		return speedWind + " m/s";
	}

	public String getDegrees() {
		String directions[] = { "North", "Northeast", "East", "Southeast",
				"South", "Southwest", "West", "Northwest", "North" };
		return degreesWind + DEGREE + " ("
				+ directions[(int) Math.round(((degreesWind % 360) / 45))]
				+ ")";
	}

	public String getClouds() {
		return clouds + " % cloudiness";
	}

	public String getUpdateTime() {
		up = new Date(dt * 1000L);
		u = new SimpleDateFormat("dd/MM/yyyy hh:mm a");
		u.setTimeZone(TimeZone.getTimeZone("GMT-5"));
		return u.format(up);
	}

	public int getCityId() {
		return locId;
	}

	public static void main(String[] args) {
		WeatherInfo current = new WeatherInfo("London,On");
		System.out.println(current.toString());
		System.out.println(current.getSpeed());
		System.out.println(current.getDegrees());
		System.out.println(current.getTemperatureC());
		System.out.println(current.getTemperatureF());
		System.out.println("Last updated: " + current.getUpdateTime());
	}

}
