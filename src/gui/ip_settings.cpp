/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-03-25 02:05:03
 * @modify date 2023-03-25 14:12:27
 */

#include "gui/ip_settings.h"
// Qt
#include <QCheckBox>
#include <QDateTime>
#include <QGridLayout>
#include <QGroupBox>
#include <QListWidget>
#include <QNetworkInterface>
#include <QVBoxLayout>

namespace gui {

GeneralTab::GeneralTab(QWidget *parent)
    : QWidget(parent) {
  QGridLayout *mainLayout = new QGridLayout;

  const QString port_tooltip = "Input valid port number. Range from 1 to 65535";
  QValidator *port_validator = new QIntValidator(1, 65535, this);

  mainLayout->addWidget(new QLabel(tr("Your IP")), 0, 0, 1, 1);
  QString placeholder_ip = getAddress().toString();
  my_ip_                 = new QLabel(placeholder_ip);
  mainLayout->addWidget(my_ip_, 0, 1, 1, 2);

  mainLayout->addWidget(new QLabel(tr("Port")), 0, 4, 1, 1);
  my_port_ = new QLineEdit();
  my_port_->setValidator(port_validator);
  my_port_->setPlaceholderText("4040");
  my_port_->setToolTip(port_tooltip);
  mainLayout->addWidget(my_port_, 0, 5, 1, 2);

  QLabel *ip_address = new QLabel(tr("Opponent IP"));
  ip_address->setToolTip("Input valid IPv4 address from opponent machine (xxx.xxx.xxx.xxx)");
  mainLayout->addWidget(ip_address, 1, 0, 1, 1);

  ip_edit_         = new QLineEdit();
  QString ip_range = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
  QRegularExpression ip_regex("^" + ip_range + "(\\." + ip_range + ")" + "(\\." + ip_range + ")" + "(\\." + ip_range + ")$");
  ip_validator_ = new QRegularExpressionValidator(ip_regex, this);
  ip_edit_->setValidator(ip_validator_);
  ip_edit_->setPlaceholderText(placeholder_ip);
  ip_edit_->setToolTip("Input valid IPv4 address from opponent machine (xxx.xxx.xxx.xxx)");
  mainLayout->addWidget(ip_edit_, 1, 1, 1, 2);

  mainLayout->addWidget(new QLabel(tr("Port")), 1, 4, 1, 1);

  port_edit_ = new QLineEdit();
  port_edit_->setValidator(port_validator);
  port_edit_->setPlaceholderText("8080");
  port_edit_->setToolTip(port_tooltip);
  mainLayout->addWidget(port_edit_, 1, 5, 1, 2);

  setLayout(mainLayout);
}

/**
 * @brief get local IP address. If cannot find anything, return localhost.
 * 
 * source: https://stackoverflow.com/questions/13835989/get-local-ip-address-in-qt
 * 
 * @return const QHostAddress 
 */
const QHostAddress GeneralTab::getAddress() {
  const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
  for (const QHostAddress &address : QNetworkInterface::allAddresses()) {
    // qDebug() << address.toString();
    if (address.protocol() == QAbstractSocket::IPv4Protocol   // filter only IPv4 address
        && address != localhost                               // filter out localhost
        && address.toString().section(".", -1, -1) != "1") {  // filter out virtual machines' IP
      return address;
    }
  }
  return localhost;
}

/*
PermissionsTab::PermissionsTab(const QFileInfo &fileInfo, QWidget *parent)
    : QWidget(parent) {
  QGroupBox *permissionsGroup = new QGroupBox(tr("Permissions"));

  QCheckBox *readable = new QCheckBox(tr("Readable"));
  if (fileInfo.isReadable())
    readable->setChecked(true);

  QCheckBox *writable = new QCheckBox(tr("Writable"));
  if (fileInfo.isWritable())
    writable->setChecked(true);

  QCheckBox *executable = new QCheckBox(tr("Executable"));
  if (fileInfo.isExecutable())
    executable->setChecked(true);

  QGroupBox *ownerGroup = new QGroupBox(tr("Ownership"));

  QLabel *ownerLabel      = new QLabel(tr("Owner"));
  QLabel *ownerValueLabel = new QLabel(fileInfo.owner());
  ownerValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

  QLabel *groupLabel      = new QLabel(tr("Group"));
  QLabel *groupValueLabel = new QLabel(fileInfo.group());
  groupValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

  QVBoxLayout *permissionsLayout = new QVBoxLayout;
  permissionsLayout->addWidget(readable);
  permissionsLayout->addWidget(writable);
  permissionsLayout->addWidget(executable);
  permissionsGroup->setLayout(permissionsLayout);

  QVBoxLayout *ownerLayout = new QVBoxLayout;
  ownerLayout->addWidget(ownerLabel);
  ownerLayout->addWidget(ownerValueLabel);
  ownerLayout->addWidget(groupLabel);
  ownerLayout->addWidget(groupValueLabel);
  ownerGroup->setLayout(ownerLayout);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(permissionsGroup);
  mainLayout->addWidget(ownerGroup);
  mainLayout->addStretch(1);
  setLayout(mainLayout);
}

ApplicationsTab::ApplicationsTab(const QFileInfo &fileInfo, QWidget *parent)
    : QWidget(parent) {
  QLabel *topLabel = new QLabel(tr("Open with:"));

  QListWidget *applicationsListBox = new QListWidget;
  QStringList applications;

  for (int i = 1; i <= 30; ++i)
    applications.append(tr("Application %1").arg(i));
  applicationsListBox->insertItems(0, applications);

  QCheckBox *alwaysCheckBox;

  if (fileInfo.suffix().isEmpty())
    alwaysCheckBox = new QCheckBox(tr(
        "Always use this application to "
        "open this type of file"));
  else
    alwaysCheckBox = new QCheckBox(tr("Always use this application to "
                                      "open files with the extension '%1'")
                                       .arg(fileInfo.suffix()));

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(topLabel);
  layout->addWidget(applicationsListBox);
  layout->addWidget(alwaysCheckBox);
  setLayout(layout);
}
*/

///////////// Singleton /////////////
IPSettingDialog *IPSettingDialog::pinstance_{nullptr};
std::mutex IPSettingDialog::mutex_;

IPSettingDialog::IPSettingDialog(const QString &fileName, QWidget *parent)
    : QDialog(parent) {
  QFileInfo fileInfo(fileName);

  tabWidget    = new QTabWidget;
  tab_general_ = new GeneralTab();
  tabWidget->addTab(tab_general_, tr("General"));

  buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

  connect(buttonBox, &QDialogButtonBox::accepted, this, &IPSettingDialog::onAccept);
  connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(tabWidget);
  mainLayout->addWidget(buttonBox);
  setLayout(mainLayout);

  setWindowTitle(tr("Remote Connection Settings"));
}

IPSettingDialog::~IPSettingDialog() { pinstance_ = nullptr; }

IPSettingDialog *IPSettingDialog::GetInstance(const QString &fileName, QWidget *parent) {
  std::lock_guard<std::mutex> lock(mutex_);
  if (pinstance_ == nullptr) {
    pinstance_ = new IPSettingDialog(fileName, parent);
  }
  return pinstance_;
}
/////////////////////////////////////

void IPSettingDialog::onAccept() {
  QStringList res = {tab_general_->myIP(), tab_general_->myPort(), tab_general_->targetIP(), tab_general_->targetPort()};
  emit this->confirmIPs(res);
  this->accept();
}

}  // namespace gui
