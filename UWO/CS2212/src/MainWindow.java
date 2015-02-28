import javax.swing.JFrame;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;

import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;

import java.awt.Dimension;
import java.awt.Font;

import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.JButton;
import javax.swing.ButtonGroup;
import javax.swing.JRadioButton;

import java.awt.Color;

import javax.swing.GroupLayout;
import java.awt.BorderLayout;

import javax.swing.SwingConstants;
import javax.swing.GroupLayout.Alignment;
import javax.swing.LayoutStyle.ComponentPlacement;

public class MainWindow extends JFrame {

	private JTextField location;
	private JLabel temp, updated;
	private JRadioButton fahrenheit;
	private JRadioButton celcius;
	private String c;
	private WeatherInfo current;

	// degree symbol
	final String DEGREE = "\u00b0";

	public MainWindow() {
		this.initUI();
	}

	/**
	 * Create the frame
	 */
	private void initUI() {

		this.setFont(new Font("Monaco", Font.BOLD, 14));
		this.setTitle("Weather App - Team 1");
		this.setSize(480, 800);
		this.setLocationRelativeTo(null);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.setJMenuBar(this.createMenubar());

		getContentPane().setLayout(new BorderLayout());
		getContentPane().add(this.createForm(), BorderLayout.CENTER);

		JPanel pnlWest = new JPanel();
		pnlWest.setBackground(Color.BLUE);
		pnlWest.setPreferredSize(new Dimension(10, 800));

		JPanel pnlEast = new JPanel();
		pnlEast.setBackground(Color.BLUE);
		pnlEast.setPreferredSize(new Dimension(10, 800));

		JPanel pnlNorth = new JPanel();
		pnlNorth.setBackground(Color.RED);
		pnlNorth.setPreferredSize(new Dimension(480, 50));
			
		JPanel pnlSouth = new JPanel();
		pnlSouth.setBackground(Color.BLUE);
		pnlSouth.setPreferredSize(new Dimension(480, 50));

		// this.add(pnlEast, BorderLayout.EAST);
		// this.add(pnlWest, BorderLayout.WEST);
		this.add(pnlNorth, BorderLayout.NORTH);
		// this.add(pnlSouth, BorderLayout.SOUTH);
	}

	private JPanel createForm() {

		JPanel panel = new JPanel();
		panel.setBackground(Color.ORANGE);
		
		JLabel locationLabel = new JLabel("Location: ");
		location = new JTextField();
		location.setPreferredSize(new Dimension(75, 25));

		JLabel optLabel = new JLabel("Options: ");
		celcius = new JRadioButton(DEGREE + "C");
		fahrenheit = new JRadioButton(DEGREE + "F");

		ButtonGroup tempChoice = new ButtonGroup();
		tempChoice.add(this.celcius);
		tempChoice.add(this.fahrenheit);

		/**
		 * View Weather button event
		 */
		temp = new JLabel();
		updated = new JLabel();
		JButton view = new JButton("View Weather!");
		view.setHorizontalAlignment(SwingConstants.RIGHT);
		view.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				// message displayed when button view weather pressed
				String temperature = null;
				String lastUpdate = null;
				c = location.getText();
				current = new WeatherInfo(c);
				if (celcius.isSelected()) {
					temperature = "The temperature in " + current.getLocation()
							+ " is " + current.getTemperature("C");
					lastUpdate = "Last updated " + current.getUpdateTime();
				} else if (fahrenheit.isSelected()) {
					temperature = "The temperature in " + current.getLocation()
							+ " is " + current.getTemperature("F");
					lastUpdate = "Last updated " + current.getUpdateTime();
				} else {
					temperature = "Choose an option first!";
					lastUpdate = "";
				}
				temp.setText(temperature);
				updated.setText(lastUpdate);
			}
		});

		/**
		 * Layout of the app from panel
		 */
		GroupLayout layout = new GroupLayout(panel);
		layout.setHorizontalGroup(layout
				.createParallelGroup(Alignment.LEADING)
				.addGroup(
						layout.createSequentialGroup()
								.addGroup(
										layout.createParallelGroup(
												Alignment.LEADING)
												.addGroup(
														layout.createSequentialGroup()
																.addGroup(
																		layout.createParallelGroup(
																				Alignment.LEADING)
																				.addComponent(
																						locationLabel)
																				.addComponent(
																						optLabel))
																.addGroup(
																		layout.createParallelGroup(
																				Alignment.LEADING,
																				false)
																				.addComponent(
																						location,
																						269,
																						269,
																						269)
																				.addGroup(
																						layout.createSequentialGroup()
																								.addComponent(
																										celcius)
																								.addComponent(
																										fahrenheit)
																								.addPreferredGap(
																										ComponentPlacement.RELATED,
																										GroupLayout.DEFAULT_SIZE,
																										Short.MAX_VALUE)
																								.addComponent(
																										view))))
												.addComponent(temp)
												.addComponent(updated))
								.addGap(131)));
		layout.setVerticalGroup(layout
				.createParallelGroup(Alignment.LEADING)
				.addGroup(
						layout.createSequentialGroup()
								.addGroup(
										layout.createParallelGroup(
												Alignment.BASELINE)
												.addComponent(locationLabel)
												.addComponent(
														location,
														GroupLayout.PREFERRED_SIZE,
														GroupLayout.DEFAULT_SIZE,
														GroupLayout.PREFERRED_SIZE))
								.addGroup(
										layout.createParallelGroup(
												Alignment.BASELINE)
												.addComponent(optLabel)
												.addComponent(celcius)
												.addComponent(fahrenheit)
												.addComponent(view))
								.addComponent(temp).addComponent(updated)
								.addGap(29)));
		layout.setAutoCreateGaps(true);
		layout.setAutoCreateContainerGaps(true);
		panel.setLayout(layout);
		return panel;

	}

	/**
	 * Menu bar on top bar of app
	 * 
	 * @return
	 */
	private JMenuBar createMenubar() {
		JMenuBar menubar = new JMenuBar();
		menubar.setBackground(Color.WHITE);
		JMenu mnuFile = new JMenu("File");
		mnuFile.setMnemonic(KeyEvent.VK_F);
		JMenuItem mniFileExit = new JMenuItem("Exit");
		JMenuItem test = new JMenuItem("Hi");
		mniFileExit.setMnemonic(KeyEvent.VK_E);
		mniFileExit.setToolTipText("Exit application");
		mniFileExit.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent event) {
				System.exit(0);
			}
		});
		mnuFile.add(mniFileExit);
		mnuFile.add(test);
		menubar.add(mnuFile);
		return menubar;
	}
}