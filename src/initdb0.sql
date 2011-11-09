DROP ROLE test;
CREATE ROLE test WITH NOSUPERUSER NOCREATEDB NOCREATEROLE LOGIN ENCRYPTED PASSWORD '*';
DROP ROLE sa;
CREATE ROLE sa WITH SUPERUSER CREATEDB CREATEROLE LOGIN ENCRYPTED PASSWORD '123456'; 
DROP ROLE bookkeeper;
CREATE ROLE bookkeeper WITH NOSUPERUSER NOCREATEDB NOCREATEROLE LOGIN ENCRYPTED PASSWORD '123';
DROP ROLE seller;
CREATE ROLE seller WITH NOSUPERUSER NOCREATEDB NOCREATEROLE LOGIN ENCRYPTED PASSWORD '123';

CREATE PROCEDURAL LANGUAGE plpgsql;

SET standard_conforming_strings = off;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET escape_string_warning = off;

CREATE TABLE счета (
    код INTEGER PRIMARY KEY,
    имя CHARACTER VARYING(200) DEFAULT ''::CHARACTER VARYING,
    счет CHARACTER(5) DEFAULT ''::bpchar,
    имясправочника CHARACTER VARYING(50) DEFAULT ''::CHARACTER VARYING,
    баланс BOOLEAN DEFAULT TRUE,
    количество BOOLEAN DEFAULT FALSE
);

CREATE SEQUENCE счета_код_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE счета_код_seq OWNED BY счета.код;


ALTER TABLE счета ALTER COLUMN код SET DEFAULT nextval('счета_код_seq'::regclass);

CREATE INDEX счета_имя_idx ON счета USING btree (имя);
CREATE INDEX счета_код_idx ON счета USING btree (код);


--------------------------------------------------------------------------------------------------------------------------------
CREATE TABLE сальдо (
    счет CHARACTER(5) NOT NULL,
    код INTEGER NOT NULL,
    кол NUMERIC(10,3) DEFAULT 0,
    сальдо NUMERIC(14,2) DEFAULT 0,
    дбкол NUMERIC(10,3) DEFAULT 0,
    дебет NUMERIC(14,2) DEFAULT 0,
    кркол NUMERIC(10,3) DEFAULT 0,
    кредит NUMERIC(14,2) DEFAULT 0,
    конкол NUMERIC(10,3) DEFAULT 0,
    консальдо NUMERIC(14,2) DEFAULT 0,
    концена NUMERIC(14,2) DEFAULT 0
);


CREATE INDEX сальдо_счет_код_idx ON сальдо USING btree (счет, код);


--------------------------------------------------------------------------------------------------------------------------------
CREATE TABLE документы (
    код INTEGER PRIMARY KEY,
    дата DATE,
    датавремя TIMESTAMP WITHOUT TIME ZONE,
    номер CHARACTER VARYING(10) DEFAULT ''::CHARACTER VARYING,
    комментарий CHARACTER VARYING(100) DEFAULT ''::CHARACTER VARYING,
    сумма NUMERIC(14,2) DEFAULT 0,
    описание TEXT,
    опер INTEGER,
    авто INTEGER,
    переменные BYTEA
);


CREATE SEQUENCE документы_код_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE документы_код_seq OWNED BY документы.код;


ALTER TABLE документы ALTER COLUMN код SET DEFAULT nextval('документы_код_seq'::regclass);


CREATE INDEX документы_авто_опер_дата_idx ON документы USING btree (авто, опер, дата);
CREATE INDEX документы_дата_idx ON документы USING btree (дата);
CREATE INDEX документы_дата_опер_авто_idx ON документы USING btree (дата, опер, авто);
CREATE INDEX документы_код_idx ON документы USING btree (код);


--------------------------------------------------------------------------------------------------------------------------------
CREATE TABLE проводки (
    код INTEGER PRIMARY KEY,
    дбсчет CHARACTER(5) NOT NULL,
    дбкод INTEGER NOT NULL,
    крсчет CHARACTER(5) NOT NULL,
    кркод INTEGER NOT NULL,
    кол NUMERIC(10,3) DEFAULT 0,
    цена NUMERIC(14,2) DEFAULT 0,
    сумма NUMERIC(14,2) DEFAULT 0,
    стр INTEGER NOT NULL,
    доккод INTEGER NOT NULL,
    опер NUMERIC(3,0) NOT NULL,
    номеропер NUMERIC(1,0) NOT NULL
);


CREATE SEQUENCE проводки_код_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE проводки_код_seq OWNED BY проводки.код;


ALTER TABLE проводки ALTER COLUMN код SET DEFAULT nextval('проводки_код_seq'::regclass);


CREATE INDEX проводки_дбкод_idx ON проводки USING btree (дбсчет, дбкод, доккод);
CREATE INDEX проводки_дбсчет_опер_idx ON проводки USING btree (дбсчет, опер);
CREATE INDEX проводки_доккод_idx ON проводки USING btree (доккод);
CREATE INDEX проводки_доккод_опер_idx ON проводки USING btree (доккод, опер, номеропер);
CREATE INDEX проводки_доккод_стр_idx ON проводки USING btree (доккод, стр);
CREATE INDEX проводки_код_idx ON проводки USING btree (код);
CREATE INDEX проводки_кркод_idx ON проводки USING btree (крсчет, кркод, доккод);
CREATE INDEX проводки_крсчет_опер_idx ON проводки USING btree (крсчет, опер);
CREATE INDEX проводки_опер_номеропер_idx ON проводки USING btree (опер, номеропер);


--------------------------------------------------------------------------------------------------------------------------------
CREATE TABLE константы (
    код INTEGER PRIMARY KEY,
    имя CHARACTER VARYING(100) DEFAULT ''::CHARACTER VARYING,
    значение CHARACTER VARYING(200) DEFAULT ''::CHARACTER VARYING,
    комментарий CHARACTER VARYING(100)
);


CREATE SEQUENCE константы_код_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE константы_код_seq OWNED BY константы.код;


ALTER TABLE константы ALTER COLUMN код SET DEFAULT nextval('константы_код_seq'::regclass);


CREATE INDEX константы_имя_idx ON константы USING btree (имя);
CREATE INDEX константы_код_idx ON константы USING btree (код);

--------------------------------------------------------------------------------------------------------------------------------
CREATE TABLE топер (
    код INTEGER PRIMARY KEY,
    опер INTEGER,
    номер INTEGER,
    дбсчет CHARACTER VARYING(5) DEFAULT ''::CHARACTER VARYING,
    крсчет CHARACTER VARYING(5) DEFAULT ''::CHARACTER VARYING,
    имя CHARACTER VARYING(100) DEFAULT ''::CHARACTER VARYING,
    итоги CHARACTER VARYING(1) DEFAULT ''::CHARACTER VARYING,
    меню BOOLEAN DEFAULT FALSE,
    осндокумент CHARACTER VARYING(20) DEFAULT ''::CHARACTER VARYING,
    нумератор CHARACTER VARYING(40) DEFAULT ''::CHARACTER VARYING,
    однаоперация BOOLEAN,
    кол BOOLEAN DEFAULT FALSE,
    дбпост BOOLEAN DEFAULT FALSE,
    крпост BOOLEAN DEFAULT FALSE,
    дбдобав BOOLEAN DEFAULT FALSE,
    крдобав BOOLEAN DEFAULT FALSE,
    дбвыбор BOOLEAN DEFAULT FALSE,
    крвыбор BOOLEAN DEFAULT FALSE,
    дбсалвидим BOOLEAN DEFAULT TRUE,
    крсалвидим BOOLEAN DEFAULT TRUE,
    дбвидим BOOLEAN DEFAULT TRUE,
    крвидим BOOLEAN DEFAULT TRUE,
    форма CHARACTER VARYING(50) DEFAULT ''::CHARACTER VARYING,
    независим BOOLEAN DEFAULT FALSE,
    считать BOOLEAN DEFAULT TRUE, 
    переменные TEXT
);


CREATE SEQUENCE топер_код_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE топер_код_seq OWNED BY топер.код;


ALTER TABLE топер ALTER COLUMN код SET DEFAULT nextval('топер_код_seq'::regclass);


-------------------------------------------------------------------------------------------------------------------------------
CREATE TABLE банки (
    код INTEGER PRIMARY KEY,
    имя CHARACTER VARYING(100) DEFAULT ''::CHARACTER VARYING,
    бик CHARACTER VARYING(9) DEFAULT ''::CHARACTER VARYING,
    корсчет CHARACTER VARYING(9) DEFAULT ''::CHARACTER VARYING,
    счет CHARACTER VARYING(20) DEFAULT ''::CHARACTER VARYING
);


CREATE SEQUENCE банки_код_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE банки_код_seq OWNED BY банки.код;


ALTER TABLE банки ALTER COLUMN код SET DEFAULT nextval('банки_код_seq'::regclass);


CREATE INDEX банки_имя_idx ON банки USING btree (имя);
CREATE INDEX банки_код_idx ON банки USING btree (код);


--------------------------------------------------------------------------------------------------------------------------------
CREATE TABLE банковские_счета (
    код INTEGER PRIMARY KEY,
    имя CHARACTER VARYING(100) DEFAULT ''::CHARACTER VARYING,
    счет CHARACTER VARYING(20) DEFAULT ''::CHARACTER VARYING,
    код_банки INTEGER
);


CREATE SEQUENCE банковские_счета_код_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE банковские_счета_код_seq OWNED BY банковские_счета.код;


ALTER TABLE банковские_счета ALTER COLUMN код SET DEFAULT nextval('банковские_счета_код_seq'::regclass);


CREATE INDEX банковские_счета_имя_idx ON банковские_счета USING btree (имя);
CREATE INDEX банковские_счета_код_idx ON банковские_счета USING btree (код);


--------------------------------------------------------------------------------------------------------------------------------
CREATE TABLE контрагенты (
    код INTEGER PRIMARY KEY,
    имя CHARACTER VARYING(200) DEFAULT ''::CHARACTER VARYING,
    адрес CHARACTER VARYING(100) DEFAULT ''::CHARACTER VARYING,
    телефон CHARACTER VARYING(100) DEFAULT ''::CHARACTER VARYING,
	e_mail CHARACTER VARYING(50) DEFAULT ''::CHARACTER VARYING,
	руководитель CHARACTER VARYING(50) DEFAULT ''::CHARACTER VARYING,
	гл_бухгалтер CHARACTER VARYING(50) DEFAULT ''::CHARACTER VARYING,
    инн CHARACTER VARYING(12) DEFAULT ''::CHARACTER VARYING,
    кпп CHARACTER VARYING(9) DEFAULT ''::CHARACTER VARYING,
    оконх CHARACTER VARYING(15) DEFAULT ''::CHARACTER VARYING,
    окпо CHARACTER VARYING(10) DEFAULT ''::CHARACTER VARYING,
    счет CHARACTER VARYING(20) DEFAULT ''::CHARACTER VARYING,
    код_банки INTEGER,
    лимит NUMERIC(14,2) DEFAULT 0,
    код_vw_грузополучатели INTEGER
);


CREATE SEQUENCE контрагенты_код_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE контрагенты_код_seq OWNED BY контрагенты.код;


ALTER TABLE контрагенты ALTER COLUMN код SET DEFAULT nextval('контрагенты_код_seq'::regclass);

CREATE INDEX контрагенты_имя_idx ON контрагенты USING btree (имя);
CREATE INDEX контрагенты_код_idx ON контрагенты USING btree (код);


--------------------------------------------------------------------------------------------------------------------------------
CREATE TABLE материалы (
    код INTEGER PRIMARY KEY,
    имя CHARACTER VARYING(100) DEFAULT ''::CHARACTER VARYING,
    едизм CHARACTER VARYING(5) DEFAULT ''::CHARACTER VARYING
);


CREATE SEQUENCE материалы_код_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER SEQUENCE материалы_код_seq OWNED BY материалы.код;


ALTER TABLE материалы ALTER COLUMN код SET DEFAULT nextval('материалы_код_seq'::regclass);


CREATE INDEX материалы_имя_idx ON материалы USING btree (имя);
CREATE INDEX материалы_код_idx ON материалы USING btree (код);


--------------------------------------------------------------------------------------------------------------------------------
CREATE TABLE номенклатура (
    код INTEGER NOT NULL,
    имя CHARACTER VARYING(100) DEFAULT ''::CHARACTER VARYING,
    едизм CHARACTER VARYING(10) DEFAULT ''::CHARACTER VARYING,
    артикул CHARACTER VARYING(25) DEFAULT ''::CHARACTER VARYING,
    код_группы INTEGER,
    цена_розн NUMERIC(10, 2) DEFAULT 0,
    запас NUMERIC(5,0) DEFAULT 0,
    имя_на_ценнике CHARACTER VARYING(80) DEFAULT ''::CHARACTER VARYING,
    тип_ценника INTEGER DEFAULT 3,
    fts TSVECTOR, 
    CONSTRAINT номенклатура_pkey PRIMARY KEY (код)
);

CREATE SEQUENCE номенклатура_код_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER SEQUENCE номенклатура_код_seq OWNED BY номенклатура.код;
ALTER TABLE номенклатура ALTER COLUMN код SET DEFAULT nextval('номенклатура_код_seq'::regclass);
CREATE INDEX номенклатура_код_idx ON номенклатура USING btree (код);
CREATE INDEX номенклатура_имя_idx ON номенклатура USING btree (имя);


