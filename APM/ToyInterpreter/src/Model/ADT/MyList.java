package Model.ADT;

import Exception.EmptyADTEXcep;

import java.util.ArrayList;
import java.util.List;
import java.util.ListIterator;

public class MyList<T> implements IList<T> {
    private final List<T> list;

    public MyList() {
        list = new ArrayList<>();
    }

    public MyList(List<T> li){
        list = new ArrayList<>(li);
    }

    @Override
    public List<T> getList(){
        return this.list;
    }

    @Override
    public Integer size() {
        return list.size();
    }

    @Override
    public void add(T v) {
        list.add(v);
    }

    @Override
    public T pop() throws Exception {
        if (empty()) {
            throw new EmptyADTEXcep("MyList: Nothing to remove");
        }
        return list.remove(list.size() - 1);
    }

    @Override
    public boolean empty() {
        return this.list.isEmpty();
    }

    @Override
    public void clear() {
        this.list.clear();
    }

    @Override
    public ListIterator<T> getIterator() {
        return list.listIterator();
    }

    @Override
    public String toString() {
        StringBuilder str = new StringBuilder();
        for (T t : list) {
            str.append(t.toString()).append("\n");
        }
        return str.toString();
    }

    @Override
    public T get() throws Exception {
        if (empty()) {
            throw new EmptyADTEXcep("MyList: Nothing to get");
        }
        return list.get(list.size() - 1);
    }

    @Override
    public T get(int i){
        return list.get(i);
    }
}
