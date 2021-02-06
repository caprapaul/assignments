package models;

public class Bird implements IEntity {
    private int weight = 0;

    public Bird(int weight) {
        this.weight = weight;
    }

    @Override
    public int getWeight() {
        return this.weight;
    }

    @Override
    public String toString() {
        return "Bird{" +
                "weight=" + weight +
                '}';
    }
}
