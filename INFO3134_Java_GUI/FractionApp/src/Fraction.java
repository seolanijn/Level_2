/**
 * Program Name:    Fraction.java
 * Purpose:     	it has some useful methods for creating a FractionCalculator class
 * @author    		Seolan Jin, Junyeong Jo
 * @version     	1.0
 * @since           Jul. 31, 2021
 */

public class Fraction implements Comparable<Fraction>
{
	private int num;
	private int den;
	
	/**
	 * Constructs a new Fraction object initializes attribute
	*/
	public Fraction() {
		num = 1;
		den = 1;
	}
	/**
	 * Constructs a new Fraction object
	 * @param num initializes attribute
	 * @param den initializes attribute
	*/
	public Fraction(int num, int den){
			this.num = num;
			this.den = den;
	}
	
	
	/**
	 * Gets the num of this object
	 * @return the num
	*/
	public int getNum()
	{
		return num;
	}
	/**
	 * Gets the den of this object
	 * @return the den
	*/
	public int getDen()
	{
		return den;
	}
	
	/**
	 * Sets the num of this object
	 * @param num - the value to set
	*/
	public void setNum(int num)
	{
		this.num = num;
	}
	/**
	 * Sets the den of this object
	 * @param den - the value to set
	*/
	public void setDen(int den)
	{
		this.den = den;
	}
	
	/**
	 *  converts fraction to decimal
	 *  @return 'num / den' of type double
	 */
	public double toDecimal() {
		return num / (double)den;
	}
	
	/**
	 *  converts reciprocal
	 *  @return a Fraction
	 */
	public Fraction toReciprocal(){
		int temp = this.getNum();
		return new Fraction(this.getDen(), temp);
	}
	
	/**
	 *  adds two fractions
	 *  @param f
	 *  @return a Fraction
	 */
	public Fraction add(Fraction f){
		return new Fraction(this.num * f.den + f.num * this.den,
							this.den * f.den).lowestTerms();
		
	}
	/**
	 *  multiplies two fractions
	 *  @param f
	 *  @return a Fraction
	 */
	public Fraction multiply(Fraction f){
		return new Fraction(this.num * f.num,
							this.den * f.den).lowestTerms();	
	}
	
	/**
	 *  compares two fraction if they are equal
	 *  @param f
	 *  @return true if they are equal or false if they are not.
	 */
	public boolean equals(Fraction f){
		Fraction temp1 = f.lowestTerms();
		Fraction temp2 = this.lowestTerms();
		
		if ((temp1.getNum() == temp2.getNum()) &&(temp1.getDen() == temp2.getDen()))
			return true;
		else
			return false;
	}
	/**
	 *  compares two fraction which one is greater than the other.
	 *  @param f
	 *  @return true if thisDen > fDen or false if thisDen < fDen
	 */
	public boolean greaterThan(Fraction f) {
		int thisDen = this.getDen()*f.getNum();
		int fDen = f.getDen()*this.getNum();
		if(thisDen > fDen)
			return true;
		else
			return false;
	}
	
	/**
	 *  finds Greatest Common Divisor
	 *  @param den1
	 *  @param den2
	 *  @return a gcd
	 */
	private int gcd(int den1, int den2) {
		// if den1 > den2, swap
		if (den1 < den2) {
			int temp = den1;
			den1 = den2;
			den2 = temp;
		}
		
		if (den2 == 0)
			return den1;
		else
			return gcd(den2,den1%den2);
	}
	/**
	 *  finds lowestTerms of fractions
	 *  @return a fraction that is lowestTerm
	 */
	public Fraction lowestTerms(){
		int gcdFraction = gcd(Math.abs(this.getNum()), Math.abs(this.getDen()));
		return new Fraction(this.getNum()/gcdFraction, this.getDen()/gcdFraction);
	}
	
	/*  (non-Javadoc)
	 * @see java.lang.Comparable#compareTo(java.lang.Object)
	*/
	@Override public int compareTo(Fraction f){
		
		if (greaterThan(f))
			return 1;
		else if (equals(f)) 
			return 0;
		else
			return -1;
	}
	/*  (non-Javadoc)
	 * @see java.lang.Object#toString()
	*/
	@Override public String toString() {
		return this.getNum() + "/" + this.getDen();
	}
	
}
//End of class