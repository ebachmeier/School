/**
 * Class that represents a Feed as a list of news items
 * 
 * @author Eric Bachmeier 250738776
 * 
 */

public class Feed {

	private final int DEFAULT_MAX_SIZE = 10; // default size of list

	//////////////// Attribute declarations ///////////////
	
	private String name; // declare variable for name of feed
	private String[] list; // declare list of Strings
	private int size; // declare variable for size of feed list

	//////////////// Constructor ///////////////
	
	/**
	 * constructor creates Feed of default size
	 * 
	 * @param name
	 */
	public Feed(String name) {
		this.name = name; // set name of feed
		list = new String[DEFAULT_MAX_SIZE]; // set list to the default size declared
	}

	//////////////// Methods ///////////////
	
	/**
	 * add method that adds a news item to the list
	 * 
	 * @param item
	 */
	public void add(String item) {
		if (size == list.length)
			expandCapacity(); // double capacity of list if size is filled
		list[size] = item; // insert item in next list position
		size++; // increment size by one
	}

	/**
	 * expandCapacity method is a helper method that creates a new array to
	 * store news items with twice the capacity
	 */
	private void expandCapacity() {
		String[] largerList = new String[list.length * 2]; // double the list capacity 
		for (int i = 0; i < list.length; i++)
			largerList[i] = list[i]; // append the original list to the new larger list
		list = largerList; // set it back to use list name variable
	}

	/**
	 * find method that prints all the news items in the list that contain a
	 * certain string
	 * 
	 * @param args
	 */
	public void find(String pattern) {
		for (int i = 0; i < size; i++) { // loop through feed list
			if (list[i].contains(pattern)) // print if feed contains passed String
				System.out.println(name + ": " + list[i]); // print feed name ahead of every feed item
		}
	}

	/**
	 * readFrom method prints all the items in the list starting from position
	 * start, and returns the number of items in the list
	 * 
	 * @param args
	 */
	public int readFrom(int start) {
		for (int i = start; i < size; i++) {
			System.out.println(name + ": " + list[i]); // print feed name ahead of every feed item
		}
		return size; // return integer size of the list 
	}
}
