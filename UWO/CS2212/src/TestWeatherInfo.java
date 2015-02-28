/**
 * This class is for testing my backend classes and so you group members can see
 * how to implement my methods in your GUI pages
 * 
 * @author Eric Bachmeier
 * 
 */
public class TestWeatherInfo {
	public static void main(String[] args) {
		// local weather view
		System.out.println("LOCAL WEATHER VIEW\n");
		WeatherInfo local = new WeatherInfo("London, on");
		System.out.println("\tLocation: " + local.getLocation());
		System.out.println("\tTemperature: "
				+ local.getTemperature("c") // c for celcius
				+ "\tMin: " + local.getMinTemp("c") + "\tMax: "
				+ local.getMaxTemp("c"));
		System.out.println("\tWind: " + local.getSpeed("c") + " "
				+ local.getDegrees());
		System.out.println("\tAir Pressure: " + local.getPressure("c"));
		System.out.println("\tHumidity: " + local.getHumidity());
		System.out.println("\tSky: " + local.getSky());
		System.out.println("\tSunrise: " + local.getSunrise() + "\tSunset: "
				+ local.getSunset());
		/*
		 * code to get icon image JLabel label = new JLabel(new
		 * ImageIcon(weatherObj.getIcon())); JPanel panel = new JPanel();
		 * panel.add(label); this.add(panel);
		 */

		// ///////////////////////////////////////

		WeatherInfo increment;
		// short term forecast
		System.out.println("\nSHORT-TERM FORECAST\n");
		ShortTermForecast shortterm = new ShortTermForecast("London, on");
		WeatherInfo[] hourly = shortterm.getHourly();
		increment = hourly[0];
		System.out.println("\tLocation: " + increment.getLocation());
		// first closest 3 hour increment
		increment = hourly[1];
		System.out.println("\t-- " + increment.getUpdateTime() + " --");
		System.out.println("\tTemperature: " + increment.getTemperature("c"));
		System.out.println("\tSky: " + increment.getSky());
		// second closest 3 hour increment
		increment = hourly[2];
		System.out.println("\n\t-- " + increment.getUpdateTime() + " --");
		System.out.println("\tTemperature: " + increment.getTemperature("c"));
		System.out.println("\tSky: " + increment.getSky());
		// third increment
		increment = hourly[3];
		System.out.println("\n\t-- " + increment.getUpdateTime() + " --");
		System.out.println("\tTemperature: " + increment.getTemperature("c"));
		System.out.println("\tSky: " + increment.getSky());

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
		System.out.println("\tTemperature: " + day.getTemperature("c")
				+ "\tMin: " + day.getMinTemp("c") + "\tMax: "
				+ day.getMaxTemp("c"));
		System.out.println("\tSky: " + day.getSky());
		// second day
		day = daily[2];
		System.out.println("\n\t-- " + day.getDate() + " --");
		System.out.println("\tTemperature: " + day.getTemperature("c")
				+ "\tMin: " + day.getMinTemp("c") + "\tMax: "
				+ day.getMaxTemp("c"));
		System.out.println("\tSky: " + day.getSky());
		// third day
		day = daily[3];
		System.out.println("\n\t-- " + day.getDate() + " --");
		System.out.println("\tTemperature: " + day.getTemperature("c")
				+ "\tMin: " + day.getMinTemp("c") + "\tMax: "
				+ day.getMaxTemp("c"));
		System.out.println("\tSky: " + day.getSky());

		System.out.println("\nLast updated " + local.getUpdateTime() + "\n");
	}
}
