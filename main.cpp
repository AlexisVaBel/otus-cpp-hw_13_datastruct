#include <iostream>
#include "data/tables.h"


int main()
{    
    JOIN_SERVER::J_SERVER server;

    std::cout << server.insert("a",0,"test") << std::endl;
    std::cout << server.insert("A",0,"test") << std::endl;
    std::cout << server.insert("A",0,"test") << std::endl;
    std::cout << server.insert("B",0,"phase") << std::endl;
    std::cout << server.insert("A",1,"brest") << std::endl;
    std::cout << server.insert("A",5,"best") << std::endl;
    std::cout << server.insert("A",2,"achtung") << std::endl;
    std::cout << server.insert("B",32,"normal") << std::endl;
    std::cout << server.insert("B",2,"value") << std::endl;
    std::cout << server.insert("B",4,"gangboy") << std::endl;
    std::cout << server.insert("B",1,"badboy") << std::endl;


    JOIN_SERVER::TABLE_OPS *tbl = server.INTERSECTION();
    auto it = tbl->m_entities.begin();
    while (it != tbl->m_entities.end()) {
        std::cout << (*it).first.id << " | " << (*it).first.name  << " | " << (*it).second.name << std::endl;
        ++it;
    }

    std::cout << "--------------------------------------" << std::endl;
    JOIN_SERVER::TABLE_OPS *tbl2 = server.SYMMETRIC_DIFFERENCE();
    auto it2 = tbl2->m_entities.begin();
    while (it2 != tbl2->m_entities.end()) {
        std::cout << (*it2).first.id << " | " << (*it2).first.name  << " | " << (*it2).second.name << std::endl;
        ++it2;
    }
    delete tbl2;
    return 0;
}
