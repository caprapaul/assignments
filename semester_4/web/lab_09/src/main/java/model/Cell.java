package model;

import java.util.HashMap;
import java.util.Map;

public enum Cell {
    Empty(-10),
    O(0),
    X(1);

    private int value;
    private static Map<Integer, Cell> map = new HashMap<>();

    Cell(int value) {
        this.value = value;
    }

    static {
        for (Cell value : Cell.values()) {
            map.put(value.value, value);
        }
    }

    public int getValue() {
        return this.value;
    }

    public static Cell valueOf(int pageType) {
        return map.get(pageType);
    }
}
