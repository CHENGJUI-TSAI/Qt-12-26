#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include <QMainWindow>
#include <QLabel>
#include <QListWidget>
#include <QMouseEvent>
#include <QImage>

class MouseEvent : public QMainWindow {
    Q_OBJECT

public:
    explicit MouseEvent(QWidget *parent = nullptr);
    ~MouseEvent();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QLabel *imageLabel;
    QImage *image;
    QListWidget *eventLogWidget;

    void logEvent(const QString &eventMessage);
    void openImageFile();
};

#endif // MOUSEEVENT_H
