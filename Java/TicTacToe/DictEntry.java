/*
 *  Eric Bachmeier
 *  
 *  This class represents an entry into the dictionary associated with 
 *  its integer score 
 * */

public class DictEntry {

	// fields
	private String configeration;
	private int levelScore;

	// constructor for DictEntry object
	public DictEntry(String config, int score) {
		this.configeration = config;
		this.levelScore = score;
	}

	// methods

	// getter method for config key
	public String getConfig() {
		return this.configeration;
	}

	// getter method for level score
	public int getScore() {
		return this.levelScore;
	}
}