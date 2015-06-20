/**
 * Class that constructs a binary search tree of DictEntry nodes
 * 
 * @author Eric Bachmeier 250738776
 * 
 */

public class OrderedDictionary implements OrderedDictionaryADT {

	// variables
	private OrderedDictionaryNode root, node, s, p, parent, remove, replace,
			child, check;
	String def;
	int type;

	/**
	 * Constructor to initialize an empty binary search tree
	 */
	public OrderedDictionary() {
		root = null;
		node = root;
	}

	/**
	 * Returns a node containing the word key passed, or null if no word is
	 * found.
	 * 
	 * @param word
	 * @return DictEntry node with word
	 */
	private OrderedDictionaryNode find(String word) {

		// start traversal at the tree root
		check = root;
		// traverse until word or leaf is found
		while (check != null
				&& check.getDictEntry().word().compareTo(word) != 0) {
			// check if word key is stored to the left
			if (check.getDictEntry().word().compareTo(word) >= 1) {
				// move the node left in the tree if compare is 1
				check = check.getLeftChild();
			}

			// otherwise, the word is stored to the right
			else {
				check = check.getRightChild();
			}
		}
		// return the node containing the passed key even if it is null
		return check;

	}

	/**
	 * Returns the definition of the given word, or it returns an empty string
	 * if the word is not in the dictionary.
	 */
	public String findWord(String word) {
		// return a blank string if word is not in dictionary or tree is still
		// empty
		if (node == null) {
			return "";
		}
		// check if the current node has the same word key as the parameter
		else if (node.getDictEntry().word().compareTo(word) == 0) {
			// return the definition if they match
			return node.getDictEntry().definition();
		}

		// check if word key is stored to the left
		else if (node.getDictEntry().word().compareTo(word) >= 1) {
			// move the node left in the tree
			node = node.getLeftChild();
			// recurse the tree looking for the word
			def = findWord(word);
			// reset the current node to the root of the tree
			node = root;
			// return the definition of the passed word key
			return def;
		}

		// otherwise, the word key should be to the right
		else {
			// move the node right in the tree
			node = node.getRightChild();
			// recurse the tree looking for the word
			def = findWord(word);
			// reset the current node to the root of the tree
			node = root;
			// return the definition of the passed word key
			return def;
		}
	}

	/**
	 * Returns the type of the given word, or it returns -1 if the word is not
	 * in the dictionary.
	 */
	public int findType(String word) {
		// return -1 if the word is not in the dictionary or the tree is empty
		if (node == null)
			return -1;

		// check if the current node has the same word key as the parameter
		else if (node.getDictEntry().word().compareTo(word) == 0) {
			// return the def type if they match
			return node.getDictEntry().type();
		}

		// check if word key is stored to the left
		else if (node.getDictEntry().word().compareTo(word) >= 1) {
			// move the node left in the tree
			node = node.getLeftChild();
			// recurse the tree looking for the word
			type = findType(word);
			// reset the current node to the root of the tree
			node = root;
			// return the def type of the passed word key
			return type;
		}

		// otherwise, the word key is be to the right
		else {
			// move the node right in the tree
			node = node.getRightChild();
			// recurse the tree looking for the word
			type = findType(word);
			// reset the current node to the root of the tree
			node = root;
			// return the def type of the passed word key
			return type;
		}
	}

	/**
	 * Adds the word, its definition, and type into the dictionary. It throws a
	 * DictionaryException if the word is already in the dictionary.
	 */
	public void insert(String word, String definition, int type)
			throws DictionaryException {
		// check for tree being empty
		if (root == null) {
			// create a root if it is empty
			root = new OrderedDictionaryNode(new DictEntry(word, definition,
					type));
			// set current node to the newly created root
			node = root;
		}

		// check if the current node has the same word key as the parameter
		else if (node.getDictEntry().word().compareTo(word) == 0) {
			// reset the current node to the root of the tree
			node = root;
			// throw new exception for the word already being in the dictionary
			throw new DictionaryException(
					"Error: *IN INSERT* the word is already in the dictionary");
		}

		// check if word key is stored to the left
		else if (node.getDictEntry().word().compareTo(word) >= 1) {
			// check if the left child is a leaf
			if (node.getLeftChild() == null) {
				// insert the word in a new left child
				// construct the new node with a parent pointer
				node.setLeftChild(new OrderedDictionaryNode(node,
						new DictEntry(word, definition, type)));
			}
			// otherwise, move the current node to the left and insert
			// recursively
			else {
				node = node.getLeftChild();
				insert(word, definition, type);
				// reset the current node to the root
				node = root;
			}
		}

		// otherwise, the word key should be to the right
		else {
			// check if the right child is a leaf
			if (node.getRightChild() == null) {
				// insert the word in a new right child
				// consttruct a new node with a parent pointer
				node.setRightChild(new OrderedDictionaryNode(node,
						new DictEntry(word, definition, type)));
			}

			// otherwise, move the current node to the right and insert
			// recursively
			else {
				node = node.getRightChild();
				insert(word, definition, type);
				// reset the current node to the root
				node = root;
			}
		}
	}

