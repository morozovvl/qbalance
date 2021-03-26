print "докатрибуты1";
DELETE FROM докатрибуты1;

print "докатрибуты71";
DELETE FROM докатрибуты71;

print "докатрибуты123";
DELETE FROM докатрибуты123;

print "докатрибуты78";
DELETE FROM докатрибуты78;

print "атрибуты121";
DELETE FROM атрибуты121;

print "атрибуты123";
DELETE FROM атрибуты123;

print "атрибуты129";
DELETE FROM атрибуты129;

print "атрибуты5";
DELETE FROM атрибуты5;

print "атрибуты8";
DELETE FROM атрибуты8;

print "атрибуты71";
DELETE FROM атрибуты71;

print "атрибуты3";
DELETE FROM атрибуты3;

print "блокдокументов";
DELETE FROM блокдокументов;

-------------
DROP TRIGGER "УдалитьПроводку" ON "проводки";
  
DROP TRIGGER "СчитатьИтогДокумента" ON "проводки";  

print "проводки";
DELETE FROM проводки;

CREATE TRIGGER "УдалитьПроводку"
  BEFORE DELETE
  ON "проводки"
  FOR EACH ROW
  EXECUTE PROCEDURE "УдалитьПроводку"();
  
CREATE CONSTRAINT TRIGGER "СчитатьИтогДокумента"
  AFTER INSERT OR UPDATE OR DELETE
  ON "проводки"
  FOR EACH ROW
  EXECUTE PROCEDURE calcdocitog();
  
ALTER SEQUENCE "проводки_КОД_seq" RESTART;

--------------
print "сальдо";
DELETE FROM сальдо;

--------------
DROP TRIGGER "УдалитьДокумент" 
ON public."документы";

DROP TRIGGER "ОбновитьДокумент" 
ON public."документы";

print "документы";
DELETE FROM документы;

CREATE TRIGGER "ОбновитьДокумент"
  BEFORE UPDATE OF "СУММА"
  ON public."документы"
  FOR EACH ROW
  EXECUTE PROCEDURE public."ОбновитьДокумент"();
  
CREATE TRIGGER "УдалитьДокумент"
  AFTER DELETE
  ON public."документы"
  FOR EACH ROW
  EXECUTE PROCEDURE public."УдалитьДокумент"();

ALTER SEQUENCE "документы_КОД_seq" RESTART;

---------------

DROP TRIGGER "testdeleting_товар" ON "товар";

print "товар";
DELETE FROM товар;

CREATE TRIGGER "testdeleting_товар"
  BEFORE DELETE
  ON "товар"
  FOR EACH ROW
  EXECUTE PROCEDURE testdeletingdictobject();

ALTER SEQUENCE "товар_КОД_seq" RESTART;
----------------

print "посладрес";
DELETE FROM посладрес;

----------------
DROP TRIGGER "testdeleting_адрес" ON "адрес";

print "адрес";
DELETE FROM адрес;

CREATE TRIGGER "testdeleting_адрес"
  BEFORE DELETE
  ON "адрес"
  FOR EACH ROW
  EXECUTE PROCEDURE testdeletingdictobject();

ALTER SEQUENCE "адрес_КОД_seq" RESTART;
----------------


print "бюджет";
DELETE FROM бюджет;

------------------------------
DROP TRIGGER "testdeleting_организации" ON "организации";

print "организации";
DELETE FROM организации;

CREATE TRIGGER "testdeleting_организации"
  BEFORE DELETE
  ON "организации"
  FOR EACH ROW
  EXECUTE PROCEDURE testdeletingdictobject();

ALTER SEQUENCE "организации_КОД_seq" RESTART;

------------------------------
DROP TRIGGER "testdeleting_банковские_счета" ON "банковские_счета";

print "банковские_счета";
DELETE FROM банковские_счета;

CREATE TRIGGER "testdeleting_банковские_счета"
  BEFORE DELETE
  ON "банковские_счета"
  FOR EACH ROW
  EXECUTE PROCEDURE testdeletingdictobject();