--------------------------------------------------------------------------------------------------------------------------------
CREATE TABLE группы (
    код INTEGER NOT NULL,
    имя CHARACTER VARYING(100) DEFAULT ''::CHARACTER VARYING,
    цены_снижать BOOLEAN DEFAULT FALSE,
    CONSTRAINT группы_pkey PRIMARY KEY (код)
);

CREATE SEQUENCE группы_код_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE группы_код_seq OWNED BY группы.код;
ALTER TABLE группы ALTER COLUMN код SET DEFAULT nextval('группы_код_seq'::regclass);
CREATE INDEX группы_имя_idx ON группы USING btree (имя);
CREATE INDEX группы_код_idx ON группы USING btree (код);

--------------------------------------------------------------------------------------------------------------------------------
CREATE TABLE персонал (
    код INTEGER PRIMARY KEY,
    имя CHARACTER VARYING(50) DEFAULT ''::CHARACTER VARYING,
    инн CHARACTER VARYING(12) DEFAULT ''::CHARACTER VARYING,
    паспорт_серия CHARACTER VARYING(7) DEFAULT ''::CHARACTER VARYING,
    паспорт_номер CHARACTER VARYING(6) DEFAULT ''::CHARACTER VARYING,
    паспорт_выдан CHARACTER VARYING(50) DEFAULT ''::CHARACTER VARYING,
    паспорт_дата DATE,
    адрес CHARACTER VARYING(50) DEFAULT ''::CHARACTER VARYING,
    день_рождения DATE,
    работает BOOLEAN,
    медстрах CHARACTER VARYING(14) DEFAULT ''::CHARACTER VARYING
);


CREATE SEQUENCE персонал_код_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE персонал_код_seq OWNED BY персонал.код;


ALTER TABLE персонал ALTER COLUMN код SET DEFAULT nextval('персонал_код_seq'::regclass);


CREATE INDEX персонал_имя_idx ON персонал USING btree (имя);
CREATE INDEX персонал_код_idx ON персонал USING btree (код);


--------------------------------------------------------------------------------------------------------------------------------
CREATE TABLE предметы (
    код INTEGER PRIMARY KEY,
    имя CHARACTER VARYING(100) DEFAULT ''::CHARACTER VARYING,
    едизм CHARACTER VARYING(6) DEFAULT ''::CHARACTER VARYING
);


CREATE SEQUENCE предметы_код_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE предметы_код_seq OWNED BY предметы.код;


ALTER TABLE предметы ALTER COLUMN код SET DEFAULT nextval('предметы_код_seq'::regclass);


CREATE INDEX предметы_имя_idx ON предметы USING btree (имя);
CREATE INDEX предметы_код_idx ON предметы USING btree (код);


--------------------------------------------------------------------------------------------------------------------------------
CREATE TABLE виды_расходов (
    код INTEGER PRIMARY KEY,
    имя CHARACTER VARYING(100) DEFAULT ''::CHARACTER VARYING
);


CREATE SEQUENCE виды_расходов_код_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE виды_расходов_код_seq OWNED BY виды_расходов.код;


ALTER TABLE виды_расходов ALTER COLUMN код SET DEFAULT nextval('виды_расходов_код_seq'::regclass);


CREATE INDEX виды_расходов_имя_idx ON виды_расходов USING btree (имя);
CREATE INDEX виды_расходов_код_idx ON виды_расходов USING btree (код);


--------------------------------------------------------------------------------------------------------------------------------
CREATE TABLE нумераторы (
    код INTEGER PRIMARY KEY,
    имя CHARACTER VARYING(100) DEFAULT ''::CHARACTER VARYING,
    значение INTEGER DEFAULT 0
);


CREATE SEQUENCE нумераторы_код_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE нумераторы_код_seq OWNED BY нумераторы.код;


ALTER TABLE нумераторы ALTER COLUMN код SET DEFAULT nextval('нумераторы_код_seq'::regclass);


CREATE INDEX нумераторы_имя_idx ON нумераторы USING btree (имя);
CREATE INDEX нумераторы_код_idx ON нумераторы USING btree (код);


--------------------------------------------------------------------------------------------------------------------------------
CREATE TABLE блокпериоды (
    код INTEGER PRIMARY KEY,
    имя CHARACTER VARYING(100) DEFAULT ''::CHARACTER VARYING,
    блокконец DATE,
    начало DATE NOT NULL DEFAULT ('now'::text)::date - 30,
    конец DATE NOT NULL DEFAULT ('now'::text)::date,
    пользователь CHARACTER VARYING(30) DEFAULT "current_user"()
);


CREATE SEQUENCE блокпериоды_код_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE блокпериоды_код_seq OWNED BY блокпериоды.код;


ALTER TABLE блокпериоды ALTER COLUMN код SET DEFAULT nextval('блокпериоды_код_seq'::regclass);


CREATE INDEX блокпериоды_имя_idx ON блокпериоды USING btree (имя);
CREATE INDEX блокпериоды_код_idx ON блокпериоды USING btree (код);


--------------------------------------------------------------------------------------------------------------------------------
CREATE TABLE доступ (
    код INTEGER PRIMARY KEY,
    меню BOOLEAN DEFAULT TRUE,
    комментарий CHARACTER VARYING(100) DEFAULT ''::CHARACTER VARYING,
    код_типыобъектов INTEGER,
    пользователь CHARACTER VARYING(30) DEFAULT ''::CHARACTER VARYING,
    имя CHARACTER VARYING(100) DEFAULT ''::CHARACTER VARYING,
    доступ CHARACTER VARYING(30) DEFAULT ''::CHARACTER VARYING
);


CREATE SEQUENCE доступ_код_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE доступ_код_seq OWNED BY доступ.код;


ALTER TABLE доступ ALTER COLUMN код SET DEFAULT nextval('доступ_код_seq'::regclass);


CREATE INDEX доступ_имя_idx ON доступ USING btree (имя);
CREATE INDEX доступ_код_idx ON доступ USING btree (код);


--------------------------------------------------------------------------------------------------------------------------------
CREATE TABLE журнал (
    код INTEGER PRIMARY KEY,
    имя CHARACTER VARYING(20) DEFAULT ''::CHARACTER VARYING,
    датавремя TIMESTAMP WITHOUT TIME ZONE,
    содержание CHARACTER VARYING(200) DEFAULT ''::CHARACTER VARYING,
    код_номенклатура INTEGER,
    дата DATE
);


CREATE SEQUENCE журнал_код_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE журнал_код_seq OWNED BY журнал.код;


ALTER TABLE журнал ALTER COLUMN код SET DEFAULT nextval('журнал_код_seq'::regclass);


--------------------------------------------------------------------------------------------------------------------------------
CREATE TABLE справочники (
    код INTEGER PRIMARY KEY,
    имя CHARACTER VARYING(100) DEFAULT ''::CHARACTER VARYING,
    имя_в_списке CHARACTER VARYING(100) DEFAULT ''::CHARACTER VARYING,
    имя_в_форме CHARACTER VARYING(100) DEFAULT ''::CHARACTER VARYING,
    форма CHARACTER VARYING(50) DEFAULT ''::CHARACTER VARYING,
    преформулы TEXT, 
    формулы TEXT, 
    постформулы TEXT,
    фото CHARACTER VARYING(100) DEFAULT ''::CHARACTER VARYING
);


CREATE SEQUENCE справочники_код_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE справочники_код_seq OWNED BY справочники.код;


ALTER TABLE справочники ALTER COLUMN код SET DEFAULT nextval('справочники_код_seq'::regclass);


--------------------------------------------------------------------------------------------------------------------------------
CREATE TABLE типыобъектов (
    код INTEGER PRIMARY KEY,
    имя CHARACTER VARYING(20) DEFAULT ''::CHARACTER VARYING
);

CREATE SEQUENCE типыобъектов_код_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE типыобъектов_код_seq OWNED BY типыобъектов.код;

ALTER TABLE типыобъектов ALTER COLUMN код SET DEFAULT nextval('типыобъектов_код_seq'::regclass);

CREATE INDEX типыобъектов_имя_idx ON типыобъектов USING btree (имя);
CREATE INDEX типыобъектов_код_idx ON типыобъектов USING btree (код);


--------------------------------------------------------------------------------------------------------------------------------
CREATE TABLE справочник (
    код INTEGER PRIMARY KEY,
    имя CHARACTER VARYING(100) DEFAULT ''::CHARACTER VARYING
);

CREATE SEQUENCE справочник_код_seq
    start WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;

ALTER SEQUENCE справочник_код_seq OWNED BY справочник.код;

ALTER TABLE справочник ALTER COLUMN код SET DEFAULT nextval('справочник_код_seq'::regclass);


--------------------------------------------------------------------------------------------------------------------------------
CREATE TABLE столбцы (
    код INTEGER PRIMARY KEY,
    код_vw_справочники_со_столбцами INTEGER,
    имя CHARACTER VARYING(100) DEFAULT ''::CHARACTER VARYING,
    заголовок CHARACTER VARYING(100) DEFAULT ''::CHARACTER VARYING, 
    номер NUMERIC(3)
);

CREATE SEQUENCE столбцы_код_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;
	
ALTER SEQUENCE столбцы_код_seq OWNED BY столбцы.код;

ALTER TABLE столбцы ALTER COLUMN код SET DEFAULT nextval('столбцы_код_seq'::regclass);


--------------------------------------------------------------------------------------------------------------------------------
CREATE TABLE файлы (
  код serial NOT NULL,
  имя CHARACTER VARYING(100) DEFAULT ''::CHARACTER VARYING,
  тип INTEGER,
  значение bytea,
  CONSTRAINT файлы_pkey PRIMARY KEY ("код")
)
WITH (
  OIDS=FALSE
);

--------------------------------------------------------------------------------------------------------------------------------
CREATE TABLE прайсы (
    код INTEGER PRIMARY KEY,
    имя CHARACTER VARYING(100) DEFAULT ''::CHARACTER VARYING,
    код_фирмы INTEGER,
    кодвпрайсе CHARACTER VARYING (50) DEFAULT ''::CHARACTER VARYING,
    артикул CHARACTER VARYING (20) DEFAULT ''::CHARACTER VARYING,
    едизм CHARACTER VARYING (10) DEFAULT ''::CHARACTER VARYING,
    дата DATE,
    цена NUMERIC (10, 2) DEFAULT 0,
    упаковка INTEGER,
    наличие CHARACTER (1) DEFAULT '+'::CHARACTER,
    код_товар INTEGER,
    кол_прайс NUMERIC(8,3) DEFAULT 1,
    кол_товар NUMERIC(8,3) DEFAULT 1,
    приоритет INTEGER DEFAULT 1,
    fts TSVECTOR
);

CREATE SEQUENCE прайсы_код_seq
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;
	
ALTER SEQUENCE прайсы_код_seq OWNED BY прайсы.код;

ALTER TABLE прайсы ALTER COLUMN код SET DEFAULT nextval('прайсы_код_seq'::regclass);

CREATE INDEX "прайсы_fts_idx" ON "прайсы" USING gin(fts);
CREATE INDEX "прайсы_имя_idx" ON "прайсы" USING btree("имя" varchar_pattern_ops);
CREATE INDEX "прайсы_код_idx" ON "прайсы" USING btree("код");
CREATE INDEX "прайсы_код_товар" ON "прайсы" USING btree("код_товар");
CREATE INDEX "прайсы_код_товар_код_фирмы" ON "прайсы" USING btree("код_товар", "код_фирмы");
CREATE INDEX "прайсы_код_фирмы_idx" ON "прайсы" USING btree("код_фирмы");
CREATE INDEX "прайсы_код_фирмы_имя" ON "прайсы" USING btree("код_фирмы", "имя");
CREATE INDEX "прайсы_код_фирмы_кодвпрайсе" ON "прайсы" USING btree("код_фирмы", "кодвпрайсе");
CREATE INDEX "прайсы_кодвпрайсе" ON "прайсы" USING btree("кодвпрайсе");


--------------------------------------------------------------------------------------------------------------------------------
CREATE VIEW vw_tables AS 
SELECT tablename as name, 'table' AS type FROM pg_catalog.pg_tables
UNION
SELECT viewname as name, 'view' AS type FROM pg_catalog.pg_views;

--------------------------------------------------------------------------------------------------------------------------------
CREATE VIEW vw_справочники_со_столбцами AS
SELECT s.код, s.имя
FROM справочники s
UNION
SELECT 1000000 + опер AS код, 'СписокДокументов' || trim(cast(опер AS varchar(20))) AS имя 
FROM топер 
WHERE номер = 1
UNION 
SELECT 2000000 + опер AS код, 'Документ' || trim(cast(опер AS varchar(20))) AS имя 
FROM топер 
WHERE номер = 1;


--------------------------------------------------------------------------------------------------------------------------------
CREATE VIEW vw_столбцы AS
SELECT d.имя AS справочник, s.имя AS столбец, s.заголовок, s.номер
FROM столбцы s INNER JOIN vw_справочники_со_столбцами d ON s.код_vw_справочники_со_столбцами = d.код
ORDER BY справочник, номер;


