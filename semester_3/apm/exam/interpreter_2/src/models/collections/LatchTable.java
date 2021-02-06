package models.collections;

import exceptions.CollectionException;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class LatchTable implements ILatchTable {
    private final Map<Integer, Integer> elements;
    private final IStack<Integer> freeAddresses;
    private int freeAddress;

    public LatchTable() {
        this.elements = new HashMap<>();
        this.freeAddresses = new Stack<>();
        this.freeAddress = 1;
    }

    @Override
    public Set<Map.Entry<Integer, Integer>> getAll() {
        return null;
    }

    @Override
    public synchronized int get(int address) {
        if (!this.elements.containsKey(address)) {
            return -1;
        }

        return this.elements.get(address);
    }

    @Override
    public synchronized int add(int count) {
        int newAddress;

        try {
            newAddress = this.freeAddresses.pop();
        }
        catch (CollectionException exception) {
            newAddress = this.freeAddress;
            this.freeAddress += 1;
        }

        this.elements.put(newAddress, count);
        return newAddress;
    }

    @Override
    public synchronized boolean decrement(int address) {
        if (this.elements.get(address) <= 0) {
            return false;
        }

        int count = this.elements.get(address);
        this.elements.put(address, count - 1);

        return true;
    }

    @Override
    public String toString() {
        return this.elements.entrySet()
                            .stream()
                            .map(e -> e.getKey().toString() + " -> " + e.getValue().toString())
                            .reduce("", (s1, s2) -> s1 + s2 + "\n");
    }
}
