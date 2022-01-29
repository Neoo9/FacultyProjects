package Model.Exp;

import Exception.InvalidTypeExcep;
import Model.ADT.IDict;
import Model.ADT.IHeap;
import Model.Types.BoolType;
import Model.Types.IType;
import Model.Types.IntType;
import Model.Values.BoolValue;
import Model.Values.IValue;

public class LogicExp implements Exp {
    private final Exp ex1;
    private final Exp ex2;
    private final String op;

    public LogicExp(Exp ex1, Exp ex2, String op) {
        this.ex1 = ex1;
        this.ex2 = ex2;
        this.op = op;
    }


    @Override
    public IValue eval(IDict<String, IValue> symTable, IHeap<Integer, IValue> heap) throws Exception {
        boolean i1 = ((BoolValue) ex1.eval(symTable, heap)).getValue();
        boolean i2 = ((BoolValue) ex2.eval(symTable, heap)).getValue();
        if ("&&".equals(op)) {
            return new BoolValue(i1 && i2);
        }
        return new BoolValue(i1 || i2);
    }

    @Override
    public IType typeCheck(IDict<String, IType> typeEnv) throws Exception {
        IType t1 = ex1.typeCheck(typeEnv);
        IType t2 = ex2.typeCheck(typeEnv);
        if (!t1.equals(new BoolType())) {
            throw new InvalidTypeExcep("LogicExp: TypeCheck - First operand is not a bool");
        }
        if (!t2.equals(new BoolType())) {
            throw new InvalidTypeExcep("LogicExp: TypeCheck - Second operand is not a bool");
        }
        return new BoolType();
    }

    @Override
    public String toString() {
        return this.ex1.toString() + " " + this.op + " " + this.ex2.toString() + "; ";
    }
}