--------------------------------------------------------------------------------------------------------------------------------
CREATE VIEW vw_пользователи AS
    SELECT pg_user.usesysid AS код, pg_user.usename AS имя FROM pg_user WHERE pg_user.usename <> 'test' AND pg_user.usename <> 'postgres' ;


--------------------------------------------------------------------------------------------------------------------------------
CREATE VIEW vw_блокпериоды AS
    SELECT b.код, b.имя, b.блокконец, b.начало, b.конец 
    FROM блокпериоды b
    WHERE lower(trim(пользователь)) = lower(current_user);


--------------------------------------------------------------------------------------------------------------------------------
CREATE VIEW vw_константы AS
    SELECT * 
    FROM константы;


--------------------------------------------------------------------------------------------------------------------------------
CREATE VIEW vw_документы AS
    SELECT d.код, d.дата, d.датавремя, d.номер, d.комментарий, d.сумма, d.опер, d.авто, d.описание 
    FROM документы d JOIN vw_блокпериоды b ON (d.дата > (b.начало - 1)) AND (d.дата < (b.конец + 1));


-------------------------------------------------------------------------------------------------------------------------------
CREATE VIEW vw_баланс AS
    SELECT DISTINCT счета.код, счета.счет, счета.имя, COALESCE(дбсальдо.дбконсальдо, (0)::NUMERIC) AS дбконсальдо, COALESCE(крсальдо.крконсальдо, (0)::NUMERIC) AS крконсальдо FROM ((счета LEFT JOIN (SELECT DISTINCT сальдо.счет, sum(сальдо.консальдо) AS дбконсальдо FROM сальдо WHERE ((сальдо.консальдо > (0)::NUMERIC) AND (substr((сальдо.счет)::TEXT, 1, 2) <> '00'::TEXT)) GROUP BY сальдо.счет ORDER BY сальдо.счет, sum(сальдо.консальдо)) дбсальдо ON ((счета.счет = дбсальдо.счет))) LEFT JOIN (SELECT DISTINCT сальдо.счет, (- sum(сальдо.консальдо)) AS крконсальдо FROM сальдо WHERE ((сальдо.консальдо < (0)::NUMERIC) AND (substr((сальдо.счет)::TEXT, 1, 2) <> '00'::TEXT)) GROUP BY сальдо.счет ORDER BY сальдо.счет, (- sum(сальдо.консальдо))) крсальдо ON ((счета.счет = крсальдо.счет))) ORDER BY счета.код, счета.счет, счета.имя, COALESCE(дбсальдо.дбконсальдо, (0)::NUMERIC), COALESCE(крсальдо.крконсальдо, (0)::NUMERIC);


--------------------------------------------------------------------------------------------------------------------------------
CREATE VIEW vw_проводки AS
    SELECT проводки.код, проводки.дбсчет, проводки.дбкод, проводки.крсчет, проводки.кркод, проводки.кол, проводки.цена, проводки.сумма, проводки.стр, проводки.доккод, проводки.опер, проводки.номеропер 
	FROM проводки 
	WHERE проводки.доккод in (SELECT vw_документы.код 
								  FROM vw_документы);

--------------------------------------------------------------------------------------------------------------------------------
CREATE VIEW vw_топер AS
 SELECT топер.код, топер.опер, топер.номер, топер.имя, счета.счет AS дбсчет, счета.имясправочника AS дбсправ, '                                        '::bpchar AS дбсправалиас, счета.количество AS дбкол, топер.дбпост, топер.дбсалвидим, топер.дбвидим, счета1.счет AS крсчет, счета1.имясправочника AS крсправ, '                                        '::bpchar AS крсправалиас, счета1.количество AS кркол, топер.однаоперация, топер.итоги, топер.крпост, топер.крсалвидим, топер.крвидим, топер.независим, топер.считать, топер.переменные
   FROM топер
   LEFT JOIN счета счета ON топер.дбсчет::bpchar = счета.счет
   LEFT JOIN счета счета1 ON топер.крсчет::bpchar = счета1.счет;

--------------------------------------------------------------------------------------------------------------------------------
CREATE VIEW vw_грузополучатели AS
    SELECT * FROM контрагенты;


--------------------------------------------------------------------------------------------------------------------------------
CREATE VIEW vw_доступ AS 
SELECT s.имя, s.код_типыобъектов, s.меню, has_table_privilege(s.имя, 'select'::text) AS selectable, 
	CASE 
		WHEN s.type = 'table' THEN has_table_privilege(s.имя, 'insert'::text)
		ELSE false
	END AS insertable, 
	CASE
		WHEN s.type = 'table' THEN has_table_privilege(s.имя, 'delete'::text)
		ELSE false
	END AS deleteable, 
	CASE 
		WHEN s.type = 'table' THEN has_table_privilege(s.имя, 'update'::text)
		ELSE false
	END AS updateable
   FROM ( SELECT DISTINCT s.имя, s.код_типыобъектов, s.меню, s.type
           FROM ( SELECT rtrim(d.имя::text) AS имя, d.код_типыобъектов, d.меню, t.type
                   FROM доступ d
              JOIN vw_пользователи p ON rtrim(d.пользователь::text) = rtrim(p.имя::text)
         JOIN vw_tables t ON rtrim(d.имя::text) = rtrim(t.name::text)
        WHERE upper(rtrim(p.имя::text)) = upper(rtrim(current_user::text)) OR btrim(current_user::text) = 'sa'::text) s
          ORDER BY s.имя, s.код_типыобъектов, s.меню) s
UNION
SELECT 'проводки' AS имя, 1 AS код_типыобъектов, false AS меню, has_table_privilege('проводки', 'select'::text) AS selectable, 
       has_table_privilege('проводки', 'insert'::text) AS insertable, 
       has_table_privilege('проводки', 'delete'::text) AS deleteable, 
       has_table_privilege('проводки', 'update'::text) AS updateable
UNION 
 SELECT rtrim(d.имя::text) AS имя, d.код_типыобъектов, d.меню, true AS selectable, true AS insertable, true AS deleteable, true AS updateable
   FROM доступ d
   JOIN vw_пользователи p ON rtrim(d.пользователь::text) = rtrim(p.имя::text) AND d.код_типыобъектов <> 1
  WHERE upper(rtrim(p.имя::text)) = upper(rtrim(current_user::text)) OR btrim(current_user::text) = 'sa'::text;


--------------------------------------------------------------------------------------------------------------------------------
CREATE VIEW vw_доступ_к_оборотам AS
    SELECT DISTINCT счета.имя, счета.счет 
    FROM (счета LEFT JOIN vw_доступ ON (((счета.счет)::TEXT = vw_доступ.имя))) 
    WHERE (vw_доступ.код_типыобъектов = 4) 
    ORDER BY счета.имя, счета.счет;

--------------------------------------------------------------------------------------------------------------------------------
CREATE VIEW vw_доступ_к_сальдо AS
    SELECT DISTINCT счета.имя, счета.счет 
    FROM (счета JOIN vw_доступ ON ((rtrim((счета.счет)::TEXT) = rtrim(vw_доступ.имя)))) 
    WHERE (vw_доступ.код_типыобъектов = 2) 
    ORDER BY счета.имя, счета.счет;


--------------------------------------------------------------------------------------------------------------------------------
CREATE VIEW vw_доступ_к_справочникам AS
	SELECT s.имя_в_списке AS имя, s.имя_в_форме, d.имя AS таблица, d.меню, d.selectable, d.insertable, d.deleteable, d.updateable
	FROM vw_доступ d LEFT OUTER JOIN справочники s ON upper(rtrim(d.имя)) = upper(rtrim(s.имя))
	WHERE d.код_типыобъектов = 1
	ORDER BY s.имя_в_списке;

--------------------------------------------------------------------------------------------------------------------------------
CREATE VIEW vw_доступ_к_топер AS 
 SELECT DISTINCT топер.имя, топер.меню, топер.опер, топер.форма, топер.независим, s.selectable, s.insertable, s.deleteable, s.updateable
   FROM топер
   JOIN ( SELECT vw_доступ.имя, vw_доступ.код_типыобъектов, vw_доступ.меню, vw_доступ.selectable, vw_доступ.insertable, vw_доступ.deleteable, vw_доступ.updateable
           FROM vw_доступ
          WHERE vw_доступ.код_типыобъектов = 3) s ON rtrim(топер.опер::text) = rtrim(s.имя)
  WHERE топер.номер = 1 AND топер.меню = true
  ORDER BY топер.имя, топер.меню, топер.опер, топер.форма, топер.независим;

--------------------------------------------------------------------------------------------------------------------------------
CREATE VIEW vw_журнал AS
    SELECT журнал.код, журнал.содержание AS имя, журнал.дата, журнал.код_номенклатура FROM журнал ORDER BY журнал.датавремя desc, журнал.содержание;

--------------------------------------------------------------------------------------------------------------------------------
CREATE VIEW vw_контрагенты AS
   SELECT * FROM контрагенты;
	
--------------------------------------------------------------------------------------------------------------------------------
CREATE VIEW vw_номенклатура AS
   SELECT * FROM номенклатура;

--------------------------------------------------------------------------------------------------------------------------------
CREATE VIEW vw_материалы AS
   SELECT * FROM материалы;

--------------------------------------------------------------------------------------------------------------------------------
CREATE TYPE sp_calcaccoborot_fret AS (
	дата DATE,
	оперномер INTEGER,
	оперимя CHARACTER VARYING(100),
	доккод INTEGER,
	документ CHARACTER VARYING(20),
	номер CHARACTER VARYING(10),
	комментарий CHARACTER VARYING(100),
	сумма NUMERIC(10,2),
	дбсчет CHARACTER(5),
	крсчет CHARACTER(5),
	дебет NUMERIC(10,2),
	кредит NUMERIC(10,2),
	сдебет CHARACTER VARYING(15),
	скредит CHARACTER VARYING(15)
);


CREATE TYPE sp_calcobjoborot_fret AS (
	дата DATE,
	оперномер INTEGER,
	оперимя CHARACTER VARYING(100),
	доккод INTEGER,
	документ CHARACTER VARYING(20),
	номер CHARACTER VARYING(10),
	стр INTEGER,
	комментарий CHARACTER VARYING(100),
	сумма NUMERIC(10,2),
	дбсчет CHARACTER(5),
	крсчет CHARACTER(5),
	дбкол NUMERIC(10,3),
	дебет NUMERIC(10,2),
	кркол NUMERIC(10,3),
	кредит NUMERIC(10,2),
	сдбкол CHARACTER VARYING(15),
	сдебет CHARACTER VARYING(15),
	скркол CHARACTER VARYING(15),
	скредит CHARACTER VARYING(15)
);


CREATE TYPE sp_calcoborot_fret AS (
	код INTEGER,
	кол NUMERIC(10,3),
	сальдо NUMERIC(10,2),
	дбкол NUMERIC(10,3),
	дебет NUMERIC(10,2),
	кркол NUMERIC(10,3),
	кредит NUMERIC(10,2),
	конкол NUMERIC(10,3),
	консальдо NUMERIC(10,2),
	cкол CHARACTER VARYING(15),
	cсальдо CHARACTER VARYING(15),
	cдбкол CHARACTER VARYING(15),
	cдебет CHARACTER VARYING(15),
	cкркол CHARACTER VARYING(15),
	cкредит CHARACTER VARYING(15),
	cконкол CHARACTER VARYING(15),
	cконсальдо CHARACTER VARYING(15)
);


	
--------------------------------------------------------------------------------------------------------------------------------
CREATE FUNCTION sp_calcaccoborot(cAcc CHARACTER VARYING, cDate1 CHARACTER VARYING, cDate2 CHARACTER VARYING) RETURNS SETOF sp_calcaccoborot_fret
    AS $$
DECLARE ret_row record;
	dDate1 DATE;
	dDate2 DATE;
