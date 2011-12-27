--
-- PostgreSQL database dump
--

-- Dumped from database version 9.1.1
-- Dumped by pg_dump version 9.1.1
-- Started on 2011-12-27 09:10:55 MSK

SET statement_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;


DROP ROLE test;
CREATE ROLE test WITH NOSUPERUSER NOCREATEDB NOCREATEROLE LOGIN ENCRYPTED PASSWORD '*';
DROP ROLE sa;
CREATE ROLE sa WITH SUPERUSER CREATEDB CREATEROLE LOGIN ENCRYPTED PASSWORD '123456'; 
DROP ROLE bookkeeper;
CREATE ROLE bookkeeper WITH NOSUPERUSER NOCREATEDB NOCREATEROLE LOGIN ENCRYPTED PASSWORD '123';
DROP ROLE seller;
CREATE ROLE seller WITH NOSUPERUSER NOCREATEDB NOCREATEROLE LOGIN ENCRYPTED PASSWORD '123';

--
-- TOC entry 237 (class 3079 OID 12249)
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- TOC entry 2980 (class 0 OID 0)
-- Dependencies: 237
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

--
-- TOC entry 699 (class 1247 OID 20498)
-- Dependencies: 5 234
-- Name: sp_calcaccoborot_fret; Type: TYPE; Schema: public; Owner: sa
--

CREATE TYPE sp_calcaccoborot_fret AS (
	"дата" date,
	"оперномер" integer,
	"оперимя" character varying(100),
	"доккод" integer,
	"документ" character varying(20),
	"номер" character varying(10),
	"комментарий" character varying(100),
	"сумма" numeric(10,2),
	"дбсчет" character(5),
	"крсчет" character(5),
	"дебет" numeric(10,2),
	"кредит" numeric(10,2),
	"сдебет" character varying(15),
	"скредит" character varying(15)
);


ALTER TYPE public.sp_calcaccoborot_fret OWNER TO sa;

--
-- TOC entry 701 (class 1247 OID 20501)
-- Dependencies: 5 235
-- Name: sp_calcobjoborot_fret; Type: TYPE; Schema: public; Owner: sa
--

CREATE TYPE sp_calcobjoborot_fret AS (
	"дата" date,
	"оперномер" integer,
	"оперимя" character varying(100),
	"доккод" integer,
	"документ" character varying(20),
	"номер" character varying(10),
	"стр" integer,
	"комментарий" character varying(100),
	"сумма" numeric(10,2),
	"дбсчет" character(5),
	"крсчет" character(5),
	"дбкол" numeric(10,3),
	"дебет" numeric(10,2),
	"кркол" numeric(10,3),
	"кредит" numeric(10,2),
	"сдбкол" character varying(15),
	"сдебет" character varying(15),
	"скркол" character varying(15),
	"скредит" character varying(15)
);


ALTER TYPE public.sp_calcobjoborot_fret OWNER TO sa;

--
-- TOC entry 703 (class 1247 OID 20504)
-- Dependencies: 5 236
-- Name: sp_calcoborot_fret; Type: TYPE; Schema: public; Owner: sa
--

CREATE TYPE sp_calcoborot_fret AS (
	"код" integer,
	"кол" numeric(10,3),
	"сальдо" numeric(10,2),
	"дбкол" numeric(10,3),
	"дебет" numeric(10,2),
	"кркол" numeric(10,3),
	"кредит" numeric(10,2),
	"конкол" numeric(10,3),
	"консальдо" numeric(10,2),
	"cкол" character varying(15),
	"cсальдо" character varying(15),
	"cдбкол" character varying(15),
	"cдебет" character varying(15),
	"cкркол" character varying(15),
	"cкредит" character varying(15),
	"cконкол" character varying(15),
	"cконсальдо" character varying(15)
);


ALTER TYPE public.sp_calcoborot_fret OWNER TO sa;

--
-- TOC entry 263 (class 1255 OID 20505)
-- Dependencies: 705 699 5
-- Name: sp_calcaccoborot(character varying, character varying, character varying); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION sp_calcaccoborot(cacc character varying, cdate1 character varying, cdate2 character varying) RETURNS SETOF sp_calcaccoborot_fret
    LANGUAGE plpgsql
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
$$;


ALTER FUNCTION public.sp_calcaccoborot(cacc character varying, cdate1 character varying, cdate2 character varying) OWNER TO sa;

--
-- TOC entry 249 (class 1255 OID 20506)
-- Dependencies: 705 5
-- Name: sp_calcdocoborot(character varying, character varying, character varying); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION sp_calcdocoborot(cacc character varying, cdate1 character varying, cdate2 character varying) RETURNS void
    LANGUAGE plpgsql
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
$$;


ALTER FUNCTION public.sp_calcdocoborot(cacc character varying, cdate1 character varying, cdate2 character varying) OWNER TO sa;

--
-- TOC entry 264 (class 1255 OID 20507)
-- Dependencies: 701 705 5
-- Name: sp_calcobjoborot(character varying, integer, character varying, character varying); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION sp_calcobjoborot(cacc character varying, pnobj integer, cdate1 character varying, cdate2 character varying) RETURNS SETOF sp_calcobjoborot_fret
    LANGUAGE plpgsql
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
$$;


ALTER FUNCTION public.sp_calcobjoborot(cacc character varying, pnobj integer, cdate1 character varying, cdate2 character varying) OWNER TO sa;

--
-- TOC entry 265 (class 1255 OID 20508)
-- Dependencies: 703 705 5
-- Name: sp_calcoborot(character varying, character varying, character varying); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION sp_calcoborot(cacc character varying, cdate1 character varying, cdate2 character varying) RETURNS SETOF sp_calcoborot_fret
    LANGUAGE plpgsql
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
$$;


ALTER FUNCTION public.sp_calcoborot(cacc character varying, cdate1 character varying, cdate2 character varying) OWNER TO sa;

--
-- TOC entry 266 (class 1255 OID 20509)
-- Dependencies: 5 705
-- Name: sp_calctotobjoborot(character varying, character varying, integer, character varying, character varying); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION sp_calctotobjoborot(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) RETURNS void
    LANGUAGE plpgsql
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
$$;


ALTER FUNCTION public.sp_calctotobjoborot(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) OWNER TO sa;

--
-- TOC entry 251 (class 1255 OID 20510)
-- Dependencies: 705 5
-- Name: sp_deletedoc(integer); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION sp_deletedoc(ndocid integer) RETURNS void
    LANGUAGE plpgsql
    AS $$
BEGIN
	DELETE FROM документы WHERE код = nDocId;
	DELETE FROM проводки WHERE доккод = nDocId;
END;
$$;


ALTER FUNCTION public.sp_deletedoc(ndocid integer) OWNER TO sa;

--
-- TOC entry 254 (class 1255 OID 20511)
-- Dependencies: 5 705
-- Name: sp_deletedocstr(integer, integer); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION sp_deletedocstr(ndocid integer, ndocstr integer) RETURNS void
    LANGUAGE plpgsql
    AS $$
BEGIN
	DELETE FROM проводки WHERE доккод = nDocId AND стр = nDocStr;
END;
$$;


ALTER FUNCTION public.sp_deletedocstr(ndocid integer, ndocstr integer) OWNER TO sa;

--
-- TOC entry 267 (class 1255 OID 20512)
-- Dependencies: 705 5
-- Name: sp_insertdoc(integer, character varying); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION sp_insertdoc(noper integer, cdate character varying) RETURNS character varying
    LANGUAGE plpgsql
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
$$;


ALTER FUNCTION public.sp_insertdoc(noper integer, cdate character varying) OWNER TO sa;

--
-- TOC entry 252 (class 1255 OID 20513)
-- Dependencies: 5 705
-- Name: sp_insertdocstr(integer, integer, character varying, integer, integer); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION sp_insertdocstr(noper integer, ndocid integer, pcparam character varying, pncount integer, pndocstr integer) RETURNS void
    LANGUAGE plpgsql
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
$$;


ALTER FUNCTION public.sp_insertdocstr(noper integer, ndocid integer, pcparam character varying, pncount integer, pndocstr integer) OWNER TO sa;

--
-- TOC entry 253 (class 1255 OID 20514)
-- Dependencies: 5 705
-- Name: sp_islockedperiod(character varying); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION sp_islockedperiod(cdate character varying) RETURNS void
    LANGUAGE plpgsql
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
$$;


ALTER FUNCTION public.sp_islockedperiod(cdate character varying) OWNER TO sa;

--
-- TOC entry 268 (class 1255 OID 20515)
-- Dependencies: 705 5
-- Name: sp_maketotobjoborotcommand(character varying, character varying, integer, character varying, character varying); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION sp_maketotobjoborotcommand(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) RETURNS character varying
    LANGUAGE plpgsql
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
$$;


ALTER FUNCTION public.sp_maketotobjoborotcommand(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) OWNER TO sa;

