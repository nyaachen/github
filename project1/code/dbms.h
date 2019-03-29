#ifndef DBMS_H_
#define DBMS_H_

#include "table.h"

namespace KTV {
    namespace dbms {
        class dbms_system {
        private:
            // 保存歌曲信息的数据库
            table::Table db_table;
            // 保存播放列表的第一首歌曲
            song::Song *playlist_head;
        };
    }
}


#endif