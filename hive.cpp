//
// Created by Barnabas Maidics on 2019-08-05.
//

#include "hive.h"

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
    session->Close();
    service->Close();
}

//load schema from hive
schema_hive::schema_hive(std::string &conninfo) : hive_connection(conninfo) {
    unique_ptr <Operation> show_tables_op;
    Status status = session->ExecuteStatement("show tables", &show_tables_op);
    if (!status.ok()) {
        cout << "Failed to execute GetTables: " << status.GetMessage();
        show_tables_op->Close();
        return;
    }
    Util::PrintResults(show_tables_op.get(), cout);
    unique_ptr <ColumnarRowSet> showtables_results;
    bool has_more_rows = true;
    int total_retrieved = 0;
    cout << "Getting tables in given database\n";
    while (has_more_rows) {
        status = show_tables_op->Fetch(&showtables_results, &has_more_rows);
        if (!status.ok()) {
            cout << "Failed to fetch results: " << status.GetMessage();
            show_tables_op->Close();
            return;
        }
    }
    unique_ptr <StringColumn> string_col = showtables_results->GetStringCol(1);
    for (int64_t i = 0; i < string_col->length(); ++i) {
        if (string_col->IsNull(i)) {
            cout << "NULL";
        } else {
            cout << "'" << string_col->GetData(i) << "'";
        }
    }
    /*cerr << "init booltype, inttype, internaltype, arraytype here" << endl;
    booltype = sqltype::get("boolean");
    inttype = sqltype::get("int");
    internaltype = sqltype::get("internal");
    arraytype = sqltype::get("ARRAY");

    cerr << "Loading tables from database: " << conninfo << endl;
//	string qry = "select t.name, s.name, t.system, t.type from sys.tables t,  sys.schemas s where t.schema_id=s.id and t.system=false";
    string qry = "select t.name, s.name, t.system, t.type from sys.tables t,  sys.schemas s where t.schema_id=s.id ";
    MapiHdl hdl = mapi_query(dbh, qry.c_str());
    while (mapi_fetch_row(hdl)) {
        tables.push_back(table(mapi_fetch_field(hdl, 0), mapi_fetch_field(hdl, 1),
                               strcmp(mapi_fetch_field(hdl, 2), "false") == 0 ? true : false,
                               atoi(mapi_fetch_field(hdl, 3)) == 0 ? false : true));
    }
    mapi_close_handle(hdl);
    cerr << " done." << endl;

    cerr << "Loading columns and constraints...";
    for (auto t = tables.begin(); t != tables.end(); t++) {
        string q("select col.name,"
                 " col.type "
                 " from sys.columns col, sys.tables tab"
                 " where tab.name= '");
        q += t->name;
        q += "' and tab.id = col.table_id";

        hdl = mapi_query(dbh, q.c_str());
        while (mapi_fetch_row(hdl)) {
            column c(mapi_fetch_field(hdl, 0), sqltype::get(mapi_fetch_field(hdl, 1)));
            t->columns().push_back(c);
        }
        mapi_close_handle(hdl);
    }
    // TODO: confirm with Martin or Stefan about column
    // constraints in hive
    cerr << " done." << endl;

    cerr << "Loading operators...";
    string opq("select f.func, a.type, b.type, c.type"
               " from sys.functions f, sys.args a, sys.args b, sys.args c"
               "  where f.id=a.func_id and f.id=b.func_id and f.id=c.func_id and a.name='arg_1' and b.name='arg_2' and c.number=0");
    hdl = mapi_query(dbh, opq.c_str());
    while (mapi_fetch_row(hdl)) {
        op o(mapi_fetch_field(hdl, 0), sqltype::get(mapi_fetch_field(hdl, 1)),
             sqltype::get(mapi_fetch_field(hdl, 2)), sqltype::get(mapi_fetch_field(hdl, 3)));
        register_operator(o);
    }
    mapi_close_handle(hdl);
    cerr << " done." << endl;


    cerr << "Loading routines...";
    string routq(
            "select s.name, f.id, a.type, f.name from sys.schemas s, sys.args a, sys.types t, sys.functions f where f.schema_id = s.id and f.id=a.func_id and a.number=0 and a.type = t.sqlname and f.mod<>'aggr'");
    hdl = mapi_query(dbh, routq.c_str());
    while (mapi_fetch_row(hdl)) {
        routine proc(mapi_fetch_field(hdl, 0), mapi_fetch_field(hdl, 1), sqltype::get(mapi_fetch_field(hdl, 2)),
                     mapi_fetch_field(hdl, 3));
        register_routine(proc);
    }
    mapi_close_handle(hdl);
    cerr << " done." << endl;

    cerr << "Loading routine parameters...";
    for (auto &proc : routines) {
        string routpq("select a.type from sys.args a,"
                      " sys.functions f "
                      " where f.id = a.func_id and a.number <> 0 and f.id = '");
        routpq += proc.specific_name;
        routpq += "'";
        hdl = mapi_query(dbh, routpq.c_str());
        while (mapi_fetch_row(hdl)) {
            proc.argtypes.push_back(sqltype::get(mapi_fetch_field(hdl, 0)));
        }
        mapi_close_handle(hdl);
    }
    cerr << " done." << endl;


    cerr << "Loading aggregates...";
    string aggq(
            "select s.name, f.id, a.type, f.name from sys.schemas s, sys.args a, sys.types t, sys.functions f where f.schema_id = s.id and f.id=a.func_id and a.number=0 and a.type = t.sqlname and f.mod='aggr'");

    hdl = mapi_query(dbh, aggq.c_str());
    while (mapi_fetch_row(hdl)) {
        routine proc(mapi_fetch_field(hdl, 0), mapi_fetch_field(hdl, 1), sqltype::get(mapi_fetch_field(hdl, 2)),
                     mapi_fetch_field(hdl, 3));
        register_aggregate(proc);
    }
    mapi_close_handle(hdl);
    cerr << " done." << endl;

    cerr << "Loading aggregates parameters...";
    for (auto &proc: aggregates) {
        string aggpq("select a.type from sys.args a, sys.functions f "
                     "where f.id = a.func_id and a.number <> 0 and f.id = '");
        aggpq += proc.specific_name;
        aggpq += "'";
        hdl = mapi_query(dbh, aggpq.c_str());
        while (mapi_fetch_row(hdl)) {
            proc.argtypes.push_back(sqltype::get(mapi_fetch_field(hdl, 0)));
        }
        mapi_close_handle(hdl);
    }
    cerr << " done." << endl;

    mapi_destroy(dbh);
    generate_indexes();*/

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
