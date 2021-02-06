package models.collections;

import exceptions.CollectionException;

public interface IStack<T> {
    T pop() throws CollectionException;
    void push(T element);
    boolean isEmpty();
    java.util.List<T> toList();
}
