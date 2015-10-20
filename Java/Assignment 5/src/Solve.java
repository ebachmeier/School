import java.util.*;
import java.io.*;

public class Solve {

	public static void main(String[] args) {
		Node u, v;
		DrawMap display;
		int delay = 0;

		if (args.length != 1)
			System.out.println("Usage: java Solve inputFile");
		else {
			if (args.length > 0)
				delay = Integer.parseInt(args[0]);

			BufferedReader inText = new BufferedReader(new InputStreamReader(
					System.in));
			System.out.println("Enter map number to test ");
			String line = "";
			try {
				line = inText.readLine();
			} catch (IOException e1) {
				e1.printStackTrace();
			}

			if (line.equals("") || line == null)
				line = "0";

			String fileName = "map" + line + ".txt";

			display = new DrawMap(fileName);
			try {
				Map streetMap = new Map(fileName);

				Iterator solution = streetMap.findPath();

				try {
					System.out.println("Press a key to start");
					new java.util.Scanner(System.in).nextLine();
				} catch (Exception exo) {
					exo.printStackTrace();
				}

				if (solution != null) {
					if (solution.hasNext())
						u = (Node) solution.next();
					else
						return;
					while (solution.hasNext()) {
						v = (Node) solution.next();
						Thread.sleep(delay);
						display.drawEdge(u, v);
						u = v;
					}
				} else {
					System.out.println("No solution was found");
					System.out.println("");
				}

				System.out.println("Press a key to finish");
				new java.util.Scanner(System.in).nextLine();

			} catch (MapException e) {
				System.out.println(e.getMessage());
				System.out.println("Error reading input file");
			} catch (Exception ex) {
				System.out.println(ex.getMessage());
			}

			display.dispose();
			System.exit(0);
		}
	}
}