BEGIN
	dDate1 := to_date(cDate1, 'dd.mm.yyyy');
	dDate2 := to_date(cDate2, 'dd.mm.yyyy') + 1;
	FOR ret_row in
		SELECT dDate1 AS дата, 0 AS оперномер, ''::VARCHAR(100) AS оперимя, 0 AS доккод, ''::VARCHAR(20) AS документ, ''::VARCHAR(10) AS номер, ''::VARCHAR(100) AS комментарий, 0.0 AS сумма, 
       			''::char(5) AS дбсчет, ''::char(5) AS крсчет,
       			CASE
               			WHEN s.сальдо > 0 THEN s.сальдо
               			ELSE 0.0
               		END AS дебет,
       			CASE
                		WHEN s.сальдо < 0 THEN -s.сальдо
                		ELSE 0.0
                	END AS кредит, ''::VARCHAR(15) AS сдебет, ''::VARCHAR(15) AS скредит
		FROM (SELECT (s.сальдо + p1.сумма - p2.сумма) AS сальдо
      	      	      FROM (SELECT счет, sum(COALESCE(сальдо, 0)) AS сальдо 
		    	    FROM сальдо 
		    	    WHERE счет = cAcc 
		    	    GROUP BY счет) s LEFT OUTER JOIN (SELECT p.дбсчет, sum(COALESCE(p.сумма, 0)) AS сумма 
                                		 	      FROM проводки p INNER JOIN документы d ON p.доккод=d.код 
			                        	      WHERE p.дбсчет = cAcc AND d.дата < dDate1 
			         		      	      GROUP BY p.дбсчет) p1 ON s.счет = p1.дбсчет
			             	     LEFT OUTER JOIN (SELECT p.крсчет, sum(COALESCE(p.сумма, 0)) AS сумма 
                                 			      FROM проводки p INNER JOIN документы d ON p.доккод=d.код 
                                 		      	      WHERE p.крсчет = cAcc AND d.дата < dDate1
       			         		      	      GROUP BY p.крсчет) p2 ON s.счет = p2.крсчет
		) s
		UNION
		SELECT d.дата, d.опер AS оперномер, t.имя AS оперимя, d.код, COALESCE(t.осндокумент, ''), d.номер, d.комментарий, d.сумма, cAcc AS дбсчет, p.крсчет, sum(COALESCE(p.сумма, 0)) AS дбсумма, 0 AS крсумма, ''::VARCHAR(15) AS cдебет, ''::VARCHAR(15) AS cкредит
		FROM проводки p INNER JOIN документы d ON p.доккод=d.код 
                		INNER JOIN топер t ON p.опер = t.опер AND t.номер = 1
		WHERE p.дбсчет = cAcc AND p.крсчет <> cAcc AND p.сумма <> 0 AND d.дата >= dDate1 AND d.дата < dDate2
		GROUP BY d.дата, d.опер, t.имя, d.код, t.осндокумент, d.номер, d.комментарий, d.сумма, p.крсчет
		UNION
		SELECT d.дата, d.опер AS оперномер, t.имя AS оперимя, d.код, COALESCE(t.осндокумент, ''), d.номер, d.комментарий, d.сумма, p.дбсчет, cAcc AS крсчет, 0 AS дбсумма, sum(COALESCE(p.сумма, 0)) AS крсумма, ''::VARCHAR(15) AS cдебет, ''::VARCHAR(15) AS cкредит
		FROM проводки p INNER JOIN документы d ON p.доккод=d.код 
        		        INNER JOIN топер t ON p.опер = t.опер AND t.номер = 1
		WHERE p.крсчет = cAcc AND p.дбсчет <> cAcc AND p.сумма <> 0 AND d.дата >= cDate1 AND d.дата < dDate2
		GROUP BY d.дата, d.опер, t.имя, d.код, t.осндокумент, d.номер, d.комментарий, d.сумма, p.дбсчет
		ORDER BY дата LOOP

		RETURN NEXT ret_row;
	END LOOP;
	RETURN;
END;
$$
    LANGUAGE plpgsql;


--------------------------------------------------------------------------------------------------------------------------------
CREATE FUNCTION sp_calcdocoborot(cAcc CHARACTER VARYING, cDate1 CHARACTER VARYING, cDate2 CHARACTER VARYING) RETURNS VOID
    AS $$
BEGIN
	SELECT to_date(cDate1, 'dd.mm.yyyy') AS дата, null AS оперномер, '' AS оперимя, '' AS доккод, '' AS документ, '' AS номер, '' AS комментарий, 0 AS сумма, '' AS дбсчет, '' AS крсчет,
       		дебет = CASE
               			WHEN s.сальдо > 0 THEN s.сальдо
               			ELSE 0
               		END,
       		кредит = CASE
                		WHEN s.сальдо < 0 THEN -s.сальдо
                		ELSE 0
                	END, '             ' AS сдебет, '             ' AS скредит
	FROM (SELECT (s.сальдо + COALESCE(p1.сумма, 0) - COALESCE(p2.сумма, 0)) AS сальдо 
       	      FROM (SELECT sum(сальдо) AS сальдо 
		    FROM сальдо 
		    WHERE счет = cAcc) s,
	           (SELECT sum(COALESCE(p.сумма, 0)) AS сумма 
                    FROM проводки p INNER JOIN документы d ON p.доккод=d.код 
                    WHERE p.дбсчет = cAcc AND to_date(d.дата, 'dd.mm.yyyy') < to_date(cDate1, 'dd.mm.yyyy')) p1,
                   (SELECT sum(COALESCE(p.сумма, 0)) AS сумма 
                    FROM проводки p INNER JOIN документы d ON p.доккод=d.код 
	            WHERE p.крсчет = cAcc AND to_date(d.дата, 'dd.mm.yyyy') < to_date(cDate1, 'dd.mm.yyyy')) p2
              ) s
	UNION
	SELECT d.дата, d.опер AS оперномер, t.имя AS оперимя, d.код, COALESCE(t.осндокумент, ''), d.номер, d.комментарий, d.сумма, cAcc AS дбсчет, p.крсчет, sum(COALESCE(p.сумма, 0)) AS дебет, 0 AS кредит, '             ', '             '
	FROM проводки p INNER JOIN документы d ON p.доккод=d.код 
                        INNER JOIN топер t ON p.опер = t.опер AND t.номер = 1
	WHERE p.дбсчет = cAcc AND (p.сумма <> 0) AND (to_date(d.дата, 'dd.mm.yyyy') >= to_date(cDate1, 'dd.mm.yyyy')) AND (to_date(d.дата, 'dd.mm.yyyy') < to_date(cDate2, 'dd.mm.yyyy') + 1)
	GROUP BY d.дата, d.опер, t.имя, d.код, t.осндокумент, d.номер, d.комментарий, d.сумма, p.крсчет
	UNION
	SELECT d.дата, d.опер AS оперномер, t.имя AS оперимя, d.код, COALESCE(t.осндокумент, ''), d.номер, d.комментарий, d.сумма, p.дбсчет, cAcc AS крсчет, 0 AS дебет, sum(COALESCE(p.сумма, 0)) AS кредит, '             ', '             '
	FROM проводки p INNER JOIN документы d ON p.доккод=d.код 
                        INNER JOIN топер t ON p.опер = t.опер AND t.номер = 1
	WHERE p.крсчет = cAcc AND (p.сумма <> 0) AND (to_date(d.дата, 'dd.mm.yyyy') >= to_date(cDate1, 'dd.mm.yyyy')) AND (to_date(d.дата, 'dd.mm.yyyy') < to_date(cDate2, 'dd.mm.yyyy') + 1)
	GROUP BY d.дата, d.опер, t.имя, d.код, t.осндокумент, d.номер, d.комментарий, d.сумма, p.дбсчет
	ORDER BY дата;
END;
$$
    LANGUAGE plpgsql;


--------------------------------------------------------------------------------------------------------------------------------
CREATE FUNCTION sp_calcobjoborot(cAcc CHARACTER VARYING, pnObj INTEGER, cDate1 CHARACTER VARYING, cDate2 CHARACTER VARYING) RETURNS SETOF sp_calcobjoborot_fret
    AS $$
DECLARE ret_row record;
	nObj INTEGER;
	dDate1 DATE;
	dDate2 DATE;
BEGIN
	dDate1 := to_date(cDate1, 'dd.mm.yyyy');
	dDate2 := to_date(cDate2, 'dd.mm.yyyy') + 1;
	nObj := COALESCE(pnObj, 0);
	IF (SELECT количество FROM счета WHERE счет = cAcc) = TRUE THEN		-- если для этого счета есть количественный учет, то в результат включим ссылку на номер строки в документе для облегчения поиска позиции
		FOR ret_row in
			SELECT  dDate1 AS дата, 0 AS оперномер, ''::VARCHAR(100) AS оперимя, 0 AS доккод, ''::VARCHAR(20) AS документ, ''::VARCHAR(10) AS номер, 0 AS стр, ''::VARCHAR(100) AS комментарий, 0 AS сумма, ''::char(5) AS дбсчет, ''::char(5) AS крсчет,
	       			CASE
             				WHEN s.кол > 0 THEN s.кол
		               		ELSE 0.0
		               	END AS дбкол,
	       			CASE
             				WHEN s.сальдо > 0 THEN s.сальдо
		               		ELSE 0.0
        	     		END AS дебет,
	       			CASE
             				WHEN s.кол < 0 THEN -s.кол
	               			ELSE 0.0
	             		END AS кркол,
		       		CASE
             				WHEN s.сальдо < 0 THEN -s.сальдо
	                		ELSE 0.0
             			END AS кредит, ''::VARCHAR(15) AS сдбкол, ''::VARCHAR(15) AS скркол, ''::VARCHAR(15) AS сдебет, ''::VARCHAR(15) AS скредит
			FROM (SELECT (s.кол + p1.кол - p2.кол) AS кол, (s.сальдо + p1.сумма - p2.сумма) AS сальдо 
			      FROM (SELECT код, кол, сальдо 
				    FROM сальдо 
				    WHERE счет = cAcc AND код = nObj) s,
				   (SELECT sum(p.кол) AS кол, sum(p.сумма) AS сумма 
             		            FROM (SELECT p.код AS код, p.кол, p.сумма
					  FROM проводки p INNER JOIN (SELECT код 
								      FROM документы 
								      WHERE дата < dDate1) d ON p.доккод=d.код
	                            	  WHERE p.дбсчет = cAcc AND p.дбкод = nObj
					  UNION
				    	  SELECT 0 AS код, 0 AS кол, 0 AS сумма) p) p1,
             			   (SELECT sum(p.кол) AS кол, sum(p.сумма) AS сумма 
                        	    FROM (SELECT p.код AS код, p.кол, p.сумма
					  FROM проводки p INNER JOIN (SELECT код 
								      FROM документы 
								      WHERE дата < dDate1) d ON p.доккод=d.код
					  WHERE p.крсчет = cAcc AND p.кркод = nObj
					  UNION
					  SELECT 0 AS код, 0 AS кол, 0 AS сумма) p) p2
		              ) s
			UNION
			SELECT d.дата, d.опер AS оперномер, t.имя AS оперимя, d.код, t.осндокумент AS документ, d.номер, p.стр, d.комментарий, d.сумма, cAcc AS дбсчет, p.крсчет, sum(p.кол) AS дбкол, sum(p.сумма) AS дебет, 0 AS кркол, 0 AS кредит, '', '', '', ''
			FROM проводки p INNER JOIN документы d ON p.доккод=d.код 
        	     		        INNER JOIN топер t ON p.опер = t.опер AND t.номер = 1
			WHERE p.дбсчет = cAcc AND p.дбкод = nObj AND d.дата >= dDate1 AND d.дата < dDate2
			GROUP BY d.дата, d.опер, t.имя, d.код, t.осндокумент, d.номер, p.стр, d.комментарий, d.сумма, p.крсчет
			UNION
			SELECT d.дата, d.опер AS оперномер, t.имя AS оперимя, d.код, t.осндокумент AS документ, d.номер, p.стр, d.комментарий, d.сумма, p.дбсчет, cAcc AS крсчет, 0 AS дбкол, 0 AS дебет, sum(p.кол) AS кркол, sum(p.сумма) AS кредит, '', '', '', ''
			FROM проводки p INNER JOIN документы d ON p.доккод=d.код 
             	        	        INNER JOIN топер t ON p.опер = t.опер AND t.номер = 1
			WHERE p.крсчет = cAcc AND p.кркод = nObj AND d.дата >= dDate1 AND d.дата < dDate2
			GROUP BY d.дата, d.опер, t.имя, d.код, t.осндокумент, d.номер, p.стр, d.комментарий, d.сумма, p.дбсчет
			ORDER BY дата LOOP
			RETURN NEXT ret_row;
		END LOOP;
	ELSE
		FOR ret_row in
			SELECT  dDate1 AS дата, 0 AS оперномер, ''::VARCHAR(100) AS оперимя, 0 AS доккод, ''::VARCHAR(20) AS документ, ''::VARCHAR(10) AS номер, 0 AS стр, ''::VARCHAR(100) AS комментарий, 0 AS сумма, ''::char(5) AS дбсчет, ''::char(5) AS крсчет,
		       		CASE
             				WHEN s.кол > 0 THEN s.кол
	               			ELSE 0.0
		               	END AS дбкол,
		       		CASE
             				WHEN s.сальдо > 0 THEN s.сальдо
	               			ELSE 0.0
	             		END AS дебет,
		       		CASE
             				WHEN s.кол < 0 THEN -s.кол
	               			ELSE 0.0
	             		END AS кркол,
		       		CASE
             				WHEN s.сальдо < 0 THEN -s.сальдо
	                		ELSE 0.0
	             		END AS кредит, ''::VARCHAR(15) AS сдбкол, ''::VARCHAR(15) AS скркол, ''::VARCHAR(15) AS сдебет, ''::VARCHAR(15) AS скредит
			FROM (SELECT (s.кол + p1.кол - p2.кол) AS кол, (s.сальдо + p1.сумма - p2.сумма) AS сальдо 
			      FROM (SELECT код, кол, сальдо 
				    FROM сальдо 
				    WHERE счет = cAcc AND код = nObj) s,
				   (SELECT sum(p.кол) AS кол, sum(p.сумма) AS сумма 
             		            FROM (SELECT p.код, p.кол, p.сумма
					  FROM проводки p INNER JOIN (SELECT код 
								      FROM документы 
								      WHERE дата < dDate1) d ON p.доккод=d.код
	                            	  WHERE p.дбсчет = cAcc AND p.дбкод = nObj
					  UNION
				    	  SELECT 0 AS код, 0 AS кол, 0 AS сумма) p) p1,
             			   (SELECT sum(p.кол) AS кол, sum(p.сумма) AS сумма 
                        	    FROM (SELECT p.код, p.кол, p.сумма
					  FROM проводки p INNER JOIN (SELECT код 
								      FROM документы 
								      WHERE дата < dDate1) d ON p.доккод=d.код
					  WHERE p.крсчет = cAcc AND p.кркод = nObj
					  UNION
					  SELECT 0 AS код, 0 AS кол, 0 AS сумма) p) p2
		              ) s
			UNION
			SELECT d.дата, d.опер AS оперномер, t.имя AS оперимя, d.код, t.осндокумент AS документ, d.номер, 0 AS стр, d.комментарий, d.сумма, cAcc AS дбсчет, p.крсчет, sum(p.кол) AS дбкол, sum(p.сумма) AS дебет, 0 AS кркол, 0 AS кредит, '', '', '', ''
			FROM проводки p INNER JOIN документы d ON p.доккод=d.код
             	        	        INNER JOIN топер t ON p.опер = t.опер AND t.номер = 1
			WHERE p.дбсчет = cAcc AND p.дбкод = nObj AND d.дата >= dDate1 AND d.дата < dDate2
			GROUP BY d.дата, d.опер, t.имя, d.код, t.осндокумент, d.номер, d.комментарий, d.сумма, p.крсчет
			UNION
			SELECT d.дата, d.опер AS оперномер, t.имя AS оперимя, d.код, t.осндокумент AS документ, d.номер, 0 AS стр, d.комментарий, d.сумма, p.дбсчет, cAcc AS крсчет, 0 AS дбкол, 0 AS дебет, sum(p.кол) AS кркол, sum(p.сумма) AS кредит, '', '', '', ''
			FROM проводки p INNER JOIN документы d ON p.доккод=d.код
             		                INNER JOIN топер t ON p.опер = t.опер AND t.номер = 1
			WHERE p.крсчет = cAcc AND p.кркод = nObj AND d.дата >= dDate1 AND d.дата < dDate2
			GROUP BY d.дата, d.опер, t.имя, d.код, t.осндокумент, d.номер, d.комментарий, d.сумма, p.дбсчет
			ORDER BY дата LOOP
			RETURN NEXT ret_row;
		END LOOP;
	END IF;
