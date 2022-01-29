package Model.Stmt;

import Exception.InvalidTypeExcep;
import Exception.UndefVarExcep;
import Model.ADT.IDict;
import Model.ADT.IHeap;
import Model.Exp.Exp;
import Model.PrgState;
import Model.Types.IType;
import Model.Types.IntType;
import Model.Types.RefType;
import Model.Types.StringType;
import Model.Values.IValue;
import Model.Values.IntValue;
import Model.Values.StringValue;

import java.io.BufferedReader;

public class ReadFileStmt implements IStmt {
    private final Exp path;
    private final String var_name;

    public ReadFileStmt(Exp fp, String name) {
        this.path = fp;
        this.var_name = name;
    }

    @Override
    public PrgState execute(PrgState state) throws Exception {
        IDict<String, IValue> symT = state.getSymTable();
        synchronized (state.getHeap()) {
            synchronized (state.getFileTable()) {
                IHeap<Integer, IValue> heap = state.getHeap();
                IDict<StringValue, BufferedReader> fileT = state.getFileTable();
                if (!symT.isDefined(this.var_name)) {
                    throw new UndefVarExcep("ReadFileStmt: Undefined variable");
                }
                IValue pathValue = path.eval(symT, heap);
                if (!fileT.isDefined((StringValue) pathValue)) {
                    throw new UndefVarExcep("ReadFileStmt: File path not defined");
                }
                BufferedReader buf = fileT.lookup((StringValue) pathValue);
                String line = buf.readLine();
                if (line == null) {
                    symT.update(this.var_name, new IntValue());
                } else {
                    symT.update(this.var_name, new IntValue(Integer.parseInt(line)));
                }
            }
        }
        return null;
    }

    @Override
    public IDict<String, IType> typeCheck(IDict<String, IType> typeEnv) throws Exception {
        IType t1 = typeEnv.lookup(var_name);
        IType t2 = path.typeCheck(typeEnv);
        if (!t1.equals(new IntType())) {
            throw new InvalidTypeExcep("ReadFileStmt: Invalid path type");
        }
        if (!t2.equals(new StringType())) {
            throw new InvalidTypeExcep("ReadFileStmt: Invalid var name type");
        }
        return typeEnv;

    }

    @Override
    public String toString() {
        return "readFile(" + this.path + ", " + this.var_name + ");";
    }
}
