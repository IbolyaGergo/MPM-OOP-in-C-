#include "zad8.h"
#include <algorithm>

zad8::zad8(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    
    for (int i = 0; i < 10; i++)
    {
        questions[i].setQuestion(QString("Otazka_%1?").arg(i));
        questions[i].setAns(i % 4);
        questionCopy[i] = questions[i];
    }

    
}

void zad8::on_Uroven_currentIndexChanged(int index)
{
    if (index == 0)
    {
        ui.zol_0->setVisible(true);
        ui.zol_1->setVisible(true);
        ui.zol_2->setVisible(true);
    }

    else if (index == 1)
    {
        ui.zol_0->setVisible(true);
        ui.zol_1->setVisible(true);
        ui.zol_2->setVisible(false);
    }

    else if (index == 2)
    {
        ui.zol_0->setVisible(true);
        ui.zol_1->setVisible(false);
        ui.zol_2->setVisible(false);
    }
}

void zad8::on_Meno_textChanged(const QString& text)
{
    if (text == Q_NULLPTR)
    {
        ui.Meno->setEnabled(true);
        ui.Uroven->setEnabled(true);
        ui.Nahodne->setEnabled(true);
        ui.NovaHra->setEnabled(false);
        ui.UkoncitHru->setEnabled(false);
        ui.zoliky->setEnabled(false);
        ui.OtazkaBox->setEnabled(false);
        ui.Moznosti->setEnabled(false);
        ui.PotvrdBox->setEnabled(false);
    }
    else
    {
        ui.NovaHra->setEnabled(true);
        player.setName(text);
    }
}

void zad8::on_NovaHra_clicked()
{
    ui.Meno->setEnabled(false);

    ui.NovaHra->setEnabled(false);
    ui.UkoncitHru->setEnabled(true);

    ui.Uroven->setEnabled(false);

    ui.zoliky->setEnabled(true);
    ui.zol_0->setEnabled(true);
    ui.zol_1->setEnabled(true);
    ui.zol_2->setEnabled(true);

    ui.Nahodne->setEnabled(false);
    if (ui.Nahodne->isChecked())
    {
        shuffled = 1;
        std::random_shuffle(&questions[0], &questions[9]);
    }
    else if(!ui.Nahodne->isChecked() && shuffled)
    {
        for (size_t i = 0; i < 10; i++)
        {
            questions[i] = questionCopy[i];
        }
        shuffled = 0;
    }
    ui.OtazkaBox->setEnabled(true);
    ui.Moznosti->setEnabled(true);

    ui.PotvrdBox->setEnabled(true);

    ui.OtazkaText->setMarkdown(questions[counter].getQ());
    for (int i = 0; i < 4; i++)
    {
        ui.buttonGroup->buttons()[i]->setText(questions[counter].getPossib(i));
    }

}

void zad8::on_Potvrdit_clicked()
{
    for (int i = 0; i < 4; i++)
    {
        ui.buttonGroup->buttons()[i]->setEnabled(true);
    }

    if (ui.buttonGroup->buttons()[questions[counter].getAns()]->isChecked())
    {
        ui.Score->setValue(player.getScore() + 1.0);
        player.setScore(player.getScore() + 1.0);
    }

    else
    {
        if (player.getScore() > 0.5)
        {
            ui.Score->setValue(player.getScore() - 1.0);
            player.setScore(player.getScore() - 1.0);
        }
    }
    counter++;
    if (counter == 10)
    {
        ui.OtazkaText->setMarkdown(QString("Koniec hry.\n Hrac %1 ma finalne skore: %2").arg(player.getName()).arg(player.getScore()));
        counter = 0;
        player.setScore(0);
        ui.Score->setValue(0);
        ui.Meno->setText(Q_NULLPTR);
    }
    else
    {
        ui.OtazkaText->setMarkdown(questions[counter].getQ());
        for (int i = 0; i < 4; i++)
        {
            ui.buttonGroup->buttons()[i]->setText(questions[counter].getPossib(i));
        }
        qDebug() << counter;
    }
    ui.zoliky->setEnabled(true);
}

