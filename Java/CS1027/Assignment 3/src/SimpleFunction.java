import java.util.StringTokenizer; // import string tokenizer utility

/**
 * Assignment 3
 * 
 * @class SimpleFunction
 * 
 *        This class creates SimpleFunction objects from text files and
 *        evaluates them with numbers passed in from other stacks and programs.
 * 
 * @author Eric Bachmeier 
 * # 250738776
 * 
 */

public class SimpleFunction {

	// attributes
	private SimpleListADT<String> arguments;
	private SimpleListADT<String> operands;
	private String name, current, s;
	private int test;
	private SimpleFunction temp;
	private int first, second;

	// constructor

	/**
	 * constructor for creating a SimpleFunction object, separating the operand
	 * and argument strings.
	 * 
	 * @param input
	 */
	public SimpleFunction(StringTokenizer input) {

		// initialize arguments and operands lists
		arguments = new ArraySimpleList<String>();
		operands = new ArraySimpleList<String>();

		// name is the first token
		name = input.nextToken();
		// current is the current token item of String
		current = input.nextToken();

		// add argument tokens to arguments list
		while (!current.equals("{")) {
			arguments.addToRear(current);
			current = input.nextToken(); // next token
		}

		if (current.equals("{")) {
			current = input.nextToken();
		}

		// add operand tokens to operands list
		while (!current.equals("}")) {
			operands.addToRear(current);
			current = input.nextToken();
		}
	}

	// methods

	/**
	 * eval method with one parameter takes the stack of numbers and evaluates
	 * the numbers according to the function it is called upon.
	 * 
	 * @param stack
	 */
	public void eval(StackADT<Integer> stack) {

		// initialize new list of Integers called vals to store the numbers from
		// the stack
		SimpleListADT<Integer> vals = new ArraySimpleList<Integer>();

		// add all of the argument integer values to the vals list
		for (int x = 0; x < arguments.size(); x++) {
			vals.addToRear(stack.pop());
		}

		// evaluate the operands
		for (int i = 0; i < operands.size(); i++) {

			// current operand is string s
			s = operands.get(i);

			// push all integers to the stack to be used for calculations
			if (arguments.indexOf(s) > -1) {
				stack.push(vals.get(arguments.indexOf(s)));
			}

			// pop the two numbers from the stack and perform addition
			if (s.equals("+")) {
				second = stack.pop();
				first = stack.pop();
				stack.push(first + second);
			}

			// pop the two numbers from the stack and perform subtraction
			if (s.equals("-")) {
				second = stack.pop();
				first = stack.pop();
				stack.push(first - second);
			}

			// pop the two numbers from the stack and perform multiplication
			if (s.equals("*")) {
				second = stack.pop();
				first = stack.pop();
				stack.push(first * second);
			}
		}
	}

	/**
	 * eval method with two parameters takes the stack of numbers and evaluates
	 * the numbers according to the function it is called upon, and uses the
	 * passed program to create a sub-function to evaluate inside.
	 * 
	 * @param stack
	 * @param prog
	 */
	public void eval(StackADT<Integer> stack, Program prog) {

		// initialize new list of Integers called vals to store the numbers from
		// the stack
		SimpleListADT<Integer> vals = new ArraySimpleList<Integer>();

		// add all of the argument integer values to the vals list
		for (int x = 0; x < arguments.size(); x++) {
			vals.addToRear(stack.pop());
		}

		// evaluate the operands
		for (int i = 0; i < operands.size(); i++) {

			// current operand is string s
			s = operands.get(i);

			// push all integers to the stack to be used for calculations
			if (arguments.indexOf(s) > -1) {
				stack.push(vals.get(arguments.indexOf(s)));
			}

			// pop the two numbers from the stack and perform addition
			if (s.equals("+")) {
				second = stack.pop();
				first = stack.pop();
				stack.push(first + second);
			}

			// pop the two numbers from the stack and perform subtraction
			if (s.equals("-")) {
				second = stack.pop();
				first = stack.pop();
				stack.push(first - second);
			}

			// pop the two numbers from the stack and perform multiplication
			if (s.equals("*")) {
				second = stack.pop();
				first = stack.pop();
				stack.push(first * second);
			}

			// if the current operand is not in the arguments list, test if its
			// an integer
			if (arguments.indexOf(s) < 0) {
				try {
					// try to parse the current operand to an integer
					Integer test = Integer.parseInt(s);
				} catch (NumberFormatException e) {
					// if its not an integer, create a new SimpleFunction from
					// that point in the Program
					temp = prog.find(s);
					// recursively call eval on this function, evaluating it
					// inside the main function
					temp.eval(stack);
				}
			}
		}

	}

	// toString method to retrieve the name of the function
	public String toString() {
		return name;
	}

}
