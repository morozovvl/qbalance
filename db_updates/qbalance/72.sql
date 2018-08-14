﻿-- View: "vw_новыецены"

-- DROP VIEW "vw_новыецены";

CREATE OR REPLACE VIEW "vw_новыецены" AS 
 SELECT DISTINCT t."КОД",
    t."КОД_АДРЕС",
    t."КОД_ТОВАР",
    t."ИМЯ",
    t."КОД_ГРУППЫ",
    t."ЗАКЦЕНА",
    t."ЦЕНА",
    t."НАЦЕНКА",
    t."НОВЦЕНА"::numeric(10,2) AS "НОВЦЕНА",
    t."НОВНАЦЕНКА",
    t."АВТОМАТ_ЦЕНА",
    t."КОЛ",
    t."ТИП"
   FROM ( SELECT d."КОД",
            d."КОД_АДРЕС",
            d."КОД_ТОВАР",
            d."ИМЯ",
            d."КОД_ГРУППЫ",
            d."ЗАКЦЕНА",
            d."ЦЕНА",
            d."НАЦЕНКА",
                CASE
                    WHEN d."ОКРУГЛЕНИЕ" = 1::numeric THEN round(d."НОВЦЕНА" * 2::numeric, 0) / 2::numeric
                    WHEN d."ОКРУГЛЕНИЕ" = 2::numeric THEN round(d."НОВЦЕНА", 0)
                    WHEN d."ОКРУГЛЕНИЕ" = 3::numeric THEN round(d."НОВЦЕНА", (-1))
                    WHEN d."ОКРУГЛЕНИЕ" = 4::numeric THEN round(d."НОВЦЕНА", (-2))
                    ELSE d."НОВЦЕНА"
                END AS "НОВЦЕНА",
            d."НОВНАЦЕНКА",
            d."АВТОМАТ_ЦЕНА",
            d."КОЛ",
            d."ТИП"
           FROM ( SELECT t_1."КОД",
                    t_1."КОД_АДРЕС",
                    t_1."КОД_ТОВАР",
                    t_1."ИМЯ",
                    t_1."КОД_ГРУППЫ",
                    t_1."ЗАКЦЕНА",
                    t_1."ЦЕНА",
                    (t_1."НАЦЕНКА" * 100::numeric)::numeric(10,2) AS "НАЦЕНКА",
                    (t_1."НОВНАЦЕНКА" * 100::numeric)::numeric(10,2) AS "НОВНАЦЕНКА",
                        CASE
                            WHEN (t_1."НАЦЕНКА" < t_1."МИНПРОЦЕНТ" OR t_1."НАЦЕНКА" > t_1."МАКСПРОЦЕНТ") AND (t_1."ЗАКЦЕНА" * (t_1."НОВНАЦЕНКА" + 1::numeric)) < (t_1."ЦЕНА" * (1::numeric - s."ПРОЦЕНТ" / 100::numeric)) THEN (t_1."ЦЕНА" * (1::numeric - s."ПРОЦЕНТ" / 100::numeric))::numeric(10,2)
                            ELSE (t_1."ЗАКЦЕНА" * (t_1."НОВНАЦЕНКА" + 1::numeric))::numeric(10,2)
                        END AS "НОВЦЕНА",
                    t_1."ОКРУГЛЕНИЕ",
                    t_1."АВТОМАТ_ЦЕНА",
                    t_1."КОЛ",
                    t_1."ТИП"
                   FROM ( SELECT t_2."КОД",
                            t_2."ЗАКЦЕНА",
                            t_2."КОД_АДРЕС",
                            t_2."КОД_ТОВАР",
                            t_2."ИМЯ",
                            t_2."КОД_ГРУППЫ",
                            t_2."ЦЕНА",
                            t_2."НАЦЕНКА",
                            t_2."АВТОМАТ_ЦЕНА",
                            t_2."КОЛ",
                            t_2."ТИП",
                            n."МИНПРОЦЕНТ",
                            n."МАКСПРОЦЕНТ",
                            n."НАЦЕНКА" AS "НОВНАЦЕНКА",
                            n."ОКРУГЛЕНИЕ"
                           FROM ( SELECT v."КОД",
                                    s_1."ЗАКЦЕНА",
                                    v."КОД_АДРЕС",
                                    v."КОД_ТОВАР",
                                    v."ИМЯ",
                                    v."КОД_ГРУППЫ",
                                    v."ЦЕНА",
                                    (COALESCE(v."ЦЕНА", 0::numeric) - s_1."ЗАКЦЕНА") / s_1."ЗАКЦЕНА" AS "НАЦЕНКА",
                                    v."АВТОМАТ_ЦЕНА",
                                    v."КОЛ",
                                    v."ТИП"
                                   FROM "vw_закупоч_цены_на_новый_товар" v
                                     JOIN (SELECT v."КОД_ТОВАР",
    v."ТИП",
    round(sum(v."КОЛ" * v."ЗАКЦЕНА") / sum(v."КОЛ"), 2)::numeric(10,2) AS "ЗАКЦЕНА"
   FROM "vw_закупоч_цены_на_новый_товар" v
     LEFT JOIN "адрес" ON v."КОД_АДРЕС" = "адрес"."КОД"
  WHERE v."КОЛ" > 0::numeric
  GROUP BY v."КОД_ТОВАР", v."ТИП") s_1 ON v."КОД_ТОВАР" = s_1."КОД_ТОВАР" AND v."ТИП" = s_1."ТИП"
                                  WHERE s_1."ЗАКЦЕНА" <> 0::numeric) t_2
                             JOIN ( SELECT "наценки"."КОД_ГРУППЫ",
                                    "наценки"."МИНПРОЦЕНТ" / 100::numeric AS "МИНПРОЦЕНТ",
                                    "наценки"."МАКСПРОЦЕНТ" / 100::numeric AS "МАКСПРОЦЕНТ",
                                    ("наценки"."НАЦЕНКА" + s_1."НАЦЕНКА") / 100::numeric AS "НАЦЕНКА",
                                    s_1."НАЦЕНКА" / 100::numeric AS "ДОПНАЦЕНКА",
                                    "наценки"."ОКРУГЛЕНИЕ",
                                    "наценки"."МИНПОРОГСУММА",
                                    "наценки"."МАКСПОРОГСУММА"
                                   FROM "наценки",
                                    ( SELECT "константы"."ЗНАЧЕНИЕ"::numeric AS "НАЦЕНКА"
   FROM "константы"
  WHERE "константы"."ИМЯ"::text = 'ДополнительнаяНаценка'::text) s_1) n ON t_2."ЗАКЦЕНА" >= n."МИНПОРОГСУММА" AND t_2."ЗАКЦЕНА" < n."МАКСПОРОГСУММА" AND t_2."КОД_ГРУППЫ" = n."КОД_ГРУППЫ"
                          WHERE t_2."НАЦЕНКА" < n."МИНПРОЦЕНТ" OR t_2."НАЦЕНКА" > (n."МАКСПРОЦЕНТ" + n."ДОПНАЦЕНКА")) t_1,
                    ( SELECT "константы"."ЗНАЧЕНИЕ"::numeric(10,5) AS "ПРОЦЕНТ"
                           FROM "константы"
                          WHERE rtrim("константы"."ИМЯ"::text) = 'ПроцентСнижения'::text) s) d) t
  WHERE COALESCE(t."ЦЕНА", 0::numeric) <> t."НОВЦЕНА"
  ORDER BY t."КОД", t."КОД_АДРЕС", t."КОД_ТОВАР", t."ИМЯ", t."КОД_ГРУППЫ", t."ЗАКЦЕНА", t."ЦЕНА", t."НАЦЕНКА", t."НОВЦЕНА"::numeric(10,2), t."НОВНАЦЕНКА", t."АВТОМАТ_ЦЕНА", t."КОЛ";

ALTER TABLE "vw_новыецены"
  OWNER TO sa;
GRANT ALL ON TABLE "vw_новыецены" TO sa;