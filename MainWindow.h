#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>

#include "SerDeserWgt.h"
#include "FileDialogService.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	void createWidgets();
	void placeWidgets();
	void connectSignals();

	void saveFile();
	void loadFile();

	void closeEvent( QCloseEvent *event );

private slots:
	void onPrintButtonClicked();
	void onExitButtonClicked();
	void onSaveButtonClicked();
	void onLoadButtonClicked();

private:
	SerDeserWgt *serDeserWgt;

	QPlainTextEdit *textInfo;
	QPushButton * exitButton;
	QPushButton * printButton;
	QPushButton * saveButton;
	QPushButton * loadButton;

private:
	FileDialogService fileDialogService;
	std::string filePath = "main.userdata";

};
#endif // MAINWINDOW_H
