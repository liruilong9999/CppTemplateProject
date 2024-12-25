
#include "lddsbus.h"

QByteArray LDdsBus::serializeVariant(const QVariant & variant)
{
    QByteArray  byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << variant; // д�� QVariant
    return byteArray;
}

QVariant LDdsBus::deserializeVariant(const QByteArray & byteArray)
{
    QVariant    variant;
    QDataStream stream(byteArray);
    stream >> variant; // ��ȡ QVariant
    return variant;
}