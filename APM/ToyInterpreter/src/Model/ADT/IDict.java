package Model.ADT;

import java.util.Collection;
import java.util.HashMap;
import java.util.concurrent.ConcurrentHashMap;

public interface IDict<T1, T2> {

    void add(T1 v1, T2 v2);

    void update(T1 v1, T2 v2) throws Exception;

    T2 lookup(T1 id) throws Exception;

    boolean isDefined(T1 id);

    String toString();

    T2 remove(T1 id) throws Exception;

    Collection<T2> getAllValues();

    ConcurrentHashMap<T1, T2> getAllPairs();

    void setContent(ConcurrentHashMap<T1, T2> newDict);

    IDict<T1, T2> clone();
}
