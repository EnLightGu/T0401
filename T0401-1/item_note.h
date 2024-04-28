#ifndef ITEM_NOTE_H
#define ITEM_NOTE_H

#include <QMetaType>

struct item_note{
    qint8 m_id;//大意id
    qint8 p_id;//前承id
    qint8 n_id;//后启id
    QString m_text;//大意主旨文本

    qint8 t_id;//内容id
    QString t_text;//内容文本

    item_note *p;//链表
    item_note *n;
};

Q_DECLARE_METATYPE(item_note)


#endif // ITEM_NOTE_H
