/**
 * @file LabyrinthCharacter
 * @author Miguel Angel De la Vega Rodríguez
 * @author Alberto De la Vera Sánchez
 * @description This file contains the LabyrinthCharacter class, which serves
 * as an abstraction for Player and Monster Labyrinth characters
 */
package irrgarten;

abstract public class LabyrinthCharacter {
    private String name;

    private float intelligence;
    private float strength;
    private float health;
    
    private int row;
    private int col;
    
    /**
     * Constructor for class Labyrinth, it sets row and col to 0
     * 
     * @param name of the labyrinth character
     * @param intelligence of the labyrinth character
     * @param strength of the labyrinth character
     * @param health of the labyrinth character
     */
    public LabyrinthCharacter(String name, float intelligence, float strength, float health) {
        this.name = name;
        this.intelligence = intelligence;
        this.strength = strength;
        this.health = health;
        
        this.row = 0;
        this.col = 0;
    }

    /**
     * Copy constructor for class Labyrinth Character
     * 
     * @param other
     */
    public LabyrinthCharacter(LabyrinthCharacter other) {
        this(other.name, other.intelligence, other.strength, other.health);
        
        this.row = other.row;
        this.col = other.col;
    }

    /**
     * Returns whether the labyrinth character is dead or not
     * 
     * @return whether it is dead or not
     */
    public boolean dead() {
        return this.health <= 0;
    }

    /**
     * Returns the row of the labyrinth character
     * 
     * @return row
     */
    public int getRow() {
        return this.row;
    }

    /**
     * Returns the col of the labyrinth character
     * 
     * @return col
     */
    public int getCol() {
        return this.col;
    }

    /**
     * Returns the intelligence of the labyrinth character
     * 
     * @return intelligence
     */
    protected float getIntelligence() {
        return this.intelligence;
    }

    /**
     * Returns the strength of the labyrinth character
     * 
     * @return strength
     */
    protected float getStrength() {
        return this.strength;
    }

    /**
     * Returns the health of the labyrinth character
     * 
     * @return health
     */
    protected float getHealth() {
        return this.health;
    }

    /**
     * Sets the new health for the labyrinth character
     * 
     * @param health new health for the labyrinth character
     */
    protected void setHealth(float health) {
        this.health = health;
    }

    /**
     * Sets the new pos for the labyrinth character
     * 
     * @param row new row
     * @param col new col
     */
    public void setPos(int row, int col) {
        this.row = row;
        this.col = col;
    }

    /**
     * Returns a string with the current state of the Labyrinth character
     * 
     * @return String with the state
     */
    @Override
    public String toString() {
        String toReturn = "[" + name + ", ";
        toReturn += String.format("%.1f♥, %.3f, %.3f]\n", health, intelligence, strength);
        
        return toReturn; 
    }

    /**
     * This method decreases the health of the labyrinth character in one unit
     */
    protected void gotWounded() {
       --this.health; 
    }

    /**
     * Attack method to be implemented by the subclasses
     */
    abstract float attack();

    
    /**
     * Defend method to be implemented by the subclasses
     * @param attack attack value
     * @return
     */
    abstract boolean defend(float attack);
}
