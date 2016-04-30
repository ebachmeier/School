"use strict";

var Cell = function (id, view) {
        this.id = id;
        this.view = view;
        this.value = ' ';
}

Cell.prototype.getValue = function () {
        return this.value;
}

Cell.prototype.setValue = function (newValue) {
        this.value = newValue;
}

Cell.prototype.updateView = function () {
        this.view.innerHTML = this.getValue();
}

var Grid3x3 = function () {
        this.cells = new Array(9);
        for (var i = 0; i < this.cells.length; ++i) {
            this.cells[i] = new Cell(i, document.getElementById("cell" + i));
        }
}

Grid3x3.prototype.getCellById = function (id) {
        return this.cells[id];
}

Grid3x3.prototype.getCellByPosition = function (r,c) {
        return this.getCellById(this.getIdByPosition(r,c));
}

Grid3x3.prototype.getIdByPosition = function (r,c) {
        return r * 3 + c;
}

Grid3x3.prototype.updateView = function () {
        for (var i = 0; i < this.cells.length; ++i) {
            this.getCellById(i).updateView();
        }
}

var isWin = function (getValueByPosition,cellValue) {
    var isWin = false;

    for (var r = 0; !isWin && (r < 3); ++r) {
        isWin = true;
        for (var c = 0; isWin && (c < 3); ++c) {
            if (getValueByPosition(r,c) != cellValue) { 
                isWin = false;
            }
        }
    }

    for (var c = 0; !isWin && (c < 3); ++c) {
        isWin = true;
        for (var r = 0; isWin && (r < 3); ++r) {
            if (getValueByPosition(r,c) != cellValue) { 
                isWin = false;
            }
        }
    } 

    if (!isWin) {
        isWin = true;
        for (var i = 0; isWin && (i < 3); ++i) {
            if (getValueByPosition(i,i) != cellValue) {
                isWin = false;
            }
        }
    }

    if (!isWin) {
        isWin = true;
        for (var i = 0; isWin && (i < 3); ++i) {
            if (getValueByPosition(i,2-i) != cellValue) {
                isWin = false;
            }
        }
    }

    return isWin;
}

var minimax = function(grid, cellValue) {
    var choice = undefined;

    var getValueByPosition = function (r,c) {
        return grid.getCellByPosition(r,c).getValue();
    }

    var opponentCellValue = function (cellValue) {
        switch (cellValue) {
            case 'X' : 
                return 'O';
            case 'O':
                return 'X';
        }
    }

    var loop = function (cellValue) {
        if (isWin(getValueByPosition, 'X')) {
            return 10;
        }

        if (isWin(getValueByPosition, 'O')) {
            return -10;
        }

        var scores = new Array();

        for (var i = 0; i < 9; ++i) {
            var cell = grid.getCellById(i);
            if (cell.getValue() === ' ') {
                cell.setValue(cellValue);
                scores[i] = loop(opponentCellValue(cellValue));
                cell.setValue(' ');
            }
        }

        if (scores.length == 0) {
            return 0;
        } else {
            choice = undefined;

            switch (cellValue) {
                case 'X':
                    for (var i in scores) {
                        if (choice === undefined || scores[i] > scores[choice]) {
                            choice = i;
                        }
                    }
                    break;
                case 'O':
                    for (var i in scores) {
                        if (choice === undefined || scores[i] < scores[choice]) {
                            choice = i;
                        }
                    }
                    break;
            }

            return scores[choice];
        }
    }

    loop(cellValue);
    return choice;
}

var printMessage = function (message) {
    document.getElementById("message").innerHTML = message;
}

var grid = new Grid3x3();

document.getElementById("tictactoe").onclick = function(e) {
    var re = /cell([0-8])/;
    var result = re.exec(e.target.id);
    var id = result[1];
    printMessage("");
    if (grid.getCellById(id).getValue() !== ' ') {
       printMessage("You cannot move on top of a square that is already taken.");
       return true;
    }
    var yourChoice = minimax(grid, 'X');
    if (yourChoice === undefined) {
       printMessage("You lost.");
       return true;
    }
    grid.getCellById(id).setValue('X');
    var choice = minimax(grid, 'O');
    if (choice === undefined) {
       printMessage("You drew, congratulations human.");
       return true;
    }
    grid.getCellById(choice).setValue('O');
    grid.updateView();
}
