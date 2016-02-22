import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.Calendar;
import java.util.GregorianCalendar;

import javax.swing.GroupLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JFrame;
import javax.swing.LayoutStyle;
import javax.swing.border.BevelBorder;
import javax.swing.border.SoftBevelBorder;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.GroupLayout.Alignment;
import javax.swing.LayoutStyle.ComponentPlacement;

/**
 * 
 * This class displays the Graphical User Interface for the page
 * "Long term forecast"
 * 
 * this page specified user'a abilities as following: must be able to view a
 * daily forecast for the current location for at least 5 days be able to view
 * temperature, sky condition,and an icon representing the sky condition
 * 
 * 
 * @author Menghan Yu
 * 
 */
public class LongTermInterface extends JFrame {

	private static final long serialVersionUID = 1L;

	//private JLabel clock;
	private JPanel day0;
	private JPanel day1;
	private JPanel day2;
	private JPanel day3;
	private JPanel day4;
	private JPanel day5;
	private JButton localUpdateButt;
	private JLabel day0_date;
	private JLabel day0_temp;
	private JLabel day0_icon;
	private JLabel day1_date;
	private JLabel day1_temp;
	private JLabel day1_icon;
	private JLabel localCityName;
	private JLabel day2_date;
	private JLabel day2_temp;
	private JLabel day2_icon;
	private JLabel day3_date;
	private JLabel day3_temp;
	private JLabel day3_icon;
	private JLabel day4_date;
	private JLabel day4_temp;
	private JLabel day4_icon;
	private JLabel day5_date;
	private JLabel day5_temp;
	private JLabel day5_icon;
	private JLabel lastUpdateTime;
	private JLabel localTemp;
	private JLabel day2_minTemp;
	private JLabel day2_maxTemp;
	private JLabel day0_minTemp;
	private JLabel day0_maxTemp;
	private JLabel day1_minTemp;
	private JLabel day1_maxTemp;
	private JLabel day3_minTemp;
	private JLabel day3_maxTemp;
	private JLabel day4_minTemp;
	private JLabel day4_maxTemp;
	private JLabel day5_minTemp;
	private JLabel day5_maxTemp;
	private JPanel lTLeftPanel;
	private JPanel lTMidPanel;
	private JScrollPane lTMidScroll;
	private JPanel lTRightPanel;
	private JPanel longPanel;
	private JPanel midInside;
	private String unit;
	private JLabel lastUpdate;	//add for system update
	private JLabel clock;
	private int timeRun = 0; // clock function
	private JLabel date;
	
	WeatherInfo current;
	LongTermForecast  lCast;
	WeatherInfo[] daily;
	WeatherInfo i;
	
