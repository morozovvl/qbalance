reportContext.setValue("[документы.сумма_прописью]", SumToString(reportContext.getValue("[документы.сумма]")));
query = SqlQuery("SELECT * FROM номенклатура;");
query.exec();
query.first();
//print(query.value(1));
record = query.record();
//print(record.value("имя"));
//print(record.count());
//print(record.field("имя").fieldName());
field = record.field("имя");
for (i = 0; i < record.count(); i++) {
    print(record.fieldName(i));
}
scriptResult = false;


