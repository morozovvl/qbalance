--
-- PostgreSQL database dump
--

-- Dumped from database version 9.1.3
-- Dumped by pg_dump version 9.1.3
-- Started on 2012-09-29 20:30:53 MSK

SET statement_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- TOC entry 252 (class 3079 OID 12223)
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- TOC entry 3133 (class 0 OID 0)
-- Dependencies: 252
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

--
-- TOC entry 593 (class 1247 OID 16392)
-- Dependencies: 6 161
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
-- TOC entry 596 (class 1247 OID 16395)
-- Dependencies: 6 162
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
-- TOC entry 599 (class 1247 OID 16398)
-- Dependencies: 6 163
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
-- TOC entry 277 (class 1255 OID 16399)
-- Dependencies: 6 810 593
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
-- TOC entry 264 (class 1255 OID 16400)
-- Dependencies: 810 6
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
-- TOC entry 278 (class 1255 OID 16401)
-- Dependencies: 596 810 6
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
-- TOC entry 279 (class 1255 OID 16402)
-- Dependencies: 599 810 6
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
-- TOC entry 266 (class 1255 OID 16403)
-- Dependencies: 810 6
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
-- TOC entry 265 (class 1255 OID 16404)
-- Dependencies: 810 6
-- Name: sp_deletedoc(integer); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION sp_deletedoc(ndocid integer) RETURNS void
    LANGUAGE plpgsql
    AS $_$
DECLARE
	nOperNum INTEGER;
	cAttrName VARCHAR (50);
BEGIN
	nOperNum := (SELECT опер FROM документы WHERE код = ndocid LIMIT 1);
	DELETE FROM документы WHERE код = nDocId;
	DELETE FROM проводки WHERE доккод = nDocId;
	cAttrName = 'атрибуты' || rtrim(ltrim(cast(nOperNum AS VARCHAR(10))));
	IF (SELECT COUNT(*) FROM pg_tables WHERE schemaname='public' AND tablename = cAttrName) > 0 THEN
		EXECUTE 'DELETE FROM ' || cAttrName || ' WHERE доккод=$1;' USING ndocid;
	END IF;
END;
$_$;


ALTER FUNCTION public.sp_deletedoc(ndocid integer) OWNER TO sa;

--
-- TOC entry 283 (class 1255 OID 16405)
-- Dependencies: 6 810
-- Name: sp_deletedocstr(integer, integer); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION sp_deletedocstr(ndocid integer, ndocstr integer) RETURNS void
    LANGUAGE plpgsql
    AS $_$
DECLARE
	nOperNum INTEGER;
	nFreePrvNum INTEGER;
	nMinStrNum INTEGER;
	cDbAcc VARCHAR(5);
	cCrAcc VARCHAR(5);
	curResult REFCURSOR;
BEGIN
	nOperNum := (SELECT опер FROM документы WHERE код = ndocid LIMIT 1);
	nFreePrvNum := (SELECT номер  FROM топер WHERE опер = nOperNum AND независим = true);
	DELETE FROM проводки WHERE доккод = nDocId AND стр = nDocStr;
	IF nFreePrvNum > 0 AND
	   (SELECT count(*) FROM проводки WHERE доккод = ndocid) > 0 AND
	   (SELECT count(*) FROM проводки WHERE доккод = ndocid AND номеропер = nFreePrvNum) = 0 THEN
		OPEN curResult FOR SELECT дбсчет, крсчет FROM топер WHERE опер = nOperNum AND независим = true;
		FETCH first FROM curResult INTO cDbAcc, cCrAcc;
		nMinStrNum := (SELECT min(стр) FROM проводки WHERE доккод = ndocid);
		INSERT INTO проводки (доккод, стр, опер, номеропер, дбсчет, дбкод, крсчет, кркод) VALUES (ndocid, nMinStrNum, nOperNum, nFreePrvNum, cDbAcc, 0, cCrAcc, 0);
	END IF;

	-- Проверим, не использует ли документ таблицу атрибутов, и если использует, то удалим соответствующую строку
	IF (SELECT COUNT(*) FROM топер WHERE опер = nOperNum AND атрибуты = TRUE) > 0 THEN
		EXECUTE 'DELETE FROM атрибуты' || rtrim(ltrim(cast(nOperNum AS VARCHAR(10)))) || ' WHERE доккод=$1 AND стр=$2;' USING nDocId, nDocStr;
	END IF;
END;
$_$;


ALTER FUNCTION public.sp_deletedocstr(ndocid integer, ndocstr integer) OWNER TO sa;

--
-- TOC entry 267 (class 1255 OID 16406)
-- Dependencies: 6 810
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
-- TOC entry 282 (class 1255 OID 16407)
-- Dependencies: 810 6
-- Name: sp_insertdocstr(integer, integer, character varying, integer, integer); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION sp_insertdocstr(noper integer, ndocid integer, pcparam character varying, pncount integer, pndocstr integer) RETURNS void
    LANGUAGE plpgsql
    AS $_$
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
	nFreeCount INTEGER;
	bFreePrv BOOLEAN;
	curResult REFCURSOR;
	cCommand VARCHAR(1000);
BEGIN
	cParam := pcParam;
	nCount := pnCount;
	nDocStr := pnDocStr;

	IF nCount IS NULL THEN
		nCount := 1;
	END IF;
	IF (SELECT COUNT(*) FROM топер WHERE опер = noper AND номер = 0 AND атрибуты = TRUE) > 0 THEN
		EXECUTE 'SELECT max(стр) FROM атрибуты' || rtrim(ltrim(cast(noper AS VARCHAR(10)))) INTO nDocStr;
		IF nDocStr IS NULL THEN
			nDocStr := 1;
		ELSE
			nDocStr := nDocStr + 1;
		END IF;
		WHILE nCount > 0 LOOP
			-- Проверим, не использует ли документ таблицу атрибутов, и если использует, то добавим строку в таблицу атрибутов
			EXECUTE 'INSERT INTO атрибуты' || rtrim(ltrim(cast(noper AS VARCHAR(10)))) || ' (доккод, стр) VALUES ($1, $2);' USING nDocId, nDocStr;
			nCount := nCount - 1;
		END LOOP;
	ELSE
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
		OPEN curResult FOR SELECT дбсчет, крсчет, номер, независим  FROM топер WHERE опер = noper ORDER BY номер;
		WHILE nCount > 0 LOOP
			-- Проверим, не использует ли документ таблицу атрибутов, и если использует, то добавим строку в таблицу атрибутов
			IF (SELECT COUNT(*) FROM топер WHERE опер = noper AND номер = 1 AND атрибуты = TRUE) > 0 THEN
				EXECUTE 'INSERT INTO атрибуты' || rtrim(ltrim(cast(noper AS VARCHAR(10)))) || ' (доккод, стр) VALUES ($1, $2);' USING nDocId, nDocStr;
			END IF;

			cParam1 := cParam;
			FETCH first FROM curResult INTO cDbAcc, cCrAcc, nNum, bFreePrv;
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
				IF bFreePrv THEN 
					nFreeCount := (SELECT count(*) FROM проводки p WHERE p.доккод = nDocId AND p.опер = noper AND p.номеропер = nNum);
					IF nFreeCount = 0 THEN
						INSERT INTO проводки (доккод, стр, опер, номеропер, дбсчет, дбкод, крсчет, кркод, кол, цена, сумма) VALUEs (nDocId, nDocStr, noper, nNum, cDbAcc, nDbId, cCrAcc, nCrId, nQuan, nPrice, nSum);
					END IF;
				ELSE
					INSERT INTO проводки (доккод, стр, опер, номеропер, дбсчет, дбкод, крсчет, кркод, кол, цена, сумма) VALUEs (nDocId, nDocStr, noper, nNum, cDbAcc, nDbId, cCrAcc, nCrId, nQuan, nPrice, nSum);
				END IF;
				FETCH NEXT FROM curResult INTO cDbAcc, cCrAcc, nNum, bFreePrv;
			END LOOP;
			nCount := nCount - 1;
			nDocStr := nDocStr + 1;
		END LOOP;
		CLOSE curResult;
	END IF;
END;
$_$;


ALTER FUNCTION public.sp_insertdocstr(noper integer, ndocid integer, pcparam character varying, pncount integer, pndocstr integer) OWNER TO sa;

--
-- TOC entry 280 (class 1255 OID 16408)
-- Dependencies: 810 6
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
-- TOC entry 281 (class 1255 OID 16409)
-- Dependencies: 6 810
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
-- TOC entry 268 (class 1255 OID 16410)
-- Dependencies: 810 6
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
-- TOC entry 273 (class 1255 OID 16411)
-- Dependencies: 6 810
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
-- TOC entry 269 (class 1255 OID 16412)
-- Dependencies: 810 6
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
-- TOC entry 270 (class 1255 OID 16413)
-- Dependencies: 6 810
-- Name: tsvectorupdate(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION tsvectorupdate() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	NEW.fts = to_tsvector(lower(replace(replace(replace(trim(NEW.имя) || ' ' || trim(NEW.артикул), '-', ' '), ',', ' '), '.', ' ')));
	RETURN NEW;
END;
$$;


ALTER FUNCTION public.tsvectorupdate() OWNER TO sa;

--
-- TOC entry 271 (class 1255 OID 16414)
-- Dependencies: 6 810
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
-- TOC entry 272 (class 1255 OID 16415)
-- Dependencies: 6 810
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
-- TOC entry 274 (class 1255 OID 16416)
-- Dependencies: 810 6
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
-- TOC entry 275 (class 1255 OID 16417)
-- Dependencies: 6 810
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
-- TOC entry 276 (class 1255 OID 16418)
-- Dependencies: 6 810
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

SET default_tablespace = '';

SET default_with_oids = false;

--
-- TOC entry 164 (class 1259 OID 16419)
-- Dependencies: 6
-- Name: objectnames; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE objectnames (
    name character varying(50),
    value character varying(50)
);


ALTER TABLE public.objectnames OWNER TO sa;

--
-- TOC entry 165 (class 1259 OID 16422)
-- Dependencies: 2752 6
-- Name: vw_tables; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW vw_tables AS
    SELECT pg_tables.tablename AS name, 'table'::text AS type FROM pg_tables UNION SELECT pg_views.viewname AS name, 'view'::text AS type FROM pg_views;


ALTER TABLE public.vw_tables OWNER TO sa;

--
-- TOC entry 166 (class 1259 OID 16426)
-- Dependencies: 2753 6
-- Name: vw_types; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW vw_types AS
    SELECT dummy.oid AS "код", dummy.typname AS "имя", dummy.typname_orig AS "тип", dummy.typlen AS "длина" FROM ((SELECT format_type(t.oid, NULL::integer) AS typname, t.typname AS typname_orig, CASE WHEN (t.typelem > (0)::oid) THEN t.typelem ELSE t.oid END AS elemoid, t.typlen, t.typtype, t.oid, nsp.nspname, ((SELECT count(1) AS count FROM pg_type t2 WHERE (t2.typname = t.typname)) > 1) AS isdup FROM (pg_type t JOIN pg_namespace nsp ON ((t.typnamespace = nsp.oid))) WHERE ((((((NOT ((t.typname = 'unknown'::name) AND (nsp.nspname = 'pg_catalog'::name))) AND t.typisdefined) AND (t.typtype = ANY (ARRAY['b'::"char", 'c'::"char", 'd'::"char", 'e'::"char"]))) AND (NOT (EXISTS (SELECT 1 FROM pg_class WHERE (((pg_class.relnamespace = t.typnamespace) AND (pg_class.relname = t.typname)) AND (pg_class.relkind <> 'c'::"char")))))) AND ((t.typname !~~ '_%'::text) OR (NOT (EXISTS (SELECT 1 FROM pg_class WHERE (((pg_class.relnamespace = t.typnamespace) AND (pg_class.relname = ("substring"((t.typname)::text, 2))::name)) AND (pg_class.relkind <> 'c'::"char"))))))) AND (nsp.nspname <> 'information_schema'::name)) UNION SELECT 'bigserial'::text AS text, 'bigserial'::text AS text, 0, 8, 'b'::"char" AS "char", 0, 'pg_catalog'::name AS name, false AS bool) UNION SELECT 'serial'::text AS text, 'serial'::text AS text, 0, 4, 'b'::"char" AS "char", 0, 'pg_catalog'::name AS name, false AS bool) dummy ORDER BY (dummy.nspname <> 'pg_catalog'::name), (dummy.nspname <> 'public'::name), dummy.nspname, dummy.oid;


ALTER TABLE public.vw_types OWNER TO sa;

--
-- TOC entry 167 (class 1259 OID 16431)
-- Dependencies: 2774 2775 2776 2777 2778 2779 2780 2781 2782 6
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
-- TOC entry 168 (class 1259 OID 16443)
-- Dependencies: 2783 2784 2785 2786 2787 6
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
-- TOC entry 169 (class 1259 OID 16451)
-- Dependencies: 2754 6
-- Name: vw_баланс; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_баланс" AS
    SELECT DISTINCT "счета"."код", "счета"."счет", "счета"."имя", COALESCE("дбсальдо"."дбконсальдо", (0)::numeric) AS "дбконсальдо", COALESCE("крсальдо"."крконсальдо", (0)::numeric) AS "крконсальдо" FROM (("счета" LEFT JOIN (SELECT DISTINCT "сальдо"."счет", sum("сальдо"."консальдо") AS "дбконсальдо" FROM "сальдо" WHERE (("сальдо"."консальдо" > (0)::numeric) AND (substr(("сальдо"."счет")::text, 1, 2) <> '00'::text)) GROUP BY "сальдо"."счет" ORDER BY "сальдо"."счет", sum("сальдо"."консальдо")) "дбсальдо" ON (("счета"."счет" = "дбсальдо"."счет"))) LEFT JOIN (SELECT DISTINCT "сальдо"."счет", (- sum("сальдо"."консальдо")) AS "крконсальдо" FROM "сальдо" WHERE (("сальдо"."консальдо" < (0)::numeric) AND (substr(("сальдо"."счет")::text, 1, 2) <> '00'::text)) GROUP BY "сальдо"."счет" ORDER BY "сальдо"."счет", (- sum("сальдо"."консальдо"))) "крсальдо" ON (("счета"."счет" = "крсальдо"."счет"))) ORDER BY "счета"."код", "счета"."счет", "счета"."имя", COALESCE("дбсальдо"."дбконсальдо", (0)::numeric), COALESCE("крсальдо"."крконсальдо", (0)::numeric);


ALTER TABLE public."vw_баланс" OWNER TO sa;

--
-- TOC entry 170 (class 1259 OID 16456)
-- Dependencies: 2789 2790 2791 2792 6
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
-- TOC entry 171 (class 1259 OID 16463)
-- Dependencies: 2755 6
-- Name: vw_блокпериоды; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_блокпериоды" AS
    SELECT b."код", b."имя", b."блокконец", b."начало", b."конец" FROM "блокпериоды" b WHERE (lower(btrim((b."пользователь")::text)) = lower(("current_user"())::text));


ALTER TABLE public."vw_блокпериоды" OWNER TO sa;

--
-- TOC entry 172 (class 1259 OID 16467)
-- Dependencies: 2794 2795 2796 2797 2798 2799 2800 2801 2802 2803 2804 2805 6
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
    "код_фирмы" integer,
    "код_vw_грузополучатели" integer
);


ALTER TABLE public."контрагенты" OWNER TO sa;

--
-- TOC entry 173 (class 1259 OID 16485)
-- Dependencies: 2756 6
-- Name: vw_грузополучатели; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_грузополучатели" AS
    SELECT "контрагенты"."код", "контрагенты"."имя", "контрагенты"."адрес", "контрагенты"."телефон", "контрагенты".e_mail, "контрагенты"."руководитель", "контрагенты"."гл_бухгалтер", "контрагенты"."инн", "контрагенты"."кпп", "контрагенты"."оконх", "контрагенты"."окпо", "контрагенты"."счет", "контрагенты"."код_банки", "контрагенты"."лимит", "контрагенты"."код_vw_грузополучатели" FROM "контрагенты";


ALTER TABLE public."vw_грузополучатели" OWNER TO sa;

--
-- TOC entry 174 (class 1259 OID 16489)
-- Dependencies: 2807 2808 2809 6
-- Name: документы; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "документы" (
    "код" integer NOT NULL,
    "дата" date,
    "датавремя" timestamp without time zone,
    "номер" character varying(12) DEFAULT ''::character varying,
    "комментарий" character varying(100) DEFAULT ''::character varying,
    "сумма" numeric(14,2) DEFAULT 0,
    "описание" text,
    "опер" integer,
    "авто" integer,
    "переменные" bytea
);


ALTER TABLE public."документы" OWNER TO sa;

--
-- TOC entry 175 (class 1259 OID 16498)
-- Dependencies: 2757 6
-- Name: vw_документы; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_документы" AS
    SELECT d."код", d."дата", d."датавремя", d."номер", d."комментарий", d."сумма", d."опер", d."авто", d."описание" FROM ("документы" d JOIN "vw_блокпериоды" b ON (((d."дата" > (b."начало" - 1)) AND (d."дата" < (b."конец" + 1)))));


ALTER TABLE public."vw_документы" OWNER TO sa;

--
-- TOC entry 176 (class 1259 OID 16502)
-- Dependencies: 2758 6
-- Name: vw_пользователи; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_пользователи" AS
    SELECT pg_user.usesysid AS "код", pg_user.usename AS "имя" FROM pg_user WHERE ((pg_user.usename <> 'test'::name) AND (pg_user.usename <> 'postgres'::name));


ALTER TABLE public."vw_пользователи" OWNER TO sa;

--
-- TOC entry 177 (class 1259 OID 16506)
-- Dependencies: 2811 2812 2813 2814 2816 6
-- Name: доступ; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "доступ" (
    "код" integer NOT NULL,
    "меню" boolean DEFAULT true,
    "комментарий" character varying(100) DEFAULT ''::character varying,
    "код_типыобъектов" integer,
    "пользователь" character varying(30) DEFAULT 'sa'::character varying,
    "имя" character varying(100) DEFAULT ''::character varying,
    "доступ" character varying(30) DEFAULT ''::character varying
);


ALTER TABLE public."доступ" OWNER TO sa;

--
-- TOC entry 178 (class 1259 OID 16514)
-- Dependencies: 2759 6
-- Name: vw_доступ; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_доступ" AS
    (SELECT s."имя", s."код_типыобъектов", s."меню", has_table_privilege(s."имя", 'select'::text) AS selectable, CASE WHEN (s.type = 'table'::text) THEN has_table_privilege(s."имя", 'insert'::text) ELSE false END AS insertable, CASE WHEN (s.type = 'table'::text) THEN has_table_privilege(s."имя", 'delete'::text) ELSE false END AS deleteable, CASE WHEN (s.type = 'table'::text) THEN has_table_privilege(s."имя", 'update'::text) ELSE false END AS updateable FROM (SELECT DISTINCT s."имя", s."код_типыобъектов", s."меню", s.type FROM (SELECT rtrim((d."имя")::text) AS "имя", d."код_типыобъектов", d."меню", t.type FROM (("доступ" d JOIN "vw_пользователи" p ON (((rtrim((d."пользователь")::text) = rtrim((p."имя")::text)) OR (rtrim((d."пользователь")::text) = '*'::text)))) JOIN vw_tables t ON ((rtrim((d."имя")::text) = rtrim((t.name)::text)))) WHERE ((upper(rtrim((p."имя")::text)) = upper(rtrim(("current_user"())::text))) OR (btrim(("current_user"())::text) = 'sa'::text))) s ORDER BY s."имя", s."код_типыобъектов", s."меню") s UNION SELECT 'проводки'::text AS "имя", 1 AS "код_типыобъектов", false AS "меню", has_table_privilege(quote_ident('проводки'::text), 'select'::text) AS selectable, has_table_privilege(quote_ident('проводки'::text), 'insert'::text) AS insertable, has_table_privilege(quote_ident('проводки'::text), 'delete'::text) AS deleteable, has_table_privilege(quote_ident('проводки'::text), 'update'::text) AS updateable) UNION SELECT rtrim((d."имя")::text) AS "имя", d."код_типыобъектов", d."меню", true AS selectable, true AS insertable, true AS deleteable, true AS updateable FROM ("доступ" d JOIN "vw_пользователи" p ON (((rtrim((d."пользователь")::text) = rtrim((p."имя")::text)) AND (d."код_типыобъектов" <> 1)))) WHERE ((upper(rtrim((p."имя")::text)) = upper(rtrim(("current_user"())::text))) OR (btrim(("current_user"())::text) = 'sa'::text));


ALTER TABLE public."vw_доступ" OWNER TO sa;

--
-- TOC entry 179 (class 1259 OID 16519)
-- Dependencies: 2760 6
-- Name: vw_доступ_к_оборотам; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_доступ_к_оборотам" AS
    SELECT DISTINCT "счета"."имя", "счета"."счет" FROM ("счета" LEFT JOIN "vw_доступ" ON ((("счета"."счет")::text = "vw_доступ"."имя"))) WHERE ("vw_доступ"."код_типыобъектов" = 4) ORDER BY "счета"."имя", "счета"."счет";


ALTER TABLE public."vw_доступ_к_оборотам" OWNER TO sa;

--
-- TOC entry 180 (class 1259 OID 16523)
-- Dependencies: 2761 6
-- Name: vw_доступ_к_сальдо; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_доступ_к_сальдо" AS
    SELECT DISTINCT "счета"."имя", "счета"."счет" FROM ("счета" JOIN "vw_доступ" ON ((rtrim(("счета"."счет")::text) = rtrim("vw_доступ"."имя")))) WHERE ("vw_доступ"."код_типыобъектов" = 2) ORDER BY "счета"."имя", "счета"."счет";


ALTER TABLE public."vw_доступ_к_сальдо" OWNER TO sa;

--
-- TOC entry 181 (class 1259 OID 16527)
-- Dependencies: 2817 2818 2819 2820 2821 6
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
    "фото" character varying(100) DEFAULT ''::character varying,
    "прототип" character varying(100)
);


ALTER TABLE public."справочники" OWNER TO sa;

--
-- TOC entry 182 (class 1259 OID 16538)
-- Dependencies: 2762 6
-- Name: vw_доступ_к_справочникам; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_доступ_к_справочникам" AS
    SELECT DISTINCT s."имя_в_списке" AS "имя", s."имя_в_форме", d."имя" AS "таблица", d."меню", d.selectable, d.insertable, d.deleteable, d.updateable FROM ("vw_доступ" d LEFT JOIN "справочники" s ON ((upper(rtrim(d."имя")) = upper(rtrim((s."имя")::text))))) WHERE (d."код_типыобъектов" = 1) ORDER BY s."имя_в_списке";


ALTER TABLE public."vw_доступ_к_справочникам" OWNER TO sa;

--
-- TOC entry 183 (class 1259 OID 16543)
-- Dependencies: 2823 2824 2825 2826 2827 2828 2829 2830 2831 2832 2833 2834 2835 2836 2837 2838 2839 2840 2841 2842 2844 6
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
    "переменные" text,
    "атрибуты" boolean DEFAULT false
);


ALTER TABLE public."топер" OWNER TO sa;

--
-- TOC entry 184 (class 1259 OID 16569)
-- Dependencies: 2763 6
-- Name: vw_доступ_к_топер; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_доступ_к_топер" AS
    SELECT DISTINCT "топер"."имя", s."меню", "топер"."опер", "топер"."форма", "топер"."независим", s.selectable, s.insertable, s.deleteable, s.updateable FROM ("топер" JOIN (SELECT "vw_доступ"."имя", "vw_доступ"."код_типыобъектов", "vw_доступ"."меню", "vw_доступ".selectable, "vw_доступ".insertable, "vw_доступ".deleteable, "vw_доступ".updateable FROM "vw_доступ" WHERE ("vw_доступ"."код_типыобъектов" = 3)) s ON ((rtrim(("топер"."опер")::text) = rtrim(s."имя")))) WHERE ((("топер"."номер" = 0) OR ("топер"."номер" = 1)) AND (s."меню" = true)) ORDER BY "топер"."имя", s."меню", "топер"."опер", "топер"."форма", "топер"."независим";


ALTER TABLE public."vw_доступ_к_топер" OWNER TO sa;

--
-- TOC entry 185 (class 1259 OID 16574)
-- Dependencies: 2845 2846 6
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
-- TOC entry 186 (class 1259 OID 16579)
-- Dependencies: 2764 6
-- Name: vw_журнал; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_журнал" AS
    SELECT "журнал"."код", "журнал"."содержание" AS "имя", "журнал"."дата", "журнал"."код_номенклатура" FROM "журнал" ORDER BY "журнал"."датавремя" DESC, "журнал"."содержание";


ALTER TABLE public."vw_журнал" OWNER TO sa;

--
-- TOC entry 187 (class 1259 OID 16583)
-- Dependencies: 2848 2849 6
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
-- TOC entry 188 (class 1259 OID 16588)
-- Dependencies: 2765 6
-- Name: vw_константы; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_константы" AS
    SELECT "константы"."код", "константы"."имя", "константы"."значение", "константы"."комментарий" FROM "константы";


ALTER TABLE public."vw_константы" OWNER TO sa;

--
-- TOC entry 189 (class 1259 OID 16592)
-- Dependencies: 2766 6
-- Name: vw_контрагенты; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_контрагенты" AS
    SELECT "контрагенты"."код", "контрагенты"."имя", "контрагенты"."адрес", "контрагенты"."телефон", "контрагенты".e_mail, "контрагенты"."руководитель", "контрагенты"."гл_бухгалтер", "контрагенты"."инн", "контрагенты"."кпп", "контрагенты"."оконх", "контрагенты"."окпо", "контрагенты"."счет", "контрагенты"."код_банки", "контрагенты"."лимит", "контрагенты"."код_фирмы", "контрагенты"."код_vw_грузополучатели" FROM "контрагенты";


ALTER TABLE public."vw_контрагенты" OWNER TO sa;

--
-- TOC entry 190 (class 1259 OID 16596)
-- Dependencies: 2851 2852 6
-- Name: материалы; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "материалы" (
    "код" integer NOT NULL,
    "имя" character varying(100) DEFAULT ''::character varying,
    "едизм" character varying(5) DEFAULT ''::character varying
);


ALTER TABLE public."материалы" OWNER TO sa;

--
-- TOC entry 191 (class 1259 OID 16601)
-- Dependencies: 2767 6
-- Name: vw_материалы; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_материалы" AS
    SELECT "материалы"."код", "материалы"."имя", "материалы"."едизм" FROM "материалы";


ALTER TABLE public."vw_материалы" OWNER TO sa;

