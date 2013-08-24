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
	"����" date,
	"���������" integer,
	"�������" character varying(100),
	"������" integer,
	"��������" character varying(20),
	"�����" character varying(10),
	"�����������" character varying(100),
	"�����" numeric(10,2),
	"������" bpchar,
	"������" bpchar,
	"�����" numeric(10,2),
	"������" numeric(10,2),
	"������" character varying(15),
	"�������" character varying(15)
);


ALTER TYPE public.sp_calcaccoborot_fret OWNER TO sa;

--
-- TOC entry 331 (class 1247 OID 71793)
-- Dependencies: 6 1629
-- Name: sp_calcobjoborot_fret; Type: TYPE; Schema: public; Owner: sa
--

CREATE TYPE sp_calcobjoborot_fret AS (
	"����" date,
	"���������" integer,
	"�������" character varying(100),
	"������" integer,
	"��������" character varying(20),
	"�����" character varying(10),
	"���" integer,
	"�����������" character varying(100),
	"�����" numeric(10,2),
	"������" character(5),
	"������" character(5),
	"�����" numeric(10,3),
	"�����" numeric(10,2),
	"�����" numeric(10,3),
	"������" numeric(10,2),
	"������" character varying(15),
	"������" character varying(15),
	"������" character varying(15),
	"�������" character varying(15)
);


ALTER TYPE public.sp_calcobjoborot_fret OWNER TO sa;

--
-- TOC entry 333 (class 1247 OID 71796)
-- Dependencies: 6 1630
-- Name: sp_calcoborot_fret; Type: TYPE; Schema: public; Owner: sa
--

