#include "settingdialog.h"
#include "ui_settingdialog.h"

SettingDialog::SettingDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    this->move(parent->width()*0.5,parent->height()*0.5);
    ui->resolutionComboBox->addItem("800x600");
    ui->resolutionComboBox->addItem("1280x720");
    ui->resolutionComboBox->addItem("1920x1080");
    ui->resolutionComboBox->setCurrentText("1280x720");
    connect(ui->resolutionComboBox,&QComboBox::currentTextChanged,this,&SettingDialog::changeResolution);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::changeResolution(const QString &resolution)
{
    if (resolution == "800x600") {
        this->parentWidget()->resize(800, 600);
    } else if (resolution == "1280x720") {
        this->parentWidget()->resize(1280, 720);
    } else if (resolution == "1920x1080") {
        this->parentWidget()->resize(1920, 1080);
    }
}
