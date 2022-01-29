package Model.ADT;

import Exception.UndefVarExcep;

import java.util.Collection;
import java.util.concurrent.ConcurrentHashMap;

public class Dict<T1, T2> implements IDict<T1, T2> {
    protected ConcurrentHashMap<T1, T2> dictionary;

    public Dict() {
        dictionary = new ConcurrentHashMap<>();
    }

    @Override
    public void add(T1 v1, T2 v2) {
        dictionary.put(v1, v2);
    }

    @Override
    public void update(T1 v1, T2 v2) throws UndefVarExcep {
        try {
            lookup(v1);
        } catch (Exception e) {
            throw new UndefVarExcep("Dict: Variable not defined");
        } finally {
            dictionary.replace(v1, v2);
        }
    }

    @Override
    public T2 lookup(T1 id) throws UndefVarExcep {
        try {
            return dictionary.get(id);
        } catch (Exception e) {
            throw new UndefVarExcep("Dict: Variable not defined");
        }
    }

    @Override
    public boolean isDefined(T1 id) {
        return dictionary.containsKey(id);
    }

    @Override
    public String toString() {
        StringBuilder str = new StringBuilder();
        for (T1 key : dictionary.keySet()) {
            str.append(key.toString()).append(" -> ").append(dictionary.get(key).toString()).append("\n");
        }
        return str.toString();
    }

    @Override
    public T2 remove(T1 id) throws Exception {
        try {
            return dictionary.remove(id);
        } catch (Exception e) {
            throw new UndefVarExcep("Dict: Variable not defined");
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
    public IDict<T1, T2> clone() {
        IDict<T1, T2> cpy = new Dict<>();
        this.dictionary.forEach(cpy::add);
        return cpy;
    }
}
