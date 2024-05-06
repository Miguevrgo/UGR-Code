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
    
    /*----------------------------Custom Labyrinth----------------------------*/
    private static final int ROWS = 11;
    private static final int COLS = 10;
    
    private static final int NMONSTERS = 5;
    private static final int[][] MONSTERS_POS = {{0,0},{1,6},{2,2},{5,5},{7,1}};
    
    private static final int NBLOCKS = 4;
    private static final Object[][] BLOCKS_POS = {{Orientation.HORIZONTAL,0,1,4},
                                                  {Orientation.HORIZONTAL,9,0,2},
                                                  {Orientation.VERTICAL,2,8,7},
                                                  {Orientation.VERTICAL,3,3,4}};
    
    private int currentPlayerIndex;
    private Player currentPlayer;
    private String log;
    private Labyrinth labyrinth;
    private ArrayList<Player> players;
    private ArrayList<Monster> monsters;

    /**
     * Constructor for the game, it receives the number of players and sets up
     * the labyrinth for the players to play 
     * 
     * @param nPlayers number of players
     */
    public Game(int nPlayers) {
        int exitRow = Dice.randomPos(ROWS);
        int exitCol = Dice.randomPos(COLS);
        
        
        players = new ArrayList<>();
        monsters = new ArrayList<>();
        
        for (int playerNum = 0; playerNum < nPlayers; ++playerNum) {
            players.add(new Player(Character.forDigit(playerNum,10), Dice.randomIntelligence(), Dice.randomStrength()));
        }
        
        currentPlayerIndex = Dice.whoStarts(nPlayers);
        currentPlayer = players.get(currentPlayerIndex);
        
        labyrinth = new Labyrinth(ROWS, COLS, exitRow, exitCol);
        configureLabyrinth();
        labyrinth.spreadPlayers(players);
        
        
        log = "╔════════════════════════════╗\n" +
              "║    The Game has started!   ║\n" +
              "╚════════════════════════════╝\n\n";
        
    }

    /**
     * Returns whether the game has finished or not using the haveAWinner
     * method of the labyrinth
     *
     * @return true if the game has finished, false otherwise
     */
    public boolean finished() {
        return this.labyrinth.haveAWinner();
    }

    /**
     * It manages a whole turn in the game.
     * 
     * @param preferredDirection direction in which the player prefers to go
     * @return Whether the game ended or not
     */
    public boolean nextStep(Directions preferredDirection) {
        boolean dead = currentPlayer.dead();
        log = "";

        if (!dead) {
            Directions direction = actualDirection(preferredDirection);
            if (direction != preferredDirection) {
                logPlayerNoOrders();
            }
            Monster monster = labyrinth.putPlayer(direction, currentPlayer);
            
            if (monster == null) {
                logNoMonster();
            }
            else{
                GameCharacter winner = combat(monster);
                manageReward(winner);
            }

        }
        else{
            manageResurrection();
        }

        boolean endGame = finished();

        if (!endGame) {
            nextPlayer();
        }
        
        return endGame;
    }

    /**
     * Returns the current state of the game as a GameState object formatted
     * 
     * @return current state of the game
     */
    public GameState getGameState() {
        String player="";
        String monster= "";
        
        for (int i = 0; i < players.size(); ++i) {
            player += players.get(i).toString() + "\n";
        }
        for (int i = 0; i < monsters.size(); ++i) {
            monster += monsters.get(i).toString()+ "\n";
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
        for (int i = 0; i < NMONSTERS; ++i) {
            Monster monster = new Monster("Monster " + i, Dice.randomIntelligence(),
                Dice.randomStrength());
            
            monsters.add(monster);
            labyrinth.addMonster(MONSTERS_POS[i][0], MONSTERS_POS[i][1], monster);
        }
        
        for (int i = 0; i < NBLOCKS; ++i) {
            labyrinth.addBlock((Orientation)BLOCKS_POS[i][0], (int)BLOCKS_POS[i][1],
                    (int)BLOCKS_POS[i][2], (int)BLOCKS_POS[i][3]);
        }
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
     * Returns the actual direction where the player moves considering the
     * preferred direction 
     * 
     * @param preferredDirection direction which the player prefers to go to
     * @return Actual direction where the players goes
     */
    private Directions actualDirection(Directions preferredDirection) {
        int currentRow = currentPlayer.getRow();
        int currentCol = currentPlayer.getCol();

        ArrayList<Directions> validMoves = labyrinth.validMoves(currentRow, currentCol);

        return currentPlayer.move(preferredDirection, validMoves);
    }

    /**
     * This method is responsible for managing combat between a player
     * and a monster, it returns the winner of the combat
     * 
     * @param monster monster which is in combat with current player
     * @return who wins
     */
    private GameCharacter combat(Monster monster) {
        int rounds = 0;
        GameCharacter winner = GameCharacter.PLAYER;
        boolean lose = monster.defend(currentPlayer.attack());

        while (!lose && rounds < MAX_ROUNDS) {
            winner = GameCharacter.MONSTER;
            rounds++;

            lose = currentPlayer.defend(monster.attack());

            if (!lose) {
                winner = GameCharacter.PLAYER;
                lose = monster.defend(currentPlayer.attack());
            }
        }
        
        logRounds(rounds,MAX_ROUNDS);
        return winner;
    }

    /**
     * This method manages the rewards produced when finished a combat
     * it also logs whether one of them has won
     * 
     * @param winner of the combat
     */
    private void manageReward(GameCharacter winner) {
        if (winner == GameCharacter.PLAYER) {
            currentPlayer.receiveReward();
            logPlayerWon();
        }
        else{
            logMonsterWon();
        }
    }

    /**
     * This method manages the resurrection of a player
     */
    private void manageResurrection() {
        if (Dice.resurrectPlayer()) {
            currentPlayer.resurrect();
            logResurrected();
        }
        else{
            logPlayerSkipTurn();
        }
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
     * the rounds 
     */
    private void logRounds(int rounds, int max) {
        log += "Rounds: " + rounds + "|" + max + "\n";
    }
}