END;
$$
    LANGUAGE plpgsql;


--------------------------------------------------------------------------------------------------------------------------------
CREATE FUNCTION sp_calcoborot(cAcc CHARACTER VARYING, cDate1 CHARACTER VARYING, cDate2 CHARACTER VARYING) RETURNS SETOF sp_calcoborot_fret
    AS $$
-- cComm1 - секция SELECT команды
-- cComm2 - секция ORder команды
-- cAcc - bookkeeperский счет
-- dDate1 - начальная дата
-- dDate2 - конечная дата
DECLARE ret_row record;
	dDate1 DATE;
	dDate2 DATE;
BEGIN
	dDate1 := to_date(cDate1, 'dd.mm.yyyy');
	dDate2 := to_date(cDate2, 'dd.mm.yyyy') + 1;
	
	FOR ret_row in
		SELECT *
		FROM (SELECT s.код, COALESCE(s.кол, 0) AS кол, COALESCE(s.сальдо, 0) AS сальдо, COALESCE(p1.кол, 0) AS дбкол, COALESCE(p1.сумма, 0) AS дебет, COALESCE(p2.кол, 0) AS кркол, COALESCE(p2.сумма, 0) AS кредит, (COALESCE(s.кол, 0) + COALESCE(p1.кол, 0) - COALESCE(p2.кол, 0)) AS конкол, (COALESCE(s.сальдо, 0) + COALESCE(p1.сумма, 0) - COALESCE(p2.сумма, 0)) AS консальдо, 
			''::VARCHAR(15) AS cкол, ''::VARCHAR(15) AS cсальдо, ''::VARCHAR(15) AS cдбкол, ''::VARCHAR(15) AS cдебет, ''::VARCHAR(15) AS cкркол, ''::VARCHAR(15) AS cкредит, ''::VARCHAR(15) AS cконкол, ''::VARCHAR(15) AS cконсальдо
 		      FROM (SELECT s.код, (s.кол + COALESCE(p1.кол, 0) - COALESCE(p2.кол, 0)) AS кол, (s.сальдо + COALESCE(p1.сумма, 0) - COALESCE(p2.сумма, 0)) AS сальдо
                	    FROM (SELECT код, COALESCE(кол, 0) AS кол, сальдо FROM сальдо WHERE счет = cAcc
                    		 ) s LEFT JOIN (SELECT p.дбкод AS код, sum(COALESCE(p.кол, 0)) AS кол, sum(COALESCE(p.сумма, 0)) AS сумма
			        	   	FROM проводки p INNER JOIN (SELECT код FROM документы WHERE дата < dDate1) d ON p.доккод=d.код
					   	WHERE p.дбсчет = cAcc
					   	GROUP BY p.дбкод) p1 ON s.код = p1.код
			             LEFT JOIN (SELECT p.кркод AS код, sum(COALESCE(p.кол, 0)) AS кол, sum(COALESCE(p.сумма, 0)) AS сумма
		        	           	FROM проводки p INNER JOIN (SELECT код FROM документы WHERE дата < dDate1) d ON p.доккод=d.код
			        	   	WHERE p.крсчет = cAcc
		        	   		GROUP BY p.кркод) p2 ON s.код = p2.код
                    	    ) s LEFT JOIN (SELECT p.дбкод AS код, sum(COALESCE(p.кол, 0)) AS кол, sum(COALESCE(p.сумма, 0)) AS сумма
                         		   FROM проводки p INNER JOIN (SELECT код FROM документы WHERE дата >= dDate1 AND дата < dDate2) d ON p.доккод=d.код
                                	   WHERE p.дбсчет = cAcc
                            		   GROUP BY p.дбкод
	                           	  ) p1 ON s.код = p1.код
        	        	LEFT JOIN (SELECT p.кркод AS код, sum(COALESCE(p.кол, 0)) AS кол, sum(COALESCE(p.сумма, 0)) AS сумма
					   FROM проводки p INNER JOIN (SELECT код FROM документы WHERE дата >= dDate1 AND дата < dDate2) d ON p.доккод=d.код
                        	   	   WHERE p.крсчет = cAcc
                                   	   GROUP BY p.кркод
                                   	   ) p2 ON s.код = p2.код
      	     	) s
		WHERE кол <> 0 OR сальдо <> 0 OR дбкол <> 0 OR дебет <> 0 OR кркол <> 0 OR кредит <> 0 OR конкол <> 0 OR консальдо <> 0 
		LOOP
		RETURN NEXT ret_row;
	END LOOP;
END;
$$
    LANGUAGE plpgsql;


--------------------------------------------------------------------------------------------------------------------------------
CREATE FUNCTION sp_calctotobjoborot(cAcc CHARACTER VARYING, pcDictname CHARACTER VARYING, pnObj INTEGER, cDate1 CHARACTER VARYING, cDate2 CHARACTER VARYING) RETURNS VOID
    AS $$
DECLARE cSetName VARCHAR(50);
	cCommand VARCHAR(8000);
	cDictname VARCHAR (50);
	nObj INTEGER;
BEGIN
	cDictname := upper(pcDictname);
	nObj = COALESCE(pnObj, 0);
	cSetName = (SELECT имясправочника FROM счета WHERE счет = cAcc);
	cSetName = rtrim(cSetName);

	IF (SELECT count(*) FROM vw_columns WHERE таблица = cSetName AND столбец = 'код') = 1			-- если есть одно поле код
		AND (SELECT count(*) FROM vw_columns WHERE таблица = cSetName AND столбец = 'имя') = 1	THEN 	-- и одно поле имя
		-- мы определили, что код объекта определяется справочником, поэтому информацию об объекте можно
		-- собрать напрямую
		SELECT sp_calcobjoborot(cAcc, nObj, cDate1, cDate2);
	ELSE
		-- мы определили, что код объекта определяется набором справочников
		IF (SELECT count(*) FROM vw_columns WHERE таблица = cSetName AND столбец = 'код') = 1				-- если есть одно поле код
		AND (SELECT count(*) FROM vw_columns WHERE таблица = cSetName AND столбец = 'код_' + cDictname) = 1 THEN	-- и одно поле со ссылкой на справочник
			SELECT sp_maketotobjoborotcommAND(cAcc, cDictname, nObj, cDate1, cDate2) INTO cCommand;
			EXECUTE cCommand;
		END IF;
	END IF;
END;
$$
    LANGUAGE plpgsql;


--------------------------------------------------------------------------------------------------------------------------------
CREATE FUNCTION sp_DeleteDoc(nDocId INTEGER) RETURNS VOID
    AS $$
BEGIN
	DELETE FROM документы WHERE код = nDocId;
	DELETE FROM проводки WHERE доккод = nDocId;
END;
$$
    LANGUAGE plpgsql;


--------------------------------------------------------------------------------------------------------------------------------
CREATE FUNCTION sp_DeleteDocStr(nDocId INTEGER, nDocStr INTEGER) RETURNS VOID
    AS $$
BEGIN
	DELETE FROM проводки WHERE доккод = nDocId AND стр = nDocStr;
END;
$$
    LANGUAGE plpgsql;


--------------------------------------------------------------------------------------------------------------------------------
CREATE FUNCTION sp_InsertDoc(noper INTEGER, cDate CHARACTER VARYING) RETURNS CHARACTER VARYING
    AS $$
DECLARE 
	cNumName нумераторы.имя%TYPE;		-- наименование нумератора
	nValue нумераторы.значение%TYPE;	-- значение нумератора
	dDate DATE;				-- дата документа
	cNumber документы.номер%TYPE;			
BEGIN
	cNumName := rtrim((SELECT нумератор FROM топер WHERE опер = noper AND номер = 1 LIMIT 1));	-- загрузим наименование нумератора
	IF cNumName is NOT NULL AND char_length(cNumName) > 0 THEN
		nValue := (SELECT значение FROM нумераторы WHERE rtrim(имя) = cNumName LIMIT 1);	-- получим новое значение нумератора
		nValue := nValue + 1;
		UPDATE нумераторы SET значение = nValue WHERE rtrim(имя) = cNumName;		-- сохраним новое значение нумератора
		cNumber := trim(leading FROM to_char(nValue, '999999999'));
	ELSE
		cNumber := '';
	END IF;
	IF cDate IS NULL THEN
		dDate = current_date;
	ELSE
		dDate = to_date(cDate, 'dd.mm.yyyy');
	END IF;
	INSERT INTO документы (дата, датавремя, опер, номер, авто) VALUEs (dDate, current_timestamp, noper, cNumber, 0);
	RETURN cNumber;
END;
$$
    LANGUAGE plpgsql;


--------------------------------------------------------------------------------------------------------------------------------
CREATE FUNCTION sp_InsertDocStr(noper INTEGER, nDocId INTEGER, pcParam CHARACTER VARYING, pnCount INTEGER, pnDocStr INTEGER) RETURNS VOID
    AS $$
DECLARE nNum INTEGER;
	cDbAcc VARCHAR(5);
	cCrAcc VARCHAR(5);
	nDbId INTEGER;
	nCrId INTEGER;
	nQuan NUMERIC(8,3);
	nPrice NUMERIC(14,2);
	nSum NUMERIC(14,2);
	cParam1 VARCHAR(100);
	cParam VARCHAR(100);
	nCount INTEGER;
	nDocStr INTEGER;
	curResult REFCURSOR;
BEGIN
	cParam := pcParam;
	nCount := pnCount;
	nDocStr := pnDocStr;

	IF nCount IS NULL THEN
		nCount := 1;
	END IF;

	IF nDocStr IS NULL OR nDocStr = 0 THEN
		-- найдем наибольший номер строки в документе
		nDocStr := (SELECT max(p.стр) AS max_value FROM проводки p WHERE p.доккод = nDocId AND p.опер = noper);
		IF nDocStr IS NULL THEN
			nDocStr := 1;
		ELSE
			nDocStr := nDocStr + 1;
		END IF;
	END IF;

	-- вставим в документ проводки для новой строки
	OPEN curResult FOR SELECT дбсчет, крсчет, номер  FROM топер WHERE опер = noper ORDER BY номер;
	WHILE nCount > 0 LOOP
		cParam1 := cParam;
		FETCH first FROM curResult INTO cDbAcc, cCrAcc, nNum;
		WHILE found LOOP
			IF length(cParam) = 0 THEN
				cParam1 := '0,0,0,0,0,';
			END IF;
			nDbId := to_number(substring(cParam1 FROM 1 FOR position(',' in cParam1) - 1), '999999999');	
			cParam1 := substring(cParam1 FROM position(',' in cParam1) + 1);
			nCrId := to_number(substring(cParam1 FROM 1 FOR position(',' in cParam1) - 1), '999999999');	
			cParam1 := substring(cParam1 FROM position(',' in cParam1) + 1);
			nQuan := to_number(substring(cParam1 FROM 1 FOR position(',' in cParam1) - 1), '99999d999');	
			cParam1 := substring(cParam1 FROM position(',' in cParam1) + 1);
			nPrice := to_number(substring(cParam1 FROM 1 FOR position(',' in cParam1) - 1), '99999999d99');	
			cParam1 := substring(cParam1 FROM position(',' in cParam1) + 1);
			nSum := to_number(substring(cParam1 FROM 1 FOR position(',' in cParam1) - 1), '99999999d99');	
			cParam1 := substring(cParam1 FROM position(',' in cParam1) + 1);
			INSERT INTO проводки (доккод, стр, опер, номеропер, дбсчет, дбкод, крсчет, кркод, кол, цена, сумма) VALUEs (nDocId, nDocStr, noper, nNum, cDbAcc, nDbId, cCrAcc, nCrId, nQuan, nPrice, nSum);
			FETCH NEXT FROM curResult INTO cDbAcc, cCrAcc, nNum;
		END LOOP;
		nCount := nCount - 1;
		nDocStr := nDocStr + 1;
	END LOOP;
	CLOSE curResult;