ALTER SEQUENCE "банковские_счета_КОД_seq" RESTART;

------------------------------
DROP TRIGGER "testdeleting_виды_расходов" ON "виды_расходов";

print "виды_расходов";
DELETE FROM виды_расходов;

CREATE TRIGGER "testdeleting_виды_расходов"
  BEFORE DELETE
  ON "виды_расходов"
  FOR EACH ROW
  EXECUTE PROCEDURE testdeletingdictobject();

ALTER SEQUENCE "виды_расходов_КОД_seq" RESTART;
------------------------------

print "заявка";
DELETE FROM заявка;

print "прайс";
DELETE FROM прайс WHERE NOT (КОД_ФИРМЫ = 117);

print "карточки";
DELETE FROM карточки;
ALTER SEQUENCE "карточки_КОД_seq" RESTART;

------------------------------
DROP TRIGGER "testdeleting_материалы" ON "материалы";

print "материалы";
DELETE FROM материалы;

CREATE TRIGGER "testdeleting_материалы"
  BEFORE DELETE
  ON "материалы"
  FOR EACH ROW
  EXECUTE PROCEDURE testdeletingdictobject();

ALTER SEQUENCE "материалы_КОД_seq" RESTART;

------------------------------
DROP TRIGGER "testdeleting_набор1" ON "набор1";

print "набор1";
DELETE FROM набор1;

CREATE TRIGGER "testdeleting_набор1"
  BEFORE DELETE
  ON "набор1"
  FOR EACH ROW
  EXECUTE PROCEDURE testdeletingdictobject();

ALTER SEQUENCE "набор1_КОД_seq" RESTART;
-------------------------------

DROP TRIGGER "testdeleting_набор3" ON "набор3";

print "набор3";
DELETE FROM набор3;

CREATE TRIGGER "testdeleting_набор3"
  BEFORE DELETE
  ON "набор3"
  FOR EACH ROW
  EXECUTE PROCEDURE testdeletingdictobject();

ALTER SEQUENCE "набор3_КОД_seq" RESTART;

------------------------------
DROP TRIGGER "testdeleting_набор4" ON "набор4";

print "набор4";
DELETE FROM набор4;

CREATE TRIGGER "testdeleting_набор4"
  BEFORE DELETE
  ON "набор4"
  FOR EACH ROW
  EXECUTE PROCEDURE testdeletingdictobject();

ALTER SEQUENCE "набор4_КОД_seq" RESTART;

------------------------------
DROP TRIGGER "testdeleting_набор401" ON "набор401";

print "набор401";
DELETE FROM набор401;

CREATE TRIGGER "testdeleting_набор401"
  BEFORE DELETE
  ON "набор401"
  FOR EACH ROW
  EXECUTE PROCEDURE testdeletingdictobject();

ALTER SEQUENCE "набор401_КОД_seq" RESTART;

------------------------------
DROP TRIGGER "testdeleting_набор402" ON "набор402";

print "набор402";
DELETE FROM набор402;

CREATE TRIGGER "testdeleting_набор402"
  BEFORE DELETE
  ON "набор402"
  FOR EACH ROW
  EXECUTE PROCEDURE testdeletingdictobject();

ALTER SEQUENCE "набор402_КОД_seq" RESTART;

------------------------------
DROP TRIGGER "testdeleting_объекты" ON "объекты";

print "объекты";
DELETE FROM объекты;

CREATE TRIGGER "testdeleting_объекты"
  BEFORE DELETE
  ON "объекты"
  FOR EACH ROW
  EXECUTE PROCEDURE testdeletingdictobject();

ALTER SEQUENCE "объекты_КОД_seq" RESTART;

------------------------------
DROP TRIGGER "testdeleting_ОС" ON "ос";

print "ос";
DELETE FROM ос;

CREATE TRIGGER "testdeleting_ОС"
  BEFORE DELETE
  ON "ос"
  FOR EACH ROW
  EXECUTE PROCEDURE testdeletingdictobject();

