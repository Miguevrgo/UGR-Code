/**
 * @file Labyrinth.java
 * @author Miguel Angel De la Vega Rodríguez
 * @author Alberto De la Vera Sanchez
 * @description This file contains the Labyrinth class, which provides methods
 * to manage the labyrinth, such as adding monsters, players, blocks, and moving
 * the players
 */

package irrgarten;

import java.util.ArrayList;

public class Labyrinth {
    private static final char BLOCK_CHAR = 'X';
    private static final char EMPTY_CHAR = '-';
    private static final char MONSTER_CHAR = 'M';
    private static final char COMBAT_CHAR = 'C';
    private static final char EXIT_CHAR = 'E';
    private static final int ROW = 0;
    private static final int COL = 1;
    
    private int nRows;
    private int nCols;
    private int exitRow;
    private int exitCol;
    
    private char[][] labyrinth;
    private Monster[][] monsters;
    private Player[][] players;
    private static final int INVALID_POS = -1;

    public Labyrinth(int nRows, int nCols, int exitRow, int exitCol) {
        this.nRows = nRows;
        this.nCols = nCols;
        this.exitRow = exitRow;
        this.exitCol = exitCol;
        
        this.labyrinth = new char[nRows][nCols];
        this.monsters = new Monster[nRows][nCols];
        this.players = new Player[nRows][nCols];
        
        for (int i = 0; i < nRows; ++i) {
            for (int j = 0; j < nCols; ++j) {
                labyrinth[i][j] = EMPTY_CHAR;
            }
        }
        
        labyrinth[exitRow][exitCol] = EXIT_CHAR;

    }

    /**
     * Spreads de players all around the map
     * 
     * @param players
     */
    public void spreadPlayers(ArrayList<Player> players) {
        for (Player player : players) {
            int[] pos = randomEmptyPos();
            putPlayer2D(INVALID_POS, INVALID_POS, pos[ROW], pos[COL], player);
        }
    }

    /**
     * Returns true or false depending on whether a player is in the exit cell
     * or not
     *
     * @return true if a player is in the exit cell, false otherwise
     */
    public boolean haveAWinner() {
        return (players[exitRow][exitCol] != null);
    }

    /**
     * Returns a string with the complete state of the labyrinth
     *
     * @return a string with the complete state of the labyrinth
     */
    public String toString() {
        String returnString = "╔";
        for (int i = 0; i < nCols*2; ++i) { returnString += "═";}
        returnString += "╗\n";
        
        for (int i = 0; i < nRows; ++i) {
            returnString += "║";
            for (int j = 0; j < nCols; ++j) {
                returnString += labyrinth[i][j] + " ";
            }
            returnString += "║\n";
        }
        
        returnString += "╚";
        for (int i = 0; i < nCols*2; ++i) { returnString += "═";}
        returnString += "╝";
        return returnString;
    }

    /**
     * If the position provided is within the limits of the labyrinth and 
     * its empty, it adds a monster to the labyrinth in the position provided, keeps
     * the reference to the monster in the adequate container and sets the position 
     * of the monster (setPos)
     *
     * @param row row of the position where the monster is to be added
     * @param col column of the position where the monster is to be added
     * @param monster monster to be added to the labyrinth
     */
    public void addMonster(int row, int col, Monster monster) {
        if (posOK(row, col) && emptyPos(row, col)) {
            labyrinth[row][col] = MONSTER_CHAR;
            monsters[row][col] = monster;
            monster.setPos(row, col);
        }
    }

    /**
     * This method moves a player in the labyrinth on a direction, it
     * also tells if a monster has been found
     * 
     * @param direction direction to move
     * @param player to move
     * @return Whether there is a monster or not
     */
    public Monster putPlayer(Directions direction, Player player) {
        int oldRow = player.getRow();
        int oldCol = player.getCol();

        int[] newPos = dir2Pos(oldRow, oldCol, direction);
        return putPlayer2D(oldRow, oldCol, newPos[ROW], newPos[COL], player);
    }

    /**
     * It adds a block to the labyrinth
     * 
     * @param orientation of the block
     * @param startRow starting row
     * @param startCol starting col
     * @param length length of the block
     */
    public void addBlock(Orientation orientation, int startRow, int startCol, int length) {
        int incRow,incCol;
        if (orientation == Orientation.VERTICAL) {
            incRow = 1;
            incCol = 0;
        }
        else{
            incRow = 0;
            incCol = 1;
        }

        int row = startRow;
        int col = startCol;

        while (posOK(row, col) && emptyPos(row, col) && length > 0) {
            labyrinth[row][col] = BLOCK_CHAR;
            row += incRow;
            col += incCol;
            length--;
        }
    }

    /**
     * Returns the valid moves for a given position in the labyrinth
     *
     * @param row row of the position to be checked
     * @param col column of the position to be checked
     * @return Array with the valid moves for the position provided
     */
    public ArrayList<Directions> validMoves(int row, int col) {
        ArrayList<Directions> output = new ArrayList<Directions>();
        if (canStepOn(row-1, col)) {
            output.add(Directions.UP);
        }
        if (canStepOn(row+1, col)) {
            output.add(Directions.DOWN);
        }
        if (canStepOn(row, col-1)) {
            output.add(Directions.LEFT);
        }
        if (canStepOn(row, col+1)) {
            output.add(Directions.RIGHT);
        }

        return output;
    }

