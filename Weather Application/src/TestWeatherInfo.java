/**
 * This class is for testing my backend classes and so you group members can see
 * how to implement my methods in your GUI pages
 * 
 * @author Eric Bachmeier
 * 
 */
public class TestWeatherInfo {
	
	/*public static void main(String args[]) {
		String[] cities = {"London, On"};
		String unit = "c";
		String elements = "YYYYYYYYYY";
		new LocalWeatherInterface(cities, unit, cities.length, 0, elements).setVisible(true);
	}*/
	
	public static void main(String[] args) {

		// UNITS selection from user
		String UNIT = "c"; // "c" or "f"

		// city search
		String location = "London, on";

		try {
			WeatherInfo local = new WeatherInfo(location);
			if (local.getLocation().length() <= 0
					|| local.getLocation() == null) {
				System.out.println(local.getLocation()
						+ " was not found in the database.");
			} else {
				System.out.println(local.getLocation() + " was found... ");
				// local weather view
				System.out.println("\nLOCAL WEATHER VIEW\n");
				System.out.println("\tLocation: " + local.getLocation());
				System.out.println("\tTemperature: "
						+ local.getTemperature(UNIT) // c for celcius
						+ "\tMin: " + local.getMinTemp(UNIT) + "\tMax: "
						+ local.getMaxTemp(UNIT));
				System.out.println("\tWind: " + local.getSpeed(UNIT) + " "
						+ local.getDegrees());
				System.out
						.println("\tAir Pressure: " + local.getPressure(UNIT));
				System.out.println("\tHumidity: " + local.getHumidity());
				System.out.println("\tSky: " + local.getSky());
				System.out.println("\tSunrise: " + local.getSunrise()
						+ "\tSunset: " + local.getSunset());
				/*
				 * // CODE FOR SKY CONDITION IMAGE JLabel label = new JLabel(new
				 * ImageIcon(weatherObj.getIcon())); JPanel panel = new
				 * JPanel(); panel.add(label);
				 */

				// ///////////////////////////////////////

				WeatherInfo increment;
				// short term forecast
				System.out.println("\nSHORT-TERM FORECAST\n");
				ShortTermForecast shortterm = new ShortTermForecast(
						"London, on");
				WeatherInfo[] hourly = shortterm.getHourly();
				increment = hourly[0];
				System.out.println("\tLocation: " + increment.getLocation());
				// first closest 3 hour increment
				increment = hourly[1];
				System.out.println("\t-- " + increment.getUpdateTime() + " --");
				System.out.println("\tTemperature: "
						+ increment.getTemperature(UNIT));
				System.out.println("\tSky: " + increment.getSky());
				// second closest 3 hour increment
				increment = hourly[2];
				System.out.println("\n\t-- " + increment.getUpdateTime()
						+ " --");
				System.out.println("\tTemperature: "
						+ increment.getTemperature(UNIT));
				System.out.println("\tSky: " + increment.getSky());
				// third increment
				increment = hourly[3];
				System.out.println("\n\t-- " + increment.getUpdateTime()
						+ " --");
				System.out.println("\tTemperature: "
						+ increment.getTemperature(UNIT));
				System.out.println("\tSky: " + increment.getSky());
				/*
				 * // CODE FOR SKY CONDITION IMAGE JLabel label = new JLabel(new
				 * ImageIcon(weatherObj.getIcon())); JPanel panel = new
				 * JPanel(); panel.add(label);
				 */

				// ///////////////////////////////////////

				WeatherInfo day;
				// long term forecast
				System.out.println("\nLONG-TERM FORECAST\n");
				LongTermForecast longterm = new LongTermForecast("London, on");
				WeatherInfo[] daily = longterm.getDaily();
				day = daily[0];
				System.out.println("\tLocation: " + day.getLocation());
				// first day
				day = daily[1];
				System.out.println("\t-- " + day.getDate() + " --");
				System.out.println("\tTemperature: " + day.getTemperature(UNIT)
						+ "\tMin: " + day.getMinTemp(UNIT) + "\tMax: "
						+ day.getMaxTemp(UNIT));
				System.out.println("\tSky: " + day.getSky());
				// second day
				day = daily[2];
				System.out.println("\n\t-- " + day.getDate() + " --");
				System.out.println("\tTemperature: " + day.getTemperature(UNIT)
						+ "\tMin: " + day.getMinTemp(UNIT) + "\tMax: "
						+ day.getMaxTemp(UNIT));
				System.out.println("\tSky: " + day.getSky());
				// third day
				day = daily[3];
				System.out.println("\n\t-- " + day.getDate() + " --");
				System.out.println("\tTemperature: " + day.getTemperature(UNIT)
						+ "\tMin: " + day.getMinTemp(UNIT) + "\tMax: "
						+ day.getMaxTemp(UNIT));
				System.out.println("\tSky: " + day.getSky());
				/*
				 * // CODE FOR SKY CONDITION IMAGE JLabel label = new JLabel(new
				 * ImageIcon(weatherObj.getIcon())); JPanel panel = new
				 * JPanel(); panel.add(label);
				 */

				System.out.println("\nLast updated " + local.getUpdateTime()
						+ "\n");
			}
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}
}
