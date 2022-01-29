package Model.Exp;

import Exception.DivByZero;
import Exception.InvalidTypeExcep;
import Model.ADT.IDict;
import Model.ADT.IHeap;
import Model.Types.IType;
import Model.Types.IntType;
import Model.Values.IValue;
import Model.Values.IntValue;

public class ArithExp implements Exp {
    private final char op;
    private final Exp e1;
    private final Exp e2;

    public ArithExp(char o, Exp e1, Exp e2) {
        this.op = o;
        this.e1 = e1;
        this.e2 = e2;
    }

    @Override
    public IValue eval(IDict<String, IValue> symTable, IHeap<Integer, IValue> heap) throws Exception {
        int n1 = ((IntValue) e1.eval(symTable, heap)).getValue();
        int n2 = ((IntValue) e2.eval(symTable, heap)).getValue();
        switch (op) {
            case '+':
                return new IntValue(n1 + n2);
            case '-':
                return new IntValue(n1 - n2);
            case '*':
                return new IntValue(n1 * n2);
            default:
                if (n2 == 0) {
                    throw new DivByZero("ArithExp: Division by zero");
                }
                return new IntValue(n1 / n2);
        }
    }


    @Override
    public IType typeCheck(IDict<String, IType> typeEnv) throws Exception {
        IType t1 = e1.typeCheck(typeEnv);
        IType t2 = e2.typeCheck(typeEnv);
        if (!t1.equals(new IntType())) {
            throw new InvalidTypeExcep("ArithExp: TypeCheck - First operand is not an int");
        }
        if (!t2.equals(new IntType())) {
            throw new InvalidTypeExcep("ArithExp: TypeCheck - Second operand is not an int");
        }
        return new IntType();
    }

    @Override
    public String toString() {
        return e1.toString() + " " + op + " " + e2.toString();
    }
}
