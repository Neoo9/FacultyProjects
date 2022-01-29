package Model.Stmt;

import Exception.InvalidTypeExcep;
import Exception.UndefVarExcep;
import Model.ADT.IDict;
import Model.ADT.IHeap;
import Model.Exp.Exp;
import Model.PrgState;
import Model.Types.IType;
import Model.Values.IValue;

public class AssignStmt implements IStmt {

    private final String id;
    private final Exp expression;

    public AssignStmt(String id, Exp exp) {
        this.id = id;
        expression = exp;
    }

    @Override
    public String toString() {
        return this.id + " = " + this.expression.toString() + ";";
    }

    @Override
    public PrgState execute(PrgState state) throws Exception {
        IDict<String, IValue> symTbl = state.getSymTable();
        IHeap<Integer, IValue> heap = state.getHeap();
        if (!symTbl.isDefined(id)) {
            throw new UndefVarExcep("AssignStmt: Variable not defined");
        }
        IValue val = expression.eval(symTbl, heap);
        symTbl.update(id, val);
        return null;
    }

    @Override
    public IDict<String, IType> typeCheck(IDict<String, IType> typeEnv) throws Exception {
        IType t1 = typeEnv.lookup(id);
        IType t2 = expression.typeCheck(typeEnv);
        if (!t1.equals(t2)) {
            throw new InvalidTypeExcep("AssignStmt: RHS and LHS have different types");
        }
        return typeEnv;
    }
}
