package models;

public class Pig implements IEntity {
    private int weight = 0;

    public Pig(int weight) {
        this.weight = weight;
    }

    @Override
    public int getWeight() {
        return this.weight;
    }

    @Override
    public String toString() {
        return "Pig{" +
                "weight=" + weight +
                '}';
    }
}
