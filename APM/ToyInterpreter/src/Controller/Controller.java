package Controller;

import Model.ADT.IDict;
import Model.ADT.IHeap;
import Model.ADT.IList;
import Model.ADT.MyList;
import Model.PrgState;
import Model.Values.IValue;
import Model.Values.RefValue;
import Repository.IRepo;

import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.concurrent.*;
import java.util.stream.Collectors;

public class Controller {
    private final IRepo rep;
    private ExecutorService executor;

    public Controller(IRepo repo) {
        this.rep = repo;
    }

    public void addProgram(PrgState newPrg) {
        this.rep.addPrg(newPrg);
    }

    public IRepo getRepository(){return this.rep;}

    public void setExecutor(ExecutorService es){
        this.executor = es;
    }

    public void shutDownExecutor(){
        this.executor.shutdownNow();
    }

    public void allStep() throws Exception{
        rep.clearFile();
        executor = Executors.newFixedThreadPool(2);
        List<PrgState> prgList = removeCompletedPrg(rep.getPrgList());
        while(prgList.size() > 0){
            prgList.get(0).getHeap().setContent(safeGarbageCollector(prgList.get(0)));
            oneStepForAllPrg(prgList);
            prgList = removeCompletedPrg(rep.getPrgList());
        }
        executor.shutdownNow();
        rep.setPrgList(new MyList<>(prgList));
    }

    public void oneStepForAllPrg(List<PrgState> li) throws Exception{
        List<Callable<PrgState>> callList = li.stream()
                .map((PrgState p)->(Callable<PrgState>) p::oneStep)
                .collect(Collectors.toList());
        List<PrgState> newPrgList = executor.invokeAll(callList).stream()
                .map(future -> {
                    try {
                        return future.get();
                    } catch (InterruptedException | ExecutionException e) {
                        throw new RuntimeException("Controller: future.get() error");
                    }
                })
                .filter(Objects::nonNull)
                .collect(Collectors.toList());
        li.addAll(newPrgList);
        for (PrgState prg : li) {
            rep.logPrgStateExec(prg);
        }
        rep.setPrgList(new MyList<>(li));
    }

    public List<PrgState> removeCompletedPrg(IList<PrgState> inPrgList){
        return inPrgList.getList().stream()
                .filter(PrgState::isNotCompleted)
                .collect(Collectors.toList());
    }

    public ConcurrentHashMap<Integer, IValue> safeGarbageCollector(PrgState state) {
        IDict<String, IValue> symT = state.getSymTable();
        IHeap<Integer, IValue> heap = state.getHeap();
        List<Integer> symTAddr = getAddrFromSymTable(symT);
        List<Integer> heapAddr = getAddrFromHeap(heap);
        return (ConcurrentHashMap<Integer, IValue>) heap.getAllPairs().entrySet().stream()
                .filter(e -> symTAddr.contains(e.getKey()) || heapAddr.contains(e.getKey()))
                .collect(Collectors.toConcurrentMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    public List<Integer> getAddrFromSymTable(IDict<String, IValue> symTable) {
        return symTable.getAllValues().stream()
                .filter(v -> v instanceof RefValue)
                .map(v -> {
                    RefValue v1 = (RefValue) v;
                    return v1.getAddress();
                })
                .collect(Collectors.toList());
    }

    public List<Integer> getAddrFromHeap(IHeap<Integer, IValue> heap) {
        return heap.getAllValues().stream()
                .filter(v -> v instanceof RefValue)
                .map(v -> {
                    RefValue v1 = (RefValue) v;
                    return v1.getAddress();
                })
                .collect(Collectors.toList());
    }
    @Override
    public String toString(){
        try{
            return this.getRepository().getPrgList().getList().get(0).getOriginalProgramString();
        }catch(Exception e){
            return "";
        }
    }
}
