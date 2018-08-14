-- View: "vw_новыецены3"

-- DROP VIEW "vw_новыецены3";

CREATE OR REPLACE VIEW "vw_новыецены3" AS 
 SELECT p."КОД",
    p."КОД_ТОВАР",
    COALESCE(p."КОД_АДРЕС", 0) AS "КОД_АДРЕС",
    p."КОЛ",
    p."ЗАКЦЕНА",
    COALESCE(p."ЦЕНА", 0::numeric)::numeric(10,2) AS "ЦЕНА",
    p."НАЦЕНКА",
    p."НОВЦЕНА",
    p."НОВНАЦЕНКА"
   FROM "vw_новыецены" p
     JOIN "группы" g ON p."КОД_ГРУППЫ" = g."КОД"
     JOIN "товар" t ON p."КОД_ТОВАР" = t."КОД"
     LEFT JOIN "адрес" a ON p."КОД_АДРЕС" = a."КОД"
  WHERE p."АВТОМАТ_ЦЕНА" = true AND (p."НОВЦЕНА" <> COALESCE(p."ЦЕНА", 0::numeric) AND g."ЦЕНЫ_СНИЖАТЬ" = true OR p."НОВЦЕНА" > p."ЦЕНА" AND g."ЦЕНЫ_СНИЖАТЬ" = false) AND NOT t."ЦЕНАФИКСИРОВАНА"
  ORDER BY t."ИМЯ", a."ИМЯ";

ALTER TABLE "vw_новыецены3"
  OWNER TO sa;
GRANT ALL ON TABLE "vw_новыецены3" TO sa;
