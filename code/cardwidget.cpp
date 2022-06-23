#include "cardwidget.h"
//#include "ui_cardwidget.h"

CardWidget::CardWidget(const Card& card, QWidget *parent) :
    QLabel(parent), _card(card)
{
    QString code = QString::fromStdString(_card.getCode());
    this->setText(code);

    QColor crA = QColor(225, 225, 225, 125);
    QString str = QString("QLabel{background:%1;}").arg(crA.name(QColor::HexRgb));
    this->setStyleSheet(str);
    this->setGeometry(QRect(500, 500, DefaultCardWidth, DefaultCardHeight));
    this->setAlignment(Qt::AlignmentFlag::AlignCenter);
}

CardWidget::~CardWidget()
{

}
