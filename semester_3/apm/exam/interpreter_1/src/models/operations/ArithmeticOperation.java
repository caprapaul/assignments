package models.operations;

public enum ArithmeticOperation {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE;

    @Override
    public String toString() {
        String string = "";

        switch (this) {
            case ADD -> {
                string = "+";
            }
            case SUBTRACT -> {
                string = "-";
            }
            case MULTIPLY -> {
                string = "*";
            }
            case DIVIDE -> {
                string = "/";
            }
        }

        return string;
    }
}
