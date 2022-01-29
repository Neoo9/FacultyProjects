package Model.Exp;

import Exception.InvalidTypeExcep;
import Model.ADT.IDict;
import Model.ADT.IHeap;
import Model.Types.BoolType;
import Model.Types.IType;
import Model.Types.IntType;
import Model.Values.BoolValue;
import Model.Values.IValue;
import Model.Values.IntValue;

public class RelExp implements Exp {
    private final String op;
    private final Exp e1;
    private final Exp e2;

    public RelExp(String o, Exp e1, Exp e2) {
        this.op = o;
        this.e1 = e1;
        this.e2 = e2;
    }

    @Override
    public IValue eval(IDict<String, IValue> symTable, IHeap<Integer, IValue> heap) throws Exception {
        int n1 = ((IntValue) e1.eval(symTable, heap)).getValue();
        int n2 = ((IntValue) e2.eval(symTable, heap)).getValue();
        return switch (op) {
            case "<" -> new BoolValue(n1 < n2);
            case "<=" -> new BoolValue(n1 <= n2);
            case "==" -> new BoolValue(n1 == n2);
            case "!=" -> new BoolValue(n1 != n2);
            case ">" -> new BoolValue(n1 > n2);
            default -> new BoolValue(n1 >= n2);
        };
    }

    @Override
    public IType typeCheck(IDict<String, IType> typeEnv) throws Exception {
        IType t1 = e1.typeCheck(typeEnv);
        IType t2 = e2.typeCheck(typeEnv);
        if (!t1.equals(new IntType())) {
            throw new InvalidTypeExcep("RelExp: TypeCheck - First operand is not a bool");
        }
        if (!t2.equals(new IntType())) {
            throw new InvalidTypeExcep("RelExp: TypeCheck - Second operand is not a bool");
        }
        return new BoolType();
    }

    @Override
    public String toString() {
        return e1.toString() + " " + op + " " + e2.toString();
    }
}
