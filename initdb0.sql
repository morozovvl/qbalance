--
-- PostgreSQL database dump
--

-- Dumped from database version 9.0.4
-- Dumped by pg_dump version 9.0.4
-- Started on 2013-08-20 23:39:19

SET statement_timeout = 0;
SET client_encoding = 'WIN1251';
SET standard_conforming_strings = off;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET escape_string_warning = off;

--
-- TOC entry 435 (class 2612 OID 11574)
-- Name: plpgsql; Type: PROCEDURAL LANGUAGE; Schema: -; Owner: postgres
--

CREATE OR REPLACE PROCEDURAL LANGUAGE plpgsql;


ALTER PROCEDURAL LANGUAGE plpgsql OWNER TO postgres;

SET search_path = public, pg_catalog;

--
-- TOC entry 329 (class 1247 OID 71790)
-- Dependencies: 6 1628
-- Name: sp_calcaccoborot_fret; Type: TYPE; Schema: public; Owner: sa
--

CREATE TYPE sp_calcaccoborot_fret AS (
	"ДАТА" date,
	"ОПЕРНОМЕР" integer,
	"ОПЕРИМЯ" character varying(100),
	"ДОККОД" integer,
	"ДОКУМЕНТ" character varying(20),
	"НОМЕР" character varying(10),
	"КОММЕНТАРИЙ" character varying(100),
	"СУММА" numeric(10,2),
	"ДБСЧЕТ" bpchar,
	"КРСЧЕТ" bpchar,
	"ДЕБЕТ" numeric(10,2),
	"КРЕДИТ" numeric(10,2),
	"СДЕБЕТ" character varying(15),
	"СКРЕДИТ" character varying(15)
);


ALTER TYPE public.sp_calcaccoborot_fret OWNER TO sa;

--
-- TOC entry 331 (class 1247 OID 71793)
-- Dependencies: 6 1629
-- Name: sp_calcobjoborot_fret; Type: TYPE; Schema: public; Owner: sa
--

CREATE TYPE sp_calcobjoborot_fret AS (
	"ДАТА" date,
	"ОПЕРНОМЕР" integer,
	"ОПЕРИМЯ" character varying(100),
	"ДОККОД" integer,
	"ДОКУМЕНТ" character varying(20),
	"НОМЕР" character varying(10),
	"СТР" integer,
	"КОММЕНТАРИЙ" character varying(100),
	"СУММА" numeric(10,2),
	"ДБСЧЕТ" character(5),
	"КРСЧЕТ" character(5),
	"ДБКОЛ" numeric(10,3),
	"ДЕБЕТ" numeric(10,2),
	"КРКОЛ" numeric(10,3),
	"КРЕДИТ" numeric(10,2),
	"СДБКОЛ" character varying(15),
	"СДЕБЕТ" character varying(15),
	"СКРКОЛ" character varying(15),
	"СКРЕДИТ" character varying(15)
);


ALTER TYPE public.sp_calcobjoborot_fret OWNER TO sa;

--
-- TOC entry 333 (class 1247 OID 71796)
-- Dependencies: 6 1630
-- Name: sp_calcoborot_fret; Type: TYPE; Schema: public; Owner: sa
--

CREATE TYPE sp_calcoborot_fret AS (
	"КОД" integer,
	"КОЛ" numeric(10,3),
	"САЛЬДО" numeric(10,2),
	"ДБКОЛ" numeric(10,3),
	"ДЕБЕТ" numeric(10,2),
	"КРКОЛ" numeric(10,3),
	"КРЕДИТ" numeric(10,2),
	"КОНКОЛ" numeric(10,3),
	"КОНСАЛЬДО" numeric(10,2),
	"cКОЛ" character varying(15),
	"cСАЛЬДО" character varying(15),
	"cДБКОЛ" character varying(15),
	"cДЕБЕТ" character varying(15),
	"cКРКОЛ" character varying(15),
	"cКРЕДИТ" character varying(15),
	"cКОНКОЛ" character varying(15),
	"cКОНСАЛЬДО" character varying(15)
);


ALTER TYPE public.sp_calcoborot_fret OWNER TO sa;

--
-- TOC entry 38 (class 1255 OID 71797)
-- Dependencies: 329 435 6
-- Name: sp_calcaccoborot(character, character varying, character varying); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION sp_calcaccoborot(cacc character DEFAULT '10'::bpchar, cdate1 character varying DEFAULT NULL::character varying, cdate2 character varying DEFAULT NULL::character varying) RETURNS SETOF sp_calcaccoborot_fret
    LANGUAGE plpgsql
    AS $$
DECLARE ret_row RECORD;
	dDate1 DATE;
	dDate2 DATE;
BEGIN
	IF cDate1 IS NULL THEN
		dDate1 := (SELECT НАЧАЛО FROM vw_блокпериоды);
	ELSE
		dDate1 := to_date(cDate1, 'DD.MM.YYYY');
	END IF;
	IF cDate2 IS NULL THEN
		dDate2 := (SELECT КОНЕЦ FROM vw_блокпериоды);
	ELSE
		dDate2 := to_date(cDate2, 'DD.MM.YYYY') + 1;
	END IF;
	RAISE NOTICE '%', dDate1;
	FOR ret_row IN
		SELECT dDate1 AS "ДАТА", 0::integer AS "ОПЕРНОМЕР", ''::VARCHAR(100) AS "ОПЕРИМЯ", 0::integer AS "ДОККОД", ''::VARCHAR(20) AS "ДОКУМЕНТ", ''::VARCHAR(10) AS "НОМЕР", ''::VARCHAR(100) AS "КОММЕНТАРИЙ", 0.0::numeric(10,2) AS "СУММА", 
       			''::char(5) AS "ДБСЧЕТ", ''::char(5) AS "КРСЧЕТ",
       			CASE
               			WHEN S."САЛЬДО" > 0 THEN S."САЛЬДО"
               			ELSE 0.0
               		END::numeric(10,2) AS "ДЕБЕТ",
       			CASE
                		WHEN S."САЛЬДО" < 0 THEN -S."САЛЬДО"
                		ELSE 0.0
                	END::numeric(10,2) AS "КРЕДИТ", ''::VARCHAR(15) AS "СДЕБЕТ", ''::VARCHAR(15) AS "СКРЕДИТ"
		FROM (SELECT (S."САЛЬДО" + P1."СУММА" - P2."СУММА") AS "САЛЬДО"
      	      	      FROM (SELECT "СЧЕТ", SUM(COALESCE("САЛЬДО", 0)) AS "САЛЬДО" 
		    	    FROM "сальдо" 
		    	    WHERE "СЧЕТ" = cAcc 
		    	    GROUP BY "СЧЕТ") S LEFT OUTER JOIN (SELECT P."ДБСЧЕТ", SUM(COALESCE(P."СУММА", 0)) AS "СУММА" 
                                		 	      FROM "проводки" P INNER JOIN "документы" D ON P."ДОККОД"=D."КОД" 
			                        	      WHERE P."ДБСЧЕТ" = cAcc AND D."ДАТА" < dDate1 
			         		      	      GROUP BY P."ДБСЧЕТ") P1 ON S."СЧЕТ" = P1."ДБСЧЕТ"
			             	     LEFT OUTER JOIN (SELECT P."КРСЧЕТ", SUM(COALESCE(P."СУММА", 0)) AS "СУММА" 
                                 			      FROM "проводки" P INNER JOIN "документы" D ON P."ДОККОД"=D."КОД" 
                                 		      	      WHERE P."КРСЧЕТ" = cAcc AND D."ДАТА" < dDate1
       			         		      	      GROUP BY P."КРСЧЕТ") P2 ON S."СЧЕТ" = P2."КРСЧЕТ"
		) S
		UNION
		SELECT D."ДАТА", D."ОПЕР" AS "ОПЕРНОМЕР", T."ИМЯ" AS "ОПЕРИМЯ", D."КОД", COALESCE(T."ОСНДОКУМЕНТ", '')::VARCHAR(20), D."НОМЕР", D."КОММЕНТАРИЙ", D."СУММА", cAcc AS "ДБСЧЕТ", P."КРСЧЕТ", SUM(COALESCE(P."СУММА", 0))::numeric(10,2) AS "ДБСУММА", 0::numeric(10,2) AS "КРСУММА", ''::VARCHAR(15) AS "CДЕБЕТ", ''::VARCHAR(15) AS "CКРЕДИТ"
		FROM "проводки" P INNER JOIN "документы" D ON P."ДОККОД"=D."КОД" 
                		INNER JOIN "топер" T ON P."ОПЕР" = T."ОПЕР" AND T."НОМЕР" = 1
		WHERE P."ДБСЧЕТ" = cAcc AND P."КРСЧЕТ" <> cAcc AND P."СУММА" <> 0 AND D."ДАТА" >= dDate1 AND D."ДАТА" < dDate2
		GROUP BY D."ДАТА", D."ОПЕР", T."ИМЯ", D."КОД", T."ОСНДОКУМЕНТ", D."НОМЕР", D."КОММЕНТАРИЙ", D."СУММА", P."КРСЧЕТ"
		UNION
		SELECT D."ДАТА", D."ОПЕР" AS "ОПЕРНОМЕР", T."ИМЯ" AS "ОПЕРИМЯ", D."КОД", COALESCE(T."ОСНДОКУМЕНТ", '')::VARCHAR(20), D."НОМЕР", D."КОММЕНТАРИЙ", D."СУММА", P."ДБСЧЕТ", cAcc AS "КРСЧЕТ", 0::numeric(10,2) AS "ДБСУММА", SUM(COALESCE(P."СУММА", 0))::numeric(10,2) AS "КРСУММА", ''::VARCHAR(15) AS "CДЕБЕТ", ''::VARCHAR(15) AS "CКРЕДИТ"
		FROM "проводки" P INNER JOIN "документы" D ON P."ДОККОД"=D."КОД" 
        		        INNER JOIN "топер" T ON P."ОПЕР" = T."ОПЕР" AND T."НОМЕР" = 1
		WHERE P."КРСЧЕТ" = cAcc AND P."ДБСЧЕТ" <> cAcc AND P."СУММА" <> 0 AND D."ДАТА" >= dDate1 AND D."ДАТА" < dDate2
		GROUP BY D."ДАТА", D."ОПЕР", T."ИМЯ", D."КОД", T."ОСНДОКУМЕНТ", D."НОМЕР", D."КОММЕНТАРИЙ", D."СУММА", P."ДБСЧЕТ"
		ORDER BY "ДАТА" LOOP

		RETURN NEXT ret_row;
	END LOOP;
	RETURN;
END;
$$;


ALTER FUNCTION public.sp_calcaccoborot(cacc character, cdate1 character varying, cdate2 character varying) OWNER TO sa;

--
-- TOC entry 18 (class 1255 OID 71798)
-- Dependencies: 6 435
-- Name: sp_calcdocoborot(character varying, character varying, character varying); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION sp_calcdocoborot(cacc character varying, cdate1 character varying, cdate2 character varying) RETURNS void
    LANGUAGE plpgsql
    AS $$
BEGIN
	SELECT to_date(cDate1, 'DD.MM.YYYY') AS ДАТА, NULL AS ОПЕРНОМЕР, '' AS ОПЕРИМЯ, '' AS ДОККОД, '' AS ДОКУМЕНТ, '' AS НОМЕР, '' AS КОММЕНТАРИЙ, 0 AS СУММА, '' AS ДБСЧЕТ, '' AS КРСЧЕТ,
       		ДЕБЕТ = CASE
               			WHEN S.САЛЬДО > 0 THEN S.САЛЬДО
               			ELSE 0
               		END,
       		КРЕДИТ = CASE
                		WHEN S.САЛЬДО < 0 THEN -S.САЛЬДО
                		ELSE 0
                	END, '             ' AS СДЕБЕТ, '             ' AS СКРЕДИТ
	FROM (SELECT (S.САЛЬДО + COALESCE(P1.СУММА, 0) - COALESCE(P2.СУММА, 0)) AS САЛЬДО 
       	      FROM (SELECT SUM(САЛЬДО) AS САЛЬДО 
		    FROM сальдо 
		    WHERE СЧЕТ = cAcc) S,
	           (SELECT SUM(COALESCE(P.СУММА, 0)) AS СУММА 
                    FROM проводки P INNER JOIN документы D ON P.ДОККОД=D.КОД 
                    WHERE P.ДБСЧЕТ = cAcc AND to_date(D.ДАТА, 'DD.MM.YYYY') < to_date(cDate1, 'DD.MM.YYYY')) P1,
                   (SELECT SUM(COALESCE(P.СУММА, 0)) AS СУММА 
                    FROM проводки P INNER JOIN документы D ON P.ДОККОД=D.КОД 
	            WHERE P.КРСЧЕТ = cAcc AND to_date(D.ДАТА, 'DD.MM.YYYY') < to_date(cDate1, 'DD.MM.YYYY')) P2
              ) S
	UNION
	SELECT D.ДАТА, D.ОПЕР AS ОПЕРНОМЕР, T.ИМЯ AS ОПЕРИМЯ, D.КОД, COALESCE(T.ОСНДОКУМЕНТ, ''), D.НОМЕР, D.КОММЕНТАРИЙ, D.СУММА, cAcc AS ДБСЧЕТ, P.КРСЧЕТ, SUM(COALESCE(P.СУММА, 0)) AS ДЕБЕТ, 0 AS КРЕДИТ, '             ', '             '
	FROM проводки P INNER JOIN документы D ON P.ДОККОД=D.КОД 
                        INNER JOIN топер T ON P.ОПЕР = T.ОПЕР AND T.НОМЕР = 1
	WHERE P.ДБСЧЕТ = cAcc AND (P.СУММА <> 0) AND (to_date(D.ДАТА, 'DD.MM.YYYY') >= to_date(cDate1, 'DD.MM.YYYY')) AND (to_date(D.ДАТА, 'DD.MM.YYYY') < to_date(cDate2, 'DD.MM.YYYY') + 1)
	GROUP BY D.ДАТА, D.ОПЕР, T.ИМЯ, D.КОД, T.ОСНДОКУМЕНТ, D.НОМЕР, D.КОММЕНТАРИЙ, D.СУММА, P.КРСЧЕТ
	UNION
	SELECT D.ДАТА, D.ОПЕР AS ОПЕРНОМЕР, T.ИМЯ AS ОПЕРИМЯ, D.КОД, COALESCE(T.ОСНДОКУМЕНТ, ''), D.НОМЕР, D.КОММЕНТАРИЙ, D.СУММА, P.ДБСЧЕТ, cAcc AS КРСЧЕТ, 0 AS ДЕБЕТ, SUM(COALESCE(P.СУММА, 0)) AS КРЕДИТ, '             ', '             '
	FROM проводки P INNER JOIN документы D ON P.ДОККОД=D.КОД 
                        INNER JOIN топер T ON P.ОПЕР = T.ОПЕР AND T.НОМЕР = 1
	WHERE P.КРСЧЕТ = cAcc AND (P.СУММА <> 0) AND (to_date(D.ДАТА, 'DD.MM.YYYY') >= to_date(cDate1, 'DD.MM.YYYY')) AND (to_date(D.ДАТА, 'DD.MM.YYYY') < to_date(cDate2, 'DD.MM.YYYY') + 1)
	GROUP BY D.ДАТА, D.ОПЕР, T.ИМЯ, D.КОД, T.ОСНДОКУМЕНТ, D.НОМЕР, D.КОММЕНТАРИЙ, D.СУММА, P.ДБСЧЕТ
	ORDER BY ДАТА;
END;
$$;


ALTER FUNCTION public.sp_calcdocoborot(cacc character varying, cdate1 character varying, cdate2 character varying) OWNER TO sa;

--
-- TOC entry 39 (class 1255 OID 71799)
-- Dependencies: 435 331 6
-- Name: sp_calcobjoborot(character varying, integer, character varying, character varying); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION sp_calcobjoborot(cacc character varying, pnobj integer, cdate1 character varying, cdate2 character varying) RETURNS SETOF sp_calcobjoborot_fret
    LANGUAGE plpgsql
    AS $$
DECLARE ret_row sp_calcobjoborot_fret%ROWTYPE;
	nObj INTEGER;
	dDate1 DATE;
	dDate2 DATE;
BEGIN
	dDate1 := to_date(cDate1, 'DD.MM.YYYY');
	dDate2 := to_date(cDate2, 'DD.MM.YYYY') + 1;
	nObj := COALESCE(pnObj, 0);
	IF (SELECT КОЛИЧЕСТВО FROM счета WHERE СЧЕТ = cAcc) = TRUE THEN		-- если для этого счета есть количественный учет, то в результат включим ссылку на номер строки в документе для облегчения поиска позиции
		FOR ret_row IN
			SELECT  dDate1 AS ДАТА, 0 AS ОПЕРНОМЕР, ''::VARCHAR(100) AS ОПЕРИМЯ, 0 AS ДОККОД, ''::VARCHAR(20) AS ДОКУМЕНТ, ''::VARCHAR(10) AS НОМЕР, 0 AS СТР, ''::VARCHAR(100) AS КОММЕНТАРИЙ, 0 AS СУММА, '' AS ДБСЧЕТ, '' AS КРСЧЕТ,
	       			CASE
             				WHEN S.КОЛ > 0 THEN S.КОЛ
		               		ELSE 0::NUMERIC(10, 3)
		               	END AS ДБКОЛ,
	       			CASE
             				WHEN S.САЛЬДО > 0 THEN S.САЛЬДО
		               		ELSE 0::NUMERIC(10, 2)
        	     		END AS ДЕБЕТ,
	       			CASE
             				WHEN S.КОЛ < 0 THEN -S.КОЛ
	               			ELSE 0::NUMERIC(10, 3)
	             		END AS КРКОЛ,
		       		CASE
             				WHEN S.САЛЬДО < 0 THEN -S.САЛЬДО
	                		ELSE 0::NUMERIC(10, 2)
             			END AS КРЕДИТ, ''::VARCHAR(15) AS СДБКОЛ, ''::VARCHAR(15) AS СКРКОЛ, ''::VARCHAR(15) AS СДЕБЕТ, ''::VARCHAR(15) AS СКРЕДИТ
			FROM (SELECT (S.КОЛ + P1.КОЛ - P2.КОЛ) AS КОЛ, (S.САЛЬДО + P1.СУММА - P2.СУММА) AS САЛЬДО 
			      FROM (SELECT КОД, КОЛ, САЛЬДО 
				    FROM сальдо 
				    WHERE СЧЕТ = cAcc AND КОД = nObj) S,
				   (SELECT SUM(P.КОЛ) AS КОЛ, SUM(P.СУММА) AS СУММА 
             		            FROM (SELECT p.КОД AS КОД, p.КОЛ, p.СУММА
					  FROM проводки P INNER JOIN (SELECT КОД 
								      FROM документы 
								      WHERE ДАТА < dDate1) D ON P.ДОККОД=D.КОД
	                            	  WHERE P.ДБСЧЕТ = cAcc AND P.ДБКОД = nObj
					  UNION
				    	  SELECT 0 AS КОД, 0 AS КОЛ, 0 AS СУММА) p) P1,
             			   (SELECT SUM(P.КОЛ) AS КОЛ, SUM(P.СУММА) AS СУММА 
                        	    FROM (SELECT p.КОД AS КОД, p.КОЛ, p.СУММА
					  FROM проводки P INNER JOIN (SELECT КОД 
								      FROM документы 
								      WHERE ДАТА < dDate1) D ON P.ДОККОД=D.КОД
					  WHERE P.КРСЧЕТ = cAcc AND P.КРКОД = nObj
					  UNION
					  SELECT 0 AS КОД, 0 AS КОЛ, 0 AS СУММА) p) P2
		              ) S
			UNION
			SELECT D.ДАТА, D.ОПЕР AS ОПЕРНОМЕР, T.ИМЯ AS ОПЕРИМЯ, D.КОД, T.ОСНДОКУМЕНТ AS ДОКУМЕНТ, D.НОМЕР, P.СТР, D.КОММЕНТАРИЙ, D.СУММА, cAcc AS ДБСЧЕТ, P.КРСЧЕТ, SUM(P.КОЛ) AS ДБКОЛ, SUM(P.СУММА) AS ДЕБЕТ, 0 AS КРКОЛ, 0 AS КРЕДИТ, '', '', '', ''
			FROM проводки P INNER JOIN документы D ON P.ДОККОД=D.КОД 
        	     		        INNER JOIN топер T ON P.ОПЕР = T.ОПЕР AND T.НОМЕР = 1
			WHERE P.ДБСЧЕТ = cAcc AND P.ДБКОД = nObj AND D.ДАТА >= dDate1 AND D.ДАТА < dDate2
			GROUP BY D.ДАТА, D.ОПЕР, T.ИМЯ, D.КОД, T.ОСНДОКУМЕНТ, D.НОМЕР, P.СТР, D.КОММЕНТАРИЙ, D.СУММА, P.КРСЧЕТ
			UNION
			SELECT D.ДАТА, D.ОПЕР AS ОПЕРНОМЕР, T.ИМЯ AS ОПЕРИМЯ, D.КОД, T.ОСНДОКУМЕНТ AS ДОКУМЕНТ, D.НОМЕР, P.СТР, D.КОММЕНТАРИЙ, D.СУММА, P.ДБСЧЕТ, cAcc AS КРСЧЕТ, 0 AS ДБКОЛ, 0 AS ДЕБЕТ, SUM(P.КОЛ) AS КРКОЛ, SUM(P.СУММА) AS КРЕДИТ, '', '', '', ''
			FROM проводки P INNER JOIN документы D ON P.ДОККОД=D.КОД 
             	        	        INNER JOIN топер T ON P.ОПЕР = T.ОПЕР AND T.НОМЕР = 1
			WHERE P.КРСЧЕТ = cAcc AND P.КРКОД = nObj AND D.ДАТА >= dDate1 AND D.ДАТА < dDate2
			GROUP BY D.ДАТА, D.ОПЕР, T.ИМЯ, D.КОД, T.ОСНДОКУМЕНТ, D.НОМЕР, P.СТР, D.КОММЕНТАРИЙ, D.СУММА, P.ДБСЧЕТ
			ORDER BY ДАТА, НОМЕР LOOP
			RETURN NEXT ret_row;
		END LOOP;
	ELSE
		FOR ret_row IN
			SELECT  dDate1 AS ДАТА, 0 AS ОПЕРНОМЕР, ''::VARCHAR(100) AS ОПЕРИМЯ, 0 AS ДОККОД, ''::VARCHAR(20) AS ДОКУМЕНТ, ''::VARCHAR(10) AS НОМЕР, 0 AS СТР, ''::VARCHAR(100) AS КОММЕНТАРИЙ, 0 AS СУММА, '' AS ДБСЧЕТ, '' AS КРСЧЕТ,
		       		CASE
             				WHEN S.КОЛ > 0 THEN S.КОЛ
	               			ELSE 0::NUMERIC(10, 3)
		               	END AS ДБКОЛ,
		       		CASE
             				WHEN S.САЛЬДО > 0 THEN S.САЛЬДО
	               			ELSE 0::NUMERIC(10, 2)
	             		END AS ДЕБЕТ,
		       		CASE
             				WHEN S.КОЛ < 0 THEN -S.КОЛ
	               			ELSE 0::NUMERIC(10, 3)
	             		END AS КРКОЛ,
		       		CASE
             				WHEN S.САЛЬДО < 0 THEN -S.САЛЬДО
	                		ELSE 0::NUMERIC(10, 2)
	             		END AS КРЕДИТ, ''::VARCHAR(15) AS СДБКОЛ, ''::VARCHAR(15) AS СКРКОЛ, ''::VARCHAR(15) AS СДЕБЕТ, ''::VARCHAR(15) AS СКРЕДИТ
			FROM (SELECT (S.КОЛ + P1.КОЛ - P2.КОЛ) AS КОЛ, (S.САЛЬДО + P1.СУММА - P2.СУММА) AS САЛЬДО 
			      FROM (SELECT КОД, КОЛ, САЛЬДО 
				    FROM сальдо 
				    WHERE СЧЕТ = cAcc AND КОД = nObj) S,
				   (SELECT SUM(P.КОЛ) AS КОЛ, SUM(P.СУММА) AS СУММА 
             		            FROM (SELECT p.КОД, p.КОЛ, p.СУММА
					  FROM проводки P INNER JOIN (SELECT КОД 
								      FROM документы 
								      WHERE ДАТА < dDate1) D ON P.ДОККОД=D.КОД
	                            	  WHERE P.ДБСЧЕТ = cAcc AND P.ДБКОД = nObj
					  UNION
				    	  SELECT 0 AS КОД, 0 AS КОЛ, 0 AS СУММА) p) P1,
             			   (SELECT SUM(P.КОЛ) AS КОЛ, SUM(P.СУММА) AS СУММА 
                        	    FROM (SELECT p.КОД, p.КОЛ, p.СУММА
					  FROM проводки P INNER JOIN (SELECT КОД 
								      FROM документы 
								      WHERE ДАТА < dDate1) D ON P.ДОККОД=D.КОД
					  WHERE P.КРСЧЕТ = cAcc AND P.КРКОД = nObj
					  UNION
					  SELECT 0 AS КОД, 0 AS КОЛ, 0 AS СУММА) p) P2
		              ) S
			UNION
			SELECT D.ДАТА, D.ОПЕР AS ОПЕРНОМЕР, T.ИМЯ AS ОПЕРИМЯ, D.КОД, T.ОСНДОКУМЕНТ AS ДОКУМЕНТ, D.НОМЕР, 0 AS СТР, D.КОММЕНТАРИЙ, D.СУММА, cAcc AS ДБСЧЕТ, P.КРСЧЕТ, SUM(P.КОЛ) AS ДБКОЛ, SUM(P.СУММА) AS ДЕБЕТ, 0 AS КРКОЛ, 0 AS КРЕДИТ, '', '', '', ''
			FROM проводки P INNER JOIN документы D ON P.ДОККОД=D.КОД
             	        	        INNER JOIN топер T ON P.ОПЕР = T.ОПЕР AND T.НОМЕР = 1
			WHERE P.ДБСЧЕТ = cAcc AND P.ДБКОД = nObj AND D.ДАТА >= dDate1 AND D.ДАТА < dDate2
			GROUP BY D.ДАТА, D.ОПЕР, T.ИМЯ, D.КОД, T.ОСНДОКУМЕНТ, D.НОМЕР, D.КОММЕНТАРИЙ, D.СУММА, p.КРСЧЕТ
			UNION
			SELECT D.ДАТА, D.ОПЕР AS ОПЕРНОМЕР, T.ИМЯ AS ОПЕРИМЯ, D.КОД, T.ОСНДОКУМЕНТ AS ДОКУМЕНТ, D.НОМЕР, 0 AS СТР, D.КОММЕНТАРИЙ, D.СУММА, P.ДБСЧЕТ, cAcc AS КРСЧЕТ, 0 AS ДБКОЛ, 0 AS ДЕБЕТ, SUM(P.КОЛ) AS КРКОЛ, SUM(P.СУММА) AS КРЕДИТ, '', '', '', ''
			FROM проводки P INNER JOIN документы D ON P.ДОККОД=D.КОД
             		                INNER JOIN топер T ON P.ОПЕР = T.ОПЕР AND T.НОМЕР = 1
			WHERE P.КРСЧЕТ = cAcc AND P.КРКОД = nObj AND D.ДАТА >= dDate1 AND D.ДАТА < dDate2
			GROUP BY D.ДАТА, D.ОПЕР, T.ИМЯ, D.КОД, T.ОСНДОКУМЕНТ, D.НОМЕР, D.КОММЕНТАРИЙ, D.СУММА, p.ДБСЧЕТ
			ORDER BY ДАТА, ОПЕРНОМЕР, НОМЕР LOOP
			RETURN NEXT ret_row;
		END LOOP;
	END IF;
