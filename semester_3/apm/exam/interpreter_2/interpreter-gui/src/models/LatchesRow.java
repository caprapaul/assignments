package models;

import javafx.beans.property.SimpleIntegerProperty;

public class LatchesRow {
    private final SimpleIntegerProperty address;
    private final SimpleIntegerProperty value;

    public LatchesRow(int address, int value) {
        this.address = new SimpleIntegerProperty(address);
        this.value = new SimpleIntegerProperty(value);
    }

    private int getAddress() {
        return this.address.get();
    }

    public SimpleIntegerProperty addressProperty() {
        return this.address;
    }

    private int getValue() {
        return this.value.get();
    }

    public SimpleIntegerProperty valueProperty() {
        return this.value;
    }
}
