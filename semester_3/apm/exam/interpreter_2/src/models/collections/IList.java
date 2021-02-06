package models.collections;

public interface IList<T> {
    void setAll(java.util.List<T> elements);
    java.util.List<T> getAll();
    T get(int index);
    void add(T element);
    void add(int index, T element);
    int size();
}
