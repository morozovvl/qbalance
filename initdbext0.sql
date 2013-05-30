--
-- PostgreSQL database dump
--

-- Dumped from database version 9.1.5
-- Dumped by pg_dump version 9.1.5
-- Started on 2012-11-18 11:01:03 MSK

SET statement_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- TOC entry 163 (class 3079 OID 12223)
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- TOC entry 2445 (class 0 OID 0)
-- Dependencies: 163
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

--
-- TOC entry 175 (class 1255 OID 42457)
-- Dependencies: 5 490
-- Name: testupdatingid(); Type: FUNCTION; Schema: public; Owner: sa
--

CREATE FUNCTION testupdatingid() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	IF OLD.код <> NEW.код THEN
		RAISE EXCEPTION 'Запрещено изменять значение ключевого столбца';
		RETURN OLD;
	END IF;
	RETURN NEW;
END;
$$;


ALTER FUNCTION public.testupdatingid() OWNER TO sa;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- TOC entry 162 (class 1259 OID 42460)
-- Dependencies: 2433 5
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
-- TOC entry 161 (class 1259 OID 42458)
-- Dependencies: 5 162
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
-- TOC entry 2447 (class 0 OID 0)
-- Dependencies: 161
-- Name: файлы_код_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "файлы_код_seq" OWNED BY "файлы"."код";


--
-- TOC entry 2448 (class 0 OID 0)
-- Dependencies: 161
-- Name: файлы_код_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"файлы_код_seq"', 35, true);


--
-- TOC entry 2432 (class 2604 OID 42463)
-- Dependencies: 162 161 162
-- Name: код; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "файлы" ALTER COLUMN "код" SET DEFAULT nextval('"файлы_код_seq"'::regclass);


--
-- TOC entry 2437 (class 0 OID 42460)
-- Dependencies: 162 2438
-- Data for Name: файлы; Type: TABLE DATA; Schema: public; Owner: sa
--



--
-- TOC entry 2435 (class 2606 OID 42469)
-- Dependencies: 162 162 2439
-- Name: файлы_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "файлы"
    ADD CONSTRAINT "файлы_pkey" PRIMARY KEY ("код");


--
-- TOC entry 2436 (class 2620 OID 42470)
-- Dependencies: 162 175 2439
-- Name: testupdating_файлы; Type: TRIGGER; Schema: public; Owner: sa
--

CREATE TRIGGER "testupdating_файлы" BEFORE UPDATE ON "файлы" FOR EACH ROW EXECUTE PROCEDURE testupdatingid();


--
-- TOC entry 2444 (class 0 OID 0)
-- Dependencies: 5
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- TOC entry 2446 (class 0 OID 0)
-- Dependencies: 162
-- Name: файлы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "файлы" FROM PUBLIC;
REVOKE ALL ON TABLE "файлы" FROM sa;
GRANT ALL ON TABLE "файлы" TO sa;
GRANT SELECT ON TABLE "файлы" TO PUBLIC;


-- Completed on 2012-11-18 11:01:03 MSK

--
-- PostgreSQL database dump complete
--

