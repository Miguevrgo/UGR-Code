/**
 * @file Game.java
 * @author Miguel Angel De la Vega Rodríguez
 * @description This file contains the Game class, which provides methods
 * to manage the game, such as moving the players, managing the turns, and
 * checking if the game has finished
 */

package irrgarten;

import java.util.ArrayList;

public class Game {
    private static final int MAX_ROUNDS = 10;
    private int currentPlayerIndex;
    private String log;
    private Labyrinth labyrinth;
    private Player currentPlayer;
    private ArrayList<Player> players;
    private ArrayList<Monster> monsters;

    public Game(int nPlayers) {
        players = new ArrayList<>();
        monsters = new ArrayList<>();
        log = "";
        currentPlayerIndex = Dice.whoStarts(nPlayers);
        configureLabyrinth();
        for (char i = 0; i < nPlayers; ++i) {
            players.add(new Player(i, Dice.randomIntelligence(), Dice.randomStrength()));
        }
        currentPlayer = players.get(currentPlayerIndex);
    }

    /**
     * Returns whether the game has finished or not using the haveAWinner
     * method of the labyrinth
     *
     * @return true if the game has finished, false otherwise
     */
    public boolean finished() {
        return labyrinth.haveAWinner(); // ¿Consider MAX_ROUNDS?
    }

    /**
     * INFORMATION PROVIDED IN THE NEXT PRACTICE
     */
    public boolean nextStep(Directions preferredDirection) {
        throw new UnsupportedOperationException();
    }

    /**
     * Returns the current state of the game as a GameState object
     * 
     * @return current state of the game
     */
    public GameState getGameState() {
        String player="";
        String monster= "";
        for (int i = 0; i <players.size(); ++i) {
            player += players.get(i).toString();
        }
        for (int i = 0; i<monsters.size(); ++i) {
            monster += monsters.get(i).toString();
        }

        return new GameState(this.labyrinth.toString(),player,monster,
                this.currentPlayerIndex,this.finished(),this.log);
    }

    /**
     * Configures the labyrinth for the game, it adds obstacles and monsters 
     * saving them in this class
     *
     */
    private void configureLabyrinth() {
        labyrinth = new Labyrinth(5, 5, 2, 5);
        // Configure a labyrinth with obstacles and monsters
        labyrinth.addBlock(Orientation.VERTICAL,0,0,5);
        labyrinth.addBlock(Orientation.HORIZONTAL,4,1,1);
        labyrinth.addBlock(Orientation.HORIZONTAL,4,3,2);
        labyrinth.addBlock(Orientation.HORIZONTAL, 0,1,4);
        labyrinth.addBlock(Orientation.HORIZONTAL,2,2,3);
        labyrinth.addMonster(3,1, new Monster("Monster1", 0.5f, 0.5f, 3, 1));
    }

    /**
     * Updates both the attributes that store the current player and the index 
     * of the current player
     */
    private void nextPlayer() {
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
        currentPlayer = players.get(currentPlayerIndex);
    }

    /**
     * Information provided in the next practice
     */
    private Directions actualDirection(Directions preferredDirection) {
        throw new UnsupportedOperationException();
    }

    /**
     * Information provided in the next practice
     */
    private GameCharacter combat(Monster monster) {
        throw new UnsupportedOperationException();
    }

    /**
     * Information provided in the next practice
     */
    private void manageReward(GameCharacter winner) {
        throw new UnsupportedOperationException();
    }

    /**
     * Information provided in the next practice
     */
    private void manageResurrection() {
        throw new UnsupportedOperationException();
    }

    /**
     * Appends to the end of the attribute log the message indicating
     * that the player has won, it also adds a new line at the end
     */
    private void logPlayerWon() {
        log += "The player has won\n";
    }

    /**
     * Appends to the end of the attribute log the message indicating 
     * that the monster has won, it also adds a new line at the end
     */
    private void logMonsterWon() {
        log += "The monster has won\n";
    }

    /**
     * Appends to the end of the attribute log the message indicating
     * that the player has been resurrected, it also adds a new line at the end
     */
    private void logResurrected() {
        log += "The player has been resurrected\n";
    }

    /**
     * Appends to the end of the attribute log the message indicating
     * that the player has skipped his turn for being dead, it also adds a new line at the end
     */
    private void logPlayerSkipTurn() {
        log += "The player has skipped his turn for being dead\n";
    }

    /**
     * Appends to the end of the attribute log the message indicating
     * that the player has not followed the orders as it was not possible
     */
    private void logPlayerNoOrders() {
        log += "The player hasn't followed the orders\n";
    }

    /**
     * Appends to the end of the attribute log the message indicating
     * that the player has moved to an empty cell or has not moved
     * it also adds a new line at the end
     */
    private void logNoMonster() {
        log += "Player has moved to an empty cell or has not moved\n";
    }

    /**
     * Appends to the end of the attribute log the message indicating
     * that the game has finished after the maximum number of rounds
     */
    private void logRounds() {
        log += "The game has finished after " + MAX_ROUNDS + " rounds\n";
    }
}