	/**
	 * Removes the entry with the given word from the dictionary. It throws a
	 * DictionaryException if the word is not in the dictionary.
	 */
	public void remove(String word) throws DictionaryException {
		// find the node with the word key that has been passed
		remove = find(word);
		// throw a new exception if the word is not in the dictionary
		if (remove == null) {
			throw new DictionaryException(
					"Error: *IN REMOVE* the word is not in the dictionary");
		}

		// otherwise, remove the node from the tree
		else {
			// check if one of the child nodes is a leaf
			if (remove.getLeftChild() == null || remove.getRightChild() == null) {
				// set the node we want to replace with to itself
				replace = remove;
			}
			// otherwise, replace with the successor
			else {
				replace = successor(remove);
			}

			// if there is a left child, store iit
			if (replace.getLeftChild() != null) {
				child = replace.getLeftChild();
			}
			// otherwise, store the right child
			else {
				child = replace.getRightChild();
			}

			// check if both nodes of which we wish to replace are null
			if (child != null) {
				// set child replacement node to the parents parent
				child.setParent(replace.getParent());
			}

			// if the replacement node is the root, set the root to replacemen t
			if (replace.getParent() == null) {
				root = child;
			}

			// otherwise replace the node we wish to remove
			else {
				// replacement node to left child of parent, if it is left
				if (replace == replace.getParent().getLeftChild()) {
					replace.getParent().setLeftChild(child);
				}

				// otherwise, do the same for right child situation
				else {
					replace.getParent().setRightChild(child);
				}
			}

			// store the node we are replacing with in the remove node
			if (replace != remove) {
				remove.setRoot(replace.getDictEntry());
			}
		}
	}

	/**
	 * Returns the successor of the given word (the word from the dictionary
	 * that lexicographically follows the given one); it returns an empty string
	 * if the given word has no successor.
	 */
	public String successor(String word) {
		// find the successor of the node containing the word
		s = successor(find(word));
		// if there is no successor, return a blank string
		if (s != null)
			// return the word of the successor
			return s.getDictEntry().word();
		else
			// otherwise, return blank string
			return "";
	}

	/**
	 * Returns the successor of the node passed, null if none passed.
	 * 
	 * @param start
	 * @return successor node
	 */
	private OrderedDictionaryNode successor(OrderedDictionaryNode start) {
		// check if a node was passed to method
		if (start == null)
			// return null if no node passed
			return null;
		// check if there is a right child to the passed node
		if (start.getRightChild() != null) {
			// move to the right child
			start = start.getRightChild();
			// find the farthest left child of that node
			while (start.getLeftChild() != null) {
				start = start.getLeftChild();
			}
			// return the found node
			return start;
		}

		// otherwise, check the parents for successor
		else {
			// store the parent
			parent = start.getParent();
			// continue traversing until reach a left child or root of tree
			while (parent != null && start == parent.getRightChild()) {
				// move the current node to its parent
				start = parent;
				// move the parent to the parent of itself
				parent = parent.getParent();
			}
			// return the found node
			return parent;
		}
	}

	/**
	 * Returns the predecessor of the given word (the word from the dictionary
	 * that lexicographically precedes the given one); it returns an empty
	 * string if the given word has no predecessor. The given word DOES NOT need
	 * to be in the dictionary.
	 */
	public String predecessor(String word) {
		// find the predecessor of the node containing the word
		p = predecessor(find(word));
		// if there is none, return a blank string
		if (p != null)
			// return the word of the predecessor
			return p.getDictEntry().word();
		else
			// otherwise, return blank strinbg
			return "";
	}

	/**
	 * Return the predecessor of the node passed, null if none are.
	 * 
	 * @param toFind
	 * @return predecessor ndoe
	 */
	private OrderedDictionaryNode predecessor(OrderedDictionaryNode start) {
		// check if a node was passed to method
		if (start == null)
			// return null if no node passed
			return null;
		// check if there is a left child to the passed node
		if (start.getLeftChild() != null) {
			// move to the left child
			start = start.getLeftChild();
			// find the farthest right child of that node
			while (start.getRightChild() != null) {
				start = start.getRightChild();
			}
			// return the found node
			return start;
		}

		// otherwise, check the parents for predecessor
		else {
			// store the parent
			parent = start.getParent();
			// continue traversing until reach a right child or root of tree
			while (parent != null && start == parent.getLeftChild()) {
				// move the current node to its parent
				start = parent;
				// move the parent to the parent of itself
				parent = parent.getParent();
			}
			// return the found node
			return parent;
		}
	}
}