END;
$$;


ALTER FUNCTION public.sp_calcobjoborot(cacc character varying, pnobj integer, cdate1 character varying, cdate2 character varying) OWNER TO sa;

--
-- TOC entry 20 (class 1255 OID 71800)
-- Dependencies: 6 435 333
-- Name: sp_calcoborot(character varying, character varying, character varying); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION sp_calcoborot(cacc character varying, cdate1 character varying, cdate2 character varying) RETURNS SETOF sp_calcoborot_fret
    LANGUAGE plpgsql
    AS $$
-- cComm1 - секция select команды
-- cComm2 - секция order команды
-- cAcc - бухгалтерский счет
-- dDate1 - начальная дата
-- dDate2 - конечная дата
DECLARE ret_row RECORD;
	dDate1 DATE;
	dDate2 DATE;
BEGIN
	dDate1 := to_date(cDate1, 'DD.MM.YYYY');
	dDate2 := to_date(cDate2, 'DD.MM.YYYY') + 1;
	
	FOR ret_row IN
		SELECT *
		FROM (SELECT S.КОД, COALESCE(S.КОЛ, 0)::NUMERIC(10, 3) AS КОЛ, COALESCE(S.САЛЬДО, 0)::NUMERIC(10, 2) AS САЛЬДО, COALESCE(P1.КОЛ, 0)::NUMERIC(10, 3) AS ДБКОЛ, COALESCE(P1.СУММА, 0)::NUMERIC(10, 2) AS ДЕБЕТ, COALESCE(P2.КОЛ, 0)::NUMERIC(10, 3) AS КРКОЛ, COALESCE(P2.СУММА, 0)::NUMERIC(10, 2) AS КРЕДИТ, (COALESCE(S.КОЛ, 0) + COALESCE(P1.КОЛ, 0) - COALESCE(P2.КОЛ, 0))::NUMERIC(10, 3) AS КОНКОЛ, (COALESCE(S.САЛЬДО, 0) + COALESCE(P1.СУММА, 0) - COALESCE(P2.СУММА, 0))::NUMERIC(10, 2) AS КОНСАЛЬДО, 
			''::VARCHAR(15) AS CКОЛ, ''::VARCHAR(15) AS CСАЛЬДО, ''::VARCHAR(15) AS CДБКОЛ, ''::VARCHAR(15) AS CДЕБЕТ, ''::VARCHAR(15) AS CКРКОЛ, ''::VARCHAR(15) AS CКРЕДИТ, ''::VARCHAR(15) AS CКОНКОЛ, ''::VARCHAR(15) AS CКОНСАЛЬДО
 		      FROM (SELECT S.КОД, (S.КОЛ + COALESCE(P1.КОЛ, 0) - COALESCE(P2.КОЛ, 0)) AS КОЛ, (S.САЛЬДО + COALESCE(P1.СУММА, 0) - COALESCE(P2.СУММА, 0)) AS САЛЬДО
                	    FROM (SELECT КОД, COALESCE(КОЛ, 0) AS КОЛ, САЛЬДО FROM сальдо WHERE СЧЕТ = cAcc
                    		 ) S LEFT JOIN (SELECT P.ДБКОД AS КОД, SUM(COALESCE(P.КОЛ, 0)) AS КОЛ, SUM(COALESCE(P.СУММА, 0)) AS СУММА
			        	   	FROM проводки P INNER JOIN (SELECT КОД FROM документы WHERE ДАТА < dDate1) D ON P.ДОККОД=D.КОД
					   	WHERE P.ДБСЧЕТ = cAcc
					   	GROUP BY P.ДБКОД) P1 ON S.КОД = P1.КОД
			             LEFT JOIN (SELECT P.КРКОД AS КОД, SUM(COALESCE(P.КОЛ, 0)) AS КОЛ, SUM(COALESCE(P.СУММА, 0)) AS СУММА
		        	           	FROM проводки P INNER JOIN (SELECT КОД FROM документы WHERE ДАТА < dDate1) D ON P.ДОККОД=D.КОД
			        	   	WHERE P.КРСЧЕТ = cAcc
		        	   		GROUP BY P.КРКОД) P2 ON S.КОД = P2.КОД
                    	    ) S LEFT JOIN (SELECT P.ДБКОД AS КОД, SUM(COALESCE(P.КОЛ, 0)) AS КОЛ, SUM(COALESCE(P.СУММА, 0)) AS СУММА
                         		   FROM проводки P INNER JOIN (SELECT КОД FROM документы WHERE ДАТА >= dDate1 AND ДАТА < dDate2) D ON P.ДОККОД=D.КОД
                                	   WHERE P.ДБСЧЕТ = cAcc
                            		   GROUP BY P.ДБКОД
	                           	  ) P1 ON S.КОД = P1.КОД
        	        	LEFT JOIN (SELECT P.КРКОД AS КОД, SUM(COALESCE(P.КОЛ, 0)) AS КОЛ, SUM(COALESCE(P.СУММА, 0)) AS СУММА
					   FROM проводки P INNER JOIN (SELECT КОД FROM документы WHERE ДАТА >= dDate1 AND ДАТА < dDate2) D ON P.ДОККОД=D.КОД
                        	   	   WHERE P.КРСЧЕТ = cAcc
                                   	   GROUP BY P.КРКОД
                                   	   ) P2 ON S.КОД = P2.КОД
      	     	) S
		WHERE КОЛ <> 0 OR САЛЬДО <> 0 OR ДБКОЛ <> 0 OR ДЕБЕТ <> 0 OR КРКОЛ <> 0 OR КРЕДИТ <> 0 OR КОНКОЛ <> 0 OR КОНСАЛЬДО <> 0 
		LOOP
		RETURN NEXT ret_row;
	END LOOP;
END;
$$;


ALTER FUNCTION public.sp_calcoborot(cacc character varying, cdate1 character varying, cdate2 character varying) OWNER TO sa;

--
-- TOC entry 32 (class 1255 OID 71801)
-- Dependencies: 435 6
-- Name: sp_calctotobjoborot(character varying, character varying, integer, character varying, character varying); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION sp_calctotobjoborot(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) RETURNS void
    LANGUAGE plpgsql
    AS $$
DECLARE cSetName VARCHAR(50);
	cCommand VARCHAR(8000);
	cDictName VARCHAR (50);
	nObj INTEGER;
BEGIN
	cDictName := UPPER(pcDictName);
	nObj = COALESCE(pnObj, 0);
	cSetName = (SELECT ИМЯСПРАВОЧНИКА FROM счета WHERE СЧЕТ = cAcc);
	cSetName = RTRIM(cSetName);

	IF (SELECT COUNT(*) FROM vw_columns WHERE ТАБЛИЦА = cSetName AND СТОЛБЕЦ = 'КОД') = 1			-- Если есть одно поле код
		AND (SELECT COUNT(*) FROM vw_columns WHERE ТАБЛИЦА = cSetName AND СТОЛБЕЦ = 'ИМЯ') = 1	THEN 	-- и одно поле имя
		-- Мы определили, что код объекта определяется справочником, поэтому информацию об объекте можно
		-- Собрать напрямую
		SELECT sp_CalcObjOborot(cAcc, nObj, cDate1, cDate2);
	ELSE
		-- Мы определили, что код объекта определяется набором справочников
		IF (SELECT COUNT(*) FROM vw_columns WHERE ТАБЛИЦА = cSetName AND СТОЛБЕЦ = 'КОД') = 1				-- Если есть одно поле код
		AND (SELECT COUNT(*) FROM vw_columns WHERE ТАБЛИЦА = cSetName AND СТОЛБЕЦ = 'КОД_' + cDictName) = 1 THEN	-- и одно поле со ссылкой на справочник
			SELECT sp_MakeTotObjOborotCommand(cAcc, cDictName, nObj, cDate1, cDate2) INTO cCommand;
			EXECUTE cCommand;
		END IF;
	END IF;
END;
$$;


ALTER FUNCTION public.sp_calctotobjoborot(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) OWNER TO sa;

--
-- TOC entry 22 (class 1255 OID 71802)
-- Dependencies: 6 435
-- Name: sp_deletedoc(integer); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION sp_deletedoc(ndocid integer) RETURNS void
    LANGUAGE plpgsql
    AS $_$
DECLARE
	nOperNum INTEGER;
	cAttrName VARCHAR (50);
BEGIN
	nOperNum := (SELECT "ОПЕР" FROM "документы" WHERE "КОД" = ndocid LIMIT 1);
	DELETE FROM "документы" WHERE "КОД" = nDocId;
	DELETE FROM "проводки" WHERE "ДОККОД" = nDocId;
	cAttrName = 'атрибуты' || rtrim(ltrim(cast(nOperNum AS VARCHAR(10))));
	IF (SELECT COUNT(*) FROM pg_tables WHERE schemaname='public' AND tablename = cAttrName) > 0 THEN
		EXECUTE 'DELETE FROM ' || cAttrName || ' WHERE "ДОККОД"=$1;' USING ndocid;
	END IF;
	cAttrName = 'докатрибуты' || rtrim(ltrim(cast(nOperNum AS VARCHAR(10))));
	IF (SELECT COUNT(*) FROM pg_tables WHERE schemaname='public' AND tablename = cAttrName) > 0 THEN
		EXECUTE 'DELETE FROM ' || cAttrName || ' WHERE "КОД"=$1;' USING ndocid;
	END IF;
END;
$_$;


ALTER FUNCTION public.sp_deletedoc(ndocid integer) OWNER TO sa;

--
-- TOC entry 21 (class 1255 OID 71803)
-- Dependencies: 435 6
-- Name: sp_deletedocstr(integer, integer); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION sp_deletedocstr(ndocid integer, ndocstr integer) RETURNS void
    LANGUAGE plpgsql
    AS $$
DECLARE 
	nOper INTEGER;
	nFreeOper INTEGER;
	nNewDocStr INTEGER;
	cDbAcc VARCHAR(5);
	cCrAcc VARCHAR(5);
BEGIN
	nOper := (SELECT "ОПЕР" FROM "документы" WHERE "КОД" = nDocId);
	nFreeOper := (SELECT "НОМЕР" FROM "топер" WHERE "ОПЕР" = nOper AND "НЕЗАВИСИМ" = true);
	IF nFreeOper IS NOT NULL THEN
		IF (SELECT "СТР" FROM "проводки" WHERE "ДОККОД" = nDocId AND "НОМЕРОПЕР" = nFreeOper LIMIT 1) = nDocStr THEN
			nNewDocStr := (SELECT MIN("СТР") FROM "проводки" WHERE "ДОККОД" = nDocId AND "ОПЕР" = nOper AND "СТР" <> nDocStr);
			IF nNewDocStr IS NOT NULL AND nNewDocStr <> nDocStr THEN
				cDbAcc := (SELECT "ДБСЧЕТ" FROM "топер" WHERE "ОПЕР" = nOper AND "НЕЗАВИСИМ" = true);			
				cCrAcc := (SELECT "КРСЧЕТ" FROM "топер" WHERE "ОПЕР" = nOper AND "НЕЗАВИСИМ" = true);			
				INSERT INTO "проводки" ("ДОККОД", "СТР", "ОПЕР", "НОМЕРОПЕР", "ДБСЧЕТ", "ДБКОД", "КРСЧЕТ", "КРКОД") 
					VALUES (nDocId, nNewDocStr, nOper, nFreeOper, cDbAcc, 0, cCrAcc, 0);
			END IF;
	
		END IF;
	END IF;
	DELETE FROM "проводки" WHERE "ДОККОД" = nDocId AND "СТР" = nDocStr;
END;
$$;


ALTER FUNCTION public.sp_deletedocstr(ndocid integer, ndocstr integer) OWNER TO sa;

--
-- TOC entry 40 (class 1255 OID 71804)
-- Dependencies: 435 6
-- Name: sp_insertdoc(integer, character varying); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION sp_insertdoc(noper integer, cdate character varying) RETURNS integer
    LANGUAGE plpgsql
    AS $_$
DECLARE 
cNumName "нумераторы"."ИМЯ"%TYPE;		-- Наименование нумератора
	nValue "нумераторы"."ЗНАЧЕНИЕ"%TYPE;	-- Значение нумератора
	dDate DATE;				-- Дата документа
	nDocId "документы"."КОД"%TYPE;
	cNumber "документы"."НОМЕР"%TYPE;			
BEGIN
	cNumName := RTRIM((SELECT "НУМЕРАТОР" FROM "топер" WHERE "ОПЕР" = nOper AND "НОМЕР" = 1 LIMIT 1));	-- Загрузим наименование нумератора
	IF cNumName IS NOT NULL AND char_length(cNumName) > 0 THEN
		nValue := (SELECT "ЗНАЧЕНИЕ" FROM "нумераторы" WHERE RTRIM("ИМЯ") = cNumName LIMIT 1);	-- Получим новое значение нумератора
		nValue := nValue + 1;
		UPDATE "нумераторы" SET "ЗНАЧЕНИЕ" = nValue WHERE RTRIM("ИМЯ") = cNumName;		-- Сохраним новое значение нумератора
		cNumber := trim(leading from to_char(nValue, '999999999'));
	ELSE
		cNumber := '';
	END IF;
	IF cDate IS NULL THEN
		dDate = CURRENT_DATE;
	ELSE
		dDate = to_date(cDate, 'DD.MM.YYYY');
	END IF;
	INSERT INTO "документы" ("ДАТА", "ДАТАВРЕМЯ", "ОПЕР", "НОМЕР", "АВТО") VALUES (dDate, current_timestamp, nOper, cNumber, 0) RETURNING "КОД" INTO nDocId;
	IF (SELECT COUNT(*) FROM "топер" WHERE "ОПЕР" = nOper AND "ДОКАТРИБУТЫ" = TRUE) > 0 THEN
		EXECUTE 'INSERT INTO "докатрибуты' || rtrim(ltrim(cast(nOper AS VARCHAR(10)))) || '" ("КОД") VALUES ($1);' USING nDocId;
	END IF;
	RETURN nDocId;
END;
$_$;


ALTER FUNCTION public.sp_insertdoc(noper integer, cdate character varying) OWNER TO sa;

--
-- TOC entry 41 (class 1255 OID 71805)
-- Dependencies: 435 6
-- Name: sp_insertdocstr(integer, integer, character varying, integer, integer); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION sp_insertdocstr(noper integer, ndocid integer, pcparam character varying, pncount integer, pndocstr integer) RETURNS integer
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
	nCount1 INTEGER;
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
	IF (SELECT COUNT(*) FROM "топер" WHERE "ОПЕР" = noper AND "НОМЕР" = 0 AND "АТРИБУТЫ" = TRUE) > 0 THEN
		EXECUTE 'SELECT max("СТР") FROM "атрибуты' || rtrim(ltrim(cast(noper AS VARCHAR(10)))) || '"' INTO nDocStr;
		IF nDocStr IS NULL THEN
			nDocStr := 1;
		ELSE
			nDocStr := nDocStr + 1;
		END IF;
		WHILE nCount > 0 LOOP
			-- Проверим, не использует ли документ таблицу атрибутов, и если использует, то добавим строку в таблицу атрибутов
			EXECUTE 'SELECT COUNT(*) FROM "атрибуты' || rtrim(ltrim(cast(noper AS VARCHAR(10)))) || '" WHERE "ДОККОД" = $1 AND "СТР" = $2;' INTO nCount1 USING nDocId, nDocStr;
			IF nCount1 = 0 THEN
				EXECUTE 'INSERT INTO "атрибуты' || rtrim(ltrim(cast(noper AS VARCHAR(10)))) || '" ("ДОККОД", "СТР") VALUES ($1, $2);' USING nDocId, nDocStr;
			END IF;
			nCount := nCount - 1;
		END LOOP;
	ELSE
		IF nDocStr IS NULL OR nDocStr = 0 THEN
			-- найдем наибольший "НОМЕР" строки в документе
			nDocStr := (SELECT max(p."СТР") AS max_value FROM "проводки" p WHERE p."ДОККОД" = nDocId AND p."ОПЕР" = noper);
			IF nDocStr IS NULL THEN
				nDocStr := 1;
			ELSE
				nDocStr := nDocStr + 1;
			END IF;
		END IF;
		-- вставим в документ проводки для новой строки
		OPEN curResult FOR SELECT "ДБСЧЕТ", "КРСЧЕТ", "НОМЕР", "НЕЗАВИСИМ"  FROM "топер" WHERE "ОПЕР" = noper ORDER BY "НОМЕР";
		WHILE nCount > 0 LOOP
			-- Проверим, не использует ли документ таблицу атрибутов, и если использует, то добавим строку в таблицу атрибутов
			IF (SELECT COUNT(*) FROM "топер" WHERE "ОПЕР" = noper AND "НОМЕР" = 1 AND "АТРИБУТЫ" = TRUE) > 0 THEN
				EXECUTE 'INSERT INTO "атрибуты' || rtrim(ltrim(cast(noper AS VARCHAR(10)))) || '" ("ДОККОД", "СТР") VALUES ($1, $2);' USING nDocId, nDocStr;
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
					nFreeCount := (SELECT count(*) FROM "проводки" p WHERE p."ДОККОД" = nDocId AND p."ОПЕР" = noper AND p."НОМЕРОПЕР" = nNum);
					IF nFreeCount = 0 THEN
						INSERT INTO "проводки" ("ДОККОД", "СТР", "ОПЕР", "НОМЕРОПЕР", "ДБСЧЕТ", "ДБКОД", "КРСЧЕТ", "КРКОД", "КОЛ", "ЦЕНА", "СУММА") VALUES (nDocId, nDocStr, noper, nNum, cDbAcc, nDbId, cCrAcc, nCrId, nQuan, nPrice, nSum);
					END IF;
				ELSE
					INSERT INTO "проводки" ("ДОККОД", "СТР", "ОПЕР", "НОМЕРОПЕР", "ДБСЧЕТ", "ДБКОД", "КРСЧЕТ", "КРКОД", "КОЛ", "ЦЕНА", "СУММА") VALUES (nDocId, nDocStr, noper, nNum, cDbAcc, nDbId, cCrAcc, nCrId, nQuan, nPrice, nSum);
				END IF;
				FETCH NEXT FROM curResult INTO cDbAcc, cCrAcc, nNum, bFreePrv;
			END LOOP;
			nCount := nCount - 1;
			nDocStr := nDocStr + 1;
		END LOOP;
		nDocStr := nDocStr - 1;
		CLOSE curResult;
	END IF;
	RETURN nDocStr;
END;
$_$;


ALTER FUNCTION public.sp_insertdocstr(noper integer, ndocid integer, pcparam character varying, pncount integer, pndocstr integer) OWNER TO sa;

--
-- TOC entry 25 (class 1255 OID 71806)
-- Dependencies: 435 6
-- Name: sp_maketotobjoborotcommand(character varying, character varying, integer, character varying, character varying); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION sp_maketotobjoborotcommand(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) RETURNS character varying
    LANGUAGE plpgsql
    AS $$
DECLARE cSetName VARCHAR(50);
	cCommand VARCHAR(8000);
	cDictName VARCHAR (50);
	nObj INTEGER;
