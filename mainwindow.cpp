#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    readCount = 0;

    frameSM = new FrameStateMachine();
    m_state.state = FrameStateMachine::disable;

    ui->setupUi(this);

    ui->databits->addItem(tr("8 Bits"));
    ui->databits->addItem(tr("7 Bits"));

    ui->parity->addItem(tr("N"));
    ui->parity->addItem(tr("E"));
    ui->parity->addItem(tr("P"));

    ui->stopbits->addItem(tr("1 Bit"));
    ui->stopbits->addItem(tr("2 Bits"));

    connect(&serialPort, SIGNAL(readyRead()), SLOT(serialReader()));
    connect(&serialPort, SIGNAL(error(QSerialPort::SerialPortError)), SLOT(serialErrorHandler(QSerialPort::SerialPortError)));
    connect(&serial_timer, SIGNAL(timeout()), SLOT(serialTimeHandler()));

    serialInfoUpdate();
}

void MainWindow::serialInfoUpdate(void)
{
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->portnum->insertItem(0, info.systemLocation());
        ui->portnum->setCurrentIndex(0);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_portnum_activated(const QString &arg1)
{
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        if(ui->portnum->findText(info.systemLocation()) == -1)
        {
            ui->portnum->insertItem(0, info.systemLocation());
            ui->portnum->setCurrentIndex(0);
        }

        if(info.systemLocation() == arg1)
        {
           QString s = info.description() + tr(" ") + info.manufacturer() + tr(" ")
                   + tr("VID:") + (info.hasVendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : QString())
                   + tr(" ") + tr("PID:")
                   + (info.hasProductIdentifier() ? QString::number(info.productIdentifier(), 16): QString());
           ui->statusBar->showMessage(s);
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
//配置串口名称
   serialPort.setPortName(ui->portnum->currentText());

//配置波特率
   serialPort.setBaudRate(ui->baudrate->currentText().toInt());

//配置数据位
   if(ui->databits->currentText() == tr("7 Bits"))
    {
        if(serialPort.setDataBits(QSerialPort::Data7 ) != true)
        {
            ui->statusBar->showMessage(tr("set data bits as 7 bits error"));
            return;
        }
    }
    else  if(ui->databits->currentText() == tr("8 Bits"))
    {
        if(serialPort.setDataBits(QSerialPort::Data8) != true)
        {
            ui->statusBar->showMessage(tr("set data bits as 8 bits error"));
            return;
        }
    }

//配置停止位
   if(ui->stopbits->currentText() == tr("1 Bit"))
    {
        if(serialPort.setStopBits(QSerialPort::OneStop) != true)
        {
            ui->statusBar->showMessage(tr("set stop bits one stop bit error"));
            return;
        }
    }
    else  if(ui->stopbits->currentText() == tr("2 Bits"))
    {
        if(serialPort.setStopBits(QSerialPort::TwoStop) != true)
        {
            ui->statusBar->showMessage(tr("set stop bits as two stop bits error"));
            return;
        }
    }

//配置奇偶校验
   if(ui->parity->currentText() == tr("N"))
    {
        if(serialPort.setParity(QSerialPort::NoParity) != true)
        {
            ui->statusBar->showMessage(tr("set parity as none parity error"));
            return;
        }
    }
    else  if(ui->parity->currentText() == tr("E"))
    {
        if(serialPort.setParity(QSerialPort::EvenParity) != true)
        {
            ui->statusBar->showMessage(tr("set parity as even error"));
            return;
        }
    }
    else  if(ui->parity->currentText() == tr("O"))
    {
        if(serialPort.setParity(QSerialPort::OddParity) != true)
        {
            ui->statusBar->showMessage(tr("set parity as odd error"));
            return;
        }
    }

   if(!serialPort.open(QIODevice::ReadWrite))
       ui->statusBar->showMessage( tr("%1打开失败, error: %2").arg(serialPort.portName()).arg(serialPort.errorString()));
   else
       ui->statusBar->showMessage(tr("串口%1打开成功").arg((serialPort.portName())));
}

void MainWindow::on_pushButton_4_clicked()
{
    QString receiveFileName;

    receiveFileName = QFileDialog::getSaveFileName(this,
        tr("Open Receive File"), "/home/life", tr("Any files(*)"));

    receiveFile.setFileName(receiveFileName);

    if(!receiveFile.open(QIODevice::ReadWrite))
            ui->statusBar->showMessage(tr("open file error"));
    else
        ui->statusBar->showMessage(tr("open file succeed"));
}

void MainWindow::serialReader(void)
{
    int i;

    serialReadData =  serialPort.readAll();

    for(i = 0; i < serialReadData.length(); i++)
       frameSM->FrameStateMachineDispatch(&m_state, serialReadData[i]);

    if(m_state.state == FrameStateMachine::done)
    {
       frameSM->FrameStateMachineDispatch(&m_state, 0);

       if(m_state.dataType != FrameConfigure::FrameRawDate)
            receiveFile.write(m_state.res.toStdString().data());
       else
       {
            receiveFile.write(m_state.frameBuff);
       }

       frameSM->FrameStateMachineUpdateInfo(&m_state);
    }
}

void MainWindow::serialErrorHandler(QSerialPort::SerialPortError error)
{
    ui->statusBar->showMessage(tr("串口错误：%1").arg(error));
}

void MainWindow::serialTimeHandler(void)
{

}

void MainWindow::on_pushButton_3_clicked()
{
    QString fileName;

    serialPort.close();
    receiveFile.close();

    fileName = receiveFile.fileName();

    ui->statusBar->showMessage(tr("串口已关闭"));

    if(ui->checkBox_2->isChecked())
    {
       w.play(fileName);
    }
    else
        receiveFile.close();
}

void MainWindow::on_pushButton_5_clicked()
{
    QString hexBuff;
    int i = 0;
    char sendData;
    bool ok;

    if(!ui->checkBox->isChecked())
    {
        if(serialPort.write(ui->lineEdit_2->text().toStdString().data(),  ui->lineEdit_2->text().length()) < 0 )
            ui->statusBar->showMessage(tr("wirte serial error"));
        else
            ui->statusBar->showMessage(tr("wirte serial succeed"));
     }
    else
    {
        hexBuff = ui->lineEdit_2->text();

        for(i = 0; i < hexBuff.length()/2; i++)
        {
            sendData = (QString(hexBuff[2*i]) + QString(hexBuff[2*i+1])).toUInt(&ok, 16);

            if(ok)
                serialPort.write(&sendData, 1);
            else
            {
                ui->statusBar->showMessage(tr("convert error"));
                return;
            }
        }
             ui->statusBar->showMessage(tr("wirte serial succeed"));
    }
}

void MainWindow::on_pushButton_2_clicked()
{
   frameSM->frameDialog.show();
}

void MainWindow::on_pushButton_6_clicked()
{
   frameSM->FrameStateMachineUpdateInfo(&m_state);
   ui->statusBar->showMessage(tr("开始记录数据..."));
}
