#ifndef BOOKINGDIALOG_H
#define BOOKINGDIALOG_H

#include <QDialog>
#include "ui_BookingDialog.h"

// forward decl to the gui pointer
namespace Ui {
  class BookingDialog;
}

class BookingDialog : public QDialog
{
	/** gui elements (view) */
    Q_OBJECT
public:
    /** standard constructor */
    explicit BookingDialog(QWidget* parent = nullptr);
    /** deconstructor */
    virtual ~BookingDialog();

    /** returns the params which were inserted */
    QStringList getParameter();

private:
	/** pointer to itself */
    Ui::BookingDialog* m_ui;

private slots:
	/** triggered by clicking OK button */
	void btOK();
	/** triggered by clicking Cancel button */
	void btCancel();
};

#endif // BOOKINGDIALOG_H
