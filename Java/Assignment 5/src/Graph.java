/**
 * This class represents an undirected graph of nodes and edges.
 * 
 * @author Eric Bachmeier
 */

import java.util.*;

public class Graph implements GraphADT {

	// ////////// attributes ////////////
	// array for the nodes stored
	private Node nodes[];
	// matrix for the edges
	private Edge edges[][];
	// number of nodes in the graph
	private int n;
	// names of the nodes
	private int firstName, secondName;

	// ////////// constructors ////////////
	/**
	 * Constructor to create a graph with n nodes and no edges
	 */
	public Graph(int n) {
		this.n = n;
		// initialize a new nodes array
		this.nodes = new Node[n];
		// populate the array with named Nodes
		for (int x = 0; x < n; x++)
			nodes[x] = new Node(x);
		// initialize new matrix to store edges
		this.edges = new Edge[n][n];
	}

	// ////////// methods ///////////
	/**
	 * Method to add an edge connecting the two nodes with no label. Throw a
	 * Throw GraphException if one of the nodes doesn't exist or the edge
	 * already exists
	 * 
	 * @param u
	 *            The first endpoint
	 * @param v
	 *            The second endpoint
	 * @param edgeType
	 *            The type of edge free or toll
	 */
	public void insertEdge(Node u, Node v, String edgeType)
			throws GraphException {
		// declare and initialize variables for the names of the two nodes
		firstName = u.getName();
		secondName = v.getName();
		// check if the nodes exist or not
		if (firstName < 0 || firstName >= n || secondName < 0
				|| secondName >= n)
			throw new GraphException(
					"Error: *insertEdge* node(s) u and/or v could not be found in the graph");
		// check if edge exists between the two nodes
		if (edges[firstName][secondName] != null
				|| edges[secondName][firstName] != null)
			throw new GraphException(
					"Error: *insertEdge* there is already an edge here");
		// now add the edge to the matrix if no edge is already there
		edges[firstName][secondName] = new Edge(u, v, edgeType);
		edges[secondName][firstName] = new Edge(v, u, edgeType);
	}

	/**
	 * Method for returning the node with given name. Throw GraphException if
	 * the given node does not exist
	 * 
	 * @param name
	 *            The name of the searched for node
	 * @return the name of the give node
	 */
	public Node getNode(int name) throws GraphException {
		// check if node exists in graph
		if (name < 0 || name >= n)
			throw new GraphException(
					"Error: *getNode* the Node doesnt not exist in the graph");
		// return the name of the node passed
		return nodes[name];
	}

	/**
	 * Method for returning an Iterator storing all incident edges on Node u,
	 * null if there are none.
	 * 
	 * @param u
	 *            The Node for checking edges
	 * @return an Iterator with all incident edges on Node u
	 */
	public Iterator<Edge> incidentEdges(Node u) throws GraphException {
		// store the name of the node
		firstName = u.getName();
		// check to make sure node exists with name
		if (firstName < 0 || firstName >= n)
			throw new GraphException(
					"Error: *incidentEdges* the Node doesnt not exist in the graph");
		// create a stack of possible edges connecting passed node
		Stack<Edge> edgesTemp = new Stack<Edge>();
		// iterate matrix looking for incident edges
		for (int x = 0; x < n; x++) {
			if (edges[firstName][x] != null)
				// add the edge to the top of the stack if it exists
				edgesTemp.push(edges[firstName][x]);
		}
		// if the temp edges list is not empty, return iterator for it
		if (edgesTemp.empty())
			return null;
		// return an interator for the stack of edges
		return edgesTemp.iterator();
	}

	/**
	 * Method for returning the edge connecting two nodes. Throws GraphException
	 * if there is no edge.
	 * 
	 * @param u
	 *            The first node endpoint
	 * 
	 * @param v
	 *            The second node
	 * 
	 * @return the edge connecting the two nodes
	 */
	public Edge getEdge(Node u, Node v) throws GraphException {
		// declare and initialize variables for the names of the two nodes
		firstName = u.getName();
		secondName = v.getName();
		// check if the nodes exist
		if (firstName < 0 || firstName >= n || secondName < 0
				|| secondName >= n)
			throw new GraphException(
					"Error: *getEdge* node(s) u and/or v could not be found in the graph");
		// check if there is an edge connecting the two nodes
		if (!areAdjacent(u, v))
			throw new GraphException(
					"Error: *getEdge* there is no edge connecting these two nodes");
		// if there is an edge between two valid nodes, return the edge
		return edges[firstName][secondName];
	}

	/**
	 * Method returns true if the two nodes are adjacent, false otherwise.
	 * 
	 * @param u
	 *            The first node
	 * 
	 * @param v
	 *            The second node
	 * 
	 * @return boolean true or false for adjacency
	 */
	public boolean areAdjacent(Node u, Node v) throws GraphException {
		// declare and initialize variables for the names of the two nodes
		firstName = u.getName();
		secondName = v.getName();
		// check if the nodes exist
		if (firstName < 0 || firstName >= n || secondName < 0
				|| secondName >= n)
			throw new GraphException(
					"Error: *getEdge* node(s) u and/or v could not be found in the graph");
		// these nodes are not adjacent if there is no edge
		if (edges[firstName][secondName] == null)
			return false;
		return true;
	}
}
