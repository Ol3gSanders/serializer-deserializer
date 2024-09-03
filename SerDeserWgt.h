#ifndef SERDESERWGT_H
#define SERDESERWGT_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QGroupBox>

typedef struct {
	int x = 0;
	double y = 0;
	std::string text = "default";
} data_t;

class SerDeserWgt : public QGroupBox
{
	Q_OBJECT
public:
	SerDeserWgt();

	std::string toStr();

	std::string serialize();
	void deserialize( const std::string &str );

private:
	void init();
	void createWidgets();
	void placeWidgets();
	void connectSignals();

	data_t widgetsToData();
	void dataToWidgets( data_t data );

private slots:
	void onValueChanged();

private:
	QLabel *xLabel;
	QSpinBox *xSpinBox;

	QLabel *yLabel;
	QDoubleSpinBox *ySpinBox;

	QLabel *textLabel;
	QLineEdit *textLineEdit;

private:
	data_t data;

};

#endif // SERDESERWGT_H
