import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;

import javax.swing.*;

/**
 * Program Name:    FractionCalculator.java
 * Purpose:     	To simulate a fraction calculator.
 * @author    		Seolan Jin, Junyeong Jo
 * @version     	1.0
 * @since           Jul. 31, 2021
 */

public class FractionCalculator extends JFrame
{
	// declare GUI components
	private JLabel lblNum, lblDen;
	private JTextField txtNum, txtDen;
	
	private JButton btnBuild, btnStart;
	private JList<String> lstFrac, lstOp;
	private JComboBox<String> cboOp;
	private JPanel enterPanel, fracPanel, selectPanel, opPanel;

	// declare class variables
	private String[] printFrac, printOp;
	private ArrayList<Fraction> userFrac;
	
	private int listSize;
	
	//No-arg constructor
	/**
	 * Constructs a new FractionCalculator object initializes attribute
	*/
	public FractionCalculator() {
		
		super("Fraction Calculator");
		
		//Set the layout manager
		this.setLayout(new GridLayout(1,4));

		//Initialize class variables
		userFrac = new ArrayList<Fraction>();
		listSize = 16;
		printFrac = new String[listSize];
		
		
		//Initialize array to display as an empty box
		for (int i = 0; i < listSize; ++i) {
			printFrac[i] = " ";
		}
		
		printOp = new String[listSize];
		
		for (int i = 0; i < listSize; ++i) {
			printOp[i] = " ";
		}
		
		//Build panel
		buildEnterPanel();	
		buildFracPanel();	
		buildSelectPanel();	
		buildOpPanel();	

		//Add text area and panel to frame
		add(enterPanel);
		add(fracPanel);	
		add(selectPanel);		
		add(opPanel);		
				
		//Set up methods for the frame
		this.setSize(900, 400);							
		this.setLocationRelativeTo(null);										
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);				
		this.setVisible(true);			
	}//End of constructor
	
	/**
	 *  build enterPanel
	 */
	private void buildEnterPanel()
	{
		//Create panel
		enterPanel = new JPanel();		
		enterPanel.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.BLACK, 1), "Enter a fraction:"));
		
		//Initialize GUI components
		lblNum = new JLabel("Numerator:");
		lblDen = new JLabel("Denominator:");
		
		txtNum = new JTextField(15);
		txtDen = new JTextField(15);
		
		txtNum.setEditable(true);
		txtDen.setEditable(true);
		
		btnBuild = new JButton("Build Fraction");
		btnStart = new JButton("Start Over!");
		
		//add action listener
		btnBuild.addActionListener(new buttonBuildListener());
		
		// create action listener
		btnStart.addActionListener(new ActionListener() {
			@Override public void actionPerformed(ActionEvent e) {
				// restore the "Decimal" operation in the combo box
				cboOp.setSelectedIndex(0);
				
				for (int i = 0; i < listSize; ++i) {
					printFrac[i] = " ";
				}
				
				userFrac = new ArrayList<Fraction>();
				
				// display array to each list.
				lstFrac.setListData(printFrac);
				lstOp.setListData(printFrac);
				
				//reset the input fields
				txtNum.setText("");
				txtDen.setText("");
			}
		});
		
		//Add components to panel
		enterPanel.add(lblNum);
		enterPanel.add(txtNum);
		enterPanel.add(lblDen);
		enterPanel.add(txtDen);		
		enterPanel.add(btnBuild);
		enterPanel.add(btnStart);
	}//End of buildEnterPanel method
	
	/**
	 * build action listener for build fraction button
	 */
	private class buttonBuildListener implements ActionListener {
		@Override public void actionPerformed(ActionEvent e) {
			try {
				// throw exception if error occurs
				if ((txtNum.getText().length() > 10) || (txtDen.getText().length() > 10))
					throw new LongOperandException();
				if ((txtNum.getText().length() == 0) || (txtDen.getText().length() == 0))
					throw new EmptyOperandException();
				
				if (Integer.valueOf(txtDen.getText()) == 0)
					throw new DivisionByZeroException();
				
				// populate arraylist using Fraction
				userFrac.add(new Fraction(Integer.valueOf(txtNum.getText()), Integer.valueOf(txtDen.getText())));
				
				
				// populate array using toString()
				for (int i = 0; i < userFrac.size(); ++i) 
					printFrac[i] = userFrac.get(i).toString();
				
				// display array to each list.
				lstFrac.setListData(printFrac);
				
				//reset the input fields
				txtNum.setText("");
				txtDen.setText("");
			}
			// catch the exceptions, and the focus cursor returns to the text where error occurred
			catch(NumberFormatException ex) {
				JOptionPane.showMessageDialog(null, "Invalid data type. Enter an integer.", "NumberFormatException", JOptionPane.ERROR_MESSAGE);
				txtNum.requestFocusInWindow();  
				txtNum.setText("");
				txtDen.setText("");
			}
			catch(DivisionByZeroException ex) {
				JOptionPane.showMessageDialog(null, ex.getMessage(), "DivisionByZeroException", JOptionPane.ERROR_MESSAGE);
				txtDen.requestFocusInWindow();
			}
			catch(LongOperandException ex) {
				JOptionPane.showMessageDialog(null, ex.getMessage(), "LongOperandException", JOptionPane.ERROR_MESSAGE);
			
				if (txtNum.getText().length() > 10)
					txtNum.requestFocusInWindow();
				else if (txtDen.getText().length() > 10)
					txtDen.requestFocusInWindow();
			}
			catch(EmptyOperandException ex) {
				JOptionPane.showMessageDialog(null, ex.getMessage(), "LongOperandException", JOptionPane.ERROR_MESSAGE);
				
				if (txtNum.getText().length() == 0)
					txtNum.requestFocusInWindow();
				else if (txtDen.getText().length() == 0)
					txtDen.requestFocusInWindow();
			}
		}//End of action performed method	
	}//End of inner listener class
	
	
	/**
	 *  build a fraction Panel
	 */
	private void buildFracPanel()
	{
		//Create panel
		fracPanel = new JPanel();
		
		//sets the border
		fracPanel.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.BLACK, 1), "Here is your fraction:"));
		
		lstFrac = new JList<String>(printFrac);
		
		lstFrac.setFixedCellWidth(200);
		
		//add JList to the Fraction panel
		fracPanel.add(lstFrac);
	}

	/**
	 *  build a selection panel
	 */
	private void buildSelectPanel()
	{
		//Create panel
		selectPanel = new JPanel();		
		
		//sets the border
		selectPanel.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.BLACK, 1), "Select an operation:"));
		
		//populate array for comboBox
		String [] opList = {"Decimal", "Reciprocal", "Fraction1 + Fraction2", "Fraction1 * Fraction2", "Is Fraction1 = Fraction2", "Is Fraction1 > Fraction2",
							"Lowest Terms", "Sort List"};
		cboOp = new JComboBox<String>(opList);
		
		cboOp.addActionListener(new comboBoxOperationListener());
		
		//add comboBox to the select panel
		selectPanel.add(cboOp);

	}//End of buildSelectPanel method
	
	/** 
	 * build action listener for combo box
	 */
	private class comboBoxOperationListener implements ActionListener{
		@Override public void actionPerformed(ActionEvent e) {
			String userSelect = (String)(cboOp.getSelectedItem());
			
			// operate a user selected operations
			if(userSelect.equals("Decimal")) {
				for (int i = 0; i < listSize; ++i)
					printOp[i] = " ";
				double toDecimal = userFrac.get(userFrac.size()-1).toDecimal();
				printOp[0] = String.valueOf(toDecimal);
			}
			else if(userSelect.equals("Reciprocal")) {
				// restore the "Decimal" operation in the combo box
				cboOp.setSelectedIndex(0);
				for (int i = 0; i < listSize; ++i)
					printOp[i] = " ";
				Fraction reciprocalFrac = userFrac.get(userFrac.size()-1).toReciprocal();
				printOp[0] = reciprocalFrac.toString();
			}
			else if(userSelect.equals("Fraction1 + Fraction2")) {
				// restore the "Decimal" operation in the combo box
				cboOp.setSelectedIndex(0);
				// if size is less than required fractions, pop up a warning sign
				if (userFrac.size() < 2)
					JOptionPane.showMessageDialog(null, "Invalid Operation. Add another fraction.", "Input Error", JOptionPane.ERROR_MESSAGE);
				else {
					for (int i = 0; i < listSize; ++i)
						printOp[i] = " ";
					Fraction addFrac = userFrac.get(userFrac.size()-1).add(userFrac.get(userFrac.size()-2));			
					printOp[0] = addFrac.toString();
				}
			}
			else if(userSelect.equals("Fraction1 * Fraction2")) {
				// restore the "Decimal" operation in the combo box
				cboOp.setSelectedIndex(0);
				
				// if size is less than required fractions, pop up a warning sign
				if (userFrac.size() < 2)
					JOptionPane.showMessageDialog(null, "Invalid Operation. Add another fraction.", "Input Error", JOptionPane.ERROR_MESSAGE);
				else {
					for (int i = 0; i < listSize; ++i)
						printOp[i] = " ";
					Fraction multiplyFrac = userFrac.get(userFrac.size()-1).multiply(userFrac.get(userFrac.size()-2));			
					printOp[0] = multiplyFrac.toString();
				}
			}
			else if(userSelect.equals("Is Fraction1 = Fraction2")) {
				// restore the "Decimal" operation in the combo box
				cboOp.setSelectedIndex(0);
				
				// if size is less than required fractions, pop up a warning sign
				if (userFrac.size() < 2)
					JOptionPane.showMessageDialog(null, "Invalid Operation. Add another fraction.", "Input Error", JOptionPane.ERROR_MESSAGE);
				else {
					for (int i = 0; i < listSize; ++i)
						printOp[i] = " ";
					boolean equalBool = userFrac.get(userFrac.size()-1).equals(userFrac.get(userFrac.size()-2));			
					printOp[0] = String.valueOf(equalBool);
				}
			}
			else if(userSelect.equals("Is Fraction1 > Fraction2")) {
				// restore the "Decimal" operation in the combo box
				cboOp.setSelectedIndex(0);
				
				// if size is less than required fractions, pop up a warning sign
				if (userFrac.size() < 2)
					JOptionPane.showMessageDialog(null, "Invalid Operation. Add another fraction.", "Input Error", JOptionPane.ERROR_MESSAGE);
				else {
					for (int i = 0; i < listSize; ++i)
						printOp[i] = " ";
					boolean greaterBool = userFrac.get(userFrac.size()-1).greaterThan(userFrac.get(userFrac.size()-2));			
					printOp[0] = String.valueOf(greaterBool);
				}
			}
			else if(userSelect.equals("Lowest Terms")) {
				// restore the "Decimal" operation in the combo box
				cboOp.setSelectedIndex(0);
				for (int i = 0; i < userFrac.size(); ++i) {
					userFrac.set(i, userFrac.get(i).lowestTerms());
					printOp[i] = userFrac.get(i).toString();
					printFrac[i] = userFrac.get(i).toString();
				}
			}
			else if(userSelect.equals("Sort List")) {
				// restore the "Decimal" operation in the combo box
				cboOp.setSelectedIndex(0);
				
				// if size is less than required fractions, pop up a warning sign
				if (userFrac.size() < 2)
					JOptionPane.showMessageDialog(null, "Invalid Operation. Add another fraction.", "Input Error", JOptionPane.ERROR_MESSAGE);
				else {
				for (int i = 0; i < userFrac.size()-1; ++i) {
					for (int j = 0; j < userFrac.size()-1; ++j) {
						if (userFrac.get(j).compareTo(userFrac.get(j+1)) == -1) {
							Fraction temp = userFrac.get(j);
							userFrac.remove(j);
							userFrac.add(j+1, temp);
						}
					}
				}
				
				for (int i = 0; i < userFrac.size(); ++i) {
					printOp[i] = userFrac.get(i).toString();
					printFrac[i] = userFrac.get(i).toString();
				}
			}
		}
		//set each list using modified array
		lstFrac.setListData(printFrac);
		lstOp.setListData(printOp);
	}//End of action performed method
	}//End of inner listener class
	
	/**
	 *  build an operation panel
	 */
	private void buildOpPanel()
	{
		//initialize components
		opPanel = new JPanel();		
		opPanel.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.BLACK, 1), "Here is your operation:"));
		
		lstOp = new JList<String>(printOp);
		
		lstOp.setFixedCellWidth(200);
		
		//add operation list to the operation panel
		opPanel.add(lstOp);
		
	}//End of buildOpPanel method
	
	//Add an embedded main method
	public static void main(String [] args)
	{
		try
		{
			UIManager.setLookAndFeel("javax.swing.plaf.nimbus.NimbusLookAndFeel");
		}	
		catch (Exception e)
		{
			System.out.println(e.getMessage());
		}
		//Creates an instance of the frame
		FractionCalculator frame = new FractionCalculator ();		
	}//End of main method
}//End of class