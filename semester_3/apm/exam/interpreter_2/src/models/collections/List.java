package models.collections;

import java.util.ArrayList;

public class List<T> implements IList<T> {
    private java.util.List<T> elements;

    public List() {
        this.elements = new ArrayList<>();
    }

    @Override
    public void setAll(java.util.List<T> elements) {
        this.elements = elements;
    }

    @Override
    public java.util.List<T> getAll() {
        return this.elements;
    }

    @Override
    public T get(int index) {
        return this.elements.get(index);
    }

    @Override
    public void add(T element) {
        this.elements.add(element);
    }

    @Override
    public void add(int index, T element) {
        this.elements.add(index, element);
    }

    @Override
    public int size() {
        return this.elements.size();
    }

    @Override
    public String toString() {
        return this.elements.stream()
                            .map(Object::toString)
                            .reduce("", (s1, s2) -> s1 + s2 + "\n");
    }
}
