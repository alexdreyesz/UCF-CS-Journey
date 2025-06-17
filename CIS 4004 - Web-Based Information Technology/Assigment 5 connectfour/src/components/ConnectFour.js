import React from "react";
import "./ConnectFour.css"

// declare class ConnectFour so it extends class React.Componenet
class ConnectFour extends React.Component {     
    // declare the constructor receiving parameter props
    constructor(props) {
        // call method super() passing parameter props as an argument
        super(props);
        
        // initialize this.state object to include properties:
        // initialMatrix initialized to [[0, 0, 0, 0, 0, 0, 0],
        //                              [0, 0, 0, 0, 0, 0, 0],
        //                              [0, 0, 0, 0, 0, 0, 0],
        //                              [0, 0, 0, 0, 0, 0, 0],
        //                              [0, 0, 0, 0, 0, 0, 0],
        //                              [0, 0, 0, 0, 0, 0, 0]
        //                             ] 
        //
        // currentPlayer intialized to 1
        this.state = {
            initialMatrix: [
              [0, 0, 0, 0, 0, 0, 0],
              [0, 0, 0, 0, 0, 0, 0],
              [0, 0, 0, 0, 0, 0, 0],
              [0, 0, 0, 0, 0, 0, 0],
              [0, 0, 0, 0, 0, 0, 0],
              [0, 0, 0, 0, 0, 0, 0],
            ],
            currentPlayer: 1, // Start with Player 1
            isGameOver: false, // Stop Game When Is Over
        };         
    }
    
    // define function fillbox, receives one parameter, e
    fillBox = (e) => {
      // Prevent further input if the game is over
      if (this.state.isGameOver) {
        return;
      }

      console.log("fillBox");

      // Declare variable colValue set equal to function parseInt() of parameter e, object target, function getAttribute, passing as argument "data-value"
      const colValue = parseInt(e.target.getAttribute("data-value"), 10);

      // Call function this.setPiece, passing arguments 5 (because we have 6 rows, 0 - 5) and variable colValue 
      this.setPiece(5, colValue); 

      // Call method this.setState to update the state of property currentPlayer, if currently 1 then 2, if currently 2, then 1 
      this.setState({
          currentPlayer: this.state.currentPlayer === 1 ? 2 : 1,
      });       
    }   
    
    // define function setPiece, receives two parameters, startCount and colValue
    setPiece = (startCount, colValue) => {
        console.log("setPiece");

        // declare variable initialMatrix intialized to state property initialMatrix
        const { initialMatrix, currentPlayer } = this.state;
        
        // Declare variable rows initialized to object document, method querySelectorAll, passing argument class ".grid-row"
        const rows = document.querySelectorAll(".grid-row");

        // write exception handling with try/catch to catch index out of bounds exception when array column is full 
        try {
            // If the element in array initialMatrix at indexes parameters startCount and colValue is NOT identical to 0
            if (initialMatrix[startCount][colValue] !== 0) {
                // Decrement parameter startCount by 1 
                // Call function this.setPiece, passing as arguments parameters startCount and colValue
                this.setPiece(startCount - 1, colValue);
            } else { // Else
            
                // Declare variable currentRow initialized to array rows, index startCount, method querySelectorAll, passing as an argument class ".grid-box"
                const currentRow = rows[startCount].querySelectorAll(".grid-box");

                // Modify currentRow, index colValue, object classlist, method add, passing as arguments "filled" and player${`this.state.currentPlayer}` 
                currentRow[colValue].classList.add("filled", `player${currentPlayer}`);

                // Update array initialMatrix, indexes startCount and colValue, set equal to this.state.currentPlayer
                initialMatrix[startCount][colValue] = currentPlayer;

                this.setState({ initialMatrix });
                
                // If function call this.winCheck is true
                if (this.winCheck()) {
                    // Display an alert dialog box with message "Player " + this.state.currentPlayer + " wins!"
                    alert("Player " + this.state.currentPlayer + " wins!");

                    // Stop further input
                    this.setState({ isGameOver: true });
                    
                    // return true
                    return true;
                }
            }
        } catch (e) {  // catch with parameter e
          // Display an alert dialog box with message "Column full, select again"
          alert("Column full, select again");
          
          if(this.state.currentPlayer === 1) {
            this.state.currentPlayer = 2;
          } else {
            this.state.currentPlayer = 1;
          }
          
        }

        // Call function this.gameOverCheck
        this.gameOverCheck();
    };
    
    // Define function winCheck, no parameters
    winCheck = () => {
        console.log("winCheck");

        // Write decision making logic, if function call this.checkHorizontal, this.checkVertical, this.checkPositiveDiagonal, or this.checkNegativeDiagonal is true, return true
        if(this.checkHorizontal() || this.checkVertical() || this.checkPositiveDiagonal() || this.checkNegativeDiagonal()) {
            return true;
        } 
    };
    
