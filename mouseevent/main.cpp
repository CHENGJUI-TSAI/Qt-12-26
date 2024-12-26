#include "mouseevent.h"
#include <QWheelEvent>
#include <QListWidget>

MouseEvent::MouseEvent(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("測試滑鼠事件"));

    // 初始化 statusLabel
    statusLabel = new QLabel;
    statusLabel->setText(tr("指標位置"));
    statusLabel->setFixedWidth(150);
    statusLabel->setStyleSheet("color: blue; font-weight: bold;");

    // 初始化 mousePosLabel
    mousePosLabel = new QLabel;
    mousePosLabel->setText(tr(" "));
    mousePosLabel->setFixedWidth(150);
    mousePosLabel->setStyleSheet("color: green; font-style: italic;");

    // 初始化事件記錄
    eventLogWidget = new QListWidget;
    eventLogWidget->setMinimumHeight(100);

    // 設置中心 widget
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(eventLogWidget);
    setCentralWidget(centralWidget);

    // 添加永久 widget 到狀態列
    statusBar()->addPermanentWidget(statusLabel);
    statusBar()->addPermanentWidget(mousePosLabel);

    // 啟用滑鼠追蹤
    setMouseTracking(true);

    resize(400, 300);
}

MouseEvent::~MouseEvent()
{
    // Qt 自動管理 widget 記憶體，無需手動刪除
}

void MouseEvent::logEvent(const QString &eventMessage)
{
    eventLogWidget->addItem(eventMessage);
}

void MouseEvent::mouseMoveEvent(QMouseEvent *event)
{
    QString positionText = QString("滑鼠位置：( %1, %2 )")
                               .arg(event->x())
                               .arg(event->y());
    mousePosLabel->setText(positionText);
    logEvent(tr("滑鼠移動：") + positionText);
}

void MouseEvent::mousePressEvent(QMouseEvent *event)
{
    QString status = QString("滑鼠按下：%1 ( %2, %3 )")
                         .arg(event->button() == Qt::LeftButton ? tr("左鍵") :
                                  event->button() == Qt::RightButton ? tr("右鍵") :
                                  event->button() == Qt::MiddleButton ? tr("中鍵") : tr("其他按鍵"))
                         .arg(event->x())
                         .arg(event->y());
    statusLabel->setText(status);
    logEvent(status);
}

void MouseEvent::mouseReleaseEvent(QMouseEvent *event)
{
    QString status = QString("滑鼠釋放：%1 ( %2, %3 )")
                         .arg(event->button() == Qt::LeftButton ? tr("左鍵") :
                                  event->button() == Qt::RightButton ? tr("右鍵") :
                                  event->button() == Qt::MiddleButton ? tr("中鍵") : tr("其他按鍵"))
                         .arg(event->x())
                         .arg(event->y());
    statusLabel->setText(status);
    logEvent(status);
}

void MouseEvent::mouseDoubleClickEvent(QMouseEvent *event)
{
    QString status = QString("滑鼠雙擊：%1 ( %2, %3 )")
                         .arg(event->button() == Qt::LeftButton ? tr("左鍵") :
                                  event->button() == Qt::RightButton ? tr("右鍵") :
                                  event->button() == Qt::MiddleButton ? tr("中鍵") : tr("其他按鍵"))
                         .arg(event->x())
                         .arg(event->y());
    statusLabel->setText(status);
    logEvent(status);
}

void MouseEvent::wheelEvent(QWheelEvent *event)
{
    QString status = QString("滾輪滾動：%1")
                         .arg(event->angleDelta().y() > 0 ? tr("向上") : tr("向下"));
    statusLabel->setText(status);
    logEvent(status);
}