END;
$$
    LANGUAGE plpgsql;


--------------------------------------------------------------------------------------------------------------------------------
CREATE FUNCTION sp_IsLockedPeriod(cDate CHARACTER VARYING) RETURNS VOID
    AS $$
DECLARE dDate DATE;
BEGIN
	IF (cDate IS NULL) OR (cDate = '') THEN					-- если дата не указана
		dDate = current_date;				-- то выберем текущую дату
	ELSE
		dDate = to_date(cDate, 'dd.mm.yyyy');
	END IF;
	SELECT b.* 
	FROM блокпериоды b INNER JOIN vw_пользователи u ON b.код_vw_пользователи = u.код AND u.имя = current_user 
	WHERE (dDate > b.начало - '1') AND (dDate < b.конец + '1') AND (dDate < b.блокконец + '1');
END;
$$
    LANGUAGE plpgsql;


--------------------------------------------------------------------------------------------------------------------------------
CREATE FUNCTION sp_maketotobjoborotcommand(cAcc CHARACTER VARYING, pcDictname CHARACTER VARYING, pnObj INTEGER, cDate1 CHARACTER VARYING, cDate2 CHARACTER VARYING) RETURNS CHARACTER VARYING
    AS $$
DECLARE cSetName VARCHAR(50);
	cCommand VARCHAR(8000);
	cDictname VARCHAR (50);
	nObj INTEGER;
BEGIN
	cDictname = upper(pcDictname);
	nObj = COALESCE(pnObj, 0);
	cSetName = (SELECT имясправочника FROM счета WHERE счет = cAcc);
	cSetName = rtrim(cSetName);

	cCommand = 'SELECT код FROM ' || cSetName || ' WHERE код_' || cDictname || '=' || rtrim(ltrim(cast(nObj AS VARCHAR(20))));
	cCommand = 'SELECT дата, оперномер, оперимя, дбсчет, крсчет, sum(дбкол) AS дбкол, sum(дебет) AS дебет, sum(кркол) AS кркол, sum(кредит) AS кредит '
		 || 'FROM (SELECT to_date("' || cDate1 || '", "dd.mm.yyyy") AS дата, 0 AS оперномер, "" AS оперимя, "" AS дбсчет, "" AS крсчет, '
			       || 'дбкол = CASE '
			               || 'WHEN s.кол > 0 THEN s.кол '
	        		       || 'ELSE 0 '
			               || 'END, '
			       || 'дебет = CASE '
        			       || 'WHEN s.сальдо > 0 THEN s.сальдо '
			               || 'ELSE 0 '
			               || 'END, '
			       || 'кркол = CASE '
			               || 'WHEN s.кол < 0 THEN -s.кол '
        			       || 'ELSE 0 '
			               || 'END, '
			       || 'кредит = CASE '
	        		        || 'WHEN s.сальдо < 0 THEN -s.сальдо '
			                || 'ELSE 0 '
			                || 'END '
			 || 'FROM (SELECT (s.кол + COALESCE(p1.кол, 0) - COALESCE(p2.кол, 0)) AS кол, (s.сальдо + COALESCE(p1.сумма, 0) - COALESCE(p2.сумма, 0)) AS сальдо '
 		        	     || 'FROM (SELECT код, COALESCE(кол, 0) AS кол, COALESCE(сальдо, 0) AS сальдо '
				     || 'FROM сальдо WHERE счет = "' || cAcc || '" AND код in (' || cCommand || ') '
     		        		             || ') s LEFT OUTER JOIN (SELECT p.дбкод AS код, sum(COALESCE(p.кол, 0)) AS кол, sum(COALESCE(p.сумма, 0)) AS сумма '
     	               		        		                  || 'FROM проводки p INNER JOIN документы d ON p.доккод=d.код '
                	                       		        		  || 'WHERE p.дбсчет = "' || cAcc || '" AND COALESCE(p.дбкод, 0) in (' || cCommand || ') AND to_date(d.дата, "dd.mm.yyyy") < to_date("' || cDate1 || '", "dd.mm.yyyy") '
	                	                                       		  || 'GROUP BY p.дбкод) p1 ON s.код = p1.код '
			        	                     	 || 'LEFT OUTER JOIN (SELECT p.кркод AS код, sum(COALESCE(p.кол, 0)) AS кол, sum(COALESCE(p.сумма, 0)) AS сумма '
	               				                                  || 'FROM проводки p INNER JOIN документы d ON p.доккод=d.код '
        	                				                  || 'WHERE p.крсчет = "' || cAcc || '" AND COALESCE(p.кркод, 0) in (' || cCommand || ') AND to_date(d.дата, "dd.mm.yyyy") < to_date("' || cDate1 || '", "dd.mm.yyyy") '
				                                		  || 'GROUP BY p.кркод) p2 ON s.код = p2.код '
				     		      || ') s '
						|| 'UNION '
						|| 'SELECT d.датавремя AS дата, d.опер AS оперномер, t.имя AS оперимя, "' || cAcc || '" AS дбсчет, p.крсчет, COALESCE(p.кол, 0) AS дбкол, COALESCE(p.сумма, 0) AS дбсумма, 0 AS кркол, 0 AS крсумма '
						|| 'FROM проводки p INNER JOIN документы d ON p.доккод=d.код '
               							               || 'INNER JOIN топер t ON p.опер = t.опер AND t.номер = 1 '
						|| 'WHERE p.дбсчет <> p.крсчет AND p.дбсчет = "' || cAcc || '" AND p.дбкод in (' || cCommand || ') AND (p.кол <> 0 OR p.сумма <> 0) AND (to_date(d.дата, "dd.mm.yyyy") >= to_date("' || cDate1 || '", "dd.mm.yyyy")) AND (to_date(d.дата, "dd.mm.yyyy") < to_date("' || cDate2 || '", "dd.mm.yyyy") + 1) '
						|| 'UNION '
						|| 'SELECT d.датавремя AS дата, d.опер AS оперномер, t.имя AS оперимя, p.дбсчет, "' || cAcc || '" AS крсчет, 0 AS дбкол, 0 AS дбсумма, COALESCE(p.кол, 0) AS кркол, COALESCE(p.сумма, 0) AS крсумма '
						|| 'FROM проводки p INNER JOIN документы d ON p.доккод=d.код '
               							               || 'INNER JOIN топер t ON p.опер = t.опер AND t.номер = 1 '
						|| 'WHERE p.дбсчет <> p.крсчет AND p.крсчет = "' || cAcc || '" AND p.кркод in (' || cCommand || ') AND (p.кол <> 0 OR p.сумма <> 0) AND (to_date(d.дата, "dd.mm.yyyy") >= to_date("' || cDate1 || '", "dd.mm.yyyy")) AND (to_date(d.дата, "dd.mm.yyyy") < to_date("' || cDate2 || '", "dd.mm.yyyy") + 1) '
						|| ') s '
					|| 'GROUP BY дата, оперномер, оперимя, дбсчет, крсчет';
	RETURN cCommand;
END;
$$
    LANGUAGE plpgsql;


--------------------------------------------------------------------------------------------------------------------------------
CREATE FUNCTION testdeleting_сальдо() RETURNS trigger
    AS $$
DECLARE 
	cAcc VARCHAR(20);
	nId INTEGER;
BEGIN
	IF (SELECT count(*) FROM проводки WHERE (дбсчет = OLD.счет AND дбкод = OLD.код) OR (дбсчет = OLD.счет AND дбкод = OLD.код)) > 0 THEN
		RAISE EXCEPTION 'Запрещено удалять запись, т.к. для нее были сделаны бухгалтерские проводки.';
	END IF;
	RETURN OLD;
END;
$$
    LANGUAGE plpgsql;


--------------------------------------------------------------------------------------------------------------------------------
CREATE FUNCTION testdeletingdictobject() RETURNS trigger
    AS $$
DECLARE 
	lError BOOLEAN;
	cDict VARCHAR(100);
	nId INTEGER;
	cTable VARCHAR(100);
	cAcc VARCHAR(20);
	nCount INTEGER;
	nDocId INTEGER;
	count INTEGER;
	OperName VARCHAR(100);
	OperNum VARCHAR(10);
	OperDate DATE;
	OperId INTEGER;
	cCommand VARCHAR(100);

	curTables REFCURSOR;
	curAccounts REFCURSOR;
