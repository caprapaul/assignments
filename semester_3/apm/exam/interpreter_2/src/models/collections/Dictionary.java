package models.collections;

import utils.ICopy;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class Dictionary<K, V> implements IDictionary<K, V> {
    private final Map<K,V> elements;

    public Dictionary() {
        this.elements = new HashMap<>();
    }

    @Override
    public Set<Map.Entry<K, V>> getAll() {
        return this.elements.entrySet();
    }

    @Override
    public Set<K> getKeys() {
        return this.elements.keySet();
    }

    @Override
    public Collection<V> getValues() {
        return this.elements.values();
    }

    @Override
    public V get(K key) {
        return this.elements.get(key);
    }

    @Override
    public void put(K key, V value) {
        this.elements.put(key, value);
    }

    @Override
    public V remove(K key) {
        V value = this.elements.get(key);

        this.elements.remove(key);

        return value;
    }

    @Override
    public String toString() {
        return this.elements.entrySet()
                            .stream()
                            .map(e -> e.getKey().toString() + " -> " + e.getValue().toString())
                            .reduce("", (s1, s2) -> s1 + s2 + "\n");
    }
}