BEGIN
	cDictName = UPPER(pcDictName);
	nObj = COALESCE(pnObj, 0);
	cSetName = (SELECT ИМЯСПРАВОЧНИКА FROM счета WHERE СЧЕТ = cAcc);
	cSetName = RTRIM(cSetName);

	cCommand = 'SELECT КОД FROM ' || cSetName || ' WHERE КОД_' || cDictName || '=' || RTRIM(LTRIM(CAST(nObj AS VARCHAR(20))));
	cCommand = 'SELECT ДАТА, ОПЕРНОМЕР, ОПЕРИМЯ, ДБСЧЕТ, КРСЧЕТ, SUM(ДБКОЛ) AS ДБКОЛ, SUM(ДЕБЕТ) AS ДЕБЕТ, SUM(КРКОЛ) AS КРКОЛ, SUM(КРЕДИТ) AS КРЕДИТ '
		 || 'FROM (SELECT to_date("' || cDate1 || '", "DD.MM.YYYY") AS ДАТА, 0 AS ОПЕРНОМЕР, "" AS ОПЕРИМЯ, "" AS ДБСЧЕТ, "" AS КРСЧЕТ, '
			       || 'ДБКОЛ = CASE '
			               || 'WHEN S.КОЛ > 0 THEN S.КОЛ '
	        		       || 'ELSE 0 '
			               || 'END, '
			       || 'ДЕБЕТ = CASE '
        			       || 'WHEN S.САЛЬДО > 0 THEN S.САЛЬДО '
			               || 'ELSE 0 '
			               || 'END, '
			       || 'КРКОЛ = CASE '
			               || 'WHEN S.КОЛ < 0 THEN -S.КОЛ '
        			       || 'ELSE 0 '
			               || 'END, '
			       || 'КРЕДИТ = CASE '
	        		        || 'WHEN S.САЛЬДО < 0 THEN -S.САЛЬДО '
			                || 'ELSE 0 '
			                || 'END '
			 || 'FROM (SELECT (S.КОЛ + COALESCE(P1.КОЛ, 0) - COALESCE(P2.КОЛ, 0)) AS КОЛ, (S.САЛЬДО + COALESCE(P1.СУММА, 0) - COALESCE(P2.СУММА, 0)) AS САЛЬДО '
 		        	     || 'FROM (SELECT КОД, COALESCE(КОЛ, 0) AS КОЛ, COALESCE(САЛЬДО, 0) AS САЛЬДО '
				     || 'FROM сальдо WHERE СЧЕТ = "' || cAcc || '" AND КОД IN (' || cCommand || ') '
     		        		             || ') S LEFT OUTER JOIN (SELECT P.ДБКОД AS КОД, SUM(COALESCE(P.КОЛ, 0)) AS КОЛ, SUM(COALESCE(P.СУММА, 0)) AS СУММА '
     	               		        		                  || 'FROM проводки P INNER JOIN документы D ON P.ДОККОД=D.КОД '
                	                       		        		  || 'WHERE P.ДБСЧЕТ = "' || cAcc || '" AND COALESCE(P.ДБКОД, 0) IN (' || cCommand || ') AND to_date(D.ДАТА, "DD.MM.YYYY") < to_date("' || cDate1 || '", "DD.MM.YYYY") '
	                	                                       		  || 'GROUP BY P.ДБКОД) P1 ON S.КОД = P1.КОД '
			        	                     	 || 'LEFT OUTER JOIN (SELECT P.КРКОД AS КОД, SUM(COALESCE(P.КОЛ, 0)) AS КОЛ, SUM(COALESCE(P.СУММА, 0)) AS СУММА '
	               				                                  || 'FROM проводки P INNER JOIN документы D ON P.ДОККОД=D.КОД '
        	                				                  || 'WHERE P.КРСЧЕТ = "' || cAcc || '" AND COALESCE(P.КРКОД, 0) IN (' || cCommand || ') AND to_date(D.ДАТА, "DD.MM.YYYY") < to_date("' || cDate1 || '", "DD.MM.YYYY") '
				                                		  || 'GROUP BY P.КРКОД) P2 ON S.КОД = P2.КОД '
				     		      || ') S '
						|| 'UNION '
						|| 'SELECT D.ДАТАВРЕМЯ AS ДАТА, D.ОПЕР AS ОПЕРНОМЕР, T.ИМЯ AS ОПЕРИМЯ, "' || cAcc || '" AS ДБСЧЕТ, P.КРСЧЕТ, COALESCE(P.КОЛ, 0) AS ДБКОЛ, COALESCE(P.СУММА, 0) AS ДБСУММА, 0 AS КРКОЛ, 0 AS КРСУММА '
						|| 'FROM проводки P INNER JOIN документы D ON P.ДОККОД=D.КОД '
               							               || 'INNER JOIN топер T ON P.ОПЕР = T.ОПЕР AND T.НОМЕР = 1 '
						|| 'WHERE P.ДБСЧЕТ <> P.КРСЧЕТ AND P.ДБСЧЕТ = "' || cAcc || '" AND P.ДБКОД IN (' || cCommand || ') AND (P.КОЛ <> 0 OR P.СУММА <> 0) AND (to_date(D.ДАТА, "DD.MM.YYYY") >= to_date("' || cDate1 || '", "DD.MM.YYYY")) AND (to_date(D.ДАТА, "DD.MM.YYYY") < to_date("' || cDate2 || '", "DD.MM.YYYY") + 1) '
						|| 'UNION '
						|| 'SELECT D.ДАТАВРЕМЯ AS ДАТА, D.ОПЕР AS ОПЕРНОМЕР, T.ИМЯ AS ОПЕРИМЯ, P.ДБСЧЕТ, "' || cAcc || '" AS КРСЧЕТ, 0 AS ДБКОЛ, 0 AS ДБСУММА, COALESCE(P.КОЛ, 0) AS КРКОЛ, COALESCE(P.СУММА, 0) AS КРСУММА '
						|| 'FROM проводки P INNER JOIN документы D ON P.ДОККОД=D.КОД '
               							               || 'INNER JOIN топер T ON P.ОПЕР = T.ОПЕР AND T.НОМЕР = 1 '
						|| 'WHERE P.ДБСЧЕТ <> P.КРСЧЕТ AND P.КРСЧЕТ = "' || cAcc || '" AND P.КРКОД IN (' || cCommand || ') AND (P.КОЛ <> 0 OR P.СУММА <> 0) AND (to_date(D.ДАТА, "DD.MM.YYYY") >= to_date("' || cDate1 || '", "DD.MM.YYYY")) AND (to_date(D.ДАТА, "DD.MM.YYYY") < to_date("' || cDate2 || '", "DD.MM.YYYY") + 1) '
						|| ') S '
					|| 'GROUP BY ДАТА, ОПЕРНОМЕР, ОПЕРИМЯ, ДБСЧЕТ, КРСЧЕТ';
	RETURN cCommand;
END;
$$;


ALTER FUNCTION public.sp_maketotobjoborotcommand(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) OWNER TO sa;

