-- Function: tsvectorupdate()

-- DROP FUNCTION tsvectorupdate();

CREATE OR REPLACE FUNCTION tsvectorupdate()
  RETURNS trigger AS
$BODY$
DECLARE
	_exp	VARCHAR(200);
	_words	TEXT[];
	_result VARCHAR(1000);
	_word	VARCHAR(100);
BEGIN
	_result = lower(trim(NEW."ИМЯ") || ' ' || trim(NEW."ШИФР_ПО_КАТАЛОГУ")  || ' ' || trim(NEW."АРТИКУЛ"));
--	_result = '';
--	_exp = lower(trim(NEW."ИМЯ") || ' ' || trim(NEW."ШИФР_ПО_КАТАЛОГУ")  || ' ' || trim(NEW."АРТИКУЛ"));
--	SELECT regexp_split_to_array(_exp, E'\\s+') INTO _words;
--	FOR i IN 1..array_length(_words, 1) LOOP
--		IF char_length(_result) > 0 THEN
--			_result = _result || '|';
--		END IF;
--		_result = _result || _words[i];
--		_word = (SELECT ИМЯ1 FROM синонимы WHERE ИМЯ = _words[i] LIMIT 1);
--		IF char_length(_word) > 0 AND position(_word in _result) = 0 THEN
--			_result = _result || '|' || _word;
--		END IF;
--		_word = (SELECT ИМЯ FROM синонимы WHERE ИМЯ1 = _words[i] LIMIT 1);
--		IF char_length(_word) > 0 AND position(_word in _result) = 0 THEN
--			_result = _result || '|' || _word;
--		END IF;
--	END LOOP;
	NEW.fts = to_tsvector(replace(replace(replace(_result, '-', ' '), ',', ' '), '.', ' '));
	RETURN NEW;
END;
$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION tsvectorupdate()
  OWNER TO sa;
