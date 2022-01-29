package Model.Stmt;

import Model.ADT.IDict;
import Model.ADT.IHeap;
import Model.ADT.IList;
import Model.Exp.Exp;
import Model.PrgState;
import Model.Types.IType;
import Model.Values.IValue;

public class PrintStmt implements IStmt {
    private final Exp expression;

    public PrintStmt(Exp exp) {
        this.expression = exp;
    }

    @Override
    public PrgState execute(PrgState state) throws Exception {
        IList<IValue> output = state.getOut();
        IDict<String, IValue> symT = state.getSymTable();
        IHeap<Integer, IValue> heap = state.getHeap();
        output.add(expression.eval(symT, heap));
        return null;
    }

    @Override
    public IDict<String, IType> typeCheck(IDict<String, IType> typeEnv) throws Exception {
        expression.typeCheck(typeEnv);
        return typeEnv;
    }

    @Override
    public String toString() {
        return "print(" + expression.toString() + ");";
    }
}