--
-- TOC entry 192 (class 1259 OID 16605)
-- Dependencies: 2854 2855 2856 2857 2858 2859 2860 6
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
    fts tsvector,
    "артикул_оем" character varying(25)
);


ALTER TABLE public."номенклатура" OWNER TO sa;

--
-- TOC entry 193 (class 1259 OID 16618)
-- Dependencies: 2768 6
-- Name: vw_номенклатура; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_номенклатура" AS
    SELECT "номенклатура"."код", "номенклатура"."имя", "номенклатура"."едизм", "номенклатура"."артикул", "номенклатура"."код_группы", "номенклатура"."цена_розн", "номенклатура"."запас", "номенклатура"."имя_на_ценнике", "номенклатура"."тип_ценника", "номенклатура".fts FROM "номенклатура";


ALTER TABLE public."vw_номенклатура" OWNER TO sa;

--
-- TOC entry 194 (class 1259 OID 16622)
-- Dependencies: 2862 2863 2864 6
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
-- TOC entry 195 (class 1259 OID 16628)
-- Dependencies: 2769 6
-- Name: vw_проводки; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_проводки" AS
    SELECT "проводки"."код", "проводки"."дбсчет", "проводки"."дбкод", "проводки"."крсчет", "проводки"."кркод", "проводки"."кол", "проводки"."цена", "проводки"."сумма", "проводки"."стр", "проводки"."доккод", "проводки"."опер", "проводки"."номеропер" FROM "проводки" WHERE ("проводки"."доккод" IN (SELECT "vw_документы"."код" FROM "vw_документы"));


ALTER TABLE public."vw_проводки" OWNER TO sa;

--
-- TOC entry 196 (class 1259 OID 16632)
-- Dependencies: 2770 6
-- Name: vw_справочники_со_столбцами; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_справочники_со_столбцами" AS
    (SELECT s."код", s."имя" FROM "справочники" s UNION SELECT (1000000 + "топер"."опер") AS "код", ('СписокДокументов'::text || btrim((("топер"."опер")::character varying(20))::text)) AS "имя" FROM "топер" WHERE (("топер"."номер" = 0) OR ("топер"."номер" = 1))) UNION SELECT (2000000 + "топер"."опер") AS "код", ('Документ'::text || btrim((("топер"."опер")::character varying(20))::text)) AS "имя" FROM "топер" WHERE (("топер"."номер" = 0) OR ("топер"."номер" = 1));


ALTER TABLE public."vw_справочники_со_столбцами" OWNER TO sa;

--
-- TOC entry 197 (class 1259 OID 16637)
-- Dependencies: 2866 2867 6
-- Name: столбцы; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "столбцы" (
    "код" integer NOT NULL,
    "код_vw_справочники_со_столбцами" integer,
    "имя" character varying(100) DEFAULT ''::character varying,
    "заголовок" character varying(100) DEFAULT ''::character varying,
    "номер" numeric(3,0),
    "толькочтение" boolean
);


ALTER TABLE public."столбцы" OWNER TO sa;

--
-- TOC entry 243 (class 1259 OID 34046)
-- Dependencies: 2773 6
-- Name: vw_столбцы; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW "vw_столбцы" AS
    SELECT s."справочник", s."столбец", s."заголовок", s."номер", s."толькочтение" FROM (SELECT DISTINCT d."имя" AS "справочник", CASE WHEN ("position"((s."имя")::text, '.'::text) > 0) THEN ("substring"((s."имя")::text, ("position"((s."имя")::text, '.'::text) + 1)))::character varying ELSE s."имя" END AS "столбец", s."заголовок", s."номер", s."толькочтение" FROM ("столбцы" s JOIN "vw_справочники_со_столбцами" d ON ((s."код_vw_справочники_со_столбцами" = d."код")))) s WHERE ((s."столбец")::text <> ''::text) ORDER BY s."справочник", s."номер";


ALTER TABLE public."vw_столбцы" OWNER TO postgres;

--
-- TOC entry 198 (class 1259 OID 16652)
-- Dependencies: 2771 6
-- Name: vw_счета; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_счета" AS
    SELECT s."код", s."имя", s."счет", s."имясправочника", s."баланс", s."количество", sp."прототип" FROM ("счета" s LEFT JOIN "справочники" sp ON (((s."имясправочника")::text = (sp."имя")::text)));


ALTER TABLE public."vw_счета" OWNER TO sa;

--
-- TOC entry 199 (class 1259 OID 16656)
-- Dependencies: 2772 6
-- Name: vw_топер; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_топер" AS
    SELECT "топер"."код", "топер"."опер", "топер"."номер", "топер"."имя", "счета"."счет" AS "дбсчет", "счета"."имясправочника" AS "дбсправ", '                                        '::bpchar AS "дбсправалиас", "счета"."количество" AS "дбкол", "топер"."дбпост", "топер"."дбсалвидим", "топер"."дбвидим", "счета1"."счет" AS "крсчет", "счета1"."имясправочника" AS "крсправ", '                                        '::bpchar AS "крсправалиас", "счета1"."количество" AS "кркол", "топер"."однаоперация", "топер"."итоги", "топер"."крпост", "топер"."крсалвидим", "топер"."крвидим", "топер"."независим", "топер"."считать", "топер"."переменные", "топер"."атрибуты" FROM (("топер" LEFT JOIN "счета" "счета" ON ((("топер"."дбсчет")::bpchar = "счета"."счет"))) LEFT JOIN "счета" "счета1" ON ((("топер"."крсчет")::bpchar = "счета1"."счет")));


ALTER TABLE public."vw_топер" OWNER TO sa;

--
-- TOC entry 200 (class 1259 OID 16661)
-- Dependencies: 2869 6
-- Name: адрес; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "адрес" (
    "код" integer NOT NULL,
    "имя" character varying(100) DEFAULT ''::character varying
);


ALTER TABLE public."адрес" OWNER TO sa;

--
-- TOC entry 201 (class 1259 OID 16665)
-- Dependencies: 6 200
-- Name: адрес_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "адрес_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."адрес_код_seq" OWNER TO sa;

--
-- TOC entry 3175 (class 0 OID 0)
-- Dependencies: 201
-- Name: адрес_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "адрес_код_seq" OWNED BY "адрес"."код";


--
-- TOC entry 3176 (class 0 OID 0)
-- Dependencies: 201
-- Name: адрес_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"адрес_код_seq"', 4, true);


--
-- TOC entry 249 (class 1259 OID 34104)
-- Dependencies: 6
-- Name: атрибуты1; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "атрибуты1" (
    "код" integer NOT NULL,
    "доккод" integer NOT NULL,
    "стр" integer NOT NULL,
    "код_прайсы" integer
);


ALTER TABLE public."атрибуты1" OWNER TO sa;

--
-- TOC entry 248 (class 1259 OID 34102)
-- Dependencies: 249 6
-- Name: атрибуты1_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "атрибуты1_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."атрибуты1_код_seq" OWNER TO sa;

--
-- TOC entry 3178 (class 0 OID 0)
-- Dependencies: 248
-- Name: атрибуты1_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "атрибуты1_код_seq" OWNED BY "атрибуты1"."код";


--
-- TOC entry 3179 (class 0 OID 0)
-- Dependencies: 248
-- Name: атрибуты1_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"атрибуты1_код_seq"', 33, true);


--
-- TOC entry 245 (class 1259 OID 34063)
-- Dependencies: 6
-- Name: атрибуты3; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "атрибуты3" (
    "код" integer NOT NULL,
    "доккод" integer NOT NULL,
    "стр" integer NOT NULL,
    "поле1" character varying(100)
);


ALTER TABLE public."атрибуты3" OWNER TO sa;

--
-- TOC entry 244 (class 1259 OID 34061)
-- Dependencies: 6 245
-- Name: атрибуты3_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "атрибуты3_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."атрибуты3_код_seq" OWNER TO sa;

--
-- TOC entry 3181 (class 0 OID 0)
-- Dependencies: 244
-- Name: атрибуты3_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "атрибуты3_код_seq" OWNED BY "атрибуты3"."код";


--
-- TOC entry 3182 (class 0 OID 0)
-- Dependencies: 244
-- Name: атрибуты3_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"атрибуты3_код_seq"', 4, true);


--
-- TOC entry 247 (class 1259 OID 34075)
-- Dependencies: 2932 2933 2934 6
-- Name: атрибуты6; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "атрибуты6" (
    "код" integer NOT NULL,
    "доккод" integer NOT NULL,
    "стр" integer NOT NULL,
    "код_номенклатура" integer,
    "кол" numeric(10,3) DEFAULT 0,
    "старцена" numeric(14,2) DEFAULT 0,
    "новцена" numeric(14,2) DEFAULT 0,
    "старнаценка" numeric(5,2),
    "новнаценка" numeric(5,2),
    "закцена" numeric(14,2)
);


ALTER TABLE public."атрибуты6" OWNER TO sa;

--
-- TOC entry 246 (class 1259 OID 34073)
-- Dependencies: 247 6
-- Name: атрибуты6_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "атрибуты6_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."атрибуты6_код_seq" OWNER TO sa;

--
-- TOC entry 3184 (class 0 OID 0)
-- Dependencies: 246
-- Name: атрибуты6_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "атрибуты6_код_seq" OWNED BY "атрибуты6"."код";


--
-- TOC entry 3185 (class 0 OID 0)
-- Dependencies: 246
-- Name: атрибуты6_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"атрибуты6_код_seq"', 110, true);


--
-- TOC entry 202 (class 1259 OID 16667)
-- Dependencies: 2871 2872 2873 2874 6
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
-- TOC entry 203 (class 1259 OID 16674)
-- Dependencies: 6 202
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
-- TOC entry 3187 (class 0 OID 0)
-- Dependencies: 203
-- Name: банки_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "банки_код_seq" OWNED BY "банки"."код";


--
-- TOC entry 3188 (class 0 OID 0)
-- Dependencies: 203
-- Name: банки_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"банки_код_seq"', 1, false);


--
-- TOC entry 204 (class 1259 OID 16676)
-- Dependencies: 2876 2877 6
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
-- TOC entry 205 (class 1259 OID 16681)
-- Dependencies: 6 204
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
-- TOC entry 3190 (class 0 OID 0)
-- Dependencies: 205
-- Name: банковские_счета_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "банковские_счета_код_seq" OWNED BY "банковские_счета"."код";


--
-- TOC entry 3191 (class 0 OID 0)
-- Dependencies: 205
-- Name: банковские_счета_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"банковские_счета_код_seq"', 1, false);


--
-- TOC entry 206 (class 1259 OID 16683)
-- Dependencies: 170 6
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
-- TOC entry 3192 (class 0 OID 0)
-- Dependencies: 206
-- Name: блокпериоды_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "блокпериоды_код_seq" OWNED BY "блокпериоды"."код";


--
-- TOC entry 3193 (class 0 OID 0)
-- Dependencies: 206
-- Name: блокпериоды_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"блокпериоды_код_seq"', 2, true);


--
-- TOC entry 207 (class 1259 OID 16685)
-- Dependencies: 2879 6
-- Name: виды_расходов; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "виды_расходов" (
    "код" integer NOT NULL,
    "имя" character varying(100) DEFAULT ''::character varying
);


ALTER TABLE public."виды_расходов" OWNER TO sa;

--
-- TOC entry 208 (class 1259 OID 16689)
-- Dependencies: 6 207
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
-- TOC entry 3195 (class 0 OID 0)
-- Dependencies: 208
-- Name: виды_расходов_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "виды_расходов_код_seq" OWNED BY "виды_расходов"."код";


--
-- TOC entry 3196 (class 0 OID 0)
-- Dependencies: 208
-- Name: виды_расходов_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"виды_расходов_код_seq"', 1, false);


--
-- TOC entry 209 (class 1259 OID 16691)
-- Dependencies: 2881 2882 6
-- Name: группы; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "группы" (
    "код" integer NOT NULL,
    "имя" character varying(100) DEFAULT ''::character varying,
    "цены_снижать" boolean DEFAULT false
);


ALTER TABLE public."группы" OWNER TO sa;

--
-- TOC entry 210 (class 1259 OID 16696)
-- Dependencies: 209 6
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
-- TOC entry 3197 (class 0 OID 0)
-- Dependencies: 210
-- Name: группы_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "группы_код_seq" OWNED BY "группы"."код";


--
-- TOC entry 3198 (class 0 OID 0)
-- Dependencies: 210
-- Name: группы_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"группы_код_seq"', 3, true);


--
-- TOC entry 211 (class 1259 OID 16698)
-- Dependencies: 174 6
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
-- TOC entry 3199 (class 0 OID 0)
-- Dependencies: 211
-- Name: документы_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "документы_код_seq" OWNED BY "документы"."код";


--
-- TOC entry 3200 (class 0 OID 0)
-- Dependencies: 211
-- Name: документы_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"документы_код_seq"', 211, true);


--
-- TOC entry 212 (class 1259 OID 16700)
-- Dependencies: 177 6
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
-- TOC entry 3201 (class 0 OID 0)
-- Dependencies: 212
-- Name: доступ_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "доступ_код_seq" OWNED BY "доступ"."код";


--
-- TOC entry 3202 (class 0 OID 0)
-- Dependencies: 212
-- Name: доступ_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"доступ_код_seq"', 68, true);


--
-- TOC entry 213 (class 1259 OID 16702)
-- Dependencies: 185 6
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
-- TOC entry 3203 (class 0 OID 0)
-- Dependencies: 213
-- Name: журнал_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "журнал_код_seq" OWNED BY "журнал"."код";


--
-- TOC entry 3204 (class 0 OID 0)
-- Dependencies: 213
-- Name: журнал_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"журнал_код_seq"', 1, false);


--
-- TOC entry 242 (class 1259 OID 34036)
-- Dependencies: 2929 6
-- Name: запросы; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "запросы" (
    "код" integer NOT NULL,
    "имя" character varying(100) DEFAULT ''::character varying,
    "опер" integer,
    "номер" integer,
    "текст" text
);


ALTER TABLE public."запросы" OWNER TO sa;

--
-- TOC entry 241 (class 1259 OID 34034)
-- Dependencies: 6 242
-- Name: запросы_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "запросы_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."запросы_код_seq" OWNER TO sa;

--
-- TOC entry 3206 (class 0 OID 0)
-- Dependencies: 241
-- Name: запросы_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "запросы_код_seq" OWNED BY "запросы"."код";


--
-- TOC entry 3207 (class 0 OID 0)
-- Dependencies: 241
-- Name: запросы_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"запросы_код_seq"', 2, true);


--
-- TOC entry 240 (class 1259 OID 25802)
-- Dependencies: 2917 2918 2919 2920 2921 2922 2923 2924 2925 2926 2927 6
-- Name: заявка; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "заявка" (
    "код" integer NOT NULL,
    "код_люди" integer,
    "код_номенклатура" integer,
    "код_фирмы" integer,
    "кодвпрайсе" character varying(20) DEFAULT ''::character varying,
    "имявпрайсе" character varying(100) DEFAULT ''::character varying,
    "едизмвпрайсе" character varying(10) DEFAULT ''::character varying,
    "кол" numeric(10,3) DEFAULT 0,
    "цена" numeric(10,2) DEFAULT 0,
    "максцена" numeric(10,2) DEFAULT 0,
    "датазаявки" date,
    "авто" boolean DEFAULT true,
    "быстрее" boolean DEFAULT true,
    "модифицировано" boolean DEFAULT false,
    "код_группы" integer,
    "датаобработки" date,
    "кол_обработанное" numeric(10,3) DEFAULT 0,
    "наличие" character(1),
    "цена_обработанная" numeric(10,2) DEFAULT 0
);


ALTER TABLE public."заявка" OWNER TO sa;

--
-- TOC entry 239 (class 1259 OID 25800)
-- Dependencies: 6 240
-- Name: заявка_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "заявка_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."заявка_код_seq" OWNER TO sa;

--
-- TOC entry 3208 (class 0 OID 0)
-- Dependencies: 239
-- Name: заявка_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "заявка_код_seq" OWNED BY "заявка"."код";


--
-- TOC entry 3209 (class 0 OID 0)
-- Dependencies: 239
-- Name: заявка_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"заявка_код_seq"', 1, false);


--
-- TOC entry 214 (class 1259 OID 16704)
-- Dependencies: 187 6
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
-- TOC entry 3210 (class 0 OID 0)
-- Dependencies: 214
-- Name: константы_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "константы_код_seq" OWNED BY "константы"."код";


--
-- TOC entry 3211 (class 0 OID 0)
-- Dependencies: 214
-- Name: константы_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"константы_код_seq"', 5, true);


--
-- TOC entry 215 (class 1259 OID 16706)
-- Dependencies: 172 6
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
-- TOC entry 3212 (class 0 OID 0)
-- Dependencies: 215
-- Name: контрагенты_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "контрагенты_код_seq" OWNED BY "контрагенты"."код";


--
-- TOC entry 3213 (class 0 OID 0)
-- Dependencies: 215
-- Name: контрагенты_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"контрагенты_код_seq"', 9, true);


--
-- TOC entry 216 (class 1259 OID 16708)
-- Dependencies: 190 6
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
-- TOC entry 3214 (class 0 OID 0)
-- Dependencies: 216
-- Name: материалы_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "материалы_код_seq" OWNED BY "материалы"."код";


--
-- TOC entry 3215 (class 0 OID 0)
-- Dependencies: 216
-- Name: материалы_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"материалы_код_seq"', 1, false);


--
-- TOC entry 217 (class 1259 OID 16710)
-- Dependencies: 6
-- Name: набор1; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "набор1" (
    "код" integer NOT NULL,
    "код_vw_номенклатура" integer,
    "код_адрес" integer
);


ALTER TABLE public."набор1" OWNER TO sa;

--
-- TOC entry 218 (class 1259 OID 16713)
-- Dependencies: 6 217
-- Name: набор1_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "набор1_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."набор1_код_seq" OWNER TO sa;

--
-- TOC entry 3217 (class 0 OID 0)
-- Dependencies: 218
-- Name: набор1_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "набор1_код_seq" OWNED BY "набор1"."код";


--
-- TOC entry 3218 (class 0 OID 0)
-- Dependencies: 218
-- Name: набор1_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"набор1_код_seq"', 69, true);


--
-- TOC entry 251 (class 1259 OID 34140)
-- Dependencies: 2937 2938 2939 2940 2941 2942 2943 6
-- Name: наценки; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "наценки" (
    "код" integer NOT NULL,
    "код_группы" integer,
    "имя" character varying(50) DEFAULT ''::character varying,
    "минпроцент" numeric(5,2) DEFAULT 0,
    "макспроцент" numeric(5,2) DEFAULT 0,
    "минпорогсумма" numeric(10,2) DEFAULT 0,
    "макспорогсумма" numeric(10,2) DEFAULT 0,
    "наценка" numeric(5,2) DEFAULT 0,
    "округление" numeric(1,0) DEFAULT 0
);


ALTER TABLE public."наценки" OWNER TO sa;

--
-- TOC entry 250 (class 1259 OID 34138)
-- Dependencies: 6 251
-- Name: наценки_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "наценки_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."наценки_код_seq" OWNER TO sa;

--
-- TOC entry 3220 (class 0 OID 0)
-- Dependencies: 250
-- Name: наценки_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "наценки_код_seq" OWNED BY "наценки"."код";


--
-- TOC entry 3221 (class 0 OID 0)
-- Dependencies: 250
-- Name: наценки_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"наценки_код_seq"', 11, true);


--
-- TOC entry 219 (class 1259 OID 16715)
-- Dependencies: 192 6
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
-- TOC entry 3222 (class 0 OID 0)
-- Dependencies: 219
-- Name: номенклатура_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "номенклатура_код_seq" OWNED BY "номенклатура"."код";


--
-- TOC entry 3223 (class 0 OID 0)
-- Dependencies: 219
-- Name: номенклатура_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"номенклатура_код_seq"', 62, true);


--
-- TOC entry 220 (class 1259 OID 16717)
-- Dependencies: 2885 2886 6
-- Name: нумераторы; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "нумераторы" (
    "код" integer NOT NULL,
    "имя" character varying(100) DEFAULT ''::character varying,
    "значение" integer DEFAULT 0
);


ALTER TABLE public."нумераторы" OWNER TO sa;

--
-- TOC entry 221 (class 1259 OID 16722)
-- Dependencies: 220 6
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
-- TOC entry 3225 (class 0 OID 0)
-- Dependencies: 221
-- Name: нумераторы_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "нумераторы_код_seq" OWNED BY "нумераторы"."код";


--
-- TOC entry 3226 (class 0 OID 0)
-- Dependencies: 221
-- Name: нумераторы_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"нумераторы_код_seq"', 5, true);


--
-- TOC entry 222 (class 1259 OID 16724)
-- Dependencies: 2888 2889 2890 2891 2892 2893 2894 6
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
-- TOC entry 223 (class 1259 OID 16734)
-- Dependencies: 6 222
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
-- TOC entry 3228 (class 0 OID 0)
-- Dependencies: 223
-- Name: персонал_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "персонал_код_seq" OWNED BY "персонал"."код";


--
-- TOC entry 3229 (class 0 OID 0)
-- Dependencies: 223
-- Name: персонал_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"персонал_код_seq"', 1, false);


--
-- TOC entry 224 (class 1259 OID 16736)
-- Dependencies: 2896 2897 2898 2899 2900 2901 2902 2903 2904 2905 6
-- Name: прайсы; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "прайсы" (
    "код" integer NOT NULL,
    "имя" character varying(100) DEFAULT ''::character varying,
    "код_фирмы" integer,
    "кодвпрайсе" character varying(50) DEFAULT ''::character varying,
    "артикул" character varying(20) DEFAULT ''::character varying,
    "едизм" character varying(10) DEFAULT ''::character varying,
    "дата" date DEFAULT ('now'::text)::date,
    "цена" numeric(10,2) DEFAULT 0,
    "упаковка" integer,
    "наличие" character(1) DEFAULT '+'::character(1),
    "код_номенклатура" integer,
    "кол_прайс" numeric(8,3) DEFAULT 1,
    "кол_номенклатура" numeric(8,3) DEFAULT 1,
    "приоритет" integer DEFAULT 1,
    fts tsvector
);


ALTER TABLE public."прайсы" OWNER TO sa;

--
-- TOC entry 225 (class 1259 OID 16752)
-- Dependencies: 6 224
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
-- TOC entry 3231 (class 0 OID 0)
-- Dependencies: 225
-- Name: прайсы_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "прайсы_код_seq" OWNED BY "прайсы"."код";


--
-- TOC entry 3232 (class 0 OID 0)
-- Dependencies: 225
-- Name: прайсы_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"прайсы_код_seq"', 293, true);


--
-- TOC entry 226 (class 1259 OID 16754)
-- Dependencies: 2907 2908 6
-- Name: предметы; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "предметы" (
    "код" integer NOT NULL,
    "имя" character varying(100) DEFAULT ''::character varying,
    "едизм" character varying(6) DEFAULT ''::character varying
);


ALTER TABLE public."предметы" OWNER TO sa;

--
-- TOC entry 227 (class 1259 OID 16759)
-- Dependencies: 6 226
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
-- TOC entry 3234 (class 0 OID 0)
-- Dependencies: 227
-- Name: предметы_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "предметы_код_seq" OWNED BY "предметы"."код";


--
-- TOC entry 3235 (class 0 OID 0)
-- Dependencies: 227
-- Name: предметы_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"предметы_код_seq"', 1, false);


--
-- TOC entry 228 (class 1259 OID 16761)
-- Dependencies: 6 194
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
-- TOC entry 3236 (class 0 OID 0)
-- Dependencies: 228
-- Name: проводки_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "проводки_код_seq" OWNED BY "проводки"."код";


--
-- TOC entry 3237 (class 0 OID 0)
-- Dependencies: 228
-- Name: проводки_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"проводки_код_seq"', 1341, true);


--
-- TOC entry 229 (class 1259 OID 16763)
-- Dependencies: 6 181
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
-- TOC entry 3238 (class 0 OID 0)
-- Dependencies: 229
-- Name: справочники_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "справочники_код_seq" OWNED BY "справочники"."код";


--
-- TOC entry 3239 (class 0 OID 0)
-- Dependencies: 229
-- Name: справочники_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"справочники_код_seq"', 55, true);


--
-- TOC entry 230 (class 1259 OID 16765)
-- Dependencies: 6 197
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
-- TOC entry 3240 (class 0 OID 0)
-- Dependencies: 230
-- Name: столбцы_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "столбцы_код_seq" OWNED BY "столбцы"."код";


--
-- TOC entry 3241 (class 0 OID 0)
-- Dependencies: 230
-- Name: столбцы_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"столбцы_код_seq"', 867, true);


--
-- TOC entry 231 (class 1259 OID 16767)
-- Dependencies: 6 168
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
-- TOC entry 3242 (class 0 OID 0)
-- Dependencies: 231
-- Name: счета_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "счета_код_seq" OWNED BY "счета"."код";


--
-- TOC entry 3243 (class 0 OID 0)
-- Dependencies: 231
-- Name: счета_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"счета_код_seq"', 105, true);


--
-- TOC entry 232 (class 1259 OID 16769)
-- Dependencies: 2910 6
-- Name: типыобъектов; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "типыобъектов" (
    "код" integer NOT NULL,
    "имя" character varying(20) DEFAULT ''::character varying
);


ALTER TABLE public."типыобъектов" OWNER TO sa;

--
-- TOC entry 233 (class 1259 OID 16773)
-- Dependencies: 6 232
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
-- TOC entry 3245 (class 0 OID 0)
-- Dependencies: 233
-- Name: типыобъектов_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "типыобъектов_код_seq" OWNED BY "типыобъектов"."код";


--
-- TOC entry 3246 (class 0 OID 0)
-- Dependencies: 233
-- Name: типыобъектов_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"типыобъектов_код_seq"', 6, true);


--
-- TOC entry 234 (class 1259 OID 16775)
-- Dependencies: 183 6
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
-- TOC entry 3247 (class 0 OID 0)
-- Dependencies: 234
-- Name: топер_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "топер_код_seq" OWNED BY "топер"."код";


--
-- TOC entry 3248 (class 0 OID 0)
-- Dependencies: 234
-- Name: топер_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"топер_код_seq"', 878, true);


--
-- TOC entry 235 (class 1259 OID 16777)
-- Dependencies: 2912 6
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
-- TOC entry 236 (class 1259 OID 16784)
-- Dependencies: 6 235
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
-- TOC entry 3250 (class 0 OID 0)
-- Dependencies: 236
-- Name: файлы_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "файлы_код_seq" OWNED BY "файлы"."код";


