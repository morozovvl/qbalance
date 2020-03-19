--
-- PostgreSQL database dump
--

-- Dumped from database version 9.3.10
-- Dumped by pg_dump version 9.3.10
-- Started on 2015-12-16 14:42:16 MSK

SET statement_timeout = 0;
SET lock_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- TOC entry 172 (class 3079 OID 12350)
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- TOC entry 2544 (class 0 OID 0)
-- Dependencies: 172
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- TOC entry 170 (class 1259 OID 217259)
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
-- TOC entry 171 (class 1259 OID 217266)
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
-- TOC entry 2546 (class 0 OID 0)
-- Dependencies: 171
-- Name: файлы_КОД_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: sa
--

ALTER SEQUENCE "файлы_КОД_seq" OWNED BY "файлы"."КОД";


--
-- TOC entry 2424 (class 2604 OID 217268)
-- Name: КОД; Type: DEFAULT; Schema: public; Owner: sa
--

ALTER TABLE ONLY "файлы" ALTER COLUMN "КОД" SET DEFAULT nextval('"файлы_КОД_seq"'::regclass);


--
-- TOC entry 2535 (class 0 OID 217259)
-- Dependencies: 170
-- Data for Name: файлы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "файлы" ("КОД", "ИМЯ", "ТИП", "ЗНАЧЕНИЕ", "КОНТРСУММА") FROM stdin;
\.


--
-- TOC entry 2547 (class 0 OID 0)
-- Dependencies: 171
-- Name: файлы_КОД_seq; Type: SEQUENCE SET; Schema: public; Owner: sa
--

SELECT pg_catalog.setval('"файлы_КОД_seq"', 948, true);


--
-- TOC entry 2427 (class 2606 OID 217282)
-- Name: файлы_pkey; Type: CONSTRAINT; Schema: public; Owner: sa; Tablespace: 
--

ALTER TABLE ONLY "файлы"
    ADD CONSTRAINT "файлы_pkey" PRIMARY KEY ("КОД");


--
-- TOC entry 2425 (class 1259 OID 217283)
-- Name: ИМЯ_ТИП; Type: INDEX; Schema: public; Owner: sa; Tablespace: 
--

CREATE INDEX "ИМЯ_ТИП" ON "файлы" USING btree ("ИМЯ", "ТИП");


--
-- TOC entry 2543 (class 0 OID 0)
-- Dependencies: 6
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- TOC entry 2545 (class 0 OID 0)
-- Dependencies: 170
-- Name: файлы; Type: ACL; Schema: public; Owner: sa
--

REVOKE ALL ON TABLE "файлы" FROM PUBLIC;
REVOKE ALL ON TABLE "файлы" FROM sa;
GRANT ALL ON TABLE "файлы" TO sa;
GRANT SELECT ON TABLE "файлы" TO PUBLIC;


-- Completed on 2015-12-16 14:42:16 MSK

--
-- PostgreSQL database dump complete
--

