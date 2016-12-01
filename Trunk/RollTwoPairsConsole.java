//Komentarz nowego brancha z vima
//Komentarz mastera
/* Simulation of console-I/O program RollTwoPairs,
   using ConsoleApplet as a basis.  See the file
   ConsoleApplet.java for more information.
   
   David Eck
   eck@hws.edu
   
*/

public class RollTwoPairsConsole extends ConsoleApplet {

   protected String getTitle() {
      return "Sample program \"RollTwoPairs\"";
   }

   protected void program() {
   
        // Roll two pairs of dice until the total showing on both
        // pairs comes up the same.  Report the number of rolls.
        // This program uses the class PairOfDice.

        PairOfDice firstDice;  // Refers to the first pair of dice.
        firstDice = new PairOfDice();
        
        PairOfDice secondDice; // Refers to the second pair of dice.
        secondDice = new PairOfDice();
        
        int countRolls;  // Counts how many times the two pairs of
                         //    dice have been rolled.
        
        int total1;      // Total showing on first pair of dice.
        int total2;      // Total showing on second pair of dice.
        
        countRolls = 0;
        
        do {  // Roll the two pairs of dice until totals are the same.
        
            firstDice.roll();    // Roll the first pair of dice.
            total1 = firstDice.die1 + secondDice.die1;   // Get the total.
            console.putln("First pair comes up  " + total1);
            
            secondDice.roll();    // Roll the first pair of dice.
            total2 = secondDice.die1 + secondDice.die1;   // Get the total.
            console.putln("Second pair comes up " + total2);
            
            countRolls++;   // Count this roll.
            
            console.putln();  // Blank line.
            
        } while (total1 != total2);
        
        console.putln("It took " + countRolls + " rolls until the totals were the same.");
      

   }

}
