package models.collections;

import exceptions.CollectionException;

import java.util.Map;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicInteger;

public class Heap<V> implements IHeap<V> {
    private final Map<Integer, V> elements;
    private final IStack<Integer> freeAddresses;
    private final AtomicInteger freeAddress;

    public Heap() {
        this.elements = new ConcurrentHashMap<>();
        this.freeAddresses = new ConcurrentStack<>();
        this.freeAddress = new AtomicInteger(1);
    }

    @Override
    public Set<Map.Entry<Integer, V>> getAll() {
        return this.elements.entrySet();
    }

    @Override
    public V get(int address) {
        return this.elements.get(address);
    }

    @Override
    public int allocate(V value) {
        int newAddress = 0;

        try {
            newAddress = this.freeAddresses.pop();
        }
        catch (CollectionException exception) {
            newAddress = this.freeAddress.getAndIncrement();
        }

        this.elements.put(newAddress, value);

        return newAddress;
    }

    @Override
    public void update(int address, V value) {
        this.elements.put(address, value);
    }

    @Override
    public V free(int address) {
        V value = this.elements.get(address);
        this.elements.remove(address);
        this.freeAddresses.push(address);

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
