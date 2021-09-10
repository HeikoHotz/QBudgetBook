#ifndef QBUDGETBOOKMAINWINDOW_H
#define QBUDGETBOOKMAINWINDOW_H

#include <QMainWindow>
#include <QUrl>
#include <QTimer>
#include <QFileDialog>
#include "BookingModel.h"

#define STD_HEADER "//id;booking_name;category;incoming/outgoing;amount"

namespace Ui {
	class QBudgetBookMainWindow;
}

/*
 * main window contains all instances of apps, controllers, widgets and management classes.
 */
class QBudgetBookMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	enum budgetBookMask
	{
		MASK_NONE = -1,
		MASK_BOOKING,
		MASK_CONFIG
	};

	/** constructor */
	QBudgetBookMainWindow();
	/** destructor */
	virtual ~QBudgetBookMainWindow();

	/* get main user interface instance */
	Ui::QBudgetBookMainWindow* getUi() const { return m_ui; }

	/** show or hide applications */
	void initScreen();

public slots:
	/** this slot is responsible to show the page booking in our state-machine */
	void btBooking();
	/** this slot is responsible to show the page config in our state-machine */
	void btConfig();
	/** this slot is responsible to create a new csv file */
	void btNewFile();
	/** this slot is responsible to open an existing csv file */
	void btOpenFile();

	/** this method controls the button behaviour */
	void guiControl();

private slots:
	/** this slot is called when new booking button was released */
	void btNewBooking();
	/** this slot is called when edit booking button was released */
	void btEditBooking();
	/** this slot is called when delete booking button was released */
	void btDeleteBooking();
	/** this slot is called when save booking button was released */
	void btSaveBooking();
	/** user has selected measurement in table */
	void selectedBookingEntry(const QItemSelection& select, const QItemSelection& deselect);

	/** */
	void parseCSVFile();

private:
	/** this method is a helper to detect the current booking number */
	int getCurrentBookingNumber() const;

	/** pointer to the gui */
	Ui::QBudgetBookMainWindow* m_ui;
	/** member represents the model */
	BookingModel m_model;

	/** this member represents the current selected id of the table view */
	int m_modelIdx;
	/** file member */
	QFile m_csvFile;

	/** member is responsible to */
	QString m_header = "";

signals:
	/** will be emitted when a csv file was opened */
	void budgetFileOpened();
};

#endif // QBUDGETBOOKMAINWINDOW_H
