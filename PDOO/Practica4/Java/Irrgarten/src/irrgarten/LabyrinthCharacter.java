/**
 * @file LabyrinthCharacter
 * @description This file contains the LabyrinthCharacter class, which serves
 * as a father for Player and Monster //TODO:
 */
package irrgarten;

abstract public class LabyrinthCharacter {
    private String name;

    private float intelligence;
    private float strength;
    private float health;
    
    private int row;
    private int col;
    

    public LabyrinthCharacter(String name, float intelligence, float strength, float health) {
        this.name = name;
        this.intelligence = intelligence;
        this.strength = strength;
        this.health = health;
        
        this.row = 0;
        this.col = 0;
    }

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

    public int getRow() {
        return this.row;
    }

    public int getCol() {
        return this.col;
    }

    protected float getIntelligence() {
        return this.intelligence;
    }

    protected float getStrength() {
        return this.strength;
    }

    protected float getHealth() {
        return this.health;
    }

    protected void setHealth(float health) {
        this.health = health;
    }

    public void setPos(int row, int col) {
        this.row = row;
        this.col = col;
    }

    public String toString() {
        String toReturn = "[" + name + ", ";
        toReturn += String.format("%.1f♥, %.3f, %.3f]\n", health, intelligence, strength);
        
        return toReturn; 
    }

    protected void gotWounded() {
       --this.health; 
    }

    abstract float attack();

    abstract boolean defend(float attack);
}



































