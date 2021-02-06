package models.collections;

import exceptions.CollectionException;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;

public class Stack<T> implements IStack<T> {
    private final Deque<T> elements;

    public Stack() {
        this.elements = new ArrayDeque<>();
    }

    @Override
    public T pop() throws CollectionException {
        if (this.elements.isEmpty()) {
            throw new CollectionException("Stack is empty.");
        }

        return this.elements.pop();
    }

    @Override
    public void push(T element) {
        this.elements.push(element);
    }

    @Override
    public boolean isEmpty() {
        return this.elements.isEmpty();
    }

    @Override
    public java.util.List<T> toList() {
        return new ArrayList<>(this.elements);
    }

    @Override
    public String toString() {
        return this.elements.stream()
                            .map(Object::toString)
                            .reduce("", (s1, s2) -> s1 + s2 + "\n");
    }
}
