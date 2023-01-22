/**
 * Program Name:    DivisionByZeroException.java
 * Purpose:     	DivisionByZeroException will be thrown if the user enters a fraction with a denominator of zero
 * @author    		Seolan Jin, Junyeong Jo
 * @version     	1.0
 * @since           Jul. 31, 2021
 */

public class DivisionByZeroException extends Exception
{
	/**
	 * Constructs a new DivisionByZeroException object initializes attribute
	*/
	public DivisionByZeroException() {
		super("Error: denominator cannot be zero");
	}

}
//End of class