    // Define function checkHorizontal, no parameters
    checkHorizontal = () => {
        console.log("checkHorizontal");

        const { initialMatrix, currentPlayer } = this.state;

        // Write a nested for loop to iterate through the rows and columns
        for (let row of initialMatrix) {
            for (let col = 0; col < 4; col++) {
                // if the currentPlayer has four discs in a row horizontally, return true
                if (row[col] === currentPlayer && row[col + 1] === currentPlayer && row[col + 2] === currentPlayer && row[col + 3] === currentPlayer) {
                return true;
                }
            }
        }

        // return false
        return false;
    };

    // Define function checkVertical, no parameters
    checkVertical = () => {
        console.log("checkVertical");

        const { initialMatrix, currentPlayer } = this.state;

        // Write a nested for loop to iterate through the columns and rows
        for (let col = 0; col < 7; col++) {
            for (let row = 0; row < 3; row++) {
                // if the currentPlayer has four discs in a row vertically, return true
                if (initialMatrix[row][col] === currentPlayer && initialMatrix[row + 1][col] === currentPlayer && initialMatrix[row + 2][col] === currentPlayer && initialMatrix[row + 3][col] === currentPlayer) {
                    return true;
                }
            }
        }

        // return false
        return false;
    };

    // Define function checkPositiveDiagonal, no parameters
    checkPositiveDiagonal = () => {
        console.log("checkPositiveDiagonal");

        const { initialMatrix, currentPlayer } = this.state;

        // Write a nested for loop to iterate through the rows and columns
        for (let row = 3; row < 6; row++) {
            for (let col = 0; col < 4; col++) {
                // if the currentPlayer has four discs in a row diagonally, bottom right to top left, return true
                if (initialMatrix[row][col] === currentPlayer && initialMatrix[row - 1][col + 1] === currentPlayer && initialMatrix[row - 2][col + 2] === currentPlayer && initialMatrix[row - 3][col + 3] === currentPlayer) {
                return true;
              }
            }
          }

        // return false   
        return false; 
    };

    // Define function checkNegativeDiagonal, no parameters
    checkNegativeDiagonal = () =>{
        console.log("checkNegativeDiagonal");

        const { initialMatrix, currentPlayer } = this.state;

        // Write a nested for loop to iterate through the rows and columns
        for (let row = 3; row < 6; row++) {
            // If the currentPlayer has four discs in a row diagonally, bottom left to top right, return true
            for (let col = 3; col < 7; col++) {
              if (initialMatrix[row][col] === currentPlayer && initialMatrix[row - 1][col - 1] === currentPlayer && initialMatrix[row - 2][col - 2] === currentPlayer && initialMatrix[row - 3][col - 3] === currentPlayer) {
                return true;
              }
            }
        }

        // return false
        return false;
    }

    // define function gameOverCheck, no parameters
    gameOverCheck = () => {
        console.log("gameOverCheck");

        // declare variable count intialized to 0
        let count = 0;

        // declare variable initialMatrix initialized to state property initialMatrix
        const { initialMatrix } = this.state;

        // Write a for/of loop to iterate through the rows, loop control variable innerArray, in 2d array initialMatrix
        for (let row of initialMatrix) {
            // If object innerArray, function every(val => (val) != 0))
            if (row.every((val) => val !== 0)) {
                // increment variable count by 1
                count++;
            } else { // Else
                return false; // return false
            }
        }

        // If variable count is identical to 6
        if (count === 6) {
            // display alert dialog box that the game is over
            alert("Game Over! The board is full.");

            // Stop further input
            this.setState({ isGameOver: true });

            return true; // return true
        }
    }    

    // *********************************************************** //
    // ATTENTION!!!! The // comments MUST be removed for the JSX   //
    //               to render correctly!!!!!                      //
    // *********************************************************** //
    render() {
    return (
      <div className="wrapper">
        <div className="container">
          {Array(6)
            .fill(null)
            .map((_, rowIndex) => (
              <div key={rowIndex} className="grid-row">
                {Array(7)
                  .fill(null)
                  .map((_, colIndex) => (
                    <div
                      key={colIndex}
                      className="grid-box"
                      data-value={colIndex}
                      onClick={(e) => this.fillBox(e)}
                    ></div>
                  ))}
              </div>
            ))}
        </div>
        <div id="information">
          <div className="player-wrapper">
            Player 1 <div className="player1"></div>
          </div>
          <div className="player-wrapper">
            Player 2 <div className="player2"></div>
          </div>
        </div>
      </div>
    );
  }
}

// write the export default statement
export default ConnectFour;
