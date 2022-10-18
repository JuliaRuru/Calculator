#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <iostream>
#include <QKeyEvent>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void push_button();
    void push_button_back();
    void push_button_enter();
    void push_button_draw_clicked();
    void push_button_credit_calculate();
    void push_button_back_x();
};

class QLineWithoutEdit: public QLineEdit
{
public:
    QLineWithoutEdit(QWidget *parent = 0) : QLineEdit(parent) { }
protected:
    void keyPressEvent(QKeyEvent *event)
    {
          event->ignore();
    }
};

#endif // MAINWINDOW_H
