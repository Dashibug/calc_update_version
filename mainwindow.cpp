#include "MainWindow.h"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->comboBox, &QComboBox::textActivated, this, &MainWindow::buttonControl);
    buttonControl();
}

void MainWindow::buttonControl() {
    if (ui->comboBox->currentText().toInt() > 2) ui->pushButton_2->setEnabled(true);
    else ui->pushButton_2->setEnabled(false);
    if (ui->comboBox->currentText().toInt() > 3) ui->pushButton_3->setEnabled(true);
    else ui->pushButton_3->setEnabled(false);
    if (ui->comboBox->currentText().toInt() > 4) ui->pushButton_4->setEnabled(true);
    else ui->pushButton_4->setEnabled(false);
    if (ui->comboBox->currentText().toInt() > 5) ui->pushButton_5->setEnabled(true);
    else ui->pushButton_5->setEnabled(false);
    if (ui->comboBox->currentText().toInt() > 6) ui->pushButton_6->setEnabled(true);
    else ui->pushButton_6->setEnabled(false);
    if (ui->comboBox->currentText().toInt() > 7) ui->pushButton_7->setEnabled(true);
    else ui->pushButton_7->setEnabled(false);
    if (ui->comboBox->currentText().toInt() > 8) ui->pushButton_8->setEnabled(true);
    else ui->pushButton_8->setEnabled(false);
    if (ui->comboBox->currentText().toInt() > 9) ui->pushButton_9->setEnabled(true);
    else ui->pushButton_9->setEnabled(false);
    if (ui->comboBox->currentText().toInt() > 10) ui->pushButton_A->setEnabled(true);
    else ui->pushButton_A->setEnabled(false);
    if (ui->comboBox->currentText().toInt() > 11) ui->pushButton_B->setEnabled(true);
    else ui->pushButton_B->setEnabled(false);
    if (ui->comboBox->currentText().toInt() > 12) ui->pushButton_C->setEnabled(true);
    else ui->pushButton_C->setEnabled(false);
    if (ui->comboBox->currentText().toInt() > 13) ui->pushButton_D->setEnabled(true);
    else ui->pushButton_D->setEnabled(false);
    if (ui->comboBox->currentText().toInt() > 14) ui->pushButton_E->setEnabled(true);
    else ui->pushButton_E->setEnabled(false);
    if (ui->comboBox->currentText().toInt() > 15) ui->pushButton_F->setEnabled(true);
    else ui->pushButton_F->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

double MainWindow::predstav(int system, QString numberQstring) {
    std::string number = numberQstring.toStdString();
    std::vector<int> integer;
    std::vector<int> fractional;
    bool isInt = true;
    int startingPoint = 0;
    if (number[0] == '-') startingPoint = 1;

    for (int i = startingPoint; i < number.size(); ++i) {//проверка на допустимое значение
        if (std::find(validValues.begin(), validValues.end(), number[i]) == validValues.end()) {
            invalidSymbol = 1;
            return NULL;
        }
    }

    for (int i = startingPoint; i < number.size(); ++i) {//допустимость для системы счисления
        auto pos = std::find(validDigit.begin(), validDigit.end(), number[i]);
        if (pos - validDigit.begin() >= system) {
            invalidDigit = 1;
            return NULL;
        }
    }

    for (int i = startingPoint; i < number.size(); ++i) {
        if (number[i] == ',' || number[i] == '.') {
            isInt = false;
            continue;
        }
        if (isInt) {
            if (number[i] == 'A' || number[i] == 'a') integer.push_back(10);
            else if (number[i] == 'B' || number[i] == 'b') integer.push_back(11);
            else if (number[i] == 'C' || number[i] == 'c') integer.push_back(12);
            else if (number[i] == 'D' || number[i] == 'd') integer.push_back(13);
            else if (number[i] == 'E' || number[i] == 'e') integer.push_back(14);
            else if (number[i] == 'F' || number[i] == 'f') integer.push_back(15);
            else integer.push_back((int)number[i] - 48);
        }
        else {
            if (number[i] == 'A' || number[i] == 'a') fractional.push_back(10);
            else if (number[i] == 'B' || number[i] == 'b') fractional.push_back(11);
            else if (number[i] == 'C' || number[i] == 'c') fractional.push_back(12);
            else if (number[i] == 'D' || number[i] == 'd') fractional.push_back(13);
            else if (number[i] == 'E' || number[i] == 'e') fractional.push_back(14);
            else if (number[i] == 'F' || number[i] == 'f') fractional.push_back(15);
            else fractional.push_back((int)number[i] - 48);
        }
    }
    std::reverse(integer.begin(), integer.end());//преобразует числовую строку, представляющую число в заданной системе счисления, в число с плавающей запятой.
    double var = 0;
    for (int i = 0; i < integer.size(); ++i) {
        var += (integer[i] * pow(system, i));
    }
    if (!isInt) {
        for (int i = 0; i < fractional.size(); ++i) {
            var += (fractional[i] * pow(system, -(i + 1)));
        }
    }
    return var;
}

void MainWindow::save_first() {
    first_var = predstav(ui->comboBox->currentText().toInt(), ui->text_1var->text());
    if (invalidSymbol) {
        QMessageBox::information(this, QString("Error!"), QString("Used invalid symbol"));
        on_pushButton_AC_clicked();
        return;
    }
    if (invalidDigit) {
        QMessageBox::information(this, QString("Error!"), QString("Used invalid digit for chosen notation"));
        on_pushButton_AC_clicked();
        return;
    }
    if (var_sign) {
        first_var *= (-1);
    }
    ui->text_1var->setText("");
}

void MainWindow::save_second() {
    second_var = predstav(ui->comboBox->currentText().toInt(), ui->text_1var->text());

    if (invalidSymbol) {
        QMessageBox::information(this, QString("Error!"), QString("Used invalid symbol"));
        on_pushButton_AC_clicked();
        return;
    }
    if (invalidDigit) {
        QMessageBox::information(this, QString("Error!"), QString("Used invalid digit for chosen notation"));
        on_pushButton_AC_clicked();
        return;
    }
    if (var_sign) {
        second_var *= (-1);
    }
    ui->text_1var->setText("");
}

void MainWindow::on_pushButton_1_clicked() {
    ui->text_1var->setText(ui->text_1var->text() + "1");
}

void MainWindow::on_pushButton_2_clicked() {
    ui->text_1var->setText(ui->text_1var->text() + "2");
}

void MainWindow::on_pushButton_3_clicked() {
    ui->text_1var->setText(ui->text_1var->text() + "3");
}

void MainWindow::on_pushButton_4_clicked() {
    ui->text_1var->setText(ui->text_1var->text() + "4");
}

void MainWindow::on_pushButton_5_clicked() {
    ui->text_1var->setText(ui->text_1var->text() + "5");
}

void MainWindow::on_pushButton_6_clicked() {
    ui->text_1var->setText(ui->text_1var->text() + "6");
}

void MainWindow::on_pushButton_7_clicked() {
    ui->text_1var->setText(ui->text_1var->text() + "7");
}

void MainWindow::on_pushButton_8_clicked() {
    ui->text_1var->setText(ui->text_1var->text() + "8");
}

void MainWindow::on_pushButton_9_clicked() {
    ui->text_1var->setText(ui->text_1var->text() + "9");
}

void MainWindow::on_pushButton_A_clicked() {
    ui->text_1var->setText(ui->text_1var->text() + "A");
}

void MainWindow::on_pushButton_B_clicked() {
    ui->text_1var->setText(ui->text_1var->text() + "B");
}

void MainWindow::on_pushButton_C_clicked() {
    ui->text_1var->setText(ui->text_1var->text() + "C");
}

void MainWindow::on_pushButton_D_clicked() {
    ui->text_1var->setText(ui->text_1var->text() + "D");
}

void MainWindow::on_pushButton_E_clicked() {
    ui->text_1var->setText(ui->text_1var->text() + "E");
}

void MainWindow::on_pushButton_F_clicked() {
    ui->text_1var->setText(ui->text_1var->text() + "F");
}

void MainWindow::on_pushButton_0_clicked() {
    ui->text_1var->setText(ui->text_1var->text() + "0");
}

void MainWindow::on_pushButton_AC_clicked() {
    ui->text_1var->clear();
    operation_type = 0;
    var_sign = 0;
    first_var = 0;
    second_var = 0;
    answer = 0;
    invalidSymbol = 0;
    invalidDigit = 0;
}

void MainWindow::on_pushButton_delete_clicked() {
    ui->text_1var->backspace();
}

void MainWindow::on_pushButton_plus_clicked() {
    save_first();
    var_sign = 0;
    operation_type = 1;
}

void MainWindow::on_pushButton_minus_clicked() {
    save_first();
    var_sign = 0;
    operation_type = 2;
}

void MainWindow::on_pushButton_multiply_clicked() {
    save_first();
    var_sign = 0;
    operation_type = 3;
}

void MainWindow::on_pushButton_divide_clicked() {
    save_first();
    var_sign = 0;
    operation_type = 4;
}

void MainWindow::on_pushButton_point_clicked() {
    ui->text_1var->setText(ui->text_1var->text() + ".");
}

void MainWindow::on_pushButton_equal_clicked() {
    save_second();
    switch (operation_type) {
    case 1:
        answer = first_var + second_var;
        break;
    case 2:
        answer = first_var - second_var;
        break;
    case 3:
        answer = first_var * second_var;
        break;
    case 4:
        answer = first_var / second_var;
        break;
    case 0:
        answer = second_var;
        break;
    }
    ui->text_1var->setText(QString::number(answer));
    operation_type = 0;
    var_sign = 0;
    first_var = 0;
    second_var = 0;
    answer = 0;
    invalidSymbol = 0;
    invalidDigit = 0;
}

void MainWindow::on_pushButton_ChangeSign_clicked() {
    if (!var_sign) {
        ui->text_1var->setText("-" + ui->text_1var->text());
        var_sign = 1;
    }
    else {
        ui->text_1var->setText(ui->text_1var->text().remove(0,1));
        var_sign = 0;
    }
}

void MainWindow::save_firstMixed() {
    int64_t days, hours, mins, secs;
    if (ui->lineEdit_firstDay->text().isEmpty()) days = 0;
    else days = ui->lineEdit_firstDay->text().toInt(&ok);
    if (ui->lineEdit_firstHour->text().isEmpty()) hours = 0;
    else hours = ui->lineEdit_firstHour->text().toInt(&ok);
    if (ui->lineEdit_firstMinute->text().isEmpty()) mins = 0;
    else mins = ui->lineEdit_firstMinute->text().toInt(&ok);
    if (ui->lineEdit_firstSec->text().isEmpty()) secs = 0;
    else secs = ui->lineEdit_firstSec->text().toInt(&ok);

    first_operandSeconds = secs + (mins * 60) + (hours * 60 * 60) + (days * 24 * 60 * 60);
}

void MainWindow::save_secondMixed() {
    int64_t days, hours, mins, secs;
    if (ui->lineEdit_secondDay->text().isEmpty()) days = 0;
    else days = ui->lineEdit_secondDay->text().toInt(&ok);
    if (ui->lineEdit_secondHour->text().isEmpty()) hours = 0;
    else hours = ui->lineEdit_secondHour->text().toInt(&ok);
    if (ui->lineEdit_secondMinute->text().isEmpty()) mins = 0;
    else mins = ui->lineEdit_secondMinute->text().toInt(&ok);
    if (ui->lineEdit_secondSec->text().isEmpty()) secs = 0;
    else secs = ui->lineEdit_secondSec->text().toInt(&ok);

    second_operandSeconds = secs + (mins * 60) + (hours * 60 * 60) + (days * 24 * 60 * 60);
}

void MainWindow::on_pushButton_minusMixed_clicked() {
    save_firstMixed();
    save_secondMixed();
    if (!ok) {
        QMessageBox::information(this, QString("Error"), QString("Invalid data! only integer numbers allowed"));
        on_pushButton_ACMixed_clicked();
        return;
    }

    int64_t ansSeconds = first_operandSeconds - second_operandSeconds;
    if (ansSeconds < 0) ansSeconds *= (-1);

    showAnswer(ansSeconds);
}

void MainWindow::on_pushButton_plusMixed_clicked() {
    save_firstMixed();
    save_secondMixed();

    if (!ok) {
        QMessageBox::information(this, QString("Error"), QString("Invalid data! only integer numbers allowed"));
        on_pushButton_ACMixed_clicked();
        return;
    }

    int64_t ansSeconds = first_operandSeconds + second_operandSeconds;

    showAnswer(ansSeconds);
}

void MainWindow::showAnswer(int64_t ansSeconds)  {
    int64_t ansSecs = ansSeconds;
    int64_t ansMinutes = ansSecs / 60;
    ansSecs = ansSecs % 60;
    int64_t ansHours = ansMinutes / 60;
    ansMinutes = ansMinutes % 60;
    int64_t ansDays = ansHours / 24;
    ansHours = ansHours % 24;

    ui->lineEdit_answerSec->setText(QString::number(ansSecs));
    ui->lineEdit_answerMinute->setText(QString::number(ansMinutes));
    ui->lineEdit_answerHour->setText(QString::number(ansHours));
    ui->lineEdit_answerDay->setText(QString::number(ansDays));
}

void MainWindow::on_pushButton_ACMixed_clicked() {
    first_operandSeconds = 0;
    second_operandSeconds = 0;
    ok = true;

    ui->lineEdit_answerSec->clear();
    ui->lineEdit_answerMinute->clear();
    ui->lineEdit_answerHour->clear();
    ui->lineEdit_answerDay->clear();

    ui->lineEdit_firstSec->clear();
    ui->lineEdit_firstMinute->clear();
    ui->lineEdit_firstHour->clear();
    ui->lineEdit_firstDay->clear();

    ui->lineEdit_secondSec->clear();
    ui->lineEdit_secondMinute->clear();
    ui->lineEdit_secondHour->clear();
    ui->lineEdit_secondDay->clear();
}
