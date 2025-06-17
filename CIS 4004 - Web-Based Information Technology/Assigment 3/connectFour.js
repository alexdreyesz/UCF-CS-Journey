// Initial references
// Create global variables for the different elements in the document
// The querySelector() method returns the first element that matches a CSS selector 
// The getElementById() method returns the element that matches the ID

// Declare constant container set equal to object document, method querySelector, passing as an argument class ".container"
const container = document.querySelector(".container");

// Declare constant playerTurn set equal to object document, method getElementById, passing as an argument id "playerTurn"
const playerTurn = document.getElementById("playerTurn");

// Declare constant message set equal to object document, method getElementById, passing as an argument id "message"
const message = document.getElementById("message");

// Declare variable initialMatrix as a 2d array, 6 rows, 7 columns, initialized to all 0s
var initialMatrix = Array(6).fill(0).map(() => Array(7).fill(0));

// Declare variable currentPlayer to store the current player
var currentPlayer;

var isGameOver = false;

// Write function gameOverCheck
function gameOverCheck() {
    console.log("gameOverCheck");
        
    // Declare variable count, initialized to 0
    var count = 0;
    
    // Iterate through the 2d array initialMatrix
    // Write a for/of loop to iterate through the rows, loop control variable innerArray, in 2d array initialMatrix
    for (let innerArray of initialMatrix) {
        // If object innerArray, function every(val => (val) != 0))
        if(innerArray.every(val => val != 0)) {
            // increment variable count by 1
            count++;
        } else { // Else
            // return false
            return false 
        }
    }
  
    // If variable count is equal to 6
    if(count === 6) {
        // Set constant message, property innerText, equal to "Game Over"
        message.innerText = "Game Over";
        // return false
        return false   
    }

    return true; // Continue the game if not all rows are filled
}

// Write function winCheck 
function winCheck (row, column) {
    console.log("winCheck");
    // Write decision making logic, if function call checkHorizontal, checkVertical, checkPositiveDiagonal, or checkNegativeDiagonal is true, return true
    if (checkHorizontal(row) || checkVertical(column) || checkPositiveDiagonal(row, column) || checkNegativeDiagonal(row, column)) {
        return true;
    } else { // else return false
        return false;
    }
}

// Write function checkHorizontal to do the following
function checkHorizontal(row) {
    let count = 0; 

    // Write a nest for loop to iterate through the rows and columns
    for (let col = 0; col < initialMatrix[row].length; col++) {
        // if the currentPlayer has four discs in a row horizontally, return true
        if (initialMatrix[row][col] === currentPlayer) {
            count++; 
            // Check if we have four in a row
            if (count === 4) {
                return true;
            }
        } else {
            count = 0; // Reset count if the sequence is broken
        }
    }
    
    // return false
    return false;
}

// Write function checkVertical to do the following
function checkVertical(column) {
    let count = 0;

    // Write a nest for loop to iterate through the rows and columns
    for (let row = 0; row < initialMatrix.length; row++) {
        // if the currentPlayer has four discs in a row vertically, return true
        if (initialMatrix[row][column] === currentPlayer) {
            count++; 
            // Check if we have four in a row
            if (count === 4) {
                return true;
            }
        } else {
            count = 0; // Reset count if the sequence is broken
        }
    }
    
    // return false
    return false; 
}

// Write function checkPositiveDiagonal to do the following
function checkPositiveDiagonal(row, column) {
    // Write a nest for loop to iterate through the rows and columns
    for (let r = row, c = column; r >= 0 && c < initialMatrix[0].length; r--, c++) {
        let count = 0; 

        // Check the diagonal
        for (let offset = 0; offset < 4; offset++) {
            // if the currentPlayer has four discs in a row diagonally, bottom right to top left, return true
            if (r + offset < initialMatrix.length && c - offset >= 0) {
                if (initialMatrix[r + offset][c - offset] === currentPlayer) {
                    count++;
                    // Check if we have four in a row
                    if (count === 4) {
                        return true;
                    }
                } else {
                    break; // Break if the current cell does not match
                }
            }
        }
    }
    
    // return false 
    return false; 
}

// Write function checkNegativeDiagonal to do the following
function checkNegativeDiagonal(row, column) {
    // Write a nest for loop to iterate through the rows and columns
    for (let r = row, c = column; r >= 0 && c >= 0; r--, c--) {
        let count = 0; 

        // Check the diagonal
        for (let offset = 0; offset < 4; offset++) {

            if (r + offset < initialMatrix.length && c + offset < initialMatrix[0].length) {
                // if the currentPlayer has four discs in a row diagonally, bottom left to top right, return true
                if (initialMatrix[r + offset][c + offset] === currentPlayer) {
                    count++;
                    // Check if we have four in a row
                    if (count === 4) {
                        return true;
                    }
                } else {
                    break; // Break if the current cell does not match
                }
            }
        }
    }
    
    // return false  
    return false;
}

