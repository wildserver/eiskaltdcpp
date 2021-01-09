/***************************************************************************
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 3 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
***************************************************************************/

#pragma once

#include <QAbstractItemModel>
#include <QHash>

#define COLUMN_USER_NICK        0
#define COLUMN_USER_HOST        1
#define COLUMN_USER_SEEN        2
#define COLUMN_USER_DESC        3

class FavoriteUserItem{

public:

    FavoriteUserItem(const QList<QVariant> &data, FavoriteUserItem *parent = nullptr);
    ~FavoriteUserItem();

    void appendChild(FavoriteUserItem *child);

    FavoriteUserItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    FavoriteUserItem *parent();

    QList<FavoriteUserItem*> childItems;

    void updateColumn(const int, const QVariant &);
    QString cid;

private:
    QList<QVariant> itemData;
    FavoriteUserItem *parentItem;
};

class FavoriteUsersModel : public QAbstractItemModel
{
Q_OBJECT
public:
    typedef QVariantMap VarMap;

    explicit FavoriteUsersModel(QObject *parent = nullptr);
    ~FavoriteUsersModel() override;

    /** */
    QVariant data(const QModelIndex &, int) const override;
    /** */
    Qt::ItemFlags flags(const QModelIndex &) const override;
    /** */
    QVariant headerData(int section, Qt::Orientation, int role = Qt::DisplayRole) const override;
    /** */
    QModelIndex index(int, int, const QModelIndex &parent = QModelIndex()) const override;
    /** */
    QModelIndex parent(const QModelIndex &index) const override;
    /** */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    /** */
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    /** sort list */
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

    void addUser(const VarMap&);
    void updateUserStatus(const QString &, const QString &, const QString &);
    void removeUser(const QString &);

    FavoriteUserItem *itemForCID(const QString &cid){
        if (itemHash.contains(cid))
            return itemHash.value(cid);

        return nullptr;
    }

    QStringList getUsers() const;

    void repaint();
private:
    Qt::SortOrder sortOrder;
    int sortColumn;

    QHash<QString, FavoriteUserItem*> itemHash;

    FavoriteUserItem *rootItem;
};
