package models.collections;

import exceptions.CollectionException;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.List;

public class ConcurrentStack<T> implements IStack<T> {
    private final Deque<T> elements;

    public ConcurrentStack() {
        this.elements = new ArrayDeque<>();
    }

    @Override
    public synchronized T pop() throws CollectionException {
        if (this.elements.isEmpty()) {
            throw new CollectionException("Stack is empty.");
        }

        return this.elements.pop();
    }

    @Override
    public synchronized void push(T element) {
        this.elements.push(element);
    }

    @Override
    public synchronized boolean isEmpty() {
        return this.elements.isEmpty();
    }

    @Override
    public List<T> toList() {
        return new ArrayList<>(this.elements);
    }

    @Override
    public synchronized String toString() {
        return this.elements.stream()
                            .map(Object::toString)
                            .reduce("", (s1, s2) -> s1 + s2 + "\n");
    }
}
