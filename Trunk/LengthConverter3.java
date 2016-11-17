//komentarza Katarzyna Rugie³³o
public class LengthConverter3 {

   /* 
      This program will convert measurements expressed in inches,
      feet, yards, or miles into each of the possible units of
      measure.  The measurement is input by the user, followed by
      the unit of measure.  For example:  "17 feet", "1 inch",
      "2.73 mi".  Several measurements can be combined on
      one line of input.  For example:  "2 miles 5 yards 1 inch".
      In this case, the measurements are combined into one total.
      Abbreviations in, ft, yd, and mi are accepted.  Negative 
      measurements are not allowed.
      
      The program will continue to read and convert measurements
      until the user enters an empty line.
      
      This version of the program uses exception handling.
   */
  

   static class ParseError extends Exception {
         // This nested class is used to represent errors in the
         // user's input.
      ParseError(String message) {
         super(message);
      }
   }

   public static void main(String[] args) {
   
      
      double measurement;  // Numerical measurement, input by user.
      String units;        // The unit of measure for the input, also
                           //    specified by the user.
      
      double inches, feet, yards, miles;  // Measurement expressed in each
                                          //   possible unit of measure.
      
      TextIO.putln("Enter measurements in inches, feet, yards, or miles.");
      TextIO.putln("For example:  1 inch    17 feet    2.73 miles");
      TextIO.putln("You can use abbreviations:   in   ft  yd   mi");
      TextIO.putln("I will convert your input into the other units of measure.");
      
      while (true) {
         
         /* Get the user's input, and convert it to inches. */
         
         TextIO.putln();
         TextIO.putln();
         TextIO.putln("Enter your measurement, or press return to end:");
         
         skipBlanks();  
         
         if (TextIO.peek() == '\n')  // End if there is nothing on the line.
            break;
         
         try {
            inches = readMeasurement();
         }
         catch (ParseError e) {
            TextIO.putln( "Error:  " + e.getMessage() );
            TextIO.getln();  // Discard the rest of the input line.
            continue;  // jump back to the start of the while loop
         }
         
         /* If we get to this point, we know that the user's input
            was legal and that the value of inches is valid. */
            
         /* Convert the measurement in inches to feet, yards, and miles. */
      
         feet = inches / 12;
         yards = inches / 36;
         miles = inches / (12*5280);
       
         /* Output the measurement in terms of each unit of measure. */
      
         TextIO.putln();
         TextIO.putln("That's equivalent to:");
         TextIO.put(inches, 15);
         TextIO.putln(" inches");
         TextIO.put(feet, 15);
         TextIO.putln(" feet");
         TextIO.put(yards, 15);
         TextIO.putln(" yards");
         TextIO.put(miles, 15);
         TextIO.putln(" miles");
            
         TextIO.getln();  // Discard the end-of-line character.
      
      } // end while
      
      TextIO.putln();
      TextIO.putln("OK!  Bye for now.");
      
   } // end main()
   
   
   static void skipBlanks() {
         // Reads past any blanks and tabs in the input.
         // Postcondition:  The next character in the input is an
         //                 end-of-line or a non-blank character.
      char ch;
      ch = TextIO.peek();
      while (ch == ' ' || ch == '\t') {
         ch = TextIO.getAnyChar();
         ch = TextIO.peek();
      }
   }
   
   
   static double readMeasurement() throws ParseError {

         // Reads the user's input measurement from one line of input.
         // Preconditino:  The input line is not empty.
         // Postcondition:  The measurement is converted to inches and
         //                 returned.  However, if the input is not legal,
         //                 a ParseError is thrown.
         // Note:  The end-of-line is NOT read by this routine.

      double inches;  // Total number of inches in user's measurement.
      
      double measurement;  // One measurement, such as the 12 in "12 miles"
      String units;   // The units specified for the measurement, such as "miles"
      
      char ch;  // Used to peek at next character in the user's input.

      inches = 0;  // No inches have yet been read.

      skipBlanks();
      ch = TextIO.peek();
      
      /* As long as there is more input on the line, read a measurement and
         add the equivalent number of inches to the variable, inches.  If an
         error is detected during the loop, end the subroutine immediately
         by throwing a ParseError. */

      while (ch != '\n') {
      
          /* Get the next measurement and the units.  Before reading
             anything, make sure that a legal value is there to read. */
      
          if ( ! Character.isDigit(ch) ) {
              throw new ParseError("Expected to find a number, but found " + ch);
          }
          measurement = TextIO.getDouble();
          skipBlanks();
          if (TextIO.peek() == '\n') {
             throw new ParseError("Missing unit of measure at end of line.");
          }
          units = TextIO.getWord();
          units = units.toLowerCase();
          
          /* Convert the measurement to inches and add it to the total. */
          
          if (units.equals("inch") || units.equals("inches") || units.equals("in"))
              inches += measurement;
          else if (units.equals("foot") || units.equals("feet") || units.equals("ft"))
              inches += measurement * 12;
          else if (units.equals("yard") || units.equals("yards") || units.equals("yd"))
              inches += measurement * 36;
          else if (units.equals("mile") || units.equals("miles") || units.equals("mi"))
              inches += measurement * 12 * 5280;
          else {
              throw new ParseError("\"" + units + "\" is not a legal unit of measure.");
          }
        
          /* Look ahead to see whether the next thing on the line is the end-of-line. */
         
          skipBlanks();
          ch = TextIO.peek();
          
      }  // end while
      
      return inches;
      
   } // end readMeasurement()
   

} // end class LengthConverter
