-- View: vw_saldo411_1

-- DROP VIEW vw_saldo411_1;

CREATE OR REPLACE VIEW public.vw_saldo411_1 AS 
 SELECT "сальдо"."КОД",
    "набор1"."КОД_ТОВАР",
    "набор1"."КОД_ГРУППЫ",
    "набор1"."КОД_АДРЕС",
    "сальдо"."КОНКОЛ",
    "сальдо"."КОНЦЕНА",
    "сальдо"."КОНСАЛЬДО",
    "сальдо"."КОНСАЛЬДО" + s1."КОНСАЛЬДО" AS "ЗАКСУММА"
   FROM "сальдо"
     JOIN ( SELECT s."КОД",
            s."КОД_ТОВАР",
            s."КОД_АДРЕС",
            t."КОД_ГРУППЫ"
           FROM "набор1" s
             JOIN "товар" t ON s."КОД_ТОВАР" = t."КОД") "набор1" ON "сальдо"."КОД" = "набор1"."КОД"
     JOIN "сальдо" s1 ON s1."СЧЕТ" = '421'::bpchar AND "сальдо"."КОД" = s1."КОД"
  WHERE "сальдо"."СЧЕТ" = '411'::bpchar AND "сальдо"."КОНКОЛ" <> 0::numeric AND "набор1"."КОД_АДРЕС" <> (SELECT КОД FROM vw_кодадресбрак);

ALTER TABLE vw_saldo411_1
  OWNER TO sa;
GRANT ALL ON TABLE vw_saldo411_1 TO sa;
GRANT SELECT ON TABLE vw_saldo411_1 TO "продавец";
