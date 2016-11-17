//komentarza Katarzyna Rugie³³o
/* Simulation of console-I/O program PostfixConsole,
   using ConsoleApplet as a basis.  See the file
   ConsoleApplet.java for more information.
   
*/

public class PostfixEvalConsole extends ConsoleApplet {

   protected String getTitle() {
      return "Sample program \"PostfixEval\"";
   }


   protected void program() {

      /*
          This program evaluates postfix expressions entered by the
          user.  The expressions can use non-negative real nubmers and
          the operators +, -, *, /, and ^ (where ^ represents exponentiation).
          Numbers must begin with a digit.  That is, you have to say
          0.7 rather than just .7.  The value of an expression might
          be given as infinity or NaN.
    
          A stack is used to evaluate the expression.  The stack is represented
          by an object of type NumberStack, as defined in NumberStack.java.
          For demonstration purposes, the stack operations are reported as
          they are performed.
      */
      
      console.putln("This program can evaluate postfix expressions such as\n");
      console.putln("        2 2 +");
      console.putln("or");
      console.putln("        7.3 89.2 + 9 1.83 * 2 + /\n");
      console.putln("The operators +, -, *, /, and ^ can be used.\n\n");
      
      while (true) {
             // Get and process one line of input from the user.
         console.putln("\n\n\nEnter a postfix expression or press return to end:\n");
         console.put("?  ");
         skipSpaces();
         if (console.peek() == '\n') {
                // If the line is empty (except for spaces), we are done.
            break;
         }
         readAndEvaluate();  // Process the input.
         console.getln();  // Discard the end-of-line.
      }
      
      console.putln("\n\nExiting program.");

   } // end program()


   void skipSpaces() {
         // Skip past any spaces and tabs on the current input line.
         // When this routine returns, the next character is either
         // the end-of-line character, '\n', or is a non-blank.
      while (console.peek() == ' ' || console.peek() == '\t') {
         console.getAnyChar();
      }
   }
   
   
   void readAndEvaluate() {
         // Read one line of input and process it as a postfix expression.
         // If the input is not a legal postfix expression, then an error
         // message is displayed.  Otherwise, the value of the expression
         // is displayed.  It is assumed that the first character on
         // the input line is a non-blank.  (This is checked in the
         // main() routine.)
         
      NumberStack stack;  // For evaluating the expression.
      
      stack = new NumberStack();  // Make a new, empty stack.
      
      console.putln();
      
      while (console.peek() != '\n') {
      
          if ( Character.isDigit(console.peek()) ) {
                  // The next item in input is a number.  Read it and
                  // save it on the stack.
              double num = console.getDouble();
              stack.push(num);
              console.putln("   Pushed constant " + num);
          }
          else {
                 // Since the next item is not a number, the only thing
                 // it can legally be is an operator.  Get the operator
                 // and perform the operation.
              char op;  // The operator, which must be +, -, *, /, or ^.
              double x,y;     // The operands, from the stack, for the operation.
              double answer;  // The result, to be pushed onto the stack.
              op = console.getChar();
              if (op != '+' && op != '-' && op != '*' && op != '/' && op != '^') {
                      // The character is not one of the acceptable operations.
                  console.putln("\nIllegal operator found in input: " + op);
                  return;
              }
              if (stack.isEmpty()) {
                  console.putln("   Stack is empty while trying to evaluate " + op);
                  console.putln("\nNot enough numbers in expression!");
                  return;
              }
              y = stack.pop();
              if (stack.isEmpty()) {
                  console.putln("   Stack is empty while trying to evaluate " + op);
                  console.putln("\nNot enough numbers in expression!");
                  return;
              }
              x = stack.pop();
              switch (op) {
                 case '+':  answer = x + y;  break;
                 case '-':  answer = x - y;  break;
                 case '*':  answer = x * y;  break;
                 case '/':  answer = x / y;  break;
                 default:   answer = Math.pow(x,y);  // (op must be '^'.)
              }
              stack.push(answer);
              console.putln("   Evaluated " + op + " and pushed " + answer);
          }
          
          skipSpaces();
      
      }  // end while
      
      // If we get to this point, the input has been read successfully.
      // If the expression was legal, then the value of the expression is
      // on the stack, and it is the only thing on the stack.
      
      if (stack.isEmpty()) {  // Impossible if the input is really non-empty.
          console.putln("No expression provided.");
          return;
      }
         
      double value = stack.pop();  // Value of the expression.
      console.putln("   Popped " + value + " at end of expression.");

      if (stack.isEmpty() == false) {
          console.putln("   Stack is not empty.");
          console.putln("\nNot enough operators for all the numbers!");
          return;
      }

      console.putln("\nValue = " + value);
      
   } // end readAndEvaluate()


} // end class PostfixEvalConsole
