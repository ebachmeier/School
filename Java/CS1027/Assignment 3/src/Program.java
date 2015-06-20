import java.util.StringTokenizer; // import string tokenizer utility

/**
 * Assignment 3
 * 
 * @class Program
 * 
 * This class creates Program objects from passed tokenizer objects by adding the tokens to a list.
 * 
 * @author Eric Bachmeier
 * # 250738776
 * 
 */

public class Program {

	// attributes
	SimpleListADT<SimpleFunction> func;
	
	// constructor
	
	/**
	 * constructor for creating a Program object from the tokenizer objects passed in
	 * 
	 * @param st
	 */
	public Program(StringTokenizer st) {
		// declare a new list to func
		func = new ArraySimpleList<SimpleFunction>();
		// add string tokens to list until there aren't any tokens left
		while (st.hasMoreTokens()){
			func.addToRear(new SimpleFunction(st));
		}
	}
	
	// method
	
	// find method for Program string names
	public SimpleFunction find(String name){
		// return the function corresponding to the passed name
		return func.find(name);
	}

}