void zad8::on_Preskocit_clicked()
{
    for (int i = 0; i < 4; i++)
    {
        ui.buttonGroup->buttons()[i]->setEnabled(true);
    }

    if (player.getScore() > 0.5)
    {
        ui.Score->setValue(player.getScore() - 0.5);
        player.setScore(player.getScore() - 0.5);
    }
    counter++;
    if (counter == 10)
    {
        ui.OtazkaText->setMarkdown(QString("Koniec hry.\n Hrac %1 ma finalne skore: %2").arg(player.getName()).arg(player.getScore()));
        counter = 0;
        player.setScore(0);
        ui.Score->setValue(0);
        ui.Meno->setText(Q_NULLPTR);
    }
    else
    {
        ui.OtazkaText->setMarkdown(questions[counter].getQ());
        for (int i = 0; i < 4; i++)
        {
            ui.buttonGroup->buttons()[i]->setText(questions[counter].getPossib(i));
        }
        qDebug() << counter;
    }
    ui.zoliky->setEnabled(true);
}

void zad8::on_UkoncitHru_clicked()
{
    double score = player.getScore();
    while (counter != 10)
    {
        if (score > 0)
        {
            score -= 0.5;
            player.setScore(score);
        }
        counter++;
    }
    ui.OtazkaText->setMarkdown(QString("Koniec hry.\n Hrac %1 ma finalne skore: %2").arg(player.getName()).arg(player.getScore()));
    counter = 0;
    player.setScore(0);
    ui.Score->setValue(0);
    ui.Meno->setText(Q_NULLPTR);
}

void zad8::on_zol_0_clicked()
{
    if (questions[counter].getAns() == 0 || questions[counter].getAns() == 3)
    {
        ui.buttonGroup->buttons()[1]->setEnabled(false);
        ui.buttonGroup->buttons()[2]->setEnabled(false);
        ui.radioButton_A->setChecked(true);
    }
    else
    {
        ui.buttonGroup->buttons()[questions[counter].getAns() - 1]->setEnabled(false);
        ui.buttonGroup->buttons()[questions[counter].getAns() + 1]->setEnabled(false);
        if (ui.buttonGroup->buttons()[0]->isEnabled())
        {
            ui.radioButton_A->setChecked(true);
        }
        else
        {
            ui.radioButton_D->setChecked(true);
        }
    }
    ui.zol_0->setEnabled(false);
    ui.zoliky->setEnabled(false);
}

void zad8::on_zol_1_clicked()
{
    if (questions[counter].getAns() == 0 || questions[counter].getAns() == 3)
    {
        ui.buttonGroup->buttons()[1]->setEnabled(false);
        ui.buttonGroup->buttons()[2]->setEnabled(false);
        ui.radioButton_A->setChecked(true);
    }
    else
    {
        ui.buttonGroup->buttons()[questions[counter].getAns() - 1]->setEnabled(false);
        ui.buttonGroup->buttons()[questions[counter].getAns() + 1]->setEnabled(false);
        if (ui.buttonGroup->buttons()[0]->isEnabled())
        {
            ui.radioButton_A->setChecked(true);
        }
        else
        {
            ui.radioButton_D->setChecked(true);
        }
    }
    ui.zol_1->setEnabled(false);
    ui.zoliky->setEnabled(false);
}

void zad8::on_zol_2_clicked()
{
    if (questions[counter].getAns() == 0 || questions[counter].getAns() == 3)
    {
        ui.buttonGroup->buttons()[1]->setEnabled(false);
        ui.buttonGroup->buttons()[2]->setEnabled(false);
        ui.radioButton_A->setChecked(true);
    }
    else
    {
        ui.buttonGroup->buttons()[questions[counter].getAns() - 1]->setEnabled(false);
        ui.buttonGroup->buttons()[questions[counter].getAns() + 1]->setEnabled(false);
        if (ui.buttonGroup->buttons()[0]->isEnabled())
        {
            ui.radioButton_A->setChecked(true);
        }
        else
        {
            ui.radioButton_D->setChecked(true);
        }
    }
    ui.zol_2->setEnabled(false);
    ui.zoliky->setEnabled(false);
}

