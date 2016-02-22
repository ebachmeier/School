import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.border.LineBorder;

import java.awt.Color;
import java.awt.Dimension;

import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.JScrollPane;

import java.awt.Font;
import java.util.LinkedList;
import java.util.List;

import javax.swing.*;
import javax.swing.GroupLayout.Alignment;

import java.awt.GridLayout;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;


import org.json.JSONObject;
import org.json.JSONException;


/**
 * This class displays the Graphical User Interface for the page "My Locations".
 * 
 * @author Marc Stahl
 */

public class MyLocationsInterface extends JFrame {

	/**
	 * Instance Variables
	 */
	private static final long serialVersionUID = 1L;
	private String pendingCity; /** The city that is waiting to be added.*/
	private String pendingCountryCode; /** The country code that is waiting to be added.*/
	private String[] citiesHTML; /** The list of locations expressed in HTML.*/
	private String[] citiesComma; /** The list of locations expressed with a comma separating the city and country code.*/
	private int numCities;  /** Number of locations in the location list.*/
	private int currentCityIndex;  /** Index into array of locations, indicating currently selected city.*/
	private JPanel contentPane;  /** Top level panel for form.*/
	public static JTabbedPane tabShort;  /** Tabs for top level panel.*/
	public static ShortTermInterface STI; /** This object represents the Short Term Interface page.*/
	public static LongTermInterface LTI; /** This object represents the Long Term Interface page.*/
	public static CustomWeatherInterface CWI; /** This object represents the custom Weather View page.*/
	private JTextField cityTF; /** A text field where the user enters part of the search term.*/
	private JTextField countryCodeTF; /** A text field where the user enters part of the search term.*/
	private JTextField displaySearchResult; /** This uneditable text field displays your search result, and also
			any error messages relating to the search term, or error messages relating to adding the search result
			to the location list.*/
	private JButton addButton; /** When pressed, this button adds the search result to the locations list.*/
	private JPanel jpanelInsideSP; /** This jpanel holds the location list.*/
	private GridLayout myGridLayout; /** This grid layout is applied to jpanelInsideSP.*/
	private List<JToggleButton> toggleButtons; /** A list of location buttons to be displayed in the location list.*/
	private List<JButton> removeButtons; /** A list of remove buttons to be displayed in the location list.*/


	/**
	 * Initialize the array of cities, and an integer variable to track the number of cities.
	 * 
	 * @param h			List of locations in HTML format.
	 * @param c			List of locations with city and country code separated by a comma.
	 * @param num		The number of locations that start in the location list.
	 */
	public MyLocationsInterface()
	{
		citiesHTML = Settings.instance.getHTMLList();
		citiesComma = Settings.instance.getCommaList();
		numCities = Settings.instance.getNumCities();
		currentCityIndex = Settings.instance.getLocationIndex();  // Initialize default city
		//StoreData.storeSettings(Settings.instance);
		initUI();  // Initialize the form
	}


