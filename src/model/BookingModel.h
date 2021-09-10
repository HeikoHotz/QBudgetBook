#ifndef BOOKINGMODEL_H
#define BOOKINGMODEL_H

#include <QAbstractTableModel>
#include <QItemSelection>
#include <QVariant>
#include <QDateTime>

#include <QDebug>

#include <cmath>
#include <cstdlib>

#define BOOKING_ID				0
#define BOOKING_NAME			1
#define BOOKING_CATEGORY		2
#define BOOKING_FLAG			3
#define BOOKING_AMOUNT			4

#define BOOKING_COLUMNS			5

/**
 * Model keeps all data.
 */
class BookingModel : public QAbstractTableModel
{
    /** Qt stuff */
    Q_OBJECT

public:
    /** standard constructor */
    explicit BookingModel(QObject* parent = nullptr);
    /** standard deconstructor */
    virtual ~BookingModel();

    /** returns the current booking list*/
    QList<QStringList> getBookingList() const { return m_bookingList;}

    /** number of elements in model */
    int getSize() const	{ return m_bookingList.size(); }

    /** get an refence to the element at given index idx */
    QStringList& getEntryRef(unsigned int idx)	{ return m_bookingList[idx]; }
    /** get a const element at given index idx */
    QStringList getEntry(unsigned int idx) const { return m_bookingList.at(idx); }

    /** view interface method, number of rows */
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    /** view interface method, number of columns */
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    /** view interface method, data element */
    QVariant data(const QModelIndex &index, int role) const;

    /** view interface method, header names */
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    /** insert a data entry to model; it cares that only  */
    void insertDataEntry(QStringList booking);
    /** delete a data entry in model */
    void removeDataEntry(const unsigned int index);

    /** delete all entries in model */
    void clearAll();

private:
	/** member represents the current bookings in a list of stringlists */
	QList<QStringList> m_bookingList;

signals:
	/* none */
};

#endif //BOOKINGMODEL_H
