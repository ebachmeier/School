import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JFrame;

import java.util.Calendar;
import java.util.GregorianCalendar;
import javax.swing.GroupLayout.Alignment;
import javax.swing.GroupLayout;
import javax.swing.LayoutStyle.ComponentPlacement;
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * 
 * @author menghanyu
 */
public class ShortTermInterface extends JFrame {

	private static final long serialVersionUID = 1L;
	
	/**
	 * creating local variables
	 */
	private JLabel clock;
    private JScrollPane jScrollPane1;
    private JLabel lastUpdateTime;
    private JLabel localCityName;
    private JLabel localTemp;
    private JPanel midInside;
    private JPanel sTLeftPanel;
    private JPanel sTRightPanel;
    private JPanel sTmidPanel;
    private JLabel sunrise;
    private JLabel sunset;
    private JLabel minTemp;
    private JLabel maxTemp;
    private JPanel time0;
    private JLabel time0_icon;
    private JLabel time0_temp;
    private JLabel time0_time;
    private JPanel time3;
    private JLabel time3_icon;
    private JLabel time3_temp;
    private JLabel time3_time;
    private JPanel time6;
    private JLabel time6_icon;
    private JLabel time6_temp;
    private JLabel time6_time;
    private JPanel time9;
    private JLabel time9_icon;
    private JLabel time9_temp;
    private JLabel time9_time;
    private JPanel time12;
    private JLabel time12_icon;
    private JLabel time12_temp;
    private JLabel time12_time;
    private JPanel time15;
    private JLabel time15_icon;
    private JLabel time15_temp;
    private JLabel time15_time;
    private JPanel time18;
    private JLabel time18_icon;
    private JLabel time18_temp;
    private JLabel time18_time;
    private JPanel time21;
    private JLabel time21_icon;
    private JLabel time21_temp;
    private JLabel time21_time;
    private JPanel time24;
    private JLabel time24_time;
    private JLabel time24_temp;
    private JLabel time24_icon;
    private JButton updateButton;
	//private String[] cities;
	private String unit;
	//private int city;
	
	private JLabel lastUpdate;
	private int timeRun = 0;
	private int check;
	
	WeatherInfo current;
	ShortTermForecast sCast;
	WeatherInfo[] hourly;
	WeatherInfo i;