--
-- TOC entry 23 (class 1255 OID 71807)
-- Dependencies: 6 435
-- Name: synonymtsvectorupdate(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION synonymtsvectorupdate() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	NEW."FTS" = to_tsvector(lower(NEW.ИМЯ || ' ' || NEW.ИМЯ1));
	RETURN NEW;
END;
$$;


ALTER FUNCTION public.synonymtsvectorupdate() OWNER TO sa;

--
-- TOC entry 24 (class 1255 OID 71808)
-- Dependencies: 435 6
-- Name: testdeleting_Сальдо(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION "testdeleting_Сальдо"() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
DECLARE 
	cAcc VARCHAR(20);
	nId INTEGER;
BEGIN
	IF (SELECT COUNT(*) FROM "проводки" WHERE ("ДБСЧЕТ" = OLD."СЧЕТ" AND "ДБКОД" = OLD."КОД") OR ("ДБСЧЕТ" = OLD."СЧЕТ" AND "ДБКОД" = OLD."КОД")) > 0 THEN
		RAISE EXCEPTION 'Запрещено удалять запись, т.к. для нее были сделаны бухгалтерские проводки.';
	END IF;
	RETURN OLD;
END;
$$;


ALTER FUNCTION public."testdeleting_Сальдо"() OWNER TO sa;

--
-- TOC entry 26 (class 1255 OID 71809)
-- Dependencies: 435 6
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
	Count INTEGER;
	OperName VARCHAR(100);
	OperNum VARCHAR(10);
	OperDate DATE;
	OperID INTEGER;
	cCommand VARCHAR(1000);

	CurTables REFCURSOR;
	CurAccounts REFCURSOR;
BEGIN
	lError := FALSE;		-- Считаем поначалу, что никаких проблем не обнаружено
	
	-- Проверим, есть ли ссылка на этот объект в одном из справочников
	cDict := LTRIM(RTRIM(UPPER(TG_RELNAME)));	-- Возьмем имя обрабатываемого справочника
	nId := OLD."КОД";					-- и возьмем код удаляемой позиции

	OPEN CurTables FOR
		SELECT DISTINCT t.RELNAME
		FROM pg_attribute C
			INNER JOIN (SELECT c.RELFILENODE, c.RELNAME
				    FROM pg_class c
				    WHERE c.RELNAME IN (SELECT TABLENAME FROM pg_tables WHERE SCHEMANAME = 'public')
				    ) t ON C.ATTRELID = t.RELFILENODE
		WHERE UPPER(c.ATTNAME) = 'КОД_' || cDict;

	LOOP
		FETCH CurTables INTO cTable;
		IF NOT FOUND THEN
			EXIT;
		ELSE
			EXECUTE 'SELECT COUNT(*) FROM ' || cTable || ' WHERE КОД_' || cDict || ' = ' || LTRIM(RTRIM(CAST(nId AS VARCHAR(20)))) INTO nCount;
			IF nCount > 0 THEN
				lError := TRUE;
				RAISE EXCEPTION 'Запрещено удалять запись, т.к. на нее имеется ссылка в справочнике <%>', cTable;
				EXIT;			
			END IF;
		END IF;
	END LOOP;

	CLOSE CurTables;

	IF NOT lError THEN	-- Если еще нет никакой ошибки, то продолжим дальше
		OPEN CurAccounts FOR 
			SELECT "СЧЕТ" 
			FROM "счета" 
			WHERE LTRIM(RTRIM(UPPER("ИМЯСПРАВОЧНИКА"))) = cDict;
	
		LOOP
			FETCH CurAccounts INTO cAcc;
			IF NOT FOUND THEN
				EXIT;
			ELSE
				cAcc := RTRIM(cAcc);
				cCommand := 'FROM "проводки" WHERE ("ДБСЧЕТ" = ''' || cAcc || ''' AND "ДБКОД" = ' || LTRIM(RTRIM(CAST(nId AS VARCHAR(20)))) || ') OR ("КРСЧЕТ" = ''' || cAcc || ''' AND "КРКОД" = ' || LTRIM(RTRIM(CAST(nId AS VARCHAR(20)))) || ')';
				EXECUTE 'SELECT COUNT(*) ' || cCommand INTO nCount;
				IF nCount > 0 THEN
					lError := TRUE;
					EXECUTE 'SELECT "ДОККОД" ' || cCommand || ' ORDER BY "ДОККОД" DESC LIMIT 1' INTO nDocId;
					EXECUTE 'SELECT "ОПЕР" ' || cCommand || ' ORDER BY "ДОККОД" DESC LIMIT 1' INTO OperId;
					cCommand := LTRIM(RTRIM(CAST(nDocId AS VARCHAR(20))));
					EXECUTE 'SELECT "ДАТА" FROM "документы" WHERE "КОД" = ' || cCommand INTO OperDate;
					EXECUTE 'SELECT "НОМЕР" FROM "документы" WHERE "КОД" = ' || cCommand INTO OperNum;
					EXECUTE 'SELECT "ИМЯ" FROM "топер" WHERE "ОПЕР" = ' || LTRIM(RTRIM(CAST(OperId AS VARCHAR(20)))) || ' AND "НОМЕР" = 1' INTO OperName;
					RAISE EXCEPTION 'Запрещено удалять запись, т.к. для нее были сделаны операции (% шт.). Последняя операция <%> по документу номер <%> была сделана <%>.', nCount, RTRIM(OperName), RTRIM(OperNum), OperDate;
					EXIT;
				END IF;
			END IF;
		END LOOP;
		CLOSE CurAccounts;
	END IF;

	IF lError THEN
		RETURN NULL;	-- Ошибка, удалять нельзя
	ELSE
		RETURN OLD;	-- Ошибки нет, можно удалять запись
	END IF;
END;
$$;


ALTER FUNCTION public.testdeletingdictobject() OWNER TO sa;

--
-- TOC entry 27 (class 1255 OID 71810)
-- Dependencies: 435 6
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
	DocId INTEGER;
	Count INTEGER;
	OperName VARCHAR(100);
	OperNum VARCHAR(10);
	OperDate VARCHAR(10);
	OperID INTEGER;

	CurTables REFCURSOR;
	CurAccounts REFCURSOR;
BEGIN
	lError := FALSE;		-- Считаем поначалу, что никаких проблем не обнаружено

	-- Проверим, есть ли ссылка на этот объект в одном из справочников
	cDict := LTRIM(RTRIM(UPPER(TG_RELNAME)));	-- Возьмем имя обрабатываемого справочника
	nId := OLD."КОД";				-- и возьмем код удаляемой позиции

	OPEN CurTables FOR
		SELECT DISTINCT "ТАБЛИЦА"
		FROM vw_columns
		WHERE "СТОЛБЕЦ" = 'КОД_' || cDict;

	LOOP
		FETCH CurTables INTO cTable;
		IF NOT FOUND THEN
			EXIT;
		ELSE
			EXECUTE 'SELECT COUNT(*) FROM ' || cTable || ' WHERE "КОД_' || cDict || '" = ' || LTRIM(RTRIM(CAST(nId AS VARCHAR(20)))) INTO nCount;
			IF nCount > 0 THEN
				lError := TRUE;
				RAISE EXCEPTION 'Запрещено удалять запись, т.к. на нее имеется ссылка в справочнике <%>', cTable;
				EXIT;			
			END IF;
		END IF;
	END LOOP;

	CLOSE CurTables;

	IF NOT lError THEN	-- Если еще нет никакой ошибки, то продолжим дальше
		OPEN CurAccounts FOR 
			SELECT "СЧЕТ" 
			FROM "счета" 
			WHERE UPPER("ИМЯСПРАВОЧНИКА") = cDict;
	
		LOOP
			FETCH CurAccounts INTO cAcc;
			IF NOT FOUND THEN
				EXIT;
			ELSE
				cAcc := RTRIM(cAcc);
				EXECUTE 'SELECT COUNT(*) FROM "проводки" WHERE ("ДБСЧЕТ" = cAcc AND "ДБКОД" = nId) OR ("КРСЧЕТ" = cAcc AND "КРКОД" = nId)' INTO nCount;
				IF nCount > 0 THEN
					lError := TRUE;
					EXECUTE 'SELECT TOP 1 "ДОККОД" FROM "проводки" WHERE ("ДБСЧЕТ" = cAcc AND "ДБКОД" = nId) OR ("КРСЧЕТ" = cAcc AND "КРКОД" = nId) ORDER BY "ДОККОД" DESC' INTO DocId;
					EXECUTE 'SELECT TOP 1 "ОПЕР" FROM "проводки" WHERE ("ДБСЧЕТ" = cAcc AND "ДБКОД" = nId) OR ("КРСЧЕТ" = cAcc AND "КРКОД" = nId) ORDER BY "ДОККОД" DESC' INTO OperId;
					RAISE EXCEPTION 'Запрещено удалять запись, т.к. для нее были сделаны операции (% шт.). Последняя операция <> по документу номер <> была сделана <>.', nCount;
					EXIT;
				END IF;
			END IF;
		END LOOP;
		CLOSE CurAccounts;
	END IF;

	IF lError THEN
		RETURN NULL;	-- Ошибка, удалять нельзя
	ELSE
		RETURN OLD;	-- Ошибки нет, можно удалять запись
	END IF;
END;
$$;


ALTER FUNCTION public.testdeletingtoperobject() OWNER TO sa;

--
-- TOC entry 28 (class 1255 OID 71811)
-- Dependencies: 6 435
-- Name: testupdatingattrib(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION testupdatingattrib() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	IF (OLD."КОД" <> NEW."КОД") OR (OLD."ДОККОД" <> NEW."ДОККОД") OR (OLD."СТР" <> NEW."СТР") THEN
		RAISE EXCEPTION 'Запрещено изменять значение ключевого столбца';
		RETURN OLD;
	END IF;
	RETURN NEW;
END;
$$;


ALTER FUNCTION public.testupdatingattrib() OWNER TO sa;

--
-- TOC entry 29 (class 1255 OID 71812)
-- Dependencies: 6 435
-- Name: testupdatingdocattrib(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION testupdatingdocattrib() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	IF (OLD."КОД" <> NEW."КОД") THEN
		RAISE EXCEPTION 'Запрещено изменять значение ключевого столбца';
		RETURN OLD;
	END IF;
	RETURN NEW;
END;
$$;


ALTER FUNCTION public.testupdatingdocattrib() OWNER TO sa;

--
-- TOC entry 30 (class 1255 OID 71813)
-- Dependencies: 6 435
-- Name: testupdatingid(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION testupdatingid() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	IF OLD."КОД" <> NEW."КОД" THEN
		RAISE EXCEPTION 'Запрещено изменять значение ключевого столбца';
		RETURN OLD;
	END IF;
	RETURN NEW;
END;
$$;


ALTER FUNCTION public.testupdatingid() OWNER TO sa;

--
-- TOC entry 31 (class 1255 OID 71814)
-- Dependencies: 435 6
-- Name: tsvectorupdate(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION tsvectorupdate() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	NEW."fts" = to_tsvector(lower(replace(replace(replace(trim(NEW."ИМЯ") || ' ' || trim(NEW."АРТИКУЛ"), '-', ' '), ',', ' '), '.', ' ')));
	RETURN NEW;
END;
$$;


ALTER FUNCTION public.tsvectorupdate() OWNER TO sa;

--
-- TOC entry 33 (class 1255 OID 71815)
-- Dependencies: 6 435
-- Name: ВставитьПроводку(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION "ВставитьПроводку"() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	IF (SELECT "СЧИТАТЬ" FROM "топер" WHERE "ОПЕР" = NEW."ОПЕР" AND "НОМЕР" = 1) = '1' THEN			-- Если эту проводку учитывать
		IF char_length(NEW."ДБСЧЕТ") > 0 AND (SELECT "БАЛАНС" FROM "счета" WHERE "СЧЕТ" = NEW."ДБСЧЕТ") = '1' THEN		-- Если счет указан и это не забалансовый счет
			IF (SELECT COUNT(*) FROM "счета" WHERE "СЧЕТ" = NEW."ДБСЧЕТ") = 0 THEN			-- Если не существует такого счета
				INSERT INTO "счета" ("СЧЕТ") VALUES (NEW."ДБСЧЕТ");					-- То добавим его. название счета введет пользователь потом
			END IF;
			IF (SELECT COUNT(*) FROM "сальдо" WHERE "СЧЕТ" = NEW."ДБСЧЕТ" AND "КОД" = NEW."ДБКОД") = 0 THEN
				INSERT INTO "сальдо" ("СЧЕТ", "КОД")  VALUES (NEW."ДБСЧЕТ", NEW."ДБКОД");
			END IF;
			UPDATE "сальдо"					-- ... а теперь новую
				SET "ДБКОЛ" = "ДБКОЛ" + NEW."КОЛ", 
					"ДЕБЕТ" = "ДЕБЕТ" + NEW."СУММА"
				WHERE "СЧЕТ" = NEW."ДБСЧЕТ" AND "КОД" = NEW."ДБКОД";
		END IF;
		IF char_length(NEW."КРСЧЕТ") > 0 AND (SELECT "БАЛАНС" FROM "счета" WHERE "СЧЕТ" = NEW."КРСЧЕТ") = '1' THEN		-- Если счет указан и это не забалансовый счет
			IF (SELECT COUNT(*) FROM "счета" WHERE "СЧЕТ" = NEW."КРСЧЕТ") = 0 THEN			-- Если не существует такого счета
				INSERT INTO "счета" ("СЧЕТ") VALUES (NEW."КРСЧЕТ");					-- То добавим его. название счета введет пользователь потом
			END IF;
			IF (SELECT COUNT(*) FROM "сальдо" WHERE "СЧЕТ" = NEW."КРСЧЕТ" AND "КОД" = NEW."КРКОД") = 0 THEN
				INSERT INTO "сальдо" ("СЧЕТ", "КОД")  VALUES (NEW."КРСЧЕТ", NEW."КРКОД");
			END IF;
			UPDATE "сальдо"					-- ... а теперь новую
				SET "КРКОЛ" = "КРКОЛ" + NEW."КОЛ", 
					"КРЕДИТ" = "КРЕДИТ" + NEW."СУММА"
				WHERE "СЧЕТ" = NEW."КРСЧЕТ" AND "КОД" = NEW."КРКОД";
		END IF;
		RETURN NEW;
	ELSE
		RETURN NULL;
	END IF;
END;
$$;


ALTER FUNCTION public."ВставитьПроводку"() OWNER TO sa;

--
-- TOC entry 34 (class 1255 OID 71816)
-- Dependencies: 6 435
-- Name: СчитатьКонечноеСальдо(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION "СчитатьКонечноеСальдо"() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	NEW."КОНКОЛ" := NEW."КОЛ" + NEW."ДБКОЛ" - NEW."КРКОЛ";
	NEW."КОНСАЛЬДО" := NEW."САЛЬДО" + NEW."ДЕБЕТ" - NEW."КРЕДИТ";
	IF NEW."КОНКОЛ" = 0 THEN
		NEW."КОНЦЕНА" := NEW."КОНСАЛЬДО";
	ELSE
		NEW."КОНЦЕНА" := NEW."КОНСАЛЬДО" / NEW."КОНКОЛ";
	END IF;
	RETURN NEW;
END;
$$;


ALTER FUNCTION public."СчитатьКонечноеСальдо"() OWNER TO sa;

--
-- TOC entry 35 (class 1255 OID 71817)
-- Dependencies: 435 6
-- Name: СчитатьПроводку(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION "СчитатьПроводку"() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	IF NOT (NEW."ДБСЧЕТ" = NEW."КРСЧЕТ" AND NEW."ДБКОД" = NEW."КРКОД") THEN    -- Если объект не замыкается сам на себя
		-- то, значит, проводка ссылается на разные объекты и можно обрабатывать счета раздельно по дебетовому и по кредитовому обороту
		
		-- Cначала обработаем по дебетовому обороту	
		IF (OLD."ДБСЧЕТ" = NEW."ДБСЧЕТ") AND (OLD."ДБКОД" = NEW."ДБКОД") THEN	-- Ссылка на кредитовый объект не изменилась
			UPDATE "сальдо"
				SET "ДБКОЛ" = "ДБКОЛ" - OLD."КОЛ" + NEW."КОЛ", 
					"ДЕБЕТ" = "ДЕБЕТ" - OLD."СУММА" + NEW."СУММА"
				WHERE "СЧЕТ" = OLD."ДБСЧЕТ" AND "КОД" = OLD."ДБКОД";
		ELSE
			UPDATE "сальдо"						-- Сначала обработаем старый счет
				SET "ДБКОЛ" = "ДБКОЛ" - OLD."КОЛ", 
					"ДЕБЕТ" = "ДЕБЕТ" - OLD."СУММА"
				WHERE "СЧЕТ" = OLD."ДБСЧЕТ" AND "КОД" = OLD."ДБКОД";
			IF char_length(NEW."ДБСЧЕТ") > 0 AND (SELECT "БАЛАНС" FROM "счета" WHERE "СЧЕТ" = NEW."ДБСЧЕТ") = '1' THEN	-- Если счет указан и не забалансовый счет
				IF (SELECT COUNT(*) FROM "сальдо" WHERE "СЧЕТ" = NEW."ДБСЧЕТ" AND "КОД" = NEW."ДБКОД") = 0 THEN
					INSERT INTO "сальдо" ("СЧЕТ", "КОД") VALUES (NEW."ДБСЧЕТ", NEW."ДБКОД");
				END IF;
				UPDATE "сальдо"
					SET "ДБКОЛ" = "ДБКОЛ" + NEW."КОЛ", 
						"ДЕБЕТ" = "ДЕБЕТ" + NEW."СУММА"
					WHERE "СЧЕТ" = NEW."ДБСЧЕТ" AND "КОД" = NEW."ДБКОД";
			END IF;
		END IF;

		-- Таперь обработаем по кредитовому обороту	
		IF (OLD."КРСЧЕТ" = NEW."КРСЧЕТ") AND (OLD."КРКОД" = NEW."КРКОД") THEN	-- Ссылка на кредитовый объект не изменилась
			UPDATE "сальдо"
			          SET "КРКОЛ" = "КРКОЛ" - OLD."КОЛ" + NEW."КОЛ", 
				     "КРЕДИТ" = "КРЕДИТ" - OLD."СУММА" + NEW."СУММА"
				WHERE "СЧЕТ" = OLD."КРСЧЕТ" AND "КОД" = OLD."КРКОД";
		ELSE
			UPDATE "сальдо"						-- Сначала обработаем старый счет
				SET "КРКОЛ" = "КРКОЛ" - OLD."КОЛ", 
					"КРЕДИТ" = "КРЕДИТ" - OLD."СУММА"
				WHERE "СЧЕТ" = OLD."КРСЧЕТ" AND "КОД" = OLD."КРКОД";
			IF char_length(NEW."КРСЧЕТ") > 0 AND (SELECT "БАЛАНС" FROM "счета" WHERE "СЧЕТ" = NEW."КРСЧЕТ") = '1' THEN	-- Если счет указан и не забалансовый счет
				IF (SELECT COUNT(*) FROM "сальдо" WHERE "СЧЕТ" = NEW."КРСЧЕТ" AND "КОД" = NEW."КРКОД") = 0 THEN
					INSERT INTO "сальдо" ("СЧЕТ", "КОД") VALUES (NEW."КРСЧЕТ", NEW."КРКОД");
				END IF;
				UPDATE "сальдо"
					SET "КРКОЛ" = "КРКОЛ" + NEW."КОЛ", 
						"КРЕДИТ" = "КРЕДИТ" + NEW."СУММА"
					WHERE "СЧЕТ" = NEW."КРСЧЕТ" AND "КОД" = NEW."КРКОД";
			END IF;
		END IF;
	END IF;
	RETURN NEW;
END;
$$;


ALTER FUNCTION public."СчитатьПроводку"() OWNER TO sa;

--
-- TOC entry 36 (class 1255 OID 71818)
-- Dependencies: 6 435
-- Name: УдалитьДокумент(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION "УдалитьДокумент"() RETURNS trigger
    LANGUAGE plpgsql
    AS $_$
DECLARE
	cAttrName VARCHAR (50);
BEGIN
	cAttrName = 'докатрибуты' || rtrim(ltrim(cast(OLD."ОПЕР" AS VARCHAR(10))));
	IF (SELECT COUNT(*) FROM pg_tables WHERE schemaname='public' AND tablename = cAttrName) > 0 THEN
		EXECUTE 'DELETE FROM "' || cAttrName || '" WHERE "КОД"=$1;' USING OLD."КОД";
	END IF;

	DELETE FROM "проводки" WHERE "ДОККОД" = OLD."КОД";
	RETURN OLD;
END;
$_$;


ALTER FUNCTION public."УдалитьДокумент"() OWNER TO sa;

--
-- TOC entry 37 (class 1255 OID 71819)
-- Dependencies: 6 435
-- Name: УдалитьПроводку(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION "УдалитьПроводку"() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	IF (SELECT "СЧИТАТЬ" FROM "топер" WHERE "ОПЕР" = OLD."ОПЕР" AND "НОМЕР" = 1) = '1' THEN				-- если эту проводку учитывать
		IF char_length(OLD."ДБСЧЕТ") > 0 AND (SELECT "БАЛАНС" FROM "счета" WHERE "СЧЕТ" = OLD."ДБСЧЕТ") = '1' THEN		-- если счет указан и это не забалансовый счет
			UPDATE "сальдо"				
			          SET "ДБКОЛ" = "ДБКОЛ" - OLD."КОЛ",
				     "ДЕБЕТ" = "ДЕБЕТ" - OLD."СУММА"
				WHERE "СЧЕТ" = OLD."ДБСЧЕТ" AND "КОД" = OLD."ДБКОД";
		END IF;
		IF char_length(OLD."КРСЧЕТ") > 0 AND (SELECT "БАЛАНС" FROM "счета" WHERE "СЧЕТ" = OLD."КРСЧЕТ") = '1' THEN		-- если счет указан и не забалансовый счет
			UPDATE "сальдо"
			          SET "КРКОЛ" = "КРКОЛ" - OLD."КОЛ",
				     "КРЕДИТ" = "КРЕДИТ" - OLD."СУММА"
				WHERE "СЧЕТ" = OLD."КРСЧЕТ" AND "КОД" = OLD."КРКОД";
		END IF;
	END IF;
	RETURN OLD;
END;
$$;


ALTER FUNCTION public."УдалитьПроводку"() OWNER TO sa;

--
-- TOC entry 19 (class 1255 OID 71820)
-- Dependencies: 435 6
-- Name: УдалитьСправочник(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION "УдалитьСправочник"() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	IF (OLD."СИСТЕМНЫЙ") THEN
		RAISE EXCEPTION 'Запрещено удалять запись, т.к. это системный справочник';
		RETURN NULL;
	END IF;
	RETURN OLD;
END;
$$;


ALTER FUNCTION public."УдалитьСправочник"() OWNER TO sa;

--
-- TOC entry 1275 (class 3600 OID 71821)
-- Dependencies: 6 1258
-- Name: mydict_showball; Type: TEXT SEARCH DICTIONARY; Schema: public; Owner: sa
--

CREATE TEXT SEARCH DICTIONARY mydict_showball (
    TEMPLATE = pg_catalog.snowball,
    language = 'russian', stopwords = 'russian' );


ALTER TEXT SEARCH DICTIONARY public.mydict_showball OWNER TO sa;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- TOC entry 1631 (class 1259 OID 71822)
-- Dependencies: 6
-- Name: configs; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE configs (
    "group" character varying(200),
    name character varying(200),
    value text
);


ALTER TABLE public.configs OWNER TO sa;

--
-- TOC entry 1632 (class 1259 OID 71828)
-- Dependencies: 1773 6
-- Name: vw_columns; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW vw_columns AS
    SELECT t.relname AS "ТАБЛИЦА", upper((c.attname)::text) AS "СТОЛБЕЦ", s.typname AS "ТИП" FROM ((pg_attribute c JOIN (SELECT c.relfilenode, c.relname FROM pg_class c WHERE ((c.relname IN (SELECT pg_tables.tablename FROM pg_tables WHERE (pg_tables.schemaname = 'public'::name))) OR (c.relname IN (SELECT pg_views.viewname FROM pg_views WHERE (pg_views.schemaname = 'public'::name))))) t ON ((c.attrelid = t.relfilenode))) JOIN pg_type s ON ((c.atttypid = s.oid))) WHERE (c.attnum > 0) ORDER BY t.relname, c.attnum;


ALTER TABLE public.vw_columns OWNER TO sa;

--
-- TOC entry 1633 (class 1259 OID 71833)
-- Dependencies: 1774 6 264 263
-- Name: vw_permissions; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW vw_permissions AS
    SELECT lower((table_privileges.grantee)::text) AS "user", '                    '::bpchar AS maindbname, table_privileges.table_name AS object, '(All)'::bpchar AS "column", 'Grant'::bpchar AS protecttype, table_privileges.privilege_type AS action FROM information_schema.table_privileges WHERE (((table_privileges.table_schema)::text = 'public'::text) AND (((((table_privileges.privilege_type)::text = 'SELECT'::text) OR ((table_privileges.privilege_type)::text = 'INSERT'::text)) OR ((table_privileges.privilege_type)::text = 'DELETE'::text)) OR ((table_privileges.privilege_type)::text = 'UPDATE'::text)));


ALTER TABLE public.vw_permissions OWNER TO sa;

--
-- TOC entry 1634 (class 1259 OID 71837)
-- Dependencies: 1775 6
-- Name: vw_sp_calcaccoborot; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW vw_sp_calcaccoborot AS
    SELECT sp_calcaccoborot."ДАТА", sp_calcaccoborot."ОПЕРНОМЕР", sp_calcaccoborot."ОПЕРИМЯ", sp_calcaccoborot."ДОККОД", sp_calcaccoborot."ДОКУМЕНТ", sp_calcaccoborot."НОМЕР", sp_calcaccoborot."КОММЕНТАРИЙ", sp_calcaccoborot."СУММА", sp_calcaccoborot."ДБСЧЕТ", sp_calcaccoborot."КРСЧЕТ", sp_calcaccoborot."ДЕБЕТ", sp_calcaccoborot."КРЕДИТ", sp_calcaccoborot."СДЕБЕТ", sp_calcaccoborot."СКРЕДИТ" FROM sp_calcaccoborot(('10'::character varying(5))::bpchar) sp_calcaccoborot("ДАТА", "ОПЕРНОМЕР", "ОПЕРИМЯ", "ДОККОД", "ДОКУМЕНТ", "НОМЕР", "КОММЕНТАРИЙ", "СУММА", "ДБСЧЕТ", "КРСЧЕТ", "ДЕБЕТ", "КРЕДИТ", "СДЕБЕТ", "СКРЕДИТ");


ALTER TABLE public.vw_sp_calcaccoborot OWNER TO sa;

--
-- TOC entry 1635 (class 1259 OID 71841)
-- Dependencies: 1776 6
-- Name: vw_tables; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW vw_tables AS
    SELECT pg_tables.tablename AS name, 'table'::text AS type FROM pg_tables UNION SELECT pg_views.viewname AS name, 'view'::text AS type FROM pg_views;


ALTER TABLE public.vw_tables OWNER TO sa;

--
-- TOC entry 1636 (class 1259 OID 71845)
-- Dependencies: 1777 6
-- Name: vw_types; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW vw_types AS
    SELECT dummy.oid AS "КОД", dummy.typname AS "ИМЯ", dummy.typname_orig AS "ТИП", dummy.typlen AS "ДЛИНА" FROM ((SELECT format_type(t.oid, NULL::integer) AS typname, t.typname AS typname_orig, CASE WHEN (t.typelem > (0)::oid) THEN t.typelem ELSE t.oid END AS elemoid, t.typlen, t.typtype, t.oid, nsp.nspname, ((SELECT count(1) AS count FROM pg_type t2 WHERE (t2.typname = t.typname)) > 1) AS isdup FROM (pg_type t JOIN pg_namespace nsp ON ((t.typnamespace = nsp.oid))) WHERE ((((((NOT ((t.typname = 'unknown'::name) AND (nsp.nspname = 'pg_catalog'::name))) AND t.typisdefined) AND (t.typtype = ANY (ARRAY['b'::"char", 'c'::"char", 'd'::"char", 'e'::"char"]))) AND (NOT (EXISTS (SELECT 1 FROM pg_class WHERE (((pg_class.relnamespace = t.typnamespace) AND (pg_class.relname = t.typname)) AND (pg_class.relkind <> 'c'::"char")))))) AND ((t.typname !~~ '_%'::text) OR (NOT (EXISTS (SELECT 1 FROM pg_class WHERE (((pg_class.relnamespace = t.typnamespace) AND (pg_class.relname = ("substring"((t.typname)::text, 2))::name)) AND (pg_class.relkind <> 'c'::"char"))))))) AND (nsp.nspname <> 'information_schema'::name)) UNION SELECT 'bigserial'::text AS text, 'bigserial'::text AS text, 0, 8, 'b'::"char" AS "char", 0, 'pg_catalog'::name AS name, false AS bool) UNION SELECT 'serial'::text AS text, 'serial'::text AS text, 0, 4, 'b'::"char" AS "char", 0, 'pg_catalog'::name AS name, false AS bool) dummy WHERE (dummy.typname !~~ '%[]%'::text) ORDER BY (dummy.nspname <> 'pg_catalog'::name), (dummy.nspname <> 'public'::name), dummy.nspname, dummy.oid;


ALTER TABLE public.vw_types OWNER TO sa;

--
-- TOC entry 1637 (class 1259 OID 71850)
-- Dependencies: 1985 1986 1987 1988 1989 1990 1991 1992 1993 6
-- Name: сальдо; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "сальдо" (
    "СЧЕТ" character(5) NOT NULL,
    "КОД" integer,
    "КОЛ" numeric(10,3) DEFAULT 0,
    "САЛЬДО" numeric(10,2) DEFAULT 0,
    "ДБКОЛ" numeric(10,3) DEFAULT 0,
    "ДЕБЕТ" numeric(10,2) DEFAULT 0,
    "КРКОЛ" numeric(10,3) DEFAULT 0,
    "КРЕДИТ" numeric(10,2) DEFAULT 0,
    "КОНКОЛ" numeric(10,3) DEFAULT 0,
    "КОНСАЛЬДО" numeric(10,2) DEFAULT 0,
    "КОНЦЕНА" numeric(10,2) DEFAULT 0
);


ALTER TABLE public."сальдо" OWNER TO sa;

--
-- TOC entry 1638 (class 1259 OID 71862)
-- Dependencies: 1994 1995 1996 1997 1998 1999 6
-- Name: счета; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "счета" (
    "КОД" integer NOT NULL,
    "ИМЯ" character varying(100) DEFAULT ''::character varying,
    "СЧЕТ" character(5) DEFAULT ''::bpchar,
    "ИМЯСПРАВОЧНИКА" character varying(50) DEFAULT ''::character varying,
    "АНАЛИТИКА" boolean DEFAULT false,
    "КОЛИЧЕСТВО" boolean DEFAULT false,
    "БАЛАНС" boolean DEFAULT true
);


ALTER TABLE public."счета" OWNER TO sa;

--
-- TOC entry 1639 (class 1259 OID 71871)
-- Dependencies: 1778 6
-- Name: vw_баланс; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_баланс" AS
    SELECT DISTINCT "счета"."КОД", "счета"."СЧЕТ", "счета"."ИМЯ", COALESCE("дбсальдо"."ДБКОНСАЛЬДО", (0)::numeric) AS "ДБКОНСАЛЬДО", COALESCE("крсальдо"."КРКОНСАЛЬДО", (0)::numeric) AS "КРКОНСАЛЬДО" FROM (("счета" LEFT JOIN (SELECT DISTINCT "сальдо"."СЧЕТ", sum("сальдо"."КОНСАЛЬДО") AS "ДБКОНСАЛЬДО" FROM "сальдо" WHERE (("сальдо"."КОНСАЛЬДО" > (0)::numeric) AND (substr(("сальдо"."СЧЕТ")::text, 1, 2) <> '00'::text)) GROUP BY "сальдо"."СЧЕТ" ORDER BY "сальдо"."СЧЕТ", sum("сальдо"."КОНСАЛЬДО")) "дбсальдо" ON (("счета"."СЧЕТ" = "дбсальдо"."СЧЕТ"))) LEFT JOIN (SELECT DISTINCT "сальдо"."СЧЕТ", (- sum("сальдо"."КОНСАЛЬДО")) AS "КРКОНСАЛЬДО" FROM "сальдо" WHERE (("сальдо"."КОНСАЛЬДО" < (0)::numeric) AND (substr(("сальдо"."СЧЕТ")::text, 1, 2) <> '00'::text)) GROUP BY "сальдо"."СЧЕТ" ORDER BY "сальдо"."СЧЕТ", (- sum("сальдо"."КОНСАЛЬДО"))) "крсальдо" ON (("счета"."СЧЕТ" = "крсальдо"."СЧЕТ"))) ORDER BY "счета"."КОД", "счета"."СЧЕТ", "счета"."ИМЯ", COALESCE("дбсальдо"."ДБКОНСАЛЬДО", (0)::numeric), COALESCE("крсальдо"."КРКОНСАЛЬДО", (0)::numeric);


ALTER TABLE public."vw_баланс" OWNER TO sa;

--
-- TOC entry 1640 (class 1259 OID 71876)
-- Dependencies: 2001 2002 6
-- Name: блокпериоды; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "блокпериоды" (
    "КОД" integer NOT NULL,
    "ИМЯ" character varying(100) DEFAULT ''::character varying,
    "БЛОККОНЕЦ" date,
    "НАЧАЛО" date NOT NULL,
    "КОНЕЦ" date NOT NULL,
    "ПОЛЬЗОВАТЕЛЬ" character varying(50) DEFAULT ''::character varying
);


ALTER TABLE public."блокпериоды" OWNER TO sa;

--
-- TOC entry 1641 (class 1259 OID 71881)
-- Dependencies: 1779 6
-- Name: пользователи; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "пользователи" AS
    SELECT pg_user.usesysid AS "КОД", pg_user.usename AS "ИМЯ" FROM pg_user WHERE (pg_user.usename <> 'test'::name);


ALTER TABLE public."пользователи" OWNER TO sa;

--
-- TOC entry 1642 (class 1259 OID 71885)
-- Dependencies: 1780 6
-- Name: vw_блокпериоды; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_блокпериоды" AS
    SELECT u."КОД", u."ИМЯ", COALESCE(b."БЛОККОНЕЦ", ('now'::text)::date) AS "БЛОККОНЕЦ", COALESCE(b."НАЧАЛО", (('now'::text)::date - 31)) AS "НАЧАЛО", COALESCE(b."КОНЕЦ", ('now'::text)::date) AS "КОНЕЦ" FROM ("пользователи" u LEFT JOIN "блокпериоды" b ON (((b."ПОЛЬЗОВАТЕЛЬ")::name = u."ИМЯ"))) WHERE (u."ИМЯ" = "current_user"());


ALTER TABLE public."vw_блокпериоды" OWNER TO sa;

--
-- TOC entry 1643 (class 1259 OID 71889)
-- Dependencies: 2004 2005 2006 6
-- Name: документы; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "документы" (
    "КОД" integer NOT NULL,
    "ДАТА" date,
    "ДАТАВРЕМЯ" timestamp without time zone,
    "НОМЕР" character varying(10) DEFAULT ''::character varying,
    "КОММЕНТАРИЙ" character varying(100) DEFAULT ''::character varying,
    "СУММА" numeric(10,2) DEFAULT 0,
    "ОПИСАНИЕ" text,
    "ОПЕР" integer,
    "АВТО" integer,
    "ПЕРЕМЕННЫЕ1" text,
    "ПЕРЕМЕННЫЕ" bytea
);


ALTER TABLE public."документы" OWNER TO sa;

--
-- TOC entry 1644 (class 1259 OID 71898)
-- Dependencies: 1781 6
-- Name: vw_документы; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_документы" AS
    SELECT d."КОД", d."ДАТА", d."ДАТАВРЕМЯ", d."НОМЕР", d."КОММЕНТАРИЙ", d."СУММА", d."ОПЕР", d."АВТО", d."ОПИСАНИЕ" FROM ("документы" d JOIN "vw_блокпериоды" b ON (((d."ДАТА" > (b."НАЧАЛО" - 1)) AND (d."ДАТА" < (b."КОНЕЦ" + 1)))));


ALTER TABLE public."vw_документы" OWNER TO sa;

--
-- TOC entry 1645 (class 1259 OID 71902)
-- Dependencies: 2008 2009 2010 6
-- Name: доступ; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "доступ" (
    "КОД" integer NOT NULL,
    "МЕНЮ" boolean DEFAULT true,
    "КОД_ТИПЫОБЪЕКТОВ" integer,
    "ИМЯ" character varying(100) DEFAULT ''::character varying,
    "ПОЛЬЗОВАТЕЛЬ" character varying(50),
    "ПОКАЗВСЕГДА" boolean DEFAULT false
);


ALTER TABLE public."доступ" OWNER TO sa;

--
-- TOC entry 1646 (class 1259 OID 71908)
-- Dependencies: 1782 6
-- Name: vw_доступ; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_доступ" AS
    SELECT DISTINCT s."ИМЯ", s."КОД_ТИПЫОБЪЕКТОВ", s."МЕНЮ" FROM (SELECT rtrim((d."ИМЯ")::text) AS "ИМЯ", d."КОД_ТИПЫОБЪЕКТОВ", (d."МЕНЮ" OR d."ПОКАЗВСЕГДА") AS "МЕНЮ" FROM ("доступ" d JOIN "пользователи" p ON ((((rtrim((d."ПОЛЬЗОВАТЕЛЬ")::text))::name)::text = rtrim((p."ИМЯ")::text)))) WHERE ((upper(rtrim((p."ИМЯ")::text)) = upper(rtrim(("current_user"())::text))) OR (btrim(("current_user"())::text) = 'sa'::text)) ORDER BY d."ИМЯ") s ORDER BY s."ИМЯ", s."КОД_ТИПЫОБЪЕКТОВ", s."МЕНЮ";


ALTER TABLE public."vw_доступ" OWNER TO sa;

--
-- TOC entry 1647 (class 1259 OID 71912)
-- Dependencies: 1783 6
-- Name: vw_пользователи; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_пользователи" AS
    SELECT pg_user.usesysid AS "код", pg_user.usename AS "имя" FROM pg_user WHERE (pg_user.usename <> 'test'::name);


ALTER TABLE public."vw_пользователи" OWNER TO sa;

--
-- TOC entry 1648 (class 1259 OID 71916)
-- Dependencies: 2012 2013 2014 6
-- Name: проводки; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "проводки" (
    "КОД" integer NOT NULL,
    "ДБСЧЕТ" character(5) NOT NULL,
    "ДБКОД" integer NOT NULL,
    "КРСЧЕТ" character(5) NOT NULL,
    "КРКОД" integer NOT NULL,
    "КОЛ" numeric(10,3) DEFAULT 0,
    "ЦЕНА" numeric(10,2) DEFAULT 0,
    "СУММА" numeric(10,2) DEFAULT 0,
    "СТР" integer NOT NULL,
    "ДОККОД" integer NOT NULL,
    "ОПЕР" numeric(3,0) NOT NULL,
    "НОМЕРОПЕР" numeric(1,0) NOT NULL
);


ALTER TABLE public."проводки" OWNER TO sa;

--
-- TOC entry 1649 (class 1259 OID 71922)
-- Dependencies: 1784 6
-- Name: vw_проводки; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_проводки" AS
    SELECT "проводки"."КОД", "проводки"."ДБСЧЕТ", "проводки"."ДБКОД", "проводки"."КРСЧЕТ", "проводки"."КРКОД", "проводки"."КОЛ", "проводки"."ЦЕНА", "проводки"."СУММА", "проводки"."СТР", "проводки"."ДОККОД", "проводки"."ОПЕР", "проводки"."НОМЕРОПЕР" FROM "проводки" WHERE ("проводки"."ДОККОД" IN (SELECT "vw_документы"."КОД" FROM "vw_документы"));


ALTER TABLE public."vw_проводки" OWNER TO sa;

--
-- TOC entry 1650 (class 1259 OID 71926)
-- Dependencies: 2016 2017 2018 2019 2020 6
-- Name: справочники; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "справочники" (
    "КОД" integer NOT NULL,
    "ИМЯ" character varying(100) DEFAULT ''::character varying,
    "ФОТО" character varying(100) DEFAULT ''::character varying,
    "ИМЯ_В_СПИСКЕ" character varying(100) DEFAULT ''::character varying,
    "ИМЯ_В_ФОРМЕ" character varying(100) DEFAULT ''::character varying,
    "ПРОТОТИП" character varying(100),
    "СИСТЕМНЫЙ" boolean DEFAULT false
);


ALTER TABLE public."справочники" OWNER TO sa;

--
-- TOC entry 1651 (class 1259 OID 71934)
-- Dependencies: 2022 2023 2024 2025 2026 2027 2028 2029 2030 2031 2032 2033 2034 2035 2036 2037 2038 2039 2040 2041 2042 6
-- Name: топер; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "топер" (
    "КОД" integer NOT NULL,
    "ОПЕР" integer,
    "НОМЕР" integer,
    "ДБСЧЕТ" character varying(5) DEFAULT ''::character varying,
    "КРСЧЕТ" character varying(5) DEFAULT ''::character varying,
    "ИМЯ" character varying(100) DEFAULT ''::character varying,
    "ИТОГИ" character varying(1) DEFAULT ''::character varying,
    "МЕНЮ" boolean DEFAULT true,
    "ОСНДОКУМЕНТ" character varying(20) DEFAULT ''::character varying,
    "НУМЕРАТОР" character varying(40) DEFAULT ''::character varying,
    "ОДНАОПЕРАЦИЯ" boolean,
    "КОЛ" boolean DEFAULT false,
    "ДБПОСТ" boolean DEFAULT false,
    "КРПОСТ" boolean DEFAULT false,
    "ДБДОБАВ" boolean DEFAULT false,
    "КРДОБАВ" boolean DEFAULT false,
    "ДБВЫБОР" boolean DEFAULT false,
    "КРВЫБОР" boolean DEFAULT false,
    "ДБСАЛВИДИМ" boolean DEFAULT true,
    "КРСАЛВИДИМ" boolean DEFAULT true,
    "ДБВИДИМ" boolean DEFAULT true,
    "КРВИДИМ" boolean DEFAULT true,
    "ФОРМА" character varying(50) DEFAULT ''::character varying,
    "НЕЗАВИСИМ" boolean DEFAULT false,
    "СЧИТАТЬ" boolean DEFAULT true,
    "ПЕРЕМЕННЫЕ" text,
    "АТРИБУТЫ" boolean,
    "ДОКАТРИБУТЫ" boolean
);


ALTER TABLE public."топер" OWNER TO sa;

--
-- TOC entry 1652 (class 1259 OID 71961)
-- Dependencies: 1785 6
-- Name: vw_справочники_со_столбцами; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_справочники_со_столбцами" AS
    (SELECT s."КОД", s."ИМЯ" FROM "справочники" s UNION SELECT (1000000 + "топер"."ОПЕР") AS "КОД", ('СписокДокументов'::text || btrim((("топер"."ОПЕР")::character varying(20))::text)) AS "ИМЯ" FROM "топер" WHERE ("топер"."НОМЕР" = 1)) UNION SELECT (2000000 + "топер"."ОПЕР") AS "КОД", ('Документ'::text || btrim((("топер"."ОПЕР")::character varying(20))::text)) AS "ИМЯ" FROM "топер" WHERE ("топер"."НОМЕР" = 1);


ALTER TABLE public."vw_справочники_со_столбцами" OWNER TO sa;

--
-- TOC entry 1653 (class 1259 OID 71966)
-- Dependencies: 2044 2045 6
-- Name: столбцы; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "столбцы" (
    "КОД" integer NOT NULL,
    "КОД_VW_СПРАВОЧНИКИ_СО_СТОЛБЦАМИ" integer,
    "ИМЯ" character varying(100) DEFAULT ''::character varying,
    "ЗАГОЛОВОК" character varying(100) DEFAULT ''::character varying,
    "НОМЕР" numeric(3,0),
    "ТОЛЬКОЧТЕНИЕ" boolean,
    "КОДТАБЛИЦЫ" integer
);


ALTER TABLE public."столбцы" OWNER TO sa;

--
-- TOC entry 1685 (class 1259 OID 72230)
-- Dependencies: 1792 6
-- Name: vw_столбцы; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_столбцы" AS
    SELECT s."БАЗСПРАВОЧНИК", s."СПРАВОЧНИК", s."СТОЛБЕЦ", s."ЗАГОЛОВОК", s."НОМЕР", s."ТОЛЬКОЧТЕНИЕ" FROM (SELECT DISTINCT btrim((d."ИМЯ")::text) AS "БАЗСПРАВОЧНИК", CASE WHEN ((d."КОД" >= 1000000) AND (d."КОД" < 2000000)) THEN 'документы'::character varying WHEN (d."КОД" >= 2000000) THEN 'проводки'::character varying ELSE d1."ИМЯ" END AS "СПРАВОЧНИК", CASE WHEN ("position"((s."ИМЯ")::text, '.'::text) > 0) THEN ("substring"((s."ИМЯ")::text, ("position"((s."ИМЯ")::text, '.'::text) + 1)))::character varying ELSE s."ИМЯ" END AS "СТОЛБЕЦ", s."ЗАГОЛОВОК", s."НОМЕР", s."ТОЛЬКОЧТЕНИЕ" FROM (("столбцы" s JOIN "vw_справочники_со_столбцами" d ON ((s."КОД_VW_СПРАВОЧНИКИ_СО_СТОЛБЦАМИ" = d."КОД"))) JOIN "vw_справочники_со_столбцами" d1 ON ((s."КОДТАБЛИЦЫ" = d1."КОД")))) s WHERE ((s."СТОЛБЕЦ")::text <> ''::text) ORDER BY s."СПРАВОЧНИК", s."НОМЕР";


ALTER TABLE public."vw_столбцы" OWNER TO sa;

--
-- TOC entry 1686 (class 1259 OID 72235)
-- Dependencies: 1793 263 6 264 267 264
-- Name: vw_столбцы_типы; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_столбцы_типы" AS
    SELECT DISTINCT s."БАЗСПРАВОЧНИК" AS base_table, ins.table_name, ins."column", ins.name, ins.type, ins.length, ins."precision", ins.is_updatable, COALESCE(s."ЗАГОЛОВОК", ''::character varying) AS header, COALESCE(s."НОМЕР", (0)::numeric) AS number FROM ((SELECT "vw_столбцы"."БАЗСПРАВОЧНИК", "vw_столбцы"."СПРАВОЧНИК", "vw_столбцы"."СТОЛБЕЦ", "vw_столбцы"."ЗАГОЛОВОК", "vw_столбцы"."НОМЕР" FROM "vw_столбцы") s RIGHT JOIN (SELECT DISTINCT ins.table_name, ((ins.ordinal_position)::integer - 1) AS "column", ins.column_name AS name, ins.data_type AS type, (COALESCE((ins.character_maximum_length)::integer, 0) + COALESCE((ins.numeric_precision)::integer, 0)) AS length, COALESCE((ins.numeric_scale)::integer, 0) AS "precision", ins.is_updatable FROM (information_schema.columns ins JOIN "vw_столбцы" s ON ((((ins.table_name)::text = (s."СПРАВОЧНИК")::text) AND (btrim(s."БАЗСПРАВОЧНИК") = 'заявка'::text))))) ins ON ((((s."СПРАВОЧНИК")::text = (ins.table_name)::text) AND ((s."СТОЛБЕЦ")::text = (ins.name)::text)))) ORDER BY ins.table_name, ins."column";


ALTER TABLE public."vw_столбцы_типы" OWNER TO sa;

--
-- TOC entry 1654 (class 1259 OID 71981)
-- Dependencies: 1786 6
-- Name: vw_счета; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_счета" AS
    SELECT s."КОД", s."ИМЯ", s."СЧЕТ", s."ИМЯСПРАВОЧНИКА", s."БАЛАНС", s."КОЛИЧЕСТВО", sp."ПРОТОТИП" FROM ("счета" s LEFT JOIN "справочники" sp ON (((s."ИМЯСПРАВОЧНИКА")::text = (sp."ИМЯ")::text)));


ALTER TABLE public."vw_счета" OWNER TO sa;

--
-- TOC entry 1655 (class 1259 OID 71985)
-- Dependencies: 1787 6
-- Name: vw_топер; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_топер" AS
    SELECT "топер"."КОД", "топер"."ОПЕР", "топер"."НОМЕР", "топер"."ИМЯ", "топер"."ДБСЧЕТ", "счета"."ИМЯСПРАВОЧНИКА" AS "ДБСПРАВ", '                                        '::bpchar AS "ДБСПРАВАЛИАС", "счета"."КОЛИЧЕСТВО" AS "ДБКОЛ", "топер"."ДБПОСТ", "топер"."ДБСАЛВИДИМ", "топер"."ДБВИДИМ", "топер"."КРСЧЕТ", "счета1"."ИМЯСПРАВОЧНИКА" AS "КРСПРАВ", '                                        '::bpchar AS "КРСПРАВАЛИАС", "счета1"."КОЛИЧЕСТВО" AS "КРКОЛ", "топер"."ОДНАОПЕРАЦИЯ", "топер"."ИТОГИ", "топер"."КРПОСТ", "топер"."КРСАЛВИДИМ", "топер"."КРВИДИМ", "топер"."НЕЗАВИСИМ", "топер"."ПЕРЕМЕННЫЕ", "топер"."АТРИБУТЫ", "топер"."ДОКАТРИБУТЫ" FROM (("топер" LEFT JOIN "счета" "счета" ON ((("топер"."ДБСЧЕТ")::bpchar = "счета"."СЧЕТ"))) LEFT JOIN "счета" "счета1" ON ((("топер"."КРСЧЕТ")::bpchar = "счета1"."СЧЕТ")));


ALTER TABLE public."vw_топер" OWNER TO sa;

--
-- TOC entry 1656 (class 1259 OID 71990)
-- Dependencies: 1640 6
-- Name: блокпериоды_КОД_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "блокпериоды_КОД_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."блокпериоды_КОД_seq" OWNER TO sa;

--
-- TOC entry 2201 (class 0 OID 0)
-- Dependencies: 1656
-- Name: блокпериоды_КОД_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "блокпериоды_КОД_seq" OWNED BY "блокпериоды"."КОД";


--
-- TOC entry 2202 (class 0 OID 0)
-- Dependencies: 1656
-- Name: блокпериоды_КОД_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"блокпериоды_КОД_seq"', 2, true);


--
-- TOC entry 1657 (class 1259 OID 71992)
-- Dependencies: 1643 6
-- Name: документы_КОД_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "документы_КОД_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."документы_КОД_seq" OWNER TO sa;

--
-- TOC entry 2203 (class 0 OID 0)
-- Dependencies: 1657
-- Name: документы_КОД_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "документы_КОД_seq" OWNED BY "документы"."КОД";


--
-- TOC entry 2204 (class 0 OID 0)
-- Dependencies: 1657
-- Name: документы_КОД_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"документы_КОД_seq"', 1, true);


--
-- TOC entry 1658 (class 1259 OID 71994)
-- Dependencies: 1645 6
-- Name: доступ_КОД_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "доступ_КОД_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."доступ_КОД_seq" OWNER TO sa;

--
-- TOC entry 2205 (class 0 OID 0)
-- Dependencies: 1658
-- Name: доступ_КОД_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "доступ_КОД_seq" OWNED BY "доступ"."КОД";


--
-- TOC entry 2206 (class 0 OID 0)
-- Dependencies: 1658
-- Name: доступ_КОД_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"доступ_КОД_seq"', 44, true);


--
-- TOC entry 1659 (class 1259 OID 71996)
-- Dependencies: 1788 6
-- Name: доступ_к_оборотам; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "доступ_к_оборотам" AS
    SELECT DISTINCT "счета"."КОД", "счета"."ИМЯ", "счета"."СЧЕТ" FROM ("счета" LEFT JOIN "vw_доступ" ON ((("счета"."СЧЕТ")::text = "vw_доступ"."ИМЯ"))) WHERE ("vw_доступ"."КОД_ТИПЫОБЪЕКТОВ" = 4) ORDER BY "счета"."ИМЯ", "счета"."СЧЕТ";


ALTER TABLE public."доступ_к_оборотам" OWNER TO sa;

--
-- TOC entry 1660 (class 1259 OID 72000)
-- Dependencies: 1789 6
-- Name: доступ_к_сальдо; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "доступ_к_сальдо" AS
    SELECT DISTINCT "счета"."КОД", "счета"."ИМЯ", "счета"."СЧЕТ" FROM ("счета" JOIN "vw_доступ" ON ((rtrim(("счета"."СЧЕТ")::text) = rtrim("vw_доступ"."ИМЯ")))) WHERE ("vw_доступ"."КОД_ТИПЫОБЪЕКТОВ" = 2) ORDER BY "счета"."ИМЯ", "счета"."СЧЕТ";


ALTER TABLE public."доступ_к_сальдо" OWNER TO sa;

--
-- TOC entry 1661 (class 1259 OID 72004)
-- Dependencies: 1790 6
-- Name: доступ_к_справочникам; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "доступ_к_справочникам" AS
    SELECT DISTINCT s."КОД", s."ИМЯ_В_СПИСКЕ" AS "ИМЯ", d."МЕНЮ", d."ИМЯ" AS "СПРАВОЧНИК", s."ИМЯ_В_СПИСКЕ", s."ИМЯ_В_ФОРМЕ", s."ПРОТОТИП", true AS selectable, true AS insertable, true AS deleteable, true AS updateable FROM ("vw_доступ" d JOIN "справочники" s ON ((upper(rtrim(d."ИМЯ")) = upper(rtrim((s."ИМЯ")::text)))));


ALTER TABLE public."доступ_к_справочникам" OWNER TO sa;

--
-- TOC entry 1662 (class 1259 OID 72008)
-- Dependencies: 1791 6
-- Name: доступ_к_топер; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "доступ_к_топер" AS
    SELECT DISTINCT "топер"."КОД", "топер"."ИМЯ", s."МЕНЮ", "топер"."ОПЕР", "топер"."НЕЗАВИСИМ", s.selectable, s.insertable, s.deleteable, s.updateable FROM ("топер" JOIN (SELECT "vw_доступ"."ИМЯ", "vw_доступ"."КОД_ТИПЫОБЪЕКТОВ", "vw_доступ"."МЕНЮ", true AS selectable, true AS insertable, true AS deleteable, true AS updateable FROM "vw_доступ" WHERE ("vw_доступ"."КОД_ТИПЫОБЪЕКТОВ" = 3)) s ON ((rtrim(("топер"."ОПЕР")::text) = rtrim(s."ИМЯ")))) WHERE (("топер"."НОМЕР" = 1) AND (s."МЕНЮ" = true)) ORDER BY "топер"."ИМЯ", s."МЕНЮ", "топер"."ОПЕР", "топер"."НЕЗАВИСИМ";


ALTER TABLE public."доступ_к_топер" OWNER TO sa;

--
-- TOC entry 1663 (class 1259 OID 72013)
-- Dependencies: 2047 2048 2049 6
-- Name: запросы; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "запросы" (
    "КОД" integer NOT NULL,
    "ИМЯ" character varying(100) DEFAULT ''::character varying,
    "ОПЕР" integer DEFAULT 0,
    "ФОРМУЛЫ" text DEFAULT ''::text
);


ALTER TABLE public."запросы" OWNER TO sa;

--
-- TOC entry 1664 (class 1259 OID 72022)
-- Dependencies: 6 1663
-- Name: запросы_КОД_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "запросы_КОД_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."запросы_КОД_seq" OWNER TO sa;

--
-- TOC entry 2212 (class 0 OID 0)
-- Dependencies: 1664
-- Name: запросы_КОД_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "запросы_КОД_seq" OWNED BY "запросы"."КОД";


--
-- TOC entry 2213 (class 0 OID 0)
-- Dependencies: 1664
-- Name: запросы_КОД_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"запросы_КОД_seq"', 1, false);


--
-- TOC entry 1665 (class 1259 OID 72024)
-- Dependencies: 2051 2052 6
-- Name: константы; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "константы" (
    "КОД" integer NOT NULL,
    "ИМЯ" character varying(100) DEFAULT ''::character varying,
    "ЗНАЧЕНИЕ" character varying(200) DEFAULT ''::character varying,
    "КОММЕНТАРИЙ" character varying(100)
);


ALTER TABLE public."константы" OWNER TO sa;

--
-- TOC entry 1666 (class 1259 OID 72029)
-- Dependencies: 6 1665
-- Name: константы_КОД_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "константы_КОД_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."константы_КОД_seq" OWNER TO sa;

--
-- TOC entry 2215 (class 0 OID 0)
-- Dependencies: 1666
-- Name: константы_КОД_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "константы_КОД_seq" OWNED BY "константы"."КОД";


--
-- TOC entry 2216 (class 0 OID 0)
-- Dependencies: 1666
-- Name: константы_КОД_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"константы_КОД_seq"', 22, true);


--
-- TOC entry 1680 (class 1259 OID 72172)
-- Dependencies: 2062 6
-- Name: номенклатура; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "номенклатура" (
    "КОД" integer NOT NULL,
    "ИМЯ" character varying(100) DEFAULT ''::character varying,
    "АРТИКУЛ" character varying(20),
    "ЦЕНА" numeric(10,2),
    "ЕДИЗМ" character varying(10)
);


ALTER TABLE public."номенклатура" OWNER TO sa;

--
-- TOC entry 1679 (class 1259 OID 72170)
-- Dependencies: 6 1680
-- Name: номенклатура_КОД_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "номенклатура_КОД_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."номенклатура_КОД_seq" OWNER TO sa;

--
-- TOC entry 2218 (class 0 OID 0)
-- Dependencies: 1679
-- Name: номенклатура_КОД_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "номенклатура_КОД_seq" OWNED BY "номенклатура"."КОД";


--
-- TOC entry 2219 (class 0 OID 0)
-- Dependencies: 1679
-- Name: номенклатура_КОД_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"номенклатура_КОД_seq"', 1, false);


--
-- TOC entry 1667 (class 1259 OID 72031)
-- Dependencies: 2054 2055 6
-- Name: нумераторы; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "нумераторы" (
    "КОД" integer NOT NULL,
    "ИМЯ" character varying(100) DEFAULT ''::character varying,
    "ЗНАЧЕНИЕ" integer DEFAULT 0,
    "ТЕСТ" boolean
);


ALTER TABLE public."нумераторы" OWNER TO sa;

--
-- TOC entry 1668 (class 1259 OID 72036)
-- Dependencies: 6 1667
-- Name: нумераторы_КОД_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "нумераторы_КОД_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."нумераторы_КОД_seq" OWNER TO sa;

--
-- TOC entry 2221 (class 0 OID 0)
-- Dependencies: 1668
-- Name: нумераторы_КОД_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "нумераторы_КОД_seq" OWNED BY "нумераторы"."КОД";


--
-- TOC entry 2222 (class 0 OID 0)
-- Dependencies: 1668
-- Name: нумераторы_КОД_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"нумераторы_КОД_seq"', 2, true);


--
-- TOC entry 1669 (class 1259 OID 72038)
-- Dependencies: 6 1648
-- Name: проводки_КОД_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "проводки_КОД_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."проводки_КОД_seq" OWNER TO sa;

--
-- TOC entry 2223 (class 0 OID 0)
-- Dependencies: 1669
-- Name: проводки_КОД_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "проводки_КОД_seq" OWNED BY "проводки"."КОД";


--
-- TOC entry 2224 (class 0 OID 0)
-- Dependencies: 1669
-- Name: проводки_КОД_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"проводки_КОД_seq"', 1, true);


--
-- TOC entry 1682 (class 1259 OID 72192)
-- Dependencies: 2064 6
-- Name: справочник1; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "справочник1" (
    "КОД" integer NOT NULL,
    "ИМЯ" character varying(100) DEFAULT ''::character varying,
    "КОД_ГРУППЫ" integer
);


ALTER TABLE public."справочник1" OWNER TO sa;

--
-- TOC entry 1681 (class 1259 OID 72190)
-- Dependencies: 1682 6
-- Name: справочник1_КОД_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "справочник1_КОД_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."справочник1_КОД_seq" OWNER TO sa;

--
-- TOC entry 2226 (class 0 OID 0)
-- Dependencies: 1681
-- Name: справочник1_КОД_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "справочник1_КОД_seq" OWNED BY "справочник1"."КОД";


--
-- TOC entry 2227 (class 0 OID 0)
-- Dependencies: 1681
-- Name: справочник1_КОД_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"справочник1_КОД_seq"', 1, false);


--
-- TOC entry 1684 (class 1259 OID 72202)
-- Dependencies: 2066 6
-- Name: справочник2; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "справочник2" (
    "КОД" integer NOT NULL,
    "ИМЯ" character varying(100) DEFAULT ''::character varying,
    "КОД_ГРУППЫ" integer
);


ALTER TABLE public."справочник2" OWNER TO sa;

--
-- TOC entry 1683 (class 1259 OID 72200)
-- Dependencies: 6 1684
-- Name: справочник2_КОД_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "справочник2_КОД_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."справочник2_КОД_seq" OWNER TO sa;

--
-- TOC entry 2229 (class 0 OID 0)
-- Dependencies: 1683
-- Name: справочник2_КОД_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "справочник2_КОД_seq" OWNED BY "справочник2"."КОД";


--
-- TOC entry 2230 (class 0 OID 0)
-- Dependencies: 1683
-- Name: справочник2_КОД_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"справочник2_КОД_seq"', 1, false);


--
-- TOC entry 1670 (class 1259 OID 72040)
-- Dependencies: 6 1650
-- Name: справочники_КОД_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "справочники_КОД_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."справочники_КОД_seq" OWNER TO sa;

--
-- TOC entry 2231 (class 0 OID 0)
-- Dependencies: 1670
-- Name: справочники_КОД_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "справочники_КОД_seq" OWNED BY "справочники"."КОД";


--
-- TOC entry 2232 (class 0 OID 0)
-- Dependencies: 1670
-- Name: справочники_КОД_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"справочники_КОД_seq"', 118, true);


--
-- TOC entry 1671 (class 1259 OID 72042)
-- Dependencies: 6 1653
-- Name: столбцы_КОД_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "столбцы_КОД_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."столбцы_КОД_seq" OWNER TO sa;

--
-- TOC entry 2233 (class 0 OID 0)
-- Dependencies: 1671
-- Name: столбцы_КОД_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "столбцы_КОД_seq" OWNED BY "столбцы"."КОД";


--
-- TOC entry 2234 (class 0 OID 0)
-- Dependencies: 1671
-- Name: столбцы_КОД_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"столбцы_КОД_seq"', 7531, true);


--
-- TOC entry 1672 (class 1259 OID 72044)
-- Dependencies: 1638 6
-- Name: счета_КОД_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "счета_КОД_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."счета_КОД_seq" OWNER TO sa;

--
-- TOC entry 2235 (class 0 OID 0)
-- Dependencies: 1672
-- Name: счета_КОД_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "счета_КОД_seq" OWNED BY "счета"."КОД";


--
-- TOC entry 2236 (class 0 OID 0)
-- Dependencies: 1672
-- Name: счета_КОД_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"счета_КОД_seq"', 3, true);


--
-- TOC entry 1673 (class 1259 OID 72046)
-- Dependencies: 2057 6
-- Name: типыобъектов; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "типыобъектов" (
    "КОД" integer NOT NULL,
    "ИМЯ" character varying(20) DEFAULT ''::character varying
);


ALTER TABLE public."типыобъектов" OWNER TO sa;

--
-- TOC entry 1674 (class 1259 OID 72050)
-- Dependencies: 1673 6
-- Name: типыобъектов_КОД_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "типыобъектов_КОД_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."типыобъектов_КОД_seq" OWNER TO sa;

--
-- TOC entry 2238 (class 0 OID 0)
-- Dependencies: 1674
-- Name: типыобъектов_КОД_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "типыобъектов_КОД_seq" OWNED BY "типыобъектов"."КОД";


--
-- TOC entry 2239 (class 0 OID 0)
-- Dependencies: 1674
-- Name: типыобъектов_КОД_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"типыобъектов_КОД_seq"', 4, true);


--
-- TOC entry 1675 (class 1259 OID 72052)
-- Dependencies: 6 1651
-- Name: топер_КОД_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "топер_КОД_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."топер_КОД_seq" OWNER TO sa;

--
-- TOC entry 2240 (class 0 OID 0)
-- Dependencies: 1675
-- Name: топер_КОД_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "топер_КОД_seq" OWNED BY "топер"."КОД";


--
-- TOC entry 2241 (class 0 OID 0)
-- Dependencies: 1675
-- Name: топер_КОД_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"топер_КОД_seq"', 2, true);


--
-- TOC entry 1676 (class 1259 OID 72054)
-- Dependencies: 2059 6
-- Name: файлы; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "файлы" (
    "КОД" integer NOT NULL,
    "ИМЯ" character varying(100) DEFAULT ''::character varying,
    "ТИП" integer,
    "ЗНАЧЕНИЕ" bytea,
    "КОНТРСУММА" bigint
);


ALTER TABLE public."файлы" OWNER TO sa;

--
-- TOC entry 1677 (class 1259 OID 72061)
-- Dependencies: 6 1676
-- Name: файлы_КОД_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "файлы_КОД_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."файлы_КОД_seq" OWNER TO sa;

--
-- TOC entry 2243 (class 0 OID 0)
-- Dependencies: 1677
-- Name: файлы_КОД_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "файлы_КОД_seq" OWNED BY "файлы"."КОД";


--
-- TOC entry 2244 (class 0 OID 0)
-- Dependencies: 1677
-- Name: файлы_КОД_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"файлы_КОД_seq"', 903, true);


--
-- TOC entry 1678 (class 1259 OID 72146)
-- Dependencies: 6
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
-- TOC entry 2245 (class 0 OID 0)
-- Dependencies: 1678
-- Name: файлы_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"файлы_код_seq"', 35, true);


--
-- TOC entry 2003 (class 2604 OID 72063)
-- Dependencies: 1656 1640
-- Name: КОД; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "блокпериоды" ALTER COLUMN "КОД" SET DEFAULT nextval('"блокпериоды_КОД_seq"'::regclass);


--
-- TOC entry 2007 (class 2604 OID 72064)
-- Dependencies: 1657 1643
-- Name: КОД; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "документы" ALTER COLUMN "КОД" SET DEFAULT nextval('"документы_КОД_seq"'::regclass);


--
-- TOC entry 2011 (class 2604 OID 72065)
-- Dependencies: 1658 1645
-- Name: КОД; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "доступ" ALTER COLUMN "КОД" SET DEFAULT nextval('"доступ_КОД_seq"'::regclass);


--
-- TOC entry 2050 (class 2604 OID 72066)
-- Dependencies: 1664 1663
-- Name: КОД; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "запросы" ALTER COLUMN "КОД" SET DEFAULT nextval('"запросы_КОД_seq"'::regclass);


--
-- TOC entry 2053 (class 2604 OID 72067)
-- Dependencies: 1666 1665
-- Name: КОД; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "константы" ALTER COLUMN "КОД" SET DEFAULT nextval('"константы_КОД_seq"'::regclass);


--
-- TOC entry 2061 (class 2604 OID 72175)
-- Dependencies: 1680 1679 1680
-- Name: КОД; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "номенклатура" ALTER COLUMN "КОД" SET DEFAULT nextval('"номенклатура_КОД_seq"'::regclass);


--
-- TOC entry 2056 (class 2604 OID 72068)
-- Dependencies: 1668 1667
-- Name: КОД; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "нумераторы" ALTER COLUMN "КОД" SET DEFAULT nextval('"нумераторы_КОД_seq"'::regclass);


--
-- TOC entry 2015 (class 2604 OID 72069)
-- Dependencies: 1669 1648
-- Name: КОД; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "проводки" ALTER COLUMN "КОД" SET DEFAULT nextval('"проводки_КОД_seq"'::regclass);


--
-- TOC entry 2063 (class 2604 OID 72195)
-- Dependencies: 1682 1681 1682
-- Name: КОД; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "справочник1" ALTER COLUMN "КОД" SET DEFAULT nextval('"справочник1_КОД_seq"'::regclass);


--
-- TOC entry 2065 (class 2604 OID 72205)
-- Dependencies: 1684 1683 1684
-- Name: КОД; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "справочник2" ALTER COLUMN "КОД" SET DEFAULT nextval('"справочник2_КОД_seq"'::regclass);


--
-- TOC entry 2021 (class 2604 OID 72070)
-- Dependencies: 1670 1650
-- Name: КОД; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "справочники" ALTER COLUMN "КОД" SET DEFAULT nextval('"справочники_КОД_seq"'::regclass);


--
-- TOC entry 2046 (class 2604 OID 72071)
-- Dependencies: 1671 1653
-- Name: КОД; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "столбцы" ALTER COLUMN "КОД" SET DEFAULT nextval('"столбцы_КОД_seq"'::regclass);


--
-- TOC entry 2000 (class 2604 OID 72072)
-- Dependencies: 1672 1638
-- Name: КОД; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "счета" ALTER COLUMN "КОД" SET DEFAULT nextval('"счета_КОД_seq"'::regclass);


--
-- TOC entry 2058 (class 2604 OID 72073)
-- Dependencies: 1674 1673
-- Name: КОД; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "типыобъектов" ALTER COLUMN "КОД" SET DEFAULT nextval('"типыобъектов_КОД_seq"'::regclass);


--
-- TOC entry 2043 (class 2604 OID 72074)
-- Dependencies: 1675 1651
-- Name: КОД; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "топер" ALTER COLUMN "КОД" SET DEFAULT nextval('"топер_КОД_seq"'::regclass);


--
-- TOC entry 2060 (class 2604 OID 72075)
-- Dependencies: 1677 1676
-- Name: КОД; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "файлы" ALTER COLUMN "КОД" SET DEFAULT nextval('"файлы_КОД_seq"'::regclass);


--
-- TOC entry 2147 (class 0 OID 71822)
-- Dependencies: 1631
-- Data for Name: configs; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY configs ("group", name, value) FROM stdin;
\.


--
-- TOC entry 2150 (class 0 OID 71876)
-- Dependencies: 1640
-- Data for Name: блокпериоды; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "блокпериоды" ("КОД", "ИМЯ", "БЛОККОНЕЦ", "НАЧАЛО", "КОНЕЦ", "ПОЛЬЗОВАТЕЛЬ") FROM stdin;
2	Для SA                                  	1899-12-31	2013-04-01	2013-05-31	sa
\.


--
-- TOC entry 2151 (class 0 OID 71889)
-- Dependencies: 1643
-- Data for Name: документы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "документы" ("КОД", "ДАТА", "ДАТАВРЕМЯ", "НОМЕР", "КОММЕНТАРИЙ", "СУММА", "ОПИСАНИЕ", "ОПЕР", "АВТО", "ПЕРЕМЕННЫЕ1", "ПЕРЕМЕННЫЕ") FROM stdin;
\.


--
-- TOC entry 2152 (class 0 OID 71902)
-- Dependencies: 1645
-- Data for Name: доступ; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "доступ" ("КОД", "МЕНЮ", "КОД_ТИПЫОБЪЕКТОВ", "ИМЯ", "ПОЛЬЗОВАТЕЛЬ", "ПОКАЗВСЕГДА") FROM stdin;
18	t	1	нумераторы	sa	f
2	f	1	типыобъектов	sa	f
1	f	1	доступ	sa	t
8	f	1	доступ_к_топер	sa	f
3	f	1	справочники	sa	t
11	f	1	топер	sa	t
16	t	1	счета	sa	t
17	t	1	константы	sa	f
28	f	1	vw_types	sa	f
40	t	1	номенклатура	sa	f
42	t	1	справочник1	sa	f
43	t	1	справочник2	sa	f
7	f	1	доступ_к_справочникам	sa	f
\.


--
-- TOC entry 2157 (class 0 OID 72013)
-- Dependencies: 1663
-- Data for Name: запросы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "запросы" ("КОД", "ИМЯ", "ОПЕР", "ФОРМУЛЫ") FROM stdin;
\.


--
-- TOC entry 2158 (class 0 OID 72024)
-- Dependencies: 1665
-- Data for Name: константы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "константы" ("КОД", "ИМЯ", "ЗНАЧЕНИЕ", "КОММЕНТАРИЙ") FROM stdin;
3	АдресФирмы                                                                                          		\N
13	ГлБухгалтер                                                                                         		\N
4	ГородФирмы                                                                                          		\N
6	ИНН                                               		\N
5	КодБанка                                                                                            		\N
14	КодГлБанка                                                                                          		\N
12	НазваниеМагазина                                  		\N
2	НазваниеФирмы                                                                                       		\N
9	РасчетныйСчет                                                                                       		\N
7	Руководитель                                                                                        		\N
11	Телефоны                                          		\N
\.


--
-- TOC entry 2162 (class 0 OID 72172)
-- Dependencies: 1680
-- Data for Name: номенклатура; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "номенклатура" ("КОД", "ИМЯ", "АРТИКУЛ", "ЦЕНА", "ЕДИЗМ") FROM stdin;
\.


--
-- TOC entry 2159 (class 0 OID 72031)
-- Dependencies: 1667
-- Data for Name: нумераторы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "нумераторы" ("КОД", "ИМЯ", "ЗНАЧЕНИЕ", "ТЕСТ") FROM stdin;
1	Накладная                               	1	\N
\.


--
-- TOC entry 2153 (class 0 OID 71916)
-- Dependencies: 1648
-- Data for Name: проводки; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "проводки" ("КОД", "ДБСЧЕТ", "ДБКОД", "КРСЧЕТ", "КРКОД", "КОЛ", "ЦЕНА", "СУММА", "СТР", "ДОККОД", "ОПЕР", "НОМЕРОПЕР") FROM stdin;
\.


--
-- TOC entry 2148 (class 0 OID 71850)
-- Dependencies: 1637
-- Data for Name: сальдо; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "сальдо" ("СЧЕТ", "КОД", "КОЛ", "САЛЬДО", "ДБКОЛ", "ДЕБЕТ", "КРКОЛ", "КРЕДИТ", "КОНКОЛ", "КОНСАЛЬДО", "КОНЦЕНА") FROM stdin;
\.


--
-- TOC entry 2163 (class 0 OID 72192)
-- Dependencies: 1682
-- Data for Name: справочник1; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "справочник1" ("КОД", "ИМЯ", "КОД_ГРУППЫ") FROM stdin;
\.


--
-- TOC entry 2164 (class 0 OID 72202)
-- Dependencies: 1684
-- Data for Name: справочник2; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "справочник2" ("КОД", "ИМЯ", "КОД_ГРУППЫ") FROM stdin;
\.


--
-- TOC entry 2154 (class 0 OID 71926)
-- Dependencies: 1650
-- Data for Name: справочники; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "справочники" ("КОД", "ИМЯ", "ФОТО", "ИМЯ_В_СПИСКЕ", "ИМЯ_В_ФОРМЕ", "ПРОТОТИП", "СИСТЕМНЫЙ") FROM stdin;
50	блокпериоды                                                                                         				\N	t
6	доступ                                                                                              		Служебный справочник. Доступ	Доступ	\N	t
86	доступ_к_топер		Служебный просмотр. Доступ к типовым операциям	Типовые операции	\N	t
85	столбцы		Служебный справочник. Столбцы		\N	t
23	счета                                                                                               		Бухгалтерия. План счетов		\N	t
91	типыобъектов		Служебный справочник. Типы объектов	Типы объектов	\N	t
12	топер                                                                                               		Бухгалтерия. Типовые операции (проводки)		\N	t
101	vw_types			Типы данных столбцов	\N	t
13	константы                                                                                           		Справочник. Константы	Константы	\N	t
34	нумераторы                                                                                          		Справочник. Нумераторы	Нумераторы	\N	t
114	номенклатура		Справочник. Номенклатура	Номенклатура	\N	f
4	справочники                                                                                         		Справочники	Справочники	\N	t
84	доступ_к_справочникам		Служебный просмотр. Доступ к справочникам	Справочники	\N	t
117	справочник2		Справочник2	Справочник2	\N	f
116	справочник1		Справочник1	Справочник1	\N	f
\.


--
-- TOC entry 2156 (class 0 OID 71966)
-- Dependencies: 1653
-- Data for Name: столбцы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "столбцы" ("КОД", "КОД_VW_СПРАВОЧНИКИ_СО_СТОЛБЦАМИ", "ИМЯ", "ЗАГОЛОВОК", "НОМЕР", "ТОЛЬКОЧТЕНИЕ", "КОДТАБЛИЦЫ") FROM stdin;
7403	23	ИМЯ	Наименование	1	f	\N
7404	23	СЧЕТ	Счет	2	f	\N
7405	23	ИМЯСПРАВОЧНИКА	Справочник	3	f	\N
7406	23	АНАЛИТИКА	Аналитика	4	f	\N
7407	23	КОЛИЧЕСТВО	Количество	5	f	\N
7408	23	БАЛАНС	Баланс	6	f	\N
7422	96		Код	2	f	\N
7423	96		Наименование	2	f	\N
7428	99		Код	2	f	\N
7429	99		Наименование	2	f	\N
7432	102		Код	2	f	\N
7433	102		Наименование	2	f	\N
7181	6	МЕНЮ	Меню	4	f	\N
7182	6	ТИПЫОБЪЕКТОВ__ИМЯ	Тип объекта	2	t	\N
7183	6	ИМЯ	Наименование	1	f	\N
7184	6	ПОЛЬЗОВАТЕЛЬ	Пользователь	3	f	\N
7468	13	КОД	КОД	1	t	\N
7469	13	ИМЯ	Наименование	2	f	\N
7470	13	ЗНАЧЕНИЕ	Значение	3	f	\N
7471	13	КОММЕНТАРИЙ	Комментарий	4	f	\N
7475	34	ИМЯ	Наименование	1	f	\N
7476	34	ЗНАЧЕНИЕ	Значение	2	f	\N
7478	107	КОД	Код	1	f	\N
7479	107	ИМЯ	Наименование	2	f	\N
88	12	КОД	Код	1	t	\N
89	12	ОПЕР	Операция	2	f	\N
90	12	НОМЕР	Проводка	3	f	\N
91	12	ДБСЧЕТ	Дб.Счет	4	f	\N
92	12	КРСЧЕТ	Кр.Счет	5	f	\N
93	12	ИМЯ	Наименование	6	f	\N
94	12	ИТОГИ	Итог	7	f	\N
95	12	ОСНДОКУМЕНТ	Осн.Документ	8	f	\N
17	91	КОД	Код	1	t	\N
18	91	ИМЯ	Наименование	2	f	\N
96	12	НУМЕРАТОР	Нумератор	9	f	\N
97	12	ОДНАОПЕРАЦИЯ	ОднаОперация	10	f	\N
98	12	КОЛ	Кол-во	11	f	\N
99	12	ДБПОСТ	Дб.Пост	12	f	\N
100	12	КРПОСТ	Кр.Пост	13	f	\N
29	86	ИМЯ	Наименование	1	t	\N
7480	108	КОД	Код	1	f	\N
7481	108	ИМЯ	Наименование	2	f	\N
7484	110	КОД	Код	1	f	\N
7485	110	ИМЯ	Наименование	2	f	\N
7486	110	тест	тест	1	f	\N
7490	111	КОД	Код	1	f	\N
7491	111	ИМЯ	Наименование	2	f	\N
101	12	ДБДОБАВ	Дб.Добав	14	f	\N
102	12	КРДОБАВ	Кр.Добав	15	f	\N
103	12	ДБВЫБОР	Дб.Выбор	16	f	\N
104	12	КРВЫБОР	Кр.Выбор	17	f	\N
105	12	ДБСАЛВИДИМ	Дб.СальдоВидим	18	f	\N
106	12	КРСАЛВИДИМ	Кр.СальдоВидим	19	f	\N
107	12	ДБВИДИМ	ДбВидим	20	f	\N
108	12	КРВИДИМ	КрВидим	21	f	\N
109	12	НЕЗАВИСИМ	Независим	22	f	\N
110	12	СЧИТАТЬ	Считать	23	f	\N
111	12	АТРИБУТЫ	Атрибуты	24	f	\N
7492	111	ТЕСТ	тест	3	f	\N
112	12	ДОКАТРИБУТЫ	Док.Атрибуты	25	f	\N
7420	95		Код	2	f	\N
7421	95		Наименование	2	f	\N
7424	97		Код	2	f	\N
7425	97		Наименование	2	f	\N
7426	98		Код	2	f	\N
7427	98		Наименование	2	f	\N
7430	100		Код	2	f	\N
7431	100		Наименование	2	f	\N
7434	101	ИМЯ	Наименование	1	t	\N
7435	101	ДЛИНА	Длина	2	t	\N
7439	103	КОД	КОД	1	t	\N
7440	103	ИМЯ	ИМЯ	2	f	\N
7444	104	КОД	КОД	2	t	\N
7445	104	ИМЯ	ИМЯ	3	f	\N
7446	104	ТЕСТ	Тест	1	f	\N
7477	105	КОД	КОД	1	t	\N
7482	109	КОД	Код	1	f	\N
7483	109	ИМЯ	Наименование	2	f	\N
7500	114	КОД	Код	1	t	114
7501	114	ИМЯ	Наименование	2	t	114
7502	114	АРТИКУЛ	Артикул	3	t	114
7503	114	ЦЕНА	Цена	4	t	114
7504	114	ЕДИЗМ	Ед.Изм.	6	t	114
7510	4	КОД	КОД	2	t	4
7511	4	ИМЯ	Наименование	1	t	4
7512	4	ФОТО	ФОТО	3	t	4
7513	4	ИМЯ_В_СПИСКЕ	ИМЯ_В_СПИСКЕ	4	t	4
7514	4	ИМЯ_В_ФОРМЕ	ИМЯ_В_ФОРМЕ	5	t	4
7515	4	ПРОТОТИП	ПРОТОТИП	6	t	4
7516	4	СИСТЕМНЫЙ	СИСТЕМНЫЙ	7	t	4
7517	84	ИМЯ	Наименование	1	t	84
7520	117	КОД	Код	1	t	117
7521	117	ИМЯ	Наименование	2	t	117
7530	116	КОД	Код	1	t	116
7531	116	ИМЯ	Наименование	2	t	116
\.


--
-- TOC entry 2149 (class 0 OID 71862)
-- Dependencies: 1638
-- Data for Name: счета; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "счета" ("КОД", "ИМЯ", "СЧЕТ", "ИМЯСПРАВОЧНИКА", "АНАЛИТИКА", "КОЛИЧЕСТВО", "БАЛАНС") FROM stdin;
\.


--
-- TOC entry 2160 (class 0 OID 72046)
-- Dependencies: 1673
-- Data for Name: типыобъектов; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "типыобъектов" ("КОД", "ИМЯ") FROM stdin;
1	справочник
2	сальдо
3	топер
4	оборот
\.


--
-- TOC entry 2155 (class 0 OID 71934)
-- Dependencies: 1651
-- Data for Name: топер; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "топер" ("КОД", "ОПЕР", "НОМЕР", "ДБСЧЕТ", "КРСЧЕТ", "ИМЯ", "ИТОГИ", "МЕНЮ", "ОСНДОКУМЕНТ", "НУМЕРАТОР", "ОДНАОПЕРАЦИЯ", "КОЛ", "ДБПОСТ", "КРПОСТ", "ДБДОБАВ", "КРДОБАВ", "ДБВЫБОР", "КРВЫБОР", "ДБСАЛВИДИМ", "КРСАЛВИДИМ", "ДБВИДИМ", "КРВИДИМ", "ФОРМА", "НЕЗАВИСИМ", "СЧИТАТЬ", "ПЕРЕМЕННЫЕ", "АТРИБУТЫ", "ДОКАТРИБУТЫ") FROM stdin;
\.


--
-- TOC entry 2161 (class 0 OID 72054)
-- Dependencies: 1676
-- Data for Name: файлы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "файлы" ("КОД", "ИМЯ", "ТИП", "ЗНАЧЕНИЕ", "КОНТРСУММА") FROM stdin;
893	счета.qs	0	\\x66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657253686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bed182d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74417070656e6446726f6d51756572792869642c207265636f7264290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d0bdd0bed0b2d0bed0b920d0b7d0b0d0bfd0b8d181d0b820d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726548696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b7d0b0d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7443616c635461626c6528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d18fd187d0b5d0b9d0bad0b820d0b220d182d0b0d0b1d0bbd0b8d186d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744b657950726573736564286b65794576656e74290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bbd18ed0b1d0bed0b920d0bad0bdd0bed0bfd0bad0b820d0bdd0b020d184d0bed180d0bcd0b52e20d09fd0b0d180d0b0d0bcd0b5d182d180206b65794576656e7420d0b8d0bcd0b5d0b5d18220d182d0b8d0bf20514b65794576656e740a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74536574456e61626c656428656e61626c6564290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0b5d0b4d0bdd0b0d0b7d0bdd0b0d187d0b5d0bdd0be20d0b4d0bbd18f20d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d0b820d0b4d0bed181d182d183d0bfd0b020d0ba20d18dd0bbd0b5d0bcd0b5d0bdd182d0b0d0bc20d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18cd181d0bad0bed0b920d184d0bed180d0bcd18b0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e20507265706172655069637475726555726c286f626a656374290a7b202f2f20d092d18bd0b7d0bed0b220d18dd182d0bed0b920d184d183d0bdd0bad186d0b8d0b820d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e20d097d0b4d0b5d181d18c20d0b8d0bcd0b5d0b5d182d181d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d18c20d0b7d0b0d0b3d180d183d0b7d0b8d182d18c20d184d0bed182d0bed0b3d180d0b0d184d0b8d18e20d0b4d0bbd18f20d182d0b5d0bad183d189d0b5d0b3d0be20d0bed0b1d18ad0b5d0bad182d0b0206f626a65637420d0b8d0b720d098d0bdd182d0b5d180d0bdd0b5d182d0b02e20d0a4d183d0bdd0bad186d0b8d18f20d0b4d0bed0bbd0b6d0bdd0b020d0b2d0b5d180d0bdd183d182d18c2075726c20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a	0
898	vw_types.qs	0	\\x66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657253686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bed182d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74417070656e6446726f6d51756572792869642c207265636f7264290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d0bdd0bed0b2d0bed0b920d0b7d0b0d0bfd0b8d181d0b820d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726548696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b7d0b0d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7443616c635461626c6528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d18fd187d0b5d0b9d0bad0b820d0b220d182d0b0d0b1d0bbd0b8d186d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744b657950726573736564286b65794576656e74290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bbd18ed0b1d0bed0b920d0bad0bdd0bed0bfd0bad0b820d0bdd0b020d184d0bed180d0bcd0b52e20d09fd0b0d180d0b0d0bcd0b5d182d180206b65794576656e7420d0b8d0bcd0b5d0b5d18220d182d0b8d0bf20514b65794576656e740a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74536574456e61626c656428656e61626c6564290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0b5d0b4d0bdd0b0d0b7d0bdd0b0d187d0b5d0bdd0be20d0b4d0bbd18f20d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d0b820d0b4d0bed181d182d183d0bfd0b020d0ba20d18dd0bbd0b5d0bcd0b5d0bdd182d0b0d0bc20d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18cd181d0bad0bed0b920d184d0bed180d0bcd18b0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e20507265706172655069637475726555726c286f626a656374290a7b202f2f20d092d18bd0b7d0bed0b220d18dd182d0bed0b920d184d183d0bdd0bad186d0b8d0b820d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e20d097d0b4d0b5d181d18c20d0b8d0bcd0b5d0b5d182d181d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d18c20d0b7d0b0d0b3d180d183d0b7d0b8d182d18c20d184d0bed182d0bed0b3d180d0b0d184d0b8d18e20d0b4d0bbd18f20d182d0b5d0bad183d189d0b5d0b3d0be20d0bed0b1d18ad0b5d0bad182d0b0206f626a65637420d0b8d0b720d098d0bdd182d0b5d180d0bdd0b5d182d0b02e20d0a4d183d0bdd0bad186d0b8d18f20d0b4d0bed0bbd0b6d0bdd0b020d0b2d0b5d180d0bdd183d182d18c2075726c20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a	0
901	константы.qs	0	\\x66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657253686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bed182d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74417070656e6446726f6d51756572792869642c207265636f7264290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d0bdd0bed0b2d0bed0b920d0b7d0b0d0bfd0b8d181d0b820d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726548696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b7d0b0d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7443616c635461626c6528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d18fd187d0b5d0b9d0bad0b820d0b220d182d0b0d0b1d0bbd0b8d186d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744b657950726573736564286b65794576656e74290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bbd18ed0b1d0bed0b920d0bad0bdd0bed0bfd0bad0b820d0bdd0b020d184d0bed180d0bcd0b52e20d09fd0b0d180d0b0d0bcd0b5d182d180206b65794576656e7420d0b8d0bcd0b5d0b5d18220d182d0b8d0bf20514b65794576656e740a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74536574456e61626c656428656e61626c6564290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0b5d0b4d0bdd0b0d0b7d0bdd0b0d187d0b5d0bdd0be20d0b4d0bbd18f20d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d0b820d0b4d0bed181d182d183d0bfd0b020d0ba20d18dd0bbd0b5d0bcd0b5d0bdd182d0b0d0bc20d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18cd181d0bad0bed0b920d184d0bed180d0bcd18b0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e20507265706172655069637475726555726c286f626a656374290a7b202f2f20d092d18bd0b7d0bed0b220d18dd182d0bed0b920d184d183d0bdd0bad186d0b8d0b820d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e20d097d0b4d0b5d181d18c20d0b8d0bcd0b5d0b5d182d181d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d18c20d0b7d0b0d0b3d180d183d0b7d0b8d182d18c20d184d0bed182d0bed0b3d180d0b0d184d0b8d18e20d0b4d0bbd18f20d182d0b5d0bad183d189d0b5d0b3d0be20d0bed0b1d18ad0b5d0bad182d0b0206f626a65637420d0b8d0b720d098d0bdd182d0b5d180d0bdd0b5d182d0b02e20d0a4d183d0bdd0bad186d0b8d18f20d0b4d0bed0bbd0b6d0bdd0b020d0b2d0b5d180d0bdd183d182d18c2075726c20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a	0
894	справочники.qs	0	\\x66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657253686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bed182d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74417070656e6446726f6d51756572792869642c207265636f7264290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d0bdd0bed0b2d0bed0b920d0b7d0b0d0bfd0b8d181d0b820d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726548696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b7d0b0d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7443616c635461626c6528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d18fd187d0b5d0b9d0bad0b820d0b220d182d0b0d0b1d0bbd0b8d186d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744b657950726573736564286b65794576656e74290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bbd18ed0b1d0bed0b920d0bad0bdd0bed0bfd0bad0b820d0bdd0b020d184d0bed180d0bcd0b52e20d09fd0b0d180d0b0d0bcd0b5d182d180206b65794576656e7420d0b8d0bcd0b5d0b5d18220d182d0b8d0bf20514b65794576656e740a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74536574456e61626c656428656e61626c6564290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0b5d0b4d0bdd0b0d0b7d0bdd0b0d187d0b5d0bdd0be20d0b4d0bbd18f20d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d0b820d0b4d0bed181d182d183d0bfd0b020d0ba20d18dd0bbd0b5d0bcd0b5d0bdd182d0b0d0bc20d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18cd181d0bad0bed0b920d184d0bed180d0bcd18b0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e20507265706172655069637475726555726c286f626a656374290a7b202f2f20d092d18bd0b7d0bed0b220d18dd182d0bed0b920d184d183d0bdd0bad186d0b8d0b820d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e20d097d0b4d0b5d181d18c20d0b8d0bcd0b5d0b5d182d181d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d18c20d0b7d0b0d0b3d180d183d0b7d0b8d182d18c20d184d0bed182d0bed0b3d180d0b0d184d0b8d18e20d0b4d0bbd18f20d182d0b5d0bad183d189d0b5d0b3d0be20d0bed0b1d18ad0b5d0bad182d0b0206f626a65637420d0b8d0b720d098d0bdd182d0b5d180d0bdd0b5d182d0b02e20d0a4d183d0bdd0bad186d0b8d18f20d0b4d0bed0bbd0b6d0bdd0b020d0b2d0b5d180d0bdd183d182d18c2075726c20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a	0
897	справочник2.qs	0	\\x66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657253686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bed182d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74417070656e6446726f6d51756572792869642c207265636f7264290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d0bdd0bed0b2d0bed0b920d0b7d0b0d0bfd0b8d181d0b820d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726548696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b7d0b0d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7443616c635461626c6528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d18fd187d0b5d0b9d0bad0b820d0b220d182d0b0d0b1d0bbd0b8d186d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744b657950726573736564286b65794576656e74290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bbd18ed0b1d0bed0b920d0bad0bdd0bed0bfd0bad0b820d0bdd0b020d184d0bed180d0bcd0b52e20d09fd0b0d180d0b0d0bcd0b5d182d180206b65794576656e7420d0b8d0bcd0b5d0b5d18220d182d0b8d0bf20514b65794576656e740a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74536574456e61626c656428656e61626c6564290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0b5d0b4d0bdd0b0d0b7d0bdd0b0d187d0b5d0bdd0be20d0b4d0bbd18f20d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d0b820d0b4d0bed181d182d183d0bfd0b020d0ba20d18dd0bbd0b5d0bcd0b5d0bdd182d0b0d0bc20d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18cd181d0bad0bed0b920d184d0bed180d0bcd18b0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e20507265706172655069637475726555726c286f626a656374290a7b202f2f20d092d18bd0b7d0bed0b220d18dd182d0bed0b920d184d183d0bdd0bad186d0b8d0b820d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e20d097d0b4d0b5d181d18c20d0b8d0bcd0b5d0b5d182d181d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d18c20d0b7d0b0d0b3d180d183d0b7d0b8d182d18c20d184d0bed182d0bed0b3d180d0b0d184d0b8d18e20d0b4d0bbd18f20d182d0b5d0bad183d189d0b5d0b3d0be20d0bed0b1d18ad0b5d0bad182d0b0206f626a65637420d0b8d0b720d098d0bdd182d0b5d180d0bdd0b5d182d0b02e20d0a4d183d0bdd0bad186d0b8d18f20d0b4d0bed0bbd0b6d0bdd0b020d0b2d0b5d180d0bdd183d182d18c2075726c20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a	0
899	нумераторы.qs	0	\\x66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657253686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bed182d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74417070656e6446726f6d51756572792869642c207265636f7264290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d0bdd0bed0b2d0bed0b920d0b7d0b0d0bfd0b8d181d0b820d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726548696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b7d0b0d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7443616c635461626c6528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d18fd187d0b5d0b9d0bad0b820d0b220d182d0b0d0b1d0bbd0b8d186d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744b657950726573736564286b65794576656e74290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bbd18ed0b1d0bed0b920d0bad0bdd0bed0bfd0bad0b820d0bdd0b020d184d0bed180d0bcd0b52e20d09fd0b0d180d0b0d0bcd0b5d182d180206b65794576656e7420d0b8d0bcd0b5d0b5d18220d182d0b8d0bf20514b65794576656e740a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74536574456e61626c656428656e61626c6564290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0b5d0b4d0bdd0b0d0b7d0bdd0b0d187d0b5d0bdd0be20d0b4d0bbd18f20d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d0b820d0b4d0bed181d182d183d0bfd0b020d0ba20d18dd0bbd0b5d0bcd0b5d0bdd182d0b0d0bc20d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18cd181d0bad0bed0b920d184d0bed180d0bcd18b0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e20507265706172655069637475726555726c286f626a656374290a7b202f2f20d092d18bd0b7d0bed0b220d18dd182d0bed0b920d184d183d0bdd0bad186d0b8d0b820d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e20d097d0b4d0b5d181d18c20d0b8d0bcd0b5d0b5d182d181d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d18c20d0b7d0b0d0b3d180d183d0b7d0b8d182d18c20d184d0bed182d0bed0b3d180d0b0d184d0b8d18e20d0b4d0bbd18f20d182d0b5d0bad183d189d0b5d0b3d0be20d0bed0b1d18ad0b5d0bad182d0b0206f626a65637420d0b8d0b720d098d0bdd182d0b5d180d0bdd0b5d182d0b02e20d0a4d183d0bdd0bad186d0b8d18f20d0b4d0bed0bbd0b6d0bdd0b020d0b2d0b5d180d0bdd183d182d18c2075726c20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a	0
900	нумераторы.qs	0	\\x66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657253686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bed182d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74417070656e6446726f6d51756572792869642c207265636f7264290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d0bdd0bed0b2d0bed0b920d0b7d0b0d0bfd0b8d181d0b820d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726548696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b7d0b0d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7443616c635461626c6528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d18fd187d0b5d0b9d0bad0b820d0b220d182d0b0d0b1d0bbd0b8d186d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744b657950726573736564286b65794576656e74290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bbd18ed0b1d0bed0b920d0bad0bdd0bed0bfd0bad0b820d0bdd0b020d184d0bed180d0bcd0b52e20d09fd0b0d180d0b0d0bcd0b5d182d180206b65794576656e7420d0b8d0bcd0b5d0b5d18220d182d0b8d0bf20514b65794576656e740a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74536574456e61626c656428656e61626c6564290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0b5d0b4d0bdd0b0d0b7d0bdd0b0d187d0b5d0bdd0be20d0b4d0bbd18f20d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d0b820d0b4d0bed181d182d183d0bfd0b020d0ba20d18dd0bbd0b5d0bcd0b5d0bdd182d0b0d0bc20d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18cd181d0bad0bed0b920d184d0bed180d0bcd18b0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e20507265706172655069637475726555726c286f626a656374290a7b202f2f20d092d18bd0b7d0bed0b220d18dd182d0bed0b920d184d183d0bdd0bad186d0b8d0b820d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e20d097d0b4d0b5d181d18c20d0b8d0bcd0b5d0b5d182d181d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d18c20d0b7d0b0d0b3d180d183d0b7d0b8d182d18c20d184d0bed182d0bed0b3d180d0b0d184d0b8d18e20d0b4d0bbd18f20d182d0b5d0bad183d189d0b5d0b3d0be20d0bed0b1d18ad0b5d0bad182d0b0206f626a65637420d0b8d0b720d098d0bdd182d0b5d180d0bdd0b5d182d0b02e20d0a4d183d0bdd0bad186d0b8d18f20d0b4d0bed0bbd0b6d0bdd0b020d0b2d0b5d180d0bdd183d182d18c2075726c20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a	0
895	справочники.qs	0	\\x66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657253686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bed182d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74417070656e6446726f6d51756572792869642c207265636f7264290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d0bdd0bed0b2d0bed0b920d0b7d0b0d0bfd0b8d181d0b820d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726548696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b7d0b0d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7443616c635461626c6528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d18fd187d0b5d0b9d0bad0b820d0b220d182d0b0d0b1d0bbd0b8d186d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744b657950726573736564286b65794576656e74290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bbd18ed0b1d0bed0b920d0bad0bdd0bed0bfd0bad0b820d0bdd0b020d184d0bed180d0bcd0b52e20d09fd0b0d180d0b0d0bcd0b5d182d180206b65794576656e7420d0b8d0bcd0b5d0b5d18220d182d0b8d0bf20514b65794576656e740a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74536574456e61626c656428656e61626c6564290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0b5d0b4d0bdd0b0d0b7d0bdd0b0d187d0b5d0bdd0be20d0b4d0bbd18f20d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d0b820d0b4d0bed181d182d183d0bfd0b020d0ba20d18dd0bbd0b5d0bcd0b5d0bdd182d0b0d0bc20d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18cd181d0bad0bed0b920d184d0bed180d0bcd18b0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e20507265706172655069637475726555726c286f626a656374290a7b202f2f20d092d18bd0b7d0bed0b220d18dd182d0bed0b920d184d183d0bdd0bad186d0b8d0b820d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e20d097d0b4d0b5d181d18c20d0b8d0bcd0b5d0b5d182d181d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d18c20d0b7d0b0d0b3d180d183d0b7d0b8d182d18c20d184d0bed182d0bed0b3d180d0b0d184d0b8d18e20d0b4d0bbd18f20d182d0b5d0bad183d189d0b5d0b3d0be20d0bed0b1d18ad0b5d0bad182d0b0206f626a65637420d0b8d0b720d098d0bdd182d0b5d180d0bdd0b5d182d0b02e20d0a4d183d0bdd0bad186d0b8d18f20d0b4d0bed0bbd0b6d0bdd0b020d0b2d0b5d180d0bdd183d182d18c2075726c20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a	0
902	номенклатура.qs	0	\\x66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657253686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bed182d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74417070656e6446726f6d51756572792869642c207265636f7264290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d0bdd0bed0b2d0bed0b920d0b7d0b0d0bfd0b8d181d0b820d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726548696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b7d0b0d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7443616c635461626c6528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d18fd187d0b5d0b9d0bad0b820d0b220d182d0b0d0b1d0bbd0b8d186d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744b657950726573736564286b65794576656e74290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bbd18ed0b1d0bed0b920d0bad0bdd0bed0bfd0bad0b820d0bdd0b020d184d0bed180d0bcd0b52e20d09fd0b0d180d0b0d0bcd0b5d182d180206b65794576656e7420d0b8d0bcd0b5d0b5d18220d182d0b8d0bf20514b65794576656e740a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74536574456e61626c656428656e61626c6564290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0b5d0b4d0bdd0b0d0b7d0bdd0b0d187d0b5d0bdd0be20d0b4d0bbd18f20d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d0b820d0b4d0bed181d182d183d0bfd0b020d0ba20d18dd0bbd0b5d0bcd0b5d0bdd182d0b0d0bc20d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18cd181d0bad0bed0b920d184d0bed180d0bcd18b0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e20507265706172655069637475726555726c286f626a656374290a7b202f2f20d092d18bd0b7d0bed0b220d18dd182d0bed0b920d184d183d0bdd0bad186d0b8d0b820d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e20d097d0b4d0b5d181d18c20d0b8d0bcd0b5d0b5d182d181d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d18c20d0b7d0b0d0b3d180d183d0b7d0b8d182d18c20d184d0bed182d0bed0b3d180d0b0d184d0b8d18e20d0b4d0bbd18f20d182d0b5d0bad183d189d0b5d0b3d0be20d0bed0b1d18ad0b5d0bad182d0b0206f626a65637420d0b8d0b720d098d0bdd182d0b5d180d0bdd0b5d182d0b02e20d0a4d183d0bdd0bad186d0b8d18f20d0b4d0bed0bbd0b6d0bdd0b020d0b2d0b5d180d0bdd183d182d18c2075726c20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a	0
903	доступ_к_справочникам.qs	0	\\x66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744166746572526f774368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bfd0b5d180d0b5d0bcd0b5d189d0b5d0bdd0b8d18f20d0bdd0b020d0b4d180d183d0b3d183d18e20d181d182d180d0bed0bad1830a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657253686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bed182d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74417070656e6446726f6d51756572792869642c207265636f7264290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d0bdd0bed0b2d0bed0b920d0b7d0b0d0bfd0b8d181d0b820d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726548696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b7d0b0d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7443616c635461626c6528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d18fd187d0b5d0b9d0bad0b820d0b220d182d0b0d0b1d0bbd0b8d186d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744b657950726573736564286b65794576656e74290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bbd18ed0b1d0bed0b920d0bad0bdd0bed0bfd0bad0b820d0bdd0b020d184d0bed180d0bcd0b52e20d09fd0b0d180d0b0d0bcd0b5d182d180206b65794576656e7420d0b8d0bcd0b5d0b5d18220d182d0b8d0bf20514b65794576656e740a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74536574456e61626c656428656e61626c6564290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0b5d0b4d0bdd0b0d0b7d0bdd0b0d187d0b5d0bdd0be20d0b4d0bbd18f20d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d0b820d0b4d0bed181d182d183d0bfd0b020d0ba20d18dd0bbd0b5d0bcd0b5d0bdd182d0b0d0bc20d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18cd181d0bad0bed0b920d184d0bed180d0bcd18b0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e20507265706172655069637475726555726c286f626a656374290a7b202f2f20d092d18bd0b7d0bed0b220d18dd182d0bed0b920d184d183d0bdd0bad186d0b8d0b820d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e20d097d0b4d0b5d181d18c20d0b8d0bcd0b5d0b5d182d181d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d18c20d0b7d0b0d0b3d180d183d0b7d0b8d182d18c20d184d0bed182d0bed0b3d180d0b0d184d0b8d18e20d0b4d0bbd18f20d182d0b5d0bad183d189d0b5d0b3d0be20d0bed0b1d18ad0b5d0bad182d0b0206f626a65637420d0b8d0b720d098d0bdd182d0b5d180d0bdd0b5d182d0b02e20d0a4d183d0bdd0bad186d0b8d18f20d0b4d0bed0bbd0b6d0bdd0b020d0b2d0b5d180d0bdd183d182d18c2075726c20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a	0
896	справочник1.qs	0	\\x66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657253686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bed182d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74417070656e6446726f6d51756572792869642c207265636f7264290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d0bdd0bed0b2d0bed0b920d0b7d0b0d0bfd0b8d181d0b820d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726548696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b7d0b0d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7443616c635461626c6528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d18fd187d0b5d0b9d0bad0b820d0b220d182d0b0d0b1d0bbd0b8d186d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a097072696e7428224576656e74496e6974466f726d22293b0a097461626c652e676574466f726d57696467657428292e73657457696e646f775469746c652822616161616161616122293b0a7d0a0a0a66756e6374696f6e204576656e744b657950726573736564286b65794576656e74290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bbd18ed0b1d0bed0b920d0bad0bdd0bed0bfd0bad0b820d0bdd0b020d184d0bed180d0bcd0b52e20d09fd0b0d180d0b0d0bcd0b5d182d180206b65794576656e7420d0b8d0bcd0b5d0b5d18220d182d0b8d0bf20514b65794576656e740a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74536574456e61626c656428656e61626c6564290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0b5d0b4d0bdd0b0d0b7d0bdd0b0d187d0b5d0bdd0be20d0b4d0bbd18f20d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d0b820d0b4d0bed181d182d183d0bfd0b020d0ba20d18dd0bbd0b5d0bcd0b5d0bdd182d0b0d0bc20d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18cd181d0bad0bed0b920d184d0bed180d0bcd18b0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e20507265706172655069637475726555726c286f626a656374290a7b202f2f20d092d18bd0b7d0bed0b220d18dd182d0bed0b920d184d183d0bdd0bad186d0b8d0b820d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e20d097d0b4d0b5d181d18c20d0b8d0bcd0b5d0b5d182d181d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d18c20d0b7d0b0d0b3d180d183d0b7d0b8d182d18c20d184d0bed182d0bed0b3d180d0b0d184d0b8d18e20d0b4d0bbd18f20d182d0b5d0bad183d189d0b5d0b3d0be20d0bed0b1d18ad0b5d0bad182d0b0206f626a65637420d0b8d0b720d098d0bdd182d0b5d180d0bdd0b5d182d0b02e20d0a4d183d0bdd0bad186d0b8d18f20d0b4d0bed0bbd0b6d0bdd0b020d0b2d0b5d180d0bdd183d182d18c2075726c20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a	0
\.


--
-- TOC entry 2074 (class 2606 OID 72077)
-- Dependencies: 1640 1640
-- Name: блокпериоды_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "блокпериоды"
    ADD CONSTRAINT "блокпериоды_pkey" PRIMARY KEY ("КОД");


--
-- TOC entry 2078 (class 2606 OID 72079)
-- Dependencies: 1643 1643
-- Name: документы_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "документы"
    ADD CONSTRAINT "документы_pkey" PRIMARY KEY ("КОД");


--
-- TOC entry 2084 (class 2606 OID 72081)
-- Dependencies: 1645 1645
-- Name: доступ_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "доступ"
    ADD CONSTRAINT "доступ_pkey" PRIMARY KEY ("КОД");


--
-- TOC entry 2109 (class 2606 OID 72083)
-- Dependencies: 1665 1665
-- Name: константы_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "константы"
    ADD CONSTRAINT "константы_pkey" PRIMARY KEY ("КОД");


--
-- TOC entry 2123 (class 2606 OID 72178)
-- Dependencies: 1680 1680
-- Name: номенклатура_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "номенклатура"
    ADD CONSTRAINT "номенклатура_pkey" PRIMARY KEY ("КОД");


--
-- TOC entry 2113 (class 2606 OID 72085)
-- Dependencies: 1667 1667
-- Name: нумераторы_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "нумераторы"
    ADD CONSTRAINT "нумераторы_pkey" PRIMARY KEY ("КОД");


--
-- TOC entry 2088 (class 2606 OID 72087)
-- Dependencies: 1648 1648
-- Name: проводки_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "проводки"
    ADD CONSTRAINT "проводки_pkey" PRIMARY KEY ("КОД");


--
-- TOC entry 2125 (class 2606 OID 72198)
-- Dependencies: 1682 1682
-- Name: справочник1_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "справочник1"
    ADD CONSTRAINT "справочник1_pkey" PRIMARY KEY ("КОД");


--
-- TOC entry 2127 (class 2606 OID 72208)
-- Dependencies: 1684 1684
-- Name: справочник2_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "справочник2"
    ADD CONSTRAINT "справочник2_pkey" PRIMARY KEY ("КОД");


--
-- TOC entry 2099 (class 2606 OID 72089)
-- Dependencies: 1650 1650
-- Name: справочники_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "справочники"
    ADD CONSTRAINT "справочники_pkey" PRIMARY KEY ("КОД");


--
-- TOC entry 2105 (class 2606 OID 72091)
-- Dependencies: 1653 1653
-- Name: столбцы_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "столбцы"
    ADD CONSTRAINT "столбцы_pkey" PRIMARY KEY ("КОД");


--
-- TOC entry 2070 (class 2606 OID 72093)
-- Dependencies: 1638 1638
-- Name: счета_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "счета"
    ADD CONSTRAINT "счета_pkey" PRIMARY KEY ("КОД");


--
-- TOC entry 2117 (class 2606 OID 72095)
-- Dependencies: 1673 1673
-- Name: типыобъектов_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "типыобъектов"
    ADD CONSTRAINT "типыобъектов_pkey" PRIMARY KEY ("КОД");


--
-- TOC entry 2103 (class 2606 OID 72097)
-- Dependencies: 1651 1651
-- Name: топер_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "топер"
    ADD CONSTRAINT "топер_pkey" PRIMARY KEY ("КОД");


--
-- TOC entry 2121 (class 2606 OID 72099)
-- Dependencies: 1676 1676
-- Name: файлы_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "файлы"
    ADD CONSTRAINT "файлы_pkey" PRIMARY KEY ("КОД");


--
-- TOC entry 2067 (class 1259 OID 72100)
-- Dependencies: 1631 1631
-- Name: configs_name_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX configs_name_idx ON configs USING btree ("group", name);


--
-- TOC entry 2075 (class 1259 OID 72101)
-- Dependencies: 1640
-- Name: блокпериоды_ИМЯ_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "блокпериоды_ИМЯ_idx" ON "блокпериоды" USING btree ("ИМЯ");


--
-- TOC entry 2076 (class 1259 OID 72102)
-- Dependencies: 1640
-- Name: блокпериоды_КОД_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "блокпериоды_КОД_idx" ON "блокпериоды" USING btree ("КОД");


--
-- TOC entry 2079 (class 1259 OID 72103)
-- Dependencies: 1643 1643 1643
-- Name: документы_АВТО_ОПЕР_ДАТА_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "документы_АВТО_ОПЕР_ДАТА_idx" ON "документы" USING btree ("АВТО", "ОПЕР", "ДАТА");


--
-- TOC entry 2080 (class 1259 OID 72104)
-- Dependencies: 1643
-- Name: документы_ДАТА_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "документы_ДАТА_idx" ON "документы" USING btree ("ДАТА");


--
-- TOC entry 2081 (class 1259 OID 72105)
-- Dependencies: 1643 1643 1643
-- Name: документы_ДАТА_ОПЕР_АВТО_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "документы_ДАТА_ОПЕР_АВТО_idx" ON "документы" USING btree ("ДАТА", "ОПЕР", "АВТО");


--
-- TOC entry 2082 (class 1259 OID 72106)
-- Dependencies: 1643
-- Name: документы_КОД_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "документы_КОД_idx" ON "документы" USING btree ("КОД");


--
-- TOC entry 2085 (class 1259 OID 72107)
-- Dependencies: 1645
-- Name: доступ_ИМЯ_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "доступ_ИМЯ_idx" ON "доступ" USING btree ("ИМЯ");


--
-- TOC entry 2086 (class 1259 OID 72108)
-- Dependencies: 1645
-- Name: доступ_КОД_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "доступ_КОД_idx" ON "доступ" USING btree ("КОД");


--
-- TOC entry 2106 (class 1259 OID 72109)
-- Dependencies: 1663
-- Name: запросы_ИМЯ_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "запросы_ИМЯ_idx" ON "запросы" USING btree ("ИМЯ");


--
-- TOC entry 2107 (class 1259 OID 72110)
-- Dependencies: 1663
-- Name: запросы_КОД_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "запросы_КОД_idx" ON "запросы" USING btree ("КОД");


--
-- TOC entry 2110 (class 1259 OID 72111)
-- Dependencies: 1665
-- Name: константы_ИМЯ_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "константы_ИМЯ_idx" ON "константы" USING btree ("ИМЯ");


--
-- TOC entry 2111 (class 1259 OID 72112)
-- Dependencies: 1665
-- Name: константы_КОД_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "константы_КОД_idx" ON "константы" USING btree ("КОД");


--
-- TOC entry 2114 (class 1259 OID 72113)
-- Dependencies: 1667
-- Name: нумераторы_ИМЯ_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "нумераторы_ИМЯ_idx" ON "нумераторы" USING btree ("ИМЯ");


--
-- TOC entry 2115 (class 1259 OID 72114)
-- Dependencies: 1667
-- Name: нумераторы_КОД_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "нумераторы_КОД_idx" ON "нумераторы" USING btree ("КОД");


--
-- TOC entry 2089 (class 1259 OID 72115)
-- Dependencies: 1648 1648 1648
-- Name: проводки_ДБКОД_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "проводки_ДБКОД_idx" ON "проводки" USING btree ("ДБСЧЕТ", "ДБКОД", "ДОККОД");


--
-- TOC entry 2090 (class 1259 OID 72116)
-- Dependencies: 1648 1648
-- Name: проводки_ДБСЧЕТ_ОПЕР_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "проводки_ДБСЧЕТ_ОПЕР_idx" ON "проводки" USING btree ("ДБСЧЕТ", "ОПЕР");


--
-- TOC entry 2091 (class 1259 OID 72117)
-- Dependencies: 1648
-- Name: проводки_ДОККОД_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "проводки_ДОККОД_idx" ON "проводки" USING btree ("ДОККОД");


--
-- TOC entry 2092 (class 1259 OID 72118)
-- Dependencies: 1648 1648 1648
-- Name: проводки_ДОККОД_ОПЕР_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "проводки_ДОККОД_ОПЕР_idx" ON "проводки" USING btree ("ДОККОД", "ОПЕР", "НОМЕРОПЕР");


--
-- TOC entry 2093 (class 1259 OID 72119)
-- Dependencies: 1648 1648
-- Name: проводки_ДОККОД_СТР_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "проводки_ДОККОД_СТР_idx" ON "проводки" USING btree ("ДОККОД", "СТР");


--
-- TOC entry 2094 (class 1259 OID 72120)
-- Dependencies: 1648
-- Name: проводки_КОД_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "проводки_КОД_idx" ON "проводки" USING btree ("КОД");


--
-- TOC entry 2095 (class 1259 OID 72121)
-- Dependencies: 1648 1648 1648
-- Name: проводки_КРКОД_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "проводки_КРКОД_idx" ON "проводки" USING btree ("КРСЧЕТ", "КРКОД", "ДОККОД");


--
-- TOC entry 2096 (class 1259 OID 72122)
-- Dependencies: 1648 1648
-- Name: проводки_КРСЧЕТ_ОПЕР_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "проводки_КРСЧЕТ_ОПЕР_idx" ON "проводки" USING btree ("КРСЧЕТ", "ОПЕР");


--
-- TOC entry 2097 (class 1259 OID 72123)
-- Dependencies: 1648 1648
-- Name: проводки_ОПЕР_НОМЕРОПЕР_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "проводки_ОПЕР_НОМЕРОПЕР_idx" ON "проводки" USING btree ("ОПЕР", "НОМЕРОПЕР");


--
-- TOC entry 2068 (class 1259 OID 72124)
-- Dependencies: 1637 1637
-- Name: сальдо_СЧЕТ_КОД_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "сальдо_СЧЕТ_КОД_idx" ON "сальдо" USING btree ("СЧЕТ", "КОД");


--
-- TOC entry 2100 (class 1259 OID 72125)
-- Dependencies: 1650
-- Name: справочники_ИМЯ_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "справочники_ИМЯ_idx" ON "справочники" USING btree ("ИМЯ");


--
-- TOC entry 2101 (class 1259 OID 72126)
-- Dependencies: 1650
-- Name: справочники_КОД_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "справочники_КОД_idx" ON "справочники" USING btree ("КОД");


--
-- TOC entry 2071 (class 1259 OID 72127)
-- Dependencies: 1638
-- Name: счета_ИМЯ_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "счета_ИМЯ_idx" ON "счета" USING btree ("ИМЯ");


--
-- TOC entry 2072 (class 1259 OID 72128)
-- Dependencies: 1638
-- Name: счета_КОД_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "счета_КОД_idx" ON "счета" USING btree ("КОД");


--
-- TOC entry 2118 (class 1259 OID 72129)
-- Dependencies: 1673
-- Name: типыобъектов_ИМЯ_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "типыобъектов_ИМЯ_idx" ON "типыобъектов" USING btree ("ИМЯ");


--
-- TOC entry 2119 (class 1259 OID 72130)
-- Dependencies: 1673
-- Name: типыобъектов_КОД_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "типыобъектов_КОД_idx" ON "типыобъектов" USING btree ("КОД");


--
-- TOC entry 2137 (class 2620 OID 72131)
-- Dependencies: 19 1650
-- Name: test_удалитьсправочник; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "test_удалитьсправочник" BEFORE DELETE ON "справочники" FOR EACH ROW EXECUTE PROCEDURE "УдалитьСправочник"();


--
-- TOC entry 2128 (class 2620 OID 72132)
-- Dependencies: 24 1637
-- Name: testdeleting_Сальдо; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_Сальдо" BEFORE DELETE ON "сальдо" FOR EACH ROW EXECUTE PROCEDURE "testdeleting_Сальдо"();


--
-- TOC entry 2131 (class 2620 OID 72133)
-- Dependencies: 26 1640
-- Name: testdeleting_блокпериоды; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_блокпериоды" BEFORE DELETE ON "блокпериоды" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2133 (class 2620 OID 72134)
-- Dependencies: 26 1645
-- Name: testdeleting_доступ; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_доступ" BEFORE DELETE ON "доступ" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2139 (class 2620 OID 72135)
-- Dependencies: 1663 26
-- Name: testdeleting_запросы; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_запросы" BEFORE DELETE ON "запросы" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2140 (class 2620 OID 72136)
-- Dependencies: 1665 26
-- Name: testdeleting_константы; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_константы" BEFORE DELETE ON "константы" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2144 (class 2620 OID 72179)
-- Dependencies: 1680 26
-- Name: testdeleting_номенклатура; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_номенклатура" BEFORE DELETE ON "номенклатура" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2141 (class 2620 OID 72137)
-- Dependencies: 1667 26
-- Name: testdeleting_нумераторы; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_нумераторы" BEFORE DELETE ON "нумераторы" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2145 (class 2620 OID 72199)
-- Dependencies: 1682 26
-- Name: testdeleting_справочник1; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_справочник1" BEFORE DELETE ON "справочник1" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2146 (class 2620 OID 72209)
-- Dependencies: 26 1684
-- Name: testdeleting_справочник2; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_справочник2" BEFORE DELETE ON "справочник2" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2138 (class 2620 OID 72138)
-- Dependencies: 1650 26
-- Name: testdeleting_справочники; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_справочники" BEFORE DELETE ON "справочники" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2130 (class 2620 OID 72139)
-- Dependencies: 26 1638
-- Name: testdeleting_счета; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_счета" BEFORE DELETE ON "счета" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2142 (class 2620 OID 72140)
-- Dependencies: 1673 26
-- Name: testdeleting_типыобъектов; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_типыобъектов" BEFORE DELETE ON "типыобъектов" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2143 (class 2620 OID 72148)
-- Dependencies: 1676 30
-- Name: testupdating_файлы; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testupdating_файлы" BEFORE UPDATE ON "файлы" FOR EACH ROW EXECUTE PROCEDURE testupdatingid();


--
-- TOC entry 2134 (class 2620 OID 72141)
-- Dependencies: 33 1648
-- Name: ВставитьПроводку; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "ВставитьПроводку" BEFORE INSERT ON "проводки" FOR EACH ROW EXECUTE PROCEDURE "ВставитьПроводку"();


--
-- TOC entry 2129 (class 2620 OID 72142)
-- Dependencies: 34 1637
-- Name: СчитатьКонечноеСальдо; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "СчитатьКонечноеСальдо" BEFORE INSERT OR UPDATE ON "сальдо" FOR EACH ROW EXECUTE PROCEDURE "СчитатьКонечноеСальдо"();


--
-- TOC entry 2135 (class 2620 OID 72143)
-- Dependencies: 1648 35
-- Name: СчитатьПроводку; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "СчитатьПроводку" BEFORE UPDATE ON "проводки" FOR EACH ROW EXECUTE PROCEDURE "СчитатьПроводку"();


--
-- TOC entry 2132 (class 2620 OID 72144)
-- Dependencies: 1643 36
-- Name: УдалитьДокумент; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "УдалитьДокумент" BEFORE DELETE ON "документы" FOR EACH ROW EXECUTE PROCEDURE "УдалитьДокумент"();


--
-- TOC entry 2136 (class 2620 OID 72145)
-- Dependencies: 1648 37
-- Name: УдалитьПроводку; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "УдалитьПроводку" BEFORE DELETE ON "проводки" FOR EACH ROW EXECUTE PROCEDURE "УдалитьПроводку"();


--
-- TOC entry 2169 (class 0 OID 0)
-- Dependencies: 6
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- TOC entry 2170 (class 0 OID 0)
-- Dependencies: 38
-- Name: sp_calcaccoborot(character, character varying, character varying); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_calcaccoborot(cacc character, cdate1 character varying, cdate2 character varying) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_calcaccoborot(cacc character, cdate1 character varying, cdate2 character varying) FROM sa;
GRANT ALL ON FUNCTION sp_calcaccoborot(cacc character, cdate1 character varying, cdate2 character varying) TO sa;
GRANT ALL ON FUNCTION sp_calcaccoborot(cacc character, cdate1 character varying, cdate2 character varying) TO PUBLIC;


--
-- TOC entry 2171 (class 0 OID 0)
-- Dependencies: 18
-- Name: sp_calcdocoborot(character varying, character varying, character varying); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_calcdocoborot(cacc character varying, cdate1 character varying, cdate2 character varying) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_calcdocoborot(cacc character varying, cdate1 character varying, cdate2 character varying) FROM sa;
GRANT ALL ON FUNCTION sp_calcdocoborot(cacc character varying, cdate1 character varying, cdate2 character varying) TO sa;
GRANT ALL ON FUNCTION sp_calcdocoborot(cacc character varying, cdate1 character varying, cdate2 character varying) TO PUBLIC;


--
-- TOC entry 2172 (class 0 OID 0)
-- Dependencies: 39
-- Name: sp_calcobjoborot(character varying, integer, character varying, character varying); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_calcobjoborot(cacc character varying, pnobj integer, cdate1 character varying, cdate2 character varying) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_calcobjoborot(cacc character varying, pnobj integer, cdate1 character varying, cdate2 character varying) FROM sa;
GRANT ALL ON FUNCTION sp_calcobjoborot(cacc character varying, pnobj integer, cdate1 character varying, cdate2 character varying) TO sa;
GRANT ALL ON FUNCTION sp_calcobjoborot(cacc character varying, pnobj integer, cdate1 character varying, cdate2 character varying) TO PUBLIC;


--
-- TOC entry 2173 (class 0 OID 0)
-- Dependencies: 20
-- Name: sp_calcoborot(character varying, character varying, character varying); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_calcoborot(cacc character varying, cdate1 character varying, cdate2 character varying) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_calcoborot(cacc character varying, cdate1 character varying, cdate2 character varying) FROM sa;
GRANT ALL ON FUNCTION sp_calcoborot(cacc character varying, cdate1 character varying, cdate2 character varying) TO sa;
GRANT ALL ON FUNCTION sp_calcoborot(cacc character varying, cdate1 character varying, cdate2 character varying) TO PUBLIC;


--
-- TOC entry 2174 (class 0 OID 0)
-- Dependencies: 32
-- Name: sp_calctotobjoborot(character varying, character varying, integer, character varying, character varying); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_calctotobjoborot(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_calctotobjoborot(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) FROM sa;
GRANT ALL ON FUNCTION sp_calctotobjoborot(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) TO sa;
GRANT ALL ON FUNCTION sp_calctotobjoborot(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) TO PUBLIC;


--
-- TOC entry 2175 (class 0 OID 0)
-- Dependencies: 22
-- Name: sp_deletedoc(integer); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_deletedoc(ndocid integer) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_deletedoc(ndocid integer) FROM sa;
GRANT ALL ON FUNCTION sp_deletedoc(ndocid integer) TO sa;
GRANT ALL ON FUNCTION sp_deletedoc(ndocid integer) TO PUBLIC;


--
-- TOC entry 2176 (class 0 OID 0)
-- Dependencies: 21
-- Name: sp_deletedocstr(integer, integer); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_deletedocstr(ndocid integer, ndocstr integer) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_deletedocstr(ndocid integer, ndocstr integer) FROM sa;
GRANT ALL ON FUNCTION sp_deletedocstr(ndocid integer, ndocstr integer) TO sa;
GRANT ALL ON FUNCTION sp_deletedocstr(ndocid integer, ndocstr integer) TO PUBLIC;


--
-- TOC entry 2177 (class 0 OID 0)
-- Dependencies: 40
-- Name: sp_insertdoc(integer, character varying); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_insertdoc(noper integer, cdate character varying) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_insertdoc(noper integer, cdate character varying) FROM sa;
GRANT ALL ON FUNCTION sp_insertdoc(noper integer, cdate character varying) TO sa;
GRANT ALL ON FUNCTION sp_insertdoc(noper integer, cdate character varying) TO PUBLIC;


--
-- TOC entry 2178 (class 0 OID 0)
-- Dependencies: 41
-- Name: sp_insertdocstr(integer, integer, character varying, integer, integer); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_insertdocstr(noper integer, ndocid integer, pcparam character varying, pncount integer, pndocstr integer) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_insertdocstr(noper integer, ndocid integer, pcparam character varying, pncount integer, pndocstr integer) FROM sa;
GRANT ALL ON FUNCTION sp_insertdocstr(noper integer, ndocid integer, pcparam character varying, pncount integer, pndocstr integer) TO sa;
GRANT ALL ON FUNCTION sp_insertdocstr(noper integer, ndocid integer, pcparam character varying, pncount integer, pndocstr integer) TO PUBLIC;


--
-- TOC entry 2179 (class 0 OID 0)
-- Dependencies: 25
-- Name: sp_maketotobjoborotcommand(character varying, character varying, integer, character varying, character varying); Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON FUNCTION sp_maketotobjoborotcommand(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) FROM PUBLIC;
REVOKE ALL ON FUNCTION sp_maketotobjoborotcommand(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) FROM sa;
GRANT ALL ON FUNCTION sp_maketotobjoborotcommand(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) TO sa;
GRANT ALL ON FUNCTION sp_maketotobjoborotcommand(cacc character varying, pcdictname character varying, pnobj integer, cdate1 character varying, cdate2 character varying) TO PUBLIC;


--
-- TOC entry 2180 (class 0 OID 0)
-- Dependencies: 1631
-- Name: configs; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE configs FROM PUBLIC;
REVOKE ALL ON TABLE configs FROM sa;
GRANT ALL ON TABLE configs TO sa;


--
-- TOC entry 2181 (class 0 OID 0)
-- Dependencies: 1633
-- Name: vw_permissions; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE vw_permissions FROM PUBLIC;
REVOKE ALL ON TABLE vw_permissions FROM sa;
GRANT ALL ON TABLE vw_permissions TO sa;
GRANT SELECT ON TABLE vw_permissions TO PUBLIC;


--
-- TOC entry 2182 (class 0 OID 0)
-- Dependencies: 1637
-- Name: сальдо; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "сальдо" FROM PUBLIC;
REVOKE ALL ON TABLE "сальдо" FROM sa;
GRANT ALL ON TABLE "сальдо" TO sa;


--
-- TOC entry 2183 (class 0 OID 0)
-- Dependencies: 1638
-- Name: счета; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "счета" FROM PUBLIC;
REVOKE ALL ON TABLE "счета" FROM sa;
GRANT ALL ON TABLE "счета" TO sa;


--
-- TOC entry 2184 (class 0 OID 0)
-- Dependencies: 1639
-- Name: vw_баланс; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_баланс" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_баланс" FROM sa;
GRANT ALL ON TABLE "vw_баланс" TO sa;


--
-- TOC entry 2185 (class 0 OID 0)
-- Dependencies: 1640
-- Name: блокпериоды; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "блокпериоды" FROM PUBLIC;
REVOKE ALL ON TABLE "блокпериоды" FROM sa;
GRANT ALL ON TABLE "блокпериоды" TO sa;
GRANT SELECT ON TABLE "блокпериоды" TO PUBLIC;


--
-- TOC entry 2186 (class 0 OID 0)
-- Dependencies: 1641
-- Name: пользователи; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "пользователи" FROM PUBLIC;
REVOKE ALL ON TABLE "пользователи" FROM sa;
GRANT ALL ON TABLE "пользователи" TO sa;
GRANT SELECT ON TABLE "пользователи" TO PUBLIC;
GRANT SELECT ON TABLE "пользователи" TO test;


--
-- TOC entry 2187 (class 0 OID 0)
-- Dependencies: 1642
-- Name: vw_блокпериоды; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_блокпериоды" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_блокпериоды" FROM sa;
GRANT ALL ON TABLE "vw_блокпериоды" TO sa;


--
-- TOC entry 2188 (class 0 OID 0)
-- Dependencies: 1643
-- Name: документы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "документы" FROM PUBLIC;
REVOKE ALL ON TABLE "документы" FROM sa;
GRANT ALL ON TABLE "документы" TO sa;


--
-- TOC entry 2189 (class 0 OID 0)
-- Dependencies: 1645
-- Name: доступ; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "доступ" FROM PUBLIC;
REVOKE ALL ON TABLE "доступ" FROM sa;
GRANT ALL ON TABLE "доступ" TO sa;


--
-- TOC entry 2190 (class 0 OID 0)
-- Dependencies: 1646
-- Name: vw_доступ; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_доступ" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_доступ" FROM sa;
GRANT ALL ON TABLE "vw_доступ" TO sa;
GRANT SELECT ON TABLE "vw_доступ" TO PUBLIC;


--
-- TOC entry 2191 (class 0 OID 0)
-- Dependencies: 1647
-- Name: vw_пользователи; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_пользователи" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_пользователи" FROM sa;
GRANT ALL ON TABLE "vw_пользователи" TO sa;
GRANT SELECT ON TABLE "vw_пользователи" TO test;


--
-- TOC entry 2192 (class 0 OID 0)
-- Dependencies: 1648
-- Name: проводки; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "проводки" FROM PUBLIC;
REVOKE ALL ON TABLE "проводки" FROM sa;
GRANT ALL ON TABLE "проводки" TO sa;


--
-- TOC entry 2193 (class 0 OID 0)
-- Dependencies: 1650
-- Name: справочники; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "справочники" FROM PUBLIC;
REVOKE ALL ON TABLE "справочники" FROM sa;
GRANT ALL ON TABLE "справочники" TO sa;
GRANT SELECT ON TABLE "справочники" TO PUBLIC;


--
-- TOC entry 2194 (class 0 OID 0)
-- Dependencies: 1651
-- Name: топер; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "топер" FROM PUBLIC;
REVOKE ALL ON TABLE "топер" FROM sa;
GRANT ALL ON TABLE "топер" TO sa;


--
-- TOC entry 2195 (class 0 OID 0)
-- Dependencies: 1652
-- Name: vw_справочники_со_столбцами; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_справочники_со_столбцами" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_справочники_со_столбцами" FROM sa;
GRANT ALL ON TABLE "vw_справочники_со_столбцами" TO sa;


--
-- TOC entry 2196 (class 0 OID 0)
-- Dependencies: 1653
-- Name: столбцы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "столбцы" FROM PUBLIC;
REVOKE ALL ON TABLE "столбцы" FROM sa;
GRANT ALL ON TABLE "столбцы" TO sa;


--
-- TOC entry 2197 (class 0 OID 0)
-- Dependencies: 1685
-- Name: vw_столбцы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_столбцы" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_столбцы" FROM sa;
GRANT ALL ON TABLE "vw_столбцы" TO sa;


--
-- TOC entry 2198 (class 0 OID 0)
-- Dependencies: 1686
-- Name: vw_столбцы_типы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_столбцы_типы" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_столбцы_типы" FROM sa;
GRANT ALL ON TABLE "vw_столбцы_типы" TO sa;


--
-- TOC entry 2199 (class 0 OID 0)
-- Dependencies: 1654
-- Name: vw_счета; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_счета" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_счета" FROM sa;
GRANT ALL ON TABLE "vw_счета" TO sa;
GRANT SELECT ON TABLE "vw_счета" TO PUBLIC;


--
-- TOC entry 2200 (class 0 OID 0)
-- Dependencies: 1655
-- Name: vw_топер; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_топер" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_топер" FROM sa;
GRANT ALL ON TABLE "vw_топер" TO sa;


--
-- TOC entry 2207 (class 0 OID 0)
-- Dependencies: 1659
-- Name: доступ_к_оборотам; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "доступ_к_оборотам" FROM PUBLIC;
REVOKE ALL ON TABLE "доступ_к_оборотам" FROM sa;
GRANT ALL ON TABLE "доступ_к_оборотам" TO sa;
GRANT SELECT ON TABLE "доступ_к_оборотам" TO PUBLIC;


--
-- TOC entry 2208 (class 0 OID 0)
-- Dependencies: 1660
-- Name: доступ_к_сальдо; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "доступ_к_сальдо" FROM PUBLIC;
REVOKE ALL ON TABLE "доступ_к_сальдо" FROM sa;
GRANT ALL ON TABLE "доступ_к_сальдо" TO sa;
GRANT SELECT ON TABLE "доступ_к_сальдо" TO PUBLIC;


--
-- TOC entry 2209 (class 0 OID 0)
-- Dependencies: 1661
-- Name: доступ_к_справочникам; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "доступ_к_справочникам" FROM PUBLIC;
REVOKE ALL ON TABLE "доступ_к_справочникам" FROM sa;
GRANT ALL ON TABLE "доступ_к_справочникам" TO sa;
GRANT SELECT ON TABLE "доступ_к_справочникам" TO PUBLIC;


--
-- TOC entry 2210 (class 0 OID 0)
-- Dependencies: 1662
-- Name: доступ_к_топер; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "доступ_к_топер" FROM PUBLIC;
REVOKE ALL ON TABLE "доступ_к_топер" FROM sa;
GRANT ALL ON TABLE "доступ_к_топер" TO sa;
GRANT SELECT ON TABLE "доступ_к_топер" TO PUBLIC;


--
-- TOC entry 2211 (class 0 OID 0)
-- Dependencies: 1663
-- Name: запросы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "запросы" FROM PUBLIC;
REVOKE ALL ON TABLE "запросы" FROM sa;
GRANT ALL ON TABLE "запросы" TO sa;


--
-- TOC entry 2214 (class 0 OID 0)
-- Dependencies: 1665
-- Name: константы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "константы" FROM PUBLIC;
REVOKE ALL ON TABLE "константы" FROM sa;
GRANT ALL ON TABLE "константы" TO sa;
GRANT SELECT ON TABLE "константы" TO PUBLIC;


--
-- TOC entry 2217 (class 0 OID 0)
-- Dependencies: 1680
-- Name: номенклатура; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "номенклатура" FROM PUBLIC;
REVOKE ALL ON TABLE "номенклатура" FROM sa;
GRANT ALL ON TABLE "номенклатура" TO sa;


--
-- TOC entry 2220 (class 0 OID 0)
-- Dependencies: 1667
-- Name: нумераторы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "нумераторы" FROM PUBLIC;
REVOKE ALL ON TABLE "нумераторы" FROM sa;
GRANT ALL ON TABLE "нумераторы" TO sa;


--
-- TOC entry 2225 (class 0 OID 0)
-- Dependencies: 1682
-- Name: справочник1; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "справочник1" FROM PUBLIC;
REVOKE ALL ON TABLE "справочник1" FROM sa;
GRANT ALL ON TABLE "справочник1" TO sa;


--
-- TOC entry 2228 (class 0 OID 0)
-- Dependencies: 1684
-- Name: справочник2; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "справочник2" FROM PUBLIC;
REVOKE ALL ON TABLE "справочник2" FROM sa;
GRANT ALL ON TABLE "справочник2" TO sa;


--
-- TOC entry 2237 (class 0 OID 0)
-- Dependencies: 1673
-- Name: типыобъектов; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "типыобъектов" FROM PUBLIC;
REVOKE ALL ON TABLE "типыобъектов" FROM sa;
GRANT ALL ON TABLE "типыобъектов" TO sa;


--
-- TOC entry 2242 (class 0 OID 0)
-- Dependencies: 1676
-- Name: файлы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "файлы" FROM PUBLIC;
REVOKE ALL ON TABLE "файлы" FROM sa;
GRANT ALL ON TABLE "файлы" TO sa;
GRANT SELECT ON TABLE "файлы" TO PUBLIC;


-- Completed on 2013-08-20 23:39:20

--
-- PostgreSQL database dump complete
--