--
-- TOC entry 3251 (class 0 OID 0)
-- Dependencies: 236
-- Name: файлы_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"файлы_код_seq"', 17, true);


--
-- TOC entry 237 (class 1259 OID 16786)
-- Dependencies: 2914 6
-- Name: фирмы; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "фирмы" (
    "код" integer NOT NULL,
    "имя" character varying(100) DEFAULT ''::character varying
);


ALTER TABLE public."фирмы" OWNER TO sa;

--
-- TOC entry 238 (class 1259 OID 16790)
-- Dependencies: 6 237
-- Name: фирмы_код_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "фирмы_код_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."фирмы_код_seq" OWNER TO sa;

--
-- TOC entry 3253 (class 0 OID 0)
-- Dependencies: 238
-- Name: фирмы_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "фирмы_код_seq" OWNED BY "фирмы"."код";


--
-- TOC entry 3254 (class 0 OID 0)
-- Dependencies: 238
-- Name: фирмы_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"фирмы_код_seq"', 3, true);


--
-- TOC entry 2870 (class 2604 OID 16792)
-- Dependencies: 201 200
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "адрес" ALTER COLUMN "код" SET DEFAULT nextval('"адрес_код_seq"'::regclass);


--
-- TOC entry 2935 (class 2604 OID 34107)
-- Dependencies: 249 248 249
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "атрибуты1" ALTER COLUMN "код" SET DEFAULT nextval('"атрибуты1_код_seq"'::regclass);


--
-- TOC entry 2930 (class 2604 OID 34066)
-- Dependencies: 244 245 245
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "атрибуты3" ALTER COLUMN "код" SET DEFAULT nextval('"атрибуты3_код_seq"'::regclass);


--
-- TOC entry 2931 (class 2604 OID 34078)
-- Dependencies: 246 247 247
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "атрибуты6" ALTER COLUMN "код" SET DEFAULT nextval('"атрибуты6_код_seq"'::regclass);


--
-- TOC entry 2875 (class 2604 OID 16793)
-- Dependencies: 203 202
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "банки" ALTER COLUMN "код" SET DEFAULT nextval('"банки_код_seq"'::regclass);


--
-- TOC entry 2878 (class 2604 OID 16794)
-- Dependencies: 205 204
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "банковские_счета" ALTER COLUMN "код" SET DEFAULT nextval('"банковские_счета_код_seq"'::regclass);


--
-- TOC entry 2793 (class 2604 OID 16795)
-- Dependencies: 206 170
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "блокпериоды" ALTER COLUMN "код" SET DEFAULT nextval('"блокпериоды_код_seq"'::regclass);


--
-- TOC entry 2880 (class 2604 OID 16796)
-- Dependencies: 208 207
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "виды_расходов" ALTER COLUMN "код" SET DEFAULT nextval('"виды_расходов_код_seq"'::regclass);


--
-- TOC entry 2883 (class 2604 OID 16797)
-- Dependencies: 210 209
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "группы" ALTER COLUMN "код" SET DEFAULT nextval('"группы_код_seq"'::regclass);


--
-- TOC entry 2810 (class 2604 OID 16798)
-- Dependencies: 211 174
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "документы" ALTER COLUMN "код" SET DEFAULT nextval('"документы_код_seq"'::regclass);


--
-- TOC entry 2815 (class 2604 OID 16799)
-- Dependencies: 212 177
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "доступ" ALTER COLUMN "код" SET DEFAULT nextval('"доступ_код_seq"'::regclass);


--
-- TOC entry 2847 (class 2604 OID 16800)
-- Dependencies: 213 185
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "журнал" ALTER COLUMN "код" SET DEFAULT nextval('"журнал_код_seq"'::regclass);


--
-- TOC entry 2928 (class 2604 OID 34039)
-- Dependencies: 242 241 242
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "запросы" ALTER COLUMN "код" SET DEFAULT nextval('"запросы_код_seq"'::regclass);


--
-- TOC entry 2916 (class 2604 OID 25805)
-- Dependencies: 240 239 240
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "заявка" ALTER COLUMN "код" SET DEFAULT nextval('"заявка_код_seq"'::regclass);


--
-- TOC entry 2850 (class 2604 OID 16801)
-- Dependencies: 214 187
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "константы" ALTER COLUMN "код" SET DEFAULT nextval('"константы_код_seq"'::regclass);


--
-- TOC entry 2806 (class 2604 OID 16802)
-- Dependencies: 215 172
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "контрагенты" ALTER COLUMN "код" SET DEFAULT nextval('"контрагенты_код_seq"'::regclass);


--
-- TOC entry 2853 (class 2604 OID 16803)
-- Dependencies: 216 190
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "материалы" ALTER COLUMN "код" SET DEFAULT nextval('"материалы_код_seq"'::regclass);


--
-- TOC entry 2884 (class 2604 OID 16804)
-- Dependencies: 218 217
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "набор1" ALTER COLUMN "код" SET DEFAULT nextval('"набор1_код_seq"'::regclass);


--
-- TOC entry 2936 (class 2604 OID 34143)
-- Dependencies: 250 251 251
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "наценки" ALTER COLUMN "код" SET DEFAULT nextval('"наценки_код_seq"'::regclass);


--
-- TOC entry 2861 (class 2604 OID 16805)
-- Dependencies: 219 192
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "номенклатура" ALTER COLUMN "код" SET DEFAULT nextval('"номенклатура_код_seq"'::regclass);


--
-- TOC entry 2887 (class 2604 OID 16806)
-- Dependencies: 221 220
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "нумераторы" ALTER COLUMN "код" SET DEFAULT nextval('"нумераторы_код_seq"'::regclass);


--
-- TOC entry 2895 (class 2604 OID 16807)
-- Dependencies: 223 222
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "персонал" ALTER COLUMN "код" SET DEFAULT nextval('"персонал_код_seq"'::regclass);


--
-- TOC entry 2906 (class 2604 OID 16808)
-- Dependencies: 225 224
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "прайсы" ALTER COLUMN "код" SET DEFAULT nextval('"прайсы_код_seq"'::regclass);


--
-- TOC entry 2909 (class 2604 OID 16809)
-- Dependencies: 227 226
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "предметы" ALTER COLUMN "код" SET DEFAULT nextval('"предметы_код_seq"'::regclass);


--
-- TOC entry 2865 (class 2604 OID 16810)
-- Dependencies: 228 194
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "проводки" ALTER COLUMN "код" SET DEFAULT nextval('"проводки_код_seq"'::regclass);


--
-- TOC entry 2822 (class 2604 OID 16811)
-- Dependencies: 229 181
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "справочники" ALTER COLUMN "код" SET DEFAULT nextval('"справочники_код_seq"'::regclass);


--
-- TOC entry 2868 (class 2604 OID 16812)
-- Dependencies: 230 197
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "столбцы" ALTER COLUMN "код" SET DEFAULT nextval('"столбцы_код_seq"'::regclass);


--
-- TOC entry 2788 (class 2604 OID 16813)
-- Dependencies: 231 168
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "счета" ALTER COLUMN "код" SET DEFAULT nextval('"счета_код_seq"'::regclass);


--
-- TOC entry 2911 (class 2604 OID 16814)
-- Dependencies: 233 232
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "типыобъектов" ALTER COLUMN "код" SET DEFAULT nextval('"типыобъектов_код_seq"'::regclass);


--
-- TOC entry 2843 (class 2604 OID 16815)
-- Dependencies: 234 183
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "топер" ALTER COLUMN "код" SET DEFAULT nextval('"топер_код_seq"'::regclass);


--
-- TOC entry 2913 (class 2604 OID 16816)
-- Dependencies: 236 235
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "файлы" ALTER COLUMN "код" SET DEFAULT nextval('"файлы_код_seq"'::regclass);


--
-- TOC entry 2915 (class 2604 OID 16817)
-- Dependencies: 238 237
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "фирмы" ALTER COLUMN "код" SET DEFAULT nextval('"фирмы_код_seq"'::regclass);


--
-- TOC entry 3094 (class 0 OID 16419)
-- Dependencies: 164
-- Data for Name: objectnames; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY objectnames (name, value) FROM stdin;
\.


--
-- TOC entry 3109 (class 0 OID 16661)
-- Dependencies: 200
-- Data for Name: адрес; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "адрес" ("код", "имя") FROM stdin;
1	0
2	Брак
3	Недовоз
\.


--
-- TOC entry 3126 (class 0 OID 34104)
-- Dependencies: 249
-- Data for Name: атрибуты1; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "атрибуты1" ("код", "доккод", "стр", "код_прайсы") FROM stdin;
25	194	1	276
26	194	2	279
27	194	3	278
28	194	4	282
29	196	1	\N
30	199	1	276
31	199	2	279
32	199	3	278
33	199	4	282
\.


--
-- TOC entry 3124 (class 0 OID 34063)
-- Dependencies: 245
-- Data for Name: атрибуты3; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "атрибуты3" ("код", "доккод", "стр", "поле1") FROM stdin;
\.


--
-- TOC entry 3125 (class 0 OID 34075)
-- Dependencies: 247
-- Data for Name: атрибуты6; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "атрибуты6" ("код", "доккод", "стр", "код_номенклатура", "кол", "старцена", "новцена", "старнаценка", "новнаценка", "закцена") FROM stdin;
106	210	1	39	1.000	50.00	141.30	-48.69	45.00	97.45
107	210	2	38	1.000	150.00	177.71	22.39	45.00	122.56
108	210	3	40	1.000	0.00	131.11	-100.00	45.00	90.42
109	210	4	41	1.000	230.00	107.08	211.44	45.00	73.85
110	210	5	16	1.000	410.00	315.90	75.21	35.00	234.00
\.


--
-- TOC entry 3110 (class 0 OID 16667)
-- Dependencies: 202
-- Data for Name: банки; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "банки" ("код", "имя", "бик", "корсчет", "счет") FROM stdin;
\.


--
-- TOC entry 3111 (class 0 OID 16676)
-- Dependencies: 204
-- Data for Name: банковские_счета; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "банковские_счета" ("код", "имя", "счет", "код_банки") FROM stdin;
\.


--
-- TOC entry 3097 (class 0 OID 16456)
-- Dependencies: 170
-- Data for Name: блокпериоды; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "блокпериоды" ("код", "имя", "блокконец", "начало", "конец", "пользователь") FROM stdin;
1		\N	2010-01-01	2012-09-30	sa
\.


--
-- TOC entry 3112 (class 0 OID 16685)
-- Dependencies: 207
-- Data for Name: виды_расходов; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "виды_расходов" ("код", "имя") FROM stdin;
\.


--
-- TOC entry 3113 (class 0 OID 16691)
-- Dependencies: 209
-- Data for Name: группы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "группы" ("код", "имя", "цены_снижать") FROM stdin;
1	Запчасти ВАЗ	f
3	Аксессуары	f
\.


--
-- TOC entry 3099 (class 0 OID 16489)
-- Dependencies: 174
-- Data for Name: документы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "документы" ("код", "дата", "датавремя", "номер", "комментарий", "сумма", "описание", "опер", "авто", "переменные") FROM stdin;
\.


--
-- TOC entry 3100 (class 0 OID 16506)
-- Dependencies: 177
-- Data for Name: доступ; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "доступ" ("код", "меню", "комментарий", "код_типыобъектов", "пользователь", "имя", "доступ") FROM stdin;
3	t		1	sa	справочники	
4	t		1	sa	столбцы	
5	f		1	sa	vw_справочники	
6	t		1	sa	доступ	
8	t		1	sa	счета	
9	f		1	sa	vw_справочники_со_столбцами	
10	t		1	sa	топер	
11	t		1	sa	нумераторы	
12	t		1	sa	номенклатура	
14	t		1	sa	контрагенты	
15	t		1	sa	группы	
16	f		1	sa	vw_контрагенты	
17	f		1	sa	vw_номенклатура	
18	t		1	sa	банки	
19	f		1	sa	vw_грузополучатели	
21	f		5	*	Документ2.p1__цена	ro
22	t		1	sa	константы	
23	f		5	*	номенклатура.цена_розн	ro
39	t		1	sa	адрес	
60	f		1	sa	набор1	
24	f		1	sa	блокпериоды	
7	f		1	sa	типыобъектов	
40	f		1	sa	vw_types	
63	t		3	sa	5	
64	t		1	sa	фирмы	
66	t		1	sa	прайсы	
68	t		1	sa	наценки	
1	f		1	sa	vw_доступ_к_справочникам	
2	f		1	sa	vw_доступ_к_топер	
67	t		3	sa	6	
31	t		3	sa	3	
62	t		3	sa	4	
20	t		3	sa	2	
13	t		3	sa	1	
\.


--
-- TOC entry 3103 (class 0 OID 16574)
-- Dependencies: 185
-- Data for Name: журнал; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "журнал" ("код", "имя", "датавремя", "содержание", "код_номенклатура", "дата") FROM stdin;
\.


--
-- TOC entry 3123 (class 0 OID 34036)
-- Dependencies: 242
-- Data for Name: запросы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "запросы" ("код", "имя", "опер", "номер", "текст") FROM stdin;
1	Товар вне продажи	2	1	SELECT счет, код, конкол, концена, консальдо FROM сальдо WHERE конкол <> 0 AND счет = '41.1';
2	Товар в 0 адресе	6	1	SELECT t.код, t.имя, t.конкол, t.закцена, t.цена_розн, n.минпроцент, n.макспроцент, n.наценка, n.округление\nFROM (SELECT n.код, n.имя, n.код_группы, n.цена_розн, s.конкол, s.консальдо/s.конкол AS закцена\n      FROM (SELECT n.код_vw_номенклатура as код_номенклатура, SUM(s.конкол) AS конкол, SUM(s.консальдо) AS консальдо  \n            FROM сальдо s INNER JOIN набор1 n ON s.код = n.код\n            WHERE s.счет = '41.2' AND s.конкол <> 0\n            GROUP BY n.код_vw_номенклатура) s \n            INNER JOIN (SELECT n.код_vw_номенклатура\n\t\t\tFROM сальдо s INNER JOIN набор1 n ON s.код = n.код AND n.код_адрес = 1\n\t\t\tWHERE s.счет = '41.2' AND s.конкол <> 0) t ON s.код_номенклатура = t.код_vw_номенклатура \n\t    INNER JOIN номенклатура n ON s.код_номенклатура = n.код\n      WHERE s.конкол <> 0) t\n      JOIN наценки n ON t.код_группы = n.код_группы AND t.закцена >= n.минпорогсумма AND t.закцена < n.макспорогсумма\nORDER BY t.имя
\.


--
-- TOC entry 3122 (class 0 OID 25802)
-- Dependencies: 240
-- Data for Name: заявка; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "заявка" ("код", "код_люди", "код_номенклатура", "код_фирмы", "кодвпрайсе", "имявпрайсе", "едизмвпрайсе", "кол", "цена", "максцена", "датазаявки", "авто", "быстрее", "модифицировано", "код_группы", "датаобработки", "кол_обработанное", "наличие", "цена_обработанная") FROM stdin;
\.


--
-- TOC entry 3104 (class 0 OID 16583)
-- Dependencies: 187
-- Data for Name: константы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "константы" ("код", "имя", "значение", "комментарий") FROM stdin;
1	база_фото	enterprise_pictures	\N
2	наименование_фирмы	ИП Мальцев В.А.	\N
3	руководитель_фирмы	Мальцев В.А.	\N
4	гл_бухгалтер_фирмы	Смирнова Т.В.	\N
\.


--
-- TOC entry 3098 (class 0 OID 16467)
-- Dependencies: 172
-- Data for Name: контрагенты; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "контрагенты" ("код", "имя", "адрес", "телефон", e_mail, "руководитель", "гл_бухгалтер", "инн", "кпп", "оконх", "окпо", "счет", "код_банки", "лимит", "код_фирмы", "код_vw_грузополучатели") FROM stdin;
1	ООО "АвтоОпт"	г.Москва, ул.Декабристов 15	(495)236-67-89		Сидоров Е.А.							\N	0.00	\N	\N
2	ТД "Автодеталь"	г.Н.Новгород, ул.Социалистическая 77	(8312)45-97-65		Петров С.Н.							\N	0.00	\N	\N
9	Общество с ограниченной ответственностью "Дальтек"	610014, Кировская область, г. Киров, ул. Производственная, дом № 27 а, 1 этаж										\N	0.00	3	\N
\.


--
-- TOC entry 3105 (class 0 OID 16596)
-- Dependencies: 190
-- Data for Name: материалы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "материалы" ("код", "имя", "едизм") FROM stdin;
\.


--
-- TOC entry 3114 (class 0 OID 16710)
-- Dependencies: 217
-- Data for Name: набор1; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "набор1" ("код", "код_vw_номенклатура", "код_адрес") FROM stdin;
61	38	1
62	40	1
63	39	1
64	41	1
65	0	0
66	61	0
67	16	1
68	16	4
69	16	2
\.


--
-- TOC entry 3127 (class 0 OID 34140)
-- Dependencies: 251
-- Data for Name: наценки; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "наценки" ("код", "код_группы", "имя", "минпроцент", "макспроцент", "минпорогсумма", "макспорогсумма", "наценка", "округление") FROM stdin;
9	3	3.Закупочная цена до 200 рублей	35.00	70.00	10.00	200.00	45.00	2
1	1	1.Закупочная цена до 1 рубля	175.00	275.00	0.00	1.00	200.00	1
2	1	2.Закупочная цена до 10 рублей	55.00	80.00	1.00	10.00	60.00	1
3	1	3.Закупочная цена до 200 рублей	35.00	70.00	10.00	200.00	45.00	2
4	1	4.Закупочная цена до 1000 рублей	30.00	60.00	200.00	1000.00	35.00	3
5	1	5.Закупочная цена свыше 1000 рублей	20.00	50.00	1000.00	1000000.00	25.00	3
10	3	4.Закупочная цена до 1000 рублей	30.00	60.00	200.00	1000.00	35.00	3
6	3	1.Закупочная цена до 1 рубля	175.00	275.00	0.00	1.00	200.00	1
11	3	5.Закупочная цена свыше 1000 рублей	20.00	50.00	1000.00	1000000.00	25.00	3
8	3	2.Закупочная цена до 10 рублей	55.00	80.00	1.00	10.00	60.00	1
\.


--
-- TOC entry 3106 (class 0 OID 16605)
-- Dependencies: 192
-- Data for Name: номенклатура; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "номенклатура" ("код", "имя", "едизм", "артикул", "код_группы", "цена_розн", "запас", "имя_на_ценнике", "тип_ценника", fts, "артикул_оем") FROM stdin;
18	фильтр топливный (GUR-612)  дизель универсал	шт		\N	37.00	0		3	'612':4 'gur':3 'дизел':5 'топливн':2 'универса':6 'фильтр':1	\N
2	паста притирочная алмазная (20гр)	шт		\N	56.00	0		3	'20гр':4 'алмазн':3 'паст':1 'притирочн':2	\N
4	препарат "РЕМЕТАЛЛ" для двигателя (120мл)	шт		\N	165.00	0		3	'120мл':5 'двигател':4 'препарат':1 'реметалл':2	\N
5	очиститель рук "Защитные перчатки" (40г)	шт		\N	27.00	0		3	'40г':5 'защитн':3 'очистител':1 'перчатк':4 'рук':2	\N
8	крестовина 2121 "Master-Sport" (Германия)	шт		1	178.00	0		3	'2121':2 'master':3 'sport':4 'герман':5 'крестовин':1	\N
28	диск сцепления дв. 406 (ЗМЗ)	шт		\N	770.00	0		3	'406':4 'дв':3 'диск':1 'змз':5 'сцеплен':2	40637-1601130
3	брелок оригинальный (хром)	шт		3	47.00	0		3	'брелок':1 'оригинальн':2 'хром':3	\N
29	ремкомплект рулевой рейки М-2126 (полный)	к-т		\N	520.00	0		3	'2126':5 'м':4 'полн':6 'рейк':3 'ремкомплект':1 'рулев':2	\N
27	ось верхнего рычага 2121	шт		1	97.00	0		3	'2121':4 'верхн':2 'о':1 'рычаг':3	\N
7	лампа H3 12В (55Вт) галогенн. (отеч.)	шт		\N	196.00	0		3	'12в':3 '55вт':4 'h3':2 'галоген':5 'ламп':1 'отеч':6	\N
9	стартер ГАЗ, УАЗ дв.406,405,409 (42.3708-10/11) БАТЭ	шт	42.3708-10 	\N	2440.00	0		3	'10':14 '10/11':10 '3708':9,13 '405':6 '406':5 '409':7 '42':8,12 'батэ':11 'газ':2 'дв':4 'стартер':1 'уаз':3	\N
22	фара противотуманная CIRIE круглая (лазерная)	к-т		\N	422.00	0		3	'ciri':3 'кругл':4 'лазерн':5 'противотума':2 'фар':1	\N
12	размораживатель замков "LUX-OIL" (50мл)	шт		\N	35.00	0		3	'50мл':5 'lux':3 'oil':4 'замк':2 'размораживател':1	\N
13	крестовина М-412 "Master-Sport" (Германия)	шт		\N	167.00	0		3	'412':3 'master':4 'sport':5 'герман':6 'крестовин':1 'м':2	\N
31	прокладка поддона дв.402	шт		\N	75.00	0		3	'402':4 'дв':3 'поддон':2 'прокладк':1	\N
14	пружина задней подвески 1111	шт		1	380.00	0		3	'1111':4 'задн':2 'подвеск':3 'пружин':1	\N
30	реле-регулятор 2110, дв. 406 (611.3702-11) в сборе с ЩУ	шт		1	104.00	0		3	'11':8 '2110':3 '3702':7 '406':5 '611':6 'дв':4 'регулятор':2 'рел':1 'сбор':10 'щу':12	\N
33	трубка сцепления 2101	шт		1	20.00	0		3	'2101':3 'сцеплен':2 'трубк':1	\N
17	фильтр топливный 2108 (инжектор) FRAM	шт		1	274.00	0		3	'2108':3 'fram':5 'инжектор':4 'топливн':2 'фильтр':1	\N
1	цилиндр тормозной 2108 главный	шт		1	530.00	0		3	'2108':3 'главн':4 'тормозн':2 'цилиндр':1	\N
6	бендикс 2101 "Master-Sport" (Германия)	шт		1	183.00	0		3	'2101':2 'master':3 'sport':4 'бендикс':1 'герман':5	\N
55	антирадар Crunch 213В дисплей светодиод	шт		3	0.00	0		3	'213в':3 'crunch':2 'антирадар':1 'диспл':4 'светодиод':5	\N
56	освежитель воздуха BUGALE ваниль (60мл)	шт		3	0.00	0		3	'60мл':5 'bugal':3 'ванил':4 'воздух':2 'освежител':1	\N
57	освежитель воздуха Business Class гелевый (60мл)	шт		3	0.00	0		3	'60мл':6 'busi':3 'class':4 'воздух':2 'гелев':5 'освежител':1	\N
34	ключ натяжения ремня ГРМ 2108 	шт		1	26.00	0		3	'2108':5 'грм':4 'ключ':1 'натяжен':2 'ремн':3	\N
23	ремкомплект карбюратора 1111 (Челябинск)	к-т		1	71.00	0		3	'1111':3 'карбюратор':2 'ремкомплект':1 'челябинск':4	\N
20	палец шаровый нижний с/п 2101 (FENOX)	шт		1	188.00	0		3	'2101':6 'fenox':7 'нижн':3 'п':5 'палец':1 'шаров':2	2101-2904082
11	подшипник 256907 ступицы передний 2108, М-2126 "Herzog" (Германия)	шт		1	193.00	0		3	'2108':5 '2126':7 '256907':2 'herzog':8 'герман':9 'м':6 'передн':4 'подшипник':1 'ступиц':3	2108-3103020
19	ремень генератора 2108, Таврия (710) зубч. "Хорс"	шт		1	52.00	0		3	'2108':3 '710':5 'генератор':2 'зубч':6 'ремен':1 'тавр':4 'хорс':7	2108-3701720
24	ремкомплект стоек 2108	к-т		1	22.00	0		3	'2108':3 'ремкомплект':1 'стоек':2	\N
32	шестерня КПП 5-й передачи 2108, 2110	шт		1	361.00	0		3	'2108':6 '2110':7 '5':3 'й':4 'кпп':2 'передач':5 'шестерн':1	2108-1701158
35	термостат 2101	шт		1	263.00	0		3	'2101':2 'термостат':1	2101-1306010
25	шатун 2108, 21099, 1111	шт		1	470.00	0		3	'1111':4 '2108':2 '21099':3 'шатун':1	2108-1004045
42	антенна HYUNDAI внутрисалонная активная	шт		3	0.00	0		3	'hyundai':2 'активн':4 'антен':1 'внутрисалон':3	\N
21	свеча BERU Z21 ВАЗ-2110 8-клап.  (Германия)	шт		\N	76.00	0		3	'2110':5 '8':6 'beru':2 'z21':3 'ваз':4 'герман':8 'клап':7 'свеч':1	\N
40	антенна AN4112 резиновая	шт	AN4112	3	0.00	0		3	'an4112':2,4 'антен':1 'резинов':3	\N
38	антенна AN110 на желобок	шт	AN110	3	150.00	0		3	'an110':2,5 'антен':1 'желобок':4	\N
43	антенна MYSTERY внутрисалонная активная 	шт		3	0.00	0		3	'mysteri':2 'активн':4 'антен':1 'внутрисалон':3	\N
44	антенна Ratex-R01A (АМ, УКВ, FM)	шт		3	0.00	0		3	'fm':6 'r01a':3 'ratex':2 'ам':4 'антен':1 'укв':5	\N
41	антенна "Антей" врезная в пластике	шт		3	230.00	0		3	'ант':2 'антен':1 'врезн':3 'пластик':5	\N
10	дезодорант "Mannol Eclipse"	шт		3	55.00	0		3	'eclips':3 'mannol':2 'дезодорант':1	\N
15	дезодорант "Русский лес"	шт		3	21.00	0		3	'дезодорант':1 'лес':3 'русск':2	\N
61	освежитель воздуха на дефлектор Collection Aromatique "Свежесть горного ручья"	шт		3	0.00	0		3	'aromatiqu':6 'collect':5 'воздух':2 'горн':8 'дефлектор':4 'освежител':1 'руч':9 'свежест':7	\N
62	освежитель воздуха гелевый Dr.Marcus Car Gel	шт		3	0.00	0		3	'car':6 'dr':4 'gel':7 'marcus':5 'воздух':2 'гелев':3 'освежител':1	\N
16	вал и червяк 2105	шт		1	410.00	0		3	'2105':4 'вал':1 'червяк':3	2101-3401035
39	антенна AM-203 "Антей" автомобильная на магните	шт	AM-203	3	50.00	0		3	'203':3,9 'автомобильн':5 'ант':4 'антен':1 'магн':7	\N
60	антенна "Триада" TAXI BLUES	шт		3	0.00	0		3	'blue':4 'taxi':3 'антен':1 'триад':2	\N
\.


