/**
 * Program Name:    EmptyOperandException.java
 * Purpose:     	This exception will be thrown 
 * 					if the user has failed to enter a value in either the numerator or denominator text field and then presses the “Build Fraction” button
 * @author    		Seolan Jin, Junyeong Jo
 * @version     	1.0
 * @since           Jul. 31, 2021
 */

public class EmptyOperandException extends Exception
{
	/**
	 * Constructs a new EmptyOperandException object initializes attribute
	*/
	public EmptyOperandException() {
		super("Error: empty input field");
	}
}
//End of class