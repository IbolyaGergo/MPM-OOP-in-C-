#pragma once

#include <QtWidgets>
#include <ui_zad8.h>

class Player
{
private:
    QString name = "Fero";
    double score = 0;
public:
    Player() {}
    Player(QString n) { name = n; }
    QString getName() { return name; }
    void setName(QString text) { name = text; }
    double getScore() { return score; }
    void setScore(double a) { score = a; }
};

class Question
{
private:
    QString q = "otazka?";
    QString possib[4] = {"A)", "B)", "C)", "D)"};
    int ans = 0;
public:
    Question() {}
    QString getQ() { return q; }
    Question(const Question& q2) { q = q2.q; for (size_t i = 0; i < 4; i++) { possib[i] = q2.possib[i]; } ans = q2.ans; }
    
    void setQuestion(QString text) { q = text; }
    void setPossib(QString a, QString b, QString c, QString d) { possib[0] = "A) " + a; possib[1] = "B) " + b; possib[2] = "C) " + c; possib[3] = "D) " + d; }
    QString getPossib(int index) { return possib[index]; }
    int getAns() { return ans; }
    void setAns(int i) { ans = i; }
};

class zad8 : public QMainWindow
{
    Q_OBJECT

public:
    zad8(QWidget *parent = Q_NULLPTR);

private:
    Ui::zad8Class ui;
    Player player;
    Question questions[10];
    Question questionCopy[10];
    int shuffled = 0;
    int counter = 0;

private slots:
    void on_Uroven_currentIndexChanged(int index);
    void on_Meno_textChanged(const QString& text);
    void on_NovaHra_clicked();
    void on_Potvrdit_clicked();
    void on_Preskocit_clicked();
    void on_UkoncitHru_clicked();
    void on_zol_0_clicked();
    void on_zol_1_clicked();
    void on_zol_2_clicked();
};