--
-- TOC entry 3115 (class 0 OID 16717)
-- Dependencies: 220
-- Data for Name: нумераторы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "нумераторы" ("код", "имя", "значение") FROM stdin;
5	ПлатежноеПоручение	5
2	Накладная1	25
1	Накладная	129
4	ТоварныйЧек	31
\.


--
-- TOC entry 3116 (class 0 OID 16724)
-- Dependencies: 222
-- Data for Name: персонал; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "персонал" ("код", "имя", "инн", "паспорт_серия", "паспорт_номер", "паспорт_выдан", "паспорт_дата", "адрес", "день_рождения", "работает", "медстрах") FROM stdin;
\.


--
-- TOC entry 3117 (class 0 OID 16736)
-- Dependencies: 224
-- Data for Name: прайсы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "прайсы" ("код", "имя", "код_фирмы", "кодвпрайсе", "артикул", "едизм", "дата", "цена", "упаковка", "наличие", "код_номенклатура", "кол_прайс", "кол_номенклатура", "приоритет", fts) FROM stdin;
289	Антенна Триада TAXI BLUES (аналог Bosch)	3	3147		шт	2012-06-26	141.65	\N	+	0	1.000	1.000	1	'blue':4 'bosch':6 'taxi':3 'аналог':5 'антен':1 'триад':2
286	Антирадар Crunch 213B дисплей cветодиод	3	49170		шт.	2012-02-10	1937.87	\N	+	0	1.000	1.000	1	'213b':3 'crunch':2 'cветодиод':5 'антирадар':1 'диспл':4
287	Освежитель воздуха BUGALE ваниль 60мл.	3	92280		шт.	2012-02-10	113.33	\N	+	0	1.000	1.000	1	'60мл':5 'bugal':3 'ванил':4 'воздух':2 'освежител':1
288	Освежитель воздуха Business Class гелевый musk noir (60мл.)	3	96880		шт.	2012-02-10	161.75	\N	+	0	1.000	1.000	1	'60мл':8 'busi':3 'class':4 'musk':6 'noir':7 'воздух':2 'гелев':5 'освежител':1
291	Освежитель воздуха Ocean Paradise гелевый ваниль (40мл.)	3	96910		шт.	2012-06-29	173.81	\N	+	0	1.000	1.000	1	'40мл':7 'ocean':3 'paradis':4 'ванил':6 'воздух':2 'гелев':5 'освежител':1
292	Блок фара 2104, 05, 07 правая ОСВАР (95.3711) (заводская в упаковке)	3	3669	2105-3711010-10	шт	2012-08-09	1203.51	\N	+	0	1.000	1.000	1	'05':4 '07':5 '10':15 '2104':3 '2105':13 '3711':9 '3711010':14 '95':8 'блок':1 'заводск':10 'освар':7 'прав':6 'упаковк':12 'фар':2
290	Освежитель воздуха на дефлектор Collection Aromatique свежесть горного ручья	3	98404		шт.	2012-06-26	35.17	\N	+	0	1.000	1.000	1	'aromatiqu':6 'collect':5 'воздух':2 'горн':8 'дефлектор':4 'освежител':1 'руч':9 'свежест':7
293	Освежитель воздуха гелевый Dr.Marcus Car Gel в ассортименте	3	53638		шт.	2012-08-11	42.20	\N	+	0	1.000	1.000	1	'car':6 'dr':4 'gel':7 'marcus':5 'ассортимент':9 'воздух':2 'гелев':3 'освежител':1
283	Антенна HYUNDAI внутрисалонная активная H-CA1200	3	3136	H-CA1200	шт	2012-02-08	156.72	\N	+	0	1.000	1.000	1	'ca1200':6,8 'h':5,7 'hyundai':2 'активн':4 'антен':1 'внутрисалон':3
284	Антенна MYSTERY внутрисалонная активная MANT-1	3	36687		шт	2012-02-08	147.68	\N	+	0	1.000	1.000	1	'1':6 'mant':5 'mysteri':2 'активн':4 'антен':1 'внутрисалон':3
285	Антенна Ratex-R01A(АМ,УКВ,FM) активная	3	3142		шт	2012-02-08	100.06	\N	+	0	1.000	1.000	1	'fm':6 'r01a':3 'ratex':2 'активн':7 'ам':4 'антен':1 'укв':5
276	Антенна AN110 на желобок	3	3091	AN110	шт	2012-02-07	122.56	\N	+	38	1.000	1.000	1	'an110':2,5 'антен':1 'желобок':4
279	Антенна AN4112 резиновая	3	3103	AN4112	шт	2012-02-07	90.42	\N	+	40	1.000	1.000	1	'an4112':2,4 'антен':1 'резинов':3
278	Антенна Antei автомобильная на магните наклонная AM-203	3	3124		шт	2012-02-07	97.45	\N	+	39	1.000	1.000	1	'203':8 'antei':2 'автомобильн':3 'антен':1 'магн':5 'наклон':6
282	Антенна Antei автомобильная врезная в пластике	3	3114		шт	2012-02-08	73.85	\N	+	41	1.000	1.000	1	'antei':2 'автомобильн':3 'антен':1 'врезн':4 'пластик':6
\.


--
-- TOC entry 3118 (class 0 OID 16754)
-- Dependencies: 226
-- Data for Name: предметы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "предметы" ("код", "имя", "едизм") FROM stdin;
\.


--
-- TOC entry 3107 (class 0 OID 16622)
-- Dependencies: 194
-- Data for Name: проводки; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "проводки" ("код", "дбсчет", "дбкод", "крсчет", "кркод", "кол", "цена", "сумма", "стр", "доккод", "опер", "номеропер") FROM stdin;
\.


--
-- TOC entry 3095 (class 0 OID 16431)
-- Dependencies: 167
-- Data for Name: сальдо; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "сальдо" ("счет", "код", "кол", "сальдо", "дбкол", "дебет", "кркол", "кредит", "конкол", "консальдо", "концена") FROM stdin;
\.


--
-- TOC entry 3101 (class 0 OID 16527)
-- Dependencies: 181
-- Data for Name: справочники; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "справочники" ("код", "имя", "имя_в_списке", "имя_в_форме", "форма", "преформулы", "формулы", "постформулы", "фото", "прототип") FROM stdin;
2	столбцы	Справочник. Наименование столбцов			\N	\N	\N		\N
3	доступ	Доступ			\N	\N	\N		\N
4	типыобъектов	Справочник. Типы объектов.	Тип объекта		\N	\N	\N		\N
5	счета	Бухгалтерские счета			\N	\N	\N		\N
6	vw_доступ_к_справочникам	Справочники		Справочник. Доступ к справочникам	\N	\N	\N		\N
7	vw_справочники_со_столбцами	Справочники, в которых столбцы могут иметь пользовательское название			\N	\N	\N		\N
8	топер	Справочник. Типовые операции			\N	\N	\N		\N
9	нумераторы	Справочник. Нумераторы			\N	\N	\N		\N
11	контрагенты	Справочник. Контрагенты	Контрагент		\N	\N	\N		\N
12	группы	Справочники. Группы	Группа		\N	\N	\N		\N
13	vw_доступ_к_топер	Операции		Справочник. Доступ к типовым операциям	\N	\N	\N		\N
14	vw_контрагенты	Просмотр. Контрагенты	Контрагент		\N	\N	\N		\N
16	банки	Справочник. Банки	Банк		\N	\N	\N		\N
17	vw_грузополучатели	Просмотр. Грузополучатели	Грузополучатель		\N	\N	\N		\N
18	константы	Константы			\N	\N	\N		\N
19	блокпериоды	Периоды			\N	\N	\N		\N
10	номенклатура	Справочник. Номенклатура	Номенклатура		\N	\N	\N	~/photo/nomenklatura	\N
1	справочники	Справочники			\N	\N	\N		\N
15	vw_номенклатура	Просмотр. Номенклатура	Номенклатура		\N	\N	\N		номенклатура
51	набор1	Набор1	Набор1		\N	\N	\N		\N
31	адрес	Справочник. Адреса хранения	Адреса хранения		\N	\N	\N		\N
52	фирмы	Справочник. Фирмы	Фирмы		\N	\N	\N		\N
54	прайсы	Справочник. Прайсы	Прайсы		\N	\N	\N		\N
55	наценки	Справочник. Розничные наценки			\N	\N	\N		\N
\.


--
-- TOC entry 3108 (class 0 OID 16637)
-- Dependencies: 197
-- Data for Name: столбцы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "столбцы" ("код", "код_vw_справочники_со_столбцами", "имя", "заголовок", "номер", "толькочтение") FROM stdin;
446	2000002	p1__код	p1__код	0	t
447	2000002	p1__дбсчет	p1__дбсчет	0	f
448	2000002	p1__дбкод	p1__дбкод	0	f
449	2000002	p1__крсчет	p1__крсчет	0	f
255	54	имя	Наименование в прайсе	3	\N
256	54	фирмы__имя	Поставщик	1	\N
257	54	кодвпрайсе	Код в прайсе	2	\N
258	54	артикул	Артикул в прайсе	4	\N
259	54	едизм	Ед.Изм. в прайсе	5	\N
260	54	дата	Дата	7	\N
261	54	цена	Цена в прайсе	6	\N
262	54	наличие	Наличие	8	\N
263	54	номенклатура__имя	Наименование	9	\N
264	54	номенклатура__едизм	Ед.Изм.	10	\N
265	54	номенклатура__артикул	Артикул	11	\N
266	54	номенклатура__цена_розн	Цена розн.	12	\N
267	54	номенклатура__запас	Запас	13	\N
268	54	кол_прайс	Кол-во. в прайсе	14	\N
269	54	кол_номенклатура	Наше кол-во	15	\N
270	5	имя	Наименование	1	\N
271	5	счет	Счет	2	\N
272	5	имясправочника	Справочник	3	\N
273	5	баланс	Баланс	4	\N
274	5	количество	Количество	5	\N
450	2000002	p1__кркод	p1__кркод	0	f
287	2000002	p1__кол	Кол-во	5	f
288	2000002	p1__цена	Цена	6	f
289	2000002	p1__сумма	Сумма	7	f
451	2000002	p1__стр	p1__стр	0	f
281	2000001	p1__кол	Кол-во	4	f
282	2000001	p1__цена	Цена	5	f
867	1000006	переменные	переменные	0	t
353	2000003	p1__код	p1__код	0	t
354	2000003	p1__дбсчет	p1__дбсчет	0	f
402	2000004	p1__код	p1__код	0	\N
342	1	код	Код	1	\N
355	2000003	p1__дбкод	p1__дбкод	0	f
356	2000003	p1__крсчет	p1__крсчет	0	f
357	2000003	p1__кркод	p1__кркод	0	f
297	2000003	p1__кол	Кол-во	6	f
283	2000001	p1__сумма	Сумма	6	f
517	2000001	код	код	0	t
277	2000001	номенклатура__имя	Наименование	1	f
518	2000001	кодвпрайсе	кодвпрайсе	0	f
358	2000003	p1__цена	p1__цена	0	f
359	2000003	p1__сумма	p1__сумма	0	f
403	2000004	p1__дбсчет	p1__дбсчет	0	\N
404	2000004	p1__дбкод	p1__дбкод	0	\N
405	2000004	p1__крсчет	p1__крсчет	0	\N
406	2000004	p1__кркод	p1__кркод	0	\N
407	2000004	p1__кол	p1__кол	0	\N
408	2000004	p1__цена	p1__цена	0	\N
409	2000004	p1__сумма	Сумма	1	\N
410	2000004	p1__стр	p1__стр	0	\N
411	2000004	p1__доккод	p1__доккод	0	\N
412	2000004	p1__опер	p1__опер	0	\N
413	2000004	p1__номеропер	p1__номеропер	0	\N
414	1000004	код	код	0	\N
415	1000004	дата	Дата	1	\N
416	1000004	датавремя	датавремя	0	\N
417	1000004	номер	Номер	2	\N
360	2000003	p1__стр	p1__стр	0	f
361	2000003	p1__доккод	p1__доккод	0	f
418	1000004	комментарий	Комментарий	3	\N
419	1000004	сумма	Сумма	4	\N
420	1000004	описание	описание	0	\N
421	1000004	опер	опер	0	\N
422	1000004	авто	авто	0	\N
423	1000004	переменные	переменные	0	\N
341	1	имя	Наименование	2	\N
343	1	имя_в_списке	Наименование в списке	3	\N
344	1	имя_в_форме	Наименование в форме	4	\N
345	1	прототип	Прототип	5	\N
346	6	имя	Наименование	1	\N
347	3	меню	Меню	3	\N
349	3	типыобъектов__имя	Тип объекта	1	\N
348	3	имя	Наименование	2	\N
350	13	имя	Наименование	1	\N
519	2000001	код_номенклатура	код_номенклатура	0	f
483	2000003	атрибуты__код	атрибуты__код	0	t
352	31	имя	Наименование	1	\N
364	2000003	p2__код	p2__код	0	t
365	2000003	p2__дбсчет	p2__дбсчет	0	f
366	2000003	p2__дбкод	p2__дбкод	0	f
367	2000003	p2__крсчет	p2__крсчет	0	f
368	2000003	p2__кркод	p2__кркод	0	f
369	2000003	p2__кол	p2__кол	0	f
298	2000003	p2__цена	Цена	7	t
424	2000001	p1__код	p1__код	0	t
425	2000001	p1__дбсчет	p1__дбсчет	0	f
426	2000001	p1__дбкод	p1__дбкод	0	f
427	2000001	p1__крсчет	p1__крсчет	0	f
428	2000001	p1__кркод	p1__кркод	0	f
429	2000001	p1__стр	p1__стр	0	f
430	2000001	p1__доккод	p1__доккод	0	f
431	2000001	p1__опер	p1__опер	0	f
432	2000001	p1__номеропер	p1__номеропер	0	f
433	2000001	номенклатура__код	номенклатура__код	0	t
278	2000001	номенклатура__едизм	Ед.Изм.	3	f
280	2000001	номенклатура__артикул	Артикул	2	f
434	2000001	номенклатура__код_группы	номенклатура__код_группы	0	t
470	2000002	номенклатура__запас	номенклатура__запас	0	t
471	2000002	номенклатура__имя_на_ценнике	номенклатура__имя_на_ценнике	0	t
472	2000002	номенклатура__тип_ценника	номенклатура__тип_ценника	0	t
299	2000003	p2__сумма	Сумма	8	t
370	2000003	p2__стр	p2__стр	0	f
371	2000003	p2__доккод	p2__доккод	0	f
372	2000003	p2__опер	p2__опер	0	f
373	2000003	p2__номеропер	p2__номеропер	0	f
374	2000003	p3__код	p3__код	0	t
375	2000003	p3__дбсчет	p3__дбсчет	0	f
376	2000003	p3__дбкод	p3__дбкод	0	f
377	2000003	p3__крсчет	p3__крсчет	0	f
378	2000003	p3__кркод	p3__кркод	0	f
379	2000003	p3__кол	p3__кол	0	f
380	2000003	p3__цена	p3__цена	0	f
300	2000003	p3__сумма	p3__сумма	0	f
381	2000003	p3__стр	p3__стр	0	f
382	2000003	p3__доккод	p3__доккод	0	f
383	2000003	p3__опер	p3__опер	0	f
384	2000003	p3__номеропер	p3__номеропер	0	f
482	2000003	атрибуты__поле1	Поле1	1	f
385	2000003	vw_номенклатура__код	vw_номенклатура__код	0	t
301	2000003	vw_номенклатура__имя	Наименование	2	t
302	2000003	vw_номенклатура__едизм	Ед.Изм.	3	t
386	2000003	vw_номенклатура__артикул	vw_номенклатура__артикул	0	t
393	2000003	адрес__код	адрес__код	0	t
473	2000002	номенклатура__fts	номенклатура__fts	0	t
351	2000002	крсальдо1__конкол	Остаток	3	f
474	2000002	крсальдо1__концена	крсальдо1__концена	0	t
475	2000002	крсальдо1__консальдо	крсальдо1__консальдо	0	t
476	1000002	код	код	0	t
477	1000002	дата	дата	0	t
293	1000002	датавремя	Дата, время	1	t
294	1000002	номер	Номер	2	t
295	1000002	комментарий	Комментарий	3	f
296	1000002	сумма	Сумма	4	t
435	2000001	номенклатура__цена_розн	номенклатура__цена_розн	0	t
436	2000001	номенклатура__запас	номенклатура__запас	0	t
437	2000001	номенклатура__имя_на_ценнике	номенклатура__имя_на_ценнике	0	t
438	2000001	номенклатура__тип_ценника	номенклатура__тип_ценника	0	t
439	2000001	номенклатура__fts	номенклатура__fts	0	t
390	2000003	vw_номенклатура__имя_на_ценнике	vw_номенклатура__имя_на_ценнике	0	t
391	2000003	vw_номенклатура__тип_ценника	vw_номенклатура__тип_ценника	0	t
392	2000003	vw_номенклатура__fts	vw_номенклатура__fts	0	t
303	2000003	адрес__имя	Адрес	4	t
304	2000003	крсальдо1__конкол	Остаток	5	t
394	2000003	крсальдо1__концена	крсальдо1__концена	0	t
395	2000003	крсальдо1__консальдо	крсальдо1__консальдо	0	t
396	1000003	код	код	0	t
397	1000003	дата	дата	0	t
305	1000003	датавремя	Дата, время	1	t
306	1000003	номер	Номер	2	t
307	1000003	комментарий	Комментарий	3	f
308	1000003	сумма	Сумма	4	t
398	1000003	описание	описание	0	t
399	1000003	опер	опер	0	t
400	1000003	авто	авто	0	t
521	2000001	номенклатура__артикул_оем	номенклатура__артикул_оем	0	t
440	1000001	код	код	0	t
279	1000001	дата	Дата	1	t
441	1000001	датавремя	датавремя	0	t
284	1000001	номер	Номер	2	t
362	2000003	p1__опер	p1__опер	0	f
363	2000003	p1__номеропер	p1__номеропер	0	f
387	2000003	vw_номенклатура__код_группы	vw_номенклатура__код_группы	0	t
388	2000003	vw_номенклатура__цена_розн	vw_номенклатура__цена_розн	0	t
389	2000003	vw_номенклатура__запас	vw_номенклатура__запас	0	t
452	2000002	p1__доккод	p1__доккод	0	f
453	2000002	p1__опер	p1__опер	0	f
454	2000002	p1__номеропер	p1__номеропер	0	f
455	2000002	vw_номенклатура__код	vw_номенклатура__код	0	t
290	2000002	vw_номенклатура__имя	Наименование	1	f
291	2000002	vw_номенклатура__едизм	Ед.Изм.	2	f
456	2000002	vw_номенклатура__артикул	vw_номенклатура__артикул	0	t
457	2000002	vw_номенклатура__код_группы	vw_номенклатура__код_группы	0	t
458	2000002	vw_номенклатура__цена_розн	vw_номенклатура__цена_розн	0	t
459	2000002	vw_номенклатура__запас	vw_номенклатура__запас	0	t
460	2000002	vw_номенклатура__имя_на_ценнике	vw_номенклатура__имя_на_ценнике	0	t
461	2000002	vw_номенклатура__тип_ценника	vw_номенклатура__тип_ценника	0	t
462	2000002	vw_номенклатура__fts	vw_номенклатура__fts	0	t
463	2000002	адрес__код	адрес__код	0	t
285	1000001	комментарий	Комментарий	3	f
286	1000001	сумма	Сумма	4	t
442	1000001	описание	описание	0	t
443	1000001	опер	опер	0	t
444	1000001	авто	авто	0	t
445	1000001	переменные	переменные	0	t
838	2000006	код	код	0	t
839	2000006	доккод	доккод	0	t
840	2000006	стр	стр	0	t
841	2000006	код_номенклатура	код_номенклатура	0	f
842	2000006	номенклатура__имя	Наименование	1	t
843	2000006	номенклатура__едизм	Ед.Изм.	4	t
844	2000006	номенклатура__артикул	Артикул	2	t
845	2000006	номенклатура__код_группы	номенклатура__код_группы	0	t
401	1000003	переменные	переменные	0	t
292	2000002	адрес__имя	Адрес	4	f
464	2000002	номенклатура__код	номенклатура__код	0	t
465	2000002	номенклатура__имя	номенклатура__имя	0	t
466	2000002	номенклатура__едизм	номенклатура__едизм	0	t
467	2000002	номенклатура__артикул	номенклатура__артикул	0	t
468	2000002	номенклатура__код_группы	номенклатура__код_группы	0	t
469	2000002	номенклатура__цена_розн	номенклатура__цена_розн	0	t
523	2000002	номенклатура__артикул_оем	номенклатура__артикул_оем	0	t
478	1000002	описание	описание	0	t
479	1000002	опер	опер	0	t
480	1000002	авто	авто	0	t
481	1000002	переменные	переменные	0	t
522	2000001	код_прайсы	код_прайсы	0	f
846	2000006	номенклатура__цена_розн	номенклатура__цена_розн	0	t
847	2000006	номенклатура__запас	номенклатура__запас	0	t
537	55	группы__имя	Группа	1	f
538	55	имя	Наименование	2	f
539	55	минпроцент	Мин.порог.%	3	f
563	10	имя	Наименование	3	f
564	10	едизм	Ед.Изм.	6	f
565	10	артикул	Артикул	4	f
566	10	код_группы	Код группы	1	f
567	10	группы__имя	Группа	2	f
568	10	цена_розн	Цена розн.	7	f
569	10	запас	Запас	8	f
570	10	артикул_оем	Артикул ОЕМ	5	f
848	2000006	номенклатура__имя_на_ценнике	номенклатура__имя_на_ценнике	0	t
849	2000006	номенклатура__тип_ценника	номенклатура__тип_ценника	0	t
850	2000006	номенклатура__fts	номенклатура__fts	0	t
540	55	макспроцент	Макс.порог.%	4	f
541	55	минпорогсумма	Мин.закуп.цена	5	f
542	55	макспорогсумма	Макс.закуп.цена	6	f
543	55	наценка	Сделать % наценки	7	f
544	55	округление	Округление	8	f
851	2000006	номенклатура__артикул_оем	Артикул ОЕМ	3	t
852	2000006	кол	Кол-во	5	t
853	2000006	старцена	Стар.цена	7	t
854	2000006	новцена	Нов.цена	9	f
855	2000006	старнаценка	Стар.наценка	8	t
856	2000006	новнаценка	Нов.наценка	10	t
857	2000006	закцена	Зак.цена	6	t
858	1000006	код	код	0	t
859	1000006	дата	дата	0	t
860	1000006	датавремя	Дата, время	1	t
861	1000006	номер	Номер	2	t
862	1000006	комментарий	Комментарий	3	f
863	1000006	сумма	Сумма	4	t
864	1000006	описание	описание	0	t
865	1000006	опер	опер	0	t
866	1000006	авто	авто	0	t
\.


--
-- TOC entry 3096 (class 0 OID 16443)
-- Dependencies: 168
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
43	Товары. Товары в розничной торговле	41.2 	набор1	t	t
\.


--
-- TOC entry 3119 (class 0 OID 16769)
-- Dependencies: 232
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
-- TOC entry 3102 (class 0 OID 16543)
-- Dependencies: 183
-- Data for Name: топер; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "топер" ("код", "опер", "номер", "дбсчет", "крсчет", "имя", "итоги", "осндокумент", "нумератор", "однаоперация", "кол", "дбпост", "крпост", "дбдобав", "крдобав", "дбвыбор", "крвыбор", "дбсалвидим", "крсалвидим", "дбвидим", "крвидим", "форма", "независим", "считать", "переменные", "атрибуты") FROM stdin;
82	5	1	60	51	Банковский счет. Перечисление организации	+		ПлатежноеПоручение	t	f	t	f	f	f	f	f	f	f	f	f		f	t	\N	\N
863	2	1	41.2	41.1	Товар на складе. Передача в розничную продажу	+		Накладная1	f	f	f	f	f	f	f	f	f	t	f	t		f	t	\N	f
864	1	1	41.1	60	Товар на складе. Приход от поставщика	+		Накладная	f	f	f	t	f	f	f	f	f	f	t	f		f	t	\N	t
805	3	2	50.2	90.1	Товар в рознице. Реализация за наличный расчет	+			\N	f	f	f	f	f	f	f	f	f	f	f		f	t	\N	f
806	3	3	90.1	50.2	Товар в рознице. Реализация за наличный расчет	-			\N	f	f	f	f	f	f	f	f	f	f	f		t	t	\N	f
804	3	1	90.2	41.2	Товар в рознице. Реализация за наличный расчет			ТоварныйЧек	f	f	f	f	f	f	f	f	f	t	f	t		f	t	\N	f
584	4	1	51	50.2	Выручка. Сдача денег на расчетный счет	+			t	f	f	f	f	f	f	f	f	f	f	f		f	t	\N	\N
878	6	0			Товар в рознице. Переоценка			Накладная1	f	f	f	f	f	f	f	f	f	f	f	f		f	t	\N	t
\.


