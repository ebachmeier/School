/* 
 * Eric Bachmeier
 * 
 * This class implements all the methods needed by algorithm computerPlay
 * */

public class TicTacToe {

	// fields
	private char[][] gameBoard;
	private int dimension, k;

	// final constant for new dictionary size
	private final int DICT_SIZE = 2503;

	// constructor
	public TicTacToe(int board_size, int inline, int max_levels) {
		this.dimension = board_size;
		this.k = inline;
		// initialize gameBaord
		gameBoard = new char[board_size][board_size];
		for (int y = 0; y < board_size; y++) {
			for (int x = 0; x < board_size; x++) {
				// assign a blank character to every position
				gameBoard[x][y] = ' ';
			}
		}
	}

	// methods

	// method to create a new empty dictionary
	public Dictionary createDictionary() {
		return new Dictionary(DICT_SIZE);
	}

	//
	public int repeatedConfig(Dictionary configurations) {
		String config = "";
		for (int y = 0; y < dimension; y++) {
			for (int x = 0; x < dimension; x++) {
				// append each character to config string
				config += gameBoard[x][y];
			}
		}
		// return the find output of that config key
		return configurations.find(config);
	}

	//
	public void insertConfig(Dictionary configurations, int score) {
		String config = "";
		for (int y = 0; y < dimension; y++) {
			for (int x = 0; x < dimension; x++) {
				// append each character to config string
				config += gameBoard[x][y];
			}
		}
		try {
			// try inserting the pair into the dictionary
			configurations.insert(new DictEntry(config, score));
		} catch (DictionaryException e) {
			e.printStackTrace();
		}
	}

	// stores the symbol into the gameBoard
	public void storePlay(int row, int col, char symbol) {
		gameBoard[row][col] = symbol;
	}

	// returns true only if the square is empty
	public boolean squareIsEmpty(int row, int col) {
		if (gameBoard[row][col] == (' ')) {
			return true;
		} else
			return false;
	}

	// returns true if there are k number of adjacent symbols
	public boolean wins(char symbol) {
		// check diagonals down right
		int adj = 0;
		for (int y = 0; y <= dimension - k; y++) {
			for (int x = 0; x <= dimension - k; x++) {
				adj = 0;
				for (int i = 0; i <= k - 1; i++) {
					if (gameBoard[x + i][y + i] == symbol) {
						adj += 1;
					} else
						adj = 0;
				}
				if (adj == k) {
					return true;
				}
			}
		}

		// check diagonals down left
		adj = 0;
		for (int y = 0; y <= dimension - k; y++) {
			for (int x = dimension - 1; x >= k -1; x--) {
				adj = 0;
				for (int i = 0; i <= k - 1; i++) {
					if (gameBoard[x - i][y + i] == symbol) {
						adj += 1;
					} else
						adj = 0;
				}
				if (adj == k) {
					return true;
				}
			}
		}

		// check rows
		adj = 0;
		for (int y = 0; y < dimension; y++) {
			adj = 0;
			for (int x = 0; x < dimension; x++) {
				if (gameBoard[x][y] == symbol) {
					adj += 1;
				} else
					adj = 0;
				if (adj == k) {
					return true;
				}
			}
		}
		adj = 0;
		// check columns
		for (int x = 0; x < dimension; x++) {
			adj = 0;
			for (int y = 0; y < dimension; y++) {
				if (gameBoard[x][y] == symbol) {
					adj += 1;
				} else
					adj = 0;
				if (adj == k) {
					return true;
				}
			}
		}
		return false;
	}

	// return true if there are no empty positions left
	public boolean isDraw() {
		for (int y = 0; y < dimension; y++) {
			for (int x = 0; x < dimension; x++) {
				if (gameBoard[x][y] == ' ') {
					return false;
				}
			}
		}
		return true;
	}

	// returns value for specific outcomes
	public int evalBoard() {
		// computer wins
		if (wins('O') == true)
			return 3;
		// human wins
		if (wins('X'))
			return 0;
		// draw
		if (isDraw() == true)
			return 2;
		// game undecided
		else
			return 1;
	}

}
