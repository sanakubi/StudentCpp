#ifndef CLALC_H
#define CLALC_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class clalc;
}

class clalc : public QMainWindow
{
    Q_OBJECT

public:
    explicit clalc(QWidget *parent = nullptr);
    ~clalc();
private slots:
    void on_numbutt_1_clicked();
    void on_numbutt_2_clicked();
    void on_numbutt_000_clicked();
    void on_numbutt_3_clicked();
    void on_numbutt_4_clicked();
    void on_numbutt_5_clicked();
    void on_numbutt_6_clicked();
    void on_numbutt_7_clicked();
    void on_numbutt_8_clicked();
    void on_numbutt_9_clicked();
    void on_numbutt_0_clicked();
    void on_numbutt_00_clicked();
    void on_butt_plus_clicked();
    void on_butt_minus_clicked();
    void on_butt_multiplication_clicked();
    void on_butt_division_clicked();
    void on_butt_Go_clicked();
    void on_CEL_clicked();
    void on_step_clicked();
    void on_OpenSk_clicked();
    void on_CloseSk_clicked();
    void on_Clear_clicked();
    void on_UWU_clicked();
    void on_step_3_clicked();
    void on_kor_clicked();
    void on_back_clicked();
    void on_devmode_button_clicked();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::clalc *ui;
};

#endif // CLALC_H
