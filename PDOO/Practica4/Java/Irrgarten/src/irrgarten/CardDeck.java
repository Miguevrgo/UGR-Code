package irrgarten;

import java.util.ArrayList;
import java.util.Collections;

public abstract class CardDeck<T extends CombatElement> {
    private ArrayList<T> cardDeck;

    public CardDeck() {
        cardDeck = new ArrayList<>();
    }

    protected abstract void addCards();

    /**
     * This methods add provided Card to the deck of cards
     * 
     * @param card to be added to the deck
     */
    protected void addCard(T card) {
        cardDeck.add(card);
    }

    /**
     * This method returns the first card in the Deck and erases it from
     * the Deck of cards, if empty, it adds cards using addCards() and shuffles
     * them
     * 
     * @return Next card of the Deck
     */
    public T nextCard() {
        if (cardDeck.isEmpty()) {
            addCards();
            Collections.shuffle(cardDeck);
        }
        
        T toReturn = cardDeck.get(0);
        cardDeck.remove(0);
        return toReturn;
    }
}
