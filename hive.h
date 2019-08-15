//
// Created by Barnabas Maidics on 2019-08-05.
//

#ifndef SQLSMITH_HIVE_H
#define SQLSMITH_HIVE_H


#include "schema.hh"
#include "relmodel.hh"
#include "dut.hh"

#include "hs2client/service.h"
#include "hs2client/session.h"
#include "hs2client/thrift-internal.h"

struct hive_connection {
    std::unique_ptr<hs2client::Service> service;
    std::unique_ptr<hs2client::Session> session;
    hive_connection(std::string &conninfo);
    void q(const char* query);
    ~hive_connection();
};


struct schema_hive : schema, hive_connection {
    schema_hive(std::string &conninfo);
    virtual std::string quote_name(const std::string &id) {
        return id;
    }
};

struct dut_hive : dut_base, hive_connection {
    virtual void test(const std::string &stmt);
    dut_hive(std::string &conninfo);
};

#endif //SQLSMITH_HIVE_H
