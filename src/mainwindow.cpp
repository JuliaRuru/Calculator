#include "mainwindow.h"
#include "ui_mainwindow.h"

#ifdef __cplusplus
extern "C" {
#endif
    #include "calculator.h"
#ifdef __cplusplus
}
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //  валидаторы для диапазона х
    QDoubleValidator* doubleValidator_x_min = new QDoubleValidator(-1000000.0, 1000000.0, 2, ui->lineEdit_x_min);
    QDoubleValidator* doubleValidator_x_max = new QDoubleValidator(-1000000.0, 1000000.0, 2, ui->lineEdit_x_max);
    doubleValidator_x_min->setLocale(QLocale::English);
    doubleValidator_x_max->setLocale(QLocale::English);
    doubleValidator_x_min->setNotation(QDoubleValidator::StandardNotation);
    doubleValidator_x_max->setNotation(QDoubleValidator::StandardNotation);
    ui->lineEdit_x_min->setValidator(doubleValidator_x_min);
    ui->lineEdit_x_max->setValidator(doubleValidator_x_max);
    //  валидаторы для кредита
    QDoubleValidator* doubleValidator_credit_sum = new QDoubleValidator(0, 1000000000.0, 2, ui->lineEdit_credit_sum);
    QDoubleValidator* doubleValidator_credit_rate = new QDoubleValidator(0, 1000.0, 2, ui->lineEdit_credit_rate);
    doubleValidator_credit_sum->setLocale(QLocale::English);
    doubleValidator_credit_rate->setLocale(QLocale::English);
    doubleValidator_credit_sum->setNotation(QDoubleValidator::StandardNotation);
    doubleValidator_credit_rate->setNotation(QDoubleValidator::StandardNotation);
    ui->lineEdit_credit_sum->setValidator(doubleValidator_credit_sum);
    ui->lineEdit_credit_rate->setValidator(doubleValidator_credit_rate);

    QIntValidator *intValidator_credit_years = new QIntValidator(0, 100, ui->lineEdit_credit_years);
    QIntValidator *intValidator_credit_month = new QIntValidator(0, 100, ui->lineEdit_credit_month);
    ui->lineEdit_credit_years->setValidator(intValidator_credit_years);
    ui->lineEdit_credit_month->setValidator(intValidator_credit_month);
    //  валидаторы для поля х
    QDoubleValidator* doubleValidator_x_area = new QDoubleValidator(-1000000000000000000, 1000000000000000000, 7, ui->lineEdit_x_area);
    doubleValidator_x_area->setLocale(QLocale::English);
    doubleValidator_x_area->setNotation(QDoubleValidator::StandardNotation);
    ui->lineEdit_x_area->setValidator(doubleValidator_x_area);

    ui->lineEdit_credit_payment->setEnabled(false);
    ui->lineEdit_credit_overpayment->setEnabled(false);
    ui->lineEdit_credit_all_payments->setEnabled(false);

    connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(push_button()));
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(push_button()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(push_button()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(push_button()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(push_button()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(push_button()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(push_button()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(push_button()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(push_button()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(push_button()));

    connect(ui->pushButton_add,SIGNAL(clicked()),this,SLOT(push_button()));
    connect(ui->pushButton_sub,SIGNAL(clicked()),this,SLOT(push_button()));
    connect(ui->pushButton_mul,SIGNAL(clicked()),this,SLOT(push_button()));
    connect(ui->pushButton_div,SIGNAL(clicked()),this,SLOT(push_button()));
    connect(ui->pushButton_left_brace,SIGNAL(clicked()),this,SLOT(push_button()));
    connect(ui->pushButton_right_brace,SIGNAL(clicked()),this,SLOT(push_button()));
    connect(ui->pushButton_pow,SIGNAL(clicked()),this,SLOT(push_button()));
    connect(ui->pushButton_mod,SIGNAL(clicked()),this,SLOT(push_button()));

    connect(ui->pushButton_sin,SIGNAL(clicked()),this,SLOT(push_button()));
    connect(ui->pushButton_asin,SIGNAL(clicked()),this,SLOT(push_button()));
    connect(ui->pushButton_cos,SIGNAL(clicked()),this,SLOT(push_button()));
    connect(ui->pushButton_acos,SIGNAL(clicked()),this,SLOT(push_button()));
    connect(ui->pushButton_tan,SIGNAL(clicked()),this,SLOT(push_button()));
    connect(ui->pushButton_atan,SIGNAL(clicked()),this,SLOT(push_button()));
    connect(ui->pushButton_log,SIGNAL(clicked()),this,SLOT(push_button()));
    connect(ui->pushButton_ln,SIGNAL(clicked()),this,SLOT(push_button()));
    connect(ui->pushButton_sqrt,SIGNAL(clicked()),this,SLOT(push_button()));
    connect(ui->pushButton_x,SIGNAL(clicked()),this,SLOT(push_button()));
    connect(ui->pushButton_point,SIGNAL(clicked()),this,SLOT(push_button()));
    connect(ui->pushButton_clear,SIGNAL(clicked()),this,SLOT(push_button()));

    connect(ui->pushButton_back,SIGNAL(clicked()),this,SLOT(push_button_back()));
    connect(ui->pushButton_back_x,SIGNAL(clicked()),this,SLOT(push_button_back_x()));
    connect(ui->pushButton_enter,SIGNAL(clicked()),this,SLOT(push_button_enter()));
    connect(ui->pushButton_draw,SIGNAL(clicked()),this,SLOT(push_button_draw_clicked()));

    connect(ui->pushButton_credit_calculate,SIGNAL(clicked()),this,SLOT(push_button_credit_calculate()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::push_button()
{
    QString text = ui->lineEdit_result->text();
    QPushButton *button = (QPushButton *)sender();
    QString text_x = ui->lineEdit_x_area->text();

    if (button->text() == "AC") {
        ui->lineEdit_result->clear();
        ui->lineEdit_x_area->clear();
    }

    if (ui->lineEdit_result->hasFocus() && button->text() != "AC") {
        if (button->text() == "sin" || button->text() == "cos" || button->text() == "tan" ||
            button->text() == "asin" || button->text() == "acos" || button->text() == "atan" ||
            button->text() == "log" || button->text() == "ln" || button->text() == "sqrt") {
            ui->lineEdit_result->setText(text + button->text() + "(");
        } else if (button->text() == "÷") {
            ui->lineEdit_result->setText(text + "/");
        } else if (button->text() == ".") {
            if (text == "ERROR!" || text.isEmpty()) {
                ui->lineEdit_result->setText("0.");
            } else {
                ui->lineEdit_result->setText(text + button->text());
            }
        } else {
            ui->lineEdit_result->setText(text + button->text());
        }
    } else if (ui->lineEdit_x_area->hasFocus()) {
        if (button->text() == ".") {
            if (text_x == "ERROR!" || text_x.isEmpty()) {
                ui->lineEdit_x_area->setText("0.");
            } else if (!text_x.contains(".")) {
                ui->lineEdit_x_area->setText(text_x + button->text());
            }
        } else  if (button->text() == "0" || button->text() == "1" || button->text() == "2" || button->text() == "3" ||
                    button->text() == "4" || button->text() == "5" || button->text() == "6" || button->text() == "7" ||
                    button->text() == "8" || button->text() == "9") {
            ui->lineEdit_x_area->setText(text_x + button->text());
        } else if (button->text() == "-" && (text_x == "ERROR!" || text_x.isEmpty())) {
            ui->lineEdit_x_area->setText(button->text());
        }
    }
}

void MainWindow::push_button_back()
{
    QString text = ui->lineEdit_result->text();
    if (text.endsWith("acos(") || text.endsWith("asin(") ||
        text.endsWith("atan(") || text.endsWith("sqrt(")) {
        text = text.chopped(5);
    } else if (text.endsWith("cos(") || text.endsWith("sin(") ||
               text.endsWith("tan(") || text.endsWith("log(")) {
        text = text.chopped(4);
    } else if (text.endsWith("ln(") || text.endsWith("mod")) {
        text = text.chopped(3);
    } else if (text.isEmpty()) {
    } else {
    text = text.chopped(1);
    }
    ui->lineEdit_result->setText(text);
}

void MainWindow::push_button_back_x() {
    QString text = ui->lineEdit_x_area->text();
    ui->lineEdit_x_area->setText(text.chopped(1));
}

void MainWindow::push_button_enter()
{
    QString text = ui->lineEdit_result->text();
    QByteArray text_array = ui->lineEdit_result->text().toLower().toLatin1();
    char *buff = text_array.data();
    if ((text.contains("x") || text.contains("X")) && ui->lineEdit_x_area->text().isEmpty()) {
        if (check_formula(buff) == 0) {
            ui->widget->clearGraphs();
            ui->tabWidget->setCurrentWidget(ui->graph);
        } else {
            ui->lineEdit_result->setText("ERROR!");
        }
    } else if ((text.contains("x") || text.contains("X")) && !ui->lineEdit_x_area->text().isEmpty()) {
        if (check_formula(buff) == 0) {
            QByteArray text_array = ui->lineEdit_result->text().toLower().toLatin1();
            char *buff_formula = text_array.data();
            QByteArray x_array = ui->lineEdit_x_area->text().toLower().toLatin1();
            char *buff_x = x_array.data();
            ui->lineEdit_result->setText(text + "=" + QString::number(get_result(buff_formula, buff_x), 'f', 7));
        } else {
            ui->lineEdit_result->setText("ERROR!");
        }
    } else if (!text.contains("x") && !text.contains("X")) {
        if (check_formula(buff) == 0) {
            ui->lineEdit_result->setText(text + "=" + QString::number(pars(buff), 'f', 7));
        } else {
            ui->lineEdit_result->setText("ERROR!");
        }
    }
}

void MainWindow::push_button_draw_clicked()
{
    if (!ui->lineEdit_x_min->text().isEmpty() && !ui->lineEdit_x_max->text().isEmpty()) {

        double x_start = ui->lineEdit_x_min->text().toDouble();
        double x_end = ui->lineEdit_x_max->text().toDouble();
        double y_start = 0;
        double y_end = 0;
        double step = (x_end - x_start)/1000;
        double result;

        if (x_start < x_end) {
            ui->widget->xAxis->setRange(x_start, x_end);
            QByteArray text_array = ui->lineEdit_result->text().toLower().toLatin1();
            char *buff_formula = text_array.data();
            ui->widget->clearGraphs();
            QVector<double> x, y;
            x.clear();
            y.clear();
            ui->label_formula->setText("Формула: " + ui->lineEdit_result->text());

            for (; x_start <= x_end; x_start += step) {
                char buff_x[256] = "\0";
                std::cout << sprintf(buff_x, "%.10f", x_start);
                result = get_result(buff_formula, buff_x);
                if (y_start > result && !isinf(result) && !isnan(result)) {
                  y_start = result;
                } else if (y_end < result && !isinf(result) && !isnan(result)) {
                  y_end = result;
                }
                if (!isnan(result) && result < 1e6 && result > -1e6) {
                    x.push_back(x_start);
                    y.push_back(result);
                }
            }
            ui->widget->yAxis->setRange(y_start, y_end);
            ui->widget->addGraph();
            ui->widget->graph(0)->setData(x, y);
            ui->widget->xAxis->setLabel("x");
            ui->widget->yAxis->setLabel("y");
            ui->widget->replot();
            ui->lineEdit_x_min->clear();
            ui->lineEdit_x_max->clear();
        } else {
            QMessageBox *error = new QMessageBox;
            error->setWindowTitle("Ошибка!");
            error->setText("x min должен быть меньше x max");
            error->show();
        }
    } else {
        QMessageBox *error = new QMessageBox;
        error->setWindowTitle("Ошибка!");
        error->setText("Введите ограничения для х");
        error->show();
    }
}

void MainWindow::push_button_credit_calculate()
{
    bool sum, rate, year, month;
    int period = 0;
    double credit_sum = ui->lineEdit_credit_sum->text().toDouble(&sum);
    double credit_rate = ui->lineEdit_credit_rate->text().toDouble(&rate);
    int credit_years = ui->lineEdit_credit_years->text().toInt(&year);
    int credit_month = ui->lineEdit_credit_month->text().toInt(&month);
    if (ui->lineEdit_credit_years->text().isEmpty()) {
        credit_years = 0;
    }
    if (ui->lineEdit_credit_month->text().isEmpty())  {
        credit_month = 0;
    }
    period = credit_years * 12  + credit_month;
    double month_rate = credit_rate / 100 / 12;
    if (sum && rate) {
        if (!ui->radioButton_annuitet->isChecked() && !ui->radioButton_diff->isChecked()) {
            QMessageBox * box = new QMessageBox;
            box->setWindowTitle("Ошибка!");
            box->setText("Не выбран вид платежей");
            box->show();
        } else if (ui->radioButton_annuitet->isChecked()) {
            double payment = credit_sum * (month_rate + (month_rate / (pow((1 + month_rate), period ) - 1)));
            double total = period * payment;
            double overpay = total - credit_sum;
            QString tmp_firstpay = QString::number(payment, 'f' , 2);
            ui->lineEdit_credit_payment->setText(tmp_firstpay);
            QString tmp_overpay = QString::number(overpay, 'f' , 2);
            ui->lineEdit_credit_overpayment->setText(tmp_overpay);
            QString tmp_total = QString::number(total, 'f' , 2);
            ui->lineEdit_credit_all_payments->setText(tmp_total);
        } else if (ui->radioButton_diff->isChecked()) {
            double equal_part = credit_sum / period;
            double remain = credit_sum;
            double overpay = 0.0;
            double maxpay = credit_sum * month_rate + equal_part;
            double minpay = 0;
            for (int i = period; i > 0; i--) {
                if (i == 1){
                    minpay = remain * month_rate + equal_part;
                }
                overpay += remain * month_rate;
                remain -= equal_part;
            }
            double total = overpay + credit_sum;
            QString tmp_maxpay = QString::number(maxpay, 'f' , 2);
            QString tmp_minpay = QString::number(minpay, 'f' , 2);
            ui->lineEdit_credit_payment->setText(tmp_minpay+ " ... " + tmp_maxpay);
            QString tmp_overpay = QString::number(overpay, 'f' , 2);
            ui->lineEdit_credit_overpayment->setText(tmp_overpay);
            QString tmp_total = QString::number(total, 'f' , 2);
            ui->lineEdit_credit_all_payments->setText(tmp_total);
        }
    } else {
        QMessageBox * box = new QMessageBox;
        box->setWindowTitle("Ошибка!");
        box->setText("Введены не все данные");
        box->show();
    }
}

