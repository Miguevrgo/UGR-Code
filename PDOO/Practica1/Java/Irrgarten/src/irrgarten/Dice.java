package irrgarten;

import java.util.Random;

public class Dice {
    private static final int MAX_USES = 5; // Maximum uses for both the weapons and shields
    private static final float MAX_INTELLIGENCE = 10; // Maximum intelligence for the player and the enemy
    private static final float MAX_STRENGTH = 10; // Maximum strength for the player and the enemy
    private static final float RESURRECT_PROB = 0.3F; // Probability of resurrecting after each round
    private static final int WEAPONS_REWARD = 2; // Maximum number of weapons rewarded when winning a combat
    private static final int SHIELDS_REWARD = 3; // Maximum number of shields rewarded when winning a combat
    private static final int HEALTH_REWARD = 5; // Maximum health rewarded when winning a combat
    private static final int MAX_ATTACK = 3; // Maximum attack power for the weapons
    private static final int MAX_SHIELD = 2; // Maximum shield power for the shields
    private static Random generator = new Random();

    /**
     * Returns a random number of row or column in the board, 0 represents
     * the row or column with less value
     * 
     * @param max number of rows or columns in the board
     * @return random number of row or column
     */
    public static int randomPos(int max) {
        return generator.nextInt(max);
    }

    /**
     * Returns who starts the game given the number of players
     * @param nPlayers number of players in the game
     * @return player who starts the game
     */
    public static int whoStarts(int nPlayers) {
        return generator.nextInt(nPlayers);
    }

    /**
     * Returns a random intelligence value in the range [0, MAX_INTELLIGENCE[
     * 
     * @return random intelligence value
     */
    public static float randomIntelligence() {
        return generator.nextFloat() * MAX_INTELLIGENCE;
    }

    /**
     * Returns a random strength value in the range [0, MAX_STRENGTH[
     * 
     * @return random strength value
     */
    public static float randomStrength() {
        return generator.nextFloat() * MAX_STRENGTH;
    }

    /**
     * Returns whether a dead player resurrects or not
     * 
     * @return true if the player resurrects, false otherwise
     */
    public static boolean resurrectPlayer() {
        return generator.nextFloat() <= RESURRECT_PROB;
    }

    /**
     * Returns the number of weapons the player will be given as a reward
     * for winning a combat, in the range [0, WEAPONS_REWARD]
     * 
     * @return number of weapons rewarded
     */
    public static int weaponsReward() {
        return generator.nextInt(WEAPONS_REWARD + 1); 
    }

    /**
     * Returns the number of shields the player will be given as a reward
     * for winning a combat, in the range [0, SHIELDS_REWARD]
     * 
     * @return number of shields rewarded
     */
    public static int shieldsReward() {
        return generator.nextInt(SHIELDS_REWARD + 1); 
    }

    /**
     * Returns the health the player will be given as a reward
     * for winning a combat, in the range [0, HEALTH_REWARD]
     * 
     * @return health rewarded
     */
    public static int healthReward() {
        return generator.nextInt(HEALTH_REWARD + 1); 
    }

    /**
     * Returns the power of the weapon the player will use in the combat
     * in the range [0, MAX_ATTACK[
     * 
     * @return power of the weapon
     */
    public static float weaponPower() {
        return generator.nextFloat() * MAX_ATTACK;
    }

    /**
     * Returns the power of the shield the player will use in the combat
     * in the range [0, MAX_SHIELD[
     * 
     * @return power of the shield
     */
    public static float shieldPower() {
        return generator.nextFloat() * MAX_SHIELD;
    }

    /**
     * Returns the number of uses left for the weapon or shield
     *
     * @return number of uses left
     */
    public int usesLeft() {
        return generator.nextInt(MAX_USES + 1);
    }

    /**
     * Returns a random competence value applied
     * @param competence competence of the player or the enemy
     * @return Random value in the range [0, competence[
     */
    public static float intensity(float competence) {
        return competence * generator.nextFloat();
    }

    /**
     * It returns true with a probability inversely proportional to the number of uses left
     * compared to the maximum number of uses, the border case being when the number of uses
     * left is 0, in which case it always returns true and the number of uses being the maximum
     * number of uses, in which case it always returns false
     * 
     * @param usesLeft number of uses left for the weapon or shield
     * @return
     */
    public boolean discardElement(int usesLeft) {
        float prob = (float) usesLeft / MAX_USES;
        return generator.nextFloat() >= prob;
    }

}
