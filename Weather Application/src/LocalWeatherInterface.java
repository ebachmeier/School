import javax.swing.ButtonGroup;
import javax.swing.JRadioButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JTextArea;

import java.awt.Font;
import java.awt.Color;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * This class displays information for the Local Weather View aspect of the
 * program.
 * 
 * @author Lankesh Patel
 * 
 */

public class LocalWeatherInterface extends JFrame {

	private static final long serialVersionUID = 1L;
	private JPanel contentPane;
	private String unit;
	private String[] elements;
	JButton btnUpdate;
	JLabel lblLastUpdated;
	JLabel lblInsertLocationHere;
	JRadioButton rdbtnCelcius;
	JRadioButton rdbtnFahrenheit;
	JTextArea txtrcurrentTemperature;
	JTextArea txtrConditionOfThe;
	JTextArea txtrWindSpeedWind;
	JTextArea txtrTimeOfSunrise;
	JLabel sysUpdate;

	WeatherInfo local;
	ShortTermForecast sCast;

	/**
	 * Creates the frame and all of the objects that are necessary within it.
	 */
	public LocalWeatherInterface() {
		this.unit = Settings.instance.getUnit();
		this.elements = Settings.instance.getElements();
		initUI();
	}

	public void initUI() {

		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);

		// add for Singleton
		local = new WeatherInfo(Settings.instance.getLocation());

		// Creates Button object that is used to update weather information
		btnUpdate = new JButton();
		btnUpdate.setText("Update");
		btnUpdate.setFont(new Font("Lucida Grande", 1, 16));
		btnUpdate.setBounds(519, 249, 80, 40);
		contentPane.add(btnUpdate);

