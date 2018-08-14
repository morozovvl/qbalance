CREATE OR REPLACE VIEW public.vw_кодадресбрак
AS
 SELECT "КОД"
 FROM "адрес"
 WHERE UPPER(ИМЯ) = 'БРАК'
 LIMIT 1;

ALTER TABLE vw_кодадресбрак OWNER TO sa;
GRANT SELECT ON TABLE vw_кодадресбрак TO "public";
