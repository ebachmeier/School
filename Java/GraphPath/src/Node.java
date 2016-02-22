/**
 * This class is for representing and storing the nodes of a graph.
 * 
 * @author Eric Bachmeier
 */
public class Node {

	// ////////// attributes ////////////
	// the unique name for each individual node
	private int nodeName;
	// a boolean mark to keep track of searched and non-searched nodes
	private boolean marked;

	// ////////// constructors ////////////
	/**
	 * Constructor to create an unmarked node with passed integer name
	 * 
	 * @param name
	 *            The name of the node
	 */
	public Node(int name) {
		nodeName = name;
		marked = false;
	}

	// ////////// methods ////////////
	/**
	 * Method for setting the node's mark to a specified value
	 * 
	 * @param mark
	 *            Boolean value whether the mark has been searched or not in
	 *            traversal
	 */
	public void setMark(boolean mark) {
		this.marked = mark;
	}

	/**
	 * Method for returning the mark value of the node called on
	 * 
	 * @return marked The boolen value of the node's mark
	 */
	public boolean getMark() {
		return marked;
	}

	/**
	 * Method for returning the name of the node or vertex
	 * 
	 * @return nodeName The name of the node called on
	 */
	public int getName() {
		return nodeName;
	}
}
