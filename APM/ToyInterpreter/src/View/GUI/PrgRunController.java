package View.GUI;

import Controller.Controller;
import Model.PrgState;
import Model.Stmt.IStmt;
import Model.Values.IValue;
import Model.Values.StringValue;
import javafx.beans.property.ReadOnlyStringWrapper;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;
import javafx.stage.Stage;

import java.net.URL;
import java.util.*;
import java.util.concurrent.Executors;

public class PrgRunController implements Initializable {
    private final Controller myController;
    private List<PrgState> prgList;
    @FXML
    Label nrPrgStates;
    @FXML
    Button runButton;
    @FXML
    TableView<Map.Entry<Integer, IValue>> heapTable;
    @FXML
    TableColumn<HashMap.Entry<Integer, IValue>, String> heapTableAddress;
    @FXML
    TableColumn<HashMap.Entry<Integer, IValue>, String> heapTableValue;
    @FXML
    ListView<String> outList;
    @FXML
    ListView<String> fileTable;
    @FXML
    ListView<String> prgStateList;
    @FXML
    TableView<Map.Entry<String, IValue>> symTable;
    @FXML
    TableColumn<HashMap.Entry<String, IValue>, String> symTableVariable;
    @FXML
    TableColumn<HashMap.Entry<String, IValue>, String> symTableValue;
    @FXML
    ListView<String> exeStackList;

    public PrgRunController(Controller myController) {
        this.myController = myController;
    }

    public void oneStepGUI() throws Exception{
        prgList.get(0).getHeap().setContent(myController.safeGarbageCollector(prgList.get(0)));
        myController.oneStepForAllPrg(prgList);
        prgList = myController.removeCompletedPrg(myController.getRepository().getPrgList());
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        initialRun();
        prgStateList.setOnMouseClicked(event -> setSymTableAndExeStack());
        runButton.setOnAction(actionEvent -> {
            try {
                oneStepGUI();
            } catch (IndexOutOfBoundsException ie) {
                myController.shutDownExecutor();
                showInfo(new Alert(Alert.AlertType.INFORMATION), "Current program finished", "Program finished successfully");
                Stage stage = (Stage) heapTable.getScene().getWindow();
                stage.close();

            } catch(Exception e){
                myController.shutDownExecutor();
                showInfo(new Alert(Alert.AlertType.ERROR), "ERROR", e.getMessage());
                Stage stage = (Stage) heapTable.getScene().getWindow();
                stage.close();
            }
            updateUIComponents();
        });
    }

    public static void showInfo(Alert alert, String title, String contentText){
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(contentText);
        Button confirm = (Button) alert.getDialogPane().lookupButton(ButtonType.OK);
        confirm.setDefaultButton(false);
        confirm.setStyle("-fx-focus-color: transparent; -fx-faint-focus-color: transparent; -fx-font-family: 'Comic Sans MS'");
        alert.showAndWait();
    }

    private void initialRun() {
        try {
            myController.getRepository().clearFile();
            myController.setExecutor(Executors.newFixedThreadPool(2));
            prgList = myController.removeCompletedPrg(myController.getRepository().getPrgList());
        } catch (Exception e) {
            e.printStackTrace();
        }
        setNumberLabel();
        setHeapTable();
        setOutList();
        setFileTable();
        setPrgStateList();
        prgStateList.getSelectionModel().selectFirst();
        setSymTableAndExeStack();
    }

    public void updateUIComponents() {
        setNumberLabel();
        setHeapTable();
        setOutList();
        setFileTable();
        setPrgStateList();
        if (prgStateList.getSelectionModel().getSelectedItem() == null) {
            prgStateList.getSelectionModel().selectFirst();
        }
        setSymTableAndExeStack();
    }

    public void setNumberLabel() {
        nrPrgStates.setText("The number of PrgStates: " + myController.getRepository().getPrgList().size());
    }

    public void setHeapTable() {
        ObservableList<HashMap.Entry<Integer, IValue>> heapTableList = FXCollections.observableArrayList();
        heapTableAddress.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(Integer.toString(cellData.getValue().getKey())));
        heapTableValue.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(cellData.getValue().getValue().toString()));
        heapTableList.addAll(myController.getRepository().getPrgList().get(0).getHeap().getAllPairs().entrySet());
        heapTable.setItems(heapTableList);
    }

    public void setOutList() {
        ObservableList<String> outObservableList = FXCollections.observableArrayList();
        for (IValue e : myController.getRepository().getPrgList().get(0).getOut().getList()) {
            outObservableList.add(e.toString());
        }
        outList.setItems(outObservableList);
    }

    public void setFileTable() {
        ObservableList<String> fileTableList = FXCollections.observableArrayList();
        for (StringValue s : myController.getRepository().getPrgList().get(0).getFileTable().getAllPairs().keySet()) {
            fileTableList.add(s.toString());
        }
        fileTable.setItems(fileTableList);
    }

    public void setPrgStateList() {
        ObservableList<String> prgStateIdList = FXCollections.observableArrayList();
        for (PrgState e : myController.getRepository().getPrgList().getList()) {
            prgStateIdList.add(Integer.toString(e.getId()));
        }
        prgStateList.setItems(prgStateIdList);
    }

    public void setSymTableAndExeStack() {
        ObservableList<HashMap.Entry<String, IValue>> symTableList = FXCollections.observableArrayList();
        ObservableList<String> exeStackItemsList = FXCollections.observableArrayList();
        symTableVariable.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(cellData.getValue().getKey()));
        symTableValue.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(cellData.getValue().getValue().toString()));
        List<PrgState> allPrograms = myController.getRepository().getPrgList().getList();
        PrgState prgResult = null;
        for (PrgState e : allPrograms) {
            if (e.getId() == Integer.parseInt(prgStateList.getSelectionModel().getSelectedItem())) {
                prgResult = e;
                break;
            }
        }
        if (prgResult != null) {
            symTableList.addAll(prgResult.getSymTable().getAllPairs().entrySet());
            for (IStmt e : prgResult.getStack().getStack()) {
                exeStackItemsList.add(e.toString());
            }
            Collections.reverse(exeStackItemsList);
            symTable.setItems(symTableList);
            exeStackList.setItems(exeStackItemsList);
        }
    }

}
