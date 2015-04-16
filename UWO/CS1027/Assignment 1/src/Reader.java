/**
 * Class that represents a reader object and can print the newest added objects
 * 
 * @author Eric Bachmeier 250738776
 * 
 */
public class Reader {

	//////////////// Attribute declarations ///////////////
	
	private Feed feed;
	private int nextItem;

	//////////////// Constructor ///////////////
	
	/**
	 * constructor creates a Reader from passed Feed
	 * 
	 * @param feed
	 */
	public Reader(Feed feed) {
		this.feed = feed;
	}

	//////////////// Methods ///////////////
	
	/**
	 * find method prints all the items in the feed that contain the passed pattern
	 * @param pattern
	 */
	public void find(String pattern) {
		feed.find(pattern);
	}

	/**
	 * read method prints all the new items that have been added to the list since the last read
	 */
	public void read() {
		nextItem = feed.readFrom(nextItem); // set nextItem to the size of list, to increment the next read position
	}
}