ALTER SEQUENCE "ос_КОД_seq" RESTART;

------------------------------
DROP TRIGGER "testdeleting_персонал" ON "персонал";

print "персонал";
DELETE FROM персонал;

CREATE TRIGGER "testdeleting_персонал"
  BEFORE DELETE
  ON "персонал"
  FOR EACH ROW
  EXECUTE PROCEDURE testdeletingdictobject();

ALTER SEQUENCE "персонал_КОД_seq" RESTART;

------------------------------
DROP TRIGGER "testdeleting_предметы" ON "предметы";

print "предметы";
DELETE FROM предметы;

CREATE TRIGGER "testdeleting_предметы"
  BEFORE DELETE
  ON "предметы"
  FOR EACH ROW
  EXECUTE PROCEDURE testdeletingdictobject();

ALTER SEQUENCE "предметы_КОД_seq" RESTART;
-------------------------------

print "журнал";
DELETE FROM журнал;

------------------------------
DROP TRIGGER "testdeleting_фонды" ON "фонды";

print "фонды";
DELETE FROM фонды;

CREATE TRIGGER "testdeleting_фонды"
  BEFORE DELETE
  ON "фонды"
  FOR EACH ROW
  EXECUTE PROCEDURE testdeletingdictobject();

ALTER SEQUENCE "фонды_КОД_seq" RESTART;
-------------------------------

print "last_price";
DELETE FROM last_price;

------------
DROP TRIGGER "testdeleting_банки" ON "банки";

print "банки";
DELETE FROM банки;

CREATE TRIGGER "testdeleting_банки"
  BEFORE DELETE
  ON "банки"
  FOR EACH ROW
  EXECUTE PROCEDURE testdeletingdictobject();

ALTER SEQUENCE "банки_КОД_seq" RESTART;
------------

print "анализ_продаж";
DELETE FROM анализ_продаж;

print "банкарты";
DELETE FROM банкарты;
ALTER SEQUENCE "банкарты_КОД_seq" RESTART;

print "журнал_изменений";
DELETE FROM журнал_изменений;

print "журнал_прогнозов";
DELETE FROM журнал_прогнозов;

print "история";
DELETE FROM история;

------------
DROP TRIGGER "testdeleting_люди" ON "люди";

print "люди";
DELETE FROM люди;

CREATE TRIGGER "testdeleting_люди"
  BEFORE DELETE
  ON "люди"
  FOR EACH ROW
  EXECUTE PROCEDURE testdeletingdictobject();

ALTER SEQUENCE "люди_КОД_seq" RESTART;

------------
DROP TRIGGER "testdeleting_фирмы" ON "фирмы";

print "фирмы";
DELETE FROM фирмы;

CREATE TRIGGER "testdeleting_фирмы"
  BEFORE DELETE
  ON "фирмы"
  FOR EACH ROW
  EXECUTE PROCEDURE testdeletingdictobject();

ALTER SEQUENCE "фирмы_КОД_seq" RESTART;

------------
DROP TRIGGER "testdeleting_города" ON "города";

print "города";
DELETE FROM города;

CREATE TRIGGER "testdeleting_города"
  BEFORE DELETE
  ON "города"
  FOR EACH ROW
  EXECUTE PROCEDURE testdeletingdictobject();

ALTER SEQUENCE "города_КОД_seq" RESTART;

print "поисктовара";
DELETE FROM поисктовара;

print "поисктоварадок";
DELETE FROM поисктоварадок;

print "смс_отправленные";
DELETE FROM смс_отправленные;

print "синонимы";
DELETE FROM синонимы;

print "доступ";
DELETE FROM доступ;

print "товар";
DELETE FROM товар;

UPDATE нумераторы SET ЗНАЧЕНИЕ = 0;



