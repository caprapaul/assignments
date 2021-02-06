package models.collections;

import java.util.Collection;
import java.util.Map;
import java.util.Set;

public interface IDictionary<K, V> {
    Set<Map.Entry<K, V>> getAll();
    Set<K> getKeys();
    Collection<V> getValues();
    V get(K key);
    void put(K key, V value);
    V remove(K key);
}
