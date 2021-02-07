#include "tables.h"
#include <iostream>

namespace JOIN_SERVER {
int getId(TABLE *tbl, int &idx)
{
    return tbl->m_entities[idx].id;
}

std::string getName(TABLE *tbl, int &idx)
{
    if(idx == -1) return "";
    return tbl->m_entities[idx].name;
}

int check_id_in(TABLE *atbl, int id)
{
    for(int i = 0; i < atbl->m_entities.size(); ++i)
        if(getId(atbl, i) == id) return i;

    return -1;
}


struct TABLE_COMP{
    virtual bool comp(TABLE *a, int idx)=0;
};

struct TABLE_COMP_INTERSECT: public TABLE_COMP{
    virtual bool comp(TABLE *a,  int val){
        int bpos = check_id_in(a, val);
        if(bpos != -1) return true;
        return false;
    }
};

struct TABLE_COMP_DIFFER: public TABLE_COMP{
    virtual bool comp(TABLE *a, int val){
        int apos = check_id_in(a, val);
        if(apos == -1) return true;
        return false;
    }
};

void fill_struct_with(TABLE *fst, TABLE *snd, TABLE_OPS *accum, TABLE_COMP &cmp){
    int icnt = 0;
    int aval = 0;
    int bpos = 0;
    while (icnt < fst->m_entities.size()) {
        aval = fst->m_entities.at(icnt).id;
        bpos = check_id_in(snd, aval);
        if(cmp.comp(snd,aval))
            accum->m_entities.push_back(std::make_pair(ENTITIE{aval,getName(fst, icnt)},ENTITIE{aval,getName(snd, bpos)}));
        ++icnt;
    }
}



J_SERVER::J_SERVER()
{
    m_a = new TABLE();
    m_b = new TABLE();
}

J_SERVER::~J_SERVER()
{
    delete m_a;
    delete m_b;
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

TABLE_OPS* J_SERVER::INTERSECTION()
{
    TABLE_OPS *c = new TABLE_OPS();
    return intersect(m_a, m_b, c, 0);
}

TABLE_OPS* J_SERVER::SYMMETRIC_DIFFERENCE()
{
    TABLE_OPS *c = new TABLE_OPS();
    return difference(m_a, m_b, c, 0);
}

std::string J_SERVER::insert(std::string tableName, int id, std::string name)
{
    if(tableName.compare("A") == 0)return insert_(m_a, id, name);
    else
        if(tableName.compare("B") == 0)return insert_(m_b, id, name);
    return "ERR No SUCH TABLE";
}

void J_SERVER::pushBack(TABLE *tbl, int id, std::string name)
{
    tbl->m_entities.push_back(ENTITIE{id,name});
}


std::string  J_SERVER::insert_(TABLE *atbl, int id, std::string name)
{
    if(check_id_in(atbl,id) == -1){
        pushBack(atbl,id,name);
    }else{
        return "Err duplicate " + std::to_string(id);
    }
    return "OK";
}


TABLE_OPS* J_SERVER::intersect(TABLE *a, TABLE *b, TABLE_OPS *accum, int apos)
{
    //check something shorter ))
    TABLE_COMP_INTERSECT intersect;
    if(a->m_entities.size() < b->m_entities.size())
        fill_struct_with(a, b, accum, intersect);
    else {
        fill_struct_with(b, a, accum, intersect);
    }
    return accum;

}

TABLE_OPS* J_SERVER::difference(TABLE *a, TABLE *b, TABLE_OPS *accum, int apos)
{
    //no description where table A and table B
    TABLE_COMP_DIFFER differ;
    fill_struct_with(a, b, accum, differ);
    fill_struct_with(b, a, accum, differ);
    return accum;
}

}
