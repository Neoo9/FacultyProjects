package Model.ADT;

import Exception.EmptyADTEXcep;
import Model.Stmt.CompStmt;
import Model.Stmt.IStmt;

import java.util.ArrayList;
import java.util.ListIterator;
import java.util.Stack;

public class MyStack<T> implements IStack<T> {
    private final Stack<T> stack;

    public MyStack() {
        stack = new Stack<>();
    }

    @Override
    public T pop() throws Exception {
        if (isEmpty()) {
            throw new EmptyADTEXcep("MyStack: Nothing to remove");
        }
        return stack.pop();
    }


    @Override
    public void push(T v) {
        stack.push(v);
    }

    @Override
    public boolean isEmpty() {
        return stack.isEmpty();
    }

    public String toString() {
        StringBuilder str = new StringBuilder();
        ArrayList<T> elems = new ArrayList<>(this.stack);
        for (ListIterator<T> it = elems.listIterator(elems.size()); it.hasPrevious(); ) {
            Object elem = it.previous();
            if (elem instanceof IStmt) {
                str.append(inOrderTraversal((IStmt) elem));
            } else {
                str.append(elem.toString()).append('\n');
            }
        }
        return str.toString();
    }

    @Override
    public Stack<T> getStack() {
        return this.stack;
    }

    public String inOrderTraversal(IStmt stmt) {
        if (stmt instanceof CompStmt) {
            StringBuilder str = new StringBuilder();
            IStmt stmt1 = ((CompStmt) stmt).getFirst();
            IStmt stmt2 = ((CompStmt) stmt).getSecond();
            if (stmt1 instanceof CompStmt) {
                str.append(inOrderTraversal(stmt1));
            } else {
                str.append(stmt1.toString()).append('\n');
            }
            if (stmt2 instanceof CompStmt) {
                str.append(inOrderTraversal(stmt2));
            } else {
                str.append(stmt2.toString()).append('\n');
                ;
            }
            return str.toString();
        } else {
            return stmt.toString() + '\n';
        }
    }
}
