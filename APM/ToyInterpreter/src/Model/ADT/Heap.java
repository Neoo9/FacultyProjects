package Model.ADT;

import java.util.Collection;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicInteger;
import Exception.*;

public class Heap<T1, T2> implements IHeap<T1, T2> {
    private ConcurrentHashMap<T1, T2> dictionary;
    private final AtomicInteger available;

    public Heap() {
        this.dictionary = new ConcurrentHashMap<>();
        this.available = new AtomicInteger(1);
    }

    public int getAvailable() {
        return this.available.getAndAdd(1);
    }

    @Override
    public void add(T1 v1, T2 v2) {
        dictionary.put(v1, v2);
    }

    @Override
    public void update(T1 v1, T2 v2) throws Exception {
        try {
            lookup(v1);
        } catch (Exception e) {
            throw new UndefVarExcep("Heap: Variable not defined");
        } finally {
            dictionary.replace(v1, v2);
        }
    }

    @Override
    public T2 lookup(T1 id) throws Exception {
        try {
            return dictionary.get(id);
        } catch (Exception e) {
            throw new UndefVarExcep("Heap: Variable not defined");
        }
    }

    @Override
    public boolean isDefined(T1 id) {
        return dictionary.containsKey(id);
    }

    @Override
    public T2 remove(T1 id) throws Exception {
        try {
            return dictionary.remove(id);
        } catch (Exception e) {
            throw new UndefVarExcep("Heap: Variable not defined");
        }
    }

    @Override
    public Collection<T2> getAllValues() {
        return this.dictionary.values();
    }

    @Override
    public ConcurrentHashMap<T1, T2> getAllPairs() {
        return this.dictionary;
    }

    @Override
    public void setContent(ConcurrentHashMap<T1, T2> newDict) {
        this.dictionary = newDict;
    }

    @Override
    public IHeap<T1, T2> clone() {
        IHeap<T1, T2> cpy = new Heap<>();
        this.dictionary.forEach(cpy::add);
        return cpy;
    }

    @Override
    public String toString() {
        StringBuilder str = new StringBuilder();
        for (T1 key : dictionary.keySet()) {
            str.append(key.toString()).append(" -> ").append(dictionary.get(key).toString()).append("\n");
        }
        return str.toString();
    }
}
