
#include "lddsbus.h"

QByteArray LDdsBus::serializeVariant(const QVariant & variant)
{
    QByteArray  byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << variant; // –¥»Î QVariant
    return byteArray;
}

QVariant LDdsBus::deserializeVariant(const QByteArray & byteArray)
{
    QVariant    variant;
    QDataStream stream(byteArray);
    stream >> variant; // ∂¡»° QVariant
    return variant;
}