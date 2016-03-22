/* 
 * Eric Bachmeier
 * 
 * This class implements the methods of the DictionaryADT interface 
 * */

import java.util.LinkedList;

public class Dictionary implements DictionaryADT {

	// fields
	private int size, total;
	private LinkedList<DictEntry>[] entries;

	// prime integer constant value for hash value parameter
	// integer 33 gave me the least collisions
	private final int VALUE = 33;

	// constructor for Dictionary list
	public Dictionary(int size) {
		// set total number of elements to 0
		// this will later be incremented when elements are added or deleted
		total = 0;
		// set private size variable to the passed size
		this.size = size;
		// create dictionary of passed size
		entries = new LinkedList[size];
		// create a list of DictEntry objects in every slot of 'entries'
		for (int i = 0; i < size; i++) {
			entries[i] = new LinkedList<DictEntry>();
		}
	}

	// methods

	// hash method to return the hash number of a given key
	public int hashFunction(String config, int a) {
		int x = (int) config.charAt(0);
		for (int i = 1; i < config.length(); i++) {
			// polynomial hash code in MOD with size of table
			x = (x * a + (int) config.charAt(i)) % size;
		}
		// return the integer hash code
		return x;
	}

	// find method for a given key
	public int find(String config) {
		// compute the hash code of the given key
		int hash = hashFunction(config, VALUE);
		// loop through that hash slot
		for (int i = 0; i < entries[hash].size(); i++) {
			if (entries[hash].get(i).getConfig().equals(config)) {
				// if the keys match, return the level score
				return entries[hash].get(i).getScore();
			}
		}
		// if the key is not in the table, return -1
		return -1;
	}

	// insert method for DictEntry objects
	public int insert(DictEntry pair) throws DictionaryException {
		// use getter method to retrieve config key
		String config = pair.getConfig();
		// compute hash code of key
		int hash = hashFunction(config, VALUE);
		// if the key is not in the table, throw an exception
		if (find(config) != -1) {
			throw new DictionaryException("pair is already in dictionary");
		} else {
			// otherwise, insert it into that hash slot
			if (entries[hash].size() > 0) {
				entries[hash].add(pair);
				total += 1;
				// return 1 if there is a collision
				return 1;
			} else {
				entries[hash].add(pair);
				total += 1;
				return 0;
			}
		}
	}

	// remove method for config key
	public void remove(String config) throws DictionaryException {
		// compute hash code for key
		int hash = hashFunction(config, VALUE);
		// if that hash slot is empty, throw an exception
		if (entries[hash].size() == 0) {
			throw new DictionaryException(
					"this configuration is not in the dictionary");
		} else {
			// otherwise, remove the element with that key
			entries[hash].remove(config);
			total -= 1;
		}
	}

	// getter method for total number of elements in table
	public int numElements() {
		// return the total that has kept track of how many elements
		return total;
	}
}
