﻿CREATE OR REPLACE FUNCTION sp_getconst(cName VARCHAR)
  RETURNS BOOLEAN AS
$BODY$
DECLARE
	val VARCHAR;
BEGIN
	val := (SELECT TRIM(ЗНАЧЕНИЕ) FROM константы WHERE ИМЯ = cName LIMIT 1);
	
	IF COALESCE(val, 'нет') = 'да'::VARCHAR THEN
		RETURN TRUE;
	END IF;
	RETURN FALSE;
END;
$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION sp_getconst(cName VARCHAR)
  OWNER TO sa;
GRANT EXECUTE ON FUNCTION sp_getconst(cName VARCHAR) TO public;  
