#include "mouseevent.h"
#include <QVBoxLayout>
#include <QPixmap>
#include <QFileDialog>
#include <QColor>

MouseEvent::MouseEvent(QWidget *parent)
    : QMainWindow(parent),
    imageLabel(new QLabel),
    image(new QImage),
    eventLogWidget(new QListWidget) {
    // 初始化圖片顯示區域
    imageLabel->setText(tr("請開啟檔案以載入圖片"));
    imageLabel->setAlignment(Qt::AlignCenter);

    // 設定介面佈局
    auto *layout = new QVBoxLayout;
    layout->addWidget(imageLabel);
    layout->addWidget(eventLogWidget);

    auto *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // 增加檔案選擇功能
    openImageFile();
}

MouseEvent::~MouseEvent() {
    delete image;
    delete eventLogWidget;
}

void MouseEvent::mousePressEvent(QMouseEvent *event) {
    QString status = tr("滑鼠按下位置：(%1, %2)")
                         .arg(event->position().x())
                         .arg(event->position().y());
    logEvent(status);
}

void MouseEvent::mouseMoveEvent(QMouseEvent *event) {
    if (!image->isNull()) {
        QPoint imagePos = event->position().toPoint() - imageLabel->pos();
        if (image->rect().contains(imagePos)) {
            // 取得該位置的 RGB 值
            QRgb pixelValue = image->pixel(imagePos);
            QColor color(pixelValue);
            QString positionText = tr("圖片內位置：(%1, %2)，RGB值：R=%3, G=%4, B=%5")
                                       .arg(imagePos.x())
                                       .arg(imagePos.y())
                                       .arg(color.red())
                                       .arg(color.green())
                                       .arg(color.blue());
            logEvent(positionText);
        }
    }
}

void MouseEvent::mouseReleaseEvent(QMouseEvent *event) {
    QString status = tr("滑鼠釋放位置：(%1, %2)")
                         .arg(event->position().x())
                         .arg(event->position().y());
    logEvent(status);
}

void MouseEvent::logEvent(const QString &eventMessage) {
    eventLogWidget->addItem(eventMessage);
    eventLogWidget->scrollToBottom();
}

void MouseEvent::openImageFile() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("選擇圖片檔案"), "", tr("圖片檔案 (*.png *.jpg *.jpeg *.bmp)"));

    if (filePath.isEmpty()) {
        logEvent(tr("未選擇任何檔案"));
        return;
    }

    if (!image->load(filePath)) {
        logEvent(tr("無法載入圖片：%1").arg(filePath));
        imageLabel->setText(tr("載入失敗，請選擇另一個檔案"));
    } else {
        imageLabel->setPixmap(QPixmap::fromImage(*image));
        logEvent(tr("成功載入圖片：%1").arg(filePath));
    }
}
