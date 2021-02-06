package models.collections;

import java.util.Map;
import java.util.Set;

public interface ILatchTable  {
    Set<Map.Entry<Integer, Integer>> getAll();
    int get(int address);
    int add(int count);
    boolean decrement(int address);
}
