#include "QBudgetBookMainWindow.h"
#include "ui_QBudgetBookMainWindow.h"
#include "BookingDialog.h"
#include <QDebug>
#include <QCloseEvent>
#include <QDesktopWidget>
#include <QDataStream>

QBudgetBookMainWindow::QBudgetBookMainWindow() : QMainWindow(nullptr), m_ui(new Ui::QBudgetBookMainWindow)
{
    m_ui->setupUi(this);

    connect(m_ui->b_booking, SIGNAL(clicked()), this, SLOT(btBooking()));
    connect(m_ui->b_config, SIGNAL(clicked()), this, SLOT(btConfig()));
    connect(m_ui->b_quit, SIGNAL(clicked()), this, SLOT(close()));
    connect(m_ui->b_open, SIGNAL(clicked()), this, SLOT(btOpenFile()));
    connect(m_ui->b_new, SIGNAL(clicked()), this, SLOT(btNewFile()));
    connect(this, SIGNAL(budgetFileOpened()), this, SLOT(guiControl()));
    //
    connect(m_ui->b_newBooking, SIGNAL(clicked()), this, SLOT(btNewBooking()));
    connect(m_ui->b_editBooking, SIGNAL(clicked()), this, SLOT(btEditBooking()));
    connect(m_ui->b_deleteBooking, SIGNAL(clicked()), this, SLOT(btDeleteBooking()));
    connect(m_ui->b_saveBooking, SIGNAL(clicked()), this, SLOT(btSaveBooking()));
}

QBudgetBookMainWindow::~QBudgetBookMainWindow()
{
	m_csvFile.close();
	delete m_ui;
}

void QBudgetBookMainWindow::initScreen()
{
	m_ui->tv_booking->viewport()->installEventFilter(this);
	m_ui->tv_booking->setModel(&m_model);
	m_ui->tv_booking->setEditTriggers( QAbstractItemView::DoubleClicked );

	// resize table
	m_ui->tv_booking->horizontalHeader()->resizeSection(BOOKING_ID, 80);
	m_ui->tv_booking->horizontalHeader()->resizeSection(BOOKING_NAME, 255);
	m_ui->tv_booking->horizontalHeader()->resizeSection(BOOKING_CATEGORY, 100);
	m_ui->tv_booking->horizontalHeader()->setSectionResizeMode(BOOKING_FLAG, QHeaderView::Stretch);
	m_ui->tv_booking->horizontalHeader()->setSectionResizeMode(BOOKING_AMOUNT, QHeaderView::Stretch);
	//
    connect(m_ui->tv_booking->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)), this, SLOT(selectedBookingEntry(const QItemSelection&, const QItemSelection&)));

    //init all booking buttons
	m_ui->b_newBooking->setEnabled(false);
	m_ui->b_editBooking->setEnabled(false);
	m_ui->b_deleteBooking->setEnabled(false);
	m_ui->b_saveBooking->setEnabled(false);

	//startup mask
	btBooking();
}

void QBudgetBookMainWindow::btBooking()
{
	m_ui->b_booking->setChecked(true);
	m_ui->b_config->setChecked(false);
	m_ui->stackScreen->setCurrentIndex(MASK_BOOKING);
}

void QBudgetBookMainWindow::btConfig()
{
	m_ui->b_booking->setChecked(false);
	m_ui->b_config->setChecked(true);

	m_ui->stackScreen->setCurrentIndex(MASK_CONFIG);
}

void QBudgetBookMainWindow::btNewFile()
{
	m_ui->b_new->setChecked(false);
	//to be done..
}

void QBudgetBookMainWindow::btOpenFile()
{
	m_ui->b_open->setChecked(false);
	QString path = "";
	QString filename = QFileDialog::getOpenFileName(this, tr("Select csv booking file."), path, " (*.csv)");
	if (filename.isEmpty() == true)
		return;

	m_csvFile.setFileName(filename);
	if (m_csvFile.open(QIODevice::ReadOnly | QIODevice::Text) == false)
		return;

	parseCSVFile();

	emit budgetFileOpened();
}

void QBudgetBookMainWindow::btNewBooking()
{
	BookingDialog dialog(this);
	if (dialog.exec() != QDialog::Accepted)
		return;

	QStringList list;
	int bookNum = getCurrentBookingNumber() +1;
	list.append(QString::number(bookNum));
	list.append(dialog.getParameter());
	m_model.insertDataEntry(list);
	m_ui->b_saveBooking->setEnabled(true);
}

void QBudgetBookMainWindow::btEditBooking()
{
	QStringList entry = m_model.getEntryRef(m_modelIdx);
	//to be done...
}

void QBudgetBookMainWindow::btDeleteBooking()
{
	m_model.removeDataEntry(m_modelIdx);
	m_ui->b_deleteBooking->setChecked(false);
	m_ui->b_saveBooking->setEnabled(true);
}

void QBudgetBookMainWindow::btSaveBooking()
{
	if (m_csvFile.open(QIODevice::ReadWrite |QIODevice::Truncate | QIODevice::Text) == false)
		return;

	QTextStream out(&m_csvFile);
	QList<QStringList> list = m_model.getBookingList();

	out << (m_header.isEmpty() ? STD_HEADER : m_header) << "\n";

	for (auto entry : list)
	{
		QString line;
		for (auto str : entry)
		{
			line += str;
			line += ";";
		}
		line.chop(1);
		out << line << "\n";
	}

	m_csvFile.close();
}

void QBudgetBookMainWindow::guiControl()
{
	//this is called only when a csv file was opened
	m_ui->b_newBooking->setEnabled(true);
	m_ui->b_editBooking->setEnabled(false);
	m_ui->b_deleteBooking->setEnabled(false);
}

void QBudgetBookMainWindow::selectedBookingEntry(const QItemSelection& select, const QItemSelection& deselect)
{
	// check index is out of range
	if (select.indexes().size() == 0)
	{
		m_ui->b_editBooking->setEnabled(false);
		m_ui->b_deleteBooking->setEnabled(false);
		return;
	}

	// read streaming element and save it locally
	m_modelIdx = m_ui->tv_booking->currentIndex().row();

	m_ui->b_editBooking->setEnabled(true);
	m_ui->b_deleteBooking->setEnabled(true);
}

void QBudgetBookMainWindow::parseCSVFile()
{
	m_model.clearAll();

	QTextStream in(&m_csvFile);
	m_header = in.readLine();
	while (!in.atEnd())
	{
		QString line = in.readLine();
		if (line.isEmpty())
			continue;

		QStringList booking;
		booking.append(line.split(';'));
		m_model.insertDataEntry(booking);
	}

	m_csvFile.close();
}

int QBudgetBookMainWindow::getCurrentBookingNumber() const
{
	int listSize = m_model.getSize();
	if (listSize == 0)
		return 0;

	QStringList tempList = m_model.getEntry(listSize-1);
	return tempList.at(0).toInt();
}
