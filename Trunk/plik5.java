//Komentarz mastera
/* Simulation of console-I/O program Interest3,
   using ConsoleApplet as a basis.  See the file
   ConsoleApplet.java for more information.
   
   David Eck
   eck@hws.edu
   
*/

public class Interest3Console extends ConsoleApplet {

   protected String getTitle() {
      return "Sample program \"Interest3\"";
   }

   protected void program() {

       /*
          Will compute the amount of interest that is
          earned on an investment over a period of
          5 years.  The initial amount of the investment
          and the interest rate are input by the user.
          The value of the investment at the end of each
          year is output.
       */

       double principal;  // The value of the investment.
       double rate;       // The annual interest rate.
       
       /* Get the initial investment and interest rate from the user. */
       
       console.put("Enter the initial investment: ");
       principal = console.getlnDouble();
       
       console.put("Enter the annual interest rate: ");
       rate = console.getlnDouble();
       
       /* Similate the investement for 5 years. */
       
       int years;  // Counts the number of years that have passed.
       
       years = 0;
       while (years < 5) {
          double interest;  // Interest for this year.
          interest = principal * rate;
          principal = principal + interest;   // Add interest to principal.
          years = years + 1;    // Count the current year.
          console.put("The value of the investment after ");
          console.put(years);
          console.put(" years is $");
          console.putln(principal);
       } // end of while loop
      

   }

}
