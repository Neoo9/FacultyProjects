package Model.Stmt;

import Exception.AlreadyDefVarExcep;
import Model.ADT.IDict;
import Model.PrgState;
import Model.Types.IType;
import Model.Values.IValue;

public class VarDeclStmt implements IStmt {
    private final String name;
    private final IType type;

    public VarDeclStmt(String name, IType type) {
        this.name = name;
        this.type = type;
    }


    @Override
    public PrgState execute(PrgState state) throws Exception {
        IDict<String, IValue> symTbl = state.getSymTable();
        if (symTbl.isDefined(name)) {
            throw new AlreadyDefVarExcep("VarDecl: Variable already defined");
        }
        symTbl.add(name, type.getDefaultValue());
        return null;
    }

    @Override
    public IDict<String, IType> typeCheck(IDict<String, IType> typeEnv) throws Exception {
        typeEnv.add(name, type);
        return typeEnv;
    }

    @Override
    public String toString() {
        return this.type.toString() + " " + this.name + ";";
    }
}
