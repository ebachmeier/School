/**
 * Class that implements nodes to help construct a binary search tree
 * 
 * @author Eric Bachmeier 250738776
 * 
 */

public class OrderedDictionaryNode {

	// variables
	DictEntry entry = null;
	OrderedDictionaryNode leftChild = null;
	OrderedDictionaryNode rightChild = null;
	OrderedDictionaryNode nodeParent = null;

	/**
	 * Constructor for a new node from a DictEntry object with no parent
	 * 
	 * @param data
	 */
	public OrderedDictionaryNode(DictEntry data) {
		this.entry = data;
		this.leftChild = null;
		this.rightChild = null;
		this.nodeParent = null;
	}

	/**
	 * Constructor for a new node from a DictEntry object with a pointer to its
	 * parent node
	 * 
	 * @param parent
	 * @param data
	 */
	public OrderedDictionaryNode(OrderedDictionaryNode parent, DictEntry data) {
		this.entry = data;
		this.nodeParent = parent;
		leftChild = null;
		rightChild = null;
	}

	/**
	 * @return the DictEntry object for that given node
	 */
	public DictEntry getDictEntry() {
		return entry;
	}

	/**
	 * @return the left child of the node
	 */
	public OrderedDictionaryNode getLeftChild() {
		return leftChild;
	}

	/**
	 * @return the right child of the node
	 */
	public OrderedDictionaryNode getRightChild() {
		return rightChild;
	}

	/**
	 * @return the parent of the passed node
	 */
	public OrderedDictionaryNode getParent() {
		return nodeParent;
	}

	/**
	 * Set a DictEntry object to a node
	 * 
	 * @param root
	 */
	public void setRoot(DictEntry root) {
		this.entry = root;
	}

	/**
	 * Set the left child of a node to a data object
	 * 
	 * @param leftC
	 */
	public void setLeftChild(OrderedDictionaryNode leftC) {
		this.leftChild = leftC;
	}

	/**
	 * Set the right child of a node to a data object
	 * 
	 * @param rightC
	 */
	public void setRightChild(OrderedDictionaryNode rightC) {
		this.rightChild = rightC;
	}

	/**
	 * Set a DictEntry object to store in the parent of a node
	 * 
	 * @param parent
	 */
	public void setParent(OrderedDictionaryNode parent) {
		this.nodeParent = parent;
	}
}
