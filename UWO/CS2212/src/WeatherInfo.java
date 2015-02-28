import java.awt.image.BufferedImage;
import java.io.*;

import javax.imageio.*;

import java.net.URL;

import org.json.JSONObject;
import org.json.JSONArray;
import org.json.JSONException;

import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.text.SimpleDateFormat;
import java.lang.Math;

/**
 * This class creates WeatherInfo objects to store weather data from
 * openweathermap.
 * 
 * @author Eric Bachmeier
 * 
 */

public class WeatherInfo {

	/**
	 * Weather variable declarations
	 */
	private double longitude, latitude, temp, pressure, humidity, min, max,
			speedWind, degreesWind;
	private int weatherId, clouds, cod, locId;
	private String country, main, description, iconCode, base, city;
	private JSONObject j, jCoord, jSys, jWeatherObj, jMain, jWind, jClouds;
	private JSONArray jWeather;
	private Date rise, set, up;
	private SimpleDateFormat r, s, u;
	private long sunrise, sunset, dt;
	private HttpClient client;
	private Calendar cal;

	// base url for image requests
	private static String baseImg = "http://openweathermap.org/img/w/";

	// degree symbol constant
	final String DEGREE = "\u00b0";

	/**
	 * Constructor for an empty WeatherInfo object
	 */
	public WeatherInfo() {
		this.city = "";
		this.country = "";
		this.dt = 0;
		this.temp = 0;
		this.min = 0;
		this.max = 0;
		this.iconCode = "";
		this.main = "";
		this.description = "";
	}

