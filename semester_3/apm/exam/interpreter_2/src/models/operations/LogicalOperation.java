package models.operations;

public enum LogicalOperation {
    AND,
    OR,
    LESS,
    LESS_EQUAL,
    GREATER,
    GREATER_EQUAL,
    EQUAL,
    NOT_EQUAL;

    @Override
    public String toString() {
        String string = "";

        switch (this) {
            case AND -> {
                string = "&&";
            }
            case OR -> {
                string = "||";
            }
            case LESS -> {
                string = "<";
            }
            case LESS_EQUAL -> {
                string = "<=";
            }
            case GREATER -> {
                string = ">";
            }
            case GREATER_EQUAL -> {
                string = ">=";
            }
            case EQUAL -> {
                string = "==";
            }
            case NOT_EQUAL -> {
                string = "!=";
            }
        }

        return string;
    }
}
