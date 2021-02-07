#ifndef TABLES_H
#define TABLES_H

#include <string>
#include <vector>

namespace JOIN_SERVER {
const int TABLE_SIZE = 128;

struct ENTITIE{
    int id;
    std::string name;
};

struct TABLE{
    std::vector<ENTITIE> m_entities;
};

struct TABLE_OPS{
    std::vector<std::pair<ENTITIE,ENTITIE>> m_entities;
};

struct J_SERVER{

    J_SERVER();
    ~J_SERVER();

    TABLE *m_a;
    TABLE *m_b;

    TABLE_OPS *INTERSECTION();
    TABLE_OPS *SYMMETRIC_DIFFERENCE();
    std::string insert(std::string tableName, int id, std::string name);
private:    
    void pushBack(TABLE *tbl,int id, std::string name);


    std::string insert_(TABLE *atbl, int id, std::string name);
    TABLE_OPS   *intersect(TABLE *a, TABLE *b, TABLE_OPS *accum, int apos);
    TABLE_OPS   *difference(TABLE *a, TABLE *b, TABLE_OPS *accum, int apos);
};

}
#endif // TABLES_H