	/**
	 * Constructor for a WeatherInfo object containing all categories of weather
	 * 
	 * @param location
	 *            String containing the city in which to retrieve data for
	 */
	public WeatherInfo(String location) {

		try {
			// remove any possible whitespace in the location passed
			location.replaceAll("\\s", "");
			// create Http call for the city passes, current data
			client = new HttpClient(location, "c");
			// create JSONObject for this data
			j = new JSONObject(client.getData());

			// "coordinate" tag
			jCoord = j.getJSONObject("coord");
			this.longitude = jCoord.getDouble("lon");
			this.latitude = jCoord.getDouble("lat");

			// "system" tag
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
	 * Method for retrieving the sky condition image from openweathermap api
	 * 
	 * @return BufferedImage object of the sky condition
	 */
	public BufferedImage getIcon() {
		try {
			// create a new image from the url code
			BufferedImage image = ImageIO.read(new URL(baseImg + iconCode
					+ ".png"));
			return image;
		} catch (IOException ex) {
			ex.printStackTrace();
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
				+ description + "\n\n" + "----- Base\n      " + base + "\n\n"
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

	/**
	 * Getter method for retrieving the coordinates of the city searched
	 * 
	 * @return String coordinates of the citys location
	 */
	public String getCoordinates() {
		return "(" + latitude + ", " + longitude + ")";
	}

	/**
	 * Getter method for retrieving the location and what country the city
	 * searched belongs to
	 * 
	 * @return String of the city and country name
	 */
	public String getLocation() {
		return city + ", " + country;
	}

	/**
	 * Getter method for retrieving the sunrise time
	 * 
	 * @return String of the sunrise time formatted to HH:MM AM/PM
	 */
	public String getSunrise() {
		cal = new GregorianCalendar();
		rise = new Date(sunrise * 1000L);
		r = new SimpleDateFormat("hh:mm a");
		r.setTimeZone(cal.getTimeZone());
		return r.format(rise);
	}

	/**
	 * Getter method for retrieving the sunset time
	 * 
	 * @return String of the sunset time formatted to HH:MM AM/PM
	 */
	public String getSunset() {
		cal = new GregorianCalendar();
		set = new Date(sunset * 1000L);
		s = new SimpleDateFormat("hh:mm a");
		s.setTimeZone(cal.getTimeZone());
		return s.format(set);
	}

	/**
	 * Getter method for retrieving the sky condition and its description
	 * 
	 * @return String of the sky condition formatted condition(description)
	 */
	public String getSky() {
		return main + " (" + description + ")";
	}

	/**
	 * Getter method for retrieving the weather id number
	 * 
	 * @return integer of the weather id from openweathermap
	 */
	public int getWeatherId() {
		return weatherId;
	}

	/**
	 * Getter method for retrieving weather base used for the data
	 * 
	 * @return String of the name of the weather base
	 */
	public String getWeatherBase() {
		return base;
	}

	/**
	 * Method for converting kelvin to celcius
	 * 
	 * @param the
	 *            temperature in kelvin
	 * 
	 * @return String of the converted temperature
	 */
	private static double convertCelcius(double t) {
		return Math.round((t - 273.15) * 10.0) / 10.0;
	}

	/**
	 * Method for converting kelvin to fahrenheit
	 * 
	 * @param the
	 *            temperature in kelvin
	 * 
	 * @return String of the converted temperature
	 */
	private static double convertFahrenheit(double t) {
		return Math.round((((t - 273.15) * 1.8) + 32) * 10.0) / 10.0;
	}

	/**
	 * Getter method for retrieving the current temperature of the current city
	 * 
	 * @param c
	 *            (celcius) or f (fahrenheit) to choose what conversion to be
	 *            used on the kelvin temperature
	 * 
	 * @return String of the current temperature, already converted
	 */
	public String getTemperature(String unit) {
		if (unit.equals("f") || unit.equals("F"))
			return convertFahrenheit(temp) + DEGREE + "F";
		else
			return convertCelcius(temp) + DEGREE + "C";
	}

	/**
	 * Getter method for retrieving the minimum temperature of the current city
	 * 
	 * @param c
	 *            (celcius) or f (fahrenheit) to choose what conversion to be
	 *            used on the kelvin temperature
	 * 
	 * @return String of the minimum temperature, already converted
	 */
	public String getMinTemp(String unit) {
		if (unit.equals("f") || unit.equals("F"))
			return convertFahrenheit(min) + DEGREE + "F";
		else
			return convertCelcius(min) + DEGREE + "C";
	}

	/**
	 * Getter method for retrieving the maximum temperature of the current city
	 * 
	 * @param c
	 *            (celcius) or f (fahrenheit) to choose what conversion to be
	 *            used on the kelvin temperature
	 * 
	 * @return String of the maximum temperature, already converted
	 */
	public String getMaxTemp(String unit) {
		if (unit.equals("f") || unit.equals("F"))
			return convertFahrenheit(max) + DEGREE + "F";
		else
			return convertCelcius(max) + DEGREE + "C";
	}

	/**
	 * Getter method for retrieving the humidity of the air
	 * 
	 * @return String of the percentage of humidity in the air
	 */
	public String getHumidity() {
		return humidity + "%";
	}

	/**
	 * Method for converting hpa to psi for imperial units
	 * 
	 * @param the
	 *            air pressure in hpa
	 * 
	 * @return double of the air pressure in psi
	 */
	private static double convertPressure(double p) {
		return Math.round(((p * 0.014503773773) * 1.00) / 1.00);
	}

	/**
	 * Getter method for retrieving the current air pressure
	 * 
	 * @return String of the air pressure in hpa
	 */
	public String getPressure(String unit) {
		if (unit.equals("f") || unit.equals("F"))
			return convertPressure(pressure) + "psi";
		else
			return pressure + "hpa";
	}

	/**
	 * Method for converting m/s to mph for imperial units
	 * 
	 * @param the
	 *            wind speed in m/s
	 * 
	 * @return double of the wind speed in m/s
	 */
	private static double convertSpeed(double s) {
		return Math.round(((s * 2.23694) * 1.00) / 1.00);
	}

	/**
	 * Getter method for retrieving the speed of the wind
	 * 
	 * @return String of the current wind speed in m/s
	 */
	public String getSpeed(String unit) {
		if (unit.equals("f") || unit.equals("F"))
			return convertSpeed(speedWind) + "mph";
		else
			return speedWind + "m/s";
	}

	/**
	 * Getter method for retrieving the direction of the wind
	 * 
	 * @return String of the wind direction in words
	 */
	public String getDegrees() {
		String directions[] = { "North", "Northeast", "East", "Southeast",
				"South", "Southwest", "West", "Northwest", "North" };
		return " (" + directions[(int) Math.round(((degreesWind % 360) / 45))]
				+ ")";
	}

	/**
	 * Getter method for retrieving the current cloudiness
	 * 
	 * @return String of the percentage of clouds in the sky
	 */
	public String getClouds() {
		return clouds + "% cloudiness";
	}

	/**
	 * Getter method for retrieving the time the weather info was last updated
	 * 
	 * @return String of the last update time in the format DD/MM/YYYY HH:MM
	 *         AM/PM
	 */
	public String getUpdateTime() {
		cal = new GregorianCalendar();
		up = new Date(dt * 1000L);
		u = new SimpleDateFormat("MM/dd/yyyy hh:mm a");
		u.setTimeZone(cal.getTimeZone());
		return u.format(up);
	}

	/**
	 * Getter method for retrieving the weather date for long term
	 * 
	 * @return String of the days date in the format DD/MM/YYYY
	 */
	public String getDate() {
		cal = new GregorianCalendar();
		up = new Date(dt * 1000L);
		u = new SimpleDateFormat("MM/dd/yyyy");
		u.setTimeZone(cal.getTimeZone());
		return u.format(up);
	}

	/**
	 * Getter method for retrieving the location id from openweathermap
	 * 
	 * @return integer of the current locations id
	 */
	public int getCityId() {
		return locId;
	}

	/**
	 * Setter method for setting the city name
	 * 
	 * @param name
	 *            String of city name
	 */
	public void setCity(String name) {
		this.city = name;
	}

	/**
	 * Setter method for setting the country name
	 * 
	 * @param name
	 *            String of country name
	 */
	public void setCountry(String name) {
		this.country = name;
	}

	/**
	 * Setter method for setting the icon code
	 * 
	 * @param code
	 *            String of the icon code of sky
	 */
	public void setIconCode(String code) {
		this.iconCode = code;
	}

	/**
	 * Setter method for setting the sky condition and description
	 * 
	 * @param main
	 *            String of sky condition
	 * @param desc
	 *            String description of the sky
	 */
	public void setSky(String main, String desc) {
		this.main = main;
		this.description = desc;
	}

	/**
	 * Setter method for setting the temperature
	 * 
	 * @param temp
	 *            double of the current temperature
	 */
	public void setTemp(double t) {
		this.temp = t;
	}

	/**
	 * Setter method for setting the minimum and maximum temperatures
	 * 
	 * @param min
	 *            double of the minimum temperature
	 * @param max
	 *            double of the maximum temperature
	 */
	public void setMinMax(double min, double max) {
		this.min = min;
		this.max = max;
	}

	/**
	 * Setter method for setting the unix time stamp
	 * 
	 * @param time
	 *            long unix time stamp
	 */
	public void setTime(long time) {
		this.dt = time;
	}
}