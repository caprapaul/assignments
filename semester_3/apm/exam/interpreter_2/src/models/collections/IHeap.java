package models.collections;

import java.util.Map;
import java.util.Set;

public interface IHeap<V> {
    Set<Map.Entry<Integer, V>> getAll();
    V get(int address);
    int allocate(V value);
    void update(int address, V value);
    V free(int address);
}
