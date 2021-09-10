#include "BookingModel.h"
#include <QApplication>
#include <QPalette>
#include <QDebug>

BookingModel::BookingModel(QObject* parent)
{
}

BookingModel::~BookingModel()
{
}

int BookingModel::rowCount(const QModelIndex& parent) const
{
	return m_bookingList.size();
}

int BookingModel::columnCount(const QModelIndex &parent) const
{
	return BOOKING_COLUMNS;
}

QVariant BookingModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
        return QVariant();

    if (index.row() >= m_bookingList.size() ||index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole)
    {
    	switch (index.column())
    	{
			case BOOKING_ID: 			return m_bookingList.at(index.row()).at(0);
			case BOOKING_NAME:			return m_bookingList.at(index.row()).at(1);
			case BOOKING_CATEGORY:		return m_bookingList.at(index.row()).at(2);
			case BOOKING_FLAG:			return m_bookingList.at(index.row()).at(3) == 0 ? "Income" : "Outgoings";
			case BOOKING_AMOUNT:		return m_bookingList.at(index.row()).at(4);
			default: 					return QVariant();
    	}
    }
    else if (role == Qt::TextAlignmentRole)
    {
    	return Qt::AlignRight;
    }
    else if (role == Qt::BackgroundRole)
    {
    	if (index.row() % 2 == 0)
            return qApp->palette().base();
        else
            return qApp->palette().alternateBase();
    }
    return QVariant();
}

QVariant BookingModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Vertical)
		return QVariant();

	if (role == Qt::DisplayRole)
	{
		switch (section)
		{
			case BOOKING_ID: 			return tr("Number");
			case BOOKING_NAME:			return tr("Name");
			case BOOKING_FLAG:			return tr("Transfer");
			case BOOKING_CATEGORY:		return tr("Category");
			case BOOKING_AMOUNT:		return tr("Amount");
		}
	}
	return QVariant();
}

void BookingModel::insertDataEntry(QStringList booking)
{
	// insert
	beginInsertRows(QModelIndex(), m_bookingList.size(), m_bookingList.size());
	m_bookingList.push_back(booking);
    endInsertRows();
}

void BookingModel::removeDataEntry(const unsigned int index)
{
	// check index
	if (index >= (unsigned int)m_bookingList.size())
		return;

	// remove elemet with index
	beginRemoveRows(QModelIndex(), index, index);
	m_bookingList.removeAt(index);
	endRemoveRows();
}

void BookingModel::clearAll()
{
	if (m_bookingList.size() == 0)
		return;

	// clear all
	beginRemoveRows(QModelIndex(), 0, m_bookingList.size() - 1);
	m_bookingList.clear();
	endRemoveRows();
}
