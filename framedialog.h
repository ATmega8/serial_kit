#ifndef FRAMEDIALOG_H
#define FRAMEDIALOG_H

#include <QDialog>
#include "frameconfigure.h"

namespace Ui {
class FrameDialog;
}

class FrameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FrameDialog(QWidget *parent = 0);
    ~FrameDialog();

    FrameConfigure frameConfig;

private slots:
    void on_buttonBox_accepted();

    void on_dt_currentIndexChanged(int index);

private:
    Ui::FrameDialog *ui;
};

#endif // FRAMEDIALOG_H
