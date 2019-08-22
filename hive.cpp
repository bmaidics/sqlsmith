//
// Created by Barnabas Maidics on 2019-08-05.
//

#include "hive.h"

#include "hs2client/columnar-row-set.h"
#include "hs2client/thrift-internal.h"

#include "gen-cpp/TCLIService.h"
#include "gen-cpp/TCLIService_types.h"
#include "hs2client/util.h"

using namespace hs2client;
using namespace std;

// connect hive
hive_connection::hive_connection(std::string &conninfo) {
    const std::string hostname = "localhost";
    const std::string test_db = "default";
    int port = 10000;
    ProtocolVersion protocol_version = ProtocolVersion::HS2CLIENT_PROTOCOL_V7;
    int conn_timeout = 9999;

    Status status = Service::Connect(hostname, port, conn_timeout, protocol_version, &service);
    if (!status.ok()) {
        cout << "Failed to connect to service: " << status.GetMessage();
        service->Close();
        return;
    }

    string user = "user";
    HS2ClientConfig config;
    status = service->OpenSession(user, config, &session);
    if (!status.ok()) {
        cout << "Failed to open session: " << status.GetMessage();
        session->Close();
        service->Close();
        return;
    }

    /*std::unique_ptr <Operation> use_db_op;

    status = session->ExecuteStatement("use " + test_db, &use_db_op);
    if (!status.ok()) {
        cout << "Failed to execute use db: " << status.GetMessage();
        use_db_op->Close();
        return;
    }*/
}

// execute queries on hive
void hive_connection::q(const char *query) {
    std::unique_ptr <Operation> execute_op;
    Status status = session->ExecuteStatement(query, &execute_op);
    if (!status.ok()) {
        cout << "Failed to execute select: " << status.GetMessage();
        execute_op->Close();
        return;
    }
    execute_op->Close();
}

// disconnect hive
hive_connection::~hive_connection() {
    cout<<"Hive connection closed" <<endl;
    session->Close();
    service->Close();
}

//load schema from hive
schema_hive::schema_hive(std::string &conninfo) : hive_connection(conninfo) {
    cerr << "init booltype, inttype, internaltype, arraytype here" << endl;
    booltype = sqltype::get("boolean");
    inttype = sqltype::get("int");
    internaltype = sqltype::get("internal");
    arraytype = sqltype::get("ARRAY");

    cerr << "Loading tables...";

    unique_ptr <Operation> op;
    Status status = session->ExecuteStatement("select table_name, table_schema,is_insertable_into, table_type "
                                              "from information_schema.tables where table_schema!='information_schema' "
                                              "and table_schema!='sys'", &op);
    if (!status.ok()) {
        cout << "Failed to execute GetTables: " << status.GetMessage();
        op->Close();
        return;
    }
    unique_ptr<ColumnarRowSet> results;
    bool has_more_rows = true;
    while (has_more_rows) {
        Status s = op->Fetch(&results, &has_more_rows);
        if (!s.ok()) {
            cout << s.GetMessage();
            return;
        }

        std::vector <ColumnDesc> column_descs;
        s = op->GetResultSetMetadata(&column_descs);

        if (!s.ok()) {
            cout << s.GetMessage();
            return;
        } else if (column_descs.size() == 0) {
            cout << "No tables found";
            return;
        }

        unique_ptr<StringColumn> string_col = results->GetStringCol(0);
        for (int64_t i = 0; i < string_col->length(); ++i) {
            string name = results->GetStringCol(0)->GetData(i);
            string schema = results->GetStringCol(1)->GetData(i);
            bool insertable = results->GetBoolCol(2)->GetData(i);
            bool base_table = results->GetBoolCol(3)->GetData(i);

            tables.push_back(table(name, schema, insertable, base_table));
            cout << name << " " << schema << " " << noboolalpha << insertable << " " << noboolalpha << base_table
                 << endl;
        }
    }

    cerr << "Loading columns and constraints...";

    for (auto t = tables.begin(); t != tables.end(); ++t) {
        cout << endl << t->name <<":::::" <<endl;
        string query = "select column_name, data_type from information_schema.columns where table_name='" + t->name + "'";
        unique_ptr <Operation> op_column;

        Status s_op = session->ExecuteStatement(query, &op_column);
        if (!s_op.ok()) {
            cout << "Failed to execute GetColumns: " << s_op.GetMessage();
            op_column->Close();
            return;
        }
        has_more_rows = true;
        while (has_more_rows) {
            Status s = op_column->Fetch(&results, &has_more_rows);
            if (!s.ok()) {
                cout << s.GetMessage();
                return;
            }

            std::vector <ColumnDesc> column_descs;
            s = op_column->GetResultSetMetadata(&column_descs);

            if (!s.ok()) {
                cout << s.GetMessage();
                return;
            }

            unique_ptr<StringColumn> name_col = results->GetStringCol(0);

            for (int64_t i = 0; i < name_col->length(); ++i) {
                string name = results->GetStringCol(0)->GetData(i);
                string type = results->GetStringCol(1)->GetData(i);
                sqltype* stype = sqltype::get(type);
                cout<<"TYPE: " << stype->name<< endl;
                column c(name, stype);
                t->columns().push_back(c);
                cout << name << " " <<type<<endl;
            }
        }
    }
}

dut_hive::dut_hive(std::string &conninfo) : hive_connection(conninfo) {
    cout << "szia" << endl;
}

void dut_hive::test(const std::string &stmt) {
    /*MapiHdl hdl = mapi_query(dbh, "CALL sys.settimeout(1)");
    mapi_close_handle(hdl);
    hdl = mapi_query(dbh, stmt.c_str());

    if (mapi_error(dbh) != MOK) {

        try {
            const char *error_string = mapi_result_error(hdl);

            if (!error_string)
                error_string = "unknown error";

            const char *sqlstate = mapi_result_errorcode(hdl);
            if (!sqlstate)
                sqlstate = "XXXXX";

            *//* hive appears to report sqlstate 42000 for all
               errors, so we need to match the error string to
               figure out actual syntax errors *//*

            static regex re_syntax("^syntax error,.*", regex::extended);

            if (mapi_error(dbh) == MERROR)
                throw dut::syntax(error_string, sqlstate);
            else if (mapi_error(dbh) == MTIMEOUT)
                throw dut::timeout(error_string, sqlstate);
            else if (regex_match(error_string, re_syntax))
                throw dut::syntax(error_string, sqlstate);
            else
                throw dut::failure(error_string, sqlstate);

        } catch (dut::failure &e) {
            mapi_close_handle(hdl);
            throw;
        }
    }
    mapi_close_handle(hdl);*/
}
