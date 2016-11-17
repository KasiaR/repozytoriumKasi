
/* Simulation of console-I/O program SimpleParser3,
   using ConsoleApplet as a basis.  See the file
   ConsoleApplet.java for more information.
*/

public class SimpleParser3Console extends ConsoleApplet {


   protected String getTitle() {
      return "Sample program \"SimpleParser3\"";
   }


   protected void program() {
   
        /*
            This program reads standard expressions typed in by the user. 
            The program constructs an expression tree to represent the
            exprssion.  It then prints the value of the tree.  It also uses
            the tree to print out a list of commands that could be used
            on a stack machine to evaluate the expresion.
            The expressions can use positive real numbers and
            the binary operators +, -, *, and /.  The unary minus operation
            is supported.  The expressions are defined by the BNF rules:
            
                    <expression>  ::=  [ "-" ] <term> [ [ "+" | "-" ] <term> ]...
                    
                    <term>  ::=  <factor> [ [ "*" | "/" ] <factor> ]...
                    
                    <factor>  ::=  <number>  |  "(" <expression> ")"
                    
            A number must begin with a digit (i.e., not a decimal point).
            A line of input must contain exactly one such expression.  If extra
            data is found on a line after an expression has been read, it is
            considered an error.
            
            The classes for the expression tree are defined as nested 
            classes below.
        */
        
        while (true) {
           console.putln("\n\nEnter an expression, or press return to end.");
           console.put("\n?  ");
           skipBlanks();
           if ( console.peek() == '\n' )
              break;
           try {
              ExpNode exp = expressionTree();
              skipBlanks();
              if ( console.peek() != '\n' )
                 throw new ParseError("Extra data after end of expression.");
              console.getln();
              console.putln("\nValue is " + exp.value());
              console.putln("\nOrder of postfix evaluation is:\n");
              exp.printStackCommands();
           }
           catch (ParseError e) {
              console.putln("\n*** Error in input:    " + e.getMessage());
              console.putln("*** Discarding input:  " + console.getln());
           }
        }
        
        console.putln("\n\nDone.");

    } // end program()
   
   
    static class ParseError extends Exception {
           // Represents a syntax error found in the user's input.
       ParseError(String message) {
           super(message);
       }
    } // end nested class ParseError
   
   

    //-------------------- Classes for Expression Trees ------------------------------


    abstract class ExpNode {
           // An abstract class representing any node in an expression tree.
           // The following three concrete node classes are subclasses.
           // Two instance methods are specified, so that they can be used with
           // andy ExpNode.  The value() method returns the value of the
           // expression.  The printStackCommands() method prints a list
           // of commands that could be used to evaluate the expression on
           // a stack machine (assuming that the value of the expression is
           // to be left on the stack).
       abstract double value(); 
       abstract void printStackCommands();
    }

    class ConstNode extends ExpNode {
           // An expression node that holds a number.
       double number;  // The number.
       ConstNode(double val) {
              // Construct a ConstNode containing the specified number.
          number = val;
       }
       double value() {
             // The value of the node is the number that it contains.
          return number;
       }
       void printStackCommands() {
             // On a stack machine, just push the number onto the stack.
          console.putln("  Push " + number); 
       }
    }

    class BinOpNode extends ExpNode {
           // An expression node representing a binary operator,
       char op;        // The operator.
       ExpNode left;   // The expression for its left operand.
       ExpNode right;  // The expression for its right operand.
       BinOpNode(char op, ExpNode left, ExpNode right) {
              // Construct a BinOpNode containing the specified data.
          this.op = op;
          this.left = left;
          this.right = right;
       }
       double value() {
               // The value is obtained by evaluating the left and right
               // operands and combining the values with the operator.
           double x = left.value();
           double y = right.value();
           switch (op) {
              case '+':  return x + y;
              case '-':  return x - y;
              case '*':  return x * y;
              case '/':  return x / y;
              default:   return Double.NaN;  // Bad operator!
           }
       }
       void  printStackCommands() {
              // To evalute the expression on a stack machine, first do
              // whatever is necessary to evaluate the left operand, leaving
              // the answer on the stack.  Then do the same thing for the
              // second operand.  Then apply the operator (which means popping
              // the operands, applying the operator, and pushing the result).
           left.printStackCommands();
           right.printStackCommands();
           console.putln("  Operator " + op);
       }
    }

