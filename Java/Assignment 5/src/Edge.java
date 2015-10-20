/**
 * This class is for representing the edge of a graph.
 * 
 * @author Eric Bachmeier
 */
public class Edge {

	// ////////// attributes ////////////
	// the first and second endpoints of an edge
	private Node first, second;
	// Strings for the type of road and a label for if there is a discovery or
	// not
	private String roadType, label;

	// ////////// constructors ////////////
	/**
	 * Constructor for an edge with two endpoints and road type / edge type
	 * 
	 * @param u
	 *            The beginning of the edge
	 * @param v
	 *            The endpoint of the edge
	 * @param type
	 *            The type of road ie. toll or free
	 */
	public Edge(Node u, Node v, String type) {
		first = u;
		second = v;
		roadType = type;
		label = "";
	}

	// ////////// methods ////////////
	/**
	 * Method for returning the first endpoint of an edge
	 * 
	 * @return first The first endpoint of edge called on
	 */
	public Node firstEndpoint() {
		return first;
	}

	/**
	 * Method for returning the second endpoint of an edge
	 * 
	 * @return second The second endpoint of edge called on
	 */
	public Node secondEndpoint() {
		return second;
	}

	/**
	 * Method for returning the type of edge / road
	 * 
	 * @return roadType The type of road whether it is free or toll
	 */
	public String getType() {
		return roadType;
	}

	/**
	 * Method for setting the label of an edge to discovery or back depending if
	 * a path is found or not
	 */
	public void setLabel(String label) {
		this.label = label;
	}

	/**
	 * Method for returning the label of an edge
	 * 
	 * @return label The label of the edge called upon
	 */
	public String getLabel() {
		return label;
	}
}