	/**
	 * In this method, all of the Swing components are created and displayed.
	 * 
	 * @throws JSONException		This exception is thrown if the JSONObject retrieved
	 * 								from Open Weather Map does not follow the proper
	 * 								JSON format.
	 */
	public void initUI() {

		/**
		 * Set up the tabbed pane, and the content pane.
		 */
		tabShort = new JTabbedPane();
		setTitle("Team 1 - Weather App");
		setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		setBackground(new Color(255, 255, 255));
		contentPane = new JPanel();
		contentPane.setLayout(null);

		tabShort.setBackground(new Color(255, 255, 255));
		tabShort.setBorder(new EmptyBorder(5, 5, 5, 5));
		tabShort.setPreferredSize(new Dimension(937, 577));
		tabShort.addMouseListener(new MouseAdapter() {
			public void mouseClicked(MouseEvent evt) {
				tabShortMouseClicked(evt);
			}
		});
		
		/**
		 * Create the bottom left JPanel, and add to it 1 JLabel, 1 uneditable
		 * JTextField, and 1 JButton. The bottom left JPanel uses absolute positioning.
		 */
		JPanel bottomLeftJPanel = new JPanel();
		bottomLeftJPanel.setBorder(new LineBorder(new Color(0, 0, 0)));
		bottomLeftJPanel.setBounds(0, 288, 468, 288);
		contentPane.add(bottomLeftJPanel);
		bottomLeftJPanel.setLayout(null);

		displaySearchResult = new JTextField();
		displaySearchResult.setEditable(false);
		displaySearchResult.setFont(new Font("Tahoma", Font.BOLD, 16));
		displaySearchResult.setBounds(43, 91, 174, 59);
		bottomLeftJPanel.add(displaySearchResult);
		displaySearchResult.setColumns(10);

		JLabel lblNewLabel_2 = new JLabel("Search Result:");
		lblNewLabel_2.setFont(new Font("Tahoma", Font.BOLD, 16));
		lblNewLabel_2.setBounds(21, 11, 143, 28);
		bottomLeftJPanel.add(lblNewLabel_2);

		addButton = new JButton("Add");
		addButton.setFont(new Font("Tahoma", Font.BOLD, 16));
		addButton.setBounds(255, 106, 86, 28);
		addButton.setEnabled(false);
		bottomLeftJPanel.add(addButton);
		
		addButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0)
			{
				/** Assemble strings in both formats for the search result.*/
				String pendingLocationHTML;
				StringBuilder tempPendingLocationHTML = new StringBuilder("<html>");
				tempPendingLocationHTML.append(pendingCity);
				tempPendingLocationHTML.append("<br>");
				tempPendingLocationHTML.append(pendingCountryCode);
				pendingLocationHTML = tempPendingLocationHTML.toString();
				
				String pendingLocationComma;
				StringBuilder tempPendingLocationComma = new StringBuilder(pendingCity);
				tempPendingLocationComma.append(",");
				tempPendingLocationComma.append(pendingCountryCode);
				pendingLocationComma = tempPendingLocationComma.toString();
				
				/** Regardless of which of the three cases below is true, the add button must
				 *  always be disabled immediately after being pressed.
				 */
				addButton.setEnabled(false);
				
				if (numCities == 50)
					displaySearchResult.setText("(Fail: city list at max)");
				else if (isInCityList(pendingLocationHTML))
					displaySearchResult.setText("(Fail: already in list)");
				else
				{
					/** Add the search result to the internal lists, and
					 *  to the location list displayed on screen.
					 */
					displaySearchResult.setText("('Add' successful)");
					citiesHTML[numCities] = pendingLocationHTML;
					citiesComma[numCities] = pendingLocationComma;
					myGridLayout.setRows(numCities + 1);
					addToGUICityList(numCities);
					numCities++;
				}
			}
		});
		
		/**
		 * Create the top left JPanel, and add to it 2 JLabels, 2 JTextFields,
		 * and 1 JButton. The top left JPanel uses absolute positioning.
		 */
		JPanel topLeftJPanel = new JPanel();
		topLeftJPanel.setBorder(new LineBorder(new Color(0, 0, 0)));
		topLeftJPanel.setBounds(0, 0, 468, 288);
		contentPane.add(topLeftJPanel);
		topLeftJPanel.setLayout(null);

		JLabel cityLabel = new JLabel("City");
		cityLabel.setFont(new Font("Tahoma", Font.BOLD, 16));
		cityLabel.setBounds(123, 40, 54, 28);
		topLeftJPanel.add(cityLabel);

		JLabel countryCodeLabel = new JLabel("Country Code");
		countryCodeLabel.setFont(new Font("Tahoma", Font.BOLD, 16));
		countryCodeLabel.setBounds(47, 99, 130, 28);
		topLeftJPanel.add(countryCodeLabel);

		cityTF = new JTextField();
		cityTF.setFont(new Font("Tahoma", Font.BOLD, 16));
		cityTF.setBounds(200, 40, 130, 28);
		topLeftJPanel.add(cityTF);
		cityTF.setColumns(10);

		countryCodeTF = new JTextField();
		countryCodeTF.setFont(new Font("Tahoma", Font.BOLD, 16));
		countryCodeTF.setBounds(200, 99, 130, 28);
		topLeftJPanel.add(countryCodeTF);
		countryCodeTF.setColumns(10);

		JButton searchButton = new JButton("Search");
		searchButton.setFont(new Font("Tahoma", Font.BOLD, 16));
		searchButton.setBounds(135, 168, 105, 28);
		topLeftJPanel.add(searchButton);
		
		JLabel lblOr = new JLabel("OR");
		lblOr.setFont(new Font("Tahoma", Font.BOLD, 16));
		lblOr.setBounds(133, 69, 54, 28);
		topLeftJPanel.add(lblOr);
		
		searchButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				
				/**
				 * Assemble the search term in comma format, in preparation for being sent to
				 * Open Weather Map.
				 */

				String cityInput = cityTF.getText();
				String countryCodeInput = countryCodeTF.getText();
				String searchTerm;
				
				StringBuilder tempSearchTerm = new StringBuilder(cityInput);
				tempSearchTerm.append(",");
				tempSearchTerm.append(countryCodeInput);
				searchTerm = tempSearchTerm.toString();
				
				
				try
				{
					/**
					 * Give the search term to HttpClient, which subsequently passes it to Open Weather Map.
					 * Then, retrieve the corresponding search result (or error message) in the form of
					 * a JSONObject.
					 */
					HttpClient searchForNameInOWM = new HttpClient(searchTerm, "c");
					JSONObject OWMData = new JSONObject(searchForNameInOWM.getData());
					
					/**
					 * If the user entered a valid city (indicated by the code '200'), then show the user
					 * the search result, and enable the add button.
					 */
					if ((OWMData.getInt("cod")) == 200)
					{
						System.out.println("city: " + OWMData.getString("name"));
						System.out.println("country code: " + OWMData.getJSONObject("sys").getString("country"));
						
						pendingCity = OWMData.getString("name");
						pendingCountryCode = OWMData.getJSONObject("sys").getString("country");
						
						if (pendingCountryCode.equals("Canada"))
							pendingCountryCode = "CA";
						else if (pendingCountryCode.equals("United States of America"))
							pendingCountryCode = "US";
						else if (pendingCountryCode.equals("United Kingdom"))
							pendingCountryCode = "GB";
						else if (pendingCountryCode.equals("France"))
							pendingCountryCode = "FR";
						
						displaySearchResult.setText(pendingCity + ", " + pendingCountryCode);
						addButton.setEnabled(true);
					}
					/**
					 * If the user entered an invalid city (indicated by the code '404') then show the user
					 * an error message, and disable the add button.
					 */
					else if ((OWMData.getString("cod")).equals("404"))
					{
						System.out.println(OWMData.getString("message"));
						
						displaySearchResult.setText("(city not found)");
						addButton.setEnabled(false);
					}
					/**
					 *  If Open Weather Map returns something completely wrong, then display an
					 *  error message, and disable the add button.
					 */
					else
					{
						System.out.println("Open Weather Map has given an invalid response. Below is the invalid response:\n" + OWMData);
						
						displaySearchResult.setText("(invalid response from OWM)");
						addButton.setEnabled(false);
					}
				}
				catch (JSONException ex)
				{
					System.out.println("Error retrieving country name and code for entered location.");
					
					displaySearchResult.setText("(invalid response from OWM)");
					addButton.setEnabled(false);
				}
			}
		});

		
		/**
		 * Create the top right JPanel, and add to it 1 JLabel. The top right
		 * JPanel uses absolute positioning.
		 */
		JPanel topRightJPanel = new JPanel();
		topRightJPanel.setBorder(new LineBorder(new Color(0, 0, 0)));
		topRightJPanel.setBounds(468, 0, 468, 150);
		contentPane.add(topRightJPanel);
		topRightJPanel.setLayout(null);

		JLabel lblNewLabel_3 = new JLabel(
				"<html>Your current location is shown selected.<br>You can change it by clicking on a<br>different location.");
		lblNewLabel_3.setFont(new Font("Tahoma", Font.BOLD, 16));
		lblNewLabel_3.setBounds(21, 21, 351, 56);
		topRightJPanel.add(lblNewLabel_3);

		


		
		/**
		 * Create the bottom right JPanel, and add to it a JScrollPane. Add to
		 * the JScrollPane a JPanel. Inside this inner JPanel, create a list of
		 * cities. The bottom right JPanel uses absolute positioning, and the inner
		 * JPanel uses grid layout.
		 */
		JPanel bottomRightJPanel = new JPanel();
		bottomRightJPanel.setBorder(new LineBorder(new Color(0, 0, 0)));
		bottomRightJPanel.setBounds(468, 150, 468, 427);
		contentPane.add(bottomRightJPanel);
		bottomRightJPanel.setLayout(null);

		JScrollPane scrollPane = new JScrollPane();
		scrollPane.setBounds(0, 0, 455, 390);
		bottomRightJPanel.add(scrollPane);

		jpanelInsideSP = new JPanel();
		scrollPane.setViewportView(jpanelInsideSP);
		myGridLayout = new GridLayout(numCities, 2, 8, 8);
		jpanelInsideSP.setLayout(myGridLayout);

		
		/**
		 * Create pointers to both button lists.
		 */
		toggleButtons = new LinkedList<JToggleButton>();
		removeButtons = new LinkedList<JButton>();

		/**
		 * Loop through the list of cities, and create and display buttons for each city.
		 */
		for (int cityListPos = 0; cityListPos < numCities; cityListPos++)
			addToGUICityList(cityListPos);

		/**
		 * Set the starting current city in both the singleton, and in the GUI city list
		 * which is displayed to the user. The starting current City is London, CA.
		 */
		(toggleButtons.get(Settings.instance.getLocationIndex())).setSelected(true);
		(removeButtons.get(Settings.instance.getLocationIndex())).setEnabled(false);
		Settings.instance.setLocation(citiesComma[Settings.instance.getLocationIndex()]);
		
		
		
		addWindowListener(new WindowAdapter()
        {
            @Override
            public void windowClosing(WindowEvent e)
            {
        		Settings.instance.setHTMLList(citiesHTML);
        		Settings.instance.setCommaList(citiesComma);
        		Settings.instance.setNumCities(numCities);
        		Settings.instance.setLocationIndex(currentCityIndex);  // Initialize default city
        		try {
        			StoreData.storeSettings(Settings.instance);
        		} catch (Exception ex) {
        			System.out.println("In MyLocations: couldn't store settings");
        		}
                e.getWindow().dispose();
            }
        });
		
		
		
		/**
		 * Set up all 5 tabs.
		 */
		tabShort.addTab("My Locations", contentPane);
		
		tabShort.insertTab("Local Weather", new ImageIcon(), new LocalWeatherInterface().getContentPane(), "", 1);
		
		tabShort.insertTab("Short Term", new ImageIcon(), new ShortTermInterface().getContentPane(), "", 2);
		
		tabShort.insertTab("Long Term", new ImageIcon(), new LongTermInterface().getContentPane(), "", 3);
		
		tabShort.insertTab("Customize", new ImageIcon(), new CustomWeatherInterface().getContentPane(), "", 4);
		
		GroupLayout layout = new GroupLayout(getContentPane());
		layout.setHorizontalGroup(layout.createParallelGroup(Alignment.LEADING)
				.addGroup(
						Alignment.TRAILING,
						layout.createSequentialGroup()
								.addContainerGap(5, Short.MAX_VALUE)
								.addComponent(tabShort,
										GroupLayout.PREFERRED_SIZE, 939,
										GroupLayout.PREFERRED_SIZE)
								.addContainerGap()));
		layout.setVerticalGroup(layout.createParallelGroup(Alignment.LEADING)
				.addGroup(
						layout.createSequentialGroup()
								.addContainerGap()
								.addComponent(tabShort,
										GroupLayout.PREFERRED_SIZE,
										GroupLayout.DEFAULT_SIZE,
										GroupLayout.PREFERRED_SIZE)
								.addContainerGap(GroupLayout.DEFAULT_SIZE,
										Short.MAX_VALUE)));
		getContentPane().setLayout(layout);

		pack();

	}

	/**
	 * This method receives as input the index of a city. Then, this method makes a
	 * toggle button, and a remove button corresponding to that city. Both buttons
	 * are then added to their respective linked lists, added to 'jpanelInsideSP' to be
	 * displayed on screen, and are each given an action listener.
	 * 
	 * @param cityListPos		The index of the city.
	 */
	public void addToGUICityList(int cityListPos)
	{
		// Create the toggle button for the city
		final int cityListPosFinal = cityListPos;
		JToggleButton currentToggleButton = new JToggleButton(citiesHTML[cityListPosFinal]);
		currentToggleButton.setFont(new Font("Tahoma", Font.BOLD, 16));
		toggleButtons.add(currentToggleButton);
		jpanelInsideSP.add(currentToggleButton);

		// Change selected city (and highlight)
		currentToggleButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				if (Settings.instance.getLocationIndex() != cityListPosFinal)
				{
					(toggleButtons.get(currentCityIndex)).setSelected(false);
					(removeButtons.get(currentCityIndex)).setEnabled(true);
					Settings.instance.setLocationIndex(cityListPosFinal);
					Settings.instance.setLocation(citiesComma[cityListPosFinal]);
					currentCityIndex = cityListPosFinal;
					(removeButtons.get(currentCityIndex)).setEnabled(false);
				}
				else
					(toggleButtons.get(currentCityIndex)).setSelected(true);
			}
		});

		// Create a remove button next to the city button
		JButton currentRemoveButton = new JButton("Remove");
		currentRemoveButton.setFont(new Font("Tahoma", Font.BOLD, 16));
		removeButtons.add(currentRemoveButton);
		jpanelInsideSP.add(currentRemoveButton);

		// Remove the selected city from the list and the screen
		currentRemoveButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				jpanelInsideSP.removeAll();
				for (int cityListPos = 0; cityListPos < numCities; cityListPos++)
				{
					toggleButtons.remove(0);
					removeButtons.remove(0);
				}
				removeFromCityList(cityListPosFinal);
				myGridLayout = new GridLayout(numCities, 2, 8, 8);
				
				jpanelInsideSP.setLayout(myGridLayout);
				
				for (int cityListPos = 0; cityListPos < numCities; cityListPos++)
					addToGUICityList(cityListPos);
				
				currentCityIndex = posInCityList(Settings.instance.getLocation());
				Settings.instance.setLocationIndex(currentCityIndex);
				(toggleButtons.get(currentCityIndex)).setSelected(true);
				(removeButtons.get(currentCityIndex)).setEnabled(false);
			}
		});
	}
	

	/**
	 * Determines if a city is already in the locations list. Note that this method is set
	 * up only to receive the city name in HTML format.
	 * 
	 * @param check		The city to be searched for in the locations list.
	 * @return			True if the city is in the list, false otherwise.
	 */
	public boolean isInCityList(String check)
	{
		for(int index = 0; index < numCities; index++)
			if (citiesHTML[index].equals(check))
				return true;
			
		
		return false;
	}
	
	
	/**
	 * Determines if a city is already in the locations list. Note that this method is set
	 * up only to receive the city name in Comma format.
	 * 
	 * @param check		The city to be searched for in the locations list.
	 * @return			The index if the city is in the list, -1 otherwise.
	 */
	public int posInCityList(String check)
	{
		for(int index = 0; index < numCities; index++)
			if (citiesComma[index].equals(check))
				return index;
			
		
		return -1;
	}
	
	
	/**
	 * Removes a city from the locations list. Note that this method only removes the city
	 * from the internal list, and not from the locations list displayed on screen. That is done
	 * in the action listener for the remove button.
	 * 
	 * @param indexToBeRemoved		City to be removed from the list.
	 */
	public void removeFromCityList(int indexToBeRemoved)
	{
		int indexHTML;
		for(indexHTML = indexToBeRemoved; indexHTML < numCities - 1; indexHTML++)
			citiesHTML[indexHTML] = citiesHTML[indexHTML + 1];
		citiesHTML[indexHTML] = "(empty)";
		
		int indexComma;
		for(indexComma = indexToBeRemoved; indexComma < numCities - 1; indexComma++)
			citiesComma[indexComma] = citiesComma[indexComma + 1];
		citiesComma[indexComma] = "(empty)";
		
		numCities--;
	}
	
	
	private void tabShortMouseClicked(MouseEvent evt) {// GEN-FIRST:event_tabShortMouseClicked
		// TODO add your handling code here:
	}// GEN-LAST:event_tabShortMouseClicked
}