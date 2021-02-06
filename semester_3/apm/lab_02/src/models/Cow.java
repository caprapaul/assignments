package models;

public class Cow implements IEntity {
    private int weight = 0;

    public Cow(int weight) {
        this.weight = weight;
    }

    @Override
    public int getWeight() {
        return this.weight;
    }

    @Override
    public String toString() {
        return "Cow{" +
                "weight=" + weight +
                '}';
    }
}
