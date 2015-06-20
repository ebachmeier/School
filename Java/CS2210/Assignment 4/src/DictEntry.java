/**
 * Class for storing words, definitions, and types in DictEntry data types
 * 
 * @author Eric Bachmeier 250738776
 * 
 */

public class DictEntry {
	
	// variables
	private String word, definition;
	private int type;

	/**
	 * Constructor to initialize a DictEntry with a word, definition, and type
	 * 
	 * @param word described by the definition
	 * @param definition of the word
	 * @param type of definition for the word
	 */
	public DictEntry (String word, String definition, int type) {
		
		this.word = word;
		this.definition = definition;
		this.type = type;
		
	}

	/**
	 * @return the word stored in the dictionary
	 */
	public String word() {
		return word;
	}
	
	/**
	 * @return the definition of the DictEntry word
	 */
	public String definition() {
		return definition;
	}
	
	/**
	 * @return the type of definition stored
	 */
	public int type() {
		return type;
	}
	
}