UPDATE константы SET ЗНАЧЕНИЕ = 'Индивидуальный предприниматель Иванов Иван Иванович' WHERE trim(ИМЯ) = 'ПолноеНазваниеФирмы';
UPDATE константы SET ЗНАЧЕНИЕ = 'ИП Иванов Иван Иванович' WHERE trim(ИМЯ) = 'НазваниеФирмы';
UPDATE константы SET ЗНАЧЕНИЕ = 'ИП Иванов И.И.' WHERE trim(ИМЯ) = 'КорНазваниеФирмы';
UPDATE константы SET ЗНАЧЕНИЕ = 'Иванов И.И.' WHERE trim(ИМЯ) = 'Руководитель';
UPDATE константы SET ЗНАЧЕНИЕ = 'Иванов И.И.' WHERE trim(ИМЯ) = 'Гл.бухгалтер';
UPDATE константы SET ЗНАЧЕНИЕ = '123456789012' WHERE trim(ИМЯ) = 'ИНН';
UPDATE константы SET ЗНАЧЕНИЕ = '123456, Центральная обл., г.Энск, ул.Зелёная, д.12, оф.24' WHERE trim(ИМЯ) = 'АдресФирмы';
UPDATE константы SET ЗНАЧЕНИЕ = 'Центральная обл., г.Энск' WHERE trim(ИМЯ) = 'ГородФирмы';
UPDATE константы SET ЗНАЧЕНИЕ = '9121234578' WHERE trim(ИМЯ) = 'ТелефонРуководителя';
UPDATE константы SET ЗНАЧЕНИЕ = '9121234578' WHERE trim(ИМЯ) = 'ТелефонДляСлужебныхСМС';
UPDATE константы SET ЗНАЧЕНИЕ = '40801234567890123456' WHERE trim(ИМЯ) = 'РасчетныйСчет';
UPDATE константы SET ЗНАЧЕНИЕ = '304123456789012 от 11.10.2004' WHERE trim(ИМЯ) = 'ОГРН';
UPDATE константы SET ЗНАЧЕНИЕ = 'Магазин "Запчасти", г.Энск, ул.Красная 17, тел.: 1-23-45' WHERE trim(ИМЯ) = 'НазваниеМагазина';
UPDATE константы SET ЗНАЧЕНИЕ = '' WHERE trim(ИМЯ) = 'НазваниеМагазина1';
UPDATE константы SET ЗНАЧЕНИЕ = '123456789' WHERE trim(ИМЯ) = 'КПП';
UPDATE константы SET ЗНАЧЕНИЕ = 'м-н "Запчасти"' WHERE trim(ИМЯ) = 'КорНазваниеМагазина';
UPDATE константы SET ЗНАЧЕНИЕ = '"00 № 001234567 от 11.08.11"' WHERE trim(ИМЯ) = 'СвидЕГРИП';
UPDATE константы SET ЗНАЧЕНИЕ = '' WHERE trim(ИМЯ) = 'СМС_URL';
UPDATE константы SET ЗНАЧЕНИЕ = '' WHERE trim(ИМЯ) = 'Телефоны';
UPDATE константы SET ЗНАЧЕНИЕ = '' WHERE trim(ИМЯ) = 'ОтправительСМС';
UPDATE константы SET ЗНАЧЕНИЕ = '        ИП Иванов И.И.' WHERE trim(ИМЯ) = 'ККМклише1';
UPDATE константы SET ЗНАЧЕНИЕ = 'Магазин "Запчасти", г.Энск' WHERE trim(ИМЯ) = 'ККМклише2';
UPDATE константы SET ЗНАЧЕНИЕ = 'ул.Красная 17, тел.: 1-23-45' WHERE trim(ИМЯ) = 'ККМклише3';
UPDATE константы SET ЗНАЧЕНИЕ = 'vk.com/ensk_avtozapzhasti' WHERE trim(ИМЯ) = 'ККМреклама2';



INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ) VALUES (1, TRUE, 'товар', 'sa');
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ) VALUES (1, TRUE, 'товар', 'продавец');
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ) VALUES (1, TRUE, 'адрес', 'sa');
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ) VALUES (1, TRUE, 'адрес', 'продавец');
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ) VALUES (1, TRUE, 'группы', 'sa');
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ) VALUES (1, TRUE, 'группы', 'продавец');
UPDATE справочники SET ИМЯ_В_ФОРМЕ = 'Группы' WHERE trim(ИМЯ) = 'группы';
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ, ТОЛЬКОЧТЕНИЕ) VALUES (1, TRUE, 'заявка', 'sa', false);
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ, ТОЛЬКОЧТЕНИЕ) VALUES (1, TRUE, 'заявка', 'продавец', false);
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ, ТОЛЬКОЧТЕНИЕ) VALUES (1, TRUE, 'прайс', 'sa', false);
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ, ТОЛЬКОЧТЕНИЕ) VALUES (1, TRUE, 'запросы', 'sa', false);
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ) VALUES (1, TRUE, 'прайс', 'продавец');
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ) VALUES (1, TRUE, 'vw_прайс', 'sa');
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ) VALUES (1, TRUE, 'vw_прайс', 'продавец');
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ) VALUES (1, TRUE, 'файлы', 'sa');
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ) VALUES (1, TRUE, 'доступ', 'sa');
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ) VALUES (1, TRUE, 'топер', 'sa');
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ) VALUES (1, TRUE, 'константы', 'sa');
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ) VALUES (1, TRUE, 'фирмы', 'sa');
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ) VALUES (1, TRUE, 'организации', 'sa');

INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ, ТОЛЬКОЧТЕНИЕ) VALUES (3, TRUE, '93', 'sa', false);
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ, ТОЛЬКОЧТЕНИЕ) VALUES (3, TRUE, '1', 'sa', false);
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ, ТОЛЬКОЧТЕНИЕ) VALUES (3, TRUE, '1', 'продавец', false);
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ, ТОЛЬКОЧТЕНИЕ) VALUES (3, TRUE, '123', 'sa', false);
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ, ТОЛЬКОЧТЕНИЕ) VALUES (3, TRUE, '124', 'sa', false);
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ, ТОЛЬКОЧТЕНИЕ) VALUES (3, TRUE, '124', 'продавец', false);
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ, ТОЛЬКОЧТЕНИЕ) VALUES (3, TRUE, '119', 'sa', false);
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ, ТОЛЬКОЧТЕНИЕ) VALUES (3, TRUE, '119', 'продавец', false);
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ, ТОЛЬКОЧТЕНИЕ) VALUES (3, TRUE, '3', 'sa', false);
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ, ТОЛЬКОЧТЕНИЕ) VALUES (3, TRUE, '3', 'продавец', false);
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ, ТОЛЬКОЧТЕНИЕ) VALUES (3, TRUE, '8', 'sa', false);

INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ, ТОЛЬКОЧТЕНИЕ) VALUES (4, TRUE, '60', 'sa', false);

DELETE FROM файлы WHERE ИМЯ = 'обработка.Пересчет цен от Бабицкого (сначала обновите прайс Паскер).js';
DELETE FROM файлы WHERE ИМЯ = 'обработка.Дешифровка фотографий Гала.js';
DELETE FROM файлы WHERE ИМЯ = 'обработка.Извлечение команд запросов из программы заказов Заречного.js';

INSERT INTO фирмы (ИМЯ, ФОТО_КАТАЛОГ) VALUES ('Паскер', 'паскер');
INSERT INTO фирмы (ИМЯ, ФОТО_КАТАЛОГ) VALUES ('НПН', 'нпн');

UPDATE прайс SET КОД_ФИРМЫ = 1 WHERE КОД_ФИРМЫ = 117;

DELETE FROM запросы WHERE trim(ИМЯ) = '**vw_изменение_цен1';
UPDATE запросы SET ИМЯ = trim(ИМЯ);
DELETE FROM запросы WHERE trim(ИМЯ) = 'vw_новыецены1';
DELETE FROM запросы WHERE trim(ИМЯ) = 'vw_новыецены2';
