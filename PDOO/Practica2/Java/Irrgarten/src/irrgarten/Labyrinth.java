/**
 * @file Labyrinth.java
 * @author Miguel Angel De la Vega Rodríguez
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
     * INFORMATION PROVIDED IN THE NEXT PRACTICE
     */
    public void spreadPlayers(Player[] players) {
        throw new UnsupportedOperationException();
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
        String returnString = "";
        for (int i = 0; i < nRows; ++i) {
            for (int j = 0; j < nCols; ++j) {
                returnString += labyrinth[i][j];
            }
            returnString += "\n";
        }
        return returnString;
    }

    /**
     * If the position provided is within the limits of the labyrinth and its empty, 
     * it adds a monster to the labyrinth in the position provided, keeps the 
     * reference to the monster in the adequate container and sets the position 
     * of the monster (setPos)
     *
     * @param row row of the position where the monster is to be added
     * @param col column of the position where the monster is to be added
     * @param monster monster to be added to the labyrinth
     */
    public void addMonster(int row, int col, Monster monster) {
        if (emptyPos(row, col)) {
            labyrinth[row][col] = MONSTER_CHAR;
            monsters[row][col] = monster;
            monster.setPos(row, col);
        }
    }

    /**
     * INFORMATION PROVIDED IN THE NEXT PRACTICE
     */
    public Monster putPlayer(Directions direction, Player player) {
        throw new UnsupportedOperationException();
    }

    /**
     * INFORMATION PROVIDED IN THE NEXT PRACTICE
     */
    public void addBlock(Orientation orientation, int startRow, int startCol, int length) {
        throw new UnsupportedOperationException();
    }

    /**
     * Returns the valid moves for a given position in the labyrinth
     *
     * @param row row of the position to be checked
     * @param col column of the position to be checked
     * @return Array with the valid moves for the position provided
     */
    public Directions[] validMoves(int row, int col) {
        ArrayList<Directions> validMoves = new ArrayList<Directions>();
        if (posOK(row - 1, col) && labyrinth[row - 1][col] != BLOCK_CHAR) {
            validMoves.add(Directions.UP);
        }
        if (posOK(row + 1, col) && labyrinth[row + 1][col] != BLOCK_CHAR) {
            validMoves.add(Directions.DOWN);
        }
        if (posOK(row, col - 1) && labyrinth[row][col - 1] != BLOCK_CHAR) {
            validMoves.add(Directions.LEFT);
        }
        if (posOK(row, col + 1) && labyrinth[row][col + 1] != BLOCK_CHAR) {
            validMoves.add(Directions.RIGHT);
        }
        return validMoves.toArray(new Directions[0]); //TODO: Revisar P3
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
    private boolean emptyPos(int row, int col) { //TODO: ¿posOK?
        return posOK(row, col) && labyrinth[row][col] == EMPTY_CHAR; //TODO: Comprobar Jugadores
    }

    /**
     * Returns whether the position provided is a monster or not
     *
     * @param row row of the position to be checked
     * @param col column of the position to be checked
     * @return true if the position is a monster, false otherwise
     */
    private boolean monsterPos(int row, int col) {
        return posOK(row, col) && monsters[row][col] != null;
    }

    /**
     * Returns whether the position provided is the exit or not
     *
     * @param row row of the position to be checked
     * @param col column of the position to be checked
     * @return true if the position is the exit, false otherwise
     */
    private boolean exitPos(int row, int col) {
        return posOK(row, col) && labyrinth[row][col] == EXIT_CHAR;
    }

    /**
     * Returns whether the position provided is a combat position or not
     *
     * @param row row of the position to be checked
     * @param col column of the position to be checked
     * @return true if the position is a combat position, false otherwise
     */
    private boolean combatPos(int row, int col) {
        return posOK(row,col) && labyrinth[row][col] == COMBAT_CHAR;
    }

    /**
     * Returns whether the position provided is within the limits of the labyrinth and
     * is not a player or a block
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
     * This method only updates the position if the position provided is within the limits of the labyrinth
     * if it's within the limits of the labyrinth, it updates the old position of the player considering that
     * a combat position is now a monster.
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
            players[row][col] = null;
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
                row += 1;
                break;
            case DOWN:
                row -= 1;
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
     * INFORMATION PROVIDED IN THE NEXT PRACTICE
     */
    private Monster putPlayer2D(int oldRow, int oldCol, int row, int col, Player player) {
        throw new UnsupportedOperationException();
    }
}
