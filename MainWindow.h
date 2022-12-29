//
// Created by andyroiiid on 12/29/2022.
//

#pragma once

#include <QMainWindow>

#include "ImageList.h"
#include "ImageView.h"

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    ImageList *m_imageList;
    ImageView *m_imageView;
};