		btnUpdate.addChangeListener(new javax.swing.event.ChangeListener() {
			public void stateChanged(javax.swing.event.ChangeEvent evt) {
				btnUpdateStateChanged(evt);
			}
		});
		btnUpdate.addMouseListener(new java.awt.event.MouseAdapter() {
			public void mouseClicked(java.awt.event.MouseEvent evt) {
				btnUpdateMouseClicked(evt);
			}
		});
		btnUpdate.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				updateButtonActionPerformed(evt);
			}
		});

		// Creates a Label used to display information regarding the time of the
		// last update               
		lblLastUpdated = new JLabel("User Last Updated:     " + local.getCurrentTime());
		lblLastUpdated.setFont(new Font("Lucida Grande", 1, 16));
		lblLastUpdated.setBounds(519, 208, 366, 23);
		contentPane.add(lblLastUpdated);

		// Creates a Label used to display information regarding the time of the
		// last update for the system
		sysUpdate = new JLabel("System Last Updated: " + local.getUpdateTime());
		sysUpdate.setFont(new Font("Lucida Grande", 1, 16));
		sysUpdate.setBounds(519, 173, 366, 23);
		contentPane.add(sysUpdate);

		// Label object displays the current location the user is viewing
		// weather info for
		lblInsertLocationHere = new JLabel(local.getLocation());
		lblInsertLocationHere.setFont(new Font("Lucida Grande", 1, 22));
		lblInsertLocationHere.setBounds(354, 0, 240, 31);
		contentPane.add(lblInsertLocationHere);

		// Radio Button objects are used to select between Celcius & Fahrenheit
		rdbtnCelcius = new JRadioButton("Metric");
		rdbtnCelcius.setBackground(new Color(175, 210, 250));
		rdbtnCelcius.setFont(new Font("Lucida Grande", 1, 16));
		rdbtnCelcius.setBounds(519, 43, 140, 31);
		contentPane.add(rdbtnCelcius);
		rdbtnFahrenheit = new JRadioButton("Imperial");
		rdbtnFahrenheit.setBackground(new Color(175, 210, 250));
		rdbtnFahrenheit.setFont(new Font("Lucida Grande", 1, 16));
		rdbtnFahrenheit.setBounds(519, 86, 140, 31);
		contentPane.add(rdbtnFahrenheit);

		// A Button Group is created to only allow either Celsius or Fahrenheit
		// to be selected, not both
		ButtonGroup group = new ButtonGroup();
		group.add(rdbtnCelcius);
		group.add(rdbtnFahrenheit);

		if (unit.equals("c") || unit.equals("C"))
			rdbtnCelcius.setSelected(true);
		else
			rdbtnFahrenheit.setSelected(true);

		// Creates ActionListener to react to Celisus button being preseed;
		// changes UNIT variable to c
		rdbtnCelcius.addActionListener(new ActionListener() {

			public void actionPerformed(ActionEvent e) {
				// Execute when button is pressed
				unit = "c";
				Settings.instance.setUnit("c");
				// System.out.println(unit);
			}
		});
		// Creates ActionListener to react to Fahrenheit button being pressed;
		// changes UNIT variable to f

		rdbtnFahrenheit.addActionListener(new ActionListener() {

			public void actionPerformed(ActionEvent e) {
				// Execute when button is pressed
				unit = "f";
				Settings.instance.setUnit("f");
				// System.out.println(unit);
			}
		});

		if (rdbtnCelcius.isSelected())
			unit = "c";
		else
			unit = "f";

		// Label object that holds picture displaying condition of the sky

		/**
		 * Text Areas are created to display the information regarding the
		 * weather
		 */

		txtrcurrentTemperature = new JTextArea();
		txtrcurrentTemperature.setMargin(new Insets(12,12,12,12));
		txtrcurrentTemperature.setBackground(new Color(175, 210, 250));
		txtrcurrentTemperature.setFont(new Font("Lucida Grande", 1, 16));
		txtrcurrentTemperature.setEditable(false);
		txtrcurrentTemperature.setBounds(10, 37, 483, 126);
		if (elements[0].equals("Y") && elements[1].equals("Y")) {
			txtrcurrentTemperature.setText("   Temperature: "
					+ local.getTemperature(unit) + "\r\n\r\n   Minimum: "
					+ local.getMinTemp(unit) + "\r\n\r\n   Maximum: "
					+ local.getMaxTemp(unit));
		} else if (elements[0].equals("Y")) {
			txtrcurrentTemperature.setText("   Temperature: "
					+ local.getTemperature(unit)
					+ "\r\n\r\n   The min and max temperatures are hidden");
		} else if (elements[1].equals("Y")) {
			txtrcurrentTemperature.setText("The current temperature is hidden"
					+ "\r\n\r\n   Minimum: " + local.getMinTemp(unit)
					+ "\r\n\r\n   Maximum: " + local.getMaxTemp(unit));
		} else {
			txtrcurrentTemperature
					.setText("   The temperature information is all hidden");
		}
		contentPane.add(txtrcurrentTemperature);

		txtrConditionOfThe = new JTextArea();
		txtrConditionOfThe.setMargin(new Insets(0,7,12,0));
		txtrConditionOfThe.setBackground(new Color(210, 229, 243));
		txtrConditionOfThe.setFont(new Font("Lucida Grande", 1, 16));
		txtrConditionOfThe.setEditable(false);
		txtrConditionOfThe.setBounds(10, 174, 483, 63);
		if (elements[4].equals("Y")) {
			txtrConditionOfThe.setText("\r\n   " + local.getSky());
			// Label object that holds picture displaying condition of the sky
			JLabel label = new JLabel(new ImageIcon(local.getIcon()));
			label.setSize(66, 63);
			label.setLocation(260, 179);
			contentPane.add(label);
		} else {
			txtrConditionOfThe.setText("\r\n   The sky information is hidden");
		}
		contentPane.add(txtrConditionOfThe);

		txtrWindSpeedWind = new JTextArea();
		txtrWindSpeedWind.setMargin(new Insets(12,7,12,12));
		txtrWindSpeedWind.setBackground(new Color(175, 210, 250));
		txtrWindSpeedWind.setFont(new Font("Lucida Grande", 1, 16));
		txtrWindSpeedWind.setEditable(false);
		txtrWindSpeedWind.setBounds(10, 249, 483, 179);
		if (elements[2].equals("Y") && elements[3].equals("Y")) {
			txtrWindSpeedWind.setText("   Wind Speed: " + local.getSpeed(unit)
					+ local.getDegrees() + "\r\n\r\n   Air Pressure: "
					+ local.getPressure(unit) + "\r\n\r\n   Humidity: "
					+ local.getHumidity());
		} else if (elements[2].equals("Y")) {
			txtrWindSpeedWind.setText("   Wind Speed: " + local.getSpeed(unit)
					+ local.getDegrees()
					+ "\r\n\r\n   The air information is hidden");
		} else if (elements[3].equals("Y")) {
			txtrWindSpeedWind
					.setText("   The wind speed and direction is hidden"
							+ "\r\n\r\n   Air Pressure: "
							+ local.getPressure(unit) + "\r\n\r\n   Humidity: "
							+ local.getHumidity());
		} else {
			txtrWindSpeedWind
					.setText("   The wind speed and air information is all hidden");
		}
		contentPane.add(txtrWindSpeedWind);

		txtrTimeOfSunrise = new JTextArea();
		txtrTimeOfSunrise.setMargin(new Insets(12,7,12,12));
		txtrTimeOfSunrise.setBackground(new Color(210, 229, 243));
		txtrTimeOfSunrise.setFont(new Font("Lucida Grande", 1, 16));
		txtrTimeOfSunrise.setEditable(false);
		txtrTimeOfSunrise.setBounds(10, 439, 483, 88);
		if (elements[5].equals("Y")) {
			txtrTimeOfSunrise.setText("   Time of Sunrise: "
					+ local.getSunrise() + "\r\n\r\n   Time of Sunset: "
					+ local.getSunset());
		} else {
			txtrTimeOfSunrise
					.setText("   The sunset and sunrise times are hidden");
		}
		contentPane.add(txtrTimeOfSunrise);

		Settings.instance.setUnit(unit);

		// setContentPane(contentPane);
	}

	private void btnUpdateStateChanged(javax.swing.event.ChangeEvent evt) {

	}

	private void btnUpdateMouseClicked(java.awt.event.MouseEvent evt) {

	}

	/**
	 * update Button function
	 */
	private void updateButtonActionPerformed(java.awt.event.ActionEvent evt) {
		local = new WeatherInfo(Settings.instance.getLocation());
		lblLastUpdated.setText("User Last Updated:     " + local.getCurrentTime());
		lblInsertLocationHere.setText(local.getLocation());
		sysUpdate.setText("System Last Updated: " + local.getUpdateTime());

		if (elements[0].equals("Y") && elements[1].equals("Y")) {
			txtrcurrentTemperature.setText("   Temperature: "
					+ local.getTemperature(unit) + "\r\n\r\n   Minimum: "
					+ local.getMinTemp(unit) + "\r\n\r\n   Maximum: "
					+ local.getMaxTemp(unit));
		} else if (elements[0].equals("Y")) {
			txtrcurrentTemperature.setText("   Temperature: "
					+ local.getTemperature(unit)
					+ "\r\n\r\n   The min and max temperatures are hidden");
		} else if (elements[1].equals("Y")) {
			txtrcurrentTemperature.setText("The current temperature is hidden"
					+ "\r\n\r\n   Minimum: " + local.getMinTemp(unit)
					+ "\r\n\r\n   Maximum: " + local.getMaxTemp(unit));
		} else {
			txtrcurrentTemperature
					.setText("   The temperature information is all hidden");
		}

		if (elements[2].equals("Y") && elements[3].equals("Y")) {
			txtrWindSpeedWind.setText("   Wind Speed: " + local.getSpeed(unit)
					+ local.getDegrees() + "\r\n\r\n   Air Pressure: "
					+ local.getPressure(unit) + "\r\n\r\n   Humidity: "
					+ local.getHumidity());
		} else if (elements[2].equals("Y")) {
			txtrWindSpeedWind.setText("   Wind Speed: " + local.getSpeed(unit)
					+ local.getDegrees()
					+ "\r\n\r\n   The air information is hidden");
		} else if (elements[3].equals("Y")) {
			txtrWindSpeedWind
					.setText("   The wind speed and direction is hidden"
							+ "\r\n\r\n   Air Pressure: "
							+ local.getPressure(unit) + "\r\n\r\n   Humidity: "
							+ local.getHumidity());
		} else {
			txtrWindSpeedWind
					.setText("   The wind speed and air information is all hidden");
		}

		if (elements[5].equals("Y")) {
			txtrTimeOfSunrise.setText("   Time of Sunrise: "
					+ local.getSunrise() + "\r\n\r\n   Time of Sunset: "
					+ local.getSunset());
		} else {
			txtrTimeOfSunrise
					.setText("   The sunset and sunrise times are hidden");
		}
	}
}