	/**
	 * Creates new form ShortTermInterface
	 */
	public ShortTermInterface() {
			
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
	 * body of ShortTermInterface
	 */
	private void initComponents() {

        sTLeftPanel = new javax.swing.JPanel();
        updateButton = new javax.swing.JButton();
        localCityName = new javax.swing.JLabel();
        localTemp = new javax.swing.JLabel();
        lastUpdateTime = new javax.swing.JLabel();
        sTmidPanel = new javax.swing.JPanel();
        jScrollPane1 = new javax.swing.JScrollPane();
        midInside = new javax.swing.JPanel();
        time0 = new javax.swing.JPanel();
        time0_time = new javax.swing.JLabel();
        time0_temp = new javax.swing.JLabel();
        time0_icon = new javax.swing.JLabel();
        time3 = new javax.swing.JPanel();
        time3_time = new javax.swing.JLabel();
        time3_temp = new javax.swing.JLabel();
        time3_icon = new javax.swing.JLabel();
        time6 = new javax.swing.JPanel();
        time6_time = new javax.swing.JLabel();
        time6_temp = new javax.swing.JLabel();
        time6_icon = new javax.swing.JLabel();
        time9 = new javax.swing.JPanel();
        time9_time = new javax.swing.JLabel();
        time9_temp = new javax.swing.JLabel();
        time9_icon = new javax.swing.JLabel();
        time12 = new javax.swing.JPanel();
        time12_time = new javax.swing.JLabel();
        time12_temp = new javax.swing.JLabel();
        time12_icon = new javax.swing.JLabel();
        time15 = new javax.swing.JPanel();
        time15_time = new javax.swing.JLabel();
        time15_temp = new javax.swing.JLabel();
        time15_icon = new javax.swing.JLabel();
        time18 = new javax.swing.JPanel();
        time18_time = new javax.swing.JLabel();
        time18_temp = new javax.swing.JLabel();
        time18_icon = new javax.swing.JLabel();
        time21 = new javax.swing.JPanel();
        time21_time = new javax.swing.JLabel();
        time21_temp = new javax.swing.JLabel();
        time21_icon = new javax.swing.JLabel();
        time24 = new javax.swing.JPanel();
        time24_time = new javax.swing.JLabel();
        time24_temp = new javax.swing.JLabel();
        time24_icon = new javax.swing.JLabel();
        sTRightPanel = new javax.swing.JPanel();
        clock = new javax.swing.JLabel();
        sunrise = new javax.swing.JLabel();
        sunset = new javax.swing.JLabel();
        minTemp = new javax.swing.JLabel();
        maxTemp = new javax.swing.JLabel();
        
        lastUpdate = new javax.swing.JLabel();
         
        /**
         * set left panel border
         */
        sTLeftPanel.setBorder(new javax.swing.border.SoftBevelBorder(javax.swing.border.BevelBorder.RAISED));
        sTLeftPanel.setToolTipText("");			// I believe this line is useless

        /**
         * update button function
         */
        updateButton.setText("Update");
        updateButton.setFont(new java.awt.Font("Lucida Grande", 1, 16));
        
        updateButton.addChangeListener(new javax.swing.event.ChangeListener() {
            public void stateChanged(javax.swing.event.ChangeEvent evt) {
                updateButtonStateChanged(evt);
            }
        });
        updateButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                updateButtonMouseClicked(evt);
            }
        });
        updateButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                updateButtonActionPerformed(evt);
            }
        });
        
        /**
         * Insert info for weather cast
         */
        // Add for Singleton
        this.unit = Settings.instance.getUnit();
        current = new WeatherInfo(Settings.instance.getLocation());
        // WeatherInfo current = new WeatherInfo(cities[city]);
        
        // Add for Singleton
    	sCast = new ShortTermForecast(Settings.instance.getLocation());
    	// ShortTermForecast sCast = new ShortTermForecast(cities[city]);
    	
    	hourly = sCast.getHourly();

    	i = hourly[1];
    	
		/**
		 * set city, temperature, last update time
		 */
    	localCityName.setSize(218, 525);
    	localCityName.setFont(new java.awt.Font("Lucida Grande", 1, 14));
        localCityName.setText(current.getLocation());
        localTemp.setText("Currently: " + current.getTemperature(unit));
        lastUpdateTime.setText("<html>System Last Updated:<br><html>" + current.getUpdateTime());
        lastUpdate.setText("<html>User Last Update: <br><html>" + current.getCurrentTime());
        
        /**
         * left panel properties
         */
        sTLeftPanel.setMaximumSize(new java.awt.Dimension(218, 525));
        sTLeftPanel.setMinimumSize(new java.awt.Dimension(218, 525));
        sTLeftPanel.setPreferredSize(new java.awt.Dimension(218, 525));
        javax.swing.GroupLayout sTLeftPanelLayout = new javax.swing.GroupLayout(sTLeftPanel);
        sTLeftPanelLayout.setHorizontalGroup(
        	sTLeftPanelLayout.createParallelGroup(Alignment.LEADING)
        		.addGroup(sTLeftPanelLayout.createSequentialGroup()
        			.addContainerGap()
        			.addGroup(sTLeftPanelLayout.createParallelGroup(Alignment.LEADING)
        				.addComponent(updateButton, GroupLayout.PREFERRED_SIZE, 80, GroupLayout.PREFERRED_SIZE)
        				.addComponent(localCityName)
        				.addComponent(localTemp)
        				.addComponent(lastUpdateTime)
        				.addComponent(lastUpdate, GroupLayout.PREFERRED_SIZE, 152, GroupLayout.PREFERRED_SIZE))
        			.addContainerGap(54, Short.MAX_VALUE))
        );
        sTLeftPanelLayout.setVerticalGroup(
        	sTLeftPanelLayout.createParallelGroup(Alignment.LEADING)
        		.addGroup(sTLeftPanelLayout.createSequentialGroup()
        			.addGap(12)
        			.addComponent(localCityName)
        			.addPreferredGap(ComponentPlacement.RELATED)
        			.addComponent(localTemp)
        			.addPreferredGap(ComponentPlacement.RELATED)
        			.addComponent(lastUpdateTime)
        			.addPreferredGap(ComponentPlacement.RELATED)
        			.addComponent(lastUpdate)
        			.addGap(18)
        			.addComponent(updateButton, GroupLayout.PREFERRED_SIZE, 40, GroupLayout.PREFERRED_SIZE)
        			.addContainerGap(334, Short.MAX_VALUE))
        );
        sTLeftPanel.setLayout(sTLeftPanelLayout);

        /**
         * mid Panel border and size
         */
        sTmidPanel.setBorder(new javax.swing.border.SoftBevelBorder(javax.swing.border.BevelBorder.RAISED));
        sTmidPanel.setPreferredSize(new java.awt.Dimension(550, 525));

        
        /**
         * scrollPanel size
         */
        jScrollPane1.setPreferredSize(new java.awt.Dimension(525, 1195));
        jScrollPane1.setSize(new java.awt.Dimension(525, 1195));

        
        /**
         * midInside border and size
         */
        midInside.setBorder(new javax.swing.border.SoftBevelBorder(javax.swing.border.BevelBorder.RAISED));
        midInside.setPreferredSize(new java.awt.Dimension(510, 1195));

        
        /**
         * time +0, now, forecast
         */
        time0.setBackground(new java.awt.Color(175, 210, 250));
        time0.setBorder(new javax.swing.border.MatteBorder(null));
        time0.setPreferredSize(new java.awt.Dimension(515, 125));

        time0_time.setFont(new java.awt.Font("Lucida Grande", 1, 14));		//font
        time0_time.setText("<html><tr><html>" + i.getUpdateTime());

        time0_temp.setText(" Temperature: " + i.getTemperature(unit) + "                    Sky Condition: " + i.getSky());
        
        time0_icon = new JLabel(new ImageIcon(i.getIcon()));

        javax.swing.GroupLayout time0Layout = new javax.swing.GroupLayout(time0);
        time0.setLayout(time0Layout);
        time0Layout.setHorizontalGroup(
            time0Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(time0Layout.createSequentialGroup()
                .addGroup(time0Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(time0_time)
                    .addComponent(time0_temp))
                .addGap(0, 0, Short.MAX_VALUE))
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, time0Layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(time0_icon)
                .addGap(71, 71, 71))
        );
        time0Layout.setVerticalGroup(
            time0Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(time0Layout.createSequentialGroup()
                .addComponent(time0_time)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(time0_temp, javax.swing.GroupLayout.PREFERRED_SIZE, 16, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(14, 14, 14)
                .addComponent(time0_icon)
                .addGap(0, 55, Short.MAX_VALUE))
        );

        
        /**
         * +3 hours forecast
         */
        i = hourly[2];
        time3.setBackground(new java.awt.Color(210, 229, 243));
        time3.setBorder(new javax.swing.border.MatteBorder(null));
        time3.setPreferredSize(new java.awt.Dimension(515, 125));

        time3_time.setFont(new java.awt.Font("Lucida Grande", 1, 14));		//font
        time3_time.setText("<html><tr><html>" + i.getUpdateTime());
        time3_temp.setText(" Temperature: " + i.getTemperature(unit)+"                    Sky Condition: " + i.getSky());
        time3_icon = new JLabel(new ImageIcon(i.getIcon()));

        javax.swing.GroupLayout time3Layout = new javax.swing.GroupLayout(time3);
        time3.setLayout(time3Layout);
        time3Layout.setHorizontalGroup(
            time3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(time3Layout.createSequentialGroup()
                .addGroup(time3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(time3_time)
                    .addComponent(time3_temp))
                .addGap(0, 0, Short.MAX_VALUE))
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, time3Layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(time3_icon)
                .addGap(71, 71, 71))
        );
        time3Layout.setVerticalGroup(
            time3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(time3Layout.createSequentialGroup()
                .addComponent(time3_time)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(time3_temp)
                .addGap(14, 14, 14)
                .addComponent(time3_icon)
                .addGap(0, 55, Short.MAX_VALUE))
        );

        
        /**
         * +6 hours forecast
         */
        i = hourly[3];
        time6.setBackground(new java.awt.Color(175, 210, 250));
        time6.setBorder(new javax.swing.border.MatteBorder(null));
        time6.setPreferredSize(new java.awt.Dimension(515, 125));

        time6_time.setFont(new java.awt.Font("Lucida Grande", 1, 14));		//font
        time6_time.setText("<html><tr><html>" + i.getUpdateTime());

        time6_temp.setText(" Temperature: " + i.getTemperature(unit) + "                    Sky Condition: " + i.getSky());

        time6_icon = new JLabel(new ImageIcon(i.getIcon()));

        javax.swing.GroupLayout time6Layout = new javax.swing.GroupLayout(time6);
        time6.setLayout(time6Layout);
        time6Layout.setHorizontalGroup(
            time6Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(time6Layout.createSequentialGroup()
                .addGroup(time6Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(time6_time)
                    .addComponent(time6_temp))
                .addGap(0, 0, Short.MAX_VALUE))
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, time6Layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(time6_icon)
                .addGap(71, 71, 71))
        );
        time6Layout.setVerticalGroup(
            time6Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(time6Layout.createSequentialGroup()
                .addComponent(time6_time)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(time6_temp)
                .addGap(14, 14, 14)
                .addComponent(time6_icon)
                .addGap(0, 55, Short.MAX_VALUE))
        );
        
        
        /**
         * +9 hours forecast
         */
        i = hourly[4];
        time9.setBackground(new java.awt.Color(210, 229, 243));
        time9.setBorder(new javax.swing.border.MatteBorder(null));
        time9.setPreferredSize(new java.awt.Dimension(515, 125));

        time9_time.setFont(new java.awt.Font("Lucida Grande", 1, 14));		//font
        time9_time.setText("<html><tr><html>" + i.getUpdateTime());

        time9_temp.setText(" Temperature: " + i.getTemperature(unit) + "                    Sky Condition: " + i.getSky());

        time9_icon = new JLabel(new ImageIcon(i.getIcon()));

        javax.swing.GroupLayout time9Layout = new javax.swing.GroupLayout(time9);
        time9.setLayout(time9Layout);
        time9Layout.setHorizontalGroup(
            time9Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(time9Layout.createSequentialGroup()
                .addGroup(time9Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(time9_time)
                    .addComponent(time9_temp))
                .addGap(0, 0, Short.MAX_VALUE))
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, time9Layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(time9_icon)
                .addGap(71, 71, 71))
        );
        time9Layout.setVerticalGroup(
            time9Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(time9Layout.createSequentialGroup()
                .addComponent(time9_time)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(time9_temp)
                .addGap(14, 14, 14)
                .addComponent(time9_icon)
                .addGap(0, 55, Short.MAX_VALUE))
        );

        
        /**
         * +12 hours forecast
         */
        i = hourly[5];
        time12.setBackground(new java.awt.Color(175, 210, 250));
        time12.setBorder(new javax.swing.border.MatteBorder(null));
        time12.setPreferredSize(new java.awt.Dimension(515, 125));

        time12_time.setFont(new java.awt.Font("Lucida Grande", 1, 14));		//font
        time12_time.setText("<html><tr><html>" + i.getUpdateTime());

        time12_temp.setText(" Temperature: " + i.getTemperature(unit) + "                    Sky Condition: " + i.getSky());

        time12_icon = new JLabel(new ImageIcon(i.getIcon()));

        javax.swing.GroupLayout time12Layout = new javax.swing.GroupLayout(time12);
        time12.setLayout(time12Layout);
        time12Layout.setHorizontalGroup(
            time12Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(time12Layout.createSequentialGroup()
                .addGroup(time12Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(time12_time)
                    .addComponent(time12_temp))
                .addGap(0, 0, Short.MAX_VALUE))
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, time12Layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(time12_icon)
                .addGap(71, 71, 71))
        );
        time12Layout.setVerticalGroup(
            time12Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(time12Layout.createSequentialGroup()
                .addComponent(time12_time)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(time12_temp)
                .addGap(14, 14, 14)
                .addComponent(time12_icon)
                .addGap(0, 55, Short.MAX_VALUE))
        );

        
        /**
         * +15 hours forecast
         */
        i = hourly[6];
        time15.setBackground(new java.awt.Color(210, 229, 243));
        time15.setBorder(new javax.swing.border.MatteBorder(null));
        time15.setPreferredSize(new java.awt.Dimension(515, 125));
        
        time15_time.setFont(new java.awt.Font("Lucida Grande", 1, 14));		//font
        time15_time.setText("<html><tr><html>" + i.getUpdateTime());

        time15_temp.setText(" Temperature: " + i.getTemperature(unit) + "                    Sky Condition: " + i.getSky());

        time15_icon = new JLabel(new ImageIcon(i.getIcon()));

        javax.swing.GroupLayout time15Layout = new javax.swing.GroupLayout(time15);
        time15.setLayout(time15Layout);
        time15Layout.setHorizontalGroup(
            time15Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(time15Layout.createSequentialGroup()
                .addGroup(time15Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(time15_time)
                    .addComponent(time15_temp))
                .addGap(0, 0, Short.MAX_VALUE))
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, time15Layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(time15_icon)
                .addGap(71, 71, 71))
        );
        time15Layout.setVerticalGroup(
            time15Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(time15Layout.createSequentialGroup()
                .addComponent(time15_time)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(time15_temp)
                .addGap(14, 14, 14)
                .addComponent(time15_icon)
                .addGap(0, 63, Short.MAX_VALUE))
        );

        
        /**
         * +18 hours forecast
         */
        i = hourly[7];
        time18.setBackground(new java.awt.Color(175, 210, 250));
        time18.setBorder(new javax.swing.border.MatteBorder(null));
        time18.setPreferredSize(new java.awt.Dimension(515, 125));

        time18_time.setFont(new java.awt.Font("Lucida Grande", 1, 14));		//font
        time18_time.setText("<html><tr><html>" + i.getUpdateTime());

        time18_temp.setText(" Temperature: " + i.getTemperature(unit) + "                    Sky Condition: " + i.getSky());

        time18_icon = new JLabel(new ImageIcon(i.getIcon()));

        javax.swing.GroupLayout time18Layout = new javax.swing.GroupLayout(time18);
        time18.setLayout(time18Layout);
        time18Layout.setHorizontalGroup(
            time18Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(time18Layout.createSequentialGroup()
                .addGroup(time18Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(time18_time)
                    .addComponent(time18_temp))
                .addGap(0, 0, Short.MAX_VALUE))
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, time18Layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(time18_icon)
                .addGap(71, 71, 71))
        );
        time18Layout.setVerticalGroup(
            time18Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(time18Layout.createSequentialGroup()
                .addComponent(time18_time)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(time18_temp, javax.swing.GroupLayout.PREFERRED_SIZE, 16, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(14, 14, 14)
                .addComponent(time18_icon)
                .addGap(0, 55, Short.MAX_VALUE))
        );
        
        
        /**
         * +21 hours forecast
         */
        i = hourly[8];
        time21.setBackground(new java.awt.Color(210, 229, 243));
        time21.setBorder(new javax.swing.border.MatteBorder(null));
        time21.setPreferredSize(new java.awt.Dimension(515, 125));
        
        time21_time.setFont(new java.awt.Font("Lucida Grande", 1, 14));		//font
        time21_time.setText("<html><tr><html>" + i.getUpdateTime());

        time21_temp.setText(" Temperature: " + i.getTemperature(unit) + "                    Sky Condition: " + i.getSky());

        time21_icon = new JLabel(new ImageIcon(i.getIcon()));
        
        javax.swing.GroupLayout time21Layout = new javax.swing.GroupLayout(time21);
        time21.setLayout(time21Layout);
        time21Layout.setHorizontalGroup(
            time21Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(time21Layout.createSequentialGroup()
                .addGroup(time21Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(time21_time)
                    .addComponent(time21_temp))
                .addGap(0, 0, Short.MAX_VALUE))
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, time21Layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(time21_icon)
                .addGap(71, 71, 71))
        );
        time21Layout.setVerticalGroup(
            time21Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(time21Layout.createSequentialGroup()
                .addComponent(time21_time)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(time21_temp)
                .addGap(14, 14, 14)
                .addComponent(time21_icon)
                .addGap(0, 55, Short.MAX_VALUE))
        );

        
        /**
         * +24 hours forecast
         */
        i = hourly[9];
        time24.setBackground(new java.awt.Color(175, 210, 250));
        time24.setBorder(new javax.swing.border.MatteBorder(null));
        time24.setPreferredSize(new java.awt.Dimension(515, 125));
        
        time24_time.setFont(new java.awt.Font("Lucida Grande", 1, 14));		//font
        time24_time.setText("<html><tr><html>" + i.getUpdateTime());

        time24_temp.setText(" Temperature: " + i.getTemperature(unit) + "                    Sky Condition: " + i.getSky());

        time24_icon = new JLabel(new ImageIcon(i.getIcon()));

        javax.swing.GroupLayout time24Layout = new javax.swing.GroupLayout(time24);
        time24.setLayout(time24Layout);
        time24Layout.setHorizontalGroup(
            time24Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(time24Layout.createSequentialGroup()
                .addGroup(time24Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(time24_time)
                    .addComponent(time24_temp))
                .addGap(0, 162, Short.MAX_VALUE))
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, time24Layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(time24_icon)
                .addGap(71, 71, 71))
        );
        time24Layout.setVerticalGroup(
            time24Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(time24Layout.createSequentialGroup()
                .addComponent(time24_time)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(time24_temp)
                .addGap(14, 14, 14)
                .addComponent(time24_icon)
                .addGap(0, 55, Short.MAX_VALUE))
        );

        
        /**
         * midInside layout
         */
        javax.swing.GroupLayout midInsideLayout = new javax.swing.GroupLayout(midInside);
        midInside.setLayout(midInsideLayout);
        midInsideLayout.setHorizontalGroup(
            midInsideLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(time24, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addComponent(time21, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addComponent(time18, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addComponent(time15, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addComponent(time12, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addComponent(time9, javax.swing.GroupLayout.DEFAULT_SIZE, 509, Short.MAX_VALUE)
            .addComponent(time6, javax.swing.GroupLayout.DEFAULT_SIZE, 509, Short.MAX_VALUE)
            .addComponent(time3, javax.swing.GroupLayout.DEFAULT_SIZE, 509, Short.MAX_VALUE)
            .addComponent(time0, javax.swing.GroupLayout.DEFAULT_SIZE, 509, Short.MAX_VALUE)
        );
        midInsideLayout.setVerticalGroup(
            midInsideLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(midInsideLayout.createSequentialGroup()
                .addComponent(time0, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(time3, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(time6, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(time9, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(time12, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(time15, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(time18, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(time21, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(time24, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
        );

        
        /**
         * scroll panel layout
         */
        jScrollPane1.setViewportView(midInside);

        javax.swing.GroupLayout sTmidPanelLayout = new javax.swing.GroupLayout(sTmidPanel);
        sTmidPanel.setLayout(sTmidPanelLayout);
        sTmidPanelLayout.setHorizontalGroup(
            sTmidPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 533, Short.MAX_VALUE)
        );
        sTmidPanelLayout.setVerticalGroup(
            sTmidPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jScrollPane1, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE)
        );

        
        /**
         * right panel border and size
         */
        sTRightPanel.setBorder(new javax.swing.border.SoftBevelBorder(javax.swing.border.BevelBorder.RAISED));
        sTRightPanel.setPreferredSize(new java.awt.Dimension(130, 525));
        
        
        /**
         * add text
         */

    	clock.setFont(new java.awt.Font("Lucida Grande", 1, 13));	 // font
    	
		sunrise.setText("<html>Sunrise Time:<br><html> " + current.getSunrise());

		sunset.setText("<html>Sunset Time:<br><html>" + current.getSunset());

		minTemp.setText("<html>Min Temperature:<br><html>" + current.getMinTemp(unit));
		
		maxTemp.setText("<html>Max Temperature:<br><html>" + current.getMaxTemp(unit));
		
        javax.swing.GroupLayout sTRightPanelLayout = new javax.swing.GroupLayout(sTRightPanel);
        sTRightPanel.setLayout(sTRightPanelLayout);
        sTRightPanelLayout.setHorizontalGroup(
            sTRightPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(sTRightPanelLayout.createSequentialGroup()
                .addGap(17, 17, 17)
                .addGroup(sTRightPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(sunset)
                    .addComponent(sunrise)
                    .addComponent(clock)
                    .addComponent(minTemp)
                    .addComponent(maxTemp))
                .addContainerGap(20, Short.MAX_VALUE))
        );
        sTRightPanelLayout.setVerticalGroup(
            sTRightPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(sTRightPanelLayout.createSequentialGroup()
                .addGap(63, 63, 63)
                .addComponent(clock)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(sunrise)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(sunset)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(minTemp)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(maxTemp)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addComponent(sTLeftPanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(sTmidPanel, javax.swing.GroupLayout.DEFAULT_SIZE, 539, Short.MAX_VALUE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(sTRightPanel, javax.swing.GroupLayout.PREFERRED_SIZE, 147, javax.swing.GroupLayout.PREFERRED_SIZE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(sTmidPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addComponent(sTLeftPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addComponent(sTRightPanel, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );

        pack();
    }                      

    private void updateButtonStateChanged(javax.swing.event.ChangeEvent evt) {                                          
       
    }                                         

    private void updateButtonMouseClicked(java.awt.event.MouseEvent evt) {                                          

    }                                         
    /**
     * update Button function
     */
    private void updateButtonActionPerformed(java.awt.event.ActionEvent evt) {
    	
    	// call and get the selected location
    	this.unit = Settings.instance.getUnit();
    	current = new WeatherInfo(Settings.instance.getLocation()); 
    	sCast = new ShortTermForecast(Settings.instance.getLocation());
    	hourly = sCast.getHourly();
    	i = hourly[1];

    	localCityName.setText(current.getLocation());
    	localTemp.setText("Currently: " + current.getTemperature(unit));
    	lastUpdateTime.setText("<html>System Last Updated:<br><html>" + current.getUpdateTime());
    	lastUpdate.setText("<html>User Last Update: <br><html>" + current.getCurrentTime());

    	sunrise.setText("<html>Sunrise Time:<br><html> " + current.getSunrise());
    	sunset.setText("<html>Sunset Time:<br><html>" + current.getSunset());
    	minTemp.setText("<html>Min Temperature:<br><html>" + current.getMinTemp(unit));	
    	maxTemp.setText("<html>Max Temperature:<br><html>" + current.getMaxTemp(unit));

    	time0_time.setText("<html><tr><html>" + i.getUpdateTime());
    	time0_temp.setText(" Temperature: " + i.getTemperature(unit) + "                    Sky Condition: " + i.getSky());
    	time0_icon = new JLabel(new ImageIcon(i.getIcon()));

    	i=hourly[check+2];
    	time3_time.setText("<html><tr><html>" + i.getUpdateTime());
    	time3_temp.setText(" Temperature: " + i.getTemperature(unit)+"                    Sky Condition: " + i.getSky());
    	time3_icon = new JLabel(new ImageIcon(i.getIcon()));

    	i=hourly[check+3];
    	time6_time.setText("<html><tr><html>" + i.getUpdateTime());
    	time6_temp.setText(" Temperature: " + i.getTemperature(unit)+"                    Sky Condition: " + i.getSky());
    	time6_icon = new JLabel(new ImageIcon(i.getIcon()));

    	i=hourly[check+4];
    	time9_time.setText("<html><tr><html>" + i.getUpdateTime());
    	time9_temp.setText(" Temperature: " + i.getTemperature(unit)+"                    Sky Condition: " + i.getSky());
    	time9_icon = new JLabel(new ImageIcon(i.getIcon()));

    	i=hourly[check+5];
    	time12_time.setText("<html><tr><html>" + i.getUpdateTime());
    	time12_temp.setText(" Temperature: " + i.getTemperature(unit)+"                    Sky Condition: " + i.getSky());
    	time12_icon = new JLabel(new ImageIcon(i.getIcon()));

    	i=hourly[check+6];
    	time15_time.setText("<html><tr><html>" + i.getUpdateTime());
    	time15_temp.setText(" Temperature: " + i.getTemperature(unit)+"                    Sky Condition: " + i.getSky());
    	time15_icon = new JLabel(new ImageIcon(i.getIcon()));

    	i=hourly[check+7];  
    	time18_time.setText("<html><tr><html>" + i.getUpdateTime());
    	time18_temp.setText(" Temperature: " + i.getTemperature(unit)+"                    Sky Condition: " + i.getSky());
    	time18_icon = new JLabel(new ImageIcon(i.getIcon()));

    	i=hourly[check+8];
    	time21_time.setText("<html><tr><html>" + i.getUpdateTime());
    	time21_temp.setText(" Temperature: " + i.getTemperature(unit)+"                    Sky Condition: " + i.getSky());
    	time21_icon = new JLabel(new ImageIcon(i.getIcon()));

    	i=hourly[check+9];
    	time24_time.setText("<html><tr><html>" + i.getUpdateTime());
    	time24_temp.setText(" Temperature: " + i.getTemperature(unit)+"                    Sky Condition: " + i.getSky());
    	time24_icon = new JLabel(new ImageIcon(i.getIcon()));

    }                                            
}

