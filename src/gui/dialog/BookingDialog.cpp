#include "BookingDialog.h"
#include <QDebug>

BookingDialog::BookingDialog(QWidget* parent) : QDialog(parent), m_ui(new Ui::BookingDialog)
{
	// setup GUI
	m_ui->setupUi(this);
	setWindowModality(Qt::WindowModal);

	// SIGNAL-SLOT connection
	connect(m_ui->b_ok, SIGNAL(clicked()), this, SLOT(btOK()));
	connect(m_ui->b_cancel, SIGNAL(clicked()), this, SLOT(btCancel()));
}

BookingDialog::~BookingDialog()
{
	delete m_ui;
	m_ui = nullptr;
}

void BookingDialog::btOK()
{
	done(QDialog::Accepted);
}

void BookingDialog::btCancel()
{
	done(QDialog::Rejected);
}

QStringList BookingDialog::getParameter()
{
	QStringList list;
	list.append(m_ui->e_name->text());
	list.append(m_ui->cb_category->currentText());
	list.append(QString::number(m_ui->cb_type->currentIndex()));
	list.append(m_ui->le_amount->text());

	return list;
}
