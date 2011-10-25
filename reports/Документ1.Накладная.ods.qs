reportContext.setValue("[документы.сумма_прописью]", SumToString(reportContext.getValue("[документы.сумма]")));
query = SqlQuery("SELECT * FROM номенклатура;");
query.exec();
query.first();
print(query.value(1));
/*
var query = SqlQuery("SELECT * FROM номенклатура;");
if (query.exec() < 0) {
    print(query.lastError());
}
else {
    print(query.size());
    query.first();
    print(query.value(1));
    }
*/    
//print(record.value(0));
scriptResult = false;