CREATE TYPE sp_calcoborot_fret AS (
	"���" integer,
	"���" numeric(10,3),
	"������" numeric(10,2),
	"�����" numeric(10,3),
	"�����" numeric(10,2),
	"�����" numeric(10,3),
	"������" numeric(10,2),
	"������" numeric(10,3),
	"���������" numeric(10,2),
	"c���" character varying(15),
	"c������" character varying(15),
	"c�����" character varying(15),
	"c�����" character varying(15),
	"c�����" character varying(15),
	"c������" character varying(15),
	"c������" character varying(15),
	"c���������" character varying(15)
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
		dDate1 := (SELECT ������ FROM vw_�����������);
	ELSE
		dDate1 := to_date(cDate1, 'DD.MM.YYYY');
	END IF;
	IF cDate2 IS NULL THEN
		dDate2 := (SELECT ����� FROM vw_�����������);
	ELSE
		dDate2 := to_date(cDate2, 'DD.MM.YYYY') + 1;
	END IF;
	RAISE NOTICE '%', dDate1;
	FOR ret_row IN
		SELECT dDate1 AS "����", 0::integer AS "���������", ''::VARCHAR(100) AS "�������", 0::integer AS "������", ''::VARCHAR(20) AS "��������", ''::VARCHAR(10) AS "�����", ''::VARCHAR(100) AS "�����������", 0.0::numeric(10,2) AS "�����", 
       			''::char(5) AS "������", ''::char(5) AS "������",
       			CASE
               			WHEN S."������" > 0 THEN S."������"
               			ELSE 0.0
               		END::numeric(10,2) AS "�����",
       			CASE
                		WHEN S."������" < 0 THEN -S."������"
                		ELSE 0.0
                	END::numeric(10,2) AS "������", ''::VARCHAR(15) AS "������", ''::VARCHAR(15) AS "�������"
		FROM (SELECT (S."������" + P1."�����" - P2."�����") AS "������"
      	      	      FROM (SELECT "����", SUM(COALESCE("������", 0)) AS "������" 
		    	    FROM "������" 
		    	    WHERE "����" = cAcc 
		    	    GROUP BY "����") S LEFT OUTER JOIN (SELECT P."������", SUM(COALESCE(P."�����", 0)) AS "�����" 
                                		 	      FROM "��������" P INNER JOIN "���������" D ON P."������"=D."���" 
			                        	      WHERE P."������" = cAcc AND D."����" < dDate1 
			         		      	      GROUP BY P."������") P1 ON S."����" = P1."������"
			             	     LEFT OUTER JOIN (SELECT P."������", SUM(COALESCE(P."�����", 0)) AS "�����" 
                                 			      FROM "��������" P INNER JOIN "���������" D ON P."������"=D."���" 
                                 		      	      WHERE P."������" = cAcc AND D."����" < dDate1
       			         		      	      GROUP BY P."������") P2 ON S."����" = P2."������"
		) S
		UNION
		SELECT D."����", D."����" AS "���������", T."���" AS "�������", D."���", COALESCE(T."�����������", '')::VARCHAR(20), D."�����", D."�����������", D."�����", cAcc AS "������", P."������", SUM(COALESCE(P."�����", 0))::numeric(10,2) AS "�������", 0::numeric(10,2) AS "�������", ''::VARCHAR(15) AS "C�����", ''::VARCHAR(15) AS "C������"
		FROM "��������" P INNER JOIN "���������" D ON P."������"=D."���" 
                		INNER JOIN "�����" T ON P."����" = T."����" AND T."�����" = 1
		WHERE P."������" = cAcc AND P."������" <> cAcc AND P."�����" <> 0 AND D."����" >= dDate1 AND D."����" < dDate2
		GROUP BY D."����", D."����", T."���", D."���", T."�����������", D."�����", D."�����������", D."�����", P."������"
		UNION
		SELECT D."����", D."����" AS "���������", T."���" AS "�������", D."���", COALESCE(T."�����������", '')::VARCHAR(20), D."�����", D."�����������", D."�����", P."������", cAcc AS "������", 0::numeric(10,2) AS "�������", SUM(COALESCE(P."�����", 0))::numeric(10,2) AS "�������", ''::VARCHAR(15) AS "C�����", ''::VARCHAR(15) AS "C������"
		FROM "��������" P INNER JOIN "���������" D ON P."������"=D."���" 
        		        INNER JOIN "�����" T ON P."����" = T."����" AND T."�����" = 1
		WHERE P."������" = cAcc AND P."������" <> cAcc AND P."�����" <> 0 AND D."����" >= dDate1 AND D."����" < dDate2
		GROUP BY D."����", D."����", T."���", D."���", T."�����������", D."�����", D."�����������", D."�����", P."������"
		ORDER BY "����" LOOP

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
	SELECT to_date(cDate1, 'DD.MM.YYYY') AS ����, NULL AS ���������, '' AS �������, '' AS ������, '' AS ��������, '' AS �����, '' AS �����������, 0 AS �����, '' AS ������, '' AS ������,
       		����� = CASE
               			WHEN S.������ > 0 THEN S.������
               			ELSE 0
               		END,
       		������ = CASE
                		WHEN S.������ < 0 THEN -S.������
                		ELSE 0
                	END, '             ' AS ������, '             ' AS �������
	FROM (SELECT (S.������ + COALESCE(P1.�����, 0) - COALESCE(P2.�����, 0)) AS ������ 
       	      FROM (SELECT SUM(������) AS ������ 
		    FROM ������ 
		    WHERE ���� = cAcc) S,
	           (SELECT SUM(COALESCE(P.�����, 0)) AS ����� 
                    FROM �������� P INNER JOIN ��������� D ON P.������=D.��� 
                    WHERE P.������ = cAcc AND to_date(D.����, 'DD.MM.YYYY') < to_date(cDate1, 'DD.MM.YYYY')) P1,
                   (SELECT SUM(COALESCE(P.�����, 0)) AS ����� 
                    FROM �������� P INNER JOIN ��������� D ON P.������=D.��� 
	            WHERE P.������ = cAcc AND to_date(D.����, 'DD.MM.YYYY') < to_date(cDate1, 'DD.MM.YYYY')) P2
              ) S
	UNION
	SELECT D.����, D.���� AS ���������, T.��� AS �������, D.���, COALESCE(T.�����������, ''), D.�����, D.�����������, D.�����, cAcc AS ������, P.������, SUM(COALESCE(P.�����, 0)) AS �����, 0 AS ������, '             ', '             '
	FROM �������� P INNER JOIN ��������� D ON P.������=D.��� 
                        INNER JOIN ����� T ON P.���� = T.���� AND T.����� = 1
	WHERE P.������ = cAcc AND (P.����� <> 0) AND (to_date(D.����, 'DD.MM.YYYY') >= to_date(cDate1, 'DD.MM.YYYY')) AND (to_date(D.����, 'DD.MM.YYYY') < to_date(cDate2, 'DD.MM.YYYY') + 1)
	GROUP BY D.����, D.����, T.���, D.���, T.�����������, D.�����, D.�����������, D.�����, P.������
	UNION
	SELECT D.����, D.���� AS ���������, T.��� AS �������, D.���, COALESCE(T.�����������, ''), D.�����, D.�����������, D.�����, P.������, cAcc AS ������, 0 AS �����, SUM(COALESCE(P.�����, 0)) AS ������, '             ', '             '
	FROM �������� P INNER JOIN ��������� D ON P.������=D.��� 
                        INNER JOIN ����� T ON P.���� = T.���� AND T.����� = 1
	WHERE P.������ = cAcc AND (P.����� <> 0) AND (to_date(D.����, 'DD.MM.YYYY') >= to_date(cDate1, 'DD.MM.YYYY')) AND (to_date(D.����, 'DD.MM.YYYY') < to_date(cDate2, 'DD.MM.YYYY') + 1)
	GROUP BY D.����, D.����, T.���, D.���, T.�����������, D.�����, D.�����������, D.�����, P.������
	ORDER BY ����;
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
	IF (SELECT ���������� FROM ����� WHERE ���� = cAcc) = TRUE THEN		-- ���� ��� ����� ����� ���� �������������� ����, �� � ��������� ������� ������ �� ����� ������ � ��������� ��� ���������� ������ �������
		FOR ret_row IN
			SELECT  dDate1 AS ����, 0 AS ���������, ''::VARCHAR(100) AS �������, 0 AS ������, ''::VARCHAR(20) AS ��������, ''::VARCHAR(10) AS �����, 0 AS ���, ''::VARCHAR(100) AS �����������, 0 AS �����, '' AS ������, '' AS ������,
	       			CASE
             				WHEN S.��� > 0 THEN S.���
		               		ELSE 0::NUMERIC(10, 3)
		               	END AS �����,
	       			CASE
             				WHEN S.������ > 0 THEN S.������
		               		ELSE 0::NUMERIC(10, 2)
        	     		END AS �����,
	       			CASE
             				WHEN S.��� < 0 THEN -S.���
	               			ELSE 0::NUMERIC(10, 3)
	             		END AS �����,
		       		CASE
             				WHEN S.������ < 0 THEN -S.������
	                		ELSE 0::NUMERIC(10, 2)
             			END AS ������, ''::VARCHAR(15) AS ������, ''::VARCHAR(15) AS ������, ''::VARCHAR(15) AS ������, ''::VARCHAR(15) AS �������
			FROM (SELECT (S.��� + P1.��� - P2.���) AS ���, (S.������ + P1.����� - P2.�����) AS ������ 
			      FROM (SELECT ���, ���, ������ 
				    FROM ������ 
				    WHERE ���� = cAcc AND ��� = nObj) S,
				   (SELECT SUM(P.���) AS ���, SUM(P.�����) AS ����� 
             		            FROM (SELECT p.��� AS ���, p.���, p.�����
					  FROM �������� P INNER JOIN (SELECT ��� 
								      FROM ��������� 
								      WHERE ���� < dDate1) D ON P.������=D.���
	                            	  WHERE P.������ = cAcc AND P.����� = nObj
					  UNION
				    	  SELECT 0 AS ���, 0 AS ���, 0 AS �����) p) P1,
             			   (SELECT SUM(P.���) AS ���, SUM(P.�����) AS ����� 
                        	    FROM (SELECT p.��� AS ���, p.���, p.�����
					  FROM �������� P INNER JOIN (SELECT ��� 
								      FROM ��������� 
								      WHERE ���� < dDate1) D ON P.������=D.���
					  WHERE P.������ = cAcc AND P.����� = nObj
					  UNION
					  SELECT 0 AS ���, 0 AS ���, 0 AS �����) p) P2
		              ) S
			UNION
			SELECT D.����, D.���� AS ���������, T.��� AS �������, D.���, T.����������� AS ��������, D.�����, P.���, D.�����������, D.�����, cAcc AS ������, P.������, SUM(P.���) AS �����, SUM(P.�����) AS �����, 0 AS �����, 0 AS ������, '', '', '', ''
			FROM �������� P INNER JOIN ��������� D ON P.������=D.��� 
        	     		        INNER JOIN ����� T ON P.���� = T.���� AND T.����� = 1
			WHERE P.������ = cAcc AND P.����� = nObj AND D.���� >= dDate1 AND D.���� < dDate2
			GROUP BY D.����, D.����, T.���, D.���, T.�����������, D.�����, P.���, D.�����������, D.�����, P.������
			UNION
			SELECT D.����, D.���� AS ���������, T.��� AS �������, D.���, T.����������� AS ��������, D.�����, P.���, D.�����������, D.�����, P.������, cAcc AS ������, 0 AS �����, 0 AS �����, SUM(P.���) AS �����, SUM(P.�����) AS ������, '', '', '', ''
			FROM �������� P INNER JOIN ��������� D ON P.������=D.��� 
             	        	        INNER JOIN ����� T ON P.���� = T.���� AND T.����� = 1
			WHERE P.������ = cAcc AND P.����� = nObj AND D.���� >= dDate1 AND D.���� < dDate2
			GROUP BY D.����, D.����, T.���, D.���, T.�����������, D.�����, P.���, D.�����������, D.�����, P.������
			ORDER BY ����, ����� LOOP
			RETURN NEXT ret_row;
		END LOOP;
	ELSE
		FOR ret_row IN
			SELECT  dDate1 AS ����, 0 AS ���������, ''::VARCHAR(100) AS �������, 0 AS ������, ''::VARCHAR(20) AS ��������, ''::VARCHAR(10) AS �����, 0 AS ���, ''::VARCHAR(100) AS �����������, 0 AS �����, '' AS ������, '' AS ������,
		       		CASE
             				WHEN S.��� > 0 THEN S.���
	               			ELSE 0::NUMERIC(10, 3)
		               	END AS �����,
		       		CASE
             				WHEN S.������ > 0 THEN S.������
	               			ELSE 0::NUMERIC(10, 2)
	             		END AS �����,
		       		CASE
             				WHEN S.��� < 0 THEN -S.���
	               			ELSE 0::NUMERIC(10, 3)
	             		END AS �����,
		       		CASE
             				WHEN S.������ < 0 THEN -S.������
	                		ELSE 0::NUMERIC(10, 2)
	             		END AS ������, ''::VARCHAR(15) AS ������, ''::VARCHAR(15) AS ������, ''::VARCHAR(15) AS ������, ''::VARCHAR(15) AS �������
			FROM (SELECT (S.��� + P1.��� - P2.���) AS ���, (S.������ + P1.����� - P2.�����) AS ������ 
			      FROM (SELECT ���, ���, ������ 
				    FROM ������ 
				    WHERE ���� = cAcc AND ��� = nObj) S,
				   (SELECT SUM(P.���) AS ���, SUM(P.�����) AS ����� 
             		            FROM (SELECT p.���, p.���, p.�����
					  FROM �������� P INNER JOIN (SELECT ��� 
								      FROM ��������� 
								      WHERE ���� < dDate1) D ON P.������=D.���
	                            	  WHERE P.������ = cAcc AND P.����� = nObj
					  UNION
				    	  SELECT 0 AS ���, 0 AS ���, 0 AS �����) p) P1,
             			   (SELECT SUM(P.���) AS ���, SUM(P.�����) AS ����� 
                        	    FROM (SELECT p.���, p.���, p.�����
					  FROM �������� P INNER JOIN (SELECT ��� 
								      FROM ��������� 
								      WHERE ���� < dDate1) D ON P.������=D.���
					  WHERE P.������ = cAcc AND P.����� = nObj
					  UNION
					  SELECT 0 AS ���, 0 AS ���, 0 AS �����) p) P2
		              ) S
			UNION
			SELECT D.����, D.���� AS ���������, T.��� AS �������, D.���, T.����������� AS ��������, D.�����, 0 AS ���, D.�����������, D.�����, cAcc AS ������, P.������, SUM(P.���) AS �����, SUM(P.�����) AS �����, 0 AS �����, 0 AS ������, '', '', '', ''
			FROM �������� P INNER JOIN ��������� D ON P.������=D.���
             	        	        INNER JOIN ����� T ON P.���� = T.���� AND T.����� = 1
			WHERE P.������ = cAcc AND P.����� = nObj AND D.���� >= dDate1 AND D.���� < dDate2
			GROUP BY D.����, D.����, T.���, D.���, T.�����������, D.�����, D.�����������, D.�����, p.������
			UNION
			SELECT D.����, D.���� AS ���������, T.��� AS �������, D.���, T.����������� AS ��������, D.�����, 0 AS ���, D.�����������, D.�����, P.������, cAcc AS ������, 0 AS �����, 0 AS �����, SUM(P.���) AS �����, SUM(P.�����) AS ������, '', '', '', ''
			FROM �������� P INNER JOIN ��������� D ON P.������=D.���
             		                INNER JOIN ����� T ON P.���� = T.���� AND T.����� = 1
			WHERE P.������ = cAcc AND P.����� = nObj AND D.���� >= dDate1 AND D.���� < dDate2
			GROUP BY D.����, D.����, T.���, D.���, T.�����������, D.�����, D.�����������, D.�����, p.������
			ORDER BY ����, ���������, ����� LOOP
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
-- cComm1 - ������ select �������
-- cComm2 - ������ order �������
-- cAcc - ������������� ����
-- dDate1 - ��������� ����
-- dDate2 - �������� ����
DECLARE ret_row RECORD;
	dDate1 DATE;
	dDate2 DATE;
BEGIN
	dDate1 := to_date(cDate1, 'DD.MM.YYYY');
	dDate2 := to_date(cDate2, 'DD.MM.YYYY') + 1;
	
	FOR ret_row IN
		SELECT *
		FROM (SELECT S.���, COALESCE(S.���, 0)::NUMERIC(10, 3) AS ���, COALESCE(S.������, 0)::NUMERIC(10, 2) AS ������, COALESCE(P1.���, 0)::NUMERIC(10, 3) AS �����, COALESCE(P1.�����, 0)::NUMERIC(10, 2) AS �����, COALESCE(P2.���, 0)::NUMERIC(10, 3) AS �����, COALESCE(P2.�����, 0)::NUMERIC(10, 2) AS ������, (COALESCE(S.���, 0) + COALESCE(P1.���, 0) - COALESCE(P2.���, 0))::NUMERIC(10, 3) AS ������, (COALESCE(S.������, 0) + COALESCE(P1.�����, 0) - COALESCE(P2.�����, 0))::NUMERIC(10, 2) AS ���������, 
			''::VARCHAR(15) AS C���, ''::VARCHAR(15) AS C������, ''::VARCHAR(15) AS C�����, ''::VARCHAR(15) AS C�����, ''::VARCHAR(15) AS C�����, ''::VARCHAR(15) AS C������, ''::VARCHAR(15) AS C������, ''::VARCHAR(15) AS C���������
 		      FROM (SELECT S.���, (S.��� + COALESCE(P1.���, 0) - COALESCE(P2.���, 0)) AS ���, (S.������ + COALESCE(P1.�����, 0) - COALESCE(P2.�����, 0)) AS ������
                	    FROM (SELECT ���, COALESCE(���, 0) AS ���, ������ FROM ������ WHERE ���� = cAcc
                    		 ) S LEFT JOIN (SELECT P.����� AS ���, SUM(COALESCE(P.���, 0)) AS ���, SUM(COALESCE(P.�����, 0)) AS �����
			        	   	FROM �������� P INNER JOIN (SELECT ��� FROM ��������� WHERE ���� < dDate1) D ON P.������=D.���
					   	WHERE P.������ = cAcc
					   	GROUP BY P.�����) P1 ON S.��� = P1.���
			             LEFT JOIN (SELECT P.����� AS ���, SUM(COALESCE(P.���, 0)) AS ���, SUM(COALESCE(P.�����, 0)) AS �����
		        	           	FROM �������� P INNER JOIN (SELECT ��� FROM ��������� WHERE ���� < dDate1) D ON P.������=D.���
			        	   	WHERE P.������ = cAcc
		        	   		GROUP BY P.�����) P2 ON S.��� = P2.���
                    	    ) S LEFT JOIN (SELECT P.����� AS ���, SUM(COALESCE(P.���, 0)) AS ���, SUM(COALESCE(P.�����, 0)) AS �����
                         		   FROM �������� P INNER JOIN (SELECT ��� FROM ��������� WHERE ���� >= dDate1 AND ���� < dDate2) D ON P.������=D.���
                                	   WHERE P.������ = cAcc
                            		   GROUP BY P.�����
	                           	  ) P1 ON S.��� = P1.���
        	        	LEFT JOIN (SELECT P.����� AS ���, SUM(COALESCE(P.���, 0)) AS ���, SUM(COALESCE(P.�����, 0)) AS �����
					   FROM �������� P INNER JOIN (SELECT ��� FROM ��������� WHERE ���� >= dDate1 AND ���� < dDate2) D ON P.������=D.���
                        	   	   WHERE P.������ = cAcc
                                   	   GROUP BY P.�����
                                   	   ) P2 ON S.��� = P2.���
      	     	) S
		WHERE ��� <> 0 OR ������ <> 0 OR ����� <> 0 OR ����� <> 0 OR ����� <> 0 OR ������ <> 0 OR ������ <> 0 OR ��������� <> 0 
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
	cSetName = (SELECT �������������� FROM ����� WHERE ���� = cAcc);
	cSetName = RTRIM(cSetName);

	IF (SELECT COUNT(*) FROM vw_columns WHERE ������� = cSetName AND ������� = '���') = 1			-- ���� ���� ���� ���� ���
		AND (SELECT COUNT(*) FROM vw_columns WHERE ������� = cSetName AND ������� = '���') = 1	THEN 	-- � ���� ���� ���
		-- �� ����������, ��� ��� ������� ������������ ������������, ������� ���������� �� ������� �����
		-- ������� ��������
		SELECT sp_CalcObjOborot(cAcc, nObj, cDate1, cDate2);
	ELSE
		-- �� ����������, ��� ��� ������� ������������ ������� ������������
		IF (SELECT COUNT(*) FROM vw_columns WHERE ������� = cSetName AND ������� = '���') = 1				-- ���� ���� ���� ���� ���
		AND (SELECT COUNT(*) FROM vw_columns WHERE ������� = cSetName AND ������� = '���_' + cDictName) = 1 THEN	-- � ���� ���� �� ������� �� ����������
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
	nOperNum := (SELECT "����" FROM "���������" WHERE "���" = ndocid LIMIT 1);
	DELETE FROM "���������" WHERE "���" = nDocId;
	DELETE FROM "��������" WHERE "������" = nDocId;
	cAttrName = '��������' || rtrim(ltrim(cast(nOperNum AS VARCHAR(10))));
	IF (SELECT COUNT(*) FROM pg_tables WHERE schemaname='public' AND tablename = cAttrName) > 0 THEN
		EXECUTE 'DELETE FROM ' || cAttrName || ' WHERE "������"=$1;' USING ndocid;
	END IF;
	cAttrName = '�����������' || rtrim(ltrim(cast(nOperNum AS VARCHAR(10))));
	IF (SELECT COUNT(*) FROM pg_tables WHERE schemaname='public' AND tablename = cAttrName) > 0 THEN
		EXECUTE 'DELETE FROM ' || cAttrName || ' WHERE "���"=$1;' USING ndocid;
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
	nOper := (SELECT "����" FROM "���������" WHERE "���" = nDocId);
	nFreeOper := (SELECT "�����" FROM "�����" WHERE "����" = nOper AND "���������" = true);
	IF nFreeOper IS NOT NULL THEN
		IF (SELECT "���" FROM "��������" WHERE "������" = nDocId AND "���������" = nFreeOper LIMIT 1) = nDocStr THEN
			nNewDocStr := (SELECT MIN("���") FROM "��������" WHERE "������" = nDocId AND "����" = nOper AND "���" <> nDocStr);
			IF nNewDocStr IS NOT NULL AND nNewDocStr <> nDocStr THEN
				cDbAcc := (SELECT "������" FROM "�����" WHERE "����" = nOper AND "���������" = true);			
				cCrAcc := (SELECT "������" FROM "�����" WHERE "����" = nOper AND "���������" = true);			
				INSERT INTO "��������" ("������", "���", "����", "���������", "������", "�����", "������", "�����") 
					VALUES (nDocId, nNewDocStr, nOper, nFreeOper, cDbAcc, 0, cCrAcc, 0);
			END IF;
	
		END IF;
	END IF;
	DELETE FROM "��������" WHERE "������" = nDocId AND "���" = nDocStr;
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
cNumName "����������"."���"%TYPE;		-- ������������ ����������
	nValue "����������"."��������"%TYPE;	-- �������� ����������
	dDate DATE;				-- ���� ���������
	nDocId "���������"."���"%TYPE;
	cNumber "���������"."�����"%TYPE;			
BEGIN
	cNumName := RTRIM((SELECT "���������" FROM "�����" WHERE "����" = nOper AND "�����" = 1 LIMIT 1));	-- �������� ������������ ����������
	IF cNumName IS NOT NULL AND char_length(cNumName) > 0 THEN
		nValue := (SELECT "��������" FROM "����������" WHERE RTRIM("���") = cNumName LIMIT 1);	-- ������� ����� �������� ����������
		nValue := nValue + 1;
		UPDATE "����������" SET "��������" = nValue WHERE RTRIM("���") = cNumName;		-- �������� ����� �������� ����������
		cNumber := trim(leading from to_char(nValue, '999999999'));
	ELSE
		cNumber := '';
	END IF;
	IF cDate IS NULL THEN
		dDate = CURRENT_DATE;
	ELSE
		dDate = to_date(cDate, 'DD.MM.YYYY');
	END IF;
	INSERT INTO "���������" ("����", "���������", "����", "�����", "����") VALUES (dDate, current_timestamp, nOper, cNumber, 0) RETURNING "���" INTO nDocId;
	IF (SELECT COUNT(*) FROM "�����" WHERE "����" = nOper AND "�����������" = TRUE) > 0 THEN
		EXECUTE 'INSERT INTO "�����������' || rtrim(ltrim(cast(nOper AS VARCHAR(10)))) || '" ("���") VALUES ($1);' USING nDocId;
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
	IF (SELECT COUNT(*) FROM "�����" WHERE "����" = noper AND "�����" = 0 AND "��������" = TRUE) > 0 THEN
		EXECUTE 'SELECT max("���") FROM "��������' || rtrim(ltrim(cast(noper AS VARCHAR(10)))) || '"' INTO nDocStr;
		IF nDocStr IS NULL THEN
			nDocStr := 1;
		ELSE
			nDocStr := nDocStr + 1;
		END IF;
		WHILE nCount > 0 LOOP
			-- ��������, �� ���������� �� �������� ������� ���������, � ���� ����������, �� ������� ������ � ������� ���������
			EXECUTE 'SELECT COUNT(*) FROM "��������' || rtrim(ltrim(cast(noper AS VARCHAR(10)))) || '" WHERE "������" = $1 AND "���" = $2;' INTO nCount1 USING nDocId, nDocStr;
			IF nCount1 = 0 THEN
				EXECUTE 'INSERT INTO "��������' || rtrim(ltrim(cast(noper AS VARCHAR(10)))) || '" ("������", "���") VALUES ($1, $2);' USING nDocId, nDocStr;
			END IF;
			nCount := nCount - 1;
		END LOOP;
	ELSE
		IF nDocStr IS NULL OR nDocStr = 0 THEN
			-- ������ ���������� "�����" ������ � ���������
			nDocStr := (SELECT max(p."���") AS max_value FROM "��������" p WHERE p."������" = nDocId AND p."����" = noper);
			IF nDocStr IS NULL THEN
				nDocStr := 1;
			ELSE
				nDocStr := nDocStr + 1;
			END IF;
		END IF;
		-- ������� � �������� �������� ��� ����� ������
		OPEN curResult FOR SELECT "������", "������", "�����", "���������"  FROM "�����" WHERE "����" = noper ORDER BY "�����";
		WHILE nCount > 0 LOOP
			-- ��������, �� ���������� �� �������� ������� ���������, � ���� ����������, �� ������� ������ � ������� ���������
			IF (SELECT COUNT(*) FROM "�����" WHERE "����" = noper AND "�����" = 1 AND "��������" = TRUE) > 0 THEN
				EXECUTE 'INSERT INTO "��������' || rtrim(ltrim(cast(noper AS VARCHAR(10)))) || '" ("������", "���") VALUES ($1, $2);' USING nDocId, nDocStr;
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
					nFreeCount := (SELECT count(*) FROM "��������" p WHERE p."������" = nDocId AND p."����" = noper AND p."���������" = nNum);
					IF nFreeCount = 0 THEN
						INSERT INTO "��������" ("������", "���", "����", "���������", "������", "�����", "������", "�����", "���", "����", "�����") VALUES (nDocId, nDocStr, noper, nNum, cDbAcc, nDbId, cCrAcc, nCrId, nQuan, nPrice, nSum);
					END IF;
				ELSE
					INSERT INTO "��������" ("������", "���", "����", "���������", "������", "�����", "������", "�����", "���", "����", "�����") VALUES (nDocId, nDocStr, noper, nNum, cDbAcc, nDbId, cCrAcc, nCrId, nQuan, nPrice, nSum);
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
	cSetName = (SELECT �������������� FROM ����� WHERE ���� = cAcc);
	cSetName = RTRIM(cSetName);

	cCommand = 'SELECT ��� FROM ' || cSetName || ' WHERE ���_' || cDictName || '=' || RTRIM(LTRIM(CAST(nObj AS VARCHAR(20))));
	cCommand = 'SELECT ����, ���������, �������, ������, ������, SUM(�����) AS �����, SUM(�����) AS �����, SUM(�����) AS �����, SUM(������) AS ������ '
		 || 'FROM (SELECT to_date("' || cDate1 || '", "DD.MM.YYYY") AS ����, 0 AS ���������, "" AS �������, "" AS ������, "" AS ������, '
			       || '����� = CASE '
			               || 'WHEN S.��� > 0 THEN S.��� '
	        		       || 'ELSE 0 '
			               || 'END, '
			       || '����� = CASE '
        			       || 'WHEN S.������ > 0 THEN S.������ '
			               || 'ELSE 0 '
			               || 'END, '
			       || '����� = CASE '
			               || 'WHEN S.��� < 0 THEN -S.��� '
        			       || 'ELSE 0 '
			               || 'END, '
			       || '������ = CASE '
	        		        || 'WHEN S.������ < 0 THEN -S.������ '
			                || 'ELSE 0 '
			                || 'END '
			 || 'FROM (SELECT (S.��� + COALESCE(P1.���, 0) - COALESCE(P2.���, 0)) AS ���, (S.������ + COALESCE(P1.�����, 0) - COALESCE(P2.�����, 0)) AS ������ '
 		        	     || 'FROM (SELECT ���, COALESCE(���, 0) AS ���, COALESCE(������, 0) AS ������ '
				     || 'FROM ������ WHERE ���� = "' || cAcc || '" AND ��� IN (' || cCommand || ') '
     		        		             || ') S LEFT OUTER JOIN (SELECT P.����� AS ���, SUM(COALESCE(P.���, 0)) AS ���, SUM(COALESCE(P.�����, 0)) AS ����� '
     	               		        		                  || 'FROM �������� P INNER JOIN ��������� D ON P.������=D.��� '
                	                       		        		  || 'WHERE P.������ = "' || cAcc || '" AND COALESCE(P.�����, 0) IN (' || cCommand || ') AND to_date(D.����, "DD.MM.YYYY") < to_date("' || cDate1 || '", "DD.MM.YYYY") '
	                	                                       		  || 'GROUP BY P.�����) P1 ON S.��� = P1.��� '
			        	                     	 || 'LEFT OUTER JOIN (SELECT P.����� AS ���, SUM(COALESCE(P.���, 0)) AS ���, SUM(COALESCE(P.�����, 0)) AS ����� '
	               				                                  || 'FROM �������� P INNER JOIN ��������� D ON P.������=D.��� '
        	                				                  || 'WHERE P.������ = "' || cAcc || '" AND COALESCE(P.�����, 0) IN (' || cCommand || ') AND to_date(D.����, "DD.MM.YYYY") < to_date("' || cDate1 || '", "DD.MM.YYYY") '
				                                		  || 'GROUP BY P.�����) P2 ON S.��� = P2.��� '
				     		      || ') S '
						|| 'UNION '
						|| 'SELECT D.��������� AS ����, D.���� AS ���������, T.��� AS �������, "' || cAcc || '" AS ������, P.������, COALESCE(P.���, 0) AS �����, COALESCE(P.�����, 0) AS �������, 0 AS �����, 0 AS ������� '
						|| 'FROM �������� P INNER JOIN ��������� D ON P.������=D.��� '
               							               || 'INNER JOIN ����� T ON P.���� = T.���� AND T.����� = 1 '
						|| 'WHERE P.������ <> P.������ AND P.������ = "' || cAcc || '" AND P.����� IN (' || cCommand || ') AND (P.��� <> 0 OR P.����� <> 0) AND (to_date(D.����, "DD.MM.YYYY") >= to_date("' || cDate1 || '", "DD.MM.YYYY")) AND (to_date(D.����, "DD.MM.YYYY") < to_date("' || cDate2 || '", "DD.MM.YYYY") + 1) '
						|| 'UNION '
						|| 'SELECT D.��������� AS ����, D.���� AS ���������, T.��� AS �������, P.������, "' || cAcc || '" AS ������, 0 AS �����, 0 AS �������, COALESCE(P.���, 0) AS �����, COALESCE(P.�����, 0) AS ������� '
						|| 'FROM �������� P INNER JOIN ��������� D ON P.������=D.��� '
               							               || 'INNER JOIN ����� T ON P.���� = T.���� AND T.����� = 1 '
						|| 'WHERE P.������ <> P.������ AND P.������ = "' || cAcc || '" AND P.����� IN (' || cCommand || ') AND (P.��� <> 0 OR P.����� <> 0) AND (to_date(D.����, "DD.MM.YYYY") >= to_date("' || cDate1 || '", "DD.MM.YYYY")) AND (to_date(D.����, "DD.MM.YYYY") < to_date("' || cDate2 || '", "DD.MM.YYYY") + 1) '
						|| ') S '
					|| 'GROUP BY ����, ���������, �������, ������, ������';
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
	NEW."FTS" = to_tsvector(lower(NEW.��� || ' ' || NEW.���1));
	RETURN NEW;
END;
$$;


ALTER FUNCTION public.synonymtsvectorupdate() OWNER TO sa;

--
-- TOC entry 24 (class 1255 OID 71808)
-- Dependencies: 435 6
-- Name: testdeleting_������(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION "testdeleting_������"() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
DECLARE 
	cAcc VARCHAR(20);
	nId INTEGER;
BEGIN
	IF (SELECT COUNT(*) FROM "��������" WHERE ("������" = OLD."����" AND "�����" = OLD."���") OR ("������" = OLD."����" AND "�����" = OLD."���")) > 0 THEN
		RAISE EXCEPTION '��������� ������� ������, �.�. ��� ��� ���� ������� ������������� ��������.';
	END IF;
	RETURN OLD;
END;
$$;


ALTER FUNCTION public."testdeleting_������"() OWNER TO sa;

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
	lError := FALSE;		-- ������� ��������, ��� ������� ������� �� ����������
	
	-- ��������, ���� �� ������ �� ���� ������ � ����� �� ������������
	cDict := LTRIM(RTRIM(UPPER(TG_RELNAME)));	-- ������� ��� ��������������� �����������
	nId := OLD."���";					-- � ������� ��� ��������� �������

	OPEN CurTables FOR
		SELECT DISTINCT t.RELNAME
		FROM pg_attribute C
			INNER JOIN (SELECT c.RELFILENODE, c.RELNAME
				    FROM pg_class c
				    WHERE c.RELNAME IN (SELECT TABLENAME FROM pg_tables WHERE SCHEMANAME = 'public')
				    ) t ON C.ATTRELID = t.RELFILENODE
		WHERE UPPER(c.ATTNAME) = '���_' || cDict;

	LOOP
		FETCH CurTables INTO cTable;
		IF NOT FOUND THEN
			EXIT;
		ELSE
			EXECUTE 'SELECT COUNT(*) FROM ' || cTable || ' WHERE ���_' || cDict || ' = ' || LTRIM(RTRIM(CAST(nId AS VARCHAR(20)))) INTO nCount;
			IF nCount > 0 THEN
				lError := TRUE;
				RAISE EXCEPTION '��������� ������� ������, �.�. �� ��� ������� ������ � ����������� <%>', cTable;
				EXIT;			
			END IF;
		END IF;
	END LOOP;

	CLOSE CurTables;

	IF NOT lError THEN	-- ���� ��� ��� ������� ������, �� ��������� ������
		OPEN CurAccounts FOR 
			SELECT "����" 
			FROM "�����" 
			WHERE LTRIM(RTRIM(UPPER("��������������"))) = cDict;
	
		LOOP
			FETCH CurAccounts INTO cAcc;
			IF NOT FOUND THEN
				EXIT;
			ELSE
				cAcc := RTRIM(cAcc);
				cCommand := 'FROM "��������" WHERE ("������" = ''' || cAcc || ''' AND "�����" = ' || LTRIM(RTRIM(CAST(nId AS VARCHAR(20)))) || ') OR ("������" = ''' || cAcc || ''' AND "�����" = ' || LTRIM(RTRIM(CAST(nId AS VARCHAR(20)))) || ')';
				EXECUTE 'SELECT COUNT(*) ' || cCommand INTO nCount;
				IF nCount > 0 THEN
					lError := TRUE;
					EXECUTE 'SELECT "������" ' || cCommand || ' ORDER BY "������" DESC LIMIT 1' INTO nDocId;
					EXECUTE 'SELECT "����" ' || cCommand || ' ORDER BY "������" DESC LIMIT 1' INTO OperId;
					cCommand := LTRIM(RTRIM(CAST(nDocId AS VARCHAR(20))));
					EXECUTE 'SELECT "����" FROM "���������" WHERE "���" = ' || cCommand INTO OperDate;
					EXECUTE 'SELECT "�����" FROM "���������" WHERE "���" = ' || cCommand INTO OperNum;
					EXECUTE 'SELECT "���" FROM "�����" WHERE "����" = ' || LTRIM(RTRIM(CAST(OperId AS VARCHAR(20)))) || ' AND "�����" = 1' INTO OperName;
					RAISE EXCEPTION '��������� ������� ������, �.�. ��� ��� ���� ������� �������� (% ��.). ��������� �������� <%> �� ��������� ����� <%> ���� ������� <%>.', nCount, RTRIM(OperName), RTRIM(OperNum), OperDate;
					EXIT;
				END IF;
			END IF;
		END LOOP;
		CLOSE CurAccounts;
	END IF;

	IF lError THEN
		RETURN NULL;	-- ������, ������� ������
	ELSE
		RETURN OLD;	-- ������ ���, ����� ������� ������
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
	lError := FALSE;		-- ������� ��������, ��� ������� ������� �� ����������

	-- ��������, ���� �� ������ �� ���� ������ � ����� �� ������������
	cDict := LTRIM(RTRIM(UPPER(TG_RELNAME)));	-- ������� ��� ��������������� �����������
	nId := OLD."���";				-- � ������� ��� ��������� �������

	OPEN CurTables FOR
		SELECT DISTINCT "�������"
		FROM vw_columns
		WHERE "�������" = '���_' || cDict;

	LOOP
		FETCH CurTables INTO cTable;
		IF NOT FOUND THEN
			EXIT;
		ELSE
			EXECUTE 'SELECT COUNT(*) FROM ' || cTable || ' WHERE "���_' || cDict || '" = ' || LTRIM(RTRIM(CAST(nId AS VARCHAR(20)))) INTO nCount;
			IF nCount > 0 THEN
				lError := TRUE;
				RAISE EXCEPTION '��������� ������� ������, �.�. �� ��� ������� ������ � ����������� <%>', cTable;
				EXIT;			
			END IF;
		END IF;
	END LOOP;

	CLOSE CurTables;

	IF NOT lError THEN	-- ���� ��� ��� ������� ������, �� ��������� ������
		OPEN CurAccounts FOR 
			SELECT "����" 
			FROM "�����" 
			WHERE UPPER("��������������") = cDict;
	
		LOOP
			FETCH CurAccounts INTO cAcc;
			IF NOT FOUND THEN
				EXIT;
			ELSE
				cAcc := RTRIM(cAcc);
				EXECUTE 'SELECT COUNT(*) FROM "��������" WHERE ("������" = cAcc AND "�����" = nId) OR ("������" = cAcc AND "�����" = nId)' INTO nCount;
				IF nCount > 0 THEN
					lError := TRUE;
					EXECUTE 'SELECT TOP 1 "������" FROM "��������" WHERE ("������" = cAcc AND "�����" = nId) OR ("������" = cAcc AND "�����" = nId) ORDER BY "������" DESC' INTO DocId;
					EXECUTE 'SELECT TOP 1 "����" FROM "��������" WHERE ("������" = cAcc AND "�����" = nId) OR ("������" = cAcc AND "�����" = nId) ORDER BY "������" DESC' INTO OperId;
					RAISE EXCEPTION '��������� ������� ������, �.�. ��� ��� ���� ������� �������� (% ��.). ��������� �������� <> �� ��������� ����� <> ���� ������� <>.', nCount;
					EXIT;
				END IF;
			END IF;
		END LOOP;
		CLOSE CurAccounts;
	END IF;

	IF lError THEN
		RETURN NULL;	-- ������, ������� ������
	ELSE
		RETURN OLD;	-- ������ ���, ����� ������� ������
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
	IF (OLD."���" <> NEW."���") OR (OLD."������" <> NEW."������") OR (OLD."���" <> NEW."���") THEN
		RAISE EXCEPTION '��������� �������� �������� ��������� �������';
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
	IF (OLD."���" <> NEW."���") THEN
		RAISE EXCEPTION '��������� �������� �������� ��������� �������';
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
	IF OLD."���" <> NEW."���" THEN
		RAISE EXCEPTION '��������� �������� �������� ��������� �������';
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
	NEW."fts" = to_tsvector(lower(replace(replace(replace(trim(NEW."���") || ' ' || trim(NEW."�������"), '-', ' '), ',', ' '), '.', ' ')));
	RETURN NEW;
END;
$$;


ALTER FUNCTION public.tsvectorupdate() OWNER TO sa;

--
-- TOC entry 33 (class 1255 OID 71815)
-- Dependencies: 6 435
-- Name: ����������������(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION "����������������"() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	IF (SELECT "�������" FROM "�����" WHERE "����" = NEW."����" AND "�����" = 1) = '1' THEN			-- ���� ��� �������� ���������
		IF char_length(NEW."������") > 0 AND (SELECT "������" FROM "�����" WHERE "����" = NEW."������") = '1' THEN		-- ���� ���� ������ � ��� �� ������������ ����
			IF (SELECT COUNT(*) FROM "�����" WHERE "����" = NEW."������") = 0 THEN			-- ���� �� ���������� ������ �����
				INSERT INTO "�����" ("����") VALUES (NEW."������");					-- �� ������� ���. �������� ����� ������ ������������ �����
			END IF;
			IF (SELECT COUNT(*) FROM "������" WHERE "����" = NEW."������" AND "���" = NEW."�����") = 0 THEN
				INSERT INTO "������" ("����", "���")  VALUES (NEW."������", NEW."�����");
			END IF;
			UPDATE "������"					-- ... � ������ �����
				SET "�����" = "�����" + NEW."���", 
					"�����" = "�����" + NEW."�����"
				WHERE "����" = NEW."������" AND "���" = NEW."�����";
		END IF;
		IF char_length(NEW."������") > 0 AND (SELECT "������" FROM "�����" WHERE "����" = NEW."������") = '1' THEN		-- ���� ���� ������ � ��� �� ������������ ����
			IF (SELECT COUNT(*) FROM "�����" WHERE "����" = NEW."������") = 0 THEN			-- ���� �� ���������� ������ �����
				INSERT INTO "�����" ("����") VALUES (NEW."������");					-- �� ������� ���. �������� ����� ������ ������������ �����
			END IF;
			IF (SELECT COUNT(*) FROM "������" WHERE "����" = NEW."������" AND "���" = NEW."�����") = 0 THEN
				INSERT INTO "������" ("����", "���")  VALUES (NEW."������", NEW."�����");
			END IF;
			UPDATE "������"					-- ... � ������ �����
				SET "�����" = "�����" + NEW."���", 
					"������" = "������" + NEW."�����"
				WHERE "����" = NEW."������" AND "���" = NEW."�����";
		END IF;
		RETURN NEW;
	ELSE
		RETURN NULL;
	END IF;
END;
$$;


ALTER FUNCTION public."����������������"() OWNER TO sa;

--
-- TOC entry 34 (class 1255 OID 71816)
-- Dependencies: 6 435
-- Name: ���������������������(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION "���������������������"() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	NEW."������" := NEW."���" + NEW."�����" - NEW."�����";
	NEW."���������" := NEW."������" + NEW."�����" - NEW."������";
	IF NEW."������" = 0 THEN
		NEW."�������" := NEW."���������";
	ELSE
		NEW."�������" := NEW."���������" / NEW."������";
	END IF;
	RETURN NEW;
END;
$$;


ALTER FUNCTION public."���������������������"() OWNER TO sa;

--
-- TOC entry 35 (class 1255 OID 71817)
-- Dependencies: 435 6
-- Name: ���������������(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION "���������������"() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	IF NOT (NEW."������" = NEW."������" AND NEW."�����" = NEW."�����") THEN    -- ���� ������ �� ���������� ��� �� ����
		-- ��, ������, �������� ��������� �� ������ ������� � ����� ������������ ����� ��������� �� ���������� � �� ����������� �������
		
		-- C������ ���������� �� ���������� �������	
		IF (OLD."������" = NEW."������") AND (OLD."�����" = NEW."�����") THEN	-- ������ �� ���������� ������ �� ����������
			UPDATE "������"
				SET "�����" = "�����" - OLD."���" + NEW."���", 
					"�����" = "�����" - OLD."�����" + NEW."�����"
				WHERE "����" = OLD."������" AND "���" = OLD."�����";
		ELSE
			UPDATE "������"						-- ������� ���������� ������ ����
				SET "�����" = "�����" - OLD."���", 
					"�����" = "�����" - OLD."�����"
				WHERE "����" = OLD."������" AND "���" = OLD."�����";
			IF char_length(NEW."������") > 0 AND (SELECT "������" FROM "�����" WHERE "����" = NEW."������") = '1' THEN	-- ���� ���� ������ � �� ������������ ����
				IF (SELECT COUNT(*) FROM "������" WHERE "����" = NEW."������" AND "���" = NEW."�����") = 0 THEN
					INSERT INTO "������" ("����", "���") VALUES (NEW."������", NEW."�����");
				END IF;
				UPDATE "������"
					SET "�����" = "�����" + NEW."���", 
						"�����" = "�����" + NEW."�����"
					WHERE "����" = NEW."������" AND "���" = NEW."�����";
			END IF;
		END IF;

		-- ������ ���������� �� ����������� �������	
		IF (OLD."������" = NEW."������") AND (OLD."�����" = NEW."�����") THEN	-- ������ �� ���������� ������ �� ����������
			UPDATE "������"
			          SET "�����" = "�����" - OLD."���" + NEW."���", 
				     "������" = "������" - OLD."�����" + NEW."�����"
				WHERE "����" = OLD."������" AND "���" = OLD."�����";
		ELSE
			UPDATE "������"						-- ������� ���������� ������ ����
				SET "�����" = "�����" - OLD."���", 
					"������" = "������" - OLD."�����"
				WHERE "����" = OLD."������" AND "���" = OLD."�����";
			IF char_length(NEW."������") > 0 AND (SELECT "������" FROM "�����" WHERE "����" = NEW."������") = '1' THEN	-- ���� ���� ������ � �� ������������ ����
				IF (SELECT COUNT(*) FROM "������" WHERE "����" = NEW."������" AND "���" = NEW."�����") = 0 THEN
					INSERT INTO "������" ("����", "���") VALUES (NEW."������", NEW."�����");
				END IF;
				UPDATE "������"
					SET "�����" = "�����" + NEW."���", 
						"������" = "������" + NEW."�����"
					WHERE "����" = NEW."������" AND "���" = NEW."�����";
			END IF;
		END IF;
	END IF;
	RETURN NEW;
END;
$$;


ALTER FUNCTION public."���������������"() OWNER TO sa;

--
-- TOC entry 36 (class 1255 OID 71818)
-- Dependencies: 6 435
-- Name: ���������������(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION "���������������"() RETURNS trigger
    LANGUAGE plpgsql
    AS $_$
DECLARE
	cAttrName VARCHAR (50);
BEGIN
	cAttrName = '�����������' || rtrim(ltrim(cast(OLD."����" AS VARCHAR(10))));
	IF (SELECT COUNT(*) FROM pg_tables WHERE schemaname='public' AND tablename = cAttrName) > 0 THEN
		EXECUTE 'DELETE FROM "' || cAttrName || '" WHERE "���"=$1;' USING OLD."���";
	END IF;

	DELETE FROM "��������" WHERE "������" = OLD."���";
	RETURN OLD;
END;
$_$;


ALTER FUNCTION public."���������������"() OWNER TO sa;

--
-- TOC entry 37 (class 1255 OID 71819)
-- Dependencies: 6 435
-- Name: ���������������(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION "���������������"() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	IF (SELECT "�������" FROM "�����" WHERE "����" = OLD."����" AND "�����" = 1) = '1' THEN				-- ���� ��� �������� ���������
		IF char_length(OLD."������") > 0 AND (SELECT "������" FROM "�����" WHERE "����" = OLD."������") = '1' THEN		-- ���� ���� ������ � ��� �� ������������ ����
			UPDATE "������"				
			          SET "�����" = "�����" - OLD."���",
				     "�����" = "�����" - OLD."�����"
				WHERE "����" = OLD."������" AND "���" = OLD."�����";
		END IF;
		IF char_length(OLD."������") > 0 AND (SELECT "������" FROM "�����" WHERE "����" = OLD."������") = '1' THEN		-- ���� ���� ������ � �� ������������ ����
			UPDATE "������"
			          SET "�����" = "�����" - OLD."���",
				     "������" = "������" - OLD."�����"
				WHERE "����" = OLD."������" AND "���" = OLD."�����";
		END IF;
	END IF;
	RETURN OLD;
END;
$$;


ALTER FUNCTION public."���������������"() OWNER TO sa;

--
-- TOC entry 19 (class 1255 OID 71820)
-- Dependencies: 435 6
-- Name: �����������������(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION "�����������������"() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	IF (OLD."���������") THEN
		RAISE EXCEPTION '��������� ������� ������, �.�. ��� ��������� ����������';
		RETURN NULL;
	END IF;
	RETURN OLD;
END;
$$;


ALTER FUNCTION public."�����������������"() OWNER TO sa;

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
    SELECT t.relname AS "�������", upper((c.attname)::text) AS "�������", s.typname AS "���" FROM ((pg_attribute c JOIN (SELECT c.relfilenode, c.relname FROM pg_class c WHERE ((c.relname IN (SELECT pg_tables.tablename FROM pg_tables WHERE (pg_tables.schemaname = 'public'::name))) OR (c.relname IN (SELECT pg_views.viewname FROM pg_views WHERE (pg_views.schemaname = 'public'::name))))) t ON ((c.attrelid = t.relfilenode))) JOIN pg_type s ON ((c.atttypid = s.oid))) WHERE (c.attnum > 0) ORDER BY t.relname, c.attnum;


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
    SELECT sp_calcaccoborot."����", sp_calcaccoborot."���������", sp_calcaccoborot."�������", sp_calcaccoborot."������", sp_calcaccoborot."��������", sp_calcaccoborot."�����", sp_calcaccoborot."�����������", sp_calcaccoborot."�����", sp_calcaccoborot."������", sp_calcaccoborot."������", sp_calcaccoborot."�����", sp_calcaccoborot."������", sp_calcaccoborot."������", sp_calcaccoborot."�������" FROM sp_calcaccoborot(('10'::character varying(5))::bpchar) sp_calcaccoborot("����", "���������", "�������", "������", "��������", "�����", "�����������", "�����", "������", "������", "�����", "������", "������", "�������");


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
    SELECT dummy.oid AS "���", dummy.typname AS "���", dummy.typname_orig AS "���", dummy.typlen AS "�����" FROM ((SELECT format_type(t.oid, NULL::integer) AS typname, t.typname AS typname_orig, CASE WHEN (t.typelem > (0)::oid) THEN t.typelem ELSE t.oid END AS elemoid, t.typlen, t.typtype, t.oid, nsp.nspname, ((SELECT count(1) AS count FROM pg_type t2 WHERE (t2.typname = t.typname)) > 1) AS isdup FROM (pg_type t JOIN pg_namespace nsp ON ((t.typnamespace = nsp.oid))) WHERE ((((((NOT ((t.typname = 'unknown'::name) AND (nsp.nspname = 'pg_catalog'::name))) AND t.typisdefined) AND (t.typtype = ANY (ARRAY['b'::"char", 'c'::"char", 'd'::"char", 'e'::"char"]))) AND (NOT (EXISTS (SELECT 1 FROM pg_class WHERE (((pg_class.relnamespace = t.typnamespace) AND (pg_class.relname = t.typname)) AND (pg_class.relkind <> 'c'::"char")))))) AND ((t.typname !~~ '_%'::text) OR (NOT (EXISTS (SELECT 1 FROM pg_class WHERE (((pg_class.relnamespace = t.typnamespace) AND (pg_class.relname = ("substring"((t.typname)::text, 2))::name)) AND (pg_class.relkind <> 'c'::"char"))))))) AND (nsp.nspname <> 'information_schema'::name)) UNION SELECT 'bigserial'::text AS text, 'bigserial'::text AS text, 0, 8, 'b'::"char" AS "char", 0, 'pg_catalog'::name AS name, false AS bool) UNION SELECT 'serial'::text AS text, 'serial'::text AS text, 0, 4, 'b'::"char" AS "char", 0, 'pg_catalog'::name AS name, false AS bool) dummy WHERE (dummy.typname !~~ '%[]%'::text) ORDER BY (dummy.nspname <> 'pg_catalog'::name), (dummy.nspname <> 'public'::name), dummy.nspname, dummy.oid;


ALTER TABLE public.vw_types OWNER TO sa;

--
-- TOC entry 1637 (class 1259 OID 71850)
-- Dependencies: 1985 1986 1987 1988 1989 1990 1991 1992 1993 6
-- Name: ������; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "������" (
    "����" character(5) NOT NULL,
    "���" integer,
    "���" numeric(10,3) DEFAULT 0,
    "������" numeric(10,2) DEFAULT 0,
    "�����" numeric(10,3) DEFAULT 0,
    "�����" numeric(10,2) DEFAULT 0,
    "�����" numeric(10,3) DEFAULT 0,
    "������" numeric(10,2) DEFAULT 0,
    "������" numeric(10,3) DEFAULT 0,
    "���������" numeric(10,2) DEFAULT 0,
    "�������" numeric(10,2) DEFAULT 0
);


ALTER TABLE public."������" OWNER TO sa;

--
-- TOC entry 1638 (class 1259 OID 71862)
-- Dependencies: 1994 1995 1996 1997 1998 1999 6
-- Name: �����; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "�����" (
    "���" integer NOT NULL,
    "���" character varying(100) DEFAULT ''::character varying,
    "����" character(5) DEFAULT ''::bpchar,
    "��������������" character varying(50) DEFAULT ''::character varying,
    "���������" boolean DEFAULT false,
    "����������" boolean DEFAULT false,
    "������" boolean DEFAULT true
);


ALTER TABLE public."�����" OWNER TO sa;

--
-- TOC entry 1639 (class 1259 OID 71871)
-- Dependencies: 1778 6
-- Name: vw_������; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_������" AS
    SELECT DISTINCT "�����"."���", "�����"."����", "�����"."���", COALESCE("��������"."�����������", (0)::numeric) AS "�����������", COALESCE("��������"."�����������", (0)::numeric) AS "�����������" FROM (("�����" LEFT JOIN (SELECT DISTINCT "������"."����", sum("������"."���������") AS "�����������" FROM "������" WHERE (("������"."���������" > (0)::numeric) AND (substr(("������"."����")::text, 1, 2) <> '00'::text)) GROUP BY "������"."����" ORDER BY "������"."����", sum("������"."���������")) "��������" ON (("�����"."����" = "��������"."����"))) LEFT JOIN (SELECT DISTINCT "������"."����", (- sum("������"."���������")) AS "�����������" FROM "������" WHERE (("������"."���������" < (0)::numeric) AND (substr(("������"."����")::text, 1, 2) <> '00'::text)) GROUP BY "������"."����" ORDER BY "������"."����", (- sum("������"."���������"))) "��������" ON (("�����"."����" = "��������"."����"))) ORDER BY "�����"."���", "�����"."����", "�����"."���", COALESCE("��������"."�����������", (0)::numeric), COALESCE("��������"."�����������", (0)::numeric);


ALTER TABLE public."vw_������" OWNER TO sa;

--
-- TOC entry 1640 (class 1259 OID 71876)
-- Dependencies: 2001 2002 6
-- Name: �����������; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "�����������" (
    "���" integer NOT NULL,
    "���" character varying(100) DEFAULT ''::character varying,
    "���������" date,
    "������" date NOT NULL,
    "�����" date NOT NULL,
    "������������" character varying(50) DEFAULT ''::character varying
);


ALTER TABLE public."�����������" OWNER TO sa;

--
-- TOC entry 1641 (class 1259 OID 71881)
-- Dependencies: 1779 6
-- Name: ������������; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "������������" AS
    SELECT pg_user.usesysid AS "���", pg_user.usename AS "���" FROM pg_user WHERE (pg_user.usename <> 'test'::name);


ALTER TABLE public."������������" OWNER TO sa;

--
-- TOC entry 1642 (class 1259 OID 71885)
-- Dependencies: 1780 6
-- Name: vw_�����������; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_�����������" AS
    SELECT u."���", u."���", COALESCE(b."���������", ('now'::text)::date) AS "���������", COALESCE(b."������", (('now'::text)::date - 31)) AS "������", COALESCE(b."�����", ('now'::text)::date) AS "�����" FROM ("������������" u LEFT JOIN "�����������" b ON (((b."������������")::name = u."���"))) WHERE (u."���" = "current_user"());


ALTER TABLE public."vw_�����������" OWNER TO sa;

--
-- TOC entry 1643 (class 1259 OID 71889)
-- Dependencies: 2004 2005 2006 6
-- Name: ���������; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "���������" (
    "���" integer NOT NULL,
    "����" date,
    "���������" timestamp without time zone,
    "�����" character varying(10) DEFAULT ''::character varying,
    "�����������" character varying(100) DEFAULT ''::character varying,
    "�����" numeric(10,2) DEFAULT 0,
    "��������" text,
    "����" integer,
    "����" integer,
    "����������1" text,
    "����������" bytea
);


ALTER TABLE public."���������" OWNER TO sa;

--
-- TOC entry 1644 (class 1259 OID 71898)
-- Dependencies: 1781 6
-- Name: vw_���������; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_���������" AS
    SELECT d."���", d."����", d."���������", d."�����", d."�����������", d."�����", d."����", d."����", d."��������" FROM ("���������" d JOIN "vw_�����������" b ON (((d."����" > (b."������" - 1)) AND (d."����" < (b."�����" + 1)))));


ALTER TABLE public."vw_���������" OWNER TO sa;

--
-- TOC entry 1645 (class 1259 OID 71902)
-- Dependencies: 2008 2009 2010 6
-- Name: ������; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "������" (
    "���" integer NOT NULL,
    "����" boolean DEFAULT true,
    "���_������������" integer,
    "���" character varying(100) DEFAULT ''::character varying,
    "������������" character varying(50),
    "�����������" boolean DEFAULT false
);


ALTER TABLE public."������" OWNER TO sa;

--
-- TOC entry 1646 (class 1259 OID 71908)
-- Dependencies: 1782 6
-- Name: vw_������; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_������" AS
    SELECT DISTINCT s."���", s."���_������������", s."����" FROM (SELECT rtrim((d."���")::text) AS "���", d."���_������������", (d."����" OR d."�����������") AS "����" FROM ("������" d JOIN "������������" p ON ((((rtrim((d."������������")::text))::name)::text = rtrim((p."���")::text)))) WHERE ((upper(rtrim((p."���")::text)) = upper(rtrim(("current_user"())::text))) OR (btrim(("current_user"())::text) = 'sa'::text)) ORDER BY d."���") s ORDER BY s."���", s."���_������������", s."����";


ALTER TABLE public."vw_������" OWNER TO sa;

--
-- TOC entry 1647 (class 1259 OID 71912)
-- Dependencies: 1783 6
-- Name: vw_������������; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_������������" AS
    SELECT pg_user.usesysid AS "���", pg_user.usename AS "���" FROM pg_user WHERE (pg_user.usename <> 'test'::name);


ALTER TABLE public."vw_������������" OWNER TO sa;

--
-- TOC entry 1648 (class 1259 OID 71916)
-- Dependencies: 2012 2013 2014 6
-- Name: ��������; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "��������" (
    "���" integer NOT NULL,
    "������" character(5) NOT NULL,
    "�����" integer NOT NULL,
    "������" character(5) NOT NULL,
    "�����" integer NOT NULL,
    "���" numeric(10,3) DEFAULT 0,
    "����" numeric(10,2) DEFAULT 0,
    "�����" numeric(10,2) DEFAULT 0,
    "���" integer NOT NULL,
    "������" integer NOT NULL,
    "����" numeric(3,0) NOT NULL,
    "���������" numeric(1,0) NOT NULL
);


ALTER TABLE public."��������" OWNER TO sa;

--
-- TOC entry 1649 (class 1259 OID 71922)
-- Dependencies: 1784 6
-- Name: vw_��������; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_��������" AS
    SELECT "��������"."���", "��������"."������", "��������"."�����", "��������"."������", "��������"."�����", "��������"."���", "��������"."����", "��������"."�����", "��������"."���", "��������"."������", "��������"."����", "��������"."���������" FROM "��������" WHERE ("��������"."������" IN (SELECT "vw_���������"."���" FROM "vw_���������"));


ALTER TABLE public."vw_��������" OWNER TO sa;

--
-- TOC entry 1650 (class 1259 OID 71926)
-- Dependencies: 2016 2017 2018 2019 2020 6
-- Name: �����������; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "�����������" (
    "���" integer NOT NULL,
    "���" character varying(100) DEFAULT ''::character varying,
    "����" character varying(100) DEFAULT ''::character varying,
    "���_�_������" character varying(100) DEFAULT ''::character varying,
    "���_�_�����" character varying(100) DEFAULT ''::character varying,
    "��������" character varying(100),
    "���������" boolean DEFAULT false
);


ALTER TABLE public."�����������" OWNER TO sa;

--
-- TOC entry 1651 (class 1259 OID 71934)
-- Dependencies: 2022 2023 2024 2025 2026 2027 2028 2029 2030 2031 2032 2033 2034 2035 2036 2037 2038 2039 2040 2041 2042 6
-- Name: �����; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "�����" (
    "���" integer NOT NULL,
    "����" integer,
    "�����" integer,
    "������" character varying(5) DEFAULT ''::character varying,
    "������" character varying(5) DEFAULT ''::character varying,
    "���" character varying(100) DEFAULT ''::character varying,
    "�����" character varying(1) DEFAULT ''::character varying,
    "����" boolean DEFAULT true,
    "�����������" character varying(20) DEFAULT ''::character varying,
    "���������" character varying(40) DEFAULT ''::character varying,
    "������������" boolean,
    "���" boolean DEFAULT false,
    "������" boolean DEFAULT false,
    "������" boolean DEFAULT false,
    "�������" boolean DEFAULT false,
    "�������" boolean DEFAULT false,
    "�������" boolean DEFAULT false,
    "�������" boolean DEFAULT false,
    "����������" boolean DEFAULT true,
    "����������" boolean DEFAULT true,
    "�������" boolean DEFAULT true,
    "�������" boolean DEFAULT true,
    "�����" character varying(50) DEFAULT ''::character varying,
    "���������" boolean DEFAULT false,
    "�������" boolean DEFAULT true,
    "����������" text,
    "��������" boolean,
    "�����������" boolean
);


ALTER TABLE public."�����" OWNER TO sa;

--
-- TOC entry 1652 (class 1259 OID 71961)
-- Dependencies: 1785 6
-- Name: vw_�����������_��_���������; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_�����������_��_���������" AS
    (SELECT s."���", s."���" FROM "�����������" s UNION SELECT (1000000 + "�����"."����") AS "���", ('����������������'::text || btrim((("�����"."����")::character varying(20))::text)) AS "���" FROM "�����" WHERE ("�����"."�����" = 1)) UNION SELECT (2000000 + "�����"."����") AS "���", ('��������'::text || btrim((("�����"."����")::character varying(20))::text)) AS "���" FROM "�����" WHERE ("�����"."�����" = 1);


ALTER TABLE public."vw_�����������_��_���������" OWNER TO sa;

--
-- TOC entry 1653 (class 1259 OID 71966)
-- Dependencies: 2044 2045 6
-- Name: �������; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "�������" (
    "���" integer NOT NULL,
    "���_VW_�����������_��_���������" integer,
    "���" character varying(100) DEFAULT ''::character varying,
    "���������" character varying(100) DEFAULT ''::character varying,
    "�����" numeric(3,0),
    "������������" boolean,
    "����������" integer
);


ALTER TABLE public."�������" OWNER TO sa;

--
-- TOC entry 1685 (class 1259 OID 72230)
-- Dependencies: 1792 6
-- Name: vw_�������; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_�������" AS
    SELECT s."�������������", s."����������", s."�������", s."���������", s."�����", s."������������" FROM (SELECT DISTINCT btrim((d."���")::text) AS "�������������", CASE WHEN ((d."���" >= 1000000) AND (d."���" < 2000000)) THEN '���������'::character varying WHEN (d."���" >= 2000000) THEN '��������'::character varying ELSE d1."���" END AS "����������", CASE WHEN ("position"((s."���")::text, '.'::text) > 0) THEN ("substring"((s."���")::text, ("position"((s."���")::text, '.'::text) + 1)))::character varying ELSE s."���" END AS "�������", s."���������", s."�����", s."������������" FROM (("�������" s JOIN "vw_�����������_��_���������" d ON ((s."���_VW_�����������_��_���������" = d."���"))) JOIN "vw_�����������_��_���������" d1 ON ((s."����������" = d1."���")))) s WHERE ((s."�������")::text <> ''::text) ORDER BY s."����������", s."�����";


ALTER TABLE public."vw_�������" OWNER TO sa;

--
-- TOC entry 1686 (class 1259 OID 72235)
-- Dependencies: 1793 263 6 264 267 264
-- Name: vw_�������_����; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_�������_����" AS
    SELECT DISTINCT s."�������������" AS base_table, ins.table_name, ins."column", ins.name, ins.type, ins.length, ins."precision", ins.is_updatable, COALESCE(s."���������", ''::character varying) AS header, COALESCE(s."�����", (0)::numeric) AS number FROM ((SELECT "vw_�������"."�������������", "vw_�������"."����������", "vw_�������"."�������", "vw_�������"."���������", "vw_�������"."�����" FROM "vw_�������") s RIGHT JOIN (SELECT DISTINCT ins.table_name, ((ins.ordinal_position)::integer - 1) AS "column", ins.column_name AS name, ins.data_type AS type, (COALESCE((ins.character_maximum_length)::integer, 0) + COALESCE((ins.numeric_precision)::integer, 0)) AS length, COALESCE((ins.numeric_scale)::integer, 0) AS "precision", ins.is_updatable FROM (information_schema.columns ins JOIN "vw_�������" s ON ((((ins.table_name)::text = (s."����������")::text) AND (btrim(s."�������������") = '������'::text))))) ins ON ((((s."����������")::text = (ins.table_name)::text) AND ((s."�������")::text = (ins.name)::text)))) ORDER BY ins.table_name, ins."column";


ALTER TABLE public."vw_�������_����" OWNER TO sa;

--
-- TOC entry 1654 (class 1259 OID 71981)
-- Dependencies: 1786 6
-- Name: vw_�����; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_�����" AS
    SELECT s."���", s."���", s."����", s."��������������", s."������", s."����������", sp."��������" FROM ("�����" s LEFT JOIN "�����������" sp ON (((s."��������������")::text = (sp."���")::text)));


ALTER TABLE public."vw_�����" OWNER TO sa;

--
-- TOC entry 1655 (class 1259 OID 71985)
-- Dependencies: 1787 6
-- Name: vw_�����; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "vw_�����" AS
    SELECT "�����"."���", "�����"."����", "�����"."�����", "�����"."���", "�����"."������", "�����"."��������������" AS "�������", '                                        '::bpchar AS "������������", "�����"."����������" AS "�����", "�����"."������", "�����"."����������", "�����"."�������", "�����"."������", "�����1"."��������������" AS "�������", '                                        '::bpchar AS "������������", "�����1"."����������" AS "�����", "�����"."������������", "�����"."�����", "�����"."������", "�����"."����������", "�����"."�������", "�����"."���������", "�����"."����������", "�����"."��������", "�����"."�����������" FROM (("�����" LEFT JOIN "�����" "�����" ON ((("�����"."������")::bpchar = "�����"."����"))) LEFT JOIN "�����" "�����1" ON ((("�����"."������")::bpchar = "�����1"."����")));


ALTER TABLE public."vw_�����" OWNER TO sa;

--
-- TOC entry 1656 (class 1259 OID 71990)
-- Dependencies: 1640 6
-- Name: �����������_���_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "�����������_���_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."�����������_���_seq" OWNER TO sa;

--
-- TOC entry 2201 (class 0 OID 0)
-- Dependencies: 1656
-- Name: �����������_���_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "�����������_���_seq" OWNED BY "�����������"."���";


--
-- TOC entry 2202 (class 0 OID 0)
-- Dependencies: 1656
-- Name: �����������_���_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"�����������_���_seq"', 2, true);


--
-- TOC entry 1657 (class 1259 OID 71992)
-- Dependencies: 1643 6
-- Name: ���������_���_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "���������_���_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."���������_���_seq" OWNER TO sa;

--
-- TOC entry 2203 (class 0 OID 0)
-- Dependencies: 1657
-- Name: ���������_���_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "���������_���_seq" OWNED BY "���������"."���";


--
-- TOC entry 2204 (class 0 OID 0)
-- Dependencies: 1657
-- Name: ���������_���_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"���������_���_seq"', 1, true);


--
-- TOC entry 1658 (class 1259 OID 71994)
-- Dependencies: 1645 6
-- Name: ������_���_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "������_���_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."������_���_seq" OWNER TO sa;

--
-- TOC entry 2205 (class 0 OID 0)
-- Dependencies: 1658
-- Name: ������_���_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "������_���_seq" OWNED BY "������"."���";


--
-- TOC entry 2206 (class 0 OID 0)
-- Dependencies: 1658
-- Name: ������_���_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"������_���_seq"', 44, true);


--
-- TOC entry 1659 (class 1259 OID 71996)
-- Dependencies: 1788 6
-- Name: ������_�_��������; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "������_�_��������" AS
    SELECT DISTINCT "�����"."���", "�����"."���", "�����"."����" FROM ("�����" LEFT JOIN "vw_������" ON ((("�����"."����")::text = "vw_������"."���"))) WHERE ("vw_������"."���_������������" = 4) ORDER BY "�����"."���", "�����"."����";


ALTER TABLE public."������_�_��������" OWNER TO sa;

--
-- TOC entry 1660 (class 1259 OID 72000)
-- Dependencies: 1789 6
-- Name: ������_�_������; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "������_�_������" AS
    SELECT DISTINCT "�����"."���", "�����"."���", "�����"."����" FROM ("�����" JOIN "vw_������" ON ((rtrim(("�����"."����")::text) = rtrim("vw_������"."���")))) WHERE ("vw_������"."���_������������" = 2) ORDER BY "�����"."���", "�����"."����";


ALTER TABLE public."������_�_������" OWNER TO sa;

--
-- TOC entry 1661 (class 1259 OID 72004)
-- Dependencies: 1790 6
-- Name: ������_�_������������; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "������_�_������������" AS
    SELECT DISTINCT s."���", s."���_�_������" AS "���", d."����", d."���" AS "����������", s."���_�_������", s."���_�_�����", s."��������", true AS selectable, true AS insertable, true AS deleteable, true AS updateable FROM ("vw_������" d JOIN "�����������" s ON ((upper(rtrim(d."���")) = upper(rtrim((s."���")::text)))));


ALTER TABLE public."������_�_������������" OWNER TO sa;

--
-- TOC entry 1662 (class 1259 OID 72008)
-- Dependencies: 1791 6
-- Name: ������_�_�����; Type: VIEW; Schema: public; Owner: sa
--

CREATE VIEW "������_�_�����" AS
    SELECT DISTINCT "�����"."���", "�����"."���", s."����", "�����"."����", "�����"."���������", s.selectable, s.insertable, s.deleteable, s.updateable FROM ("�����" JOIN (SELECT "vw_������"."���", "vw_������"."���_������������", "vw_������"."����", true AS selectable, true AS insertable, true AS deleteable, true AS updateable FROM "vw_������" WHERE ("vw_������"."���_������������" = 3)) s ON ((rtrim(("�����"."����")::text) = rtrim(s."���")))) WHERE (("�����"."�����" = 1) AND (s."����" = true)) ORDER BY "�����"."���", s."����", "�����"."����", "�����"."���������";


ALTER TABLE public."������_�_�����" OWNER TO sa;

--
-- TOC entry 1663 (class 1259 OID 72013)
-- Dependencies: 2047 2048 2049 6
-- Name: �������; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "�������" (
    "���" integer NOT NULL,
    "���" character varying(100) DEFAULT ''::character varying,
    "����" integer DEFAULT 0,
    "�������" text DEFAULT ''::text
);


ALTER TABLE public."�������" OWNER TO sa;

--
-- TOC entry 1664 (class 1259 OID 72022)
-- Dependencies: 6 1663
-- Name: �������_���_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "�������_���_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."�������_���_seq" OWNER TO sa;

--
-- TOC entry 2212 (class 0 OID 0)
-- Dependencies: 1664
-- Name: �������_���_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "�������_���_seq" OWNED BY "�������"."���";


--
-- TOC entry 2213 (class 0 OID 0)
-- Dependencies: 1664
-- Name: �������_���_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"�������_���_seq"', 1, false);


--
-- TOC entry 1665 (class 1259 OID 72024)
-- Dependencies: 2051 2052 6
-- Name: ���������; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "���������" (
    "���" integer NOT NULL,
    "���" character varying(100) DEFAULT ''::character varying,
    "��������" character varying(200) DEFAULT ''::character varying,
    "�����������" character varying(100)
);


ALTER TABLE public."���������" OWNER TO sa;

--
-- TOC entry 1666 (class 1259 OID 72029)
-- Dependencies: 6 1665
-- Name: ���������_���_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "���������_���_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."���������_���_seq" OWNER TO sa;

--
-- TOC entry 2215 (class 0 OID 0)
-- Dependencies: 1666
-- Name: ���������_���_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "���������_���_seq" OWNED BY "���������"."���";


--
-- TOC entry 2216 (class 0 OID 0)
-- Dependencies: 1666
-- Name: ���������_���_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"���������_���_seq"', 22, true);


--
-- TOC entry 1680 (class 1259 OID 72172)
-- Dependencies: 2062 6
-- Name: ������������; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "������������" (
    "���" integer NOT NULL,
    "���" character varying(100) DEFAULT ''::character varying,
    "�������" character varying(20),
    "����" numeric(10,2),
    "�����" character varying(10)
);


ALTER TABLE public."������������" OWNER TO sa;

--
-- TOC entry 1679 (class 1259 OID 72170)
-- Dependencies: 6 1680
-- Name: ������������_���_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "������������_���_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."������������_���_seq" OWNER TO sa;

--
-- TOC entry 2218 (class 0 OID 0)
-- Dependencies: 1679
-- Name: ������������_���_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "������������_���_seq" OWNED BY "������������"."���";


--
-- TOC entry 2219 (class 0 OID 0)
-- Dependencies: 1679
-- Name: ������������_���_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"������������_���_seq"', 1, false);


--
-- TOC entry 1667 (class 1259 OID 72031)
-- Dependencies: 2054 2055 6
-- Name: ����������; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "����������" (
    "���" integer NOT NULL,
    "���" character varying(100) DEFAULT ''::character varying,
    "��������" integer DEFAULT 0,
    "����" boolean
);


ALTER TABLE public."����������" OWNER TO sa;

--
-- TOC entry 1668 (class 1259 OID 72036)
-- Dependencies: 6 1667
-- Name: ����������_���_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "����������_���_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."����������_���_seq" OWNER TO sa;

--
-- TOC entry 2221 (class 0 OID 0)
-- Dependencies: 1668
-- Name: ����������_���_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "����������_���_seq" OWNED BY "����������"."���";


--
-- TOC entry 2222 (class 0 OID 0)
-- Dependencies: 1668
-- Name: ����������_���_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"����������_���_seq"', 2, true);


--
-- TOC entry 1669 (class 1259 OID 72038)
-- Dependencies: 6 1648
-- Name: ��������_���_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "��������_���_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."��������_���_seq" OWNER TO sa;

--
-- TOC entry 2223 (class 0 OID 0)
-- Dependencies: 1669
-- Name: ��������_���_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "��������_���_seq" OWNED BY "��������"."���";


--
-- TOC entry 2224 (class 0 OID 0)
-- Dependencies: 1669
-- Name: ��������_���_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"��������_���_seq"', 1, true);


--
-- TOC entry 1682 (class 1259 OID 72192)
-- Dependencies: 2064 6
-- Name: ����������1; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "����������1" (
    "���" integer NOT NULL,
    "���" character varying(100) DEFAULT ''::character varying,
    "���_������" integer
);


ALTER TABLE public."����������1" OWNER TO sa;

--
-- TOC entry 1681 (class 1259 OID 72190)
-- Dependencies: 1682 6
-- Name: ����������1_���_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "����������1_���_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."����������1_���_seq" OWNER TO sa;

--
-- TOC entry 2226 (class 0 OID 0)
-- Dependencies: 1681
-- Name: ����������1_���_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "����������1_���_seq" OWNED BY "����������1"."���";


--
-- TOC entry 2227 (class 0 OID 0)
-- Dependencies: 1681
-- Name: ����������1_���_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"����������1_���_seq"', 1, false);


--
-- TOC entry 1684 (class 1259 OID 72202)
-- Dependencies: 2066 6
-- Name: ����������2; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "����������2" (
    "���" integer NOT NULL,
    "���" character varying(100) DEFAULT ''::character varying,
    "���_������" integer
);


ALTER TABLE public."����������2" OWNER TO sa;

--
-- TOC entry 1683 (class 1259 OID 72200)
-- Dependencies: 6 1684
-- Name: ����������2_���_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "����������2_���_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."����������2_���_seq" OWNER TO sa;

--
-- TOC entry 2229 (class 0 OID 0)
-- Dependencies: 1683
-- Name: ����������2_���_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "����������2_���_seq" OWNED BY "����������2"."���";


--
-- TOC entry 2230 (class 0 OID 0)
-- Dependencies: 1683
-- Name: ����������2_���_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"����������2_���_seq"', 1, false);


--
-- TOC entry 1670 (class 1259 OID 72040)
-- Dependencies: 6 1650
-- Name: �����������_���_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "�����������_���_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."�����������_���_seq" OWNER TO sa;

--
-- TOC entry 2231 (class 0 OID 0)
-- Dependencies: 1670
-- Name: �����������_���_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "�����������_���_seq" OWNED BY "�����������"."���";


--
-- TOC entry 2232 (class 0 OID 0)
-- Dependencies: 1670
-- Name: �����������_���_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"�����������_���_seq"', 118, true);


--
-- TOC entry 1671 (class 1259 OID 72042)
-- Dependencies: 6 1653
-- Name: �������_���_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "�������_���_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."�������_���_seq" OWNER TO sa;

--
-- TOC entry 2233 (class 0 OID 0)
-- Dependencies: 1671
-- Name: �������_���_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "�������_���_seq" OWNED BY "�������"."���";


--
-- TOC entry 2234 (class 0 OID 0)
-- Dependencies: 1671
-- Name: �������_���_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"�������_���_seq"', 7531, true);


--
-- TOC entry 1672 (class 1259 OID 72044)
-- Dependencies: 1638 6
-- Name: �����_���_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "�����_���_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."�����_���_seq" OWNER TO sa;

--
-- TOC entry 2235 (class 0 OID 0)
-- Dependencies: 1672
-- Name: �����_���_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "�����_���_seq" OWNED BY "�����"."���";


--
-- TOC entry 2236 (class 0 OID 0)
-- Dependencies: 1672
-- Name: �����_���_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"�����_���_seq"', 3, true);


--
-- TOC entry 1673 (class 1259 OID 72046)
-- Dependencies: 2057 6
-- Name: ������������; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "������������" (
    "���" integer NOT NULL,
    "���" character varying(20) DEFAULT ''::character varying
);


ALTER TABLE public."������������" OWNER TO sa;

--
-- TOC entry 1674 (class 1259 OID 72050)
-- Dependencies: 1673 6
-- Name: ������������_���_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "������������_���_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."������������_���_seq" OWNER TO sa;

--
-- TOC entry 2238 (class 0 OID 0)
-- Dependencies: 1674
-- Name: ������������_���_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "������������_���_seq" OWNED BY "������������"."���";


--
-- TOC entry 2239 (class 0 OID 0)
-- Dependencies: 1674
-- Name: ������������_���_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"������������_���_seq"', 4, true);


--
-- TOC entry 1675 (class 1259 OID 72052)
-- Dependencies: 6 1651
-- Name: �����_���_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "�����_���_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."�����_���_seq" OWNER TO sa;

--
-- TOC entry 2240 (class 0 OID 0)
-- Dependencies: 1675
-- Name: �����_���_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "�����_���_seq" OWNED BY "�����"."���";


--
-- TOC entry 2241 (class 0 OID 0)
-- Dependencies: 1675
-- Name: �����_���_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"�����_���_seq"', 2, true);


--
-- TOC entry 1676 (class 1259 OID 72054)
-- Dependencies: 2059 6
-- Name: �����; Type: TABLE; Schema: public; Owner: sa; Tablespace: 
--

CREATE TABLE "�����" (
    "���" integer NOT NULL,
    "���" character varying(100) DEFAULT ''::character varying,
    "���" integer,
    "��������" bytea,
    "����������" bigint
);


ALTER TABLE public."�����" OWNER TO sa;

--
-- TOC entry 1677 (class 1259 OID 72061)
-- Dependencies: 6 1676
-- Name: �����_���_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "�����_���_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."�����_���_seq" OWNER TO sa;

--
-- TOC entry 2243 (class 0 OID 0)
-- Dependencies: 1677
-- Name: �����_���_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "�����_���_seq" OWNED BY "�����"."���";


--
-- TOC entry 2244 (class 0 OID 0)
-- Dependencies: 1677
-- Name: �����_���_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"�����_���_seq"', 903, true);


--
-- TOC entry 1678 (class 1259 OID 72146)
-- Dependencies: 6
-- Name: �����_���_seq; Type: SEQUENCE; Schema: public; Owner: sa
--

CREATE SEQUENCE "�����_���_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."�����_���_seq" OWNER TO sa;

--
-- TOC entry 2245 (class 0 OID 0)
-- Dependencies: 1678
-- Name: �����_���_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"�����_���_seq"', 35, true);


--
-- TOC entry 2003 (class 2604 OID 72063)
-- Dependencies: 1656 1640
-- Name: ���; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "�����������" ALTER COLUMN "���" SET DEFAULT nextval('"�����������_���_seq"'::regclass);


--
-- TOC entry 2007 (class 2604 OID 72064)
-- Dependencies: 1657 1643
-- Name: ���; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "���������" ALTER COLUMN "���" SET DEFAULT nextval('"���������_���_seq"'::regclass);


--
-- TOC entry 2011 (class 2604 OID 72065)
-- Dependencies: 1658 1645
-- Name: ���; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "������" ALTER COLUMN "���" SET DEFAULT nextval('"������_���_seq"'::regclass);


--
-- TOC entry 2050 (class 2604 OID 72066)
-- Dependencies: 1664 1663
-- Name: ���; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "�������" ALTER COLUMN "���" SET DEFAULT nextval('"�������_���_seq"'::regclass);


--
-- TOC entry 2053 (class 2604 OID 72067)
-- Dependencies: 1666 1665
-- Name: ���; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "���������" ALTER COLUMN "���" SET DEFAULT nextval('"���������_���_seq"'::regclass);


--
-- TOC entry 2061 (class 2604 OID 72175)
-- Dependencies: 1680 1679 1680
-- Name: ���; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "������������" ALTER COLUMN "���" SET DEFAULT nextval('"������������_���_seq"'::regclass);


--
-- TOC entry 2056 (class 2604 OID 72068)
-- Dependencies: 1668 1667
-- Name: ���; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "����������" ALTER COLUMN "���" SET DEFAULT nextval('"����������_���_seq"'::regclass);


--
-- TOC entry 2015 (class 2604 OID 72069)
-- Dependencies: 1669 1648
-- Name: ���; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "��������" ALTER COLUMN "���" SET DEFAULT nextval('"��������_���_seq"'::regclass);


--
-- TOC entry 2063 (class 2604 OID 72195)
-- Dependencies: 1682 1681 1682
-- Name: ���; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "����������1" ALTER COLUMN "���" SET DEFAULT nextval('"����������1_���_seq"'::regclass);


--
-- TOC entry 2065 (class 2604 OID 72205)
-- Dependencies: 1684 1683 1684
-- Name: ���; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "����������2" ALTER COLUMN "���" SET DEFAULT nextval('"����������2_���_seq"'::regclass);


--
-- TOC entry 2021 (class 2604 OID 72070)
-- Dependencies: 1670 1650
-- Name: ���; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "�����������" ALTER COLUMN "���" SET DEFAULT nextval('"�����������_���_seq"'::regclass);


--
-- TOC entry 2046 (class 2604 OID 72071)
-- Dependencies: 1671 1653
-- Name: ���; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "�������" ALTER COLUMN "���" SET DEFAULT nextval('"�������_���_seq"'::regclass);


--
-- TOC entry 2000 (class 2604 OID 72072)
-- Dependencies: 1672 1638
-- Name: ���; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "�����" ALTER COLUMN "���" SET DEFAULT nextval('"�����_���_seq"'::regclass);


--
-- TOC entry 2058 (class 2604 OID 72073)
-- Dependencies: 1674 1673
-- Name: ���; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "������������" ALTER COLUMN "���" SET DEFAULT nextval('"������������_���_seq"'::regclass);


--
-- TOC entry 2043 (class 2604 OID 72074)
-- Dependencies: 1675 1651
-- Name: ���; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "�����" ALTER COLUMN "���" SET DEFAULT nextval('"�����_���_seq"'::regclass);


--
-- TOC entry 2060 (class 2604 OID 72075)
-- Dependencies: 1677 1676
-- Name: ���; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE "�����" ALTER COLUMN "���" SET DEFAULT nextval('"�����_���_seq"'::regclass);


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
-- Data for Name: �����������; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "�����������" ("���", "���", "���������", "������", "�����", "������������") FROM stdin;
2	��� SA                                  	1899-12-31	2013-04-01	2013-05-31	sa
\.


--
-- TOC entry 2151 (class 0 OID 71889)
-- Dependencies: 1643
-- Data for Name: ���������; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "���������" ("���", "����", "���������", "�����", "�����������", "�����", "��������", "����", "����", "����������1", "����������") FROM stdin;
\.


--
-- TOC entry 2152 (class 0 OID 71902)
-- Dependencies: 1645
-- Data for Name: ������; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "������" ("���", "����", "���_������������", "���", "������������", "�����������") FROM stdin;
18	t	1	����������	sa	f
2	f	1	������������	sa	f
1	f	1	������	sa	t
8	f	1	������_�_�����	sa	f
3	f	1	�����������	sa	t
11	f	1	�����	sa	t
16	t	1	�����	sa	t
17	t	1	���������	sa	f
28	f	1	vw_types	sa	f
40	t	1	������������	sa	f
42	t	1	����������1	sa	f
43	t	1	����������2	sa	f
7	f	1	������_�_������������	sa	f
\.


--
-- TOC entry 2157 (class 0 OID 72013)
-- Dependencies: 1663
-- Data for Name: �������; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "�������" ("���", "���", "����", "�������") FROM stdin;
\.


--
-- TOC entry 2158 (class 0 OID 72024)
-- Dependencies: 1665
-- Data for Name: ���������; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "���������" ("���", "���", "��������", "�����������") FROM stdin;
3	����������                                                                                          		\N
13	�����������                                                                                         		\N
4	����������                                                                                          		\N
6	���                                               		\N
5	��������                                                                                            		\N
14	����������                                                                                          		\N
12	����������������                                  		\N
2	�������������                                                                                       		\N
9	�������������                                                                                       		\N
7	������������                                                                                        		\N
11	��������                                          		\N
\.


--
-- TOC entry 2162 (class 0 OID 72172)
-- Dependencies: 1680
-- Data for Name: ������������; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "������������" ("���", "���", "�������", "����", "�����") FROM stdin;
\.


--
-- TOC entry 2159 (class 0 OID 72031)
-- Dependencies: 1667
-- Data for Name: ����������; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "����������" ("���", "���", "��������", "����") FROM stdin;
1	���������                               	1	\N
\.


--
-- TOC entry 2153 (class 0 OID 71916)
-- Dependencies: 1648
-- Data for Name: ��������; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "��������" ("���", "������", "�����", "������", "�����", "���", "����", "�����", "���", "������", "����", "���������") FROM stdin;
\.


--
-- TOC entry 2148 (class 0 OID 71850)
-- Dependencies: 1637
-- Data for Name: ������; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "������" ("����", "���", "���", "������", "�����", "�����", "�����", "������", "������", "���������", "�������") FROM stdin;
\.


--
-- TOC entry 2163 (class 0 OID 72192)
-- Dependencies: 1682
-- Data for Name: ����������1; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "����������1" ("���", "���", "���_������") FROM stdin;
\.


--
-- TOC entry 2164 (class 0 OID 72202)
-- Dependencies: 1684
-- Data for Name: ����������2; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "����������2" ("���", "���", "���_������") FROM stdin;
\.


--
-- TOC entry 2154 (class 0 OID 71926)
-- Dependencies: 1650
-- Data for Name: �����������; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "�����������" ("���", "���", "����", "���_�_������", "���_�_�����", "��������", "���������") FROM stdin;
50	�����������                                                                                         				\N	t
6	������                                                                                              		��������� ����������. ������	������	\N	t
86	������_�_�����		��������� ��������. ������ � ������� ���������	������� ��������	\N	t
85	�������		��������� ����������. �������		\N	t
23	�����                                                                                               		�����������. ���� ������		\N	t
91	������������		��������� ����������. ���� ��������	���� ��������	\N	t
12	�����                                                                                               		�����������. ������� �������� (��������)		\N	t
101	vw_types			���� ������ ��������	\N	t
13	���������                                                                                           		����������. ���������	���������	\N	t
34	����������                                                                                          		����������. ����������	����������	\N	t
114	������������		����������. ������������	������������	\N	f
4	�����������                                                                                         		�����������	�����������	\N	t
84	������_�_������������		��������� ��������. ������ � ������������	�����������	\N	t
117	����������2		����������2	����������2	\N	f
116	����������1		����������1	����������1	\N	f
\.


--
-- TOC entry 2156 (class 0 OID 71966)
-- Dependencies: 1653
-- Data for Name: �������; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "�������" ("���", "���_VW_�����������_��_���������", "���", "���������", "�����", "������������", "����������") FROM stdin;
7403	23	���	������������	1	f	\N
7404	23	����	����	2	f	\N
7405	23	��������������	����������	3	f	\N
7406	23	���������	���������	4	f	\N
7407	23	����������	����������	5	f	\N
7408	23	������	������	6	f	\N
7422	96		���	2	f	\N
7423	96		������������	2	f	\N
7428	99		���	2	f	\N
7429	99		������������	2	f	\N
7432	102		���	2	f	\N
7433	102		������������	2	f	\N
7181	6	����	����	4	f	\N
7182	6	������������__���	��� �������	2	t	\N
7183	6	���	������������	1	f	\N
7184	6	������������	������������	3	f	\N
7468	13	���	���	1	t	\N
7469	13	���	������������	2	f	\N
7470	13	��������	��������	3	f	\N
7471	13	�����������	�����������	4	f	\N
7475	34	���	������������	1	f	\N
7476	34	��������	��������	2	f	\N
7478	107	���	���	1	f	\N
7479	107	���	������������	2	f	\N
88	12	���	���	1	t	\N
89	12	����	��������	2	f	\N
90	12	�����	��������	3	f	\N
91	12	������	��.����	4	f	\N
92	12	������	��.����	5	f	\N
93	12	���	������������	6	f	\N
94	12	�����	����	7	f	\N
95	12	�����������	���.��������	8	f	\N
17	91	���	���	1	t	\N
18	91	���	������������	2	f	\N
96	12	���������	���������	9	f	\N
97	12	������������	������������	10	f	\N
98	12	���	���-��	11	f	\N
99	12	������	��.����	12	f	\N
100	12	������	��.����	13	f	\N
29	86	���	������������	1	t	\N
7480	108	���	���	1	f	\N
7481	108	���	������������	2	f	\N
7484	110	���	���	1	f	\N
7485	110	���	������������	2	f	\N
7486	110	����	����	1	f	\N
7490	111	���	���	1	f	\N
7491	111	���	������������	2	f	\N
101	12	�������	��.�����	14	f	\N
102	12	�������	��.�����	15	f	\N
103	12	�������	��.�����	16	f	\N
104	12	�������	��.�����	17	f	\N
105	12	����������	��.�����������	18	f	\N
106	12	����������	��.�����������	19	f	\N
107	12	�������	�������	20	f	\N
108	12	�������	�������	21	f	\N
109	12	���������	���������	22	f	\N
110	12	�������	�������	23	f	\N
111	12	��������	��������	24	f	\N
7492	111	����	����	3	f	\N
112	12	�����������	���.��������	25	f	\N
7420	95		���	2	f	\N
7421	95		������������	2	f	\N
7424	97		���	2	f	\N
7425	97		������������	2	f	\N
7426	98		���	2	f	\N
7427	98		������������	2	f	\N
7430	100		���	2	f	\N
7431	100		������������	2	f	\N
7434	101	���	������������	1	t	\N
7435	101	�����	�����	2	t	\N
7439	103	���	���	1	t	\N
7440	103	���	���	2	f	\N
7444	104	���	���	2	t	\N
7445	104	���	���	3	f	\N
7446	104	����	����	1	f	\N
7477	105	���	���	1	t	\N
7482	109	���	���	1	f	\N
7483	109	���	������������	2	f	\N
7500	114	���	���	1	t	114
7501	114	���	������������	2	t	114
7502	114	�������	�������	3	t	114
7503	114	����	����	4	t	114
7504	114	�����	��.���.	6	t	114
7510	4	���	���	2	t	4
7511	4	���	������������	1	t	4
7512	4	����	����	3	t	4
7513	4	���_�_������	���_�_������	4	t	4
7514	4	���_�_�����	���_�_�����	5	t	4
7515	4	��������	��������	6	t	4
7516	4	���������	���������	7	t	4
7517	84	���	������������	1	t	84
7520	117	���	���	1	t	117
7521	117	���	������������	2	t	117
7530	116	���	���	1	t	116
7531	116	���	������������	2	t	116
\.


--
-- TOC entry 2149 (class 0 OID 71862)
-- Dependencies: 1638
-- Data for Name: �����; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "�����" ("���", "���", "����", "��������������", "���������", "����������", "������") FROM stdin;
\.


--
-- TOC entry 2160 (class 0 OID 72046)
-- Dependencies: 1673
-- Data for Name: ������������; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "������������" ("���", "���") FROM stdin;
1	����������
2	������
3	�����
4	������
\.


--
-- TOC entry 2155 (class 0 OID 71934)
-- Dependencies: 1651
-- Data for Name: �����; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "�����" ("���", "����", "�����", "������", "������", "���", "�����", "����", "�����������", "���������", "������������", "���", "������", "������", "�������", "�������", "�������", "�������", "����������", "����������", "�������", "�������", "�����", "���������", "�������", "����������", "��������", "�����������") FROM stdin;
\.


--
-- TOC entry 2161 (class 0 OID 72054)
-- Dependencies: 1676
-- Data for Name: �����; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "�����" ("���", "���", "���", "��������", "����������") FROM stdin;
893	�����.qs	0	\\x66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657253686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bed182d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74417070656e6446726f6d51756572792869642c207265636f7264290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d0bdd0bed0b2d0bed0b920d0b7d0b0d0bfd0b8d181d0b820d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726548696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b7d0b0d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7443616c635461626c6528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d18fd187d0b5d0b9d0bad0b820d0b220d182d0b0d0b1d0bbd0b8d186d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744b657950726573736564286b65794576656e74290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bbd18ed0b1d0bed0b920d0bad0bdd0bed0bfd0bad0b820d0bdd0b020d184d0bed180d0bcd0b52e20d09fd0b0d180d0b0d0bcd0b5d182d180206b65794576656e7420d0b8d0bcd0b5d0b5d18220d182d0b8d0bf20514b65794576656e740a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74536574456e61626c656428656e61626c6564290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0b5d0b4d0bdd0b0d0b7d0bdd0b0d187d0b5d0bdd0be20d0b4d0bbd18f20d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d0b820d0b4d0bed181d182d183d0bfd0b020d0ba20d18dd0bbd0b5d0bcd0b5d0bdd182d0b0d0bc20d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18cd181d0bad0bed0b920d184d0bed180d0bcd18b0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e20507265706172655069637475726555726c286f626a656374290a7b202f2f20d092d18bd0b7d0bed0b220d18dd182d0bed0b920d184d183d0bdd0bad186d0b8d0b820d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e20d097d0b4d0b5d181d18c20d0b8d0bcd0b5d0b5d182d181d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d18c20d0b7d0b0d0b3d180d183d0b7d0b8d182d18c20d184d0bed182d0bed0b3d180d0b0d184d0b8d18e20d0b4d0bbd18f20d182d0b5d0bad183d189d0b5d0b3d0be20d0bed0b1d18ad0b5d0bad182d0b0206f626a65637420d0b8d0b720d098d0bdd182d0b5d180d0bdd0b5d182d0b02e20d0a4d183d0bdd0bad186d0b8d18f20d0b4d0bed0bbd0b6d0bdd0b020d0b2d0b5d180d0bdd183d182d18c2075726c20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a	0
898	vw_types.qs	0	\\x66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657253686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bed182d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74417070656e6446726f6d51756572792869642c207265636f7264290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d0bdd0bed0b2d0bed0b920d0b7d0b0d0bfd0b8d181d0b820d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726548696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b7d0b0d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7443616c635461626c6528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d18fd187d0b5d0b9d0bad0b820d0b220d182d0b0d0b1d0bbd0b8d186d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744b657950726573736564286b65794576656e74290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bbd18ed0b1d0bed0b920d0bad0bdd0bed0bfd0bad0b820d0bdd0b020d184d0bed180d0bcd0b52e20d09fd0b0d180d0b0d0bcd0b5d182d180206b65794576656e7420d0b8d0bcd0b5d0b5d18220d182d0b8d0bf20514b65794576656e740a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74536574456e61626c656428656e61626c6564290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0b5d0b4d0bdd0b0d0b7d0bdd0b0d187d0b5d0bdd0be20d0b4d0bbd18f20d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d0b820d0b4d0bed181d182d183d0bfd0b020d0ba20d18dd0bbd0b5d0bcd0b5d0bdd182d0b0d0bc20d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18cd181d0bad0bed0b920d184d0bed180d0bcd18b0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e20507265706172655069637475726555726c286f626a656374290a7b202f2f20d092d18bd0b7d0bed0b220d18dd182d0bed0b920d184d183d0bdd0bad186d0b8d0b820d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e20d097d0b4d0b5d181d18c20d0b8d0bcd0b5d0b5d182d181d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d18c20d0b7d0b0d0b3d180d183d0b7d0b8d182d18c20d184d0bed182d0bed0b3d180d0b0d184d0b8d18e20d0b4d0bbd18f20d182d0b5d0bad183d189d0b5d0b3d0be20d0bed0b1d18ad0b5d0bad182d0b0206f626a65637420d0b8d0b720d098d0bdd182d0b5d180d0bdd0b5d182d0b02e20d0a4d183d0bdd0bad186d0b8d18f20d0b4d0bed0bbd0b6d0bdd0b020d0b2d0b5d180d0bdd183d182d18c2075726c20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a	0
901	���������.qs	0	\\x66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657253686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bed182d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74417070656e6446726f6d51756572792869642c207265636f7264290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d0bdd0bed0b2d0bed0b920d0b7d0b0d0bfd0b8d181d0b820d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726548696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b7d0b0d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7443616c635461626c6528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d18fd187d0b5d0b9d0bad0b820d0b220d182d0b0d0b1d0bbd0b8d186d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744b657950726573736564286b65794576656e74290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bbd18ed0b1d0bed0b920d0bad0bdd0bed0bfd0bad0b820d0bdd0b020d184d0bed180d0bcd0b52e20d09fd0b0d180d0b0d0bcd0b5d182d180206b65794576656e7420d0b8d0bcd0b5d0b5d18220d182d0b8d0bf20514b65794576656e740a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74536574456e61626c656428656e61626c6564290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0b5d0b4d0bdd0b0d0b7d0bdd0b0d187d0b5d0bdd0be20d0b4d0bbd18f20d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d0b820d0b4d0bed181d182d183d0bfd0b020d0ba20d18dd0bbd0b5d0bcd0b5d0bdd182d0b0d0bc20d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18cd181d0bad0bed0b920d184d0bed180d0bcd18b0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e20507265706172655069637475726555726c286f626a656374290a7b202f2f20d092d18bd0b7d0bed0b220d18dd182d0bed0b920d184d183d0bdd0bad186d0b8d0b820d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e20d097d0b4d0b5d181d18c20d0b8d0bcd0b5d0b5d182d181d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d18c20d0b7d0b0d0b3d180d183d0b7d0b8d182d18c20d184d0bed182d0bed0b3d180d0b0d184d0b8d18e20d0b4d0bbd18f20d182d0b5d0bad183d189d0b5d0b3d0be20d0bed0b1d18ad0b5d0bad182d0b0206f626a65637420d0b8d0b720d098d0bdd182d0b5d180d0bdd0b5d182d0b02e20d0a4d183d0bdd0bad186d0b8d18f20d0b4d0bed0bbd0b6d0bdd0b020d0b2d0b5d180d0bdd183d182d18c2075726c20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a	0
894	�����������.qs	0	\\x66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657253686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bed182d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74417070656e6446726f6d51756572792869642c207265636f7264290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d0bdd0bed0b2d0bed0b920d0b7d0b0d0bfd0b8d181d0b820d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726548696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b7d0b0d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7443616c635461626c6528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d18fd187d0b5d0b9d0bad0b820d0b220d182d0b0d0b1d0bbd0b8d186d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744b657950726573736564286b65794576656e74290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bbd18ed0b1d0bed0b920d0bad0bdd0bed0bfd0bad0b820d0bdd0b020d184d0bed180d0bcd0b52e20d09fd0b0d180d0b0d0bcd0b5d182d180206b65794576656e7420d0b8d0bcd0b5d0b5d18220d182d0b8d0bf20514b65794576656e740a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74536574456e61626c656428656e61626c6564290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0b5d0b4d0bdd0b0d0b7d0bdd0b0d187d0b5d0bdd0be20d0b4d0bbd18f20d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d0b820d0b4d0bed181d182d183d0bfd0b020d0ba20d18dd0bbd0b5d0bcd0b5d0bdd182d0b0d0bc20d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18cd181d0bad0bed0b920d184d0bed180d0bcd18b0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e20507265706172655069637475726555726c286f626a656374290a7b202f2f20d092d18bd0b7d0bed0b220d18dd182d0bed0b920d184d183d0bdd0bad186d0b8d0b820d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e20d097d0b4d0b5d181d18c20d0b8d0bcd0b5d0b5d182d181d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d18c20d0b7d0b0d0b3d180d183d0b7d0b8d182d18c20d184d0bed182d0bed0b3d180d0b0d184d0b8d18e20d0b4d0bbd18f20d182d0b5d0bad183d189d0b5d0b3d0be20d0bed0b1d18ad0b5d0bad182d0b0206f626a65637420d0b8d0b720d098d0bdd182d0b5d180d0bdd0b5d182d0b02e20d0a4d183d0bdd0bad186d0b8d18f20d0b4d0bed0bbd0b6d0bdd0b020d0b2d0b5d180d0bdd183d182d18c2075726c20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a	0
897	����������2.qs	0	\\x66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657253686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bed182d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74417070656e6446726f6d51756572792869642c207265636f7264290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d0bdd0bed0b2d0bed0b920d0b7d0b0d0bfd0b8d181d0b820d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726548696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b7d0b0d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7443616c635461626c6528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d18fd187d0b5d0b9d0bad0b820d0b220d182d0b0d0b1d0bbd0b8d186d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744b657950726573736564286b65794576656e74290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bbd18ed0b1d0bed0b920d0bad0bdd0bed0bfd0bad0b820d0bdd0b020d184d0bed180d0bcd0b52e20d09fd0b0d180d0b0d0bcd0b5d182d180206b65794576656e7420d0b8d0bcd0b5d0b5d18220d182d0b8d0bf20514b65794576656e740a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74536574456e61626c656428656e61626c6564290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0b5d0b4d0bdd0b0d0b7d0bdd0b0d187d0b5d0bdd0be20d0b4d0bbd18f20d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d0b820d0b4d0bed181d182d183d0bfd0b020d0ba20d18dd0bbd0b5d0bcd0b5d0bdd182d0b0d0bc20d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18cd181d0bad0bed0b920d184d0bed180d0bcd18b0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e20507265706172655069637475726555726c286f626a656374290a7b202f2f20d092d18bd0b7d0bed0b220d18dd182d0bed0b920d184d183d0bdd0bad186d0b8d0b820d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e20d097d0b4d0b5d181d18c20d0b8d0bcd0b5d0b5d182d181d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d18c20d0b7d0b0d0b3d180d183d0b7d0b8d182d18c20d184d0bed182d0bed0b3d180d0b0d184d0b8d18e20d0b4d0bbd18f20d182d0b5d0bad183d189d0b5d0b3d0be20d0bed0b1d18ad0b5d0bad182d0b0206f626a65637420d0b8d0b720d098d0bdd182d0b5d180d0bdd0b5d182d0b02e20d0a4d183d0bdd0bad186d0b8d18f20d0b4d0bed0bbd0b6d0bdd0b020d0b2d0b5d180d0bdd183d182d18c2075726c20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a	0
899	����������.qs	0	\\x66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657253686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bed182d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74417070656e6446726f6d51756572792869642c207265636f7264290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d0bdd0bed0b2d0bed0b920d0b7d0b0d0bfd0b8d181d0b820d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726548696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b7d0b0d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7443616c635461626c6528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d18fd187d0b5d0b9d0bad0b820d0b220d182d0b0d0b1d0bbd0b8d186d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744b657950726573736564286b65794576656e74290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bbd18ed0b1d0bed0b920d0bad0bdd0bed0bfd0bad0b820d0bdd0b020d184d0bed180d0bcd0b52e20d09fd0b0d180d0b0d0bcd0b5d182d180206b65794576656e7420d0b8d0bcd0b5d0b5d18220d182d0b8d0bf20514b65794576656e740a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74536574456e61626c656428656e61626c6564290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0b5d0b4d0bdd0b0d0b7d0bdd0b0d187d0b5d0bdd0be20d0b4d0bbd18f20d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d0b820d0b4d0bed181d182d183d0bfd0b020d0ba20d18dd0bbd0b5d0bcd0b5d0bdd182d0b0d0bc20d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18cd181d0bad0bed0b920d184d0bed180d0bcd18b0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e20507265706172655069637475726555726c286f626a656374290a7b202f2f20d092d18bd0b7d0bed0b220d18dd182d0bed0b920d184d183d0bdd0bad186d0b8d0b820d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e20d097d0b4d0b5d181d18c20d0b8d0bcd0b5d0b5d182d181d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d18c20d0b7d0b0d0b3d180d183d0b7d0b8d182d18c20d184d0bed182d0bed0b3d180d0b0d184d0b8d18e20d0b4d0bbd18f20d182d0b5d0bad183d189d0b5d0b3d0be20d0bed0b1d18ad0b5d0bad182d0b0206f626a65637420d0b8d0b720d098d0bdd182d0b5d180d0bdd0b5d182d0b02e20d0a4d183d0bdd0bad186d0b8d18f20d0b4d0bed0bbd0b6d0bdd0b020d0b2d0b5d180d0bdd183d182d18c2075726c20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a	0
900	����������.qs	0	\\x66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657253686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bed182d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74417070656e6446726f6d51756572792869642c207265636f7264290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d0bdd0bed0b2d0bed0b920d0b7d0b0d0bfd0b8d181d0b820d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726548696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b7d0b0d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7443616c635461626c6528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d18fd187d0b5d0b9d0bad0b820d0b220d182d0b0d0b1d0bbd0b8d186d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744b657950726573736564286b65794576656e74290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bbd18ed0b1d0bed0b920d0bad0bdd0bed0bfd0bad0b820d0bdd0b020d184d0bed180d0bcd0b52e20d09fd0b0d180d0b0d0bcd0b5d182d180206b65794576656e7420d0b8d0bcd0b5d0b5d18220d182d0b8d0bf20514b65794576656e740a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74536574456e61626c656428656e61626c6564290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0b5d0b4d0bdd0b0d0b7d0bdd0b0d187d0b5d0bdd0be20d0b4d0bbd18f20d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d0b820d0b4d0bed181d182d183d0bfd0b020d0ba20d18dd0bbd0b5d0bcd0b5d0bdd182d0b0d0bc20d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18cd181d0bad0bed0b920d184d0bed180d0bcd18b0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e20507265706172655069637475726555726c286f626a656374290a7b202f2f20d092d18bd0b7d0bed0b220d18dd182d0bed0b920d184d183d0bdd0bad186d0b8d0b820d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e20d097d0b4d0b5d181d18c20d0b8d0bcd0b5d0b5d182d181d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d18c20d0b7d0b0d0b3d180d183d0b7d0b8d182d18c20d184d0bed182d0bed0b3d180d0b0d184d0b8d18e20d0b4d0bbd18f20d182d0b5d0bad183d189d0b5d0b3d0be20d0bed0b1d18ad0b5d0bad182d0b0206f626a65637420d0b8d0b720d098d0bdd182d0b5d180d0bdd0b5d182d0b02e20d0a4d183d0bdd0bad186d0b8d18f20d0b4d0bed0bbd0b6d0bdd0b020d0b2d0b5d180d0bdd183d182d18c2075726c20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a	0
895	�����������.qs	0	\\x66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657253686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bed182d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74417070656e6446726f6d51756572792869642c207265636f7264290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d0bdd0bed0b2d0bed0b920d0b7d0b0d0bfd0b8d181d0b820d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726548696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b7d0b0d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7443616c635461626c6528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d18fd187d0b5d0b9d0bad0b820d0b220d182d0b0d0b1d0bbd0b8d186d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744b657950726573736564286b65794576656e74290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bbd18ed0b1d0bed0b920d0bad0bdd0bed0bfd0bad0b820d0bdd0b020d184d0bed180d0bcd0b52e20d09fd0b0d180d0b0d0bcd0b5d182d180206b65794576656e7420d0b8d0bcd0b5d0b5d18220d182d0b8d0bf20514b65794576656e740a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74536574456e61626c656428656e61626c6564290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0b5d0b4d0bdd0b0d0b7d0bdd0b0d187d0b5d0bdd0be20d0b4d0bbd18f20d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d0b820d0b4d0bed181d182d183d0bfd0b020d0ba20d18dd0bbd0b5d0bcd0b5d0bdd182d0b0d0bc20d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18cd181d0bad0bed0b920d184d0bed180d0bcd18b0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e20507265706172655069637475726555726c286f626a656374290a7b202f2f20d092d18bd0b7d0bed0b220d18dd182d0bed0b920d184d183d0bdd0bad186d0b8d0b820d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e20d097d0b4d0b5d181d18c20d0b8d0bcd0b5d0b5d182d181d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d18c20d0b7d0b0d0b3d180d183d0b7d0b8d182d18c20d184d0bed182d0bed0b3d180d0b0d184d0b8d18e20d0b4d0bbd18f20d182d0b5d0bad183d189d0b5d0b3d0be20d0bed0b1d18ad0b5d0bad182d0b0206f626a65637420d0b8d0b720d098d0bdd182d0b5d180d0bdd0b5d182d0b02e20d0a4d183d0bdd0bad186d0b8d18f20d0b4d0bed0bbd0b6d0bdd0b020d0b2d0b5d180d0bdd183d182d18c2075726c20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a	0
902	������������.qs	0	\\x66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657253686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bed182d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74417070656e6446726f6d51756572792869642c207265636f7264290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d0bdd0bed0b2d0bed0b920d0b7d0b0d0bfd0b8d181d0b820d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726548696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b7d0b0d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7443616c635461626c6528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d18fd187d0b5d0b9d0bad0b820d0b220d182d0b0d0b1d0bbd0b8d186d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744b657950726573736564286b65794576656e74290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bbd18ed0b1d0bed0b920d0bad0bdd0bed0bfd0bad0b820d0bdd0b020d184d0bed180d0bcd0b52e20d09fd0b0d180d0b0d0bcd0b5d182d180206b65794576656e7420d0b8d0bcd0b5d0b5d18220d182d0b8d0bf20514b65794576656e740a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74536574456e61626c656428656e61626c6564290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0b5d0b4d0bdd0b0d0b7d0bdd0b0d187d0b5d0bdd0be20d0b4d0bbd18f20d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d0b820d0b4d0bed181d182d183d0bfd0b020d0ba20d18dd0bbd0b5d0bcd0b5d0bdd182d0b0d0bc20d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18cd181d0bad0bed0b920d184d0bed180d0bcd18b0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e20507265706172655069637475726555726c286f626a656374290a7b202f2f20d092d18bd0b7d0bed0b220d18dd182d0bed0b920d184d183d0bdd0bad186d0b8d0b820d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e20d097d0b4d0b5d181d18c20d0b8d0bcd0b5d0b5d182d181d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d18c20d0b7d0b0d0b3d180d183d0b7d0b8d182d18c20d184d0bed182d0bed0b3d180d0b0d184d0b8d18e20d0b4d0bbd18f20d182d0b5d0bad183d189d0b5d0b3d0be20d0bed0b1d18ad0b5d0bad182d0b0206f626a65637420d0b8d0b720d098d0bdd182d0b5d180d0bdd0b5d182d0b02e20d0a4d183d0bdd0bad186d0b8d18f20d0b4d0bed0bbd0b6d0bdd0b020d0b2d0b5d180d0bdd183d182d18c2075726c20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a	0
903	������_�_������������.qs	0	\\x66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744166746572526f774368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bfd0b5d180d0b5d0bcd0b5d189d0b5d0bdd0b8d18f20d0bdd0b020d0b4d180d183d0b3d183d18e20d181d182d180d0bed0bad1830a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657253686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bed182d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74417070656e6446726f6d51756572792869642c207265636f7264290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d0bdd0bed0b2d0bed0b920d0b7d0b0d0bfd0b8d181d0b820d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726548696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b7d0b0d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7443616c635461626c6528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d18fd187d0b5d0b9d0bad0b820d0b220d182d0b0d0b1d0bbd0b8d186d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744b657950726573736564286b65794576656e74290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bbd18ed0b1d0bed0b920d0bad0bdd0bed0bfd0bad0b820d0bdd0b020d184d0bed180d0bcd0b52e20d09fd0b0d180d0b0d0bcd0b5d182d180206b65794576656e7420d0b8d0bcd0b5d0b5d18220d182d0b8d0bf20514b65794576656e740a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74536574456e61626c656428656e61626c6564290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0b5d0b4d0bdd0b0d0b7d0bdd0b0d187d0b5d0bdd0be20d0b4d0bbd18f20d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d0b820d0b4d0bed181d182d183d0bfd0b020d0ba20d18dd0bbd0b5d0bcd0b5d0bdd182d0b0d0bc20d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18cd181d0bad0bed0b920d184d0bed180d0bcd18b0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e20507265706172655069637475726555726c286f626a656374290a7b202f2f20d092d18bd0b7d0bed0b220d18dd182d0bed0b920d184d183d0bdd0bad186d0b8d0b820d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e20d097d0b4d0b5d181d18c20d0b8d0bcd0b5d0b5d182d181d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d18c20d0b7d0b0d0b3d180d183d0b7d0b8d182d18c20d184d0bed182d0bed0b3d180d0b0d184d0b8d18e20d0b4d0bbd18f20d182d0b5d0bad183d189d0b5d0b3d0be20d0bed0b1d18ad0b5d0bad182d0b0206f626a65637420d0b8d0b720d098d0bdd182d0b5d180d0bdd0b5d182d0b02e20d0a4d183d0bdd0bad186d0b8d18f20d0b4d0bed0bbd0b6d0bdd0b020d0b2d0b5d180d0bdd183d182d18c2075726c20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a	0
896	����������1.qs	0	\\x66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657253686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bed182d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74417070656e6446726f6d51756572792869642c207265636f7264290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d0bdd0bed0b2d0bed0b920d0b7d0b0d0bfd0b8d181d0b820d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726548696465466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b7d0b0d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7443616c635461626c6528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d18fd187d0b5d0b9d0bad0b820d0b220d182d0b0d0b1d0bbd0b8d186d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496e6974466f726d28290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a097072696e7428224576656e74496e6974466f726d22293b0a097461626c652e676574466f726d57696467657428292e73657457696e646f775469746c652822616161616161616122293b0a7d0a0a0a66756e6374696f6e204576656e744b657950726573736564286b65794576656e74290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bbd18ed0b1d0bed0b920d0bad0bdd0bed0bfd0bad0b820d0bdd0b020d184d0bed180d0bcd0b52e20d09fd0b0d180d0b0d0bcd0b5d182d180206b65794576656e7420d0b8d0bcd0b5d0b5d18220d182d0b8d0bf20514b65794576656e740a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74536574456e61626c656428656e61626c6564290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0b5d0b4d0bdd0b0d0b7d0bdd0b0d187d0b5d0bdd0be20d0b4d0bbd18f20d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d0b820d0b4d0bed181d182d183d0bfd0b020d0ba20d18dd0bbd0b5d0bcd0b5d0bdd182d0b0d0bc20d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18cd181d0bad0bed0b920d184d0bed180d0bcd18b0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e20507265706172655069637475726555726c286f626a656374290a7b202f2f20d092d18bd0b7d0bed0b220d18dd182d0bed0b920d184d183d0bdd0bad186d0b8d0b820d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e20d097d0b4d0b5d181d18c20d0b8d0bcd0b5d0b5d182d181d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d18c20d0b7d0b0d0b3d180d183d0b7d0b8d182d18c20d184d0bed182d0bed0b3d180d0b0d184d0b8d18e20d0b4d0bbd18f20d182d0b5d0bad183d189d0b5d0b3d0be20d0bed0b1d18ad0b5d0bad182d0b0206f626a65637420d0b8d0b720d098d0bdd182d0b5d180d0bdd0b5d182d0b02e20d0a4d183d0bdd0bad186d0b8d18f20d0b4d0bed0bbd0b6d0bdd0b020d0b2d0b5d180d0bdd183d182d18c2075726c20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a	0
\.


--
-- TOC entry 2074 (class 2606 OID 72077)
-- Dependencies: 1640 1640
-- Name: �����������_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "�����������"
    ADD CONSTRAINT "�����������_pkey" PRIMARY KEY ("���");


--
-- TOC entry 2078 (class 2606 OID 72079)
-- Dependencies: 1643 1643
-- Name: ���������_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "���������"
    ADD CONSTRAINT "���������_pkey" PRIMARY KEY ("���");


--
-- TOC entry 2084 (class 2606 OID 72081)
-- Dependencies: 1645 1645
-- Name: ������_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "������"
    ADD CONSTRAINT "������_pkey" PRIMARY KEY ("���");


--
-- TOC entry 2109 (class 2606 OID 72083)
-- Dependencies: 1665 1665
-- Name: ���������_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "���������"
    ADD CONSTRAINT "���������_pkey" PRIMARY KEY ("���");


--
-- TOC entry 2123 (class 2606 OID 72178)
-- Dependencies: 1680 1680
-- Name: ������������_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "������������"
    ADD CONSTRAINT "������������_pkey" PRIMARY KEY ("���");


--
-- TOC entry 2113 (class 2606 OID 72085)
-- Dependencies: 1667 1667
-- Name: ����������_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "����������"
    ADD CONSTRAINT "����������_pkey" PRIMARY KEY ("���");


--
-- TOC entry 2088 (class 2606 OID 72087)
-- Dependencies: 1648 1648
-- Name: ��������_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "��������"
    ADD CONSTRAINT "��������_pkey" PRIMARY KEY ("���");


--
-- TOC entry 2125 (class 2606 OID 72198)
-- Dependencies: 1682 1682
-- Name: ����������1_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "����������1"
    ADD CONSTRAINT "����������1_pkey" PRIMARY KEY ("���");


--
-- TOC entry 2127 (class 2606 OID 72208)
-- Dependencies: 1684 1684
-- Name: ����������2_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "����������2"
    ADD CONSTRAINT "����������2_pkey" PRIMARY KEY ("���");


--
-- TOC entry 2099 (class 2606 OID 72089)
-- Dependencies: 1650 1650
-- Name: �����������_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "�����������"
    ADD CONSTRAINT "�����������_pkey" PRIMARY KEY ("���");


--
-- TOC entry 2105 (class 2606 OID 72091)
-- Dependencies: 1653 1653
-- Name: �������_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "�������"
    ADD CONSTRAINT "�������_pkey" PRIMARY KEY ("���");


--
-- TOC entry 2070 (class 2606 OID 72093)
-- Dependencies: 1638 1638
-- Name: �����_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "�����"
    ADD CONSTRAINT "�����_pkey" PRIMARY KEY ("���");


--
-- TOC entry 2117 (class 2606 OID 72095)
-- Dependencies: 1673 1673
-- Name: ������������_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "������������"
    ADD CONSTRAINT "������������_pkey" PRIMARY KEY ("���");


--
-- TOC entry 2103 (class 2606 OID 72097)
-- Dependencies: 1651 1651
-- Name: �����_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "�����"
    ADD CONSTRAINT "�����_pkey" PRIMARY KEY ("���");


--
-- TOC entry 2121 (class 2606 OID 72099)
-- Dependencies: 1676 1676
-- Name: �����_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "�����"
    ADD CONSTRAINT "�����_pkey" PRIMARY KEY ("���");


--
-- TOC entry 2067 (class 1259 OID 72100)
-- Dependencies: 1631 1631
-- Name: configs_name_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX configs_name_idx ON configs USING btree ("group", name);


--
-- TOC entry 2075 (class 1259 OID 72101)
-- Dependencies: 1640
-- Name: �����������_���_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "�����������_���_idx" ON "�����������" USING btree ("���");


--
-- TOC entry 2076 (class 1259 OID 72102)
-- Dependencies: 1640
-- Name: �����������_���_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "�����������_���_idx" ON "�����������" USING btree ("���");


--
-- TOC entry 2079 (class 1259 OID 72103)
-- Dependencies: 1643 1643 1643
-- Name: ���������_����_����_����_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "���������_����_����_����_idx" ON "���������" USING btree ("����", "����", "����");


--
-- TOC entry 2080 (class 1259 OID 72104)
-- Dependencies: 1643
-- Name: ���������_����_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "���������_����_idx" ON "���������" USING btree ("����");


--
-- TOC entry 2081 (class 1259 OID 72105)
-- Dependencies: 1643 1643 1643
-- Name: ���������_����_����_����_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "���������_����_����_����_idx" ON "���������" USING btree ("����", "����", "����");


--
-- TOC entry 2082 (class 1259 OID 72106)
-- Dependencies: 1643
-- Name: ���������_���_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "���������_���_idx" ON "���������" USING btree ("���");


--
-- TOC entry 2085 (class 1259 OID 72107)
-- Dependencies: 1645
-- Name: ������_���_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "������_���_idx" ON "������" USING btree ("���");


--
-- TOC entry 2086 (class 1259 OID 72108)
-- Dependencies: 1645
-- Name: ������_���_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "������_���_idx" ON "������" USING btree ("���");


--
-- TOC entry 2106 (class 1259 OID 72109)
-- Dependencies: 1663
-- Name: �������_���_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "�������_���_idx" ON "�������" USING btree ("���");


--
-- TOC entry 2107 (class 1259 OID 72110)
-- Dependencies: 1663
-- Name: �������_���_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "�������_���_idx" ON "�������" USING btree ("���");


--
-- TOC entry 2110 (class 1259 OID 72111)
-- Dependencies: 1665
-- Name: ���������_���_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "���������_���_idx" ON "���������" USING btree ("���");


--
-- TOC entry 2111 (class 1259 OID 72112)
-- Dependencies: 1665
-- Name: ���������_���_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "���������_���_idx" ON "���������" USING btree ("���");


--
-- TOC entry 2114 (class 1259 OID 72113)
-- Dependencies: 1667
-- Name: ����������_���_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "����������_���_idx" ON "����������" USING btree ("���");


--
-- TOC entry 2115 (class 1259 OID 72114)
-- Dependencies: 1667
-- Name: ����������_���_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "����������_���_idx" ON "����������" USING btree ("���");


--
-- TOC entry 2089 (class 1259 OID 72115)
-- Dependencies: 1648 1648 1648
-- Name: ��������_�����_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "��������_�����_idx" ON "��������" USING btree ("������", "�����", "������");


--
-- TOC entry 2090 (class 1259 OID 72116)
-- Dependencies: 1648 1648
-- Name: ��������_������_����_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "��������_������_����_idx" ON "��������" USING btree ("������", "����");


--
-- TOC entry 2091 (class 1259 OID 72117)
-- Dependencies: 1648
-- Name: ��������_������_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "��������_������_idx" ON "��������" USING btree ("������");


--
-- TOC entry 2092 (class 1259 OID 72118)
-- Dependencies: 1648 1648 1648
-- Name: ��������_������_����_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "��������_������_����_idx" ON "��������" USING btree ("������", "����", "���������");


--
-- TOC entry 2093 (class 1259 OID 72119)
-- Dependencies: 1648 1648
-- Name: ��������_������_���_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "��������_������_���_idx" ON "��������" USING btree ("������", "���");


--
-- TOC entry 2094 (class 1259 OID 72120)
-- Dependencies: 1648
-- Name: ��������_���_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "��������_���_idx" ON "��������" USING btree ("���");


--
-- TOC entry 2095 (class 1259 OID 72121)
-- Dependencies: 1648 1648 1648
-- Name: ��������_�����_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "��������_�����_idx" ON "��������" USING btree ("������", "�����", "������");


--
-- TOC entry 2096 (class 1259 OID 72122)
-- Dependencies: 1648 1648
-- Name: ��������_������_����_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "��������_������_����_idx" ON "��������" USING btree ("������", "����");


--
-- TOC entry 2097 (class 1259 OID 72123)
-- Dependencies: 1648 1648
-- Name: ��������_����_���������_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "��������_����_���������_idx" ON "��������" USING btree ("����", "���������");


--
-- TOC entry 2068 (class 1259 OID 72124)
-- Dependencies: 1637 1637
-- Name: ������_����_���_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "������_����_���_idx" ON "������" USING btree ("����", "���");


--
-- TOC entry 2100 (class 1259 OID 72125)
-- Dependencies: 1650
-- Name: �����������_���_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "�����������_���_idx" ON "�����������" USING btree ("���");


--
-- TOC entry 2101 (class 1259 OID 72126)
-- Dependencies: 1650
-- Name: �����������_���_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "�����������_���_idx" ON "�����������" USING btree ("���");


--
-- TOC entry 2071 (class 1259 OID 72127)
-- Dependencies: 1638
-- Name: �����_���_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "�����_���_idx" ON "�����" USING btree ("���");


--
-- TOC entry 2072 (class 1259 OID 72128)
-- Dependencies: 1638
-- Name: �����_���_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "�����_���_idx" ON "�����" USING btree ("���");


--
-- TOC entry 2118 (class 1259 OID 72129)
-- Dependencies: 1673
-- Name: ������������_���_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "������������_���_idx" ON "������������" USING btree ("���");


--
-- TOC entry 2119 (class 1259 OID 72130)
-- Dependencies: 1673
-- Name: ������������_���_idx; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "������������_���_idx" ON "������������" USING btree ("���");


--
-- TOC entry 2137 (class 2620 OID 72131)
-- Dependencies: 19 1650
-- Name: test_�����������������; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "test_�����������������" BEFORE DELETE ON "�����������" FOR EACH ROW EXECUTE PROCEDURE "�����������������"();


--
-- TOC entry 2128 (class 2620 OID 72132)
-- Dependencies: 24 1637
-- Name: testdeleting_������; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_������" BEFORE DELETE ON "������" FOR EACH ROW EXECUTE PROCEDURE "testdeleting_������"();


--
-- TOC entry 2131 (class 2620 OID 72133)
-- Dependencies: 26 1640
-- Name: testdeleting_�����������; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_�����������" BEFORE DELETE ON "�����������" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2133 (class 2620 OID 72134)
-- Dependencies: 26 1645
-- Name: testdeleting_������; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_������" BEFORE DELETE ON "������" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2139 (class 2620 OID 72135)
-- Dependencies: 1663 26
-- Name: testdeleting_�������; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_�������" BEFORE DELETE ON "�������" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2140 (class 2620 OID 72136)
-- Dependencies: 1665 26
-- Name: testdeleting_���������; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_���������" BEFORE DELETE ON "���������" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2144 (class 2620 OID 72179)
-- Dependencies: 1680 26
-- Name: testdeleting_������������; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_������������" BEFORE DELETE ON "������������" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2141 (class 2620 OID 72137)
-- Dependencies: 1667 26
-- Name: testdeleting_����������; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_����������" BEFORE DELETE ON "����������" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2145 (class 2620 OID 72199)
-- Dependencies: 1682 26
-- Name: testdeleting_����������1; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_����������1" BEFORE DELETE ON "����������1" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2146 (class 2620 OID 72209)
-- Dependencies: 26 1684
-- Name: testdeleting_����������2; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_����������2" BEFORE DELETE ON "����������2" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2138 (class 2620 OID 72138)
-- Dependencies: 1650 26
-- Name: testdeleting_�����������; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_�����������" BEFORE DELETE ON "�����������" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2130 (class 2620 OID 72139)
-- Dependencies: 26 1638
-- Name: testdeleting_�����; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_�����" BEFORE DELETE ON "�����" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2142 (class 2620 OID 72140)
-- Dependencies: 1673 26
-- Name: testdeleting_������������; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testdeleting_������������" BEFORE DELETE ON "������������" FOR EACH ROW EXECUTE PROCEDURE testdeletingdictobject();


--
-- TOC entry 2143 (class 2620 OID 72148)
-- Dependencies: 1676 30
-- Name: testupdating_�����; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testupdating_�����" BEFORE UPDATE ON "�����" FOR EACH ROW EXECUTE PROCEDURE testupdatingid();


--
-- TOC entry 2134 (class 2620 OID 72141)
-- Dependencies: 33 1648
-- Name: ����������������; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "����������������" BEFORE INSERT ON "��������" FOR EACH ROW EXECUTE PROCEDURE "����������������"();


--
-- TOC entry 2129 (class 2620 OID 72142)
-- Dependencies: 34 1637
-- Name: ���������������������; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "���������������������" BEFORE INSERT OR UPDATE ON "������" FOR EACH ROW EXECUTE PROCEDURE "���������������������"();


--
-- TOC entry 2135 (class 2620 OID 72143)
-- Dependencies: 1648 35
-- Name: ���������������; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "���������������" BEFORE UPDATE ON "��������" FOR EACH ROW EXECUTE PROCEDURE "���������������"();


--
-- TOC entry 2132 (class 2620 OID 72144)
-- Dependencies: 1643 36
-- Name: ���������������; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "���������������" BEFORE DELETE ON "���������" FOR EACH ROW EXECUTE PROCEDURE "���������������"();


--
-- TOC entry 2136 (class 2620 OID 72145)
-- Dependencies: 1648 37
-- Name: ���������������; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "���������������" BEFORE DELETE ON "��������" FOR EACH ROW EXECUTE PROCEDURE "���������������"();


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
-- Name: ������; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "������" FROM PUBLIC;
REVOKE ALL ON TABLE "������" FROM sa;
GRANT ALL ON TABLE "������" TO sa;


--
-- TOC entry 2183 (class 0 OID 0)
-- Dependencies: 1638
-- Name: �����; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "�����" FROM PUBLIC;
REVOKE ALL ON TABLE "�����" FROM sa;
GRANT ALL ON TABLE "�����" TO sa;


--
-- TOC entry 2184 (class 0 OID 0)
-- Dependencies: 1639
-- Name: vw_������; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_������" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_������" FROM sa;
GRANT ALL ON TABLE "vw_������" TO sa;


--
-- TOC entry 2185 (class 0 OID 0)
-- Dependencies: 1640
-- Name: �����������; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "�����������" FROM PUBLIC;
REVOKE ALL ON TABLE "�����������" FROM sa;
GRANT ALL ON TABLE "�����������" TO sa;
GRANT SELECT ON TABLE "�����������" TO PUBLIC;


--
-- TOC entry 2186 (class 0 OID 0)
-- Dependencies: 1641
-- Name: ������������; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "������������" FROM PUBLIC;
REVOKE ALL ON TABLE "������������" FROM sa;
GRANT ALL ON TABLE "������������" TO sa;
GRANT SELECT ON TABLE "������������" TO PUBLIC;
GRANT SELECT ON TABLE "������������" TO test;


--
-- TOC entry 2187 (class 0 OID 0)
-- Dependencies: 1642
-- Name: vw_�����������; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_�����������" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_�����������" FROM sa;
GRANT ALL ON TABLE "vw_�����������" TO sa;


--
-- TOC entry 2188 (class 0 OID 0)
-- Dependencies: 1643
-- Name: ���������; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "���������" FROM PUBLIC;
REVOKE ALL ON TABLE "���������" FROM sa;
GRANT ALL ON TABLE "���������" TO sa;


--
-- TOC entry 2189 (class 0 OID 0)
-- Dependencies: 1645
-- Name: ������; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "������" FROM PUBLIC;
REVOKE ALL ON TABLE "������" FROM sa;
GRANT ALL ON TABLE "������" TO sa;


--
-- TOC entry 2190 (class 0 OID 0)
-- Dependencies: 1646
-- Name: vw_������; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_������" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_������" FROM sa;
GRANT ALL ON TABLE "vw_������" TO sa;
GRANT SELECT ON TABLE "vw_������" TO PUBLIC;


--
-- TOC entry 2191 (class 0 OID 0)
-- Dependencies: 1647
-- Name: vw_������������; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_������������" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_������������" FROM sa;
GRANT ALL ON TABLE "vw_������������" TO sa;
GRANT SELECT ON TABLE "vw_������������" TO test;


--
-- TOC entry 2192 (class 0 OID 0)
-- Dependencies: 1648
-- Name: ��������; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "��������" FROM PUBLIC;
REVOKE ALL ON TABLE "��������" FROM sa;
GRANT ALL ON TABLE "��������" TO sa;


--
-- TOC entry 2193 (class 0 OID 0)
-- Dependencies: 1650
-- Name: �����������; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "�����������" FROM PUBLIC;
REVOKE ALL ON TABLE "�����������" FROM sa;
GRANT ALL ON TABLE "�����������" TO sa;
GRANT SELECT ON TABLE "�����������" TO PUBLIC;


--
-- TOC entry 2194 (class 0 OID 0)
-- Dependencies: 1651
-- Name: �����; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "�����" FROM PUBLIC;
REVOKE ALL ON TABLE "�����" FROM sa;
GRANT ALL ON TABLE "�����" TO sa;


--
-- TOC entry 2195 (class 0 OID 0)
-- Dependencies: 1652
-- Name: vw_�����������_��_���������; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_�����������_��_���������" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_�����������_��_���������" FROM sa;
GRANT ALL ON TABLE "vw_�����������_��_���������" TO sa;


--
-- TOC entry 2196 (class 0 OID 0)
-- Dependencies: 1653
-- Name: �������; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "�������" FROM PUBLIC;
REVOKE ALL ON TABLE "�������" FROM sa;
GRANT ALL ON TABLE "�������" TO sa;


--
-- TOC entry 2197 (class 0 OID 0)
-- Dependencies: 1685
-- Name: vw_�������; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_�������" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_�������" FROM sa;
GRANT ALL ON TABLE "vw_�������" TO sa;


--
-- TOC entry 2198 (class 0 OID 0)
-- Dependencies: 1686
-- Name: vw_�������_����; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_�������_����" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_�������_����" FROM sa;
GRANT ALL ON TABLE "vw_�������_����" TO sa;


--
-- TOC entry 2199 (class 0 OID 0)
-- Dependencies: 1654
-- Name: vw_�����; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_�����" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_�����" FROM sa;
GRANT ALL ON TABLE "vw_�����" TO sa;
GRANT SELECT ON TABLE "vw_�����" TO PUBLIC;


--
-- TOC entry 2200 (class 0 OID 0)
-- Dependencies: 1655
-- Name: vw_�����; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "vw_�����" FROM PUBLIC;
REVOKE ALL ON TABLE "vw_�����" FROM sa;
GRANT ALL ON TABLE "vw_�����" TO sa;


--
-- TOC entry 2207 (class 0 OID 0)
-- Dependencies: 1659
-- Name: ������_�_��������; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "������_�_��������" FROM PUBLIC;
REVOKE ALL ON TABLE "������_�_��������" FROM sa;
GRANT ALL ON TABLE "������_�_��������" TO sa;
GRANT SELECT ON TABLE "������_�_��������" TO PUBLIC;


--
-- TOC entry 2208 (class 0 OID 0)
-- Dependencies: 1660
-- Name: ������_�_������; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "������_�_������" FROM PUBLIC;
REVOKE ALL ON TABLE "������_�_������" FROM sa;
GRANT ALL ON TABLE "������_�_������" TO sa;
GRANT SELECT ON TABLE "������_�_������" TO PUBLIC;


--
-- TOC entry 2209 (class 0 OID 0)
-- Dependencies: 1661
-- Name: ������_�_������������; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "������_�_������������" FROM PUBLIC;
REVOKE ALL ON TABLE "������_�_������������" FROM sa;
GRANT ALL ON TABLE "������_�_������������" TO sa;
GRANT SELECT ON TABLE "������_�_������������" TO PUBLIC;


--
-- TOC entry 2210 (class 0 OID 0)
-- Dependencies: 1662
-- Name: ������_�_�����; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "������_�_�����" FROM PUBLIC;
REVOKE ALL ON TABLE "������_�_�����" FROM sa;
GRANT ALL ON TABLE "������_�_�����" TO sa;
GRANT SELECT ON TABLE "������_�_�����" TO PUBLIC;


--
-- TOC entry 2211 (class 0 OID 0)
-- Dependencies: 1663
-- Name: �������; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "�������" FROM PUBLIC;
REVOKE ALL ON TABLE "�������" FROM sa;
GRANT ALL ON TABLE "�������" TO sa;


--
-- TOC entry 2214 (class 0 OID 0)
-- Dependencies: 1665
-- Name: ���������; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "���������" FROM PUBLIC;
REVOKE ALL ON TABLE "���������" FROM sa;
GRANT ALL ON TABLE "���������" TO sa;
GRANT SELECT ON TABLE "���������" TO PUBLIC;


--
-- TOC entry 2217 (class 0 OID 0)
-- Dependencies: 1680
-- Name: ������������; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "������������" FROM PUBLIC;
REVOKE ALL ON TABLE "������������" FROM sa;
GRANT ALL ON TABLE "������������" TO sa;


--
-- TOC entry 2220 (class 0 OID 0)
-- Dependencies: 1667
-- Name: ����������; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "����������" FROM PUBLIC;
REVOKE ALL ON TABLE "����������" FROM sa;
GRANT ALL ON TABLE "����������" TO sa;


--
-- TOC entry 2225 (class 0 OID 0)
-- Dependencies: 1682
-- Name: ����������1; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "����������1" FROM PUBLIC;
REVOKE ALL ON TABLE "����������1" FROM sa;
GRANT ALL ON TABLE "����������1" TO sa;


--
-- TOC entry 2228 (class 0 OID 0)
-- Dependencies: 1684
-- Name: ����������2; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "����������2" FROM PUBLIC;
REVOKE ALL ON TABLE "����������2" FROM sa;
GRANT ALL ON TABLE "����������2" TO sa;


--
-- TOC entry 2237 (class 0 OID 0)
-- Dependencies: 1673
-- Name: ������������; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "������������" FROM PUBLIC;
REVOKE ALL ON TABLE "������������" FROM sa;
GRANT ALL ON TABLE "������������" TO sa;


--
-- TOC entry 2242 (class 0 OID 0)
-- Dependencies: 1676
-- Name: �����; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "�����" FROM PUBLIC;
REVOKE ALL ON TABLE "�����" FROM sa;
GRANT ALL ON TABLE "�����" TO sa;
GRANT SELECT ON TABLE "�����" TO PUBLIC;


-- Completed on 2013-08-20 23:39:20

--
-- PostgreSQL database dump complete
--