	/**
	 * Creates new form shortTermForecast
	 */
	public LongTermInterface() {
		initComponents();
		
		
		/**
		 * clock function
		 */
		new Thread()
		{
			public void run()
			{
				while (timeRun == 0)
				{
					Calendar cal = new GregorianCalendar();

					String dHour = null;
					String dMin = null;
					String dSec = null;
					int hour = cal.get(Calendar.HOUR);
					int min = cal.get(Calendar.MINUTE);
					int sec = cal.get(Calendar.SECOND);
					int AM_PM = cal.get(Calendar.AM_PM);
					
					if (hour == 0)
						hour += 12;
					if(hour < 10){
						dHour = " " + String.valueOf(hour);
					}
					else{
						dHour = String.valueOf(hour);
					}
					
					if(min < 10){
						dMin = "0" + String.valueOf(min);
					}
					else{
						dMin = String.valueOf(min);
					}
					if(sec < 10){
						dSec = "0" + String.valueOf(sec);
					}
					else{
						dSec = String.valueOf(sec);
					}
					
					String day_night = "";
					
					if(AM_PM == 1)
					{
						day_night = "PM";
					}
					else
					{
						day_night = "AM";
					}
					
					String time = dHour + ":" + dMin + ":" + dSec + " " + day_night;

					clock.setText("<html>Current Time<br><html>" + time);
				}
			}
		}.start();
	}

/**
 * body of long term interface
 */
	private void initComponents() {

		//clock = new JLabel();
		longPanel = new JPanel();
		lTLeftPanel = new JPanel();
		localUpdateButt = new JButton();
		localCityName = new JLabel();
		lastUpdateTime = new JLabel();
		localTemp = new JLabel();
		lTMidPanel = new JPanel();
		lTMidScroll = new JScrollPane();
		midInside = new JPanel();
		lastUpdate = new JLabel();	//add for User update
		clock = new JLabel();	// clock label
		date = new JLabel();
		
		/**
		 * creating long-term forecast daily view, each day has their own small
		 * panel include today and 5 days in the future
		 */

		// today, initialize as day 0
		day0 = new JPanel();
		day0_date = new JLabel();
		day0_temp = new JLabel();
		day0_icon = new JLabel();
		day0_minTemp = new JLabel();
		day0_maxTemp = new JLabel();

		// tomorrow, day1
		day1 = new JPanel();
		day1_date = new JLabel();
		day1_temp = new JLabel();
		day1_icon = new JLabel();
		day1_minTemp = new JLabel();
		day1_maxTemp = new JLabel();

		// day2
		day2 = new JPanel();
		day2_date = new JLabel();
		day2_temp = new JLabel();
		day2_icon = new JLabel();
		day2_minTemp = new JLabel();
		day2_maxTemp = new JLabel();

		// day3
		day3 = new JPanel();
		day3_date = new JLabel();
		day3_temp = new JLabel();
		day3_icon = new JLabel();
		day3_minTemp = new JLabel();
		day3_maxTemp = new JLabel();

		// day4
		day4 = new JPanel();
		day4_date = new JLabel();
		day4_temp = new JLabel();
		day4_icon = new JLabel();
		day4_maxTemp = new JLabel();
		day4_minTemp = new JLabel();

		// day5
		day5 = new JPanel();
		day5_date = new JLabel();
		day5_temp = new JLabel();
		day5_icon = new JLabel();
		day5_maxTemp = new JLabel();
		day5_minTemp = new JLabel();
		this.unit = Settings.instance.getUnit();
		current = new WeatherInfo(Settings.instance.getLocation());
		lCast = new LongTermForecast(Settings.instance.getLocation());
		daily = lCast.getDaily();
		i = daily[1];
		

		/**
		 * creating another long term inner panel this panel sit right side of
		 * the window using for add some extra information and support the page
		 */
		lTRightPanel = new JPanel();
		setBackground(new Color(255, 255, 255));

		longPanel.setBackground(new Color(255, 255, 255));

		lTMidPanel.setBorder(new SoftBevelBorder(BevelBorder.RAISED));

		midInside.setBorder(new SoftBevelBorder(BevelBorder.RAISED));

		midInside.setPreferredSize(new Dimension(522, 820));


		/*********** left panel *************/
		lTLeftPanel.setBorder(new SoftBevelBorder(BevelBorder.RAISED));

		localUpdateButt.setText("Update");
		localUpdateButt.setFont(new java.awt.Font("Lucida Grande", 1, 16));
		localUpdateButt.addChangeListener(new ChangeListener() {
			public void stateChanged(ChangeEvent evt) {
				updateButtonStateChanged(evt);
			}
		});
		localUpdateButt.addMouseListener(new MouseAdapter() {
			public void mouseClicked(MouseEvent evt) {
				updateButtonMouseClicked(evt);
			}
		});
		localUpdateButt.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent evt) {
				updateButtonActionPerformed(evt);
			}
		});

		localCityName.setSize(218, 525);
		localCityName.setFont(new java.awt.Font("Lucida Grande", 1, 14));
		localCityName.setText(current.getLocation());
		lastUpdateTime.setText("<html>System Last Updated:<br><html> " + current.getUpdateTime());
		lastUpdate.setText("<html>User Last Update: <br><html>" + current.getCurrentTime());
		localTemp.setText("Currently: " + current.getTemperature(unit));

		lTLeftPanel.setMaximumSize(new java.awt.Dimension(218, 525));
        lTLeftPanel.setMinimumSize(new java.awt.Dimension(218, 525));
        lTLeftPanel.setPreferredSize(new java.awt.Dimension(218, 525));
		GroupLayout lTLeftPanelLayout = new GroupLayout(lTLeftPanel);
		lTLeftPanelLayout.setHorizontalGroup(
			lTLeftPanelLayout.createParallelGroup(Alignment.LEADING)
				.addGroup(lTLeftPanelLayout.createSequentialGroup()
					.addContainerGap()
					.addGroup(lTLeftPanelLayout.createParallelGroup(Alignment.LEADING)
						.addComponent(localUpdateButt, GroupLayout.PREFERRED_SIZE, 79, GroupLayout.PREFERRED_SIZE)
						.addComponent(localCityName)
						.addComponent(lastUpdateTime)
						.addComponent(localTemp)
						.addComponent(lastUpdate))
					.addContainerGap(71, Short.MAX_VALUE))
		);
		lTLeftPanelLayout.setVerticalGroup(
			lTLeftPanelLayout.createParallelGroup(Alignment.LEADING)
				.addGroup(lTLeftPanelLayout.createSequentialGroup()
					.addGap(12)
					.addComponent(localCityName)
					.addPreferredGap(ComponentPlacement.RELATED)
					.addComponent(localTemp)
					.addPreferredGap(ComponentPlacement.RELATED)
					.addComponent(lastUpdateTime)
					.addPreferredGap(ComponentPlacement.RELATED)
					.addComponent(lastUpdate)
					.addGap(18)
					.addComponent(localUpdateButt, GroupLayout.PREFERRED_SIZE, 39, GroupLayout.PREFERRED_SIZE)
					.addContainerGap(335, Short.MAX_VALUE))
		);
		lTLeftPanel.setLayout(lTLeftPanelLayout);
		// end of left panel //

		// mid panel //
		lTMidPanel.setBorder(new SoftBevelBorder(BevelBorder.RAISED));
		lTMidPanel.setPreferredSize(new java.awt.Dimension(540, 525));
		
		midInside.setBorder(new SoftBevelBorder(BevelBorder.RAISED));
		midInside.setPreferredSize(new Dimension(520, 820));

		// day 0
        day0.setBackground(new java.awt.Color(175, 210, 250));
        day0.setBorder(new javax.swing.border.MatteBorder(null));
        day0.setPreferredSize(new java.awt.Dimension(510, 130));

        day0_date.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        day0_date.setText("Today: " + i.getDate());

        day0_temp.setText("Current Temperature: " + current.getTemperature(unit));

        day0_icon = new JLabel(new ImageIcon(current.getIcon()));

        day0_minTemp.setText("Min Temp for the day: " + current.getMinTemp(unit));

        day0_maxTemp.setText("<html>Max Temp for the day: " + current.getMaxTemp(unit) + "<br><br>Sky Condition: <html>" + i.getSky());

       // day0_sky.setText("Sky Condition: " + current.getSky());
        
		GroupLayout d0Layout = new GroupLayout(day0);
		day0.setLayout(d0Layout);
		d0Layout.setHorizontalGroup(d0Layout
			.createParallelGroup(GroupLayout.Alignment.LEADING)
			.addGroup(d0Layout.createSequentialGroup()
			.addContainerGap()
			.addGroup(d0Layout.createParallelGroup(GroupLayout.Alignment.LEADING)
				.addGroup(d0Layout.createSequentialGroup()
					.addGroup(d0Layout.createParallelGroup(GroupLayout.Alignment.LEADING)
						.addComponent(day0_minTemp)
						.addComponent(day0_maxTemp))
						.addPreferredGap(LayoutStyle.ComponentPlacement.RELATED,GroupLayout.DEFAULT_SIZE,Short.MAX_VALUE)
						.addComponent(day0_icon)
						.addGap(71, 71,71))
						.addGroup(d0Layout.createSequentialGroup()
						.addComponent(day0_temp)
						.addContainerGap(GroupLayout.DEFAULT_SIZE,Short.MAX_VALUE))
						.addGroup(d0Layout.createSequentialGroup()
						.addComponent(day0_date)
						.addGap(0,0,Short.MAX_VALUE)))));
		d0Layout.setVerticalGroup(d0Layout
				.createParallelGroup(GroupLayout.Alignment.LEADING)
				.addGroup(d0Layout.createSequentialGroup()
					.addGroup(d0Layout.createParallelGroup(GroupLayout.Alignment.LEADING)
					.addGroup(d0Layout.createSequentialGroup()
						.addGap(52, 52,52)
						.addComponent(day0_icon))
							.addGroup(d0Layout.createSequentialGroup()
								.addContainerGap()
								.addComponent(day0_date)
								.addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
								.addComponent(day0_temp)
								.addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
								.addComponent(day0_minTemp)
								.addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
								.addComponent(day0_maxTemp)
								.addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)))
								.addGap(0, 41, Short.MAX_VALUE)));
		// end of mid panel //

		// day 1
		i = daily[2];
        day1.setBackground(new java.awt.Color(210, 229, 243));
        day1.setBorder(new javax.swing.border.MatteBorder(null));
        day1.setPreferredSize(new java.awt.Dimension(519, 130));

        day1_date.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        day1_date.setText("Date: " + i.getDate());

        day1_temp.setText("Temperature: " + i.getTemperature(unit));

        day1_icon = new JLabel(new ImageIcon(i.getIcon()));

        day1_minTemp.setText("Min Temp for the day: " + i.getMinTemp(unit));

        day1_maxTemp.setText("<html>Max Temp for the day: " + current.getMaxTemp(unit) + "<br><br>Sky Condition: <html>" + i.getSky());
        
        GroupLayout d1Layout = new GroupLayout(day1);
		day1.setLayout(d1Layout);
		d1Layout.setHorizontalGroup(d1Layout
				.createParallelGroup(GroupLayout.Alignment.LEADING)
				.addGroup(
						d1Layout.createSequentialGroup()
								.addContainerGap()
								.addGroup(
										d1Layout.createParallelGroup(
												GroupLayout.Alignment.LEADING)
												.addGroup(
														d1Layout.createSequentialGroup()
																.addGroup(
																		d1Layout.createParallelGroup(
																				GroupLayout.Alignment.LEADING)
																				.addComponent(
																						day1_minTemp)
																				.addComponent(
																						day1_maxTemp))
																.addPreferredGap(
																		LayoutStyle.ComponentPlacement.RELATED,
																		GroupLayout.DEFAULT_SIZE,
																		Short.MAX_VALUE)
																.addComponent(
																		day1_icon)
																.addGap(71, 71,
																		71))
												.addGroup(
														d1Layout.createSequentialGroup()
																.addComponent(
																		day1_temp)
																.addContainerGap(
																		GroupLayout.DEFAULT_SIZE,
																		Short.MAX_VALUE))
												.addGroup(
														d1Layout.createSequentialGroup()
																.addComponent(
																		day1_date)
																.addGap(0,
																		0,
																		Short.MAX_VALUE)))));
		d1Layout.setVerticalGroup(d1Layout
				.createParallelGroup(GroupLayout.Alignment.LEADING)
				.addGroup(
						d1Layout.createSequentialGroup()
								.addGroup(
										d1Layout.createParallelGroup(
												GroupLayout.Alignment.LEADING)
												.addGroup(
														d1Layout.createSequentialGroup()
																.addGap(52, 52,
																		52)
																.addComponent(
																		day1_icon))
												.addGroup(
														d1Layout.createSequentialGroup()
																.addContainerGap()
																.addComponent(
																		day1_date)
																.addPreferredGap(
																		LayoutStyle.ComponentPlacement.RELATED)
																.addComponent(
																		day1_temp)
																.addPreferredGap(
																		LayoutStyle.ComponentPlacement.RELATED)
																.addComponent(
																		day1_minTemp)
																.addPreferredGap(
																		LayoutStyle.ComponentPlacement.RELATED)
																.addComponent(
																		day1_maxTemp)))
								.addGap(0, 41, Short.MAX_VALUE)));

		// end of day 1

		// day 2
		i = daily[3];
		day2.setBackground(new java.awt.Color(175, 210, 250));
		day2.setBorder(new javax.swing.border.MatteBorder(null));
		day2.setPreferredSize(new java.awt.Dimension(519, 130));

		day2_date.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
		day2_date.setText("Date: " + i.getDate());

		day2_temp.setText("Temperature: " + i.getTemperature(unit));

		day2_icon = new JLabel(new ImageIcon(i.getIcon()));

		day2_minTemp.setText("Min Temp for the day: " + i.getMinTemp(unit));

		day2_maxTemp.setText("<html>Max Temp for the day: " + current.getMaxTemp(unit) + "<br><br>Sky Condition: <html>" + i.getSky());
		
		GroupLayout d2Layout = new GroupLayout(day2);
		day2.setLayout(d2Layout);
		d2Layout.setHorizontalGroup(d2Layout
				.createParallelGroup(GroupLayout.Alignment.LEADING)
				.addGroup(
						d2Layout.createSequentialGroup()
								.addContainerGap()
								.addGroup(
										d2Layout.createParallelGroup(
												GroupLayout.Alignment.LEADING)
												.addGroup(
														d2Layout.createSequentialGroup()
																.addGroup(
																		d2Layout.createParallelGroup(
																				GroupLayout.Alignment.LEADING)
																				.addComponent(
																						day2_minTemp)
																				.addComponent(
																						day2_maxTemp))
																.addPreferredGap(
																		LayoutStyle.ComponentPlacement.RELATED,
																		GroupLayout.DEFAULT_SIZE,
																		Short.MAX_VALUE)
																.addComponent(
																		day2_icon)
																.addGap(71, 71,
																		71))
												.addGroup(
														d2Layout.createSequentialGroup()
																.addComponent(
																		day2_temp)
																.addContainerGap(
																		GroupLayout.DEFAULT_SIZE,
																		Short.MAX_VALUE))
												.addGroup(
														d2Layout.createSequentialGroup()
																.addComponent(
																		day2_date)
																.addGap(0,
																		0,
																		Short.MAX_VALUE)))));
		d2Layout.setVerticalGroup(d2Layout
				.createParallelGroup(GroupLayout.Alignment.LEADING)
				.addGroup(
						d2Layout.createSequentialGroup()
								.addGroup(
										d2Layout.createParallelGroup(
												GroupLayout.Alignment.LEADING)
												.addGroup(
														d2Layout.createSequentialGroup()
																.addGap(52, 52,
																		52)
																.addComponent(
																		day2_icon))
												.addGroup(
														d2Layout.createSequentialGroup()
																.addContainerGap()
																.addComponent(
																		day2_date)
																.addPreferredGap(
																		LayoutStyle.ComponentPlacement.RELATED)
																.addComponent(
																		day2_temp)
																.addPreferredGap(
																		LayoutStyle.ComponentPlacement.RELATED)
																.addComponent(
																		day2_minTemp)
																.addPreferredGap(
																		LayoutStyle.ComponentPlacement.RELATED)
																.addComponent(
																		day2_maxTemp)))
								.addGap(0, 41, Short.MAX_VALUE)));
		// end of day 2

		// day 3
		i = daily[4];

		day3.setBackground(new java.awt.Color(210, 229, 243));
		day3.setBorder(new javax.swing.border.MatteBorder(null));
		day3.setPreferredSize(new java.awt.Dimension(519, 130));

		day3_date.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
		day3_date.setText("Date: " + i.getDate());

		day3_temp.setText("Temperature: " + i.getTemperature(unit));

		day3_icon = new JLabel(new ImageIcon(i.getIcon()));

		day3_minTemp.setText("Min Temp for the day: " + i.getMinTemp(unit));

		day3_maxTemp.setText("<html>Max Temp for the day: " + current.getMaxTemp(unit) + "<br><br>Sky Condition: <html>" + i.getSky());

		GroupLayout d3Layout = new GroupLayout(day3);
		day3.setLayout(d3Layout);
		d3Layout.setHorizontalGroup(d3Layout
				.createParallelGroup(GroupLayout.Alignment.LEADING)
				.addGroup(
						d3Layout.createSequentialGroup()
								.addContainerGap()
								.addGroup(
										d3Layout.createParallelGroup(
												GroupLayout.Alignment.LEADING)
												.addGroup(
														GroupLayout.Alignment.TRAILING,
														d3Layout.createSequentialGroup()
																.addGroup(
																		d3Layout.createParallelGroup(
																				GroupLayout.Alignment.LEADING)
																				.addComponent(
																						day3_minTemp)
																				.addComponent(
																						day3_maxTemp))
																.addPreferredGap(
																		LayoutStyle.ComponentPlacement.RELATED,
																		GroupLayout.DEFAULT_SIZE,
																		Short.MAX_VALUE)
																.addComponent(
																		day3_icon)
																.addGap(71, 71,
																		71))
												.addGroup(
														d3Layout.createSequentialGroup()
																.addGroup(
																		d3Layout.createParallelGroup(
																				GroupLayout.Alignment.LEADING)
																				.addComponent(
																						day3_date)
																				.addComponent(
																						day3_temp))
																.addContainerGap(
																		GroupLayout.DEFAULT_SIZE,
																		Short.MAX_VALUE)))));
		d3Layout.setVerticalGroup(d3Layout
				.createParallelGroup(GroupLayout.Alignment.LEADING)
				.addGroup(
						d3Layout.createSequentialGroup()
								.addContainerGap()
								.addComponent(day3_date)
								.addPreferredGap(
										LayoutStyle.ComponentPlacement.RELATED)
								.addComponent(day3_temp)
								.addGroup(
										d3Layout.createParallelGroup(
												GroupLayout.Alignment.LEADING)
												.addGroup(
														d3Layout.createSequentialGroup()
																.addGap(14, 14,
																		14)
																.addComponent(
																		day3_icon))
												.addGroup(
														d3Layout.createSequentialGroup()
																.addPreferredGap(
																		LayoutStyle.ComponentPlacement.RELATED)
																.addComponent(
																		day3_minTemp)
																.addPreferredGap(
																		LayoutStyle.ComponentPlacement.RELATED)
																.addComponent(
																		day3_maxTemp)))
								.addGap(0, 35, Short.MAX_VALUE)));
		// end of day 3

		// day 4
		i = daily[5];

        day4.setBackground(new java.awt.Color(175, 210, 250));
        day4.setBorder(new javax.swing.border.MatteBorder(null));
        day4.setPreferredSize(new java.awt.Dimension(519, 130));

        day4_date.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        day4_date.setText("Date: " + i.getDate());

        day4_temp.setText("Temperature: " + i.getTemperature(unit));

        day4_icon = new JLabel(new ImageIcon(i.getIcon()));

        day4_minTemp.setText("Min Temp for the day: " + i.getMinTemp(unit));

        day4_maxTemp.setText("<html>Max Temp for the day: " + current.getMaxTemp(unit) + "<br><br>Sky Condition: <html>" + i.getSky());

		GroupLayout d4Layout = new GroupLayout(day4);
		day4.setLayout(d4Layout);
		d4Layout.setHorizontalGroup(d4Layout
				.createParallelGroup(GroupLayout.Alignment.LEADING)
				.addGroup(
						d4Layout.createSequentialGroup()
								.addContainerGap()
								.addGroup(
										d4Layout.createParallelGroup(
												GroupLayout.Alignment.LEADING)
												.addGroup(
														GroupLayout.Alignment.TRAILING,
														d4Layout.createSequentialGroup()
																.addGroup(
																		d4Layout.createParallelGroup(
																				GroupLayout.Alignment.LEADING)
																				.addComponent(
																						day4_minTemp)
																				.addComponent(
																						day4_maxTemp))
																.addPreferredGap(
																		LayoutStyle.ComponentPlacement.RELATED,
																		GroupLayout.DEFAULT_SIZE,
																		Short.MAX_VALUE)
																.addComponent(
																		day4_icon)
																.addGap(71, 71,
																		71))
												.addGroup(
														d4Layout.createSequentialGroup()
																.addGroup(
																		d4Layout.createParallelGroup(
																				GroupLayout.Alignment.LEADING)
																				.addComponent(
																						day4_date)
																				.addComponent(
																						day4_temp))
																.addContainerGap(
																		GroupLayout.DEFAULT_SIZE,
																		Short.MAX_VALUE)))));
		d4Layout.setVerticalGroup(d4Layout
				.createParallelGroup(GroupLayout.Alignment.LEADING)
				.addGroup(
						d4Layout.createSequentialGroup()
								.addContainerGap()
								.addComponent(day4_date)
								.addPreferredGap(
										LayoutStyle.ComponentPlacement.RELATED)
								.addComponent(day4_temp)
								.addGroup(
										d4Layout.createParallelGroup(
												GroupLayout.Alignment.LEADING)
												.addGroup(
														d4Layout.createSequentialGroup()
																.addGap(14, 14,
																		14)
																.addComponent(
																		day4_icon))
												.addGroup(
														d4Layout.createSequentialGroup()
																.addPreferredGap(
																		LayoutStyle.ComponentPlacement.RELATED)
																.addComponent(
																		day4_minTemp)
																.addPreferredGap(
																		LayoutStyle.ComponentPlacement.RELATED)
																.addComponent(
																		day4_maxTemp)))
								.addGap(0, 35, Short.MAX_VALUE)));
		// end of day 4

		// day 5
		i = daily[6];
        day5.setBackground(new java.awt.Color(210, 229, 243));
        day5.setBorder(new javax.swing.border.MatteBorder(null));
        day5.setPreferredSize(new java.awt.Dimension(519, 130));

        day5_date.setFont(new java.awt.Font("Lucida Grande", 1, 14)); // NOI18N
        day5_date.setText("Date: " + i.getDate());

        day5_temp.setText("Temperature: " + i.getTemperature(unit));

        day5_icon = new JLabel(new ImageIcon(i.getIcon()));

        day5_minTemp.setText("Min Temp for the day: " + i.getMinTemp(unit));

        day5_maxTemp.setText("<html>Max Temp for the day: " + current.getMaxTemp(unit) + "<br><br>Sky Condition: <html>" + i.getSky());

		GroupLayout d5Layout = new GroupLayout(day5);
		day5.setLayout(d5Layout);
		d5Layout.setHorizontalGroup(d5Layout
				.createParallelGroup(GroupLayout.Alignment.LEADING)
				.addGroup(
						d5Layout.createSequentialGroup()
								.addContainerGap()
								.addGroup(
										d5Layout.createParallelGroup(
												GroupLayout.Alignment.LEADING)
												.addGroup(
														GroupLayout.Alignment.TRAILING,
														d5Layout.createSequentialGroup()
																.addGroup(
																		d5Layout.createParallelGroup(
																				GroupLayout.Alignment.LEADING)
																				.addComponent(
																						day5_minTemp)
																				.addComponent(
																						day5_maxTemp))
																.addPreferredGap(
																		LayoutStyle.ComponentPlacement.RELATED,
																		GroupLayout.DEFAULT_SIZE,
																		Short.MAX_VALUE)
																.addComponent(
																		day5_icon)
																.addGap(71, 71,
																		71))
												.addGroup(
														d5Layout.createSequentialGroup()
																.addGroup(
																		d5Layout.createParallelGroup(
																				GroupLayout.Alignment.LEADING)
																				.addComponent(
																						day5_date)
																				.addComponent(
																						day5_temp))
																.addContainerGap(
																		GroupLayout.DEFAULT_SIZE,
																		Short.MAX_VALUE)))));
		d5Layout.setVerticalGroup(d5Layout
				.createParallelGroup(GroupLayout.Alignment.LEADING)
				.addGroup(
						d5Layout.createSequentialGroup()
								.addContainerGap()
								.addComponent(day5_date)
								.addPreferredGap(
										LayoutStyle.ComponentPlacement.RELATED)
								.addComponent(day5_temp)
								.addGroup(
										d5Layout.createParallelGroup(
												GroupLayout.Alignment.LEADING)
												.addGroup(
														d5Layout.createSequentialGroup()
																.addGap(14, 14,
																		14)
																.addComponent(
																		day5_icon))
												.addGroup(
														d5Layout.createSequentialGroup()
																.addPreferredGap(
																		LayoutStyle.ComponentPlacement.RELATED)
																.addComponent(
																		day5_minTemp)
																.addPreferredGap(
																		LayoutStyle.ComponentPlacement.RELATED)
																.addComponent(
																		day5_maxTemp)))
								.addGap(0, 35, Short.MAX_VALUE)));
		// end of day 5

		GroupLayout midInsideLayout = new GroupLayout(midInside);
		midInside.setLayout(midInsideLayout);
		midInsideLayout.setHorizontalGroup(midInsideLayout.createParallelGroup(
				GroupLayout.Alignment.LEADING).addGroup(
				midInsideLayout
						.createSequentialGroup()
						.addGroup(
								midInsideLayout
										.createParallelGroup(
												GroupLayout.Alignment.TRAILING,
												false)

										.addComponent(day5,
												GroupLayout.Alignment.LEADING,
												GroupLayout.DEFAULT_SIZE,
												GroupLayout.DEFAULT_SIZE,
												Short.MAX_VALUE)

										.addComponent(day4,
												GroupLayout.Alignment.LEADING,
												GroupLayout.DEFAULT_SIZE,
												GroupLayout.DEFAULT_SIZE,
												Short.MAX_VALUE)
										.addComponent(day3,
												GroupLayout.Alignment.LEADING,
												GroupLayout.DEFAULT_SIZE,
												GroupLayout.DEFAULT_SIZE,
												Short.MAX_VALUE)
										.addComponent(day2,
												GroupLayout.Alignment.LEADING,
												GroupLayout.DEFAULT_SIZE,
												GroupLayout.DEFAULT_SIZE,
												Short.MAX_VALUE)
										.addComponent(day1,
												GroupLayout.Alignment.LEADING,
												GroupLayout.DEFAULT_SIZE,
												GroupLayout.DEFAULT_SIZE,
												Short.MAX_VALUE)
										.addComponent(day0,
												GroupLayout.Alignment.LEADING,
												GroupLayout.DEFAULT_SIZE,
												GroupLayout.DEFAULT_SIZE,
												Short.MAX_VALUE))
						.addGap(0, 4, Short.MAX_VALUE)));
		midInsideLayout
				.setVerticalGroup(midInsideLayout
						.createParallelGroup(GroupLayout.Alignment.LEADING)
						.addGroup(
								midInsideLayout
										.createSequentialGroup()
										.addComponent(day0,
												GroupLayout.PREFERRED_SIZE,
												GroupLayout.DEFAULT_SIZE,
												GroupLayout.PREFERRED_SIZE)
										.addPreferredGap(
												LayoutStyle.ComponentPlacement.RELATED)
										.addComponent(day1,
												GroupLayout.PREFERRED_SIZE,
												GroupLayout.DEFAULT_SIZE,
												GroupLayout.PREFERRED_SIZE)
										.addPreferredGap(
												LayoutStyle.ComponentPlacement.RELATED)
										.addComponent(day2,
												GroupLayout.PREFERRED_SIZE,
												GroupLayout.DEFAULT_SIZE,
												GroupLayout.PREFERRED_SIZE)
										.addPreferredGap(
												LayoutStyle.ComponentPlacement.RELATED)
										.addComponent(day3,
												GroupLayout.PREFERRED_SIZE,
												GroupLayout.DEFAULT_SIZE,
												GroupLayout.PREFERRED_SIZE)
										.addPreferredGap(
												LayoutStyle.ComponentPlacement.RELATED)
										.addComponent(day4,
												GroupLayout.PREFERRED_SIZE,
												GroupLayout.DEFAULT_SIZE,
												GroupLayout.PREFERRED_SIZE)
										.addPreferredGap(
												LayoutStyle.ComponentPlacement.RELATED)
										.addComponent(day5,
												GroupLayout.PREFERRED_SIZE,
												GroupLayout.DEFAULT_SIZE,
												GroupLayout.PREFERRED_SIZE)
										.addPreferredGap(
												LayoutStyle.ComponentPlacement.RELATED,
												GroupLayout.DEFAULT_SIZE,
												Short.MAX_VALUE)
										.addGap(359, 359, 359)));

		lTMidScroll.setViewportView(midInside);
		lTMidScroll.setSize(525,820);
		
		GroupLayout lTMidPanelLayout = new GroupLayout(lTMidPanel);
		lTMidPanel.setLayout(lTMidPanelLayout);
		lTMidPanelLayout.setHorizontalGroup(lTMidPanelLayout
				.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(
						lTMidPanelLayout
								.createSequentialGroup()
								.addComponent(lTMidScroll,
										GroupLayout.DEFAULT_SIZE, 538,
										Short.MAX_VALUE).addContainerGap()));
		lTMidPanelLayout.setVerticalGroup(lTMidPanelLayout.createParallelGroup(
				GroupLayout.Alignment.LEADING).addComponent(lTMidScroll,
				GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE));

		/**
		 * right panel
		 */
		clock.setFont(new java.awt.Font("Lucida Grande", 1, 13));	 // font
		clock.setText("clock");
		date.setFont(new java.awt.Font("Lucida Grande", 1, 13));	 // font
		date.setText("<html>Today:<br><html> " + current.getDate());
		
		lTRightPanel.setBorder(new SoftBevelBorder(BevelBorder.RAISED));
		GroupLayout lTRightPanelLayout = new GroupLayout(lTRightPanel);
		lTRightPanel.setLayout(lTRightPanelLayout);
		lTRightPanelLayout.setHorizontalGroup(
				lTRightPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
				.addGroup(lTRightPanelLayout.createSequentialGroup()
				.addGap(17,17,17)
				.addGroup(lTRightPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
						.addComponent(clock)
						.addComponent(date))
				.addGap(0,500, Short.MAX_VALUE)));
		
		lTRightPanelLayout.setVerticalGroup(lTRightPanelLayout
				.createParallelGroup(GroupLayout.Alignment.LEADING)
				.addGroup(lTRightPanelLayout.createSequentialGroup()
						.addGap(63,63,63)
						.addComponent(clock)
						.addGap(15,15,15)
						.addComponent(date))
						.addGap(0,500, Short.MAX_VALUE));

		GroupLayout longPanelLayout = new GroupLayout(longPanel);
		longPanel.setLayout(longPanelLayout);
		longPanelLayout.setHorizontalGroup(longPanelLayout.createParallelGroup(
				GroupLayout.Alignment.LEADING)
				.addGroup(
						GroupLayout.Alignment.TRAILING,
						longPanelLayout
								.createSequentialGroup()
								.addComponent(lTLeftPanel,
										GroupLayout.PREFERRED_SIZE,
										GroupLayout.DEFAULT_SIZE,
										GroupLayout.PREFERRED_SIZE)
								.addPreferredGap(
										LayoutStyle.ComponentPlacement.RELATED)
								.addComponent(lTMidPanel,
										GroupLayout.PREFERRED_SIZE,
										GroupLayout.DEFAULT_SIZE,
										GroupLayout.PREFERRED_SIZE)
								.addPreferredGap(
										LayoutStyle.ComponentPlacement.RELATED)
								.addComponent(lTRightPanel,
										GroupLayout.PREFERRED_SIZE,
										GroupLayout.DEFAULT_SIZE,
										GroupLayout.PREFERRED_SIZE)
								.addContainerGap(GroupLayout.DEFAULT_SIZE,
										Short.MAX_VALUE)));
		longPanelLayout.setVerticalGroup(longPanelLayout
				.createParallelGroup(GroupLayout.Alignment.LEADING)
				.addComponent(lTMidPanel, GroupLayout.DEFAULT_SIZE,
						GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
				.addComponent(lTLeftPanel, GroupLayout.DEFAULT_SIZE,
						GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
				.addComponent(lTRightPanel, GroupLayout.DEFAULT_SIZE,
						GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE));

		setContentPane(longPanel);

	}// </editor-fold>

	private void updateButtonActionPerformed(ActionEvent evt) {
		this.unit = Settings.instance.getUnit();
		current = new WeatherInfo(Settings.instance.getLocation()); 
		lCast = new LongTermForecast(Settings.instance.getLocation());
		daily = lCast.getDaily();
		
		localCityName.setText(current.getLocation());
		lastUpdateTime.setText("<html>System Last Updated:<br><html> " + current.getUpdateTime());
		lastUpdate.setText("<html>User Last Update: <br><html>" + current.getCurrentTime());
		localTemp.setText("Currently: " + current.getTemperature(unit));
		
		i = daily[1];
		day0_date.setText("Today: " + i.getDate());
		day0_temp.setText("Current Temperature: " + current.getTemperature(unit));
		day0_icon = new JLabel(new ImageIcon(current.getIcon()));
		day0_minTemp.setText("Min Temp for the day: " + current.getMinTemp(unit));
		day0_maxTemp.setText("<html>Max Temp for the day: " + current.getMaxTemp(unit) + "<br><br>Sky Condition: <html>" + i.getSky());

		i = daily[2];
		day1_date.setText("Date: " + i.getDate());
		day1_temp.setText("Temperature: " + i.getTemperature(unit));
		day1_icon = new JLabel(new ImageIcon(i.getIcon()));
		day1_minTemp.setText("Min Temp for the day: " + i.getMinTemp(unit));
		day1_maxTemp.setText("<html>Max Temp for the day: " + current.getMaxTemp(unit) + "<br><br>Sky Condition: <html>" + i.getSky());

		i = daily[3];
		day2_date.setText("Date: " + i.getDate());
		day2_temp.setText("Temperature: " + i.getTemperature(unit));
		day2_icon = new JLabel(new ImageIcon(i.getIcon()));
		day2_minTemp.setText("Min Temp for the day: " + i.getMinTemp(unit));
		day2_maxTemp.setText("<html>Max Temp for the day: " + current.getMaxTemp(unit) + "<br><br>Sky Condition: <html>" + i.getSky());

		i = daily[4];
		day3_date.setText("Date: " + i.getDate());
		day3_temp.setText("Temperature: " + i.getTemperature(unit));
		day3_icon = new JLabel(new ImageIcon(i.getIcon()));
		day3_minTemp.setText("Min Temp for the day: " + i.getMinTemp(unit));
		day3_maxTemp.setText("<html>Max Temp for the day: " + current.getMaxTemp(unit) + "<br><br>Sky Condition: <html>" + i.getSky());

		i = daily[5];
		day4_date.setText("Date: " + i.getDate());
		day4_temp.setText("Temperature: " + i.getTemperature(unit));
		day4_icon = new JLabel(new ImageIcon(i.getIcon()));
		day4_minTemp.setText("Min Temp for the day: " + i.getMinTemp(unit));
		day4_maxTemp.setText("<html>Max Temp for the day: " + current.getMaxTemp(unit) + "<br><br>Sky Condition: <html>" + i.getSky());

		i = daily[6];
		day5_date.setText("Date: " + i.getDate());
		day5_temp.setText("Temperature: " + i.getTemperature(unit));
		day5_icon = new JLabel(new ImageIcon(i.getIcon()));
		day5_minTemp.setText("Min Temp for the day: " + i.getMinTemp(unit));
		day5_maxTemp.setText("<html>Max Temp for the day: " + current.getMaxTemp(unit) + "<br><br>Sky Condition: <html>" + i.getSky());
	}


	private void updateButtonMouseClicked(MouseEvent evt) {
		// TODO add your handling code here:
	}

	private void updateButtonStateChanged(ChangeEvent evt) {
		// TODO add your handling code here:
	}
}