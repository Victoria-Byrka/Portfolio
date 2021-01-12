
/*
 *	Given 2 user inputted bit strings, this program performs 
 *      a Cyclic Redundancy Check in Java.  
 *
 *	Victoria Byrka
 *
 * 	November 8, 2020
 */

import java.util.*;

public class CRCProtocol {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

		// store user input for M(x)
		System.out.println("Please enter a bit string for M(x):");
		String mX = in.next();

		// store user input for G(x)
		System.out.println("Please enter a bit string for G(x):");
		String gX = in.next();

		System.out.println("M(x) = " + mX);
		System.out.println("G(x) = " + gX);

		ArrayList<String> zeros = new ArrayList<String>();

		// adds k 0's to the end of M(x)
		int zerosToAdd = gX.length() - 1;
		for (int i = 0; i < zerosToAdd; i++) {
			zeros.add("0");
		}

		String zerosP = zeros.toString().replace(" ", "").replace("[", "").replace("]", "").replace(",", "");
		String mXPrime = mX + zerosP;

		// returns P(x)
		System.out.println("P(x) = " + mX + sender(mX, gX));

		// takes P(x) and checks if it is error free or not
		System.out.println(reciever(mXPrime, gX));

		in.close();
	}

	// method to compute the CRC remainder of M(x) and G(x)
	public static String sender(String mX, String gX) {

		ArrayList<String> temp = new ArrayList<String>();

		for (int i = 1; i < mX.length(); i++) {
			for (int j = 1; j < gX.length(); j++) {

				// XOR checking
				if (mX.charAt(i) == '1' && gX.charAt(j) == '1' || mX.charAt(i) == '0' && gX.charAt(j) == '0') {
					temp.add("0");
				} else if (mX.charAt(i) == '1' && gX.charAt(j) == '0' || mX.charAt(i) == '0' && gX.charAt(j) == '1') {
					temp.add("1");
				}

			}
		}
		int lengthOfRemainder = gX.length() - 1;

		// remove symbols from arraylist
		String remainder = temp.toString().replace(" ", "").replace("[", "").replace("]", "").replace(",", "");

		// take substring from temp that is correct size
		String result = remainder.substring(temp.size() - lengthOfRemainder, temp.size());

		return result;
	}

	// method to determine if P(x) is error free (divide M'(x) by G(x))
	public static String reciever(String mXPrime, String gX) {
		String errorDet = "";
		// call sender method using M(x) prime instead of M(x)
		String result = sender(mXPrime, gX);
		// if the result is not all 0's, an error has been detected
		if (result.contains("1")) {
			errorDet = "Error Detected!";
		} else {
			errorDet = "Error Not Detected!";
		}
		return errorDet;
	}
}