    /**
     * Returns whether the position provided is within the limits of the labyrinth
     * or not
     *
     * @param row row of the position to be checked
     * @param col column of the position to be checked
     * @return true if the position is within the limits of the labyrinth, false
     * otherwise
     */
    private boolean posOK(int row, int col) {
        return row >= 0 && row < nRows && col >= 0 && col < nCols;
    }

    /**
     * Returns whether the position provided is empty or not
     *
     * @param row row of the position to be checked
     * @param col column of the position to be checked
     * @return true if the position is empty, false otherwise
     */
    private boolean emptyPos(int row, int col) {
        return labyrinth[row][col] == EMPTY_CHAR;
    }

    /**
     * Returns whether the position provided is a monster or not
     *
     * @param row row of the position to be checked
     * @param col column of the position to be checked
     * @return true if the position is a monster, false otherwise
     */
    private boolean monsterPos(int row, int col) {
        return labyrinth[row][col] == MONSTER_CHAR;
    }

    /**
     * Returns whether the position provided is the exit or not
     *
     * @param row row of the position to be checked
     * @param col column of the position to be checked
     * @return true if the position is the exit, false otherwise
     */
    private boolean exitPos(int row, int col) {
        return labyrinth[row][col] == EXIT_CHAR;
    }

    /**
     * Returns whether the position provided is a combat position or not
     *
     * @param row row of the position to be checked
     * @param col column of the position to be checked
     * @return true if the position is a combat position, false otherwise
     */
    private boolean combatPos(int row, int col) {
        return labyrinth[row][col] == COMBAT_CHAR;
    }

    /**
     * Returns whether the position provided is within the limits of the 
     * labyrinth and is not a player or a block
     *
     * @param row row of the position to be checked
     * @param col column of the position to be checked
     * @return true if the position is within the limits of the labyrinth and is not a
     * player or a block, false otherwise
     */
    private boolean canStepOn(int row, int col) {
        return posOK(row, col) && (emptyPos(row, col) || monsterPos(row, col) || exitPos(row, col));
    }

    /**
     * This method updates the position of the player who is turned into a fuzzy
     * player when resurrected
     * @param this Fuzzy player whose position has to be updated;
     */
    public void updatePos(FuzzyPlayer fuzzy) {
        this.players[fuzzy.getRow()][fuzzy.getCol()] = fuzzy;
    }

    /**
     * This method only updates the position if the position provided is 
     * within the limits of the labyrinth if it's within the limits of the labyrinth,
     * it updates the old position of the player considering that a combat position
     * is now a monster.
     *
     * @param row row of the position to be updated
     * @param col column of the position to be updated
     */
    private void updateOldPos(int row, int col) {
        if (posOK(row, col)) {
            if (combatPos(row, col)) {
                labyrinth[row][col] = MONSTER_CHAR;
            }
            else {
                labyrinth[row][col] = EMPTY_CHAR;
            }
        }
    }

    /**
     * This method calculates the position in the labyrinth where the player
     * would be moved if it moves in the direction provided. It is not necessary
     * to check if the position is within the limits of the labyrinth.
     * 
     * @param row
     * @param col
     * @param direction
     * @return the position in the labyrinth where the player would be moved
     */
    private int[] dir2Pos(int row, int col, Directions direction) {
        switch (direction) {
            case UP:
                row -= 1;
                break;
            case DOWN:
                row += 1;
                break;
            case LEFT:
                col -= 1;
                break;
            case RIGHT:
                col += 1;
                break;
        }
        return new int[]{row, col};
    }

    /**
     * Using the dice, it generates a random position within the labyrinth providing it
     * is empty, it generates infinite random positions until it finds an empty one, if no
     * empty position is found, it never stops.
     *
     * @return a random empty position within the labyrinth
     */
    private int[] randomEmptyPos() {
        int[] pos = new int[2];
        do {
            pos[0] = Dice.randomPos(nRows);
            pos[1] = Dice.randomPos(nCols);
        } while (!emptyPos(pos[0], pos[1]));

        return pos;
    }

    /**
     * This method moves a player in the labyrinth in a direction, it goes
     * from [oldRow,oldCol] to [row,col].
     * 
     * @param oldRow Old row of a player
     * @param oldCol Old col of a player
     * @param row New position of a player
     * @param col New position of a player
     * @param player to move
     * @return Monster which can be in the position
     */
    private Monster putPlayer2D(int oldRow, int oldCol, int row, int col, Player player) {
        Monster output = null;

        if (canStepOn(row, col)) {
            if(posOK(oldRow, oldCol)) {
                if (player == players[oldRow][oldCol]) {
                    updateOldPos(oldRow, oldCol);
                    players[oldRow][oldCol] = null;
                }
            }
        }

        if (monsterPos(row, col)) {
            labyrinth[row][col] = COMBAT_CHAR;
            output = monsters[row][col];
        }
        else{
            labyrinth[row][col] = player.getNumber();
        }

        players[row][col] = player;
        player.setPos(row, col);
        return output;
    }

}
