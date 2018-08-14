﻿DROP TRIGGER "УдалитьПроводку"
  ON "проводки";

DELETE FROM проводки;

CREATE TRIGGER "УдалитьПроводку"
  BEFORE DELETE
  ON "проводки"
  FOR EACH ROW
  EXECUTE PROCEDURE "УдалитьПроводку"();

DELETE FROM сальдо;
DELETE FROM документы;
DELETE FROM докатрибуты1;
DELETE FROM докатрибуты71;
DELETE FROM докатрибуты123;
DELETE FROM атрибуты121;
DELETE FROM атрибуты123;
DELETE FROM атрибуты129;
DELETE FROM атрибуты5;
DELETE FROM атрибуты8;
DELETE FROM атрибуты71;
DELETE FROM атрибуты3;
DELETE FROM набор1;
DELETE FROM посладрес;
DELETE FROM адрес;
DELETE FROM бюджет;
DELETE FROM организации;
DELETE FROM банковские_счета;
DELETE FROM виды_расходов;
DELETE FROM заявка;
DELETE FROM прайс; --WHERE NOT (КОД_ФИРМЫ = 117 OR КОД_ФИРМЫ = 224);
DELETE FROM карточки;
DELETE FROM материалы;
DELETE FROM набор3;
DELETE FROM набор4;
DELETE FROM набор401;
DELETE FROM набор402;
DELETE FROM объекты;
DELETE FROM ос;
DELETE FROM персонал;
DELETE FROM предметы;
DELETE FROM журнал;
DELETE FROM фонды;
DELETE FROM last_price;
DELETE FROM банки;
DELETE FROM анализ_продаж;
DELETE FROM банкарты;
DELETE FROM журнал_изменений;
DELETE FROM журнал_прогнозов;
DELETE FROM история;
DELETE FROM товар;
DELETE FROM люди;
DELETE FROM фирмы; --WHERE NOT (КОД = 117 OR КОД = 224);
DELETE FROM города; --WHERE NOT (КОД = 3 OR КОД = 11);
DELETE FROM поисктовара;
DELETE FROM поисктоварадок;
DELETE FROM смс_отправленные;
DELETE FROM синонимы;
DELETE FROM доступ;
DELETE FROM товар;
DELETE FROM прайс;
DELETE FROM фирмы;
DELETE FROM наценки;
DELETE FROM группы;

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
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ) VALUES (1, TRUE, 'прайс', 'продавец');
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ) VALUES (1, TRUE, 'vw_прайс', 'sa');
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ) VALUES (1, TRUE, 'vw_прайс', 'продавец');
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ) VALUES (1, TRUE, 'файлы', 'sa');
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ) VALUES (1, TRUE, 'доступ', 'sa');
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ) VALUES (1, TRUE, 'топер', 'sa');
INSERT INTO доступ (КОД_ТИПЫОБЪЕКТОВ, МЕНЮ, ИМЯ, ИМЯ_ПОЛЬЗОВАТЕЛИ) VALUES (1, TRUE, 'константы', 'sa');
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
