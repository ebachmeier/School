import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;

import javax.swing.*;

/**
 * this class provides options for customers to show and hide information from
 * openweathermap
 * 
 * @author Zeyu
 * 
 */

public class CustomWeatherInterface extends JFrame implements ItemListener {

	/**
	 * the variables used in on the interface declaration jpanel layout and
	 * checkbox
	 */
	private static final long serialVersionUID = 1L;
	private String[] elements;
	JPanel jPanel, jPanelYellow1, jPanelYellow2, jPanelYellow3, jPanelYellow4;
	GridLayout g, g11, g12, g13, g14;
	JCheckBox current = new JCheckBox("   Current Temperature");
	JCheckBox minmax = new JCheckBox("   Expected Min and Max Temp for Today");
	JCheckBox sky = new JCheckBox("   Condition of the Sky");
	JCheckBox wind = new JCheckBox("   Wind Speed and Direction");
	JCheckBox air = new JCheckBox("   Air Pressure and Humidity");
	JCheckBox sun = new JCheckBox("   Time of Sunrise and Sunset");

	JButton updateButton = new JButton();

	/**
	 * set the interface properties
	 */
	public CustomWeatherInterface() {
		this.elements = Settings.instance.getElements();
		init();
	}

	/**
	 * define all the jPanels the layouts and the jTabbedPanes
	 */

	public void init() {
	
		jPanel = new JPanel();
		jPanel.setBackground(new Color(255, 255, 255));
		jPanel.setName("Custom Weather View");

		updateButton.setText("Save Changes");

		updateButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent evt) {
				updateButtonActionPerformed(evt);
			}
		});

		updateButton.setBounds(15, 226, 150, 40);
		updateButton.setFont(new Font("Lucida Grande", 1, 16));

		jPanel.add(updateButton);

		if (elements[0].equals("Y"))
			current.setSelected(true);
		else
			current.setForeground(Color.GRAY);
		jPanel.setLayout(null);
		minmax.setBounds(5, 41, 364, 23);
		jPanel.add(minmax);
		minmax.addItemListener(this);
		minmax.setFocusPainted(false);
		current.setBounds(5, 6, 214, 23);
		jPanel.add(current);
		current.setFocusPainted(false);
		current.addItemListener(this);

		if (elements[1].equals("Y"))
			minmax.setSelected(true);
		else
			minmax.setForeground(Color.GRAY);

		if (elements[4].equals("Y"))
			sky.setSelected(true);
		else
			sky.setForeground(Color.GRAY);

		if (elements[2].equals("Y"))
			wind.setSelected(true);
		else
			wind.setForeground(Color.GRAY);
		sky.setBounds(5, 146, 333, 23);
		jPanel.add(sky);
		sky.addItemListener(this);
		sky.setFocusPainted(false);

		if (elements[3].equals("Y"))
			air.setSelected(true);
		else
			air.setForeground(Color.GRAY);
		air.setBounds(5, 111, 212, 23);
		jPanel.add(air);
		air.addItemListener(this);

		if (elements[5].equals("Y"))
			sun.setSelected(true);
		else
			sun.setForeground(Color.GRAY);
		wind.setBounds(5, 76, 413, 23);
		jPanel.add(wind);
		wind.addItemListener(this);
		wind.setFocusPainted(false);
		sun.setBounds(5, 181, 399, 23);
		jPanel.add(sun);
		sun.addItemListener(this);
		setContentPane(jPanel);
	}

	/**
	 * set the two situation of the changes content of show and hide
	 */
	public void itemStateChanged(ItemEvent arg0) {
		if (((JCheckBox) arg0.getSource()).isSelected()) {
			if (((JCheckBox) arg0.getSource()).getText().trim()
					.equals("Current Temperature")) {
				current.setForeground(Color.BLACK);
				elements[0] = "Y";
			}
			if (((JCheckBox) arg0.getSource()).getText().trim()
					.equals("Expected Min and Max Temp for Today")) {
				minmax.setForeground(Color.BLACK);
				elements[1] = "Y";
			}
			if (((JCheckBox) arg0.getSource()).getText().trim()
					.equals("Condition of the Sky")) {
				sky.setForeground(Color.BLACK);
				elements[4] = "Y";
			}
			if (((JCheckBox) arg0.getSource()).getText().trim()
					.equals("Wind Speed and Direction")) {
				wind.setForeground(Color.BLACK);
				elements[2] = "Y";
			}
			if (((JCheckBox) arg0.getSource()).getText().trim()
					.equals("Air Pressure and Humidity")) {
				air.setForeground(Color.BLACK);
				elements[3] = "Y";
			}
			if (((JCheckBox) arg0.getSource()).getText().trim()
					.equals("Time of Sunrise and Sunset")) {
				sun.setForeground(Color.BLACK);
				elements[5] = "Y";
			}
		} else {
			if (((JCheckBox) arg0.getSource()).getText().trim()
					.equals("Current Temperature")) {
				current.setForeground(Color.GRAY);
				elements[0] = "N";
			}
			if (((JCheckBox) arg0.getSource()).getText().trim()
					.equals("Expected Min and Max Temp for Today")) {
				minmax.setForeground(Color.GRAY);
				elements[1] = "N";
			}
			if (((JCheckBox) arg0.getSource()).getText().trim()
					.equals("Condition of the Sky")) {
				sky.setForeground(Color.GRAY);
				elements[4] = "N";
			}
			if (((JCheckBox) arg0.getSource()).getText().trim()
					.equals("Wind Speed and Direction")) {
				wind.setForeground(Color.GRAY);
				elements[2] = "N";
			}
			if (((JCheckBox) arg0.getSource()).getText().trim()
					.equals("Air Pressure and Humidity")) {
				air.setForeground(Color.GRAY);
				elements[3] = "N";
			}
			if (((JCheckBox) arg0.getSource()).getText().trim()
					.equals("Time of Sunrise and Sunset")) {
				sun.setForeground(Color.GRAY);
				elements[5] = "N";
			}
		}
		Settings.instance.setElements(elements);
	}

	/**
	 * update Button function
	 */
	private void updateButtonActionPerformed(ActionEvent evt) {
		MyLocationsInterface.tabShort.removeTabAt(1);
		MyLocationsInterface.tabShort.insertTab("Local Weather", new ImageIcon(), new LocalWeatherInterface().getContentPane(), "", 1);
		MyLocationsInterface.tabShort.setSelectedIndex(1);
	}
}