    class UnaryMinusNode extends ExpNode {
           // An expression node to represent a unary minus operator.
       ExpNode operand;  // The operand to which the unary minus applies.
       UnaryMinusNode(ExpNode operand) {
              // Construct a UnaryMinusNode with the specified operand.
          this.operand = operand;
       }
       double value() {
             // The value is the negative of the value of the operand.
          double neg = operand.value();
          return -neg;
       }
       void printStackCommands() {
             // To evaluate this expression on a stack machine, first do
             // whatever is necessary to evaluate the operand, leaving the
             // operand on the stack.  Then apply the unary minus (which means
             // popping the operand, negating it, and pushing the result).
          operand.printStackCommands();
          console.putln("  Unary minus");
       }
    }


    //-------------------------- Parsing routines -----------------------------
    

    void skipBlanks() {
          // Skip past any spaces and tabs on the current line of input.
          // Stop at a non-blank character or end-of-line.
       while ( console.peek() == ' ' || console.peek() == '\t' )
          console.getAnyChar();
    }
    
    
    ExpNode expressionTree() throws ParseError {
           // Read an expression from the current line of input and
           // return an expression tree representing the expression.
       skipBlanks();
       boolean negative;  // True if there is a leading minus sign.
       negative = false;
       if (console.peek() == '-') {
          console.getAnyChar();
          negative = true;
       }
       ExpNode exp;   // The expression tree for the expression.
       exp = termTree();  // Start with the first term.
       if (negative)
          exp = new UnaryMinusNode(exp);
       skipBlanks();
       while ( console.peek() == '+' || console.peek() == '-' ) {
                // Read the next term and combine it with the
                // previous terms into a bigger expression tree.
           char op = console.getAnyChar();
           ExpNode nextTerm = termTree();
           exp = new BinOpNode(op, exp, nextTerm);
           skipBlanks();
       }
       return exp;
    } // end expressionTree()


    ExpNode termTree() throws ParseError {
           // Read a term from the current line of input and
           // return an expression tree representing the term.
       skipBlanks();
       ExpNode term;  // The expression tree representing the term.
       term = factorTree();
       skipBlanks();
       while ( console.peek() == '*' || console.peek() == '/' ) {
                // Read the next factor, and combine it with the
                // previous factors into a bigger expression tree.
           char op = console.getAnyChar();
           ExpNode nextFactor = factorTree();
           term = new BinOpNode(op,term,nextFactor);
           skipBlanks();
       }
       return term;
    } // end termValue()
    
    
    ExpNode factorTree() throws ParseError {
           // Read a factor from the current line of input and
           // return an expression tree representing the factor.
       skipBlanks();
       char ch = console.peek();
       if ( Character.isDigit(ch) ) {
              // The factor is a number.  Return a ConstNode.
          double num = console.getDouble();
          return new ConstNode(num);
       }
       else if ( ch == '(' ) {
             // The factor is an expression in parentheses.
          console.getAnyChar();  // Read the "("
          ExpNode exp = expressionTree();
          skipBlanks();
          if ( console.peek() != ')' )
             throw new ParseError("Missing right parenthesis.");
          console.getAnyChar();  // Read the ")"
          return exp;
       }
       else if ( ch == '\n' )
          throw new ParseError("End-of-line encountered in the middle of an expression.");
       else if ( ch == ')' )
          throw new ParseError("Extra right parenthesis.");
       else if ( ch == '+' || ch == '-' || ch == '*' || ch == '/' )
          throw new ParseError("Misplaced operator.");
       else
          throw new ParseError("Unexpected character \"" + ch + "\" encountered.");
    }  // end factorTree()


} // end class SimpleParser3Console
