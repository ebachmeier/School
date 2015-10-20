/* 
 * Assignment 2
 * 
 * MakeFractal Class
 * 
 * Eric Bachmeier
 * 
 * This class contains the methods to make a complex final fractal from the iterations. 
 */

import java.util.Arrays;

public class MakeFractal {
	private final static int NOT_FOUND = -1;
	private String alphaNumeric;
	private String computedFractal; // the initial string is the axion
	private String initialAxion; // the initial string is the axion
	private Integer index, numSymbols, n, size;
	private String[] symbols;
	private String[] rules;
	private Integer charsPerLine = 60;
	private String x, tempFractal;
	boolean test;

	// constructor
	public MakeFractal(String[] symbols, Integer numSymbols,
			String initialAxion, String[] rules, Integer n) {
		this.numSymbols = numSymbols;
		this.symbols = new String[this.numSymbols];
		this.rules = new String[this.numSymbols];
		for (int i = 0; i < this.numSymbols; i++) {
			this.symbols[i] = symbols[i];
			this.rules[i] = rules[i];
		}
		this.computedFractal = initialAxion; // the initial string is the axion
		this.n = n;
	}

	public String buildFractal() {
		System.out.println("In buildFractal\n");
		// print out symbols and their production rules
		System.out.println("Symbol Table");
		for (int i = 0; i < numSymbols; i++) {
			System.out.println("symbol(" + i + ")=" + symbols[i] + "   rule("
					+ i + ")=" + rules[i] + "\n");
		}

		// create a new stack s to store String elements
		StackADT<String> s = new LinkedStack<String>();

		// the computedFractal is the axion for n=0 as assigned by Constructor
		for (int it_no = 1; it_no < n; it_no++) {
			// loop through previous iteration for each new interation
			for (int i = 0; i < computedFractal.length(); i++) {
				// get current character and assign it to x
				x = Character.toString(computedFractal.charAt(i));
				test = false; // test variable for assigning either a rule OR just pushing character
				for (int j = 0; j < symbols.length; j++) {
					if (in(x,symbols).equals(j)){
						// push corresponding rule 
						s.push(rules[j]);
						test = true;
					} 
				}
				// push just the current symbol if no rule was pushed
				if (test == false)
					s.push(x);
			}
			
			// variable for stack size
			int stacksize = s.size();
			// take fractal from stack and make a string of the fractal
			for (int k = 0; k < stacksize; k++) {
				if (k == 0)
					tempFractal = s.pop();
				else
					tempFractal = s.pop() + tempFractal;
			}
			computedFractal = tempFractal; // assign back to computedFractal
			tempFractal = ""; // reset tempFractal blank

		} /* end of iterations */
		return computedFractal;
	}

	public Integer in(String alphaNumeric, String[] symbols) {
		for (int i = 0; i < symbols.length; i++) {
			System.out.println("i=" + i + " alphaNumeric=" + alphaNumeric
					+ " symbols[" + i + "]=" + symbols[i]);
			if (alphaNumeric.equals(symbols[i]))
				return (i);
		}
		return (NOT_FOUND);
	}

	public void prettyPrint() {
		String str = computedFractal;
		size = str.length();
		System.out.println("prettyPrint:");
		System.out.println("size=" + size);
		// System.out.println("str=" + str);
		// System.out.println("charsPerLine=" + charsPerLine);
		while (charsPerLine < size) {
			// print out substrings of str of length charsPerLine
			System.out.println(str.substring(0, charsPerLine - 1));
			str = str.substring(charsPerLine, size);
			size = str.length();
		}
		// print last bit of str
		System.out.println(str);
	}

} // MakeFractal