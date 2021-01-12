
/*
 * 	This program reads an input file with a forwarding database of a bridge
 *	with 4 ports and an input file containing random frames with 
 * 	source and destination MAC addresses and the port number of the bridge. 
 *	Given the input files, this program decides to either forward, discard, or
 *	broadcast a frame. 
 * 
 * 	Victoria Byrka
 * 
 * 	November 8, 2020
 * 
 */
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;
import java.util.Scanner;

public class BridgeProcess {
	public static void main(String[] args) throws IOException {

		ArrayList<String> file1 = new ArrayList<>();
		ArrayList<String> file2 = new ArrayList<>();
		String filename1 = "BridgeFDB.txt";
		String filename2 = "RandomFrames.txt";

		// read in first file
		try (Scanner s1 = new Scanner(new FileReader(filename1))) {
			while (s1.hasNext()) {
				file1.add(s1.nextLine());
			}
		}

		// read in second file
		try (Scanner s2 = new Scanner(new FileReader(filename2))) {
			while (s2.hasNext()) {
				file2.add(s2.nextLine());
			}
		}

		// create output file
		PrintWriter BridgeOutput = new PrintWriter("BridgeOutput.txt");

		String frameDesc = "";
		ArrayList<String> temp = new ArrayList<>();

		int index = 0;
		for (int i = 0; i < file2.size(); i++) {
			BridgeOutput.print(file2.get(i) + "    ");
			index++;

			// add source address of file2 to temporary arraylist
			if (index == 1) {
				temp.add(file2.get(i));
			}

			// if the frame is not in FDB it is broadcasted
			if (!file1.contains(file2.get(i))) {
				frameDesc = "Broadcast";
			}

			// if the source address is already in the array, discarded
			if (temp.contains(file2.get(i))) {
				frameDesc = "Discarded";
			}

			// if source and dest frames are in FDB check what to do with it
			if (i < file2.size() - 1 && i > 0) {
				if (file1.contains(file2.get(i)) && file1.contains(file2.get(i + 1)) && file1.contains(file2.get(i - 1))
						&& !temp.contains(file2.get(i))) {
					if (file2.get(i).equals("1")) {
						frameDesc = "Forwarded on port 2";
					} else if (file2.get(i).equals("2")) {
						frameDesc = "Forwarded on Port 3";
					} else if (file2.get(i).equals("3")) {
						frameDesc = "Forwarded on port 4";
					} else {
						frameDesc = "Discarded";
					}
				}
			}

			// if we reach port number, output line results and print new line
			if (index == 3) {
				BridgeOutput.print(frameDesc);
				BridgeOutput.println("");
				index = 0; // reset index
			}
		}

		BridgeOutput.close();
	}

}
