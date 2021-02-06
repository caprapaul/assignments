package models;

import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import models.values.IValue;

public class HeapRow {
    private final SimpleIntegerProperty address;
    private final SimpleStringProperty value;

    public HeapRow(int address, IValue value) {
        this.address = new SimpleIntegerProperty(address);
        this.value = new SimpleStringProperty(value.toString());
    }

    private int getAddress() {
        return this.address.get();
    }

    public SimpleIntegerProperty addressProperty() {
        return this.address;
    }

    private String getValue() {
        return this.value.get();
    }

    public SimpleStringProperty valueProperty() {
        return this.value;
    }
}