BEGIN
	lError := FALSE;		-- считаем поначалу, что никаких проблем не обнаружено

	-- проверим, есть ли ссылка на этот объект в одном из справочников
	cDict := ltrim(rtrim(upper(tg_relname)));	-- возьмем имя обрабатываемого справочника
	nId := OLD.код;					-- и возьмем код удаляемой позиции

	OPEN curTables FOR
		SELECT DISTINCT t.relname
		FROM pg_attribute c
			INNER JOIN (SELECT c.relfilenode, c.relname
				    FROM pg_clASs c
				    WHERE c.relname in (SELECT tablename FROM pg_tables WHERE schemaname = 'PUBLIC') OR 
					  c.relname in (SELECT viewname FROM pg_views WHERE schemaname = 'PUBLIC')
				    ) t ON c.attrelid = t.relfilenode
		WHERE upper(c.attname) = 'код_' || cDict;

	LOOP
		FETCH curTables INTO cTable;
		IF NOT found THEN
			EXIT;
		ELSE
			EXECUTE 'SELECT count(*) FROM ' || cTable || ' WHERE код_' || cDict || ' = ' || ltrim(rtrim(cast(nId AS VARCHAR(20)))) INTO nCount;
			IF nCount > 0 THEN
				lError := TRUE;
				RAISE EXCEPTION 'Запрещено удалять запись, т.к. на нее имеется ссылка в справочнике <%>', cTable;
				EXIT;			
			END IF;
		END IF;
	END LOOP;

	CLOSE curTables;

	IF NOT lError THEN	-- если еще нет никакой ошибки, то продолжим дальше
		OPEN curAccounts FOR 
			SELECT счет 
			FROM счета 
			WHERE ltrim(rtrim(upper(имясправочника))) = cDict;
	
		LOOP
			FETCH curAccounts INTO cAcc;
			IF NOT found THEN
				EXIT;
			ELSE
				cAcc := rtrim(cAcc);
				cCommand := 'FROM проводки WHERE (дбсчет = ''' || cAcc || ''' AND дбкод = ' || ltrim(rtrim(cast(nId AS VARCHAR(20)))) || ') OR (крсчет = ''' || cAcc || ''' AND кркод = ' || ltrim(rtrim(cast(nId AS VARCHAR(20)))) || ')';
				EXECUTE 'SELECT count(*) ' || cCommand INTO nCount;
				IF nCount > 0 THEN
					lError := TRUE;
					EXECUTE 'SELECT доккод ' || cCommand || ' ORDER BY доккод desc LIMIT 1' INTO nDocId;
					EXECUTE 'SELECT опер ' || cCommand || ' ORDER BY доккод desc LIMIT 1' INTO OperId;
					cCommand := ltrim(rtrim(cast(nDocId AS VARCHAR(20))));
					EXECUTE 'SELECT дата FROM документы WHERE код = ' || cCommand INTO OperDate;
					EXECUTE 'SELECT номер FROM документы WHERE код = ' || cCommand INTO OperNum;
					EXECUTE 'SELECT имя FROM топер WHERE опер = ' || ltrim(rtrim(cast(OperId AS VARCHAR(20)))) || ' AND номер = 1' INTO OperName;
					RAISE EXCEPTION 'Запрещено удалять запись, т.к. для нее были сделаны операции (% шт.). Последняя операция <%> по документу номер <%> была сделана <%>.', nCount, rtrim(OperName), rtrim(OperNum), OperDate;
					EXIT;
				END IF;
			END IF;
		END LOOP;
		CLOSE curAccounts;
	END IF;

	IF lError THEN
		RETURN null;	-- ошибка, удалять нельзя
	ELSE
		RETURN OLD;	-- ошибки нет, можно удалять запись
	END IF;
END;
$$
    LANGUAGE plpgsql;


--------------------------------------------------------------------------------------------------------------------------------
CREATE FUNCTION testdeletingtoperobject() RETURNS trigger
    AS $$
DECLARE 
	lError BOOLEAN;
	cDict VARCHAR(100);
	nId INTEGER;
	cTable VARCHAR(100);
	cAcc VARCHAR(20);
	nCount INTEGER;
	docId INTEGER;
	count INTEGER;
	OperName VARCHAR(100);
	OperNum VARCHAR(10);
	OperDate VARCHAR(10);
	OperId INTEGER;

	curTables REFCURSOR;
	curAccounts REFCURSOR;
BEGIN
	lError := FALSE;		-- считаем поначалу, что никаких проблем не обнаружено

	-- проверим, есть ли ссылка на этот объект в одном из справочников
	cDict := ltrim(rtrim(upper(tg_relname)));	-- возьмем имя обрабатываемого справочника
	nId := OLD.код;					-- и возьмем код удаляемой позиции

	OPEN curTables FOR
		SELECT DISTINCT таблица
		FROM vw_columns
		WHERE столбец = 'код_' || cDict;

	LOOP
		FETCH curTables INTO cTable;
		IF NOT found THEN
			EXIT;
		ELSE
			EXECUTE 'SELECT count(*) FROM ' || cTable || ' WHERE код_' || cDict || ' = ' || ltrim(rtrim(cast(nId AS VARCHAR(20)))) INTO nCount;
			IF nCount > 0 THEN
				lError := TRUE;
				RAISE EXCEPTION 'Запрещено удалять запись, т.к. на нее имеется ссылка в справочнике <%>', cTable;
				EXIT;			
			END IF;
		END IF;
	END LOOP;

	CLOSE curTables;

	IF NOT lError THEN	-- если еще нет никакой ошибки, то продолжим дальше
		OPEN curAccounts FOR 
			SELECT счет 
			FROM счета 
			WHERE upper(имясправочника) = cDict;
	
		LOOP
			FETCH curAccounts INTO cAcc;
			IF NOT found THEN
				EXIT;
			ELSE
				cAcc := rtrim(cAcc);
				EXECUTE 'SELECT count(*) FROM проводки WHERE (дбсчет = cAcc AND дбкод = nId) OR (крсчет = cAcc AND кркод = nId)' INTO nCount;
				IF nCount > 0 THEN
					lError := TRUE;
					EXECUTE 'SELECT top 1 доккод FROM проводки WHERE (дбсчет = cAcc AND дбкод = nId) OR (крсчет = cAcc AND кркод = nId) ORDER BY доккод desc' INTO docId;
					EXECUTE 'SELECT top 1 опер FROM проводки WHERE (дбсчет = cAcc AND дбкод = nId) OR (крсчет = cAcc AND кркод = nId) ORDER BY доккод desc' INTO OperId;
					RAISE EXCEPTION 'Запрещено удалять запись, т.к. для нее были сделаны операции (% шт.). Последняя операция <> по документу номер <> была сделана <>.', nCount;
					EXIT;
				END IF;
			END IF;
		END LOOP;
		CLOSE curAccounts;
	END IF;

	IF lError THEN
		RETURN null;	-- ошибка, удалять нельзя
	ELSE
		RETURN OLD;	-- ошибки нет, можно удалять запись
	END IF;
END;
$$
    LANGUAGE plpgsql;


--------------------------------------------------------------------------------------------------------------------------------
CREATE FUNCTION tsvectorupdate() RETURNS trigger
    AS $$
BEGIN
	NEW.fts = totsvector(lower(replace(replace(replace(trim(NEW.имя) || ' ' || trim(NEW.шифр_по_каталогу), '-', ' '), ',', ' '), '.', ' ')));
	RETURN NEW;
END;
$$
    LANGUAGE plpgsql;


--------------------------------------------------------------------------------------------------------------------------------
CREATE FUNCTION вставитьпроводку() RETURNS trigger
    AS $$
BEGIN
	IF (SELECT считать FROM топер WHERE опер = NEW.опер AND номер = 1) = '1' THEN			-- если эту проводку учитывать
		IF char_length(NEW.дбсчет) > 0 AND (SELECT баланс FROM счета WHERE счет = NEW.дбсчет) = '1' THEN		-- если счет указан и это не забалансовый счет
			IF (SELECT count(*) FROM счета WHERE счет = NEW.дбсчет) = 0 THEN			-- если не существует такого счета
				INSERT INTO счета (счет) VALUEs (NEW.дбсчет);					-- то добавим его. название счета введет пользователь потом
			END IF;
			IF (SELECT count(*) FROM сальдо WHERE счет = NEW.дбсчет AND код = NEW.дбкод) = 0 THEN
				INSERT INTO сальдо (счет, код)  VALUEs (NEW.дбсчет, NEW.дбкод);
			END IF;
			UPDATE сальдо					-- ... а теперь новую
				SET дбкол = дбкол + NEW.кол, 
					дебет = дебет + NEW.сумма
				WHERE счет = NEW.дбсчет AND код = NEW.дбкод;
		END IF;
		IF char_length(NEW.крсчет) > 0 AND (SELECT баланс FROM счета WHERE счет = NEW.крсчет) = '1' THEN		-- если счет указан и это не забалансовый счет
			IF (SELECT count(*) FROM счета WHERE счет = NEW.крсчет) = 0 THEN			-- если не существует такого счета
				INSERT INTO счета (счет) VALUEs (NEW.крсчет);					-- то добавим его. название счета введет пользователь потом
			END IF;
			IF (SELECT count(*) FROM сальдо WHERE счет = NEW.крсчет AND код = NEW.кркод) = 0 THEN
				INSERT INTO сальдо (счет, код)  VALUEs (NEW.крсчет, NEW.кркод);
			END IF;
			UPDATE сальдо					-- ... а теперь новую
				SET кркол = кркол + NEW.кол, 
					кредит = кредит + NEW.сумма
				WHERE счет = NEW.крсчет AND код = NEW.кркод;
		END IF;
		RETURN NEW;
	ELSE
		RETURN null;
	END IF;
END;
$$
    LANGUAGE plpgsql;


--------------------------------------------------------------------------------------------------------------------------------
CREATE FUNCTION считатьконечноесальдо() RETURNS trigger
    AS $$
BEGIN
	NEW.конкол := NEW.кол + NEW.дбкол - NEW.кркол;
	NEW.консальдо := NEW.сальдо + NEW.дебет - NEW.кредит;
	IF NEW.конкол = 0 THEN
		NEW.концена := NEW.консальдо;
	ELSE
		NEW.концена := NEW.консальдо / NEW.конкол;
	END IF;
	RETURN NEW;
END;
$$
    LANGUAGE plpgsql;


--------------------------------------------------------------------------------------------------------------------------------
CREATE FUNCTION считатьпроводку() RETURNS trigger
    AS $$
BEGIN
	IF NOT (NEW.дбсчет = NEW.крсчет AND NEW.дбкод = NEW.кркод) THEN    -- если объект не замыкается сам на себя
		-- то, значит, проводка ссылается на разные объекты и можно обрабатывать счета раздельно по дебетовому и по кредитовому обороту

		-- cначала обработаем по дебетовому обороту	
		IF (OLD.дбсчет = NEW.дбсчет) AND (OLD.дбкод = NEW.дбкод) THEN	-- ссылка на кредитовый объект не изменилась
			UPDATE сальдо
				SET дбкол = дбкол - OLD.кол + NEW.кол, 
					дебет = дебет - OLD.сумма + NEW.сумма
				WHERE счет = OLD.дбсчет AND код = OLD.дбкод;
		ELSE
			UPDATE сальдо						-- сначала обработаем старый счет
				SET дбкол = дбкол - OLD.кол, 
					дебет = дебет - OLD.сумма
				WHERE счет = OLD.дбсчет AND код = OLD.дбкод;
			IF char_length(NEW.дбсчет) > 0 AND (SELECT баланс FROM счета WHERE счет = NEW.дбсчет) = '1' THEN	-- если счет указан и не забалансовый счет
				IF (SELECT count(*) FROM сальдо WHERE счет = NEW.дбсчет AND код = NEW.дбкод) = 0 THEN
					INSERT INTO сальдо (счет, код) VALUEs (NEW.дбсчет, NEW.дбкод);
				END IF;
				UPDATE сальдо
					SET дбкол = дбкол + NEW.кол, 
						дебет = дебет + NEW.сумма
					WHERE счет = NEW.дбсчет AND код = NEW.дбкод;
			END IF;
		END IF;

		-- таперь обработаем по кредитовому обороту	
		IF (OLD.крсчет = NEW.крсчет) AND (OLD.кркод = NEW.кркод) THEN	-- ссылка на кредитовый объект не изменилась
			UPDATE сальдо
			          SET кркол = кркол - OLD.кол + NEW.кол, 
				     кредит = кредит - OLD.сумма + NEW.сумма
				WHERE счет = OLD.крсчет AND код = OLD.кркод;
		ELSE
			UPDATE сальдо						-- сначала обработаем старый счет
				SET кркол = кркол - OLD.кол, 
					кредит = кредит - OLD.сумма
				WHERE счет = OLD.крсчет AND код = OLD.кркод;
			IF char_length(NEW.крсчет) > 0 AND (SELECT баланс FROM счета WHERE счет = NEW.крсчет) = '1' THEN	-- если счет указан и не забалансовый счет
				IF (SELECT count(*) FROM сальдо WHERE счет = NEW.крсчет AND код = NEW.кркод) = 0 THEN
					INSERT INTO сальдо (счет, код) VALUEs (NEW.крсчет, NEW.кркод);
				END IF;
				UPDATE сальдо
					SET кркол = кркол + NEW.кол, 
						кредит = кредит + NEW.сумма
					WHERE счет = NEW.крсчет AND код = NEW.кркод;
			END IF;
		END IF;
	END IF;
	RETURN NEW;
END;
$$
    LANGUAGE plpgsql;


--------------------------------------------------------------------------------------------------------------------------------
CREATE FUNCTION удалитьдокумент() RETURNS trigger
    AS $$
BEGIN
	DELETE FROM проводки WHERE доккод = OLD.код;
	RETURN OLD;
END;
$$
    LANGUAGE plpgsql;


--------------------------------------------------------------------------------------------------------------------------------
CREATE FUNCTION удалитьпроводку() RETURNS trigger
    AS $$
BEGIN
	IF (SELECT считать FROM топер WHERE опер = OLD.опер AND номер = 1) = '1' THEN				-- если эту проводку учитывать
		IF char_length(OLD.дбсчет) > 0 AND (SELECT баланс FROM счета WHERE счет = OLD.дбсчет) = '1' THEN		-- если счет указан и это не забалансовый счет
			UPDATE сальдо				
			          SET дбкол = дбкол - OLD.кол,
				     дебет = дебет - OLD.сумма
				WHERE счет = OLD.дбсчет AND код = OLD.дбкод;
		END IF;
		IF char_length(OLD.крсчет) > 0 AND (SELECT баланс FROM счета WHERE счет = OLD.крсчет) = '1' THEN		-- если счет указан и не забалансовый счет
			UPDATE сальдо
			          SET кркол = кркол - OLD.кол,
				     кредит = кредит - OLD.сумма
				WHERE счет = OLD.крсчет AND код = OLD.кркод;
		END IF;
	END IF;
	RETURN OLD;
END;
$$
    LANGUAGE plpgsql;


--------------------------------------------------------------------------------------------------------------------------------
CREATE TRIGGER testdeleting_сальдо
    BEFORE DELETE ON сальдо
    FOR EACH ROW
    EXECUTE PROCEDURE testdeleting_сальдо();

CREATE TRIGGER testdeleting_банки
    BEFORE DELETE ON банки
    FOR EACH ROW
    EXECUTE PROCEDURE testdeletingdictobject();

CREATE TRIGGER testdeleting_банковские_счета
    BEFORE DELETE ON банковские_счета
    FOR EACH ROW
    EXECUTE PROCEDURE testdeletingdictobject();

CREATE TRIGGER testdeleting_блокпериоды
    BEFORE DELETE ON блокпериоды
    FOR EACH ROW
    EXECUTE PROCEDURE testdeletingdictobject();

CREATE TRIGGER testdeleting_виды_расходов
    BEFORE DELETE ON виды_расходов
    FOR EACH ROW
    EXECUTE PROCEDURE testdeletingdictobject();

CREATE TRIGGER testdeleting_доступ
    BEFORE DELETE ON доступ
    FOR EACH ROW
    EXECUTE PROCEDURE testdeletingdictobject();

CREATE TRIGGER testdeleting_константы
    BEFORE DELETE ON константы
    FOR EACH ROW
    EXECUTE PROCEDURE testdeletingdictobject();

CREATE TRIGGER testdeleting_материалы
    BEFORE DELETE ON материалы
    FOR EACH ROW
    EXECUTE PROCEDURE testdeletingdictobject();

CREATE TRIGGER testdeleting_нумераторы
    BEFORE DELETE ON нумераторы
    FOR EACH ROW
    EXECUTE PROCEDURE testdeletingdictobject();

CREATE TRIGGER testdeleting_контрагенты
    BEFORE DELETE ON контрагенты
    FOR EACH ROW
    EXECUTE PROCEDURE testdeletingdictobject();

CREATE TRIGGER testdeleting_персонал
    BEFORE DELETE ON персонал
    FOR EACH ROW
    EXECUTE PROCEDURE testdeletingdictobject();

CREATE TRIGGER testdeleting_типыобъектов
    BEFORE DELETE ON типыобъектов
    FOR EACH ROW
    EXECUTE PROCEDURE testdeletingdictobject();

CREATE TRIGGER вставитьпроводку
    BEFORE INSERT ON проводки
    FOR EACH ROW
    EXECUTE PROCEDURE вставитьпроводку();

CREATE TRIGGER считатьконечноесальдо
    BEFORE INSERT OR UPDATE ON сальдо
    FOR EACH ROW
    EXECUTE PROCEDURE считатьконечноесальдо();

CREATE TRIGGER считатьпроводку
    BEFORE UPDATE ON проводки
    FOR EACH ROW
    EXECUTE PROCEDURE считатьпроводку();

CREATE TRIGGER удалитьдокумент
    BEFORE DELETE ON документы
    FOR EACH ROW
    EXECUTE PROCEDURE удалитьдокумент();

CREATE TRIGGER удалитьпроводку
    BEFORE DELETE ON проводки
    FOR EACH ROW
    EXECUTE PROCEDURE удалитьпроводку();

CREATE TRIGGER "tsvectorupdate_прайсы"
  BEFORE INSERT OR UPDATE
  ON "прайсы"
  FOR EACH ROW
  EXECUTE PROCEDURE tsvectorupdate();

--------------------------------------------------------------------------------------------------------------------------------
REVOKE ALL ON TABLE сальдо FROM PUBLIC;
GRANT SELECT,INSERT,UPDATE ON TABLE сальдо TO sa;
GRANT SELECT,INSERT,UPDATE ON TABLE сальдо TO bookkeeper;

REVOKE ALL ON TABLE виды_расходов FROM PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE виды_расходов TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE виды_расходов TO bookkeeper;

REVOKE ALL ON TABLE счета FROM PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE счета TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE счета TO bookkeeper;

REVOKE ALL ON TABLE vw_баланс FROM PUBLIC;
GRANT SELECT ON TABLE vw_баланс TO sa;
GRANT SELECT ON TABLE vw_баланс TO bookkeeper;

REVOKE ALL ON TABLE блокпериоды FROM PUBLIC;
GRANT SELECT,INSERT,UPDATE ON TABLE блокпериоды TO sa;
GRANT SELECT,UPDATE ON TABLE блокпериоды TO bookkeeper;

REVOKE ALL ON TABLE vw_пользователи FROM PUBLIC;
GRANT SELECT ON TABLE vw_пользователи TO sa;
GRANT SELECT ON TABLE vw_пользователи TO test;

REVOKE ALL ON TABLE vw_блокпериоды FROM PUBLIC;
GRANT SELECT ON TABLE vw_блокпериоды TO sa;
GRANT SELECT ON TABLE vw_блокпериоды TO bookkeeper;

REVOKE ALL ON TABLE контрагенты FROM PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE контрагенты TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE контрагенты TO bookkeeper;

REVOKE ALL ON TABLE vw_грузополучатели FROM PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE vw_грузополучатели TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE vw_грузополучатели TO bookkeeper;

REVOKE ALL ON TABLE документы FROM PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE документы TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE документы TO bookkeeper;

REVOKE ALL ON TABLE доступ FROM PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE доступ TO sa;

REVOKE ALL ON TABLE vw_журнал FROM PUBLIC;
GRANT ALL ON TABLE vw_журнал TO sa;

REVOKE ALL ON TABLE vw_контрагенты FROM PUBLIC;
GRANT ALL ON TABLE vw_контрагенты TO sa;
GRANT ALL ON TABLE vw_контрагенты TO bookkeeper;

REVOKE ALL ON TABLE vw_материалы FROM PUBLIC;
GRANT ALL ON TABLE vw_материалы TO sa;
GRANT ALL ON TABLE vw_материалы TO bookkeeper;

REVOKE ALL ON TABLE vw_номенклатура FROM PUBLIC;
GRANT ALL ON TABLE vw_номенклатура TO sa;
GRANT ALL ON TABLE vw_номенклатура TO bookkeeper;

REVOKE ALL ON TABLE проводки FROM PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE проводки TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE проводки TO bookkeeper;

REVOKE ALL ON TABLE справочники FROM PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE справочники TO sa;
GRANT SELECT ON TABLE справочники TO bookkeeper;

REVOKE ALL ON TABLE константы FROM PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE константы TO sa;

REVOKE ALL ON TABLE vw_константы FROM PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE vw_константы TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE vw_константы TO seller;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE vw_константы TO bookkeeper;

REVOKE ALL ON TABLE топер FROM PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE топер TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE топер TO bookkeeper;

REVOKE ALL ON TABLE vw_справочники_со_столбцами FROM PUBLIC;
GRANT SELECT ON TABLE vw_справочники_со_столбцами TO sa;
GRANT SELECT ON TABLE vw_справочники_со_столбцами TO bookkeeper;

REVOKE ALL ON TABLE столбцы FROM PUBLIC;
GRANT SELECT, INSERT, DELETE, UPDATE ON TABLE столбцы TO sa;
GRANT SELECT ON TABLE столбцы TO bookkeeper;

REVOKE ALL ON TABLE vw_столбцы FROM PUBLIC;
GRANT SELECT ON TABLE vw_столбцы TO sa;
GRANT SELECT ON TABLE vw_столбцы TO bookkeeper;

REVOKE ALL ON TABLE vw_топер FROM PUBLIC;
GRANT SELECT ON TABLE vw_топер TO sa;
GRANT SELECT ON TABLE vw_топер TO bookkeeper;

REVOKE ALL ON TABLE банки FROM PUBLIC;
GRANT SELECT,INSERT,UPDATE ON TABLE банки TO sa;
GRANT SELECT,INSERT,UPDATE ON TABLE банки TO bookkeeper;

REVOKE ALL ON TABLE банковские_счета FROM PUBLIC;
GRANT SELECT,INSERT,UPDATE ON TABLE банковские_счета TO sa;
GRANT SELECT,INSERT,UPDATE ON TABLE банковские_счета TO bookkeeper;

REVOKE ALL ON TABLE vw_доступ_к_оборотам FROM PUBLIC;
GRANT SELECT ON TABLE vw_доступ_к_оборотам TO PUBLIC;

REVOKE ALL ON TABLE vw_доступ_к_сальдо FROM PUBLIC;
GRANT SELECT ON TABLE vw_доступ_к_сальдо TO PUBLIC;

REVOKE ALL ON TABLE vw_доступ_к_справочникам FROM PUBLIC;
GRANT SELECT ON TABLE vw_доступ_к_справочникам TO PUBLIC;

REVOKE ALL ON TABLE vw_доступ_к_топер FROM PUBLIC;
GRANT SELECT ON TABLE vw_доступ_к_топер TO PUBLIC;

REVOKE ALL ON TABLE материалы FROM PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE материалы TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE материалы TO bookkeeper;

REVOKE ALL ON TABLE номенклатура FROM PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE номенклатура TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE номенклатура TO bookkeeper;

REVOKE ALL ON TABLE нумераторы FROM PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE нумераторы TO sa;
GRANT SELECT,UPDATE ON TABLE нумераторы TO bookkeeper;

REVOKE ALL ON TABLE персонал FROM PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE персонал TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE персонал TO bookkeeper;

REVOKE ALL ON TABLE предметы FROM PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE предметы TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE предметы TO bookkeeper;

REVOKE ALL ON TABLE типыобъектов FROM PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE типыобъектов TO sa;
GRANT SELECT ON TABLE типыобъектов TO bookkeeper;

REVOKE ALL ON TABLE прайсы FROM PUBLIC;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE прайсы TO sa;
GRANT SELECT ON TABLE прайсы TO bookkeeper;

GRANT SELECT, UPDATE, INSERT, DELETE ON TABLE файлы TO sa;
GRANT SELECT ON TABLE файлы TO public;

REVOKE ALL ON FUNCTION sp_calcaccoborot(cacc CHARACTER VARYING, cdate1 CHARACTER VARYING, cdate2 CHARACTER VARYING) FROM PUBLIC;
GRANT ALL ON FUNCTION sp_calcaccoborot(cacc CHARACTER VARYING, cdate1 CHARACTER VARYING, cdate2 CHARACTER VARYING) TO sa;
GRANT ALL ON FUNCTION sp_calcaccoborot(cacc CHARACTER VARYING, cdate1 CHARACTER VARYING, cdate2 CHARACTER VARYING) TO bookkeeper;

REVOKE ALL ON FUNCTION sp_calcdocoborot(cacc CHARACTER VARYING, cdate1 CHARACTER VARYING, cdate2 CHARACTER VARYING) FROM PUBLIC;
GRANT ALL ON FUNCTION sp_calcdocoborot(cacc CHARACTER VARYING, cdate1 CHARACTER VARYING, cdate2 CHARACTER VARYING) TO sa;
GRANT ALL ON FUNCTION sp_calcdocoborot(cacc CHARACTER VARYING, cdate1 CHARACTER VARYING, cdate2 CHARACTER VARYING) TO bookkeeper;

REVOKE ALL ON FUNCTION sp_calcobjoborot(cacc CHARACTER VARYING, pnobj INTEGER, cdate1 CHARACTER VARYING, cdate2 CHARACTER VARYING) FROM PUBLIC;
GRANT ALL ON FUNCTION sp_calcobjoborot(cacc CHARACTER VARYING, pnobj INTEGER, cdate1 CHARACTER VARYING, cdate2 CHARACTER VARYING) TO sa;
GRANT ALL ON FUNCTION sp_calcobjoborot(cacc CHARACTER VARYING, pnobj INTEGER, cdate1 CHARACTER VARYING, cdate2 CHARACTER VARYING) TO bookkeeper;

REVOKE ALL ON FUNCTION sp_calcoborot(cacc CHARACTER VARYING, cdate1 CHARACTER VARYING, cdate2 CHARACTER VARYING) FROM PUBLIC;
GRANT ALL ON FUNCTION sp_calcoborot(cacc CHARACTER VARYING, cdate1 CHARACTER VARYING, cdate2 CHARACTER VARYING) TO sa;
GRANT ALL ON FUNCTION sp_calcoborot(cacc CHARACTER VARYING, cdate1 CHARACTER VARYING, cdate2 CHARACTER VARYING) TO bookkeeper;

REVOKE ALL ON FUNCTION sp_calctotobjoborot(cacc CHARACTER VARYING, pcdictname CHARACTER VARYING, pnobj INTEGER, cdate1 CHARACTER VARYING, cdate2 CHARACTER VARYING) FROM PUBLIC;
GRANT ALL ON FUNCTION sp_calctotobjoborot(cacc CHARACTER VARYING, pcdictname CHARACTER VARYING, pnobj INTEGER, cdate1 CHARACTER VARYING, cdate2 CHARACTER VARYING) TO sa;
GRANT ALL ON FUNCTION sp_calctotobjoborot(cacc CHARACTER VARYING, pcdictname CHARACTER VARYING, pnobj INTEGER, cdate1 CHARACTER VARYING, cdate2 CHARACTER VARYING) TO bookkeeper;

REVOKE ALL ON FUNCTION sp_deletedoc(ndocId INTEGER) FROM PUBLIC;
GRANT ALL ON FUNCTION sp_deletedoc(ndocId INTEGER) TO sa;
GRANT ALL ON FUNCTION sp_deletedoc(ndocId INTEGER) TO bookkeeper;

REVOKE ALL ON FUNCTION sp_deletedocstr(ndocId INTEGER, ndocstr INTEGER) FROM PUBLIC;
GRANT ALL ON FUNCTION sp_deletedocstr(ndocId INTEGER, ndocstr INTEGER) TO sa;
GRANT ALL ON FUNCTION sp_deletedocstr(ndocId INTEGER, ndocstr INTEGER) TO bookkeeper;

REVOKE ALL ON FUNCTION sp_insertdoc(noper INTEGER, cdate CHARACTER VARYING) FROM PUBLIC;
GRANT ALL ON FUNCTION sp_insertdoc(noper INTEGER, cdate CHARACTER VARYING) TO sa;
GRANT ALL ON FUNCTION sp_insertdoc(noper INTEGER, cdate CHARACTER VARYING) TO bookkeeper;

REVOKE ALL ON FUNCTION sp_insertdocstr(noper INTEGER, ndocId INTEGER, pcparam CHARACTER VARYING, pncount INTEGER, pndocstr INTEGER) FROM PUBLIC;
GRANT ALL ON FUNCTION sp_insertdocstr(noper INTEGER, ndocId INTEGER, pcparam CHARACTER VARYING, pncount INTEGER, pndocstr INTEGER) TO sa;
GRANT ALL ON FUNCTION sp_insertdocstr(noper INTEGER, ndocId INTEGER, pcparam CHARACTER VARYING, pncount INTEGER, pndocstr INTEGER) TO bookkeeper;

REVOKE ALL ON FUNCTION sp_islockedperiod(cdate CHARACTER VARYING) FROM PUBLIC;
GRANT ALL ON FUNCTION sp_islockedperiod(cdate CHARACTER VARYING) TO sa;
GRANT ALL ON FUNCTION sp_islockedperiod(cdate CHARACTER VARYING) TO bookkeeper;

REVOKE ALL ON FUNCTION sp_maketotobjoborotcommand(cacc CHARACTER VARYING, pcdictname CHARACTER VARYING, pnobj INTEGER, cdate1 CHARACTER VARYING, cdate2 CHARACTER VARYING) FROM PUBLIC;
GRANT ALL ON FUNCTION sp_maketotobjoborotcommand(cacc CHARACTER VARYING, pcdictname CHARACTER VARYING, pnobj INTEGER, cdate1 CHARACTER VARYING, cdate2 CHARACTER VARYING) TO sa;
GRANT ALL ON FUNCTION sp_maketotobjoborotcommand(cacc CHARACTER VARYING, pcdictname CHARACTER VARYING, pnobj INTEGER, cdate1 CHARACTER VARYING, cdate2 CHARACTER VARYING) TO bookkeeper;