--
-- TOC entry 255 (class 1255 OID 20516)
-- Dependencies: 705 5
-- Name: testdeleting_сальдо(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION "testdeleting_сальдо"() RETURNS trigger
    LANGUAGE plpgsql
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
$$;


ALTER FUNCTION public."testdeleting_сальдо"() OWNER TO sa;

--
-- TOC entry 256 (class 1255 OID 20517)
-- Dependencies: 705 5
-- Name: testdeletingdictobject(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION testdeletingdictobject() RETURNS trigger
    LANGUAGE plpgsql
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
$$;


ALTER FUNCTION public.testdeletingdictobject() OWNER TO sa;

--
-- TOC entry 257 (class 1255 OID 20518)
-- Dependencies: 705 5
-- Name: testdeletingtoperobject(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION testdeletingtoperobject() RETURNS trigger
    LANGUAGE plpgsql
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
$$;


ALTER FUNCTION public.testdeletingtoperobject() OWNER TO sa;

--
-- TOC entry 258 (class 1255 OID 20519)
-- Dependencies: 5 705
-- Name: tsvectorupdate(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION tsvectorupdate() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	NEW.fts = totsvector(lower(replace(replace(replace(trim(NEW.имя) || ' ' || trim(NEW.шифр_по_каталогу), '-', ' '), ',', ' '), '.', ' ')));
	RETURN NEW;
END;
$$;


ALTER FUNCTION public.tsvectorupdate() OWNER TO sa;

--
-- TOC entry 259 (class 1255 OID 20520)
-- Dependencies: 5 705
-- Name: вставитьпроводку(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION "вставитьпроводку"() RETURNS trigger
    LANGUAGE plpgsql
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
$$;


ALTER FUNCTION public."вставитьпроводку"() OWNER TO sa;

--
-- TOC entry 260 (class 1255 OID 20521)
-- Dependencies: 5 705
-- Name: считатьконечноесальдо(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION "считатьконечноесальдо"() RETURNS trigger
    LANGUAGE plpgsql
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
$$;


ALTER FUNCTION public."считатьконечноесальдо"() OWNER TO sa;

--
-- TOC entry 250 (class 1255 OID 20522)
-- Dependencies: 705 5
-- Name: считатьпроводку(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION "считатьпроводку"() RETURNS trigger
    LANGUAGE plpgsql
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
$$;


ALTER FUNCTION public."считатьпроводку"() OWNER TO sa;

--
-- TOC entry 261 (class 1255 OID 20523)
-- Dependencies: 5 705
-- Name: удалитьдокумент(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION "удалитьдокумент"() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	DELETE FROM проводки WHERE доккод = OLD.код;
	RETURN OLD;
END;
$$;


ALTER FUNCTION public."удалитьдокумент"() OWNER TO sa;

--
-- TOC entry 262 (class 1255 OID 20524)
-- Dependencies: 5 705
-- Name: удалитьпроводку(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION "удалитьпроводку"() RETURNS trigger
    LANGUAGE plpgsql
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
$$;


ALTER FUNCTION public."удалитьпроводку"() OWNER TO sa;

--
-- TOC entry 214 (class 1259 OID 20411)
-- Dependencies: 2674 5
-- Name: vw_tables; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW vw_tables AS
    SELECT pg_tables.tablename AS name, 'table'::text AS type FROM pg_tables UNION SELECT pg_views.viewname AS name, 'view'::text AS type FROM pg_views;


ALTER TABLE public.vw_tables OWNER TO sa;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- TOC entry 167 (class 1259 OID 20043)
-- Dependencies: 2700 2701 2702 2703 2704 2705 2706 2707 2708 5
-- Name: сальдо; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "сальдо" (
    "счет" character(5) NOT NULL,
    "код" integer NOT NULL,
    "кол" numeric(10,3) DEFAULT 0,
    "сальдо" numeric(14,2) DEFAULT 0,
    "дбкол" numeric(10,3) DEFAULT 0,
    "дебет" numeric(14,2) DEFAULT 0,
    "кркол" numeric(10,3) DEFAULT 0,
    "кредит" numeric(14,2) DEFAULT 0,
    "конкол" numeric(10,3) DEFAULT 0,
    "консальдо" numeric(14,2) DEFAULT 0,
    "концена" numeric(14,2) DEFAULT 0
);


ALTER TABLE public."сальдо" OWNER TO sa;

--
-- TOC entry 165 (class 1259 OID 20028)
-- Dependencies: 2694 2695 2696 2697 2698 5
-- Name: счета; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "счета" (
    "код" integer NOT NULL,
    "имя" character varying(200) DEFAULT ''::character varying,
    "счет" character(5) DEFAULT ''::bpchar,
    "имясправочника" character varying(50) DEFAULT ''::character varying,
    "баланс" boolean DEFAULT true,
    "количество" boolean DEFAULT false
);


ALTER TABLE public."счета" OWNER TO sa;

--
-- TOC entry 221 (class 1259 OID 20440)
-- Dependencies: 2681 5
-- Name: vw_баланс; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_баланс" AS
    SELECT DISTINCT "счета"."код", "счета"."счет", "счета"."имя", COALESCE("дбсальдо"."дбконсальдо", (0)::numeric) AS "дбконсальдо", COALESCE("крсальдо"."крконсальдо", (0)::numeric) AS "крконсальдо" FROM (("счета" LEFT JOIN (SELECT DISTINCT "сальдо"."счет", sum("сальдо"."консальдо") AS "дбконсальдо" FROM "сальдо" WHERE (("сальдо"."консальдо" > (0)::numeric) AND (substr(("сальдо"."счет")::text, 1, 2) <> '00'::text)) GROUP BY "сальдо"."счет" ORDER BY "сальдо"."счет", sum("сальдо"."консальдо")) "дбсальдо" ON (("счета"."счет" = "дбсальдо"."счет"))) LEFT JOIN (SELECT DISTINCT "сальдо"."счет", (- sum("сальдо"."консальдо")) AS "крконсальдо" FROM "сальдо" WHERE (("сальдо"."консальдо" < (0)::numeric) AND (substr(("сальдо"."счет")::text, 1, 2) <> '00'::text)) GROUP BY "сальдо"."счет" ORDER BY "сальдо"."счет", (- sum("сальдо"."консальдо"))) "крсальдо" ON (("счета"."счет" = "крсальдо"."счет"))) ORDER BY "счета"."код", "счета"."счет", "счета"."имя", COALESCE("дбсальдо"."дбконсальдо", (0)::numeric), COALESCE("крсальдо"."крконсальдо", (0)::numeric);


ALTER TABLE public."vw_баланс" OWNER TO sa;

--
-- TOC entry 196 (class 1259 OID 20285)
-- Dependencies: 2793 2794 2795 2796 5
-- Name: блокпериоды; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "блокпериоды" (
    "код" integer NOT NULL,
    "имя" character varying(100) DEFAULT ''::character varying,
    "блокконец" date,
    "начало" date DEFAULT (('now'::text)::date - 30) NOT NULL,
    "конец" date DEFAULT ('now'::text)::date NOT NULL,
    "пользователь" character varying(30) DEFAULT "current_user"()
);


ALTER TABLE public."блокпериоды" OWNER TO sa;

--
-- TOC entry 218 (class 1259 OID 20428)
-- Dependencies: 2678 5
-- Name: vw_блокпериоды; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_блокпериоды" AS
    SELECT b."код", b."имя", b."блокконец", b."начало", b."конец" FROM "блокпериоды" b WHERE (lower(btrim((b."пользователь")::text)) = lower(("current_user"())::text));


ALTER TABLE public."vw_блокпериоды" OWNER TO sa;

--
-- TOC entry 180 (class 1259 OID 20163)
-- Dependencies: 2749 2750 2751 2752 2753 2754 2755 2756 2757 2758 2759 2760 5
-- Name: контрагенты; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "контрагенты" (
    "код" integer NOT NULL,
    "имя" character varying(200) DEFAULT ''::character varying,
    "адрес" character varying(100) DEFAULT ''::character varying,
    "телефон" character varying(100) DEFAULT ''::character varying,
    e_mail character varying(50) DEFAULT ''::character varying,
    "руководитель" character varying(50) DEFAULT ''::character varying,
    "гл_бухгалтер" character varying(50) DEFAULT ''::character varying,
    "инн" character varying(12) DEFAULT ''::character varying,
    "кпп" character varying(9) DEFAULT ''::character varying,
    "оконх" character varying(15) DEFAULT ''::character varying,
    "окпо" character varying(10) DEFAULT ''::character varying,
    "счет" character varying(20) DEFAULT ''::character varying,
    "код_банки" integer,
    "лимит" numeric(14,2) DEFAULT 0,
    "код_vw_грузополучатели" integer
);


ALTER TABLE public."контрагенты" OWNER TO sa;

--
-- TOC entry 224 (class 1259 OID 20454)
-- Dependencies: 2684 5
-- Name: vw_грузополучатели; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_грузополучатели" AS
    SELECT "контрагенты"."код", "контрагенты"."имя", "контрагенты"."адрес", "контрагенты"."телефон", "контрагенты".e_mail, "контрагенты"."руководитель", "контрагенты"."гл_бухгалтер", "контрагенты"."инн", "контрагенты"."кпп", "контрагенты"."оконх", "контрагенты"."окпо", "контрагенты"."счет", "контрагенты"."код_банки", "контрагенты"."лимит", "контрагенты"."код_vw_грузополучатели" FROM "контрагенты";


ALTER TABLE public."vw_грузополучатели" OWNER TO sa;

--
-- TOC entry 168 (class 1259 OID 20056)
-- Dependencies: 2709 2710 2711 5
-- Name: документы; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "документы" (
    "код" integer NOT NULL,
    "дата" date,
    "датавремя" timestamp without time zone,
    "номер" character varying(10) DEFAULT ''::character varying,
    "комментарий" character varying(100) DEFAULT ''::character varying,
    "сумма" numeric(14,2) DEFAULT 0,
    "описание" text,
    "опер" integer,
    "авто" integer,
    "переменные" bytea
);


ALTER TABLE public."документы" OWNER TO sa;

--
-- TOC entry 220 (class 1259 OID 20436)
-- Dependencies: 2680 5
-- Name: vw_документы; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_документы" AS
    SELECT d."код", d."дата", d."датавремя", d."номер", d."комментарий", d."сумма", d."опер", d."авто", d."описание" FROM ("документы" d JOIN "vw_блокпериоды" b ON (((d."дата" > (b."начало" - 1)) AND (d."дата" < (b."конец" + 1)))));


ALTER TABLE public."vw_документы" OWNER TO sa;

--
-- TOC entry 217 (class 1259 OID 20424)
-- Dependencies: 2677 5
-- Name: vw_пользователи; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_пользователи" AS
    SELECT pg_user.usesysid AS "код", pg_user.usename AS "имя" FROM pg_user WHERE ((pg_user.usename <> 'test'::name) AND (pg_user.usename <> 'postgres'::name));


ALTER TABLE public."vw_пользователи" OWNER TO sa;

--
-- TOC entry 198 (class 1259 OID 20299)
-- Dependencies: 2798 2799 2800 2801 2802 5
-- Name: доступ; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "доступ" (
    "код" integer NOT NULL,
    "меню" boolean DEFAULT true,
    "комментарий" character varying(100) DEFAULT ''::character varying,
    "код_типыобъектов" integer,
    "пользователь" character varying(30) DEFAULT ''::character varying,
    "имя" character varying(100) DEFAULT ''::character varying,
    "доступ" character varying(30) DEFAULT ''::character varying
);


ALTER TABLE public."доступ" OWNER TO sa;

--
-- TOC entry 225 (class 1259 OID 20458)
-- Dependencies: 2685 5
-- Name: vw_доступ; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_доступ" AS
    (SELECT s."имя", s."код_типыобъектов", s."меню", has_table_privilege(s."имя", 'select'::text) AS selectable, CASE WHEN (s.type = 'table'::text) THEN has_table_privilege(s."имя", 'insert'::text) ELSE false END AS insertable, CASE WHEN (s.type = 'table'::text) THEN has_table_privilege(s."имя", 'delete'::text) ELSE false END AS deleteable, CASE WHEN (s.type = 'table'::text) THEN has_table_privilege(s."имя", 'update'::text) ELSE false END AS updateable FROM (SELECT DISTINCT s."имя", s."код_типыобъектов", s."меню", s.type FROM (SELECT rtrim((d."имя")::text) AS "имя", d."код_типыобъектов", d."меню", t.type FROM (("доступ" d JOIN "vw_пользователи" p ON (((rtrim((d."пользователь")::text) = rtrim((p."имя")::text)) OR (rtrim((d."пользователь")::text) = '*'::text)))) JOIN vw_tables t ON ((rtrim((d."имя")::text) = rtrim((t.name)::text)))) WHERE ((upper(rtrim((p."имя")::text)) = upper(rtrim(("current_user"())::text))) OR (btrim(("current_user"())::text) = 'sa'::text))) s ORDER BY s."имя", s."код_типыобъектов", s."меню") s UNION SELECT 'проводки'::text AS "имя", 1 AS "код_типыобъектов", false AS "меню", has_table_privilege('проводки'::text, 'select'::text) AS selectable, has_table_privilege('проводки'::text, 'insert'::text) AS insertable, has_table_privilege('проводки'::text, 'delete'::text) AS deleteable, has_table_privilege('проводки'::text, 'update'::text) AS updateable) UNION SELECT rtrim((d."имя")::text) AS "имя", d."код_типыобъектов", d."меню", true AS selectable, true AS insertable, true AS deleteable, true AS updateable FROM ("доступ" d JOIN "vw_пользователи" p ON (((rtrim((d."пользователь")::text) = rtrim((p."имя")::text)) AND (d."код_типыобъектов" <> 1)))) WHERE ((upper(rtrim((p."имя")::text)) = upper(rtrim(("current_user"())::text))) OR (btrim(("current_user"())::text) = 'sa'::text));


ALTER TABLE public."vw_доступ" OWNER TO sa;

--
-- TOC entry 226 (class 1259 OID 20463)
-- Dependencies: 2686 5
-- Name: vw_доступ_к_оборотам; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_доступ_к_оборотам" AS
    SELECT DISTINCT "счета"."имя", "счета"."счет" FROM ("счета" LEFT JOIN "vw_доступ" ON ((("счета"."счет")::text = "vw_доступ"."имя"))) WHERE ("vw_доступ"."код_типыобъектов" = 4) ORDER BY "счета"."имя", "счета"."счет";


ALTER TABLE public."vw_доступ_к_оборотам" OWNER TO sa;

--
-- TOC entry 227 (class 1259 OID 20467)
-- Dependencies: 2687 5
-- Name: vw_доступ_к_сальдо; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_доступ_к_сальдо" AS
    SELECT DISTINCT "счета"."имя", "счета"."счет" FROM ("счета" JOIN "vw_доступ" ON ((rtrim(("счета"."счет")::text) = rtrim("vw_доступ"."имя")))) WHERE ("vw_доступ"."код_типыобъектов" = 2) ORDER BY "счета"."имя", "счета"."счет";


ALTER TABLE public."vw_доступ_к_сальдо" OWNER TO sa;

--
-- TOC entry 202 (class 1259 OID 20324)
-- Dependencies: 2807 2808 2809 2810 2811 5
-- Name: справочники; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "справочники" (
    "код" integer NOT NULL,
    "имя" character varying(100) DEFAULT ''::character varying,
    "имя_в_списке" character varying(100) DEFAULT ''::character varying,
    "имя_в_форме" character varying(100) DEFAULT ''::character varying,
    "форма" character varying(50) DEFAULT ''::character varying,
    "преформулы" text,
    "формулы" text,
    "постформулы" text,
    "фото" character varying(100) DEFAULT ''::character varying
);


ALTER TABLE public."справочники" OWNER TO sa;

--
-- TOC entry 228 (class 1259 OID 20471)
-- Dependencies: 2688 5
-- Name: vw_доступ_к_справочникам; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_доступ_к_справочникам" AS
    SELECT s."имя_в_списке" AS "имя", s."имя_в_форме", d."имя" AS "таблица", d."меню", d.selectable, d.insertable, d.deleteable, d.updateable FROM ("vw_доступ" d LEFT JOIN "справочники" s ON ((upper(rtrim(d."имя")) = upper(rtrim((s."имя")::text))))) WHERE (d."код_типыобъектов" = 1) ORDER BY s."имя_в_списке";


ALTER TABLE public."vw_доступ_к_справочникам" OWNER TO sa;

--
-- TOC entry 174 (class 1259 OID 20106)
-- Dependencies: 2720 2721 2722 2723 2724 2725 2726 2727 2728 2729 2730 2731 2732 2733 2734 2735 2736 2737 2738 2739 5
-- Name: топер; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "топер" (
    "код" integer NOT NULL,
    "опер" integer,
    "номер" integer,
    "дбсчет" character varying(5) DEFAULT ''::character varying,
    "крсчет" character varying(5) DEFAULT ''::character varying,
    "имя" character varying(100) DEFAULT ''::character varying,
    "итоги" character varying(1) DEFAULT ''::character varying,
    "осндокумент" character varying(20) DEFAULT ''::character varying,
    "нумератор" character varying(40) DEFAULT ''::character varying,
    "однаоперация" boolean,
    "кол" boolean DEFAULT false,
    "дбпост" boolean DEFAULT false,
    "крпост" boolean DEFAULT false,
    "дбдобав" boolean DEFAULT false,
    "крдобав" boolean DEFAULT false,
    "дбвыбор" boolean DEFAULT false,
    "крвыбор" boolean DEFAULT false,
    "дбсалвидим" boolean DEFAULT true,
    "крсалвидим" boolean DEFAULT true,
    "дбвидим" boolean DEFAULT true,
    "крвидим" boolean DEFAULT true,
    "форма" character varying(50) DEFAULT ''::character varying,
    "независим" boolean DEFAULT false,
    "считать" boolean DEFAULT true,
    "переменные" text
);


ALTER TABLE public."топер" OWNER TO sa;

--
-- TOC entry 229 (class 1259 OID 20475)
-- Dependencies: 2689 5
-- Name: vw_доступ_к_топер; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_доступ_к_топер" AS
    SELECT DISTINCT "топер"."имя", s."меню", "топер"."опер", "топер"."форма", "топер"."независим", s.selectable, s.insertable, s.deleteable, s.updateable FROM ("топер" JOIN (SELECT "vw_доступ"."имя", "vw_доступ"."код_типыобъектов", "vw_доступ"."меню", "vw_доступ".selectable, "vw_доступ".insertable, "vw_доступ".deleteable, "vw_доступ".updateable FROM "vw_доступ" WHERE ("vw_доступ"."код_типыобъектов" = 3)) s ON ((rtrim(("топер"."опер")::text) = rtrim(s."имя")))) WHERE (("топер"."номер" = 1) AND (s."меню" = true)) ORDER BY "топер"."имя", s."меню", "топер"."опер", "топер"."форма", "топер"."независим";


ALTER TABLE public."vw_доступ_к_топер" OWNER TO sa;

--
-- TOC entry 200 (class 1259 OID 20314)
-- Dependencies: 2804 2805 5
-- Name: журнал; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "журнал" (
    "код" integer NOT NULL,
    "имя" character varying(20) DEFAULT ''::character varying,
    "датавремя" timestamp without time zone,
    "содержание" character varying(200) DEFAULT ''::character varying,
    "код_номенклатура" integer,
    "дата" date
);


ALTER TABLE public."журнал" OWNER TO sa;

--
-- TOC entry 230 (class 1259 OID 20480)
-- Dependencies: 2690 5
-- Name: vw_журнал; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_журнал" AS
    SELECT "журнал"."код", "журнал"."содержание" AS "имя", "журнал"."дата", "журнал"."код_номенклатура" FROM "журнал" ORDER BY "журнал"."датавремя" DESC, "журнал"."содержание";


ALTER TABLE public."vw_журнал" OWNER TO sa;

--
-- TOC entry 172 (class 1259 OID 20094)
-- Dependencies: 2717 2718 5
-- Name: константы; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "константы" (
    "код" integer NOT NULL,
    "имя" character varying(100) DEFAULT ''::character varying,
    "значение" character varying(200) DEFAULT ''::character varying,
    "комментарий" character varying(100)
);


ALTER TABLE public."константы" OWNER TO sa;

--
-- TOC entry 219 (class 1259 OID 20432)
-- Dependencies: 2679 5
-- Name: vw_константы; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_константы" AS
    SELECT "константы"."код", "константы"."имя", "константы"."значение", "константы"."комментарий" FROM "константы";


ALTER TABLE public."vw_константы" OWNER TO sa;

--
-- TOC entry 231 (class 1259 OID 20484)
-- Dependencies: 2691 5
-- Name: vw_контрагенты; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_контрагенты" AS
    SELECT "контрагенты"."код", "контрагенты"."имя", "контрагенты"."адрес", "контрагенты"."телефон", "контрагенты".e_mail, "контрагенты"."руководитель", "контрагенты"."гл_бухгалтер", "контрагенты"."инн", "контрагенты"."кпп", "контрагенты"."оконх", "контрагенты"."окпо", "контрагенты"."счет", "контрагенты"."код_банки", "контрагенты"."лимит", "контрагенты"."код_vw_грузополучатели" FROM "контрагенты";


ALTER TABLE public."vw_контрагенты" OWNER TO sa;

--
-- TOC entry 182 (class 1259 OID 20188)
-- Dependencies: 2762 2763 5
-- Name: материалы; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "материалы" (
    "код" integer NOT NULL,
    "имя" character varying(100) DEFAULT ''::character varying,
    "едизм" character varying(5) DEFAULT ''::character varying
);


ALTER TABLE public."материалы" OWNER TO sa;

--
-- TOC entry 233 (class 1259 OID 20492)
-- Dependencies: 2693 5
-- Name: vw_материалы; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_материалы" AS
    SELECT "материалы"."код", "материалы"."имя", "материалы"."едизм" FROM "материалы";


ALTER TABLE public."vw_материалы" OWNER TO sa;

--
-- TOC entry 184 (class 1259 OID 20200)
-- Dependencies: 2765 2766 2767 2768 2769 2770 2771 5
-- Name: номенклатура; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "номенклатура" (
    "код" integer NOT NULL,
    "имя" character varying(100) DEFAULT ''::character varying,
    "едизм" character varying(10) DEFAULT ''::character varying,
    "артикул" character varying(25) DEFAULT ''::character varying,
    "код_группы" integer,
    "цена_розн" numeric(10,2) DEFAULT 0,
    "запас" numeric(5,0) DEFAULT 0,
    "имя_на_ценнике" character varying(80) DEFAULT ''::character varying,
    "тип_ценника" integer DEFAULT 3,
    fts tsvector
);


ALTER TABLE public."номенклатура" OWNER TO sa;

--
-- TOC entry 232 (class 1259 OID 20488)
-- Dependencies: 2692 5
-- Name: vw_номенклатура; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_номенклатура" AS
    SELECT "номенклатура"."код", "номенклатура"."имя", "номенклатура"."едизм", "номенклатура"."артикул", "номенклатура"."код_группы", "номенклатура"."цена_розн", "номенклатура"."запас", "номенклатура"."имя_на_ценнике", "номенклатура"."тип_ценника", "номенклатура".fts FROM "номенклатура";


ALTER TABLE public."vw_номенклатура" OWNER TO sa;

--
-- TOC entry 170 (class 1259 OID 20074)
-- Dependencies: 2713 2714 2715 5
-- Name: проводки; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "проводки" (
    "код" integer NOT NULL,
    "дбсчет" character(5) NOT NULL,
    "дбкод" integer NOT NULL,
    "крсчет" character(5) NOT NULL,
    "кркод" integer NOT NULL,
    "кол" numeric(10,3) DEFAULT 0,
    "цена" numeric(14,2) DEFAULT 0,
    "сумма" numeric(14,2) DEFAULT 0,
    "стр" integer NOT NULL,
    "доккод" integer NOT NULL,
    "опер" numeric(3,0) NOT NULL,
    "номеропер" numeric(1,0) NOT NULL
);


ALTER TABLE public."проводки" OWNER TO sa;

--
-- TOC entry 222 (class 1259 OID 20445)
-- Dependencies: 2682 5
-- Name: vw_проводки; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_проводки" AS
    SELECT "проводки"."код", "проводки"."дбсчет", "проводки"."дбкод", "проводки"."крсчет", "проводки"."кркод", "проводки"."кол", "проводки"."цена", "проводки"."сумма", "проводки"."стр", "проводки"."доккод", "проводки"."опер", "проводки"."номеропер" FROM "проводки" WHERE ("проводки"."доккод" IN (SELECT "vw_документы"."код" FROM "vw_документы"));


ALTER TABLE public."vw_проводки" OWNER TO sa;

--
-- TOC entry 215 (class 1259 OID 20415)
-- Dependencies: 2675 5
-- Name: vw_справочники_со_столбцами; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_справочники_со_столбцами" AS
    (SELECT s."код", s."имя" FROM "справочники" s UNION SELECT (1000000 + "топер"."опер") AS "код", ('СписокДокументов'::text || btrim((("топер"."опер")::character varying(20))::text)) AS "имя" FROM "топер" WHERE ("топер"."номер" = 1)) UNION SELECT (2000000 + "топер"."опер") AS "код", ('Документ'::text || btrim((("топер"."опер")::character varying(20))::text)) AS "имя" FROM "топер" WHERE ("топер"."номер" = 1);


ALTER TABLE public."vw_справочники_со_столбцами" OWNER TO sa;

--
-- TOC entry 208 (class 1259 OID 20360)
-- Dependencies: 2817 2818 5
-- Name: столбцы; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "столбцы" (
    "код" integer NOT NULL,
    "код_vw_справочники_со_столбцами" integer,
    "имя" character varying(100) DEFAULT ''::character varying,
    "заголовок" character varying(100) DEFAULT ''::character varying,
    "номер" numeric(3,0)
);


ALTER TABLE public."столбцы" OWNER TO sa;

--
-- TOC entry 216 (class 1259 OID 20420)
-- Dependencies: 2676 5
-- Name: vw_столбцы; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_столбцы" AS
    SELECT d."имя" AS "справочник", s."имя" AS "столбец", s."заголовок", s."номер" FROM ("столбцы" s JOIN "vw_справочники_со_столбцами" d ON ((s."код_vw_справочники_со_столбцами" = d."код"))) ORDER BY d."имя", s."номер";


ALTER TABLE public."vw_столбцы" OWNER TO sa;

--
-- TOC entry 223 (class 1259 OID 20449)
-- Dependencies: 2683 5
-- Name: vw_топер; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_топер" AS
    SELECT "топер"."код", "топер"."опер", "топер"."номер", "топер"."имя", "счета"."счет" AS "дбсчет", "счета"."имясправочника" AS "дбсправ", '                                        '::bpchar AS "дбсправалиас", "счета"."количество" AS "дбкол", "топер"."дбпост", "топер"."дбсалвидим", "топер"."дбвидим", "счета1"."счет" AS "крсчет", "счета1"."имясправочника" AS "крсправ", '                                        '::bpchar AS "крсправалиас", "счета1"."количество" AS "кркол", "топер"."однаоперация", "топер"."итоги", "топер"."крпост", "топер"."крсалвидим", "топер"."крвидим", "топер"."независим", "топер"."считать", "топер"."переменные" FROM (("топер" LEFT JOIN "счета" "счета" ON ((("топер"."дбсчет")::bpchar = "счета"."счет"))) LEFT JOIN "счета" "счета1" ON ((("топер"."крсчет")::bpchar = "счета1"."счет")));


ALTER TABLE public."vw_топер" OWNER TO sa;

--
-- TOC entry 176 (class 1259 OID 20137)
-- Dependencies: 2741 2742 2743 2744 5
-- Name: банки; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "банки" (
    "код" integer NOT NULL,
    "имя" character varying(100) DEFAULT ''::character varying,
    "бик" character varying(9) DEFAULT ''::character varying,
    "корсчет" character varying(9) DEFAULT ''::character varying,
    "счет" character varying(20) DEFAULT ''::character varying
);


ALTER TABLE public."банки" OWNER TO sa;

--
-- TOC entry 177 (class 1259 OID 20146)
-- Dependencies: 5 176
-- Name: банки_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "банки_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."банки_код_seq" OWNER TO sa;

--
-- TOC entry 3022 (class 0 OID 0)
-- Dependencies: 177
-- Name: банки_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "банки_код_seq" OWNED BY "банки"."код";


--
-- TOC entry 3023 (class 0 OID 0)
-- Dependencies: 177
-- Name: банки_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"банки_код_seq"', 1, false);


--
-- TOC entry 178 (class 1259 OID 20151)
-- Dependencies: 2746 2747 5
-- Name: банковские_счета; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "банковские_счета" (
    "код" integer NOT NULL,
    "имя" character varying(100) DEFAULT ''::character varying,
    "счет" character varying(20) DEFAULT ''::character varying,
    "код_банки" integer
);


ALTER TABLE public."банковские_счета" OWNER TO sa;

--
-- TOC entry 179 (class 1259 OID 20158)
-- Dependencies: 5 178
-- Name: банковские_счета_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "банковские_счета_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."банковские_счета_код_seq" OWNER TO sa;

--
-- TOC entry 3025 (class 0 OID 0)
-- Dependencies: 179
-- Name: банковские_счета_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "банковские_счета_код_seq" OWNED BY "банковские_счета"."код";


--
-- TOC entry 3026 (class 0 OID 0)
-- Dependencies: 179
-- Name: банковские_счета_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"банковские_счета_код_seq"', 1, false);


--
-- TOC entry 197 (class 1259 OID 20294)
-- Dependencies: 5 196
-- Name: блокпериоды_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "блокпериоды_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."блокпериоды_код_seq" OWNER TO sa;

--
-- TOC entry 3027 (class 0 OID 0)
-- Dependencies: 197
-- Name: блокпериоды_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "блокпериоды_код_seq" OWNED BY "блокпериоды"."код";


--
-- TOC entry 3028 (class 0 OID 0)
-- Dependencies: 197
-- Name: блокпериоды_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"блокпериоды_код_seq"', 2, true);


--
-- TOC entry 192 (class 1259 OID 20261)
-- Dependencies: 2787 5
-- Name: виды_расходов; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "виды_расходов" (
    "код" integer NOT NULL,
    "имя" character varying(100) DEFAULT ''::character varying
);


ALTER TABLE public."виды_расходов" OWNER TO sa;

--
-- TOC entry 193 (class 1259 OID 20267)
-- Dependencies: 5 192
-- Name: виды_расходов_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "виды_расходов_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."виды_расходов_код_seq" OWNER TO sa;

--
-- TOC entry 3030 (class 0 OID 0)
-- Dependencies: 193
-- Name: виды_расходов_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "виды_расходов_код_seq" OWNED BY "виды_расходов"."код";


--
-- TOC entry 3031 (class 0 OID 0)
-- Dependencies: 193
-- Name: виды_расходов_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"виды_расходов_код_seq"', 1, false);


--
-- TOC entry 186 (class 1259 OID 20220)
-- Dependencies: 2773 2774 5
-- Name: группы; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "группы" (
    "код" integer NOT NULL,
    "имя" character varying(100) DEFAULT ''::character varying,
    "цены_снижать" boolean DEFAULT false
);


ALTER TABLE public."группы" OWNER TO sa;

--
-- TOC entry 187 (class 1259 OID 20227)
-- Dependencies: 5 186
-- Name: группы_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "группы_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."группы_код_seq" OWNER TO sa;

--
-- TOC entry 3032 (class 0 OID 0)
-- Dependencies: 187
-- Name: группы_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "группы_код_seq" OWNED BY "группы"."код";


--
-- TOC entry 3033 (class 0 OID 0)
-- Dependencies: 187
-- Name: группы_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"группы_код_seq"', 2, true);


--
-- TOC entry 169 (class 1259 OID 20067)
-- Dependencies: 168 5
-- Name: документы_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "документы_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."документы_код_seq" OWNER TO sa;

--
-- TOC entry 3034 (class 0 OID 0)
-- Dependencies: 169
-- Name: документы_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "документы_код_seq" OWNED BY "документы"."код";


--
-- TOC entry 3035 (class 0 OID 0)
-- Dependencies: 169
-- Name: документы_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"документы_код_seq"', 5, true);


--
-- TOC entry 199 (class 1259 OID 20309)
-- Dependencies: 198 5
-- Name: доступ_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "доступ_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."доступ_код_seq" OWNER TO sa;

--
-- TOC entry 3036 (class 0 OID 0)
-- Dependencies: 199
-- Name: доступ_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "доступ_код_seq" OWNED BY "доступ"."код";


--
-- TOC entry 3037 (class 0 OID 0)
-- Dependencies: 199
-- Name: доступ_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"доступ_код_seq"', 31, true);


--
-- TOC entry 201 (class 1259 OID 20321)
-- Dependencies: 200 5
-- Name: журнал_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "журнал_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."журнал_код_seq" OWNER TO sa;

--
-- TOC entry 3038 (class 0 OID 0)
-- Dependencies: 201
-- Name: журнал_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "журнал_код_seq" OWNED BY "журнал"."код";


--
-- TOC entry 3039 (class 0 OID 0)
-- Dependencies: 201
-- Name: журнал_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"журнал_код_seq"', 1, false);


--
-- TOC entry 173 (class 1259 OID 20101)
-- Dependencies: 5 172
-- Name: константы_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "константы_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."константы_код_seq" OWNER TO sa;

--
-- TOC entry 3040 (class 0 OID 0)
-- Dependencies: 173
-- Name: константы_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "константы_код_seq" OWNED BY "константы"."код";


--
-- TOC entry 3041 (class 0 OID 0)
-- Dependencies: 173
-- Name: константы_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"константы_код_seq"', 5, true);


--
-- TOC entry 181 (class 1259 OID 20183)
-- Dependencies: 180 5
-- Name: контрагенты_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "контрагенты_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."контрагенты_код_seq" OWNER TO sa;

--
-- TOC entry 3042 (class 0 OID 0)
-- Dependencies: 181
-- Name: контрагенты_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "контрагенты_код_seq" OWNED BY "контрагенты"."код";


--
-- TOC entry 3043 (class 0 OID 0)
-- Dependencies: 181
-- Name: контрагенты_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"контрагенты_код_seq"', 3, true);


--
-- TOC entry 183 (class 1259 OID 20195)
-- Dependencies: 5 182
-- Name: материалы_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "материалы_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."материалы_код_seq" OWNER TO sa;

--
-- TOC entry 3044 (class 0 OID 0)
-- Dependencies: 183
-- Name: материалы_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "материалы_код_seq" OWNED BY "материалы"."код";


--
-- TOC entry 3045 (class 0 OID 0)
-- Dependencies: 183
-- Name: материалы_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"материалы_код_seq"', 1, false);


--
-- TOC entry 185 (class 1259 OID 20215)
-- Dependencies: 184 5
-- Name: номенклатура_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "номенклатура_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."номенклатура_код_seq" OWNER TO sa;

--
-- TOC entry 3046 (class 0 OID 0)
-- Dependencies: 185
-- Name: номенклатура_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "номенклатура_код_seq" OWNED BY "номенклатура"."код";


--
-- TOC entry 3047 (class 0 OID 0)
-- Dependencies: 185
-- Name: номенклатура_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"номенклатура_код_seq"', 35, true);


--
-- TOC entry 194 (class 1259 OID 20272)
-- Dependencies: 2789 2790 5
-- Name: нумераторы; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "нумераторы" (
    "код" integer NOT NULL,
    "имя" character varying(100) DEFAULT ''::character varying,
    "значение" integer DEFAULT 0
);


ALTER TABLE public."нумераторы" OWNER TO sa;

--
-- TOC entry 195 (class 1259 OID 20280)
-- Dependencies: 194 5
-- Name: нумераторы_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "нумераторы_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."нумераторы_код_seq" OWNER TO sa;

--
-- TOC entry 3049 (class 0 OID 0)
-- Dependencies: 195
-- Name: нумераторы_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "нумераторы_код_seq" OWNED BY "нумераторы"."код";


--
-- TOC entry 3050 (class 0 OID 0)
-- Dependencies: 195
-- Name: нумераторы_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"нумераторы_код_seq"', 3, true);


--
-- TOC entry 188 (class 1259 OID 20232)
-- Dependencies: 2776 2777 2778 2779 2780 2781 2782 5
-- Name: персонал; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "персонал" (
    "код" integer NOT NULL,
    "имя" character varying(50) DEFAULT ''::character varying,
    "инн" character varying(12) DEFAULT ''::character varying,
    "паспорт_серия" character varying(7) DEFAULT ''::character varying,
    "паспорт_номер" character varying(6) DEFAULT ''::character varying,
    "паспорт_выдан" character varying(50) DEFAULT ''::character varying,
    "паспорт_дата" date,
    "адрес" character varying(50) DEFAULT ''::character varying,
    "день_рождения" date,
    "работает" boolean,
    "медстрах" character varying(14) DEFAULT ''::character varying
);


ALTER TABLE public."персонал" OWNER TO sa;

--
-- TOC entry 189 (class 1259 OID 20244)
-- Dependencies: 188 5
-- Name: персонал_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "персонал_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."персонал_код_seq" OWNER TO sa;

--
-- TOC entry 3052 (class 0 OID 0)
-- Dependencies: 189
-- Name: персонал_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "персонал_код_seq" OWNED BY "персонал"."код";


--
-- TOC entry 3053 (class 0 OID 0)
-- Dependencies: 189
-- Name: персонал_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"персонал_код_seq"', 1, false);


--
-- TOC entry 212 (class 1259 OID 20382)
-- Dependencies: 2822 2823 2824 2825 2826 2827 2828 2829 2830 5
-- Name: прайсы; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "прайсы" (
    "код" integer NOT NULL,
    "имя" character varying(100) DEFAULT ''::character varying,
    "код_фирмы" integer,
    "кодвпрайсе" character varying(50) DEFAULT ''::character varying,
    "артикул" character varying(20) DEFAULT ''::character varying,
    "едизм" character varying(10) DEFAULT ''::character varying,
    "дата" date,
    "цена" numeric(10,2) DEFAULT 0,
    "упаковка" integer,
    "наличие" character(1) DEFAULT '+'::character(1),
    "код_товар" integer,
    "кол_прайс" numeric(8,3) DEFAULT 1,
    "кол_товар" numeric(8,3) DEFAULT 1,
    "приоритет" integer DEFAULT 1,
    fts tsvector
);


ALTER TABLE public."прайсы" OWNER TO sa;

--
-- TOC entry 213 (class 1259 OID 20399)
-- Dependencies: 5 212
-- Name: прайсы_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "прайсы_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."прайсы_код_seq" OWNER TO sa;

--
-- TOC entry 3055 (class 0 OID 0)
-- Dependencies: 213
-- Name: прайсы_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "прайсы_код_seq" OWNED BY "прайсы"."код";


--
-- TOC entry 3056 (class 0 OID 0)
-- Dependencies: 213
-- Name: прайсы_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"прайсы_код_seq"', 1, false);


--
-- TOC entry 190 (class 1259 OID 20249)
-- Dependencies: 2784 2785 5
-- Name: предметы; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "предметы" (
    "код" integer NOT NULL,
    "имя" character varying(100) DEFAULT ''::character varying,
    "едизм" character varying(6) DEFAULT ''::character varying
);


ALTER TABLE public."предметы" OWNER TO sa;

--
-- TOC entry 191 (class 1259 OID 20256)
-- Dependencies: 5 190
-- Name: предметы_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "предметы_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."предметы_код_seq" OWNER TO sa;

--
-- TOC entry 3058 (class 0 OID 0)
-- Dependencies: 191
-- Name: предметы_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "предметы_код_seq" OWNED BY "предметы"."код";


--
-- TOC entry 3059 (class 0 OID 0)
-- Dependencies: 191
-- Name: предметы_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"предметы_код_seq"', 1, false);


--
-- TOC entry 171 (class 1259 OID 20082)
-- Dependencies: 170 5
-- Name: проводки_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "проводки_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."проводки_код_seq" OWNER TO sa;

--
-- TOC entry 3060 (class 0 OID 0)
-- Dependencies: 171
-- Name: проводки_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "проводки_код_seq" OWNED BY "проводки"."код";


--
-- TOC entry 3061 (class 0 OID 0)
-- Dependencies: 171
-- Name: проводки_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"проводки_код_seq"', 27, true);


--
-- TOC entry 206 (class 1259 OID 20351)
-- Dependencies: 2815 5
-- Name: справочник; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "справочник" (
    "код" integer NOT NULL,
    "имя" character varying(100) DEFAULT ''::character varying
);


ALTER TABLE public."справочник" OWNER TO sa;

--
-- TOC entry 207 (class 1259 OID 20357)
-- Dependencies: 5 206
-- Name: справочник_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "справочник_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."справочник_код_seq" OWNER TO sa;

--
-- TOC entry 3062 (class 0 OID 0)
-- Dependencies: 207
-- Name: справочник_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "справочник_код_seq" OWNED BY "справочник"."код";


--
-- TOC entry 3063 (class 0 OID 0)
-- Dependencies: 207
-- Name: справочник_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"справочник_код_seq"', 1, false);


--
-- TOC entry 203 (class 1259 OID 20337)
-- Dependencies: 5 202
-- Name: справочники_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "справочники_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."справочники_код_seq" OWNER TO sa;

--
-- TOC entry 3064 (class 0 OID 0)
-- Dependencies: 203
-- Name: справочники_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "справочники_код_seq" OWNED BY "справочники"."код";


--
-- TOC entry 3065 (class 0 OID 0)
-- Dependencies: 203
-- Name: справочники_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"справочники_код_seq"', 24, true);


--
-- TOC entry 209 (class 1259 OID 20367)
-- Dependencies: 208 5
-- Name: столбцы_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "столбцы_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."столбцы_код_seq" OWNER TO sa;

--
-- TOC entry 3066 (class 0 OID 0)
-- Dependencies: 209
-- Name: столбцы_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "столбцы_код_seq" OWNED BY "столбцы"."код";


--
-- TOC entry 3067 (class 0 OID 0)
-- Dependencies: 209
-- Name: столбцы_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"столбцы_код_seq"', 84, true);


--
-- TOC entry 166 (class 1259 OID 20038)
-- Dependencies: 5 165
-- Name: счета_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "счета_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."счета_код_seq" OWNER TO sa;

--
-- TOC entry 3068 (class 0 OID 0)
-- Dependencies: 166
-- Name: счета_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "счета_код_seq" OWNED BY "счета"."код";


--
-- TOC entry 3069 (class 0 OID 0)
-- Dependencies: 166
-- Name: счета_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"счета_код_seq"', 105, true);


--
-- TOC entry 204 (class 1259 OID 20340)
-- Dependencies: 2813 5
-- Name: типыобъектов; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "типыобъектов" (
    "код" integer NOT NULL,
    "имя" character varying(20) DEFAULT ''::character varying
);


ALTER TABLE public."типыобъектов" OWNER TO sa;

--
-- TOC entry 205 (class 1259 OID 20346)
-- Dependencies: 204 5
-- Name: типыобъектов_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "типыобъектов_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."типыобъектов_код_seq" OWNER TO sa;

--
-- TOC entry 3071 (class 0 OID 0)
-- Dependencies: 205
-- Name: типыобъектов_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "типыобъектов_код_seq" OWNED BY "типыобъектов"."код";


--
-- TOC entry 3072 (class 0 OID 0)
-- Dependencies: 205
-- Name: типыобъектов_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"типыобъектов_код_seq"', 6, true);


--
-- TOC entry 175 (class 1259 OID 20134)
-- Dependencies: 174 5
-- Name: топер_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "топер_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."топер_код_seq" OWNER TO sa;

--
-- TOC entry 3073 (class 0 OID 0)
-- Dependencies: 175
-- Name: топер_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "топер_код_seq" OWNED BY "топер"."код";


--
-- TOC entry 3074 (class 0 OID 0)
-- Dependencies: 175
-- Name: топер_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"топер_код_seq"', 5, true);


--
-- TOC entry 211 (class 1259 OID 20372)
-- Dependencies: 2820 5
-- Name: файлы; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "файлы" (
    "код" integer NOT NULL,
    "имя" character varying(100) DEFAULT ''::character varying,
    "тип" integer,
    "значение" bytea
);


ALTER TABLE public."файлы" OWNER TO sa;

--
-- TOC entry 210 (class 1259 OID 20370)
-- Dependencies: 5 211
-- Name: файлы_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "файлы_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."файлы_код_seq" OWNER TO sa;

--
-- TOC entry 3076 (class 0 OID 0)
-- Dependencies: 210
-- Name: файлы_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "файлы_код_seq" OWNED BY "файлы"."код";


--
-- TOC entry 3077 (class 0 OID 0)
-- Dependencies: 210
-- Name: файлы_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"файлы_код_seq"', 2, true);


--
-- TOC entry 2745 (class 2604 OID 20148)
-- Dependencies: 177 176
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "банки" ALTER COLUMN "код" SET DEFAULT nextval('"банки_код_seq"'::regclass);


--
-- TOC entry 2748 (class 2604 OID 20160)
-- Dependencies: 179 178
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "банковские_счета" ALTER COLUMN "код" SET DEFAULT nextval('"банковские_счета_код_seq"'::regclass);


--
-- TOC entry 2792 (class 2604 OID 20296)
-- Dependencies: 197 196
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "блокпериоды" ALTER COLUMN "код" SET DEFAULT nextval('"блокпериоды_код_seq"'::regclass);


--
-- TOC entry 2788 (class 2604 OID 20269)
-- Dependencies: 193 192
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "виды_расходов" ALTER COLUMN "код" SET DEFAULT nextval('"виды_расходов_код_seq"'::regclass);


--
-- TOC entry 2775 (class 2604 OID 20229)
-- Dependencies: 187 186
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "группы" ALTER COLUMN "код" SET DEFAULT nextval('"группы_код_seq"'::regclass);


--
-- TOC entry 2712 (class 2604 OID 20069)
-- Dependencies: 169 168
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "документы" ALTER COLUMN "код" SET DEFAULT nextval('"документы_код_seq"'::regclass);


--
-- TOC entry 2797 (class 2604 OID 20311)
-- Dependencies: 199 198
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "доступ" ALTER COLUMN "код" SET DEFAULT nextval('"доступ_код_seq"'::regclass);


--
-- TOC entry 2803 (class 2604 OID 20323)
-- Dependencies: 201 200
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "журнал" ALTER COLUMN "код" SET DEFAULT nextval('"журнал_код_seq"'::regclass);


--
-- TOC entry 2719 (class 2604 OID 20103)
-- Dependencies: 173 172
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "константы" ALTER COLUMN "код" SET DEFAULT nextval('"константы_код_seq"'::regclass);


--
-- TOC entry 2761 (class 2604 OID 20185)
-- Dependencies: 181 180
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "контрагенты" ALTER COLUMN "код" SET DEFAULT nextval('"контрагенты_код_seq"'::regclass);


--
-- TOC entry 2764 (class 2604 OID 20197)
-- Dependencies: 183 182
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "материалы" ALTER COLUMN "код" SET DEFAULT nextval('"материалы_код_seq"'::regclass);


--
-- TOC entry 2772 (class 2604 OID 20217)
-- Dependencies: 185 184
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "номенклатура" ALTER COLUMN "код" SET DEFAULT nextval('"номенклатура_код_seq"'::regclass);


--
-- TOC entry 2791 (class 2604 OID 20282)
-- Dependencies: 195 194
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "нумераторы" ALTER COLUMN "код" SET DEFAULT nextval('"нумераторы_код_seq"'::regclass);


--
-- TOC entry 2783 (class 2604 OID 20246)
-- Dependencies: 189 188
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "персонал" ALTER COLUMN "код" SET DEFAULT nextval('"персонал_код_seq"'::regclass);


--
-- TOC entry 2821 (class 2604 OID 20401)
-- Dependencies: 213 212
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "прайсы" ALTER COLUMN "код" SET DEFAULT nextval('"прайсы_код_seq"'::regclass);


--
-- TOC entry 2786 (class 2604 OID 20258)
-- Dependencies: 191 190
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "предметы" ALTER COLUMN "код" SET DEFAULT nextval('"предметы_код_seq"'::regclass);


--
-- TOC entry 2716 (class 2604 OID 20084)
-- Dependencies: 171 170
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "проводки" ALTER COLUMN "код" SET DEFAULT nextval('"проводки_код_seq"'::regclass);


--
-- TOC entry 2814 (class 2604 OID 20359)
-- Dependencies: 207 206
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "справочник" ALTER COLUMN "код" SET DEFAULT nextval('"справочник_код_seq"'::regclass);


--
-- TOC entry 2806 (class 2604 OID 20339)
-- Dependencies: 203 202
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "справочники" ALTER COLUMN "код" SET DEFAULT nextval('"справочники_код_seq"'::regclass);


--
-- TOC entry 2816 (class 2604 OID 20369)
-- Dependencies: 209 208
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "столбцы" ALTER COLUMN "код" SET DEFAULT nextval('"столбцы_код_seq"'::regclass);


--
-- TOC entry 2699 (class 2604 OID 20040)
-- Dependencies: 166 165
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "счета" ALTER COLUMN "код" SET DEFAULT nextval('"счета_код_seq"'::regclass);


--
-- TOC entry 2812 (class 2604 OID 20348)
-- Dependencies: 205 204
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "типыобъектов" ALTER COLUMN "код" SET DEFAULT nextval('"типыобъектов_код_seq"'::regclass);


--
-- TOC entry 2740 (class 2604 OID 20136)
-- Dependencies: 175 174
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "топер" ALTER COLUMN "код" SET DEFAULT nextval('"топер_код_seq"'::regclass);


--
-- TOC entry 2819 (class 2604 OID 20375)
-- Dependencies: 210 211 211
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "файлы" ALTER COLUMN "код" SET DEFAULT nextval('"файлы_код_seq"'::regclass);


--
-- TOC entry 2956 (class 0 OID 20137)
-- Dependencies: 176
-- Data for Name: банки; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "банки" ("код", "имя", "бик", "корсчет", "счет") FROM stdin;
\.


--
-- TOC entry 2957 (class 0 OID 20151)
-- Dependencies: 178
-- Data for Name: банковские_счета; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "банковские_счета" ("код", "имя", "счет", "код_банки") FROM stdin;
\.


--
-- TOC entry 2966 (class 0 OID 20285)
-- Dependencies: 196
-- Data for Name: блокпериоды; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "блокпериоды" ("код", "имя", "блокконец", "начало", "конец", "пользователь") FROM stdin;
1		\N	2010-05-01	2010-05-31	sa
\.


--
-- TOC entry 2964 (class 0 OID 20261)
-- Dependencies: 192
-- Data for Name: виды_расходов; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "виды_расходов" ("код", "имя") FROM stdin;
\.


--
-- TOC entry 2961 (class 0 OID 20220)
-- Dependencies: 186
-- Data for Name: группы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "группы" ("код", "имя", "цены_снижать") FROM stdin;
1	Запчасти ВАЗ	f
\.


--
-- TOC entry 2952 (class 0 OID 20056)
-- Dependencies: 168
-- Data for Name: документы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "документы" ("код", "дата", "датавремя", "номер", "комментарий", "сумма", "описание", "опер", "авто", "переменные") FROM stdin;
3	2010-05-31	2010-07-03 19:36:05.175633	3		0.00	\N	1	0	\N
4	2010-06-30	2010-08-24 22:23:28	4		324.00	\N	1	0	\N
5	2010-06-30	2010-09-24 13:29:32	5		235.00	\N	1	0	\N
1	2010-05-17	2010-07-03 19:32:29	1	ТД "Автодеталь"	400.00	\N	1	0	\N
\.


--
-- TOC entry 2967 (class 0 OID 20299)
-- Dependencies: 198
-- Data for Name: доступ; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "доступ" ("код", "меню", "комментарий", "код_типыобъектов", "пользователь", "имя", "доступ") FROM stdin;
1	f		1	sa	vw_доступ_к_справочникам	
2	f		1	sa	vw_доступ_к_топер	
3	t		1	sa	справочники	
4	t		1	sa	столбцы	
5	f		1	sa	vw_справочники	
7	t		1	sa	типыобъектов	
6	t		1	sa	доступ	
8	t		1	sa	счета	
9	f		1	sa	vw_справочники_со_столбцами	
10	t		1	sa	топер	
11	t		1	sa	нумераторы	
12	t		1	sa	номенклатура	
13	t		3	sa	1	
14	t		1	sa	контрагенты	
15	t		1	sa	группы	
16	f		1	sa	vw_контрагенты	
17	f		1	sa	vw_номенклатура	
18	t		1	sa	банки	
19	f		1	sa	vw_грузополучатели	
20	t		3	sa	2	
21	f		5	*	Документ2.p1__цена	ro
22	t		1	sa	константы	
23	f		5	*	номенклатура.цена_розн	ro
24	t		1	sa	блокпериоды	
31	t		3	sa	3	
\.


--
-- TOC entry 2968 (class 0 OID 20314)
-- Dependencies: 200
-- Data for Name: журнал; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "журнал" ("код", "имя", "датавремя", "содержание", "код_номенклатура", "дата") FROM stdin;
\.


--
-- TOC entry 2954 (class 0 OID 20094)
-- Dependencies: 172
-- Data for Name: константы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "константы" ("код", "имя", "значение", "комментарий") FROM stdin;
1	база_фото	enterprise_pictures	\N
2	наименование_фирмы	ИП Мальцев В.А.	\N
3	руководитель_фирмы	Мальцев В.А.	\N
4	гл_бухгалтер_фирмы	Смирнова Т.В.	\N
\.


--
-- TOC entry 2958 (class 0 OID 20163)
-- Dependencies: 180
-- Data for Name: контрагенты; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "контрагенты" ("код", "имя", "адрес", "телефон", e_mail, "руководитель", "гл_бухгалтер", "инн", "кпп", "оконх", "окпо", "счет", "код_банки", "лимит", "код_vw_грузополучатели") FROM stdin;
1	ООО "АвтоОпт"	г.Москва, ул.Декабристов 15	(495)236-67-89		Сидоров Е.А.							\N	0.00	\N
2	ТД "Автодеталь"	г.Н.Новгород, ул.Социалистическая 77	(8312)45-97-65		Петров С.Н.							\N	0.00	\N
\.


--
-- TOC entry 2959 (class 0 OID 20188)
-- Dependencies: 182
-- Data for Name: материалы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "материалы" ("код", "имя", "едизм") FROM stdin;
\.


--
-- TOC entry 2960 (class 0 OID 20200)
-- Dependencies: 184
-- Data for Name: номенклатура; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "номенклатура" ("код", "имя", "едизм", "артикул", "код_группы", "цена_розн", "запас", "имя_на_ценнике", "тип_ценника", fts) FROM stdin;
34	ключ натяжения ремня ГРМ 2108	шт		1	26.00	0		3	\N
28	диск сцепления дв. 406 (ЗМЗ)	шт	40637-1601130	\N	770.00	0		3	\N
18	фильтр топливный (GUR-612)  дизель универсал	шт		\N	37.00	0		3	\N
2	паста притирочная алмазная (20гр)	шт		\N	56.00	0		3	\N
3	брелок оригинальный (хром)	шт		\N	47.00	0		3	\N
4	препарат "РЕМЕТАЛЛ" для двигателя (120мл)	шт		\N	165.00	0		3	\N
5	очиститель рук "Защитные перчатки" (40г)	шт		\N	27.00	0		3	\N
8	крестовина 2121 "Master-Sport" (Германия)	шт		1	178.00	0		3	\N
29	ремкомплект рулевой рейки М-2126 (полный)	к-т		\N	520.00	0		3	\N
27	ось верхнего рычага 2121	шт		1	97.00	0		3	\N
7	лампа H3 12В (55Вт) галогенн. (отеч.)	шт		\N	196.00	0		3	\N
21	свеча BERU Z21 ВАЗ-2110 8-клап.  (Германия)			\N	76.00	0		3	\N
9	стартер ГАЗ, УАЗ дв.406,405,409 (42.3708-10/11) БАТЭ	шт	42.3708-10 	\N	2440.00	0		3	\N
22	фара противотуманная CIRIE круглая (лазерная)	к-т		\N	422.00	0		3	\N
10	дезодорант "Mannol Eclipse"	шт		\N	55.00	0		3	\N
20	палец шаровый нижний с/п 2101 (FENOX)	шт	2101-2904082	1	188.00	0		3	\N
12	размораживатель замков "LUX-OIL" (50мл)	шт		\N	35.00	0		3	\N
13	крестовина М-412 "Master-Sport" (Германия)	шт		\N	167.00	0		3	\N
15	дезодорант "Русский лес"	шт		\N	21.00	0		3	\N
11	подшипник 256907 ступицы передний 2108, М-2126 "Herzog" (Германия)	шт	2108-3103020	1	193.00	0		3	\N
31	прокладка поддона дв.402	шт		\N	75.00	0		3	\N
14	пружина задней подвески 1111	шт		1	380.00	0		3	\N
30	реле-регулятор 2110, дв. 406 (611.3702-11) в сборе с ЩУ	шт		1	104.00	0		3	\N
19	ремень генератора 2108, Таврия (710) зубч. "Хорс"	шт	2108-3701720	1	52.00	0		3	\N
23	ремкомплект карбюратора 1111 (Челябинск)	к-т	1111-	1	71.00	0		3	\N
24	ремкомплект стоек 2108	к-т	2108-	1	22.00	0		3	\N
35	термостат 2101	шт	2101-1306010	1	263.00	0		3	\N
33	трубка сцепления 2101	шт		1	20.00	0		3	\N
17	фильтр топливный 2108 (инжектор) FRAM	шт		1	274.00	0		3	\N
1	цилиндр тормозной 2108 главный	шт		1	530.00	0		3	\N
6	бендикс 2101 "Master-Sport" (Германия)	шт		1	183.00	0		3	\N
16	вал и червяк 2105	шт	2101-3401035-20	1	410.00	0		3	\N
25	шатун 2108, 21099, 1111	шт	2108-1004045-00	1	470.00	0		3	\N
32	шестерня КПП 5-й передачи 2108, 2110	шт	2108-1701158/64	1	361.00	0		3	\N
\.


--
-- TOC entry 2965 (class 0 OID 20272)
-- Dependencies: 194
-- Data for Name: нумераторы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "нумераторы" ("код", "имя", "значение") FROM stdin;
1	Накладная	0
2	Накладная1	0
\.


--
-- TOC entry 2962 (class 0 OID 20232)
-- Dependencies: 188
-- Data for Name: персонал; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "персонал" ("код", "имя", "инн", "паспорт_серия", "паспорт_номер", "паспорт_выдан", "паспорт_дата", "адрес", "день_рождения", "работает", "медстрах") FROM stdin;
\.


--
-- TOC entry 2974 (class 0 OID 20382)
-- Dependencies: 212
-- Data for Name: прайсы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "прайсы" ("код", "имя", "код_фирмы", "кодвпрайсе", "артикул", "едизм", "дата", "цена", "упаковка", "наличие", "код_товар", "кол_прайс", "кол_товар", "приоритет", fts) FROM stdin;
\.


--
-- TOC entry 2963 (class 0 OID 20249)
-- Dependencies: 190
-- Data for Name: предметы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "предметы" ("код", "имя", "едизм") FROM stdin;
\.


--
-- TOC entry 2953 (class 0 OID 20074)
-- Dependencies: 170
-- Data for Name: проводки; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "проводки" ("код", "дбсчет", "дбкод", "крсчет", "кркод", "кол", "цена", "сумма", "стр", "доккод", "опер", "номеропер") FROM stdin;
23	41.1 	6	42   	6	0.000	0.00	0.00	1	1	1	2
25	41.1 	34	42   	34	0.000	0.00	0.00	2	1	1	2
24	41.1 	34	60   	2	2.000	75.00	150.00	2	1	1	1
22	41.1 	6	60   	2	2.000	100.00	200.00	1	1	1	1
26	41.1 	7	60   	2	4.000	50.00	200.00	3	1	1	1
27	41.1 	7	42   	7	0.000	0.00	0.00	3	1	1	2
\.


--
-- TOC entry 2951 (class 0 OID 20043)
-- Dependencies: 167
-- Data for Name: сальдо; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "сальдо" ("счет", "код", "кол", "сальдо", "дбкол", "дебет", "кркол", "кредит", "конкол", "консальдо", "концена") FROM stdin;
42   	24	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
19.3 	0	0.000	0.00	0.000	600.00	0.000	0.00	0.000	600.00	600.00
19.3 	0	0.000	0.00	0.000	600.00	0.000	0.00	0.000	600.00	600.00
42   	28	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
41.1 	3	0.000	0.00	9.000	90.80	0.000	0.00	9.000	90.80	10.09
41.1 	3	0.000	0.00	9.000	90.80	0.000	0.00	9.000	90.80	10.09
42   	3	0.000	0.00	0.000	0.00	0.000	10.80	0.000	-10.80	-10.80
42   	3	0.000	0.00	0.000	0.00	0.000	10.80	0.000	-10.80	-10.80
42   	25	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
41.1 	4	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
41.1 	32	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
42   	32	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
42   	4	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
41.1 	15	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
42   	15	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
41.1 	35	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
42   	35	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
41.1 	1	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
42   	1	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
60   	0	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
41.1 	28	0.000	0.00	1.000	400.00	0.000	0.00	1.000	400.00	400.00
41.1 	24	0.000	0.00	1.000	50.00	0.000	0.00	1.000	50.00	50.00
42   	16	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
41.1 	27	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
42   	27	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
41.1 	33	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
42   	33	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
41.1 	5	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
42   	5	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
41.1 	25	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
42   	2	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
41.1 	2	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
41.1 	16	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
60   	2	0.000	0.00	0.000	0.00	12.000	1000.00	-12.000	-1000.00	83.33
60   	2	0.000	0.00	0.000	0.00	12.000	1000.00	-12.000	-1000.00	83.33
42   	6	0.000	0.00	0.000	0.00	0.000	47.70	0.000	-47.70	-47.70
42   	6	0.000	0.00	0.000	0.00	0.000	47.70	0.000	-47.70	-47.70
41.1 	7	0.000	0.00	4.000	200.00	0.000	0.00	4.000	200.00	50.00
42   	7	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
42   	34	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
41.1 	34	0.000	0.00	4.000	250.00	0.000	0.00	4.000	250.00	62.50
60   	1	0.000	0.00	0.000	0.00	12.000	1045.00	-12.000	-1045.00	87.08
60   	1	0.000	0.00	0.000	0.00	12.000	1045.00	-12.000	-1045.00	87.08
41.1 	6	0.000	0.00	5.000	512.70	0.000	0.00	5.000	512.70	102.54
41.1 	6	0.000	0.00	5.000	512.70	0.000	0.00	5.000	512.70	102.54
\.


--
-- TOC entry 2971 (class 0 OID 20351)
-- Dependencies: 206
-- Data for Name: справочник; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "справочник" ("код", "имя") FROM stdin;
\.


--
-- TOC entry 2969 (class 0 OID 20324)
-- Dependencies: 202
-- Data for Name: справочники; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "справочники" ("код", "имя", "имя_в_списке", "имя_в_форме", "форма", "преформулы", "формулы", "постформулы", "фото") FROM stdin;
1	справочники	Справочники			\N	\N	\N	
2	столбцы	Справочник. Наименование столбцов			\N	\N	\N	
3	доступ	Доступ			\N	\N	\N	
4	типыобъектов	Справочник. Типы объектов.	Тип объекта		\N	\N	\N	
5	счета	Бухгалтерские счета			\N	\N	\N	
6	vw_доступ_к_справочникам	Справочники		Справочник. Доступ к справочникам	\N	\N	\N	
7	vw_справочники_со_столбцами	Справочники, в которых столбцы могут иметь пользовательское название			\N	\N	\N	
8	топер	Справочник. Типовые операции			\N	\N	\N	
9	нумераторы	Справочник. Нумераторы			\N	\N	\N	
10	номенклатура	Справочник. Номенклатура	Номенклатура		\N	\N	\N	~/фото/номенклатура
11	контрагенты	Справочник. Контрагенты	Контрагент		\N	\N	\N	
12	группы	Справочники. Группы	Группа		\N	\N	\N	
13	vw_доступ_к_топер	Операции		Справочник. Доступ к типовым операциям	\N	\N	\N	
14	vw_контрагенты	Просмотр. Контрагенты	Контрагент		\N	\N	\N	
15	vw_номенклатура	Просмотр. Номенклатура	Номенклатура		\N	\N	\N	
16	банки	Справочник. Банки	Банк		\N	\N	\N	
17	vw_грузополучатели	Просмотр. Грузополучатели	Грузополучатель		\N	\N	\N	
18	константы	Константы			\N	\N	\N	
19	блокпериоды	Периоды			\N	\N	\N	
\.


--
-- TOC entry 2972 (class 0 OID 20360)
-- Dependencies: 208
-- Data for Name: столбцы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "столбцы" ("код", "код_vw_справочники_со_столбцами", "имя", "заголовок", "номер") FROM stdin;
1	1	имя	Справочник	1
2	1	имя_в_списке	Имя в списке	2
3	1	имя_в_форме	Имя в форме	3
4	2	имя	Столбец	2
5	2	заголовок	Заголовок столбца	3
6	2	номер	No	4
7	2	vw_справочники_со_столбцами.имя	Справочник	1
8	3	типыобъектов.имя	Тип объекта	1
9	3	имя	Наименование	2
10	3	меню	Меню	3
11	3	пользователь	Пользователи	4
12	3	комментарий	Комментарий	6
13	5	счет	Счет	1
14	5	имя	Наименование	2
15	5	баланс	Баланс	3
16	5	количество	Количество	4
17	5	имясправочника	Справочник	5
18	7	код	Код	1
19	7	имя	Наименование	2
20	6	имя	Наименование	1
26	11	имя	Наименование	1
27	11	адрес	Адрес	2
28	11	телефон	Телефон	3
29	11	e_mail	E-mail	4
30	11	руководитель	Руководитель	5
31	11	гл_бухгалтер	Гл.бухгалтер	6
32	11	инн	ИНН	7
33	11	кпп	КПП	8
34	11	оконх	ОКОНХ	9
35	11	окпо	ОКПО	10
36	11	счет	Расчетный счет	11
37	12	имя	Наименование	1
38	13	имя	Наименование	1
39	1000001	дата	Дата	1
40	1000001	номер	Номер	2
41	1000001	комментарий	Комментарий	3
42	1000001	сумма	Сумма	4
49	15	код	Код	1
50	15	имя	Наименование	2
51	15	артикул	Артикул	3
52	15	едизм	Ед.Изм.	4
53	15	цена_роз	Розн.Цена	5
54	14	имя	Наименование	1
55	14	адрес	Адрес	2
56	14	телефон	Телефон	3
57	17	имя	Наименование	1
58	17	адрес	Адрес	2
59	17	телефон	Телефон	3
60	16	код	Код	1
61	16	имя	Наименование	2
62	16	бик	БИК	3
63	16	корсчет	Корр.Счет	4
64	16	счет	Счет	5
65	1000002	дата	Дата	1
66	1000002	номер	Номер	2
67	1000002	комментарий	Комментарий	3
68	1000002	сумма	Сумма	4
69	2000002	номенклатура__имя	Наименование	1
70	2000002	номенклатура__артикул	Артикул	2
71	2000002	номенклатура__едизм	Ед.Изм.	3
72	2000002	крсальдо1__конкол	Остаток	4
73	2000002	p1__кол	Кол-во	5
74	1	фото	Каталог с фотографиями	4
75	18	имя	Наименование	1
76	18	значение	Значение	2
77	18	комментарий	Комментарий	3
78	3	доступ	Доступ	5
79	19	имя	Комментарий	1
80	19	начало	Начало периода	2
81	19	конец	Конец периода	3
82	19	пользователь	Пользователь	4
43	2000001	номенклатура__имя	Наименование	1
44	2000001	номенклатура__артикул	Артикул	2
84	24	имя	Наименование	1
21	10	код	Код	1
22	10	имя	Наименование	2
23	10	артикул	Артикул	3
24	10	едизм	Ед.Изм.	4
25	10	цена_розн	Розн.Цена	5
45	2000001	номенклатура__едизм	Ед.Изм.	3
46	2000001	p1__кол	Кол-во	4
47	2000001	p1__цена	Цена	5
48	2000001	p1__сумма	Сумма	6
\.


--
-- TOC entry 2950 (class 0 OID 20028)
-- Dependencies: 165
-- Data for Name: счета; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "счета" ("код", "имя", "счет", "имясправочника", "баланс", "количество") FROM stdin;
41	Выпуск продукции (работ, услуг)	40   		t	t
60	Финансовые вложения. Паи и акции	58.1 		t	f
3	Амортизация основных средств	02   		t	f
26	Животные на выращивании и откорме	11   		t	f
49	Товары отгруженные	45   		t	f
4	Доходные вложения в материальные ценности	03   		t	f
42	Товары. Товары на складах	41.1 	номенклатура	t	t
27	Резервы под снижение стоимости материальных ценностей	14   		t	f
5	Нематериальные активы	04   		t	f
61	Финансовые вложения. Долговые ценные бумаги	58.2 		t	f
50	Выполненные этапы по незавершенным работам	46   		t	f
6	Амортизация нематериальных активов	05   		t	f
28	Заготовление и приобретение материальных ценностей	15   		t	f
43	Товары. Товары в розничной торговле	41.2 	номенклатура	t	t
7	Оборудование к установке	07   		t	f
62	Финансовые вложения. Предоставленные займы	58.3 		t	f
29	Отклонение в стоимости материальных ценностей	16   		t	f
51	Касса. Касса организации	50.1 		t	f
44	Товары. Тара под товаром и порожняя	41.3 		t	t
63	Финансовые вложения. Вклады по договору простого товарищества	58.4 		t	f
9	Вложения во внеоборотные активы. Приобретение земельных участков	08.1 		t	f
52	Касса. Операционная касса	50.2 		t	f
10	Вложения во внеоборотные активы. Приобретение объектов природопользования	08.2 		t	f
53	Касса. Денежные документы	50.3 		t	f
11	Вложения во внеоборотные активы. Строительство объектов основных средств	08.3 		t	f
71	Расчеты по социальному страхованию и обеспечению. Расчеты по социальному страхованию	69.1 		t	f
54	Расчетные счета	51   		t	f
12	Вложения во внеоборотные активы. Приобретение объектов основных средств	08.4 		t	f
64	Резервы под обесценивание вложений в ценные бумаги	59   		t	f
55	Валютные счета	52   		t	f
13	Вложения во внеоборотные активы. Приобретение нематериальных активов	08.5 		t	f
31	Налог на добавленную стоимость по приобретенным ценностям. НДС при приобретении основных средств	19.1 		t	f
32	Налог на добавленную стоимость по приобретенным ценностям. НДС по приобретенным нематериальным активам	19.2 		t	f
14	Вложения во внеоборотные активы. Перевод молодняка животных в основное стадо	08.6 		t	f
33	Налог на добавленную стоимость по приобретенным ценностям. НДС по приобретенным материально-производственным запасам	19.3 		t	f
15	Вложения во внеоборотные активы. Приобретение взрослых животных	08.7 		t	f
34	Основное производство	20   		t	f
69	Расчеты по долгосрочным кредитам и займам	67   		t	f
35	Полуфабрикаты собственного производства	21   		t	f
65	Расчеты с поставщиками и подрядчиками	60   	vw_контрагенты	t	f
36	Вспомогательные производства	23   		t	f
56	Специальные счета в банках. Аккредитивы	55.1 		t	f
37	Общепроизводственные расходы	25   		t	f
57	Специальные счета в банках. Чековые книжки	55.2 		t	f
58	Специальные счета в банках. Депозитные счета	55.3 		t	f
38	Общехозяйственные расходы	26   		t	f
39	Брак в производстве	28   		t	f
59	Переводы в пути	57   		t	f
40	Обслуживающие производства и хозяйства	29   		t	f
66	Расчеты с покупателями и заказчиками	62   		t	f
67	Резервы по сомнительным долгам	63   		t	f
70	Расчеты по налогам и сборам	68   		t	f
68	Расчеты по краткосрочным кредитам и займам	66   		t	f
72	Расчеты по социальному страхованию и обеспечению. Расчеты по пенсионному обеспечению	69.2 		t	f
73	Расчеты по социальному страхованию и обеспечению. Расчеты по обязательному медицинскому страхованию	69.3 		t	f
94	Продажи. Себестоимость продаж	90.2 		t	f
89	Резервный капитал	82   		t	f
90	Добавочный капитал	83   		t	f
91	Нераспределенная прибыль (непокрытый убыток)	84   		t	f
92	Целевое финансирование	86   		t	f
17	Материалы. Сырье и материалы	10.1 		t	t
20	Материалы. Тара и тарные материалы	10.4 		t	t
99	Прочие доходы и расходы. Прочие расходы	91.2 		t	f
74	Расчеты с персоналом по оплате труда	70   		t	f
21	Материалы. Запасные части	10.5 		t	t
2	Основые средства	01   		t	f
100	Прочие доходы и расходы. Сальдо прочих доходов и расходов	91.9 		t	f
75	Расчеты с подотчетными лицами	71   		t	f
22	Материалы. Прочие материалы	10.6 		t	t
46	Торговая наценка	42   	номенклатура	t	f
23	Материалы. Материалы, переданные в переработку на сторону	10.7 		t	t
24	Материалы. Строительные материалы	10.8 		t	t
47	Готовая продукция	43   		t	f
25	Материалы. Инвентарь и хозяйственные принадлежности	10.9 		t	t
45	Товары. Покупные изделия	41.4 		t	t
48	Расходы на продажу	44   		t	f
76	Расчеты с персоналом по прочим операциям. Расчеты по предоставленным займам	73.1 		t	f
77	Расчеты с персоналом по прочим операциям. Расчеты по возмещению материального ущерба	73.2 		t	f
101	Недостачи и потери от порчи ценностей	94   		t	f
78	Расчеты с учредителями. Расчеты по вкладам в уставный (складочный) капитал	75.1 		t	f
79	Расчеты с учредителями. Расчеты по выплате доходов	75.2 		t	f
102	Резервы предстоящих расходов	96   		t	f
80	Расчеты с разными дебиторами и кредиторами. Расчеты по имущественному и личному страхованию	76.1 		t	f
81	Расчеты с разными дебиторами и кредиторами. Расчеты по претензиям	76.2 		t	f
82	Расчеты с разными дебиторами и кредиторами. Расчеты по причитающимся дивидендам и другим доходам	76.3 		t	f
83	Расчеты с разными дебиторами и кредиторами. Расчеты по депонированным суммам	76.4 		t	f
103	Расходы будущих периодов	97   		t	f
84	Внутрихозяйственные расчеты. Расчеты по выделенному имуществу	79.1 		t	f
85	Внутрихозяйственные расчеты. Расчеты по текущим операциям	79.2 		t	f
86	Внутрихозяйственные расчеты. Расчеты по договору доверительного управления имуществом	79.3 		t	f
87	Уставной капитал	80   		t	f
88	Собственные акции (доли)	81   		t	f
93	Продажи. Выручка	90.1 		t	f
95	Продажи. Налог на добавленную стоимость	90.3 		t	f
96	Продажи. Акцизы	90.4 		t	f
97	Продажи. Прибыль/убыток от продаж	90.9 		t	f
98	Прочие доходы и расходы. Прочие доходы	91.1 		t	f
104	Доходы будущих периодов. Доходы, полученные в счет будущих периодов	98.1 		t	f
105	Доходы будущих периодов. Безвозмездные поступления	98.2 		t	f
106	Доходы будущих периодов. Предстоящие поступления задолженности по недостачам, выявленным за прошлые годы	98.3 		t	f
107	Доходы будущих периодов. Разница между суммой, подлежащей взысканию с виновных лиц, и балансовой стоимостью по недостачам ценностей	98.4 		t	f
108	Прибыли и убытки	99   		t	f
18	Материалы. Покупные полуфабрикаты и комплектующие изделия, конструкции и детали	10.2 		t	t
19	Материалы. Топливо	10.3 		t	t
\.


--
-- TOC entry 2970 (class 0 OID 20340)
-- Dependencies: 204
-- Data for Name: типыобъектов; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "типыобъектов" ("код", "имя") FROM stdin;
1	справочник
2	сальдо
3	топер
4	оборот
5	столбец
\.


--
-- TOC entry 2955 (class 0 OID 20106)
-- Dependencies: 174
-- Data for Name: топер; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "топер" ("код", "опер", "номер", "дбсчет", "крсчет", "имя", "итоги", "осндокумент", "нумератор", "однаоперация", "кол", "дбпост", "крпост", "дбдобав", "крдобав", "дбвыбор", "крвыбор", "дбсалвидим", "крсалвидим", "дбвидим", "крвидим", "форма", "независим", "считать", "переменные") FROM stdin;
3	2	1	41.2	41.1	Товар на складе. Передача в розничную торговлю	+		Накладная1	\N	f	f	f	f	f	f	f	f	t	t	t		f	t	\N
2	1	2	41.1	42	Товар на складе. Учтена торговая наценка				\N	f	f	f	f	f	f	f	f	f	t	f		f	f	\N
1	1	1	41.1	60	Товар на складе. Приход от поставщика	+		Накладная	f	f	f	t	f	f	f	f	f	f	t	f		f	t	\N
\.


--
-- TOC entry 2973 (class 0 OID 20372)
-- Dependencies: 211
-- Data for Name: файлы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "файлы" ("код", "имя", "тип", "значение") FROM stdin;
1	./scripts/формулы1.qs	0	\\x66756e6374696f6e20706172616d65746572734368616e6765642829207b0a2f2f20d097d0b0d0bfd0b8d188d0b5d0bc20d0bdd0b0d0b8d0bcd0b5d0bdd0bed0b2d0b0d0bdd0b8d0b520d184d0b8d180d0bcd18b2dd0bfd0bed181d182d0b0d0b2d189d0b8d0bad0b020d0b220d0bad0bed0bcd0bcd0b5d0bdd182d0b0d180d0b8d0b820d0ba20d0b4d0bed0bad183d0bcd0b5d0bdd182d1830a09d0bdd0b0d0b8d0bcd0b5d0bdd0bed0b2d0b0d0bdd0b8d0b5203d2067657444696374696f6e617279282276775fd0bad0bed0bdd182d180d0b0d0b3d0b5d0bdd182d18b22292e67657456616c75652822d0b8d0bcd18f22293b0a09646f63756d656e74732e73657456616c75652822d09ad0bed0bcd0bcd0b5d0bdd182d0b0d180d0b8d0b9222c20d0bdd0b0d0b8d0bcd0b5d0bdd0bed0b2d0b0d0bdd0b8d0b5293b0a7d0a0ad0bad0bed0bb203d2067657456616c7565282270315f5fd0bad0bed0bb22293b0ad186d0b5d0bdd0b0203d2067657456616c7565282270315f5fd186d0b5d0bdd0b022293b0ad181d183d0bcd0bcd0b0203d2067657456616c7565282270315f5fd181d183d0bcd0bcd0b022293b0a0a6966202867657443757272656e744669656c644e616d652829203d3d202270315f5fd181d183d0bcd0bcd0b02220262620d0bad0bed0bb20213d203029200a7b0a09d186d0b5d0bdd0b0203d20d181d183d0bcd0bcd0b0202f20d0bad0bed0bb3b0a7d0a656c7365200a7b0a09d181d183d0bcd0bcd0b0203d20d0bad0bed0bb202a20d186d0b5d0bdd0b03b0a7d0a0a73657456616c7565282270315f5fd0bad0bed0bb222c20d0bad0bed0bb293b0a73657456616c7565282270315f5fd186d0b5d0bdd0b0222c20d186d0b5d0bdd0b0293b0a73657456616c7565282270315f5fd181d183d0bcd0bcd0b0222c20d181d183d0bcd0bcd0b0293b0a
\.


--
-- TOC entry 2860 (class 2606 OID 20145)
-- Dependencies: 176 176
-- Name: банки_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "банки"
    ADD CONSTRAINT "банки_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2864 (class 2606 OID 20157)
-- Dependencies: 178 178
-- Name: банковские_счета_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "банковские_счета"
    ADD CONSTRAINT "банковские_счета_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2900 (class 2606 OID 20293)
-- Dependencies: 196 196
-- Name: блокпериоды_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "блокпериоды"
    ADD CONSTRAINT "блокпериоды_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2892 (class 2606 OID 20266)
-- Dependencies: 192 192
-- Name: виды_расходов_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "виды_расходов"
    ADD CONSTRAINT "виды_расходов_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2880 (class 2606 OID 20226)
-- Dependencies: 186 186
-- Name: группы_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "группы"
    ADD CONSTRAINT "группы_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2837 (class 2606 OID 20066)
-- Dependencies: 168 168
-- Name: документы_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "документы"
    ADD CONSTRAINT "документы_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2904 (class 2606 OID 20308)
-- Dependencies: 198 198
-- Name: доступ_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "доступ"
    ADD CONSTRAINT "доступ_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2908 (class 2606 OID 20320)
-- Dependencies: 200 200
-- Name: журнал_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "журнал"
    ADD CONSTRAINT "журнал_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2854 (class 2606 OID 20100)
-- Dependencies: 172 172
-- Name: константы_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "константы"
    ADD CONSTRAINT "константы_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2868 (class 2606 OID 20182)
-- Dependencies: 180 180
-- Name: контрагенты_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "контрагенты"
    ADD CONSTRAINT "контрагенты_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2872 (class 2606 OID 20194)
-- Dependencies: 182 182
-- Name: материалы_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "материалы"
    ADD CONSTRAINT "материалы_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2876 (class 2606 OID 20214)
-- Dependencies: 184 184
-- Name: номенклатура_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "номенклатура"
    ADD CONSTRAINT "номенклатура_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2896 (class 2606 OID 20278)
-- Dependencies: 194 194
-- Name: нумераторы_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "нумераторы"
    ADD CONSTRAINT "нумераторы_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2884 (class 2606 OID 20243)
-- Dependencies: 188 188
-- Name: персонал_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "персонал"
    ADD CONSTRAINT "персонал_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2923 (class 2606 OID 20398)
-- Dependencies: 212 212
-- Name: прайсы_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "прайсы"
    ADD CONSTRAINT "прайсы_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2888 (class 2606 OID 20255)
-- Dependencies: 190 190
-- Name: предметы_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "предметы"
    ADD CONSTRAINT "предметы_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2843 (class 2606 OID 20081)
-- Dependencies: 170 170
-- Name: проводки_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "проводки"
    ADD CONSTRAINT "проводки_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2916 (class 2606 OID 20356)
-- Dependencies: 206 206
-- Name: справочник_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "справочник"
    ADD CONSTRAINT "справочник_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2910 (class 2606 OID 20336)
-- Dependencies: 202 202
-- Name: справочники_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "справочники"
    ADD CONSTRAINT "справочники_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2918 (class 2606 OID 20366)
-- Dependencies: 208 208
-- Name: столбцы_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "столбцы"
    ADD CONSTRAINT "столбцы_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2832 (class 2606 OID 20037)
-- Dependencies: 165 165
-- Name: счета_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "счета"
    ADD CONSTRAINT "счета_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2912 (class 2606 OID 20345)
-- Dependencies: 204 204
-- Name: типыобъектов_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "типыобъектов"
    ADD CONSTRAINT "типыобъектов_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2858 (class 2606 OID 20133)
-- Dependencies: 174 174
-- Name: топер_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "топер"
    ADD CONSTRAINT "топер_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2920 (class 2606 OID 20381)
-- Dependencies: 211 211
-- Name: файлы_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "файлы"
    ADD CONSTRAINT "файлы_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2861 (class 1259 OID 20149)
-- Dependencies: 176
-- Name: банки_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "банки_имя_idx" ON "банки" USING btree ("имя");


--
-- TOC entry 2862 (class 1259 OID 20150)
-- Dependencies: 176
-- Name: банки_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "банки_код_idx" ON "банки" USING btree ("код");


--
-- TOC entry 2865 (class 1259 OID 20161)
-- Dependencies: 178
-- Name: банковские_счета_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "банковские_счета_имя_idx" ON "банковские_счета" USING btree ("имя");


--
-- TOC entry 2866 (class 1259 OID 20162)
-- Dependencies: 178
-- Name: банковские_счета_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "банковские_счета_код_idx" ON "банковские_счета" USING btree ("код");


--
-- TOC entry 2901 (class 1259 OID 20297)
-- Dependencies: 196
-- Name: блокпериоды_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "блокпериоды_имя_idx" ON "блокпериоды" USING btree ("имя");


--
-- TOC entry 2902 (class 1259 OID 20298)
-- Dependencies: 196
-- Name: блокпериоды_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "блокпериоды_код_idx" ON "блокпериоды" USING btree ("код");


--
-- TOC entry 2893 (class 1259 OID 20270)
-- Dependencies: 192
-- Name: виды_расходов_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "виды_расходов_имя_idx" ON "виды_расходов" USING btree ("имя");


--
-- TOC entry 2894 (class 1259 OID 20271)
-- Dependencies: 192
-- Name: виды_расходов_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "виды_расходов_код_idx" ON "виды_расходов" USING btree ("код");


--
-- TOC entry 2881 (class 1259 OID 20230)
-- Dependencies: 186
-- Name: группы_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "группы_имя_idx" ON "группы" USING btree ("имя");


--
-- TOC entry 2882 (class 1259 OID 20231)
-- Dependencies: 186
-- Name: группы_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "группы_код_idx" ON "группы" USING btree ("код");


--
-- TOC entry 2838 (class 1259 OID 20070)
-- Dependencies: 168 168 168
-- Name: документы_авто_опер_дата_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "документы_авто_опер_дата_idx" ON "документы" USING btree ("авто", "опер", "дата");


--
-- TOC entry 2839 (class 1259 OID 20071)
-- Dependencies: 168
-- Name: документы_дата_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "документы_дата_idx" ON "документы" USING btree ("дата");


--
-- TOC entry 2840 (class 1259 OID 20072)
-- Dependencies: 168 168 168
-- Name: документы_дата_опер_авто_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "документы_дата_опер_авто_idx" ON "документы" USING btree ("дата", "опер", "авто");


--
-- TOC entry 2841 (class 1259 OID 20073)
-- Dependencies: 168
-- Name: документы_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "документы_код_idx" ON "документы" USING btree ("код");


--
-- TOC entry 2905 (class 1259 OID 20312)
-- Dependencies: 198
-- Name: доступ_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "доступ_имя_idx" ON "доступ" USING btree ("имя");


--
-- TOC entry 2906 (class 1259 OID 20313)
-- Dependencies: 198
-- Name: доступ_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "доступ_код_idx" ON "доступ" USING btree ("код");


--
-- TOC entry 2855 (class 1259 OID 20104)
-- Dependencies: 172
-- Name: константы_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "константы_имя_idx" ON "константы" USING btree ("имя");


--
-- TOC entry 2856 (class 1259 OID 20105)
-- Dependencies: 172
-- Name: константы_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "константы_код_idx" ON "константы" USING btree ("код");


--
-- TOC entry 2869 (class 1259 OID 20186)
-- Dependencies: 180
-- Name: контрагенты_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "контрагенты_имя_idx" ON "контрагенты" USING btree ("имя");


--
-- TOC entry 2870 (class 1259 OID 20187)
-- Dependencies: 180
-- Name: контрагенты_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "контрагенты_код_idx" ON "контрагенты" USING btree ("код");


--
-- TOC entry 2873 (class 1259 OID 20198)
-- Dependencies: 182
-- Name: материалы_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "материалы_имя_idx" ON "материалы" USING btree ("имя");


--
-- TOC entry 2874 (class 1259 OID 20199)
-- Dependencies: 182
-- Name: материалы_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "материалы_код_idx" ON "материалы" USING btree ("код");


--
-- TOC entry 2877 (class 1259 OID 20219)
-- Dependencies: 184
-- Name: номенклатура_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "номенклатура_имя_idx" ON "номенклатура" USING btree ("имя");


--
-- TOC entry 2878 (class 1259 OID 20218)
-- Dependencies: 184
-- Name: номенклатура_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "номенклатура_код_idx" ON "номенклатура" USING btree ("код");


--
-- TOC entry 2897 (class 1259 OID 20283)
-- Dependencies: 194
-- Name: нумераторы_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "нумераторы_имя_idx" ON "нумераторы" USING btree ("имя");


--
-- TOC entry 2898 (class 1259 OID 20284)
-- Dependencies: 194
-- Name: нумераторы_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "нумераторы_код_idx" ON "нумераторы" USING btree ("код");


--
-- TOC entry 2885 (class 1259 OID 20247)
-- Dependencies: 188
-- Name: персонал_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "персонал_имя_idx" ON "персонал" USING btree ("имя");


--
-- TOC entry 2886 (class 1259 OID 20248)
-- Dependencies: 188
-- Name: персонал_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "персонал_код_idx" ON "персонал" USING btree ("код");


--
-- TOC entry 2921 (class 1259 OID 20402)
-- Dependencies: 212
-- Name: прайсы_fts_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "прайсы_fts_idx" ON "прайсы" USING gin (fts);


--
-- TOC entry 2924 (class 1259 OID 20403)
-- Dependencies: 212
-- Name: прайсы_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "прайсы_имя_idx" ON "прайсы" USING btree ("имя" varchar_pattern_ops);


--
-- TOC entry 2925 (class 1259 OID 20404)
-- Dependencies: 212
-- Name: прайсы_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "прайсы_код_idx" ON "прайсы" USING btree ("код");


--
-- TOC entry 2926 (class 1259 OID 20405)
-- Dependencies: 212
-- Name: прайсы_код_товар; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "прайсы_код_товар" ON "прайсы" USING btree ("код_товар");


--
-- TOC entry 2927 (class 1259 OID 20406)
-- Dependencies: 212 212
-- Name: прайсы_код_товар_код_фирмы; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "прайсы_код_товар_код_фирмы" ON "прайсы" USING btree ("код_товар", "код_фирмы");


--
-- TOC entry 2928 (class 1259 OID 20407)
-- Dependencies: 212
-- Name: прайсы_код_фирмы_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "прайсы_код_фирмы_idx" ON "прайсы" USING btree ("код_фирмы");


--
-- TOC entry 2929 (class 1259 OID 20408)
-- Dependencies: 212 212
-- Name: прайсы_код_фирмы_имя; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "прайсы_код_фирмы_имя" ON "прайсы" USING btree ("код_фирмы", "имя");


--
-- TOC entry 2930 (class 1259 OID 20409)
-- Dependencies: 212 212
-- Name: прайсы_код_фирмы_кодвпрайсе; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "прайсы_код_фирмы_кодвпрайсе" ON "прайсы" USING btree ("код_фирмы", "кодвпрайсе");


--
-- TOC entry 2931 (class 1259 OID 20410)
-- Dependencies: 212
-- Name: прайсы_кодвпрайсе; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "прайсы_кодвпрайсе" ON "прайсы" USING btree ("кодвпрайсе");


--
-- TOC entry 2889 (class 1259 OID 20259)
-- Dependencies: 190
-- Name: предметы_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "предметы_имя_idx" ON "предметы" USING btree ("имя");


--
-- TOC entry 2890 (class 1259 OID 20260)
-- Dependencies: 190
-- Name: предметы_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "предметы_код_idx" ON "предметы" USING btree ("код");


--
-- TOC entry 2844 (class 1259 OID 20085)
-- Dependencies: 170 170 170
-- Name: проводки_дбкод_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "проводки_дбкод_idx" ON "проводки" USING btree ("дбсчет", "дбкод", "доккод");


--
-- TOC entry 2845 (class 1259 OID 20086)
-- Dependencies: 170 170
-- Name: проводки_дбсчет_опер_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "проводки_дбсчет_опер_idx" ON "проводки" USING btree ("дбсчет", "опер");


--
-- TOC entry 2846 (class 1259 OID 20087)
-- Dependencies: 170
-- Name: проводки_доккод_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "проводки_доккод_idx" ON "проводки" USING btree ("доккод");


--
-- TOC entry 2847 (class 1259 OID 20088)
-- Dependencies: 170 170 170
-- Name: проводки_доккод_опер_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "проводки_доккод_опер_idx" ON "проводки" USING btree ("доккод", "опер", "номеропер");


--
-- TOC entry 2848 (class 1259 OID 20089)
-- Dependencies: 170 170
-- Name: проводки_доккод_стр_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "проводки_доккод_стр_idx" ON "проводки" USING btree ("доккод", "стр");


--
-- TOC entry 2849 (class 1259 OID 20090)
-- Dependencies: 170
-- Name: проводки_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "проводки_код_idx" ON "проводки" USING btree ("код");


--
-- TOC entry 2850 (class 1259 OID 20091)
-- Dependencies: 170 170 170
-- Name: проводки_кркод_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "проводки_кркод_idx" ON "проводки" USING btree ("крсчет", "кркод", "доккод");


--
-- TOC entry 2851 (class 1259 OID 20092)
-- Dependencies: 170 170
-- Name: проводки_крсчет_опер_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "проводки_крсчет_опер_idx" ON "проводки" USING btree ("крсчет", "опер");


--
-- TOC entry 2852 (class 1259 OID 20093)
-- Dependencies: 170 170
-- Name: проводки_опер_номеропер_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "проводки_опер_номеропер_idx" ON "проводки" USING btree ("опер", "номеропер");


--
-- TOC entry 2835 (class 1259 OID 20055)
-- Dependencies: 167 167
-- Name: сальдо_счет_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "сальдо_счет_код_idx" ON "сальдо" USING btree ("счет", "код");


--
-- TOC entry 2833 (class 1259 OID 20041)
-- Dependencies: 165
-- Name: счета_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "счета_имя_idx" ON "счета" USING btree ("имя");


--
-- TOC entry 2834 (class 1259 OID 20042)
-- Dependencies: 165
-- Name: счета_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "счета_код_idx" ON "счета" USING btree ("код");


--
-- TOC entry 2913 (class 1259 OID 20349)
-- Dependencies: 204
-- Name: типыобъектов_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "типыобъектов_имя_idx" ON "типыобъектов" USING btree ("имя");


--
-- TOC entry 2914 (class 1259 OID 20350)
-- Dependencies: 204
-- Name: типыобъектов_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "типыобъектов_код_idx" ON "типыобъектов" USING btree ("код");


--
-- TOC entry 2939 (class 2620 OID 20526)
-- Dependencies: 256 176
-- Name: testdeleting_банки; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_банки" BEFORE DELETE ON "банки" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2940 (class 2620 OID 20527)
-- Dependencies: 256 178
-- Name: testdeleting_банковские_счета; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_банковские_счета" BEFORE DELETE ON "банковские_счета" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2946 (class 2620 OID 20528)
-- Dependencies: 256 196
-- Name: testdeleting_блокпериоды; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_блокпериоды" BEFORE DELETE ON "блокпериоды" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2944 (class 2620 OID 20529)
-- Dependencies: 256 192
-- Name: testdeleting_виды_расходов; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_виды_расходов" BEFORE DELETE ON "виды_расходов" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2947 (class 2620 OID 20530)
-- Dependencies: 198 256
-- Name: testdeleting_доступ; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_доступ" BEFORE DELETE ON "доступ" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2938 (class 2620 OID 20531)
-- Dependencies: 172 256
-- Name: testdeleting_константы; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_константы" BEFORE DELETE ON "константы" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2941 (class 2620 OID 20534)
-- Dependencies: 256 180
-- Name: testdeleting_контрагенты; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_контрагенты" BEFORE DELETE ON "контрагенты" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2942 (class 2620 OID 20532)
-- Dependencies: 256 182
-- Name: testdeleting_материалы; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_материалы" BEFORE DELETE ON "материалы" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2945 (class 2620 OID 20533)
-- Dependencies: 256 194
-- Name: testdeleting_нумераторы; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_нумераторы" BEFORE DELETE ON "нумераторы" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2943 (class 2620 OID 20535)
-- Dependencies: 256 188
-- Name: testdeleting_персонал; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_персонал" BEFORE DELETE ON "персонал" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2932 (class 2620 OID 20525)
-- Dependencies: 255 167
-- Name: testdeleting_сальдо; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_сальдо" BEFORE DELETE ON "сальдо" FOR EACH ROW EXECUTE PROCEDURE "testdeleting_сальдо"();


--
-- TOC entry 2948 (class 2620 OID 20536)
-- Dependencies: 256 204
-- Name: testdeleting_типыобъектов; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_типыобъектов" BEFORE DELETE ON "типыобъектов" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2949 (class 2620 OID 20542)
-- Dependencies: 212 258
-- Name: tsvectorupdate_прайсы; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "tsvectorupdate_прайсы" BEFORE INSERT OR UPDATE ON "прайсы" FOR EACH ROW EXECUTE PROCEDURE tsvectorupdate();


--
-- TOC entry 2935 (class 2620 OID 20537)
-- Dependencies: 259 170
-- Name: вставитьпроводку; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "вставитьпроводку" BEFORE INSERT ON "проводки" FOR EACH ROW EXECUTE PROCEDURE "вставитьпроводку"();


--
-- TOC entry 2933 (class 2620 OID 20538)
-- Dependencies: 260 167
-- Name: считатьконечноесальдо; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "считатьконечноесальдо" BEFORE INSERT OR UPDATE ON "сальдо" FOR EACH ROW EXECUTE PROCEDURE "считатьконечноесальдо"();


--
-- TOC entry 2936 (class 2620 OID 20539)
-- Dependencies: 170 250
-- Name: считатьпроводку; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "считатьпроводку" BEFORE UPDATE ON "проводки" FOR EACH ROW EXECUTE PROCEDURE "считатьпроводку"();


--
-- TOC entry 2934 (class 2620 OID 20540)
-- Dependencies: 168 261
-- Name: удалитьдокумент; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "удалитьдокумент" BEFORE DELETE ON "документы" FOR EACH ROW EXECUTE PROCEDURE "удалитьдокумент"();


--
-- TOC entry 2937 (class 2620 OID 20541)
-- Dependencies: 170 262
-- Name: удалитьпроводку; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "удалитьпроводку" BEFORE DELETE ON "проводки" FOR EACH ROW EXECUTE PROCEDURE "удалитьпроводку"();


--
-- TOC entry 2979 (class 0 OID 0)
-- Dependencies: 5
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- TOC entry 2981 (class 0 OID 0)
-- Dependencies: 263
-- Name: sp_calcaccoborot(character varying, character varying, character varying); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_calcaccoborot(cacc character varying, cdate1 character varying, cdate2 character varying) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_calcaccoborot(cacc character varying, cdate1 character varying, cdate2 character varying) FROM sa;
GRANT ALL ON FUNCTION sp_calcaccoborot(cacc character varying, cdate1 character varying, cdate2 character varying) TO sa;
GRANT ALL ON FUNCTION sp_calcaccoborot(cacc character varying, cdate1 character varying, cdate2 character varying) TO bookkeeper;


--
-- TOC entry 2982 (class 0 OID 0)
-- Dependencies: 249
-- Name: sp_calcdocoborot(character varying, character varying, character varying); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_calcdocoborot(cacc character varying, cdate1 character varying, cdate2 character varying) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_calcdocoborot(cacc character varying, cdate1 character varying, cdate2 character varying) FROM sa;
GRANT ALL ON FUNCTION sp_calcdocoborot(cacc character varying, cdate1 character varying, cdate2 character varying) TO sa;
GRANT ALL ON FUNCTION sp_calcdocoborot(cacc character varying, cdate1 character varying, cdate2 character varying) TO bookkeeper;


--
-- TOC entry 2983 (class 0 OID 0)
-- Dependencies: 264
-- Name: sp_calcobjoborot(character varying, integer, character varying, character varying); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_calcobjoborot(cacc character varying, pnobj integer, cdate1 character varying, cdate2 character varying) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_calcobjoborot(cacc character varying, pnobj integer, cdate1 character varying, cdate2 character varying) FROM sa;
GRANT ALL ON FUNCTION sp_calcobjoborot(cacc character varying, pnobj integer, cdate1 character varying, cdate2 character varying) TO sa;
GRANT ALL ON FUNCTION sp_calcobjoborot(cacc character varying, pnobj integer, cdate1 character varying, cdate2 character varying) TO bookkeeper;


--
-- TOC entry 2984 (class 0 OID 0)
-- Dependencies: 265
-- Name: sp_calcoborot(character varying, character varying, character varying); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_calcoborot(cacc character varying, cdate1 character varying, cdate2 character varying) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_calcoborot(cacc character varying, cdate1 character varying, cdate2 character varying) FROM sa;
GRANT ALL ON FUNCTION sp_calcoborot(cacc character varying, cdate1 character varying, cdate2 character varying) TO sa;
GRANT ALL ON FUNCTION sp_calcoborot(cacc character varying, cdate1 character varying, cdate2 character varying) TO bookkeeper;


--
-- TOC entry 2985 (class 0 OID 0)
-- Dependencies: 266
-- Name: sp_calctotobjoborot(character varying, character varying, integer, character varying, character varying); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_calctotobjoborot(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_calctotobjoborot(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) FROM sa;
GRANT ALL ON FUNCTION sp_calctotobjoborot(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) TO sa;
GRANT ALL ON FUNCTION sp_calctotobjoborot(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) TO bookkeeper;


--
-- TOC entry 2986 (class 0 OID 0)
-- Dependencies: 251
-- Name: sp_deletedoc(integer); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_deletedoc(ndocid integer) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_deletedoc(ndocid integer) FROM sa;
GRANT ALL ON FUNCTION sp_deletedoc(ndocid integer) TO sa;
GRANT ALL ON FUNCTION sp_deletedoc(ndocid integer) TO bookkeeper;


--
-- TOC entry 2987 (class 0 OID 0)
-- Dependencies: 254
-- Name: sp_deletedocstr(integer, integer); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_deletedocstr(ndocid integer, ndocstr integer) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_deletedocstr(ndocid integer, ndocstr integer) FROM sa;
GRANT ALL ON FUNCTION sp_deletedocstr(ndocid integer, ndocstr integer) TO sa;
GRANT ALL ON FUNCTION sp_deletedocstr(ndocid integer, ndocstr integer) TO bookkeeper;


--
-- TOC entry 2988 (class 0 OID 0)
-- Dependencies: 267
-- Name: sp_insertdoc(integer, character varying); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_insertdoc(noper integer, cdate character varying) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_insertdoc(noper integer, cdate character varying) FROM sa;
GRANT ALL ON FUNCTION sp_insertdoc(noper integer, cdate character varying) TO sa;
GRANT ALL ON FUNCTION sp_insertdoc(noper integer, cdate character varying) TO bookkeeper;


--
-- TOC entry 2989 (class 0 OID 0)
-- Dependencies: 252
-- Name: sp_insertdocstr(integer, integer, character varying, integer, integer); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_insertdocstr(noper integer, ndocid integer, pcparam character varying, pncount integer, pndocstr integer) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_insertdocstr(noper integer, ndocid integer, pcparam character varying, pncount integer, pndocstr integer) FROM sa;
GRANT ALL ON FUNCTION sp_insertdocstr(noper integer, ndocid integer, pcparam character varying, pncount integer, pndocstr integer) TO sa;
GRANT ALL ON FUNCTION sp_insertdocstr(noper integer, ndocid integer, pcparam character varying, pncount integer, pndocstr integer) TO bookkeeper;


--
-- TOC entry 2990 (class 0 OID 0)
-- Dependencies: 253
-- Name: sp_islockedperiod(character varying); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_islockedperiod(cdate character varying) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_islockedperiod(cdate character varying) FROM sa;
GRANT ALL ON FUNCTION sp_islockedperiod(cdate character varying) TO sa;
GRANT ALL ON FUNCTION sp_islockedperiod(cdate character varying) TO bookkeeper;


--
-- TOC entry 2991 (class 0 OID 0)
-- Dependencies: 268
-- Name: sp_maketotobjoborotcommand(character varying, character varying, integer, character varying, character varying); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_maketotobjoborotcommand(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_maketotobjoborotcommand(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) FROM sa;
GRANT ALL ON FUNCTION sp_maketotobjoborotcommand(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) TO sa;
GRANT ALL ON FUNCTION sp_maketotobjoborotcommand(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) TO bookkeeper;


--
-- TOC entry 2992 (class 0 OID 0)
-- Dependencies: 167
-- Name: сальдо; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "сальдо" FROM PUBLIC;
REVOKE ALL ON TABLE "сальдо" FROM sa;
GRANT ALL ON TABLE "сальдо" TO sa;
GRANT SELECT,INSERT,UPDATE ON TABLE "сальдо" TO bookkeeper;


--
-- TOC entry 2993 (class 0 OID 0)
-- Dependencies: 165
-- Name: счета; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "счета" FROM PUBLIC;
REVOKE ALL ON TABLE "счета" FROM sa;
GRANT ALL ON TABLE "счета" TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "счета" TO bookkeeper;


--
-- TOC entry 2994 (class 0 OID 0)
-- Dependencies: 221
-- Name: vw_баланс; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_баланс" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_баланс" FROM sa;
GRANT ALL ON TABLE "vw_баланс" TO sa;
GRANT SELECT ON TABLE "vw_баланс" TO bookkeeper;


--
-- TOC entry 2995 (class 0 OID 0)
-- Dependencies: 196
-- Name: блокпериоды; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "блокпериоды" FROM PUBLIC;
REVOKE ALL ON TABLE "блокпериоды" FROM sa;
GRANT ALL ON TABLE "блокпериоды" TO sa;
GRANT SELECT,UPDATE ON TABLE "блокпериоды" TO bookkeeper;


--
-- TOC entry 2996 (class 0 OID 0)
-- Dependencies: 218
-- Name: vw_блокпериоды; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_блокпериоды" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_блокпериоды" FROM sa;
GRANT ALL ON TABLE "vw_блокпериоды" TO sa;
GRANT SELECT ON TABLE "vw_блокпериоды" TO bookkeeper;


--
-- TOC entry 2997 (class 0 OID 0)
-- Dependencies: 180
-- Name: контрагенты; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "контрагенты" FROM PUBLIC;
REVOKE ALL ON TABLE "контрагенты" FROM sa;
GRANT ALL ON TABLE "контрагенты" TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "контрагенты" TO bookkeeper;


--
-- TOC entry 2998 (class 0 OID 0)
-- Dependencies: 224
-- Name: vw_грузополучатели; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_грузополучатели" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_грузополучатели" FROM sa;
GRANT ALL ON TABLE "vw_грузополучатели" TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "vw_грузополучатели" TO bookkeeper;


--
-- TOC entry 2999 (class 0 OID 0)
-- Dependencies: 168
-- Name: документы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "документы" FROM PUBLIC;
REVOKE ALL ON TABLE "документы" FROM sa;
GRANT ALL ON TABLE "документы" TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "документы" TO bookkeeper;


--
-- TOC entry 3000 (class 0 OID 0)
-- Dependencies: 217
-- Name: vw_пользователи; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_пользователи" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_пользователи" FROM sa;
GRANT ALL ON TABLE "vw_пользователи" TO sa;
GRANT SELECT ON TABLE "vw_пользователи" TO test;


--
-- TOC entry 3001 (class 0 OID 0)
-- Dependencies: 198
-- Name: доступ; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "доступ" FROM PUBLIC;
REVOKE ALL ON TABLE "доступ" FROM sa;
GRANT ALL ON TABLE "доступ" TO sa;


--
-- TOC entry 3002 (class 0 OID 0)
-- Dependencies: 226
-- Name: vw_доступ_к_оборотам; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_доступ_к_оборотам" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_доступ_к_оборотам" FROM sa;
GRANT ALL ON TABLE "vw_доступ_к_оборотам" TO sa;
GRANT SELECT ON TABLE "vw_доступ_к_оборотам" TO PUBLIC;


--
-- TOC entry 3003 (class 0 OID 0)
-- Dependencies: 227
-- Name: vw_доступ_к_сальдо; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_доступ_к_сальдо" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_доступ_к_сальдо" FROM sa;
GRANT ALL ON TABLE "vw_доступ_к_сальдо" TO sa;
GRANT SELECT ON TABLE "vw_доступ_к_сальдо" TO PUBLIC;


--
-- TOC entry 3004 (class 0 OID 0)
-- Dependencies: 202
-- Name: справочники; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "справочники" FROM PUBLIC;
REVOKE ALL ON TABLE "справочники" FROM sa;
GRANT ALL ON TABLE "справочники" TO sa;
GRANT SELECT ON TABLE "справочники" TO bookkeeper;


--
-- TOC entry 3005 (class 0 OID 0)
-- Dependencies: 228
-- Name: vw_доступ_к_справочникам; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_доступ_к_справочникам" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_доступ_к_справочникам" FROM sa;
GRANT ALL ON TABLE "vw_доступ_к_справочникам" TO sa;
GRANT SELECT ON TABLE "vw_доступ_к_справочникам" TO PUBLIC;


--
-- TOC entry 3006 (class 0 OID 0)
-- Dependencies: 174
-- Name: топер; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "топер" FROM PUBLIC;
REVOKE ALL ON TABLE "топер" FROM sa;
GRANT ALL ON TABLE "топер" TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "топер" TO bookkeeper;


--
-- TOC entry 3007 (class 0 OID 0)
-- Dependencies: 229
-- Name: vw_доступ_к_топер; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_доступ_к_топер" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_доступ_к_топер" FROM sa;
GRANT ALL ON TABLE "vw_доступ_к_топер" TO sa;
GRANT SELECT ON TABLE "vw_доступ_к_топер" TO PUBLIC;


--
-- TOC entry 3008 (class 0 OID 0)
-- Dependencies: 230
-- Name: vw_журнал; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_журнал" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_журнал" FROM sa;
GRANT ALL ON TABLE "vw_журнал" TO sa;


--
-- TOC entry 3009 (class 0 OID 0)
-- Dependencies: 172
-- Name: константы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "константы" FROM PUBLIC;
REVOKE ALL ON TABLE "константы" FROM sa;
GRANT ALL ON TABLE "константы" TO sa;


--
-- TOC entry 3010 (class 0 OID 0)
-- Dependencies: 219
-- Name: vw_константы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_константы" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_константы" FROM sa;
GRANT ALL ON TABLE "vw_константы" TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "vw_константы" TO seller;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "vw_константы" TO bookkeeper;


--
-- TOC entry 3011 (class 0 OID 0)
-- Dependencies: 231
-- Name: vw_контрагенты; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_контрагенты" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_контрагенты" FROM sa;
GRANT ALL ON TABLE "vw_контрагенты" TO sa;
GRANT ALL ON TABLE "vw_контрагенты" TO bookkeeper;


--
-- TOC entry 3012 (class 0 OID 0)
-- Dependencies: 182
-- Name: материалы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "материалы" FROM PUBLIC;
REVOKE ALL ON TABLE "материалы" FROM sa;
GRANT ALL ON TABLE "материалы" TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "материалы" TO bookkeeper;


--
-- TOC entry 3013 (class 0 OID 0)
-- Dependencies: 233
-- Name: vw_материалы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_материалы" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_материалы" FROM sa;
GRANT ALL ON TABLE "vw_материалы" TO sa;
GRANT ALL ON TABLE "vw_материалы" TO bookkeeper;


--
-- TOC entry 3014 (class 0 OID 0)
-- Dependencies: 184
-- Name: номенклатура; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "номенклатура" FROM PUBLIC;
REVOKE ALL ON TABLE "номенклатура" FROM sa;
GRANT ALL ON TABLE "номенклатура" TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "номенклатура" TO bookkeeper;


--
-- TOC entry 3015 (class 0 OID 0)
-- Dependencies: 232
-- Name: vw_номенклатура; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_номенклатура" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_номенклатура" FROM sa;
GRANT ALL ON TABLE "vw_номенклатура" TO sa;
GRANT ALL ON TABLE "vw_номенклатура" TO bookkeeper;


--
-- TOC entry 3016 (class 0 OID 0)
-- Dependencies: 170
-- Name: проводки; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "проводки" FROM PUBLIC;
REVOKE ALL ON TABLE "проводки" FROM sa;
GRANT ALL ON TABLE "проводки" TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "проводки" TO bookkeeper;


--
-- TOC entry 3017 (class 0 OID 0)
-- Dependencies: 215
-- Name: vw_справочники_со_столбцами; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_справочники_со_столбцами" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_справочники_со_столбцами" FROM sa;
GRANT ALL ON TABLE "vw_справочники_со_столбцами" TO sa;
GRANT SELECT ON TABLE "vw_справочники_со_столбцами" TO bookkeeper;


--
-- TOC entry 3018 (class 0 OID 0)
-- Dependencies: 208
-- Name: столбцы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "столбцы" FROM PUBLIC;
REVOKE ALL ON TABLE "столбцы" FROM sa;
GRANT ALL ON TABLE "столбцы" TO sa;
GRANT SELECT ON TABLE "столбцы" TO bookkeeper;


--
-- TOC entry 3019 (class 0 OID 0)
-- Dependencies: 216
-- Name: vw_столбцы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_столбцы" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_столбцы" FROM sa;
GRANT ALL ON TABLE "vw_столбцы" TO sa;
GRANT SELECT ON TABLE "vw_столбцы" TO bookkeeper;


--
-- TOC entry 3020 (class 0 OID 0)
-- Dependencies: 223
-- Name: vw_топер; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_топер" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_топер" FROM sa;
GRANT ALL ON TABLE "vw_топер" TO sa;
GRANT SELECT ON TABLE "vw_топер" TO bookkeeper;


--
-- TOC entry 3021 (class 0 OID 0)
-- Dependencies: 176
-- Name: банки; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "банки" FROM PUBLIC;
REVOKE ALL ON TABLE "банки" FROM sa;
GRANT ALL ON TABLE "банки" TO sa;
GRANT SELECT,INSERT,UPDATE ON TABLE "банки" TO bookkeeper;


--
-- TOC entry 3024 (class 0 OID 0)
-- Dependencies: 178
-- Name: банковские_счета; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "банковские_счета" FROM PUBLIC;
REVOKE ALL ON TABLE "банковские_счета" FROM sa;
GRANT ALL ON TABLE "банковские_счета" TO sa;
GRANT SELECT,INSERT,UPDATE ON TABLE "банковские_счета" TO bookkeeper;


--
-- TOC entry 3029 (class 0 OID 0)
-- Dependencies: 192
-- Name: виды_расходов; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "виды_расходов" FROM PUBLIC;
REVOKE ALL ON TABLE "виды_расходов" FROM sa;
GRANT ALL ON TABLE "виды_расходов" TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "виды_расходов" TO bookkeeper;


--
-- TOC entry 3048 (class 0 OID 0)
-- Dependencies: 194
-- Name: нумераторы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "нумераторы" FROM PUBLIC;
REVOKE ALL ON TABLE "нумераторы" FROM sa;
GRANT ALL ON TABLE "нумераторы" TO sa;
GRANT SELECT,UPDATE ON TABLE "нумераторы" TO bookkeeper;


--
-- TOC entry 3051 (class 0 OID 0)
-- Dependencies: 188
-- Name: персонал; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "персонал" FROM PUBLIC;
REVOKE ALL ON TABLE "персонал" FROM sa;
GRANT ALL ON TABLE "персонал" TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "персонал" TO bookkeeper;


--
-- TOC entry 3054 (class 0 OID 0)
-- Dependencies: 212
-- Name: прайсы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "прайсы" FROM PUBLIC;
REVOKE ALL ON TABLE "прайсы" FROM sa;
GRANT ALL ON TABLE "прайсы" TO sa;
GRANT SELECT ON TABLE "прайсы" TO bookkeeper;


--
-- TOC entry 3057 (class 0 OID 0)
-- Dependencies: 190
-- Name: предметы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "предметы" FROM PUBLIC;
REVOKE ALL ON TABLE "предметы" FROM sa;
GRANT ALL ON TABLE "предметы" TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "предметы" TO bookkeeper;


--
-- TOC entry 3070 (class 0 OID 0)
-- Dependencies: 204
-- Name: типыобъектов; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "типыобъектов" FROM PUBLIC;
REVOKE ALL ON TABLE "типыобъектов" FROM sa;
GRANT ALL ON TABLE "типыобъектов" TO sa;
GRANT SELECT ON TABLE "типыобъектов" TO test;
GRANT SELECT ON TABLE "типыобъектов" TO bookkeeper;


--
-- TOC entry 3075 (class 0 OID 0)
-- Dependencies: 211
-- Name: файлы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "файлы" FROM PUBLIC;
REVOKE ALL ON TABLE "файлы" FROM sa;
GRANT ALL ON TABLE "файлы" TO sa;
GRANT SELECT ON TABLE "файлы" TO PUBLIC;


-- Completed on 2011-12-27 09:10:55 MSK

--
-- PostgreSQL database dump complete
--

