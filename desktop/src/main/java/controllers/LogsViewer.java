package controllers;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.TableView;
import models.LogsRequest;
import models.LogsResponse;
import services.RestService;

import java.util.TimerTask;
import java.util.Timer;

public class LogsViewer {
    private ObservableList<LogsResponse.Log> logsList;
    @FXML private TableView<LogsResponse.Log> logTableView;

    @FXML public void initialize() {
        logsList = FXCollections.observableArrayList();
        logTableView.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);
        logTableView.setItems(logsList);
        startTask();
    }

    private void startTask() {
        new Timer().scheduleAtFixedRate(new TimerTask() {
            public void run() {
                try {
                    LogsRequest request =  logsList.isEmpty() ? new LogsRequest(0) :
                            new LogsRequest(logsList.stream().mapToInt(LogsResponse.Log::getNumber).max().getAsInt());
                    LogsResponse logsResponse = RestService.postLogs("serveurweb", request);
                    logsList.addAll(logsResponse.logs);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }, 250, 10000);
    }
}
