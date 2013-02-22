#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H

#include <QTableView>
#include <QWidget>
#include <QAbstractItemDelegate>

class FormGrid;

class MyTableView : public QTableView {
    Q_OBJECT
public:
    MyTableView(FormGrid*, QWidget* parentWidget = 0);
    MyTableView(QWidget* parentWidget = 0);
    void setFormGrid(FormGrid* par) { parent = par; }
signals:
    void showPicture();
protected slots:
    virtual void closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint);
protected:
    FormGrid* parent;
    virtual void currentChanged(const QModelIndex &, const QModelIndex &);
    virtual void keyPressEvent(QKeyEvent*);     // Обработка нажатий клавиш
};

#endif // MYTABLEVIEW_H
