import java.io.BufferedReader;
import java.io.FileReader;
import java.util.StringTokenizer;

/**
 * Class that has various commands to populate a dictionary, and has the main
 * running method.
 * 
 * @author Eric Bachmeier 250738776
 * 
 */

public class Query {

	/**
	 * Main method for initiating the dictionary and performing commands
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		// variables
		String word, definition;

		// create a dictionary tree to store all the words and definitions
		OrderedDictionary dictionary = new OrderedDictionary();

		try {
			// use the BufferedReader class to read the input file line by line
			BufferedReader inFile = new BufferedReader(new FileReader(args[0]));
			// read the first word from the file
			word = inFile.readLine(); // Read the first word
			// keep reading until end of file
			while (word != null) {
				// convert word to lower case so case sensitive
				word = word.toLowerCase();
				// read the definition of above word
				definition = inFile.readLine();
				// chjeck if definition is an audio file
				if (definition.endsWith(".mid") || definition.endsWith(".wav")) {
					// insert the word, audio definition, and type into
					// dictionary
					dictionary.insert(word, definition, 2);
				}
				// check if the definition is an image file
				else if (definition.endsWith(".jpg")
						|| definition.endsWith(".gif")) {
					// insert the word, image definition, and type into
					// dictionary
					dictionary.insert(word, definition, 3);
				}
				// otherwise, the definition must be text
				else {
					// insert the word, text definition, and type into the
					// dictionary
					dictionary.insert(word, definition, 1);
				}
				// read the next line in the file at the end of the loop
				word = inFile.readLine();
			}
		} catch (Exception e) {
			// print error message and termintate execution if any caught
			System.out.println(e.getMessage());
			return;
		}

		// create new StringReader for user commands
		StringReader keyboard = new StringReader();
		// boolean variable to terminate when end is entered
		boolean end = true;

		// main looping body of program
		while (end) {
			// variables
			String command, argument;
			// prompt user for a command response
			StringTokenizer prompt = new StringTokenizer(
					keyboard.read("Enter command: "));
			// store command
			// check to see if a command was entered
			if (prompt.hasMoreElements()) {
				// if it does, separate the command to command and word
				command = prompt.nextToken();
				command = command.toLowerCase();
				// check if there is a word argument for the given comma
			}
			// otherwise, nothing was entered and we have a blank string
			else
				command = "";

			// check if there is a word argument for the given command
			if (prompt.hasMoreElements()) {
				// if it does, separate the word and possible definition from
				// command
				argument = prompt.nextToken();
				argument = argument.toLowerCase();
			}
			// otherwise, nothing was entered and we have a blank string
			else
				argument = null;

			// check if there is a word argument for the given command
			String wordDef;
			if (prompt.hasMoreElements()) {
				wordDef = prompt.nextToken();
				while (prompt.hasMoreElements()) {
					// if it does, concatentate the definition to wordDef
					wordDef = wordDef.concat(" " + prompt.nextToken());
					// check if there is a word argument for the given comma
				}
			}
			// otherwise, nothing was entered and we have a blank string
			else
				wordDef = null;

			// define command
			if (command.compareTo("define") == 0) {
				// print error message if there is no argument
				if (argument == null) {
					System.out.println("Error: command DEFINE needs argument");
				}
				// check if the definition is of type picture
				else if (dictionary.findType(argument) == 3) {
					try {
						// create a PictureViewer to display the definition
						PictureViewer picture = new PictureViewer();
						// display the picture to the screen from definition
						// file name
						picture.show(dictionary.findWord(argument));
						// print error message if picture media is not found
					} catch (MultimediaException e) {
						System.out
								.println("Error: could not find picture definition");
					}
				}
				// check if the definition is of type audio
				else if (dictionary.findType(argument) == 2) {
					try {
						// create a SoundPlayer object to play the audio file
						SoundPlayer sound = new SoundPlayer();
						// play the audio file from file name definition
						sound.play(dictionary.findWord(argument));

						// print error message if audio media is not found
					} catch (MultimediaException e) {
						System.out
								.println("Error: could not find audio definition");
					}
				}

				// check if the word is a normal text definition
				else if (dictionary.findType(argument) == 1) {
					// print the definition of the word
					System.out.println(dictionary.findWord(argument));
				}

				// otherwise, the word must not be in the dictionary
				else {
					System.out
							.println("Error: *IN DEFINE CMD* that word is not in the dictionary");
				}
			}

			// next command
			else if (command.compareTo("next") == 0) {
				// display error message if there is no argument
				if (argument == null) {
					System.out.println("Error: command NEXT needs argument");
				}
				// if there is no successor to display, error message
				else if (dictionary.successor(argument) == "") {
					// check if it is last word
					if (dictionary.findWord(argument) != "") {
						System.out.println("Error: there is no next word");
					}
					// otherwise, it must not be in the dictionary
					else {
						System.out
								.println("Error: the word is not in the dictionary");
					}
				}
				// otherwise, display the successor because it is there
				else {
					System.out.println(dictionary.successor(argument));
				}
			}

			// previous command
			else if (command.compareTo("previous") == 0) {
				// display error message if no argument was given
				if (argument == null) {
					System.out
							.println("Error: command PREVIOUS needs argument");
				}
				// if there is no predecessor to display, error message
				else if (dictionary.predecessor(argument) == "") {
					// check if it is first word
					if (dictionary.findWord(argument) != "") {
						System.out.println("Error: there is no previous word");
					}
					// otherwise, it must not be in the dictionary
					else {
						System.out
								.println("Error: the word is not in the dictionary");
					}
				}
				// otherwise, display the predecessor because it is in the
				// dictionary
				else {
					System.out.println(dictionary.predecessor(argument));
				}
			}

			// add command
			else if (command.compareTo("add") == 0) {
				// display error message if no argument was given
				if (argument == null || wordDef == null) {
					System.out.println("Error: command ADD needs arguments");
				}
				// try to add given word
				else {
					try {
						dictionary.insert(argument, wordDef, 1);
						// display error message if word is already in
						// dictionary
					} catch (DictionaryException e) {
						System.out.println(e.getMessage());
					}
				}
			}

			// delete command
			else if (command.compareTo("delete") == 0) {
				// display error message if no argument was given
				if (argument == null) {
					System.out.println("Error: command DELETE needs argument");
				}
				// try to remove given word
				else {
					try {
						dictionary.remove(argument);
						// display error message if word is not in dictionary
					} catch (DictionaryException e) {
						System.out.println(e.getMessage());
					}
				}
			}

			// list command
			else if (command.compareTo("list") == 0) {
				// display error message if no argument was given
				if (argument == null) {
					System.out.println("Error: command LIST needs argument");
				}
				// find all the words with given prefix
				else {
					try {
						// insert the prefix given into dictionary
						String prefix = argument;
						dictionary.insert(prefix,
								"*" + "DELETE" + prefix + "*", 1);
						// find the successor to this inserted item
						argument = dictionary.successor(prefix);
						// check if the successor starts with the prefix
						while (argument.startsWith(prefix)) {
							// if it does, print it in the list
							System.out.print(argument);
							// get the next successor
							argument = dictionary.successor(argument);
							if (argument.startsWith(prefix)
									&& (argument.length() > 0 || argument != ""))
								System.out.print(", ");
						}
						System.out.println();
						// remove the temporaryily added prefix
						dictionary.remove(prefix);
					} catch (DictionaryException e) {
						System.out.println(e.getMessage());
					}
				}
			}

			// end command
			else if (command.compareTo("end") == 0) {
				System.out.println("");
				System.out.println("Thank you for using the dictionary.");
				System.out.println("\t Eric Bachmeier");
				// set the program flag to false to end execution
				end = false;
			}
			// if an invalid command was entered throughout execution, display
			// an error
			// message
			else {
				System.out.println("Error: invalid command");
				System.out
						.println("Valid commands consist of: define, add, delete, next, previous, list, or end");
			}
			System.out.println(""); // new line after each command
		}
		// terminate main method
		return;
	}
}