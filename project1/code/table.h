#ifndef TABLE_H
#define TABLE_H

#include "song.h"
#include <vector>
#include <string>

namespace KTV {
    namespace table {
        class Table : public std::vector<song::Song> {
        public:
            Table();
            ~Table();
            // 歌曲检索
            Table view_subset() const;
            // 歌曲插入
            bool push(const song::Song &s);
            // 歌曲删除
            bool pop(size_t i); // TODO 优化这一函数实现
            // 歌曲排序
            Table order_by_() const;
            // 歌曲遍历： 请使用迭代器或下标
        };
    }
}






#endif