--
-- TOC entry 3120 (class 0 OID 16777)
-- Dependencies: 235
-- Data for Name: файлы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "файлы" ("код", "имя", "тип", "значение") FROM stdin;
7	./scripts/формулы5.qs	0	\\x66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a207b0a2f2f20d097d0b0d0bfd0b8d188d0b5d0bc20d0bdd0b0d0b8d0bcd0b5d0bdd0bed0b2d0b0d0bdd0b8d0b520d184d0b8d180d0bcd18b2dd0bfd0bed181d182d0b0d0b2d189d0b8d0bad0b020d0b220d0bad0bed0bcd0bcd0b5d0bdd182d0b0d180d0b8d0b820d0ba20d0b4d0bed0bad183d0bcd0b5d0bdd182d1830a09d0bdd0b0d0b8d0bcd0b5d0bdd0bed0b2d0b0d0bdd0b8d0b5203d2067657444696374696f6e617279282276775fd0bad0bed0bdd182d180d0b0d0b3d0b5d0bdd182d18b22292e67657456616c75652822d0b8d0bcd18f22293b0a09646f63756d656e74732e73657456616c75652822d09ad0bed0bcd0bcd0b5d0bdd182d0b0d180d0b8d0b9222c20d0bdd0b0d0b8d0bcd0b5d0bdd0bed0b2d0b0d0bdd0b8d0b5293b0a7d0a0a
10	счета.qs	0	\\x66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a
8	номенклатура.qs	0	\\x66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a
6	./scripts/формулы4.qs	0	\\x66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a
9	прайсы.qs	0	\\x66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a
1	./scripts/формулы1.qs	0	\\x76617220657869744b6579507265737365643b092f2f20d0a4d0bbd0b0d0b320d0bdd0b0d0b6d0b0d182d0b8d18f20d0bad0bdd0bed0bfd0bad0b82c20d0bfd180d0b5d180d18bd0b2d0b0d18ed189d0b5d0b920d0b7d0b0d0b3d180d183d0b7d0bad18320d0b4d0bed0bad183d0bcd0b5d0bdd182d0b0200a0a66756e6374696f6e204576656e74496e6974466f726d28666f726d290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a09666f726d2e676574427574746f6e4c6f616428292e73686f7728293b09092f2f20d092d0bad0bbd18ed187d0b8d0bc20d0bad0bdd0bed0bfd0bad1832022d097d0b0d0b3d180d183d0b7d0b8d182d18c20d0b4d0bed0bad183d0bcd0b5d0bdd1822220d0bdd0b020d184d0bed180d0bcd0b50a7d0a0a0a66756e6374696f6e204576656e74496d706f727428666f726d290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd097d0b0d0b3d180d183d0b7d0b8d182d18c20d0b4d0bed0bad183d0bcd0b5d0bdd1823e0a20207661722066696c654e616d65203d205146696c654469616c6f672e6765744f70656e46696c654e616d6528666f726d2c2022d09ed182d0bad180d0bed0b9d182d0b520d0b4d0bed0bad183d0bcd0b5d0bdd18220d18120d0bfd180d0b8d185d0bed0b4d0bed0bc20d182d0bed0b2d0b0d180d0b0222c20514469722e63757272656e745061746828292c2022d094d0bed0bad183d0bcd0b5d0bdd18220584d4c282a2e584d4c2922293b0a20206966202866696c654e616d6520213d202222290a20207b202020200a202020207661722066696c65203d206e6577205146696c652866696c654e616d65293b0a202020206966202866696c652e6f70656e2851494f4465766963652e4f70656e4d6f64652851494f4465766963652e526561644f6e6c792c2051494f4465766963652e54657874292929200a202020207b0a20202020202076617220646f63203d206e65772051446f6d446f63756d656e7428293b0a20202020202069662028646f632e736574436f6e74656e742866696c6529290a2020202020207b0a202020202020202069662028646f632e656c656d656e747342795461674e616d652822d0a5d0bed0b7d09ed0bfd0b5d180d0b0d186d0b8d18f22292e61742830292e746f456c656d656e7428292e746578742829203d3d2022d09ed182d0bfd183d181d0ba20d182d0bed0b2d0b0d180d0b02229092f2f20d095d181d0bbd0b820d18dd182d0be20d0b4d0bed0bad183d0bcd0b5d0bdd18220d0bdd0b020d0bed182d0b3d180d183d0b7d0bad18320d182d0bed0b2d0b0d180d0b00a20202020202020207b0a2020202020202020202076617220646f634e756d626572203d20646f632e656c656d656e747342795461674e616d652822d09dd0bed0bcd0b5d18022292e61742830292e746f456c656d656e7428292e7465787428293b0a2020202020202020202076617220646f6344617465203d20646f632e656c656d656e747342795461674e616d652822d094d0b0d182d0b022292e61742830292e746f456c656d656e7428292e7465787428293b0a20202020202020202020766172206167656e744e616d65203d2022223b0a20202020202020202020766172206167656e7446756c6c4e616d65203d2022223b0a20202020202020202020766172206167656e7441646472657373203d2022223b0a202020202020202020202f2f20d09dd0b0d0b9d0b4d0b5d0bc20d0b220d0b4d0bed0bad183d0bcd0b5d0bdd182d0b520d180d0b5d0bad0b2d0b8d0b7d0b8d182d18b20d0bad0bed0bdd182d180d0b0d0b3d0b5d0bdd182d0b02dd0bfd180d0bed0b4d0b0d0b2d186d0b00a20202020202020202020766172206167656e7473203d20646f632e656c656d656e747342795461674e616d652822d09ad0bed0bdd182d180d0b0d0b3d0b5d0bdd18222293b0a20202020202020202020666f7220287661722069203d20303b2069203c206167656e74732e636f756e7428293b20692b2b290a202020202020202020207b0a202020202020202020202020696620286167656e74732e61742869292e66697273744368696c64456c656d656e742822d0a0d0bed0bbd18c22292e746578742829203d3d2022d09fd180d0bed0b4d0b0d0b2d0b5d18622290a2020202020202020202020207b0a20202020202020202020202020206167656e744e616d65203d206167656e74732e61742869292e66697273744368696c64456c656d656e742822d09dd0b0d0b8d0bcd0b5d0bdd0bed0b2d0b0d0bdd0b8d0b522292e7465787428293b0a20202020202020202020202020206167656e7446756c6c4e616d65203d206167656e74732e61742869292e66697273744368696c64456c656d656e742822d09ed184d0b8d186d0b8d0b0d0bbd18cd0bdd0bed0b5d09dd0b0d0b8d0bcd0b5d0bdd0bed0b2d0b0d0bdd0b8d0b522292e7465787428293b0a20202020202020202020202020206167656e7441646472657373203d206167656e74732e61742869292e6e616d65644974656d2822d0aed180d0b8d0b4d0b8d187d0b5d181d0bad0b8d0b9d090d0b4d180d0b5d18122292e6e616d65644974656d2822d09fd180d0b5d0b4d181d182d0b0d0b2d0bbd0b5d0bdd0b8d0b522292e746f456c656d656e7428292e7465787428293b0a2020202020202020202020202020627265616b3b0a2020202020202020202020207d0a202020202020202020207d09090909090a20202020202020202020696620286167656e744e616d6520213d20222229092f2f20d095d181d0bbd0b820d183d0bad0b0d0b7d0b0d0bd20d0bad0bed0bdd182d180d0b0d0b3d0b5d0bdd1822dd0bfd180d0bed0b4d0b0d0b2d0b5d1860a202020202020202020207b0a202020202020202020202020696620286167656e7446756c6c4e616d65203d3d202222290a20202020202020202020202020206167656e7446756c6c4e616d65203d206167656e744e616d653b0a202020202020202020202020646f63756d656e742e7365744e756d62657228646f634e756d626572293b0a202020202020202020202020646f63756d656e742e7365744461746528646f63446174652c2051742e49534f44617465293b0a202020202020202020202020766172206167656e7444696374203d2067657444696374696f6e617279282276775fd0bad0bed0bdd182d180d0b0d0b3d0b5d0bdd182d18b22293b092f2f20d09dd0b0d0b9d0b4d0b5d0bc20d182d0b0d0bad0bed0b3d0be20d0bad0bed0bdd182d180d0b0d0b3d0b5d0bdd182d0b020d0b220d0bdd0b0d188d0b5d0b920d091d0940a2020202020202020202020206167656e74446963742e71756572792822d0b8d0bcd18f203d202722202b206167656e7446756c6c4e616d65202b20222722293b0a202020202020202020202020766172206167656e744964203d206167656e74446963742e67657449642830293b0a202020202020202020202020696620286167656e744964203d3d20302909092f2f20d095d181d0bbd0b820d182d0b0d0bad0bed0b3d0be20d0bad0bed0bdd182d180d0b0d0b3d0b5d0bdd182d0b020d0bdd0b520d181d183d189d0b5d181d182d0b2d183d0b5d18220d0b220d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b50a2020202020202020202020207b0a2020202020202020202020202020766172206167656e744d7367203d206e657720514d657373616765426f7828514d657373616765426f782e5175657374696f6e2c2022d092d0bdd0b8d0bcd0b0d0bdd0b8d0b521222c2022d09dd0b520d0bdd0b0d0b9d0b4d0b5d0bd20d182d0b0d0bad0bed0b920d0bad0bed0bdd182d180d0b0d0b3d0b5d0bdd1822e20d0a1d0bed0b7d0b4d0b0d182d18c3f222c20514d657373616765426f782e5965732c20666f726d293b0a2020202020202020202020202020696620286167656e744d73672e657865632829203d3d20514d657373616765426f782e596573290a20202020202020202020202020207b0a2020202020202020202020202020202064622e657865632851537472696e672822494e5345525420494e544f20d0bad0bed0bdd182d180d0b0d0b3d0b5d0bdd182d18b2028d0b8d0bcd18f2c20d0b0d0b4d180d0b5d181292056414c5545532028272531272c2027253227293b22292e617267286167656e7446756c6c4e616d65292e617267286167656e744164647265737329293b0a202020202020202020202020202020206167656e74446963742e71756572792822d0b8d0bcd18f203d202722202b206167656e7446756c6c4e616d65202b20222722293b0a202020202020202020202020202020206167656e744964203d206167656e74446963742e67657449642830293b0a20202020202020202020202020207d0a2020202020202020202020207d0a2020202020202020202020202f2f20d0a1d0b4d0b5d0bbd0b0d0b5d0bc20d0bdd0b0d0b8d0bcd0b5d0bdd0bed0b2d0b0d0bdd0b8d0b520d0bad0bed0bdd182d180d0b0d0b3d0b5d0bdd182d0b02dd0bfd180d0bed0b4d0b0d0b2d186d0b020d0b2d0b8d0b4d0b8d0bcd18bd0bc20d0bdd0b020d184d0bed180d0bcd0b520d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2020202020202020202020206167656e74446963742e7365744964286167656e744964293b0a202020202020202020202020646f63756d656e742e73686f77506172616d6574657254657874282276775fd0bad0bed0bdd182d180d0b0d0b3d0b5d0bdd182d18b22293b0a09202020204576656e74506172616d65746572734368616e67656428293b0a0920202020646f63756d656e74732e73657456616c75652822d09ad0bed0bcd0bcd0b5d0bdd182d0b0d180d0b8d0b9222c2067657444696374696f6e617279282276775fd0bad0bed0bdd182d180d0b0d0b3d0b5d0bdd182d18b22292e67657456616c75652822d0b8d0bcd18f2229293b0a202020202020202020202020766172206669726d4964203d206167656e74446963742e67657456616c75652822d0bad0bed0b45fd184d0b8d180d0bcd18b22293b092f2f20d09fd0bed0bbd183d187d0b8d0bc20d0bad0bed0b420d184d0b8d180d0bcd18b20d0bed182d0b3d180d183d0b7d0bad0b820d0bad0bed0bdd182d180d0b0d0b3d0b5d0bdd182d0b00a202020202020202020202020696620286669726d4964203d3d2030290a2020202020202020202020207b09090a2020202020202020202020202020766172206669726d4d7367203d206e657720514d657373616765426f7828514d657373616765426f782e5175657374696f6e2c2022d092d0bdd0b8d0bcd0b0d0bdd0b8d0b521222c2022d0a320d0bad0bed0bdd182d180d0b0d0b3d0b5d0bdd182d0b020d0bdd0b520d183d0bad0b0d0b7d0b0d0bdd0b020d184d0b8d180d0bcd0b020d0bed182d0b3d180d183d0b7d0bad0b82e20d0a1d0bed0b7d0b4d0b0d182d18c3f222c20514d657373616765426f782e5965732c20666f726d293b0a2020202020202020202020202020696620286669726d4d73672e657865632829203d3d20514d657373616765426f782e596573290a202020202020202020202020202020207b0a2020202020202020202020202020202020202f2f20d09fd0be20d183d0bcd0bed0bbd187d0b0d0bdd0b8d18e20d181d0bed0b7d0b4d0b0d0b5d182d181d18f20d184d0b8d180d0bcd0b020d0bed182d0b3d180d183d0b7d0bad0b820d18120d0bdd0b0d0b8d0bcd0b5d0bdd0bed0b2d0b0d0bdd0b8d0b5d0bc20d0bad0b0d0ba20d18320d0bad0bed0bdd182d180d0b0d0b3d0b5d0bdd182d0b00a202020202020202020202020202020202020766172206669726d44696374203d2067657444696374696f6e6172792822d184d0b8d180d0bcd18b22293b0a2020202020202020202020202020202020202f2f20d0a1d0bdd0b0d187d0b0d0bbd0b020d0bfd0bed0b8d189d0b5d0bc20d183d0b6d0b520d181d183d189d0b5d181d182d0b2d183d18ed189d183d18e20d184d0b8d180d0bcd18320d18120d182d0b0d0bad0b8d0bc20d0bdd0b0d0b8d0bcd0b5d0bdd0bed0b2d0b0d0bdd0b8d0b5d0bc0a2020202020202020202020202020202020206669726d446963742e71756572792822d0b8d0bcd18f203d202722202b206167656e744e616d65202b20222722293b0a2020202020202020202020202020202020206669726d4964203d206669726d446963742e67657449642830293b0a202020202020202020202020202020202020696620286669726d4964203d3d20302909090a2020202020202020202020202020202020207b0a20202020202020202020202020202020202020202f2f20d0a4d0b8d180d0bcd18b20d18120d182d0b0d0bad0b8d0bc20d0bdd0b0d0b8d0bcd0b5d0bdd0bed0b2d0b0d0bdd0b8d0b5d0bc20d0bdd0b5d1822c20d0bfd0bed18dd182d0bed0bcd18320d181d0bed0b7d0b4d0b0d0b5d0bc20d0bdd0bed0b2d183d18e20d0b7d0b0d0bfd0b8d181d18c0a202020202020202020202020202020202020202064622e657865632822494e5345525420494e544f20d184d0b8d180d0bcd18b2028d0b8d0bcd18f292056414c55455320282722202b206167656e744e616d65202b2022272922293b0a20202020202020202020202020202020202020206669726d446963742e71756572792822d0b8d0bcd18f203d202722202b206167656e744e616d65202b20222722293b0a20202020202020202020202020202020202020206669726d744964203d206669726d74446963742e67657449642830293b0a2020202020202020202020202020202020207d0a2020202020202020202020202020202020202f2f20d0a1d0bed185d180d0b0d0bdd18fd0b5d0bc20d181d181d18bd0bbd0bad18320d0bdd0b020d184d0b8d180d0bcd18320d0bed182d0b3d180d183d0b7d0bad0b820d0b220d0b7d0b0d0bfd0b8d181d0b820d0bad0bed0bdd182d180d0b0d0b3d0b5d0bdd182d0b00a20202020202020202020202020202020202064622e657865632851537472696e67282255504441544520d0bad0bed0bdd182d180d0b0d0b3d0b5d0bdd182d18b2053455420d0bad0bed0b45fd184d0b8d180d0bcd18b203d20253120574845524520d0bad0bed0b4203d2025323b22292e617267286669726d4964292e617267286167656e74496429293b0a202020202020202020202020202020207d0a2020202020202020202020207d0a2020202020202020202020202f2f20d09fd0b5d180d0b5d0b1d0b5d180d0b5d0bc20d0b2d181d0b520d0bfd0bed0b7d0b8d186d0b8d0b820d0b220d0bdd0b0d0bad0bbd0b0d0b4d0bdd0bed0b90a20202020202020202020202076617220746f766172203d20646f632e656c656d656e747342795461674e616d652822d0a2d0bed0b2d0b0d18022293b0a202020202020202020202020657869744b657950726573736564203d2066616c73653b092f2f20d09fd0bed0bad0b020d187d182d0be20d0bdd0b520d0b1d18bd0bbd0b020d0bdd0b0d0b6d0b0d182d0b020d0bad0bdd0bed0bfd0bad0b020d0bfd180d0b5d180d18bd0b2d0b0d0bdd0b8d18f20d0bfd180d0bed186d0b5d181d181d0b020d0b7d0b0d0b3d180d183d0b7d0bad0b80a2020202020202020202020202f2f20d0a22ed0ba2e20d0b4d0b0d0bbd0b5d0b520d0b8d0b4d0b5d18220d186d0b8d0bad0bbd0b8d187d0b5d181d0bad0b0d18f20d0bed0b1d180d0b0d0b1d0bed182d0bad0b020d181d182d180d0bed0ba2c20d0b7d0b0d0b3d0bed182d0bed0b2d0b8d0bc20d0bdd0b5d0bad0bed182d0bed180d18bd0b520d0bad0bed0bcd0b0d0bdd0b4d18b20d0b4d0bbd18f20d181d0b5d180d0b2d0b5d180d0b02c20d187d182d0bed0b1d18b20d0b8d18520d0bed0b1d180d0b0d0b1d0bed182d0bad0b020d0bfd180d0bed0b8d181d185d0bed0b4d0b8d0bbd0b020d0bdd0b020d181d0b5d180d0b2d0b5d180d0b520d0b1d18bd181d182d180d0b5d0b50a202020202020202020202064622e657865632822505245504152452073656c6563745f70726963652028696e742c2074657874292041532053454c45435420d0bad0bed0b42c20d0b8d0bcd18f2c20d186d0b5d0bdd0b02c20d0bad0bed0b45fd0bdd0bed0bcd0b5d0bdd0bad0bbd0b0d182d183d180d0b02c20d0bad0bed0bb5fd0bdd0bed0bcd0b5d0bdd0bad0bbd0b0d182d183d180d0b02c20d0bad0bed0bb5fd0bfd180d0b0d0b9d1812046524f4d20d0bfd180d0b0d0b9d181d18b20574845524520d0bad0bed0b45fd184d0b8d180d0bcd18b3d243120414e4420d0bad0bed0b4d0b2d0bfd180d0b0d0b9d181d0b53d24323b22293b0a202020202020202020202064622e6578656328225052455041524520696e736572745f70726963652028746578742c20746578742c20746578742c20746578742c206e756d657269632c20696e742c20696e742920415320494e5345525420494e544f20d0bfd180d0b0d0b9d181d18b2028d0bad0bed0b4d0b2d0bfd180d0b0d0b9d181d0b52c20d0b8d0bcd18f2c20d0b0d180d182d0b8d0bad183d0bb2c20d0b5d0b4d0b8d0b7d0bc2c20d186d0b5d0bdd0b02c20d0bdd0b0d0bbd0b8d187d0b8d0b52c20d0bad0bed0b45fd184d0b8d180d0bcd18b2c20d0bad0bed0b45fd0bdd0bed0bcd0b5d0bdd0bad0bbd0b0d182d183d180d0b0292056414c554553202824312c2024322c2024332c2024342c2024352c20272b272c2024362c202437293b22293b0a202020202020202020202064622e65786563282250524550415245207570646174655f70726963652028696e742c20746578742c20746578742c20746578742c206e756d657269632c20696e742c2074657874292041532055504441544520d0bfd180d0b0d0b9d181d18b2053455420d0bad0bed0b45fd0bdd0bed0bcd0b5d0bdd0bad0bbd0b0d182d183d180d0b03d24312cd0b8d0bcd18f3d24322cd0b0d180d182d0b8d0bad183d0bb3d24332cd0b5d0b4d0b8d0b7d0bc3d24342cd186d0b5d0bdd0b03d24352cd0bdd0b0d0bbd0b8d187d0b8d0b53d272b2720574845524520d0bad0bed0b45fd184d0b8d180d0bcd18b3d243620414e4420d0bad0bed0b4d0b2d0bfd180d0b0d0b9d181d0b53d24373b22293b0a202020202020202020202020666f7220287661722069203d20303b2069203c20746f7661722e636f756e7428293b20692b2b290a09202020207b0a0920202020202076617220746f7661724964203d20746f7661722e61742869292e66697273744368696c64456c656d656e742822d098d0b422292e7465787428293b0a0920202020202076617220746f7661724e616d65203d20746f7661722e61742869292e66697273744368696c64456c656d656e742822d09dd0b0d0b8d0bcd0b5d0bdd0bed0b2d0b0d0bdd0b8d0b522292e7465787428293b0a0920202020202076617220746f7661724172746963756c203d20746f7661722e61742869292e66697273744368696c64456c656d656e742822d090d180d182d0b8d0bad183d0bb22292e7465787428293b0a0920202020202076617220746f766172556e6974203d20746f7661722e61742869292e66697273744368696c64456c656d656e742822d095d0b4d0b8d0bdd0b8d186d0b022292e7465787428293b0a0920202020202076617220746f7661725175616e203d20746f7661722e61742869292e66697273744368696c64456c656d656e742822d09ad0bed0bbd0b8d187d0b5d181d182d0b2d0be22292e7465787428293b0a0920202020202076617220746f7661725072696365203d20746f7661722e61742869292e66697273744368696c64456c656d656e742822d0a6d0b5d0bdd0b0d097d0b0d095d0b4d0b8d0bdd0b8d186d18322292e7465787428293b0a0920202020202076617220746f76617253756d203d20746f7661722e61742869292e66697273744368696c64456c656d656e742822d0a1d183d0bcd0bcd0b022292e7465787428293b0a092020202020205772697465546f766172286669726d49642c20746f76617249642c20746f7661724e616d652c20746f7661724172746963756c2c20746f766172556e69742c20746f7661725175616e2c20746f76617250726963652c20746f76617253756d293b0a0920202020202069662028657869744b657950726573736564290a0920202020202020627265616b3b092f2f20d091d18bd0bbd0b020d0bdd0b0d0b6d0b0d182d0b020d0bad0bdd0bed0bfd0bad0b020d0bed181d182d0b0d0bdd0bed0b2d0b020d0b7d0b0d0b3d180d183d0b7d0bad0b82c20d0bfd180d0b5d180d0b2d0b5d0bc20d186d0b8d0bad0bb0a09202020207d0a2020202020202020202020202064622e6578656328224445414c4c4f434154452073656c6563745f70726963653b22293b0a2020202020202020202020202064622e6578656328224445414c4c4f4341544520696e736572745f70726963653b22293b0a2020202020202020202020202064622e6578656328224445414c4c4f43415445207570646174655f70726963653b22293b0a20202020202020202020202020646f63756d656e742e717565727928293b0a20202020202020202020202020646f63756d656e742e63616c6349746f6728293b0a202020202020202020207d0a20202020202020202020656c73650a202020202020202020202020514d657373616765426f782e7761726e696e6728666f726d2c2022d094d0bed0bad183d0bcd0b5d0bdd18220436f6d6d657263654d4c222c2022d09dd0b520d0bdd0b0d0b9d0b4d0b5d0bd20d0bad0bed0bdd182d180d0b0d0b3d0b5d0bdd182202d20d0bfd180d0bed0b4d0b0d0b2d0b5d18622293b0a20202020202020207d0a2020202020202020656c73650a20202020202020202020514d657373616765426f782e7761726e696e6728666f726d2c2022d094d0bed0bad183d0bcd0b5d0bdd18220436f6d6d657263654d4c222c2022d0add182d0be20d0bdd0b520d0b4d0bed0bad183d0bcd0b5d0bdd18220d0bdd0b020d0bed182d0b3d180d183d0b7d0bad18320d182d0bed0b2d0b0d180d0b022293b0a2020202020207d0a202020202020656c73650a2020202020202020514d657373616765426f782e7761726e696e6728666f726d2c2022d094d0bed0bad183d0bcd0b5d0bdd18220436f6d6d657263654d4c222c2022d09dd0b520d183d0b4d0b0d0bbd0bed181d18c20d180d0b0d0b7d0bed0b1d180d0b0d182d18c20d0b4d0bed0bad183d0bcd0b5d0bdd18222293b0a20202020202066696c652e636c6f736528293b0a202020207d0a20202020656c73650a202020202020514d657373616765426f782e7761726e696e6728666f726d2c2022d094d0bed0bad183d0bcd0b5d0bdd18220436f6d6d657263654d4c222c2051537472696e672822d09dd0b520d0bcd0bed0b3d18320d0bed182d0bad180d18bd182d18c20d184d0b0d0b9d0bb2025313a5c6e25322e2229202e6172672866696c654e616d6529202e6172672866696c652e6572726f72537472696e67282929293b0a20207d0a7d0a0a0a66756e6374696f6e205772697465546f766172286669726d49642c2069642c206e616d652c206172746963756c2c20756e69742c207175616e2c2070726963652c2073756d290a2f2f20d097d0b0d0bfd0b8d188d0b5d0bc20d0bfd0bed0b7d0b8d186d0b8d18e20d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1822c20d0bfd180d0b5d0b4d0b2d0b0d180d0b8d182d0b5d0bbd18cd0bdd0be20d0b2d18bd18fd181d0bdd0b8d0b220d181d0bed0bed182d0b2d0b5d182d181d182d0b2d0b8d0b520d0b220d182d0b0d0b1d0bbd0b8d186d0b520d0bfd180d0b0d0b9d181d0bed0b20a7b0a2020766172206e6f6d4964203d20303b0a20207661722070726963654964203d20303b0a2020766172206e6f6d44696374203d2067657444696374696f6e6172792822d0bdd0bed0bcd0b5d0bdd0bad0bbd0b0d182d183d180d0b022293b0a20202f2f20d09fd0bed0b8d189d0b5d0bc20d0b220d0bfd180d0b0d0b9d181d0b520d0bfd0bed181d182d0b0d0b2d189d0b8d0bad0b020d0b7d0b0d0bfd0b8d181d18c20d0be20d0bfd0bed0b7d0b8d186d0b8d0b82c20d0bad0bed182d0bed180d0b0d18f20d0bfd0bed181d182d183d0bfd0b8d0bbd0b00a2020766172207072696365526563203d2064622e6578656351756572792822455845435554452073656c6563745f70726963652822202b206669726d4964202b20222c202722202b206964202b202227293b22293b0a20206966202870726963655265632e73697a65282920213d20302909092f2f20d095d181d0bbd0b820d0b220d0bfd180d0b0d0b9d181d0b520d0b5d181d182d18c20d0b7d0b0d0bfd0b8d181d0b820d0be20d182d0b0d0bad0bed0b920d0bfd0bed0b7d0b8d186d0b8d0b80a20207b0a202020206966202870726963655265632e66697273742829290a202020202020207b09090909090a202020202020202020206e6f6d4964203d2070726963655265632e7265636f726428292e76616c75652822d0bad0bed0b45fd0bdd0bed0bcd0b5d0bdd0bad0bbd0b0d182d183d180d0b022293b092f2f20d09fd0bed181d0bcd0bed182d180d0b8d0bc2c20d0bad0b0d0bad0bed0b920d0bdd0b0d188d0b5d0b920d0bfd0bed0b7d0b8d186d0b8d0b820d181d0bed0bed182d0b2d0b5d182d181d182d0b2d183d0b5d18220d18dd182d0be20d0bdd0b0d0b7d0b2d0b0d0bdd0b8d0b520d0b220d0bfd180d0b0d0b9d181d0b50a2020202020202020202070726963654964203d2070726963655265632e7265636f726428292e76616c75652822d0bad0bed0b422293b0a202020202020207d0a20207d0a2020696620286e6f6d4964203d3d2030290909092f2f20d095d181d0bbd0b820d0bcd18b20d0bdd0b520d0b7d0bdd0b0d0b5d0bc2c20d0bad0b0d0bad0bed0b920d0bdd0b0d188d0b5d0b920d0bfd0bed0b7d0b8d186d0b8d0b820d181d0bed0bed182d181d182d0b2d0b5d182d181d182d0b2d183d0b5d18220d18dd182d0be20d0bdd0b0d0b8d0bcd0b5d0bdd0bed0b2d0b0d0bdd0b8d0b50a20207b09090909092f2f20d182d0bed0b3d0b4d0b020d181d0bfd180d0bed181d0b8d0bc20d18dd182d0be20d18320d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18f0a2020202076617220666f726d5469746c65203d206e6f6d446963742e676574466f726d5469746c6528293b0a202020206e6f6d446963742e736574466f726d5469746c652822d0a3d0bad0b0d0b6d0b8d182d0b520d0bfd0bed0b7d0b8d186d0b8d18e20d0b0d0bdd0b0d0bbd0bed0b3d0b8d187d0bdd183d18e3a2022202b206e616d65202b2022202822202b206172746963756c202b20222922293b09092f2f20d0a3d181d182d0b0d0bdd0bed0b2d0b8d0bc20d0b220d0b7d0b0d0b3d0bed0bbd0bed0b2d0bad0b520d0bed0bad0bdd0b020d0bfd0bed0b4d181d0bad0b0d0b7d0bad18320d0b4d0bbd18f20d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18f0a202020206e6f6d446963742e6578656328293b0a202020206e6f6d446963742e736574466f726d5469746c6528666f726d5469746c65293b09090909092f2f20d092d0b5d180d0bdd0b5d0bc20d0bfd180d0b5d0b6d0bdd0b5d0b520d0bdd0b0d0b7d0b2d0b0d0bdd0b8d0b520d0bed0bad0bdd0b00a20202020696620286e6f6d446963742e6973466f726d53656c6563746564282929092f2f20d0b5d181d0bbd0b820d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18c20d0bdd0b0d0b6d0b0d0bb20d0bad0bdd0bed0bfd0bad183204f6b0a2020202020206e6f6d4964203d206e6f6d446963742e676574496428293b0a20202020656c73650a20202020202020657869744b657950726573736564203d20747275653b0a207d0a2020656c73650a202020206e6f6d446963742e7365744964286e6f6d4964293b09090a2020696620286e6f6d496420213d2030290909092f2f20d095d181d0bbd0b820d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18c20d0b2d18bd0b1d180d0b0d0bb20d0bad0b0d0bad183d18e2dd0bbd0b8d0b1d0be20d0bfd0bed0b7d0b8d186d0b8d18e20d0b220d181d0b2d0bed0b5d0b920d0bdd0bed0bcd0b5d0bdd0bad0bbd0b0d182d183d180d0b520d0b8d0bbd0b820d0bfd0bed0b7d0b8d186d0b8d18f20d0b1d18bd0bbd0b020d0b2d18bd0b1d180d0b0d0bdd0b020d0b0d0b2d182d0bed0bcd0b0d182d0b8d187d0b5d181d0bad0b820d0bdd0b020d0bed181d0bdd0bed0b2d0b0d0bdd0b8d0b820d181d0bed0bed182d0b2d0b5d182d181d182d0b2d0b8d18f0a20207b0a202020206966202870726963655265632e73697a652829203d3d20302909092f2f20d095d181d0bbd0b820d0b220d0bfd180d0b0d0b9d181d0b520d180d0b0d0bdd18cd188d0b520d182d0b0d0bad0bed0b920d0bfd0bed0b7d0b8d186d0b8d0b820d0bdd0b520d0b1d18bd0bbd0be0a202020207b0a20202020202064622e6578656328224558454355544520696e736572745f7072696365282722202b206964202b2022272c2722202b206e616d65202b2022272c2722202b206172746963756c202b2022272c2722202b20756e6974202b2022272c22202b207072696365202b20222c22202b206669726d4964202b20222c22202b206e6f6d4964202b2022293b22293b0a2020202020207072696365526563203d2064622e6578656351756572792822455845435554452073656c6563745f70726963652822202b206669726d4964202b20222c202722202b206964202b202227293b22293b0a2020202020206966202870726963655265632e73697a65282920213d20302909092f2f20d095d181d0bbd0b820d0b220d0bfd180d0b0d0b9d181d0b520d0b5d181d182d18c20d0b7d0b0d0bfd0b8d181d0b820d0be20d182d0b0d0bad0bed0b920d0bfd0bed0b7d0b8d186d0b8d0b80a2020202020207b0a202020202020202020206966202870726963655265632e66697273742829290a202020202020202020202020202070726963654964203d2070726963655265632e7265636f726428292e76616c75652822d0bad0bed0b422293b0a2020202020207d0a202020207d0a20202020656c73650a202020202020202064622e65786563282245584543555445207570646174655f70726963652822202b206e6f6d4964202b20222c2722202b206e616d65202b2022272c2722202b206172746963756c202b2022272c2722202b20756e6974202b2022272c22202b207072696365202b20222c22202b206669726d4964202b20222c22202b206964202b2022293b22293b0a202020202f2f20d097d0b0d0bfd0b8d188d0b5d0bc20d0bad0bed0bb2dd0b2d0be2c20d186d0b5d0bdd1832c20d181d183d0bcd0bcd18320d0b220d0bfd180d0bed0b2d0bed0b4d0bad1830a20202020646f63756d656e742e7072657061726556616c7565282270315f5fd0bad0bed0bb222c207175616e293b0a20202020646f63756d656e742e7072657061726556616c7565282270315f5fd186d0b5d0bdd0b0222c207072696365293b0a20202020646f63756d656e742e7072657061726556616c7565282270315f5fd181d183d0bcd0bcd0b0222c2073756d293b0a20202020646f63756d656e742e7072657061726556616c75652822d0bad0bed0b45fd0bfd180d0b0d0b9d181d18b222c2070726963654964293b0a202020202f2f20d0a1d0bed185d180d0b0d0bdd0b8d0bc20d0bfd180d0bed0b2d0bed0b4d0bad18320d0bdd0b020d181d0b5d180d0b2d0b5d180d0b50a20202020646f63756d656e742e617070656e64446f63537472696e6728293b0a20207d0a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b0a2f2f20d097d0b0d0bfd0b8d188d0b5d0bc20d0bdd0b0d0b8d0bcd0b5d0bdd0bed0b2d0b0d0bdd0b8d0b520d184d0b8d180d0bcd18b2dd0bfd0bed181d182d0b0d0b2d189d0b8d0bad0b020d0b220d0bad0bed0bcd0bcd0b5d0bdd182d0b0d180d0b8d0b820d0ba20d0b4d0bed0bad183d0bcd0b5d0bdd182d1830a09646f63756d656e74732e73657456616c75652822d09ad0bed0bcd0bcd0b5d0bdd182d0b0d180d0b8d0b9222c2067657444696374696f6e617279282276775fd0bad0bed0bdd182d180d0b0d0b3d0b5d0bdd182d18b22292e67657456616c75652822d0b8d0bcd18f2229293b0a7d0a0a0a2f2f2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2f0a2f2f20d0add182d0b020d187d0b0d181d182d18c20d181d0bad180d0b8d0bfd182d0b020d0bed182d0bdd0bed181d0b8d182d181d18f20d0ba20d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18fd0bc20d182d0b0d0b1d0bbd0b8d187d0bdd0bed0b920d187d0b0d181d182d0b820d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a0ad0bad0bed0bb203d2067657456616c7565282270315f5fd0bad0bed0bb22293b0ad186d0b5d0bdd0b0203d2067657456616c7565282270315f5fd186d0b5d0bdd0b022293b0ad181d183d0bcd0bcd0b0203d2067657456616c7565282270315f5fd181d183d0bcd0bcd0b022293b0a0a6966202867657443757272656e744669656c644e616d652829203d3d202270315f5fd181d183d0bcd0bcd0b02220262620d0bad0bed0bb20213d203029200a7b0a09d186d0b5d0bdd0b0203d20d181d183d0bcd0bcd0b0202f20d0bad0bed0bb3b0a7d0a656c7365200a7b0a09d181d183d0bcd0bcd0b0203d20d0bad0bed0bb202a20d186d0b5d0bdd0b03b0a7d0a0a73657456616c7565282270315f5fd0bad0bed0bb222c20d0bad0bed0bb293b0a73657456616c7565282270315f5fd186d0b5d0bdd0b0222c20d186d0b5d0bdd0b0293b0a73657456616c7565282270315f5fd181d183d0bcd0bcd0b0222c20d181d183d0bcd0bcd0b0293b0a0a0a
11	справочники.qs	0	\\x66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a
12	vw_доступ_к_справочникам.qs	0	\\x66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a
13	доступ.qs	0	\\x66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a
14	vw_доступ_к_топер.qs	0	\\x66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a
15	адрес.qs	0	\\x66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a
5	./scripts/формулы3.qs	0	\\x76617220d0bfd180d0bed186d0b5d0bdd182d181d0bad0b8d0b4d0bad0b8203d20303b092f2f20d0bfd180d0bed186d0b5d0bdd18220d181d0b4d0b5d0bbd0b0d0bdd0bdd0bed0b920d181d0bad0b8d0b4d0bad0b80a76617220d181d183d0bcd0bcd0b0d181d0bad0b8d0b4d0bad0b8203d20303b092f2f20d181d183d0bcd0bcd0b020d181d0b4d0b5d0bbd0b0d0bdd0bdd0bed0b920d0b2d180d183d187d0bdd183d18e20d181d0bad0b8d0b4d0bad0b80a76617220d181d183d0bcd0bcd0b0203d20303b092f2f20d181d183d0bcd0bcd0b020d0bfd180d0bed0b4d0b0d0b6d0b820d0b1d0b5d0b720d181d0bad0b8d0b4d0bed0ba0a76617220d181d0bad0b8d0b4d0bad0b0203d20303b092f2f20d181d0bad0b8d0b4d0bad0b00a0a0a66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a092f2f20d09fd180d0b820d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d0b820d181d0bfd0b8d0bdd0b1d0bed0bad181d0bed0b220d18120d0bfd180d0bed186d0b5d0bdd182d0bed0bc20d0b8d0bbd0b820d181d183d0bcd0bcd0bed0b920d181d0bad0b8d0b4d0bad0b820d0b7d0b0d0bfd183d181d182d0b8d0bc20d0bfd0b5d180d0b5d181d187d0b5d18220d0b8d182d0bed0b3d0bed0b20a09666f726d2e7370696e426f782e65646974696e6746696e69736865642e636f6e6e656374284576656e74416674657243616c63756c617465293b090a09666f726d2e646f75626c655370696e426f782e65646974696e6746696e69736865642e636f6e6e656374284576656e74416674657243616c63756c617465293b090a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a092f2f20d092d0bed181d181d182d0b0d0bdd0bed0b2d0b8d0bc20d0bfd0b5d180d0b5d0bcd0b5d0bdd0bdd18bd0b520d0b8d0b720d091d0940a09d0bfd180d0bed186d0b5d0bdd182d181d0bad0b8d0b4d0bad0b8203d20726573746f72655661726961626c652822d0bfd180d0bed186d0b5d0bdd182d181d0bad0b8d0b4d0bad0b822293b0a09d181d183d0bcd0bcd0b0d181d0bad0b8d0b4d0bad0b8203d20726573746f72655661726961626c652822d181d183d0bcd0bcd0b0d181d0bad0b8d0b4d0bad0b822293b0a09666f726d2e7370696e426f782e76616c7565203d20d0bfd180d0bed186d0b5d0bdd182d181d0bad0b8d0b4d0bad0b83b0a09666f726d2e646f75626c655370696e426f782e76616c7565203d20d181d183d0bcd0bcd0b0d181d0bad0b8d0b4d0bad0b83b0a0943616c6349746f6728293b0a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a092f2f20d0a1d0bed185d180d0b0d0bdd0b8d0bc20d0bfd0b5d180d0b5d0bcd0b5d0bdd0bdd18bd0b520d0b220d091d0940a09736176655661726961626c652822d0bfd180d0bed186d0b5d0bdd182d181d0bad0b8d0b4d0bad0b8222c20d0bfd180d0bed186d0b5d0bdd182d181d0bad0b8d0b4d0bad0b8293b0a09736176655661726961626c652822d181d183d0bcd0bcd0b0d181d0bad0b8d0b4d0bad0b8222c20d181d183d0bcd0bcd0b0d181d0bad0b8d0b4d0bad0b8293b0a7d0a0a2020202020200a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b2f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a09d0bfd180d0bed186d0b5d0bdd182d181d0bad0b8d0b4d0bad0b8203d20666f726d2e7370696e426f782e76616c75653b09092f2f20d092d0bed0b7d0bcd0b5d0bc20d0b7d0bdd0b0d187d0b5d0bdd0b8d0b520d181d0bad0b8d0b4d0bad0b82c20d183d181d182d0b0d0bdd0bed0b2d0bbd0b5d0bdd0bdd0bed0b520d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd0b5d0bc0a09d181d183d0bcd0bcd0b0d181d0bad0b8d0b4d0bad0b8203d20666f726d2e646f75626c655370696e426f782e76616c75653b09092f2f20d098d0bbd0b820d181d183d0bcd0bcd0bed0b2d0bed0b520d0b7d0bdd0b0d187d0b5d0bdd0b8d0b520d181d0bad0b8d0b4d0bad0b80a0943616c6349746f6728293b0a7d090a0a0a66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a09d186d0b5d0bdd0b0203d2067657456616c7565282276775fd0bdd0bed0bcd0b5d0bdd0bad0bbd0b0d182d183d180d0b05f5fd186d0b5d0bdd0b05fd180d0bed0b7d0bd22293b0a0973657456616c7565282270325f5fd186d0b5d0bdd0b0222c20d186d0b5d0bdd0b0293b0a7d0a0a66756e6374696f6e2043616c6349746f6728290a7b0a09d181d183d0bcd0bcd0b0203d2067657453756d56616c7565282270325f5fd181d183d0bcd0bcd0b022293b09092f2f20d09fd180d0bed181d183d0bcd0bcd0b8d180d183d0b5d0bc20d0b2d182d0bed180d183d18e20d0bfd180d0bed0b2d0bed0b4d0bad18320d0b220d0bed0bfd0b5d180d0b0d186d0b8d0b820d0b4d0bbd18f20d0b2d181d0b5d0b3d0be20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a0969662028d181d183d0bcd0bcd0b0d181d0bad0b8d0b4d0bad0b8203d3d2030290909092f2f20d095d181d0bbd0b820d181d183d0bcd0bcd0bed0b2d0bed0b520d0b7d0bdd0b0d187d0b5d0bdd0b8d0b520d0bdd0b520d181d0bad0b8d0b4d0bad0b820d183d181d182d0b0d0bdd0bed0b2d0bbd0b5d0bdd0be0a097b090909092f2f20d0a2d0bed0b3d0b4d0b020d181d0bad0b8d0b4d0bad18320d181d187d0b8d182d0b0d0b5d0bc20d0bfd0be20d0bfd180d0bed186d0b5d0bdd182d1830a0909d181d0bad0b8d0b4d0bad0b0203d20d181d183d0bcd0bcd0b0202a2020d0bfd180d0bed186d0b5d0bdd182d181d0bad0b8d0b4d0bad0b8202f203130303b0a097d0a09656c73650a097b0a0909d181d0bad0b8d0b4d0bad0b0203d20d181d183d0bcd0bcd0b0d181d0bad0b8d0b4d0bad0b83b0a097d0a0973657456616c7565282270335f5fd181d183d0bcd0bcd0b0222c2020d181d0bad0b8d0b4d0bad0b0293b09092f2f20d097d0b0d0bfd0b8d188d0b5d0bc20d0b7d0bdd0b0d187d0b5d0bdd0b8d0b520d181d0bad0b8d0b4d0bad0b820d0b220d091d09420d0b220d182d180d0b5d182d18cd0b5d0b92028d181d0b2d0bed0b1d0bed0b4d0bdd0bed0b92920d0bfd180d0bed0b2d0bed0b4d0bad0b50a09666f726d2e736b69646b614e756d657269632e73657456616c756528d181d0bad0b8d0b4d0bad0b0293b0a09666f726d2e767365676f4e756d657269632e73657456616c756528d181d183d0bcd0bcd0b0293b09090a09666f726d2e69746f674e756d657269632e73657456616c756528d181d183d0bcd0bcd0b02dd181d0bad0b8d0b4d0bad0b0293b0a7d0a0a2f2f3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d3d0a2f2f20d0a1d187d0b8d182d0b0d0b5d0bc20d0b7d0bdd0b0d187d0b5d0bdd0b8d18f20d0b220d182d0b0d0b1d0bbd0b8d187d0bdd0bed0b920d187d0b0d181d182d0b80a6966202867657443757272656e744669656c644e616d652829203d3d202270315f5fd0bad0bed0bb222909092f2f20d0a2d0bed0bbd18cd0bad0be20d0bfd180d0b820d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d0b820d0bad0bed0bbd0b8d187d0b5d181d182d0b2d0b0200a7b0a096966202867657456616c7565282270325f5fd186d0b5d0bdd0b0222920213d203029092f2f20d095d181d0bbd0b820d180d0bed0b7d0bdd0b8d187d0bdd0b0d18f20d186d0b5d0bdd0b020d183d0bad0b0d0b7d0b0d0bdd0b00a097b0a090976617220d0bad0bed0bb203d206765744f6c6456616c75652829202b2067657456616c75652822d0bad180d181d0b0d0bbd18cd0b4d0be315f5fd0bad0bed0bdd0bad0bed0bb22293b09092f2f20d09ad0bed0bbd0b8d187d0b5d181d182d0b2d0be20d0b2d181d0b5d0b3d0be0a090976617220d181d183d0bcd0bcd0b0203d2067657456616c7565282270315f5fd181d183d0bcd0bcd0b02229202b2067657456616c75652822d0bad180d181d0b0d0bbd18cd0b4d0be315f5fd0bad0bed0bdd181d0b0d0bbd18cd0b4d0be22293b092f2f20d0a1d183d0bcd0bcd0b020d0b2d181d0b5d0b3d0be0a090969662028d0bad0bed0bb20213d2030290a09097b0a0909092f2f20d09fd0bed181d187d0b8d182d0b0d0b5d0bc20d0bfd0b5d180d0b2d183d18e20d0bfd180d0bed0b2d0bed0b4d0bad1832028d0bfd0be20d0b7d0b0d0bad183d0bfd0bed187d0bdd0bed0b920d186d0b5d0bdd0b5290a09090976617220d186d0b5d0bdd0b0203d20d181d183d0bcd0bcd0b0202f20d0bad0bed0bb3b0a090909d181d183d0bcd0bcd0b0203d2067657456616c7565282270315f5fd0bad0bed0bb2229202a20d186d0b5d0bdd0b03b0a09090973657456616c7565282270315f5fd186d0b5d0bdd0b0222c20d186d0b5d0bdd0b0293b0a09090973657456616c7565282270315f5fd181d183d0bcd0bcd0b0222c20d181d183d0bcd0bcd0b0293b0a0909092f2f20d09fd0bed181d187d0b8d182d0b0d0b5d0bc20d0b2d182d0bed180d183d18e20d0bfd180d0bed0b2d0bed0b4d0bad1832028d0bfd0be20d180d0bed0b7d0bdd0b8d187d0bdd0bed0b920d186d0b5d0bdd0b5290a090909d186d0b5d0bdd0b0203d2067657456616c7565282270325f5fd186d0b5d0bdd0b022293b0a090909d181d183d0bcd0bcd0b0203d2067657456616c7565282270315f5fd0bad0bed0bb2229202a20d186d0b5d0bdd0b03b0a09090973657456616c7565282270325f5fd181d183d0bcd0bcd0b0222c20d181d183d0bcd0bcd0b0293b0a09097d0a097d0a09656c73650a097b0a09096966202867657456616c7565282270315f5fd0bad0bed0bb222920213d2030290a09097b0a0909096572726f724d657373616765203d2022d0a0d0bed0b7d0bdd0b8d187d0bdd0b0d18f20d186d0b5d0bdd0b020d0bfd0bed0b7d0b8d186d0b8d0b8205b22202b2067657456616c7565282276775fd0bdd0bed0bcd0b5d0bdd0bad0bbd0b0d182d183d180d0b05f5fd0b8d0bcd18f2229202b20225d20d0bdd0b520d0bed0bfd180d0b5d0b4d0b5d0bbd0b5d0bdd0b021223b0a090909736372697074526573756c74203d2066616c73653b0a09097d0a097d0a7d0a
4	./scripts/формулы2.qs	0	\\x66756e6374696f6e204576656e74417070656e6446726f6d51756572792869642c207265636f7264290a7b20202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d0bdd0bed0b2d0bed0b920d0b7d0b0d0bfd0b8d181d0b820d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b00a09696620286964203d3d2031290a097b202f2f20d095d181d0bbd0b820d0bed0b1d180d0b0d0b1d0b0d182d18bd0b2d0b0d0b5d182d181d18f20d0bfd0b5d180d0b2d18bd0b920d0b7d0b0d0bfd180d0bed1810a09097661722073657444696374203d2067657444696374696f6e6172792822d0bdd0b0d0b1d0bed1803122293b0a09097661722076776e6f6d44696374203d2067657444696374696f6e617279282276775fd0bdd0bed0bcd0b5d0bdd0bad0bbd0b0d182d183d180d0b022293b0a0909766172206164647244696374203d2067657444696374696f6e6172792822d0b0d0b4d180d0b5d18122293b0a09097661722073616c646f203d2067657453616c646f282234312e3122293b0a09090a090976776e6f6d446963742e7365744964287265636f72642ed0bad0bed0b4293b09092f2f20d0a1d0bfd180d0b0d0b2d0bed187d0bdd0b8d0ba20d0bdd0bed0bcd0b5d0bdd0bad0bbd0b0d182d183d180d18b20d183d181d182d0b0d0bdd0bed0b2d0b8d0bc20d0b220d0b7d0bdd0b0d187d0b5d0bdd0b8d0b520d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b00a090961646472446963742e71756572792822d0b8d0bcd18f203d2027302722293b09092f2f20d0a3d181d182d0b0d0bdd0bed0b2d0b8d0bc20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0ba20d0b0d0b4d180d0b5d181d0bed0b220d0bdd0b020d0b7d0bdd0b0d187d0b5d0bdd0b8d0b520d0bdd183d0bbd0b5d0b2d0bed0b3d0be20d0b0d0b4d180d0b5d181d0b00a0909736574446963742e676574496428293b09092f2f20d0a3d181d182d0b0d0bdd0bed0b2d0b8d0bc20d0bdd0b0d0b1d0bed1802dd181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0ba2022d09dd0b0d0b1d0bed180312220d0b220d181d0bed0bed182d0b2d0b5d182d181d182d0b2d0b8d0b820d18120d182d0b5d0bad183d189d0b8d0bcd0b820d0b7d0bdd0b0d187d0b5d0bdd0b8d18fd0bcd0b820d181d0b2d18fd0b7d0b0d0bdd0bdd18bd18520d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0bed0b2202276775fd0bdd0bed0bcd0b5d0bdd0bad0bbd0b0d182d183d180d0b02220d0b82022d0b0d0b4d180d0b5d18122200a090973616c646f2e7365744964287265636f72642ed0bad0bed0b4293b090a09092f2f20d097d0b0d0bfd0b8d188d0b5d0bc20d0bad0bed0bb2dd0b2d0be2c20d186d0b5d0bdd1832c20d181d183d0bcd0bcd18320d0b220d0bfd180d0bed0b2d0bed0b4d0bad1830a0909646f63756d656e742e7072657061726556616c7565282270315f5fd0bad0bed0bb222c207265636f72642ed0bad0bed0bdd0bad0bed0bb293b0a0909646f63756d656e742e7072657061726556616c7565282270315f5fd186d0b5d0bdd0b0222c207265636f72642ed0bad0bed0bdd186d0b5d0bdd0b0293b0a0909646f63756d656e742e7072657061726556616c7565282270315f5fd181d183d0bcd0bcd0b0222c207265636f72642ed0bad0bed0bdd181d0b0d0bbd18cd0b4d0be293b0a09092f2f20d0a1d0bed185d180d0b0d0bdd0b8d0bc20d0bfd180d0bed0b2d0bed0b4d0bad18320d0bdd0b020d181d0b5d180d0b2d0b5d180d0b50a0909646f63756d656e742e617070656e64446f63537472696e6728293b0a097d0a7d0a0a6966202867657443757272656e744669656c644e616d652829203d3d202270315f5fd0bad0bed0bb2229200a7b0a09d0bad0bed0bb203d206765744f6c6456616c75652829202b2067657456616c75652822d0bad180d181d0b0d0bbd18cd0b4d0be315f5fd0bad0bed0bdd0bad0bed0bb22293b092f2f20d09ad0bed0bbd0b8d187d0b5d181d182d0b2d0be20d0b2d181d0b5d0b3d0be0a09d181d183d0bcd0bcd0b0203d2067657456616c7565282270315f5fd181d183d0bcd0bcd0b02229202b2067657456616c75652822d0bad180d181d0b0d0bbd18cd0b4d0be315f5fd0bad0bed0bdd181d0b0d0bbd18cd0b4d0be22293b092f2f20d0a1d183d0bcd0bcd0b020d0b2d181d0b5d0b3d0be0a0969662028d0bad0bed0bb20213d2030290a097b0a0909d186d0b5d0bdd0b0203d20d181d183d0bcd0bcd0b0202f20d0bad0bed0bb3b0a0909d181d183d0bcd0bcd0b0203d2067657456616c7565282270315f5fd0bad0bed0bb2229202a20d186d0b5d0bdd0b03b0a090973657456616c7565282270315f5fd186d0b5d0bdd0b0222c20d186d0b5d0bdd0b0293b0a090973657456616c7565282270315f5fd181d183d0bcd0bcd0b0222c20d181d183d0bcd0bcd0b0293b0a097d0a7d0a
17	наценки.qs	0	\\x66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744b657950726573736564286b65794576656e74290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bbd18ed0b1d0bed0b920d0bad0bdd0bed0bfd0bad0b820d0bdd0b020d184d0bed180d0bcd0b52e20d09fd0b0d180d0b0d0bcd0b5d182d180206b65794576656e7420d0b8d0bcd0b5d0b5d18220d182d0b8d0bf20514b65794576656e740a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74417070656e6446726f6d51756572792869642c207265636f7264290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d0bdd0bed0b2d0bed0b920d0b7d0b0d0bfd0b8d181d0b820d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a
16	./scripts/формулы6.qs	0	\\x66756e6374696f6e204576656e74417070656e6446726f6d51756572792869642c207265636f7264290a7b20202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d0bdd0bed0b2d0bed0b920d0b7d0b0d0bfd0b8d181d0b820d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b00a09696620286964203d3d2031290a097b202f2f20d095d181d0bbd0b820d0bed0b1d180d0b0d0b1d0b0d182d18bd0b2d0b0d0b5d182d181d18f20d0bfd0b5d180d0b2d18bd0b920d0b7d0b0d0bfd180d0bed1810a0909766172206e65775072696365203d20303b0a2f2f09097661722076776e6f6d44696374203d2067657444696374696f6e617279282276775fd0bdd0bed0bcd0b5d0bdd0bad0bbd0b0d182d183d180d0b022293b0a2f2f09090a2f2f090976776e6f6d446963742e7365744964287265636f72642ed0bad0bed0b4293b09092f2f20d0a1d0bfd180d0b0d0b2d0bed187d0bdd0b8d0ba20d0bdd0bed0bcd0b5d0bdd0bad0bbd0b0d182d183d180d18b20d183d181d182d0b0d0bdd0bed0b2d0b8d0bc20d0b220d0b7d0bdd0b0d187d0b5d0bdd0b8d0b520d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b00a2f2f090961646472446963742e71756572792822d0b8d0bcd18f203d2027302722293b09092f2f20d0a3d181d182d0b0d0bdd0bed0b2d0b8d0bc20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0ba20d0b0d0b4d180d0b5d181d0bed0b220d0bdd0b020d0b7d0bdd0b0d187d0b5d0bdd0b8d0b520d0bdd183d0bbd0b5d0b2d0bed0b3d0be20d0b0d0b4d180d0b5d181d0b00a2f2f0909736574446963742e676574496428293b09092f2f20d0a3d181d182d0b0d0bdd0bed0b2d0b8d0bc20d0bdd0b0d0b1d0bed1802dd181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0ba2022d09dd0b0d0b1d0bed180312220d0b220d181d0bed0bed182d0b2d0b5d182d181d182d0b2d0b8d0b820d18120d182d0b5d0bad183d189d0b8d0bcd0b820d0b7d0bdd0b0d187d0b5d0bdd0b8d18fd0bcd0b820d181d0b2d18fd0b7d0b0d0bdd0bdd18bd18520d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0bed0b2202276775fd0bdd0bed0bcd0b5d0bdd0bad0bbd0b0d182d183d180d0b02220d0b82022d0b0d0b4d180d0b5d18122200a2f2f090973616c646f2e7365744964287265636f72642ed0bad0bed0b4293b090a09092f2f20d097d0b0d0bfd0b8d188d0b5d0bc20d0bad0bed0bb2dd0b2d0be2c20d186d0b5d0bdd1832c20d181d183d0bcd0bcd18320d0b220d0bfd180d0bed0b2d0bed0b4d0bad1830a0909646f63756d656e742e7072657061726556616c75652822d0bad0bed0b45fd0bdd0bed0bcd0b5d0bdd0bad0bbd0b0d182d183d180d0b0222c207265636f72642ed0bad0bed0b4293b0a0909646f63756d656e742e7072657061726556616c75652822d0bad0bed0bb222c207265636f72642ed0bad0bed0bdd0bad0bed0bb293b0a0909646f63756d656e742e7072657061726556616c75652822d181d182d0b0d180d186d0b5d0bdd0b0222c207265636f72642ed186d0b5d0bdd0b05fd180d0bed0b7d0bd293b0a0909646f63756d656e742e7072657061726556616c75652822d0b7d0b0d0bad186d0b5d0bdd0b0222c207265636f72642ed0b7d0b0d0bad186d0b5d0bdd0b0293b0a0909696620287265636f72642ed0b7d0b0d0bad186d0b5d0bdd0b0203e2030290a09097b0a0909097661722063757272656e7450726f666974203d20287265636f72642ed186d0b5d0bdd0b05fd180d0bed0b7d0bd202f207265636f72642ed0b7d0b0d0bad186d0b5d0bdd0b0202d203129202a203130303b09092f2f20d092d18bd187d0b8d181d0bbd0b8d0bc20d182d0b5d0bad183d189d183d18e20d0bdd0b0d186d0b5d0bdd0bad1832c20d1822ed0ba2e20d0bdd0b0d186d0b5d0bdd0bad18320d0bfd180d0b820d182d0b5d0bad183d189d0b5d0b920d180d0bed0b7d0bdd0b8d187d0bdd0bed0b920d186d0b5d0bdd0b50a0909096966202863757272656e7450726f666974203c207265636f72642ed0bcd0b8d0bdd0bfd180d0bed186d0b5d0bdd182207c7c2063757272656e7450726f666974203e207265636f72642ed0bcd0b0d0bad181d0bfd180d0bed186d0b5d0bdd18229092f2f20d095d181d0bbd0b820d182d0b5d0bad183d189d0b0d18f20d0bdd0b0d186d0b5d0bdd0bad0b020d0bdd0b520d183d0bad0bbd0b0d0b4d18bd0b2d0b0d0b5d182d181d18f20d0b220d0b4d0b8d0b0d0bfd0b0d0b7d0bed0bd20d0b7d0b0d0b4d0b0d0bdd0bdd18bd18520d0bdd0bed180d0bcd0b0d0bbd18cd0bdd18bd18520d0bdd0b0d186d0b5d0bdd0bed0ba0a0909097b0a090909096e65775072696365203d207265636f72642ed0b7d0b0d0bad186d0b5d0bdd0b0202a20287265636f72642ed0bdd0b0d186d0b5d0bdd0bad0b0202f20313030202b2031293b0a0909097d0a090909646f63756d656e742e7072657061726556616c75652822d181d182d0b0d180d0bdd0b0d186d0b5d0bdd0bad0b0222c2063757272656e7450726f666974293b0a090909646f63756d656e742e7072657061726556616c75652822d0bdd0bed0b2d0bdd0b0d186d0b5d0bdd0bad0b0222c207265636f72642ed0bdd0b0d186d0b5d0bdd0bad0b0293b0a09097d0a0909656c73650a09097b20202f2f20d097d0b0d0bad183d0bfd0bed187d0bdd0b0d18f20d186d0b5d0bdd0b020d0bdd0b520d0b8d0b7d0b2d0b5d181d182d0bdd0b02c20d0bfd0bed0bfd180d0bed0b1d183d0b5d0bc20d0bdd0b0d0b9d182d0b820d186d0b5d0bdd18320d0bdd0b020d18dd182d18320d0bfd0bed0b7d0b8d186d0b8d18e20d18320d0bfd0bed181d182d0b0d0b2d189d0b8d0bad0bed0b20a2f2f0909096e65775072696365203d207265636f72642e0a09097d0a09092f2f20d0a1d0bed185d180d0b0d0bdd0b8d0bc20d0bfd180d0bed0b2d0bed0b4d0bad18320d0bdd0b020d181d0b5d180d0b2d0b5d180d0b50a0909646f63756d656e742e7072657061726556616c75652822d0bdd0bed0b2d186d0b5d0bdd0b0222c206e65775072696365293b0a0909646f63756d656e742e617070656e64446f63537472696e6728293b0a097d0a7d0a0a0a0a
\.


--
-- TOC entry 3121 (class 0 OID 16786)
-- Dependencies: 237
-- Data for Name: фирмы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "фирмы" ("код", "имя") FROM stdin;
3	 Дальтек
\.


--
-- TOC entry 3000 (class 2606 OID 16820)
-- Dependencies: 200 200
-- Name: адрес_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "адрес"
    ADD CONSTRAINT "адрес_pkey" PRIMARY KEY ("код");


--
-- TOC entry 3063 (class 2606 OID 34110)
-- Dependencies: 249 249
-- Name: атрибуты1_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "атрибуты1"
    ADD CONSTRAINT "атрибуты1_pkey" PRIMARY KEY ("код");


--
-- TOC entry 3055 (class 2606 OID 34068)
-- Dependencies: 245 245
-- Name: атрибуты3_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "атрибуты3"
    ADD CONSTRAINT "атрибуты3_pkey" PRIMARY KEY ("код");


--
-- TOC entry 3059 (class 2606 OID 34083)
-- Dependencies: 247 247
-- Name: атрибуты6_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "атрибуты6"
    ADD CONSTRAINT "атрибуты6_pkey" PRIMARY KEY ("код");


--
-- TOC entry 3002 (class 2606 OID 16822)
-- Dependencies: 202 202
-- Name: банки_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "банки"
    ADD CONSTRAINT "банки_pkey" PRIMARY KEY ("код");


--
-- TOC entry 3006 (class 2606 OID 16824)
-- Dependencies: 204 204
-- Name: банковские_счета_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "банковские_счета"
    ADD CONSTRAINT "банковские_счета_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2951 (class 2606 OID 16826)
-- Dependencies: 170 170
-- Name: блокпериоды_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "блокпериоды"
    ADD CONSTRAINT "блокпериоды_pkey" PRIMARY KEY ("код");


--
-- TOC entry 3010 (class 2606 OID 16828)
-- Dependencies: 207 207
-- Name: виды_расходов_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "виды_расходов"
    ADD CONSTRAINT "виды_расходов_pkey" PRIMARY KEY ("код");


--
-- TOC entry 3014 (class 2606 OID 16830)
-- Dependencies: 209 209
-- Name: группы_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "группы"
    ADD CONSTRAINT "группы_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2959 (class 2606 OID 16832)
-- Dependencies: 174 174
-- Name: документы_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "документы"
    ADD CONSTRAINT "документы_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2965 (class 2606 OID 16834)
-- Dependencies: 177 177
-- Name: доступ_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "доступ"
    ADD CONSTRAINT "доступ_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2973 (class 2606 OID 16836)
-- Dependencies: 185 185
-- Name: журнал_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "журнал"
    ADD CONSTRAINT "журнал_pkey" PRIMARY KEY ("код");


--
-- TOC entry 3053 (class 2606 OID 34045)
-- Dependencies: 242 242
-- Name: запросы_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "запросы"
    ADD CONSTRAINT "запросы_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2975 (class 2606 OID 16838)
-- Dependencies: 187 187
-- Name: константы_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "константы"
    ADD CONSTRAINT "константы_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2955 (class 2606 OID 16840)
-- Dependencies: 172 172
-- Name: контрагенты_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "контрагенты"
    ADD CONSTRAINT "контрагенты_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2979 (class 2606 OID 16842)
-- Dependencies: 190 190
-- Name: материалы_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "материалы"
    ADD CONSTRAINT "материалы_pkey" PRIMARY KEY ("код");


--
-- TOC entry 3018 (class 2606 OID 16844)
-- Dependencies: 217 217
-- Name: набор1_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "набор1"
    ADD CONSTRAINT "набор1_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2983 (class 2606 OID 16846)
-- Dependencies: 192 192
-- Name: номенклатура_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "номенклатура"
    ADD CONSTRAINT "номенклатура_pkey" PRIMARY KEY ("код");


--
-- TOC entry 3020 (class 2606 OID 16848)
-- Dependencies: 220 220
-- Name: нумераторы_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "нумераторы"
    ADD CONSTRAINT "нумераторы_pkey" PRIMARY KEY ("код");


--
-- TOC entry 3024 (class 2606 OID 16850)
-- Dependencies: 222 222
-- Name: персонал_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "персонал"
    ADD CONSTRAINT "персонал_pkey" PRIMARY KEY ("код");


--
-- TOC entry 3029 (class 2606 OID 16852)
-- Dependencies: 224 224
-- Name: прайсы_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "прайсы"
    ADD CONSTRAINT "прайсы_pkey" PRIMARY KEY ("код");


--
-- TOC entry 3039 (class 2606 OID 16854)
-- Dependencies: 226 226
-- Name: предметы_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "предметы"
    ADD CONSTRAINT "предметы_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2987 (class 2606 OID 16856)
-- Dependencies: 194 194
-- Name: проводки_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "проводки"
    ADD CONSTRAINT "проводки_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2969 (class 2606 OID 16858)
-- Dependencies: 181 181
-- Name: справочники_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "справочники"
    ADD CONSTRAINT "справочники_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2998 (class 2606 OID 16860)
-- Dependencies: 197 197
-- Name: столбцы_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "столбцы"
    ADD CONSTRAINT "столбцы_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2947 (class 2606 OID 16862)
-- Dependencies: 168 168
-- Name: счета_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "счета"
    ADD CONSTRAINT "счета_pkey" PRIMARY KEY ("код");


--
-- TOC entry 3043 (class 2606 OID 16864)
-- Dependencies: 232 232
-- Name: типыобъектов_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "типыобъектов"
    ADD CONSTRAINT "типыобъектов_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2971 (class 2606 OID 16866)
-- Dependencies: 183 183
-- Name: топер_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "топер"
    ADD CONSTRAINT "топер_pkey" PRIMARY KEY ("код");


--
-- TOC entry 3047 (class 2606 OID 16868)
-- Dependencies: 235 235
-- Name: файлы_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "файлы"
    ADD CONSTRAINT "файлы_pkey" PRIMARY KEY ("код");


--
-- TOC entry 3049 (class 2606 OID 16870)
-- Dependencies: 237 237
-- Name: фирмы_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "фирмы"
    ADD CONSTRAINT "фирмы_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2944 (class 1259 OID 16871)
-- Dependencies: 164
-- Name: objectnames_name_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX objectnames_name_idx ON objectnames USING btree (name);


--
-- TOC entry 3064 (class 1259 OID 34111)
-- Dependencies: 249 249
-- Name: атрибуты1_доккод_стр_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "атрибуты1_доккод_стр_idx" ON "атрибуты1" USING btree ("доккод", "стр");


--
-- TOC entry 3065 (class 1259 OID 34112)
-- Dependencies: 249
-- Name: атрибуты1_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "атрибуты1_код_idx" ON "атрибуты1" USING btree ("код");


--
-- TOC entry 3056 (class 1259 OID 34070)
-- Dependencies: 245 245
-- Name: атрибуты3_доккод_стр_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "атрибуты3_доккод_стр_idx" ON "атрибуты3" USING btree ("доккод", "стр");


--
-- TOC entry 3057 (class 1259 OID 34069)
-- Dependencies: 245
-- Name: атрибуты3_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "атрибуты3_код_idx" ON "атрибуты3" USING btree ("код");


--
-- TOC entry 3060 (class 1259 OID 34084)
-- Dependencies: 247 247
-- Name: атрибуты6_доккод_стр_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "атрибуты6_доккод_стр_idx" ON "атрибуты6" USING btree ("доккод", "стр");


--
-- TOC entry 3061 (class 1259 OID 34085)
-- Dependencies: 247
-- Name: атрибуты6_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "атрибуты6_код_idx" ON "атрибуты6" USING btree ("код");


--
-- TOC entry 3003 (class 1259 OID 16872)
-- Dependencies: 202
-- Name: банки_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "банки_имя_idx" ON "банки" USING btree ("имя");


--
-- TOC entry 3004 (class 1259 OID 16873)
-- Dependencies: 202
-- Name: банки_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "банки_код_idx" ON "банки" USING btree ("код");


--
-- TOC entry 3007 (class 1259 OID 16874)
-- Dependencies: 204
-- Name: банковские_счета_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "банковские_счета_имя_idx" ON "банковские_счета" USING btree ("имя");


--
-- TOC entry 3008 (class 1259 OID 16875)
-- Dependencies: 204
-- Name: банковские_счета_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "банковские_счета_код_idx" ON "банковские_счета" USING btree ("код");


--
-- TOC entry 2952 (class 1259 OID 16876)
-- Dependencies: 170
-- Name: блокпериоды_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "блокпериоды_имя_idx" ON "блокпериоды" USING btree ("имя");


--
-- TOC entry 2953 (class 1259 OID 16877)
-- Dependencies: 170
-- Name: блокпериоды_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "блокпериоды_код_idx" ON "блокпериоды" USING btree ("код");


--
-- TOC entry 3011 (class 1259 OID 16878)
-- Dependencies: 207
-- Name: виды_расходов_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "виды_расходов_имя_idx" ON "виды_расходов" USING btree ("имя");


--
-- TOC entry 3012 (class 1259 OID 16879)
-- Dependencies: 207
-- Name: виды_расходов_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "виды_расходов_код_idx" ON "виды_расходов" USING btree ("код");


--
-- TOC entry 3015 (class 1259 OID 16880)
-- Dependencies: 209
-- Name: группы_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "группы_имя_idx" ON "группы" USING btree ("имя");


--
-- TOC entry 3016 (class 1259 OID 16881)
-- Dependencies: 209
-- Name: группы_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "группы_код_idx" ON "группы" USING btree ("код");


--
-- TOC entry 2960 (class 1259 OID 16882)
-- Dependencies: 174 174 174
-- Name: документы_авто_опер_дата_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "документы_авто_опер_дата_idx" ON "документы" USING btree ("авто", "опер", "дата");


--
-- TOC entry 2961 (class 1259 OID 16883)
-- Dependencies: 174
-- Name: документы_дата_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "документы_дата_idx" ON "документы" USING btree ("дата");


--
-- TOC entry 2962 (class 1259 OID 16884)
-- Dependencies: 174 174 174
-- Name: документы_дата_опер_авто_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "документы_дата_опер_авто_idx" ON "документы" USING btree ("дата", "опер", "авто");


--
-- TOC entry 2963 (class 1259 OID 16885)
-- Dependencies: 174
-- Name: документы_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "документы_код_idx" ON "документы" USING btree ("код");


--
-- TOC entry 2966 (class 1259 OID 16886)
-- Dependencies: 177
-- Name: доступ_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "доступ_имя_idx" ON "доступ" USING btree ("имя");


--
-- TOC entry 2967 (class 1259 OID 16887)
-- Dependencies: 177
-- Name: доступ_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "доступ_код_idx" ON "доступ" USING btree ("код");


--
-- TOC entry 3050 (class 1259 OID 25817)
-- Dependencies: 240
-- Name: заявка_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "заявка_код_idx" ON "заявка" USING btree ("код");


--
-- TOC entry 3051 (class 1259 OID 25818)
-- Dependencies: 240
-- Name: заявка_код_номенклатура; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "заявка_код_номенклатура" ON "заявка" USING btree ("код_номенклатура");


--
-- TOC entry 2976 (class 1259 OID 16888)
-- Dependencies: 187
-- Name: константы_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "константы_имя_idx" ON "константы" USING btree ("имя");


--
-- TOC entry 2977 (class 1259 OID 16889)
-- Dependencies: 187
-- Name: константы_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "константы_код_idx" ON "константы" USING btree ("код");


--
-- TOC entry 2956 (class 1259 OID 16890)
-- Dependencies: 172
-- Name: контрагенты_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "контрагенты_имя_idx" ON "контрагенты" USING btree ("имя");


--
-- TOC entry 2957 (class 1259 OID 16891)
-- Dependencies: 172
-- Name: контрагенты_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "контрагенты_код_idx" ON "контрагенты" USING btree ("код");


--
-- TOC entry 2980 (class 1259 OID 16892)
-- Dependencies: 190
-- Name: материалы_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "материалы_имя_idx" ON "материалы" USING btree ("имя");


--
-- TOC entry 2981 (class 1259 OID 16893)
-- Dependencies: 190
-- Name: материалы_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "материалы_код_idx" ON "материалы" USING btree ("код");


--
-- TOC entry 3066 (class 1259 OID 34151)
-- Dependencies: 251
-- Name: наценки_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "наценки_имя_idx" ON "наценки" USING btree ("имя");


--
-- TOC entry 3067 (class 1259 OID 34152)
-- Dependencies: 251
-- Name: наценки_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "наценки_код_idx" ON "наценки" USING btree ("код");


--
-- TOC entry 3068 (class 1259 OID 34153)
-- Dependencies: 251
-- Name: наценки_код_группы_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "наценки_код_группы_idx" ON "наценки" USING btree ("код_группы");


--
-- TOC entry 2984 (class 1259 OID 16894)
-- Dependencies: 192
-- Name: номенклатура_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "номенклатура_имя_idx" ON "номенклатура" USING btree ("имя");


--
-- TOC entry 2985 (class 1259 OID 16895)
-- Dependencies: 192
-- Name: номенклатура_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "номенклатура_код_idx" ON "номенклатура" USING btree ("код");


--
-- TOC entry 3021 (class 1259 OID 16896)
-- Dependencies: 220
-- Name: нумераторы_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "нумераторы_имя_idx" ON "нумераторы" USING btree ("имя");


--
-- TOC entry 3022 (class 1259 OID 16897)
-- Dependencies: 220
-- Name: нумераторы_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "нумераторы_код_idx" ON "нумераторы" USING btree ("код");


--
-- TOC entry 3025 (class 1259 OID 16898)
-- Dependencies: 222
-- Name: персонал_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "персонал_имя_idx" ON "персонал" USING btree ("имя");


--
-- TOC entry 3026 (class 1259 OID 16899)
-- Dependencies: 222
-- Name: персонал_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "персонал_код_idx" ON "персонал" USING btree ("код");


--
-- TOC entry 3027 (class 1259 OID 16900)
-- Dependencies: 224
-- Name: прайсы_fts_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "прайсы_fts_idx" ON "прайсы" USING gin (fts);


--
-- TOC entry 3030 (class 1259 OID 16901)
-- Dependencies: 224
-- Name: прайсы_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "прайсы_имя_idx" ON "прайсы" USING btree ("имя" varchar_pattern_ops);


--
-- TOC entry 3031 (class 1259 OID 16902)
-- Dependencies: 224
-- Name: прайсы_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "прайсы_код_idx" ON "прайсы" USING btree ("код");


--
-- TOC entry 3032 (class 1259 OID 16903)
-- Dependencies: 224
-- Name: прайсы_код_товар; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "прайсы_код_товар" ON "прайсы" USING btree ("код_номенклатура");


--
-- TOC entry 3033 (class 1259 OID 16904)
-- Dependencies: 224 224
-- Name: прайсы_код_товар_код_фирмы; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "прайсы_код_товар_код_фирмы" ON "прайсы" USING btree ("код_номенклатура", "код_фирмы");


--
-- TOC entry 3034 (class 1259 OID 16905)
-- Dependencies: 224
-- Name: прайсы_код_фирмы_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "прайсы_код_фирмы_idx" ON "прайсы" USING btree ("код_фирмы");


--
-- TOC entry 3035 (class 1259 OID 16906)
-- Dependencies: 224 224
-- Name: прайсы_код_фирмы_имя; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "прайсы_код_фирмы_имя" ON "прайсы" USING btree ("код_фирмы", "имя");


--
-- TOC entry 3036 (class 1259 OID 16907)
-- Dependencies: 224 224
-- Name: прайсы_код_фирмы_кодвпрайсе; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "прайсы_код_фирмы_кодвпрайсе" ON "прайсы" USING btree ("код_фирмы", "кодвпрайсе");


--
-- TOC entry 3037 (class 1259 OID 16908)
-- Dependencies: 224
-- Name: прайсы_кодвпрайсе; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "прайсы_кодвпрайсе" ON "прайсы" USING btree ("кодвпрайсе");


--
-- TOC entry 3040 (class 1259 OID 16909)
-- Dependencies: 226
-- Name: предметы_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "предметы_имя_idx" ON "предметы" USING btree ("имя");


--
-- TOC entry 3041 (class 1259 OID 16910)
-- Dependencies: 226
-- Name: предметы_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "предметы_код_idx" ON "предметы" USING btree ("код");


--
-- TOC entry 2988 (class 1259 OID 16911)
-- Dependencies: 194 194 194
-- Name: проводки_дбкод_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "проводки_дбкод_idx" ON "проводки" USING btree ("дбсчет", "дбкод", "доккод");


--
-- TOC entry 2989 (class 1259 OID 16912)
-- Dependencies: 194 194
-- Name: проводки_дбсчет_опер_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "проводки_дбсчет_опер_idx" ON "проводки" USING btree ("дбсчет", "опер");


--
-- TOC entry 2990 (class 1259 OID 16913)
-- Dependencies: 194
-- Name: проводки_доккод_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "проводки_доккод_idx" ON "проводки" USING btree ("доккод");


--
-- TOC entry 2991 (class 1259 OID 16914)
-- Dependencies: 194 194 194
-- Name: проводки_доккод_опер_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "проводки_доккод_опер_idx" ON "проводки" USING btree ("доккод", "опер", "номеропер");


--
-- TOC entry 2992 (class 1259 OID 16915)
-- Dependencies: 194 194
-- Name: проводки_доккод_стр_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "проводки_доккод_стр_idx" ON "проводки" USING btree ("доккод", "стр");


--
-- TOC entry 2993 (class 1259 OID 16916)
-- Dependencies: 194
-- Name: проводки_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "проводки_код_idx" ON "проводки" USING btree ("код");


--
-- TOC entry 2994 (class 1259 OID 16917)
-- Dependencies: 194 194 194
-- Name: проводки_кркод_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "проводки_кркод_idx" ON "проводки" USING btree ("крсчет", "кркод", "доккод");


--
-- TOC entry 2995 (class 1259 OID 16918)
-- Dependencies: 194 194
-- Name: проводки_крсчет_опер_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "проводки_крсчет_опер_idx" ON "проводки" USING btree ("крсчет", "опер");


--
-- TOC entry 2996 (class 1259 OID 16919)
-- Dependencies: 194 194
-- Name: проводки_опер_номеропер_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "проводки_опер_номеропер_idx" ON "проводки" USING btree ("опер", "номеропер");


--
-- TOC entry 2945 (class 1259 OID 16920)
-- Dependencies: 167 167
-- Name: сальдо_счет_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "сальдо_счет_код_idx" ON "сальдо" USING btree ("счет", "код");


--
-- TOC entry 2948 (class 1259 OID 16921)
-- Dependencies: 168
-- Name: счета_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "счета_имя_idx" ON "счета" USING btree ("имя");


--
-- TOC entry 2949 (class 1259 OID 16922)
-- Dependencies: 168
-- Name: счета_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "счета_код_idx" ON "счета" USING btree ("код");


--
-- TOC entry 3044 (class 1259 OID 16923)
-- Dependencies: 232
-- Name: типыобъектов_имя_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "типыобъектов_имя_idx" ON "типыобъектов" USING btree ("имя");


