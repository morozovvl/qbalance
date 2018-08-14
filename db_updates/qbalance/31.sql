﻿-- View: "vw_заказы"

-- DROP VIEW "vw_заказы";

CREATE OR REPLACE VIEW "vw_заказы" AS 
 SELECT p."ДОККОД",
    p."КОДЗАКАЗ",
    p."СТР",
    p."КОДДОКЗАКАЗ",
    p."СТРДОКЗАКАЗ",
    s."КОД" AS "КОД_ПРАЙС",
    p."КОЛ",
    p."ЦЕНА",
    p."ВЫПОЛНЕН"
   FROM ( SELECT a."ДОККОД",
            a."КОДЗАКАЗ",
            a."СТР",
            a."КОДДОКЗАКАЗ",
            a."СТРДОКЗАКАЗ",
            p_1."ДБКОД",
            p_1."КОЛ",
            p_1."ЦЕНА",
            a."ВЫПОЛНЕН"
           FROM "проводки" p_1
             JOIN ( SELECT d_1."КОД",
                    d_1."ДАТА",
                    d_1."ДАТАВРЕМЯ",
                    d_1."НОМЕР",
                    d_1."КОММЕНТАРИЙ",
                    d_1."СУММА",
                    d_1."ОПИСАНИЕ",
                    d_1."ОПЕР",
                    d_1."АВТО",
                    d_1."ПЕРЕМЕННЫЕ1",
                    d_1."ПЕРЕМЕННЫЕ",
                    d_1."КОД_ПЕРСОНАЛ"
                   FROM "документы" d_1
                     JOIN "докатрибуты129" da ON d_1."КОД" = da."КОД"
                  WHERE NOT da."ЗАКРЫТ") d ON p_1."ДОККОД" = d."КОД"
             JOIN "атрибуты129" a ON p_1."ДОККОД" = a."ДОККОД" AND p_1."СТР" = a."СТР"
          WHERE p_1."ОПЕР" = 129::numeric) p
     LEFT JOIN "прайс" s ON p."ДБКОД" = s."КОД";

ALTER TABLE "vw_заказы"
  OWNER TO sa;
GRANT ALL ON TABLE "vw_заказы" TO sa;
GRANT SELECT ON TABLE "vw_заказы" TO public;