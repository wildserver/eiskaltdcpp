/***************************************************************************
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 3 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
***************************************************************************/

#pragma once

#include <QFrame>
#include <QResizeEvent>
#include <QMap>
#include <QList>
#include <QShortcut>

#include "ArenaWidget.h"

class FlowLayout;
class TabButton;

class TabFrame : public QFrame
{
Q_OBJECT
public:
    explicit TabFrame(QWidget *parent = nullptr);
    ~TabFrame() override;

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

public Q_SLOTS:
    virtual void removeWidget(ArenaWidget *awgt);
    virtual void insertWidget(ArenaWidget *awgt);
    virtual void updated(ArenaWidget *awgt);
    virtual bool hasWidget(ArenaWidget *awgt) const;
    virtual void redraw();
    virtual void mapped(ArenaWidget *awgt);
    virtual void toggled(ArenaWidget *awgt);
    virtual void nextTab();
    virtual void prevTab();
    void moveRight();
    void moveLeft();

private Q_SLOTS:
    void buttonClicked();
    void closeRequsted();
    void slotShorcuts();
    void slotContextMenu();
    void slotDropped(TabButton*);

protected:
    void resizeEvent(QResizeEvent *e) override;
    bool eventFilter(QObject *, QEvent *) override;

private:
    void historyPush(ArenaWidget*);
    void historyPurge(ArenaWidget*);
    void historyPop();

    FlowLayout *fr_layout;

    QList<ArenaWidget*> history;
    QList<QShortcut*> shortcuts;
    QMap<ArenaWidget*, TabButton*> awgt_map;
    QMap<TabButton*, ArenaWidget*> tbtn_map;
};
