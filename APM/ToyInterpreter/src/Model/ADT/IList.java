package Model.ADT;

import java.util.List;
import java.util.ListIterator;

public interface IList<T> {
    void add(T v);

    T pop() throws Exception;

    String toString();

    boolean empty();

    void clear();

    ListIterator<T> getIterator();

    T get() throws Exception;

    T get(int i);

    List<T> getList();

    Integer size();
}
