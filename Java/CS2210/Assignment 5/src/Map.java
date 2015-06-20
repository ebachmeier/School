/**
 * This class represents a road map that is to be stored in a graph.
 * 
 * @author Eric Bachmeier 250738776
 */

import java.util.*;
import java.io.*;

public class Map {

	// ////////// attributes ////////////
	// a graph representing the road map
	private Graph map;
	// stack for storing a path
	private Stack<Node> s;
	// start and end nodes
	private Node start, dest;
	// counter for the number of toll roads we can use
	private int tollUse;

	// ////////// constructors ////////////
	/**
	 * Constructor for building a road map from a given input file. Throws a
	 * MapException if the file does not exist
	 * 
	 * @param inputFile
	 *            The text file containing the road map information
	 */
	public Map(String inputFile) throws MapException {

		try {
			// initialize the stack that will store the path
			s = new Stack<Node>();
			// declare and initialize the reader to read inputFile
			BufferedReader inFile = new BufferedReader(
					new FileReader(inputFile));
			// read the first line (GUI param) and discard
			inFile.readLine();

			// read the width of the map and store the integer value of the
			// string read by casting it
			int width = Integer.parseInt(inFile.readLine());

			// read the length of the map and store the integer value of the
			// string read by casting it
			int length = Integer.parseInt(inFile.readLine());

			// initialize a new graph with the proper number of nodes n
			map = new Graph(length * width);

			// read the number of toll roads we are allowed use in creating our
			// path and store the integer value of the string by casting it
			tollUse = Integer.parseInt(inFile.readLine());

			// read the first line of the map from inputFile
			String lineRead = inFile.readLine();

			// loop through the length of the map
			for (int y = 0; y < (length * 2) - 1; y++) {
				// loop through width of map
				for (int x = 0; x < (width * 2) - 1; x++) {
					// if it is an even row
					if (y % 2 == 0) {
						// if it is an even column
						if (x % 2 == 0) {

							// check if we have a start or destination node
							// position from line
							if (lineRead.charAt(x) == 's')
								// set start to the name of the start node
								start = map.getNode((y / 2 * width) + (x / 2));
							else if (lineRead.charAt(x) == 'e')
								// set the dest(exit) node name
								dest = map.getNode((y / 2 * width) + (x / 2));
						}
						// checking on odd columns
						else {
							// horizontally check if it is a free or toll road
							if (lineRead.charAt(x) == 'h') {
								// insert an edge for these two nodes, from left
								// node to right node of road position
								map.insertEdge(
										map.getNode((y / 2 * width)
												+ ((x - 1) / 2)),
										map.getNode((y / 2 * width)
												+ ((x + 1) / 2)), "toll");
								// insert edge for a free horizontal road
							} else if (lineRead.charAt(x) == '-') {
								map.insertEdge(
										map.getNode(((y / 2) * width)
												+ ((x - 1) / 2)),
										map.getNode(((y / 2) * width)
												+ ((x + 1) / 2)), "free");
							}

						}
					}
					// check even columns
					else {
						// check vertically on even columns for the free and
						// toll roads
						if (x % 2 == 0) {
							if (lineRead.charAt(x) == 'v') {
								// insert an edge for these two nodes for above
								// to below the road edge position
								map.insertEdge(
										map.getNode(((y - 1) / 2 * width)
												+ (x / 2)),
										map.getNode(((y + 1) / 2 * width)
												+ (x / 2)), "toll");
								// insert vertical edge for free road
							} else if (lineRead.charAt(x) == '|') {
								map.insertEdge(
										map.getNode(((y - 1) / 2 * width)
												+ (x / 2)),
										map.getNode(((y + 1) / 2 * width)
												+ (x / 2)), "free");
							}
						}
					}
				}

				// read the next line after going through width fully
				lineRead = inFile.readLine();

			}
			inFile.close(); // close reader
		}

		// catch any errors in reading file, throw a MapException
		catch (Exception e) {
			throw new MapException(
					"Error: *Map construct.* input file was not found");
		}
	}

	/**
	 * Method for returning a reference to the road map. Throws a MapException
	 * if the graph is not already defined.
	 * 
	 * @return reference to graph called upon
	 */
	public Graph getGraph() throws MapException {
		if (map != null)
			// return the map if there is one
			return map;
		else
			throw new MapException(
					"Error: *getGraph* the graph has not yet been defined");
	}

	/**
	 * Method that returns an Iterator for the nodes along the path.
	 * 
	 * @return the iterator for the path, or null if the path does not exist
	 */
	public Iterator<Node> findPath() {
		// start checking for a path to end from the starting node
		pathway(start);
		// if there is a path, return the iterator
		if (s.empty())
			return null;
		return s.iterator();
	}

	/**
	 * A method that does a depth first search traversal (DFS) for finding a
	 * path from start to destination.
	 * 
	 * @param u
	 *            The starting node of the search
	 * @return boolean true or false if a path was successfully found or not
	 */
	private boolean pathway(Node u) {

		// push the current start node to the stack s
		s.push(u);

		// if the first node is also the end node, then the path is complete
		if (u == dest) {
			return true;
		}

		// if path is longer than one, keep traversing
		else {
			// mark the start node as visited using the setMark to true
			u.setMark(true);
			try {
				// iterator for all incident edges on node u
				Iterator<Edge> incident = map.incidentEdges(u);

				// search for all incident edges on u
				while (incident.hasNext()) {
					Edge discovery = incident.next();
					// check if the edge is the proper path
					if (discovery.getLabel() != "discovery") {
						// check if this edge is free or toll road
						if (discovery.getType() == "free") {
							// check if endpoint of this edge has been visited
							// (marked) yet
							if (!(discovery.secondEndpoint().getMark())) {
								// set the labels of both edges to discovery and
								// recursively search second endpoint node
								discovery.setLabel("discovery");
								map.getEdge(discovery.secondEndpoint(), u)
										.setLabel("discovery");
								if (pathway(discovery.secondEndpoint()))
									return true;
							}
							// must be toll road at this point
						} else {
							// if we come across a toll road, check how many
							// toll road dollars we have left
							if (tollUse > 0) {
								// check if endpoint of this edge has been
								// visited (marked) yet
								if (!discovery.secondEndpoint().getMark()) {
									// set the labels of both edges to discovery
									// and recursively search second endpoint
									// node
									discovery.setLabel("discovery");
									map.getEdge(discovery.secondEndpoint(), u)
											.setLabel("discovery");
									// subtract one dollar from toll counter
									tollUse--;
									if (pathway(discovery.secondEndpoint()))
										return true;
								}
							}
						}
					}
				}

				// if we reach a dead end, make a new iterator
				Iterator<Edge> pre = map.incidentEdges(u);
				// find the path to get to this current node
				while (pre.hasNext()) {
					Edge back = pre.next();
					if (back.getLabel() == "discovery") {
						// set the labels on both edges back to null
						back.setLabel(null);
						map.getEdge(back.secondEndpoint(), u).setLabel(null);

						// if it was a toll road, add amount back to counter
						if (back.getType() == "toll") {
							tollUse++;
						}
						break; // break once we get to a free road now
					}
				}

				// unmark the current node u to be unvisited
				u.setMark(false);
				// remove the node from the stack and return to previous node
				s.pop();
				return false;

			} catch (GraphException e) {
				System.out.println(e.getMessage());
			}
		}
		return false;
	}
}