// Write function setPiece 
function setPiece(startCount, colValue) {
    console.log("setPiece");

    // Declare variable rows initialized to object document, method querySelectorAll, passing argument class ".grid-row"
    let rows = document.querySelectorAll(".grid-row");
    
    // Add exception handling so the player cannot click a full column
    // Current if/else should be wrapped inside a try{} block
    try {
        // If the element in array initialMatrix at indexes parameters startCount and colValue is NOT equal to 0   
        if(initialMatrix[startCount][colValue] != 0) {
            // Decrement parameter startCount by 1
            startCount--;
            
            // Call function setPiece, passing as arguments parameters startCount and colValue
            return setPiece(startCount, colValue);
        } else { // Else
            // Declare variable currentRow initialized to array rows, index startCount, method querySelectorAll, passing as an argument class ".grid-box"
            let currentRow = rows[startCount].querySelectorAll(".grid-box");
        
            // Modify currentRow, index colValue, object classlist, method add, passing as arguments "filled" and `player${currentPlayer}` 
            currentRow[colValue].classList.add("filled", `player${currentPlayer}`);
        
            // Update array initialMatrix, indexes startCount and colValue, set equal to currentPlayer
            initialMatrix[startCount][colValue] = currentPlayer;
            
            // If function call winCheck, passing as arguments parameters startCount and colValue is true
            if(winCheck(startCount, colValue)) {
                // Set object message's innerHTML equal to `Player<span> ${currentPlayer}</span> wins` 
                message.innerHTML = `Player<span> ${currentPlayer}</span> wins`;

                isGameOver = true;
                
                // Return false
                return false
            }
        }

    } catch (e) { // The catch(e){} block should display and alert dialog box informing the player "Column full, select again"
        alert("Column full, select again");

         // Switch the currentPlayer, if currently 1 then 2, if currently 2, then 1
        if(currentPlayer === 1) {
            currentPlayer = 2;
        }  else {
            currentPlayer = 1;
        }
    }
    
    // Call function gameOverCheck
    gameOverCheck();
}

// Write function fillBox 
function fillBox(e) {
    console.log("fillBox");

    if (isGameOver) {
        return;
    }

    // Declare variable colValue set equal to function parseInt() of parameter e, object target, function getAttribute, passing as argument "data-value"
    var colValue = parseInt(e.target.getAttribute("data-value"));

    // Call function setPiece, passing arguments 5 (because we have 6 rows, 0 - 5) and variable colValue 
    setPiece(5, colValue);

    // Switch the currentPlayer, if currently 1 then 2, if currently 2, then 1
    if(currentPlayer === 1) {
        currentPlayer = 2;
    }  else {
        currentPlayer = 1;
    }

    // Set playerTurn's innerHTML to `Player <span>${currentPlayer}'s</span> turn`
    document.getElementById("playerTurn").innerHTML = `Player <span>${currentPlayer}'s</span> turn`;
}

// Write function createBoard 
function createBoard() {
    console.log("createBoard");
    
    // Iterate through the 2d array initialMatrix
    // Write an outer for in loop to iterate through the rows, loop control variable innerArray, in 2d array initialMatrix
    for (let innerArray in initialMatrix) { 
        // Declare variable outerDiv set equal to object document, method createElement, passing "div" as an argument
        let outerDiv = document.createElement("div");
    
        // Modify outerDiv, object classList, calling method add, passing argument "grid-row"
        outerDiv.classList.add("grid-row");
        
        // Modify outerDiv calling method setAttribute, passing arguments "data-value" and loop control variable innerArray
        outerDiv.setAttribute("data-value", innerArray);

        // Write an inner for in loop to iterate through the columns, loop control variable j, in 2d array initialMatrix, index innerArray    
        for (let j in initialMatrix[innerArray]) {
            // Set each element in array initialMatrix to the value of 0
            initialMatrix[innerArray][j] = 0;

            // Declare variable innerDiv set equal to object document, method createElement, passing "div" as an argument
            let innerDiv = document.createElement("div");

            // Modify innerDiv, object classList, method add, passing argument "grid-box"
            innerDiv.classList.add("grid-box");

            // Modify innerDiv, calling method setAttribute, passing arguments "data-value" and loop control variable j
            innerDiv.setAttribute("data-value", j);

            // Modify innerDiv, method addEventListener, passing arguments "click" and (e) => { fillBox(e); }
            innerDiv.addEventListener("click", (e) => { fillBox(e); });

            // Modify outerDiv, method appendChild, passing argument innerDiv
            outerDiv.appendChild(innerDiv);
        }
        
        // Modify container. method appendChild, passing argument outerDiv
        container.appendChild(outerDiv);
    }
}

// Write function startGame 
function startGame() {
    console.log("startGame");

    // Set currentPlayer to 1, player 1 always goes first
    currentPlayer = 1;
    isGameOver = false;

    // Set the container's innerHTML to an empty string
    const container = document.querySelector(".container");
    container.innerHTML = '';

    // Call function createBoard
    createBoard();
    
    // Set playerTurn's innerHTML to `Player <span>${currentPlayer}'s</span> turn`
    const playerTurn = document.getElementById("playerTurn");
    playerTurn.innerHTML = `Player <span>${currentPlayer}</span>'s turn`;
}

// For the window.onload event, call function startGame
window.onload = startGame;