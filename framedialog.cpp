#include "framedialog.h"
#include "ui_framedialog.h"

FrameDialog::FrameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrameDialog)
{
    ui->setupUi(this);
}

FrameDialog::~FrameDialog()
{
    delete ui;
}

void FrameDialog::on_buttonBox_accepted()
{
    uint8_t fh[4] = {0};
    uint8_t ft[2] = {0};

    int count = 0;
    bool ok;
    QString s;

    if(!ui->fh1->text().isEmpty())
    {
        count++;
        fh[0] = ui->fh1->text().toUInt(&ok, 16);
    }
    if(!ui->fh2->text().isEmpty())
    {
        count++;
        fh[1] = ui->fh2->text().toUInt(&ok, 16);
    }
    if(!ui->fh3->text().isEmpty())
    {
        count++;
        fh[2] = ui->fh3->text().toUInt(&ok, 16);
    }
    if(!ui->fh4->text().isEmpty())
    {
        count++;
        fh[3] = ui->fh4->text().toUInt(&ok, 16);
    }

    frameConfig.setFrameHead((uint8_t*)&fh, count);
    count = 0;

    if(!ui->ft1->text().isEmpty())
    {
        count++;
        ft[0] = ui->ft1->text().toUInt(&ok, 16);
    }
    if(!ui->ft2->text().isEmpty())
    {
        count++;
        ft[1] = ui->ft2->text().toUInt(&ok, 16);
    }

    frameConfig.setFrameTail((uint8_t*)&ft, count);
    count = 0;

    count = ui->dt->currentIndex();

    switch(count)
    {
        case 0:
            frameConfig.setFrameDataType(FrameConfigure::FrameIntData);
            break;
        case 1:
            frameConfig.setFrameDataType(FrameConfigure::FrameUintData);
            break;
        case 2:
            frameConfig.setFrameDataType(FrameConfigure::FrameFloatData);
            break;
        case 3:
            frameConfig.setFrameDataType(FrameConfigure::FrameCharData);
            break;
        case 4:
            frameConfig.setFrameDataType(FrameConfigure::FrameFixData);
            break;
        case 5:
            frameConfig.setFrameDataType(FrameConfigure::FrameRawDate);
            break;
    }

    count = ui->dl->currentIndex();

    switch(count)
    {
        case 0:
            frameConfig.setFrameDataLen(FrameConfigure::FrameDataLen_OneByte);
            break;
        case 1:
            frameConfig.setFrameDataLen(FrameConfigure::FrameDataLen_TwoBytes);
            break;
        case 2:
            frameConfig.setFrameDataLen(FrameConfigure::FrameDataLen_ThreeBytes);
            break;
        case 3:
            frameConfig.setFrameDataLen(FrameConfigure::FrameDataLen_FourByte);
            break;
    }

    s = ui->sp->text();
    frameConfig.setFrameOther(s.toStdString()[0], ui->ll->text().toUInt());

    frameConfig.setFrameLen(ui->fl->text().toUInt());
}

void FrameDialog::on_dt_currentIndexChanged(int index)
{
   if(index == 5)
       ui->dl->setDisabled(true);
   else
       ui->dl->setDisabled(false);
}
