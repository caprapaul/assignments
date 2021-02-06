package models;

import javafx.beans.property.SimpleStringProperty;
import models.values.IValue;

public class SymbolsRow {
    private final SimpleStringProperty name;
    private final SimpleStringProperty value;

    public SymbolsRow(String name, IValue value) {
        this.name = new SimpleStringProperty(name);
        this.value = new SimpleStringProperty(value.toString());
    }

    private String getName() {
        return this.name.get();
    }

    public SimpleStringProperty nameProperty() {
        return this.name;
    }

    private String getValue() {
        return this.value.get();
    }

    public SimpleStringProperty valueProperty() {
        return this.value;
    }
}