--
-- TOC entry 3045 (class 1259 OID 16924)
-- Dependencies: 232
-- Name: типыобъектов_код_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "типыобъектов_код_idx" ON "типыобъектов" USING btree ("код");


--
-- TOC entry 3082 (class 2620 OID 16925)
-- Dependencies: 200 273
-- Name: testdeleting_адрес; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_адрес" BEFORE DELETE ON "адрес" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 3083 (class 2620 OID 16926)
-- Dependencies: 273 202
-- Name: testdeleting_банки; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_банки" BEFORE DELETE ON "банки" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 3084 (class 2620 OID 16927)
-- Dependencies: 273 204
-- Name: testdeleting_банковские_счета; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_банковские_счета" BEFORE DELETE ON "банковские_счета" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 3071 (class 2620 OID 16928)
-- Dependencies: 273 170
-- Name: testdeleting_блокпериоды; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_блокпериоды" BEFORE DELETE ON "блокпериоды" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 3085 (class 2620 OID 16929)
-- Dependencies: 207 273
-- Name: testdeleting_виды_расходов; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_виды_расходов" BEFORE DELETE ON "виды_расходов" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 3074 (class 2620 OID 16930)
-- Dependencies: 273 177
-- Name: testdeleting_доступ; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_доступ" BEFORE DELETE ON "доступ" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 3092 (class 2620 OID 25819)
-- Dependencies: 240 273
-- Name: testdeleting_заявка; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_заявка" BEFORE DELETE ON "заявка" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 3075 (class 2620 OID 16931)
-- Dependencies: 187 273
-- Name: testdeleting_константы; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_константы" BEFORE DELETE ON "константы" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 3072 (class 2620 OID 16932)
-- Dependencies: 273 172
-- Name: testdeleting_контрагенты; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_контрагенты" BEFORE DELETE ON "контрагенты" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 3076 (class 2620 OID 16933)
-- Dependencies: 190 273
-- Name: testdeleting_материалы; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_материалы" BEFORE DELETE ON "материалы" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 3086 (class 2620 OID 16934)
-- Dependencies: 217 273
-- Name: testdeleting_набор1; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_набор1" BEFORE DELETE ON "набор1" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 3093 (class 2620 OID 34154)
-- Dependencies: 251 273
-- Name: testdeleting_наценки; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_наценки" BEFORE DELETE ON "наценки" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 3077 (class 2620 OID 25798)
-- Dependencies: 273 192
-- Name: testdeleting_номенклатура; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_номенклатура" BEFORE DELETE ON "номенклатура" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 3087 (class 2620 OID 16935)
-- Dependencies: 220 273
-- Name: testdeleting_нумераторы; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_нумераторы" BEFORE DELETE ON "нумераторы" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 3088 (class 2620 OID 16936)
-- Dependencies: 222 273
-- Name: testdeleting_персонал; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_персонал" BEFORE DELETE ON "персонал" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 3069 (class 2620 OID 16937)
-- Dependencies: 167 268
-- Name: testdeleting_сальдо; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_сальдо" BEFORE DELETE ON "сальдо" FOR EACH ROW EXECUTE PROCEDURE "testdeleting_сальдо"();


--
-- TOC entry 3090 (class 2620 OID 16938)
-- Dependencies: 273 232
-- Name: testdeleting_типыобъектов; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_типыобъектов" BEFORE DELETE ON "типыобъектов" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 3091 (class 2620 OID 16939)
-- Dependencies: 237 273
-- Name: testdeleting_фирмы; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_фирмы" BEFORE DELETE ON "фирмы" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 3078 (class 2620 OID 25799)
-- Dependencies: 192 270
-- Name: tsvectorupdate_номенклатура; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "tsvectorupdate_номенклатура" BEFORE INSERT OR UPDATE ON "номенклатура" FOR EACH ROW EXECUTE PROCEDURE tsvectorupdate();


--
-- TOC entry 3089 (class 2620 OID 16940)
-- Dependencies: 270 224
-- Name: tsvectorupdate_прайсы; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "tsvectorupdate_прайсы" BEFORE INSERT OR UPDATE ON "прайсы" FOR EACH ROW EXECUTE PROCEDURE tsvectorupdate();


--
-- TOC entry 3079 (class 2620 OID 16941)
-- Dependencies: 194 271
-- Name: вставитьпроводку; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "вставитьпроводку" BEFORE INSERT ON "проводки" FOR EACH ROW EXECUTE PROCEDURE "вставитьпроводку"();


--
-- TOC entry 3070 (class 2620 OID 16942)
-- Dependencies: 272 167
-- Name: считатьконечноесальдо; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "считатьконечноесальдо" BEFORE INSERT OR UPDATE ON "сальдо" FOR EACH ROW EXECUTE PROCEDURE "считатьконечноесальдо"();


--
-- TOC entry 3080 (class 2620 OID 16943)
-- Dependencies: 274 194
-- Name: считатьпроводку; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "считатьпроводку" BEFORE UPDATE ON "проводки" FOR EACH ROW EXECUTE PROCEDURE "считатьпроводку"();


--
-- TOC entry 3073 (class 2620 OID 16944)
-- Dependencies: 174 275
-- Name: удалитьдокумент; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "удалитьдокумент" BEFORE DELETE ON "документы" FOR EACH ROW EXECUTE PROCEDURE "удалитьдокумент"();


--
-- TOC entry 3081 (class 2620 OID 16945)
-- Dependencies: 276 194
-- Name: удалитьпроводку; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "удалитьпроводку" BEFORE DELETE ON "проводки" FOR EACH ROW EXECUTE PROCEDURE "удалитьпроводку"();


--
-- TOC entry 3132 (class 0 OID 0)
-- Dependencies: 6
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- TOC entry 3134 (class 0 OID 0)
-- Dependencies: 277
-- Name: sp_calcaccoborot(character varying, character varying, character varying); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_calcaccoborot(cacc character varying, cdate1 character varying, cdate2 character varying) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_calcaccoborot(cacc character varying, cdate1 character varying, cdate2 character varying) FROM sa;
GRANT ALL ON FUNCTION sp_calcaccoborot(cacc character varying, cdate1 character varying, cdate2 character varying) TO sa;
GRANT ALL ON FUNCTION sp_calcaccoborot(cacc character varying, cdate1 character varying, cdate2 character varying) TO bookkeeper;


--
-- TOC entry 3135 (class 0 OID 0)
-- Dependencies: 264
-- Name: sp_calcdocoborot(character varying, character varying, character varying); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_calcdocoborot(cacc character varying, cdate1 character varying, cdate2 character varying) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_calcdocoborot(cacc character varying, cdate1 character varying, cdate2 character varying) FROM sa;
GRANT ALL ON FUNCTION sp_calcdocoborot(cacc character varying, cdate1 character varying, cdate2 character varying) TO sa;
GRANT ALL ON FUNCTION sp_calcdocoborot(cacc character varying, cdate1 character varying, cdate2 character varying) TO bookkeeper;


--
-- TOC entry 3136 (class 0 OID 0)
-- Dependencies: 278
-- Name: sp_calcobjoborot(character varying, integer, character varying, character varying); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_calcobjoborot(cacc character varying, pnobj integer, cdate1 character varying, cdate2 character varying) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_calcobjoborot(cacc character varying, pnobj integer, cdate1 character varying, cdate2 character varying) FROM sa;
GRANT ALL ON FUNCTION sp_calcobjoborot(cacc character varying, pnobj integer, cdate1 character varying, cdate2 character varying) TO sa;
GRANT ALL ON FUNCTION sp_calcobjoborot(cacc character varying, pnobj integer, cdate1 character varying, cdate2 character varying) TO bookkeeper;


--
-- TOC entry 3137 (class 0 OID 0)
-- Dependencies: 279
-- Name: sp_calcoborot(character varying, character varying, character varying); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_calcoborot(cacc character varying, cdate1 character varying, cdate2 character varying) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_calcoborot(cacc character varying, cdate1 character varying, cdate2 character varying) FROM sa;
GRANT ALL ON FUNCTION sp_calcoborot(cacc character varying, cdate1 character varying, cdate2 character varying) TO sa;
GRANT ALL ON FUNCTION sp_calcoborot(cacc character varying, cdate1 character varying, cdate2 character varying) TO bookkeeper;


--
-- TOC entry 3138 (class 0 OID 0)
-- Dependencies: 266
-- Name: sp_calctotobjoborot(character varying, character varying, integer, character varying, character varying); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_calctotobjoborot(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_calctotobjoborot(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) FROM sa;
GRANT ALL ON FUNCTION sp_calctotobjoborot(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) TO sa;
GRANT ALL ON FUNCTION sp_calctotobjoborot(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) TO bookkeeper;


--
-- TOC entry 3139 (class 0 OID 0)
-- Dependencies: 265
-- Name: sp_deletedoc(integer); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_deletedoc(ndocid integer) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_deletedoc(ndocid integer) FROM sa;
GRANT ALL ON FUNCTION sp_deletedoc(ndocid integer) TO sa;
GRANT ALL ON FUNCTION sp_deletedoc(ndocid integer) TO bookkeeper;


--
-- TOC entry 3140 (class 0 OID 0)
-- Dependencies: 283
-- Name: sp_deletedocstr(integer, integer); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_deletedocstr(ndocid integer, ndocstr integer) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_deletedocstr(ndocid integer, ndocstr integer) FROM sa;
GRANT ALL ON FUNCTION sp_deletedocstr(ndocid integer, ndocstr integer) TO sa;
GRANT ALL ON FUNCTION sp_deletedocstr(ndocid integer, ndocstr integer) TO bookkeeper;


--
-- TOC entry 3141 (class 0 OID 0)
-- Dependencies: 267
-- Name: sp_insertdoc(integer, character varying); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_insertdoc(noper integer, cdate character varying) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_insertdoc(noper integer, cdate character varying) FROM sa;
GRANT ALL ON FUNCTION sp_insertdoc(noper integer, cdate character varying) TO sa;
GRANT ALL ON FUNCTION sp_insertdoc(noper integer, cdate character varying) TO bookkeeper;


--
-- TOC entry 3142 (class 0 OID 0)
-- Dependencies: 282
-- Name: sp_insertdocstr(integer, integer, character varying, integer, integer); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_insertdocstr(noper integer, ndocid integer, pcparam character varying, pncount integer, pndocstr integer) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_insertdocstr(noper integer, ndocid integer, pcparam character varying, pncount integer, pndocstr integer) FROM sa;
GRANT ALL ON FUNCTION sp_insertdocstr(noper integer, ndocid integer, pcparam character varying, pncount integer, pndocstr integer) TO sa;
GRANT ALL ON FUNCTION sp_insertdocstr(noper integer, ndocid integer, pcparam character varying, pncount integer, pndocstr integer) TO bookkeeper;


--
-- TOC entry 3143 (class 0 OID 0)
-- Dependencies: 280
-- Name: sp_islockedperiod(character varying); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_islockedperiod(cdate character varying) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_islockedperiod(cdate character varying) FROM sa;
GRANT ALL ON FUNCTION sp_islockedperiod(cdate character varying) TO sa;
GRANT ALL ON FUNCTION sp_islockedperiod(cdate character varying) TO bookkeeper;


--
-- TOC entry 3144 (class 0 OID 0)
-- Dependencies: 281
-- Name: sp_maketotobjoborotcommand(character varying, character varying, integer, character varying, character varying); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_maketotobjoborotcommand(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_maketotobjoborotcommand(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) FROM sa;
GRANT ALL ON FUNCTION sp_maketotobjoborotcommand(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) TO sa;
GRANT ALL ON FUNCTION sp_maketotobjoborotcommand(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) TO bookkeeper;


--
-- TOC entry 3145 (class 0 OID 0)
-- Dependencies: 167
-- Name: сальдо; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "сальдо" FROM PUBLIC;
REVOKE ALL ON TABLE "сальдо" FROM sa;
GRANT ALL ON TABLE "сальдо" TO sa;
GRANT SELECT,INSERT,UPDATE ON TABLE "сальдо" TO bookkeeper;


--
-- TOC entry 3146 (class 0 OID 0)
-- Dependencies: 168
-- Name: счета; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "счета" FROM PUBLIC;
REVOKE ALL ON TABLE "счета" FROM sa;
GRANT ALL ON TABLE "счета" TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "счета" TO bookkeeper;


--
-- TOC entry 3147 (class 0 OID 0)
-- Dependencies: 169
-- Name: vw_баланс; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_баланс" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_баланс" FROM sa;
GRANT ALL ON TABLE "vw_баланс" TO sa;
GRANT SELECT ON TABLE "vw_баланс" TO bookkeeper;


--
-- TOC entry 3148 (class 0 OID 0)
-- Dependencies: 170
-- Name: блокпериоды; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "блокпериоды" FROM PUBLIC;
REVOKE ALL ON TABLE "блокпериоды" FROM sa;
GRANT ALL ON TABLE "блокпериоды" TO sa;
GRANT SELECT,UPDATE ON TABLE "блокпериоды" TO bookkeeper;


--
-- TOC entry 3149 (class 0 OID 0)
-- Dependencies: 171
-- Name: vw_блокпериоды; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_блокпериоды" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_блокпериоды" FROM sa;
GRANT ALL ON TABLE "vw_блокпериоды" TO sa;
GRANT SELECT ON TABLE "vw_блокпериоды" TO bookkeeper;


--
-- TOC entry 3150 (class 0 OID 0)
-- Dependencies: 172
-- Name: контрагенты; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "контрагенты" FROM PUBLIC;
REVOKE ALL ON TABLE "контрагенты" FROM sa;
GRANT ALL ON TABLE "контрагенты" TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "контрагенты" TO bookkeeper;


--
-- TOC entry 3151 (class 0 OID 0)
-- Dependencies: 173
-- Name: vw_грузополучатели; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_грузополучатели" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_грузополучатели" FROM sa;
GRANT ALL ON TABLE "vw_грузополучатели" TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "vw_грузополучатели" TO bookkeeper;


--
-- TOC entry 3152 (class 0 OID 0)
-- Dependencies: 174
-- Name: документы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "документы" FROM PUBLIC;
REVOKE ALL ON TABLE "документы" FROM sa;
GRANT ALL ON TABLE "документы" TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "документы" TO bookkeeper;


--
-- TOC entry 3153 (class 0 OID 0)
-- Dependencies: 176
-- Name: vw_пользователи; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_пользователи" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_пользователи" FROM sa;
GRANT ALL ON TABLE "vw_пользователи" TO sa;
GRANT SELECT ON TABLE "vw_пользователи" TO test;


--
-- TOC entry 3154 (class 0 OID 0)
-- Dependencies: 177
-- Name: доступ; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "доступ" FROM PUBLIC;
REVOKE ALL ON TABLE "доступ" FROM sa;
GRANT ALL ON TABLE "доступ" TO sa;


--
-- TOC entry 3155 (class 0 OID 0)
-- Dependencies: 179
-- Name: vw_доступ_к_оборотам; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_доступ_к_оборотам" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_доступ_к_оборотам" FROM sa;
GRANT ALL ON TABLE "vw_доступ_к_оборотам" TO sa;
GRANT SELECT ON TABLE "vw_доступ_к_оборотам" TO PUBLIC;


--
-- TOC entry 3156 (class 0 OID 0)
-- Dependencies: 180
-- Name: vw_доступ_к_сальдо; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_доступ_к_сальдо" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_доступ_к_сальдо" FROM sa;
GRANT ALL ON TABLE "vw_доступ_к_сальдо" TO sa;
GRANT SELECT ON TABLE "vw_доступ_к_сальдо" TO PUBLIC;


--
-- TOC entry 3157 (class 0 OID 0)
-- Dependencies: 181
-- Name: справочники; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "справочники" FROM PUBLIC;
REVOKE ALL ON TABLE "справочники" FROM sa;
GRANT ALL ON TABLE "справочники" TO sa;
GRANT SELECT ON TABLE "справочники" TO bookkeeper;


--
-- TOC entry 3158 (class 0 OID 0)
-- Dependencies: 182
-- Name: vw_доступ_к_справочникам; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_доступ_к_справочникам" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_доступ_к_справочникам" FROM sa;
GRANT ALL ON TABLE "vw_доступ_к_справочникам" TO sa;
GRANT SELECT ON TABLE "vw_доступ_к_справочникам" TO PUBLIC;


--
-- TOC entry 3159 (class 0 OID 0)
-- Dependencies: 183
-- Name: топер; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "топер" FROM PUBLIC;
REVOKE ALL ON TABLE "топер" FROM sa;
GRANT ALL ON TABLE "топер" TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "топер" TO bookkeeper;


--
-- TOC entry 3160 (class 0 OID 0)
-- Dependencies: 184
-- Name: vw_доступ_к_топер; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_доступ_к_топер" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_доступ_к_топер" FROM sa;
GRANT ALL ON TABLE "vw_доступ_к_топер" TO sa;
GRANT SELECT ON TABLE "vw_доступ_к_топер" TO PUBLIC;


--
-- TOC entry 3161 (class 0 OID 0)
-- Dependencies: 186
-- Name: vw_журнал; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_журнал" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_журнал" FROM sa;
GRANT ALL ON TABLE "vw_журнал" TO sa;


--
-- TOC entry 3162 (class 0 OID 0)
-- Dependencies: 187
-- Name: константы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "константы" FROM PUBLIC;
REVOKE ALL ON TABLE "константы" FROM sa;
GRANT ALL ON TABLE "константы" TO sa;


--
-- TOC entry 3163 (class 0 OID 0)
-- Dependencies: 188
-- Name: vw_константы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_константы" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_константы" FROM sa;
GRANT ALL ON TABLE "vw_константы" TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "vw_константы" TO seller;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "vw_константы" TO bookkeeper;


--
-- TOC entry 3164 (class 0 OID 0)
-- Dependencies: 189
-- Name: vw_контрагенты; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_контрагенты" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_контрагенты" FROM sa;
GRANT ALL ON TABLE "vw_контрагенты" TO sa;
GRANT ALL ON TABLE "vw_контрагенты" TO bookkeeper;


--
-- TOC entry 3165 (class 0 OID 0)
-- Dependencies: 190
-- Name: материалы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "материалы" FROM PUBLIC;
REVOKE ALL ON TABLE "материалы" FROM sa;
GRANT ALL ON TABLE "материалы" TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "материалы" TO bookkeeper;


--
-- TOC entry 3166 (class 0 OID 0)
-- Dependencies: 191
-- Name: vw_материалы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_материалы" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_материалы" FROM sa;
GRANT ALL ON TABLE "vw_материалы" TO sa;
GRANT ALL ON TABLE "vw_материалы" TO bookkeeper;


--
-- TOC entry 3167 (class 0 OID 0)
-- Dependencies: 192
-- Name: номенклатура; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "номенклатура" FROM PUBLIC;
REVOKE ALL ON TABLE "номенклатура" FROM sa;
GRANT ALL ON TABLE "номенклатура" TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "номенклатура" TO bookkeeper;


--
-- TOC entry 3168 (class 0 OID 0)
-- Dependencies: 193
-- Name: vw_номенклатура; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_номенклатура" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_номенклатура" FROM sa;
GRANT ALL ON TABLE "vw_номенклатура" TO sa;
GRANT ALL ON TABLE "vw_номенклатура" TO bookkeeper;


--
-- TOC entry 3169 (class 0 OID 0)
-- Dependencies: 194
-- Name: проводки; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "проводки" FROM PUBLIC;
REVOKE ALL ON TABLE "проводки" FROM sa;
GRANT ALL ON TABLE "проводки" TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "проводки" TO bookkeeper;


--
-- TOC entry 3170 (class 0 OID 0)
-- Dependencies: 196
-- Name: vw_справочники_со_столбцами; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_справочники_со_столбцами" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_справочники_со_столбцами" FROM sa;
GRANT ALL ON TABLE "vw_справочники_со_столбцами" TO sa;
GRANT SELECT ON TABLE "vw_справочники_со_столбцами" TO bookkeeper;


--
-- TOC entry 3171 (class 0 OID 0)
-- Dependencies: 197
-- Name: столбцы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "столбцы" FROM PUBLIC;
REVOKE ALL ON TABLE "столбцы" FROM sa;
GRANT ALL ON TABLE "столбцы" TO sa;
GRANT SELECT ON TABLE "столбцы" TO bookkeeper;


--
-- TOC entry 3172 (class 0 OID 0)
-- Dependencies: 198
-- Name: vw_счета; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_счета" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_счета" FROM sa;
GRANT ALL ON TABLE "vw_счета" TO sa;
GRANT SELECT ON TABLE "vw_счета" TO bookkeeper;


--
-- TOC entry 3173 (class 0 OID 0)
-- Dependencies: 199
-- Name: vw_топер; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_топер" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_топер" FROM sa;
GRANT ALL ON TABLE "vw_топер" TO sa;
GRANT SELECT ON TABLE "vw_топер" TO bookkeeper;


--
-- TOC entry 3174 (class 0 OID 0)
-- Dependencies: 200
-- Name: адрес; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "адрес" FROM PUBLIC;
REVOKE ALL ON TABLE "адрес" FROM sa;
GRANT ALL ON TABLE "адрес" TO sa;


--
-- TOC entry 3177 (class 0 OID 0)
-- Dependencies: 249
-- Name: атрибуты1; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "атрибуты1" FROM PUBLIC;
REVOKE ALL ON TABLE "атрибуты1" FROM sa;
GRANT ALL ON TABLE "атрибуты1" TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "атрибуты1" TO bookkeeper;


--
-- TOC entry 3180 (class 0 OID 0)
-- Dependencies: 245
-- Name: атрибуты3; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "атрибуты3" FROM PUBLIC;
REVOKE ALL ON TABLE "атрибуты3" FROM sa;
GRANT ALL ON TABLE "атрибуты3" TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "атрибуты3" TO bookkeeper;


--
-- TOC entry 3183 (class 0 OID 0)
-- Dependencies: 247
-- Name: атрибуты6; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "атрибуты6" FROM PUBLIC;
REVOKE ALL ON TABLE "атрибуты6" FROM sa;
GRANT ALL ON TABLE "атрибуты6" TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "атрибуты6" TO bookkeeper;


--
-- TOC entry 3186 (class 0 OID 0)
-- Dependencies: 202
-- Name: банки; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "банки" FROM PUBLIC;
REVOKE ALL ON TABLE "банки" FROM sa;
GRANT ALL ON TABLE "банки" TO sa;
GRANT SELECT,INSERT,UPDATE ON TABLE "банки" TO bookkeeper;


--
-- TOC entry 3189 (class 0 OID 0)
-- Dependencies: 204
-- Name: банковские_счета; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "банковские_счета" FROM PUBLIC;
REVOKE ALL ON TABLE "банковские_счета" FROM sa;
GRANT ALL ON TABLE "банковские_счета" TO sa;
GRANT SELECT,INSERT,UPDATE ON TABLE "банковские_счета" TO bookkeeper;


--
-- TOC entry 3194 (class 0 OID 0)
-- Dependencies: 207
-- Name: виды_расходов; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "виды_расходов" FROM PUBLIC;
REVOKE ALL ON TABLE "виды_расходов" FROM sa;
GRANT ALL ON TABLE "виды_расходов" TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "виды_расходов" TO bookkeeper;


--
-- TOC entry 3205 (class 0 OID 0)
-- Dependencies: 242
-- Name: запросы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "запросы" FROM PUBLIC;
REVOKE ALL ON TABLE "запросы" FROM sa;
GRANT ALL ON TABLE "запросы" TO sa;
GRANT SELECT ON TABLE "запросы" TO PUBLIC;


--
-- TOC entry 3216 (class 0 OID 0)
-- Dependencies: 217
-- Name: набор1; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "набор1" FROM PUBLIC;
REVOKE ALL ON TABLE "набор1" FROM sa;
GRANT ALL ON TABLE "набор1" TO sa;


--
-- TOC entry 3219 (class 0 OID 0)
-- Dependencies: 251
-- Name: наценки; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "наценки" FROM PUBLIC;
REVOKE ALL ON TABLE "наценки" FROM sa;
GRANT ALL ON TABLE "наценки" TO sa;


--
-- TOC entry 3224 (class 0 OID 0)
-- Dependencies: 220
-- Name: нумераторы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "нумераторы" FROM PUBLIC;
REVOKE ALL ON TABLE "нумераторы" FROM sa;
GRANT ALL ON TABLE "нумераторы" TO sa;
GRANT SELECT,UPDATE ON TABLE "нумераторы" TO bookkeeper;


--
-- TOC entry 3227 (class 0 OID 0)
-- Dependencies: 222
-- Name: персонал; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "персонал" FROM PUBLIC;
REVOKE ALL ON TABLE "персонал" FROM sa;
GRANT ALL ON TABLE "персонал" TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "персонал" TO bookkeeper;


--
-- TOC entry 3230 (class 0 OID 0)
-- Dependencies: 224
-- Name: прайсы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "прайсы" FROM PUBLIC;
REVOKE ALL ON TABLE "прайсы" FROM sa;
GRANT ALL ON TABLE "прайсы" TO sa;
GRANT SELECT ON TABLE "прайсы" TO bookkeeper;


--
-- TOC entry 3233 (class 0 OID 0)
-- Dependencies: 226
-- Name: предметы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "предметы" FROM PUBLIC;
REVOKE ALL ON TABLE "предметы" FROM sa;
GRANT ALL ON TABLE "предметы" TO sa;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE "предметы" TO bookkeeper;


--
-- TOC entry 3244 (class 0 OID 0)
-- Dependencies: 232
-- Name: типыобъектов; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "типыобъектов" FROM PUBLIC;
REVOKE ALL ON TABLE "типыобъектов" FROM sa;
GRANT ALL ON TABLE "типыобъектов" TO sa;
GRANT SELECT ON TABLE "типыобъектов" TO test;
GRANT SELECT ON TABLE "типыобъектов" TO bookkeeper;


--
-- TOC entry 3249 (class 0 OID 0)
-- Dependencies: 235
-- Name: файлы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "файлы" FROM PUBLIC;
REVOKE ALL ON TABLE "файлы" FROM sa;
GRANT ALL ON TABLE "файлы" TO sa;
GRANT SELECT ON TABLE "файлы" TO PUBLIC;


--
-- TOC entry 3252 (class 0 OID 0)
-- Dependencies: 237
-- Name: фирмы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "фирмы" FROM PUBLIC;
REVOKE ALL ON TABLE "фирмы" FROM sa;
GRANT ALL ON TABLE "фирмы" TO sa;


-- Completed on 2012-09-29 20:30:53 MSK

--
-- PostgreSQL database dump complete
--

