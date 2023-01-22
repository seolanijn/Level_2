/**
 * Program Name:    LongOperandException.java
 * Purpose:     	LongOperandException will be thrown if either the numerator or the denominator 
 * 					text fields exceed a String length of 10 characters
 * @author    		Seolan Jin, Junyeong Jo
 * @version     	1.0
 * @since           Jul. 31, 2021
 */

public class LongOperandException extends Exception
{
	/**
	 * Constructs a new LongOperandException object initializes attribute
	*/
	public LongOperandException() {
		super("Error: operand entered exceeds int capacity");
	}
}
//End of class