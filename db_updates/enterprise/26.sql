UPDATE "справочники" SET "ИМЯ_В_СПИСКЕ" = '', "ИМЯ_В_ФОРМЕ" = 'Отправленные СМС' WHERE trim("ИМЯ") = 'смс_отправленные';
DELETE FROM "столбцы" WHERE "КОД_VW_СПРАВОЧНИКИ_СО_СТОЛБЦАМИ" = 99;
INSERT INTO "столбцы" ("КОД_VW_СПРАВОЧНИКИ_СО_СТОЛБЦАМИ", "ИМЯ", "ЗАГОЛОВОК", "НОМЕР", "ТОЛЬКОЧТЕНИЕ", "КОДТАБЛИЦЫ") VALUES (99, 'ИМЯ', 'Телефон', 1, true, 99);
INSERT INTO "столбцы" ("КОД_VW_СПРАВОЧНИКИ_СО_СТОЛБЦАМИ", "ИМЯ", "ЗАГОЛОВОК", "НОМЕР", "ТОЛЬКОЧТЕНИЕ", "КОДТАБЛИЦЫ") VALUES (99, 'ДАТАВРЕМЯ', 'Дата, время', 2, true, 99);
INSERT INTO "столбцы" ("КОД_VW_СПРАВОЧНИКИ_СО_СТОЛБЦАМИ", "ИМЯ", "ЗАГОЛОВОК", "НОМЕР", "ТОЛЬКОЧТЕНИЕ", "КОДТАБЛИЦЫ") VALUES (99, 'ТЕКСТ', 'Текст', 3, true, 99);
UPDATE "файлы" SET "ЗНАЧЕНИЕ" = decode('66756e6374696f6e204576656e74416674657244656c657465537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d183d0b4d0b0d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b8d0b720d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a72657475726e20747275653b0a7d0a0a0a66756e6374696f6e204576656e74496e6974466f726d28666f726d290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a097461626c652e7365744f72646572436c617573652822d094d090d0a2d090d092d0a0d095d09cd0af204445534322293b0a7d0a0a0a66756e6374696f6e204576656e744265666f726548696465466f726d28666f726d290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b7d0b0d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f72654c696e655072696e74287374724e756d290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0b4d0be20d0bfd0b5d187d0b0d182d0b820d0bed187d0b5d180d0b5d0b4d0bdd0bed0b920d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd182d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744166746572526f774368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bfd0b5d180d0b5d0bcd0b5d189d0b5d0bdd0b8d18f20d0bdd0b020d0b4d180d183d0b3d183d18e20d181d182d180d0bed0bad1830a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7443617264436f64655265616465642863617264436f6465290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bfd180d0bed187d182d0b5d0bdd0b8d18f20d0bcd0b0d0b3d0bdd0b8d182d0bdd0bed0b920d0bad0b0d180d182d18b0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a72657475726e20747275653b0a7d0a0a0a66756e6374696f6e204576656e74416674657253686f77466f726d28666f726d290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bed182d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74417070656e6446726f6d51756572792871756572794e616d652c207265636f7264290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d0bad0b0d0b6d0b4d0bed0b920d0bdd0bed0b2d0bed0b920d0b7d0b0d0bfd0b8d181d0b820d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b02e20d095d181d0bbd0b820d0b3d0bed182d0bed0b2d0bed0b3d0be20d0b7d0b0d0bfd180d0bed181d0b020d0bdd0b020d181d0b5d180d0b2d0b5d180d0b520d0bdd0b5d1822c20d182d0be20d182d0bed0b3d0b4d0b020d0b2d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bed0b4d0b8d0bd20d180d0b0d0b720d0b820d181d0bad180d0b8d0bfd18220d181d0b0d0bc20d0b4d0bed0bbd0b6d0b5d0bd20d181d0bed0b7d0b4d0b0d182d18c20d0b820d0bed0b1d180d0b0d0b1d0bed182d0b0d182d18c20d0b7d0b0d0bfd180d0bed1812e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7443616c635461626c6528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d18fd187d0b5d0b9d0bad0b820d0b220d182d0b0d0b1d0bbd0b8d186d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e2047657446696c7465722866696c746572290a7b202f2f20d092d18bd0b7d0bed0b220d18dd182d0bed0b920d184d183d0bdd0bad186d0b8d0b820d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b7d0b0d0bfd180d0bed181d0bed0bc20d0ba20d091d0942e20d0a4d183d0bdd0bad186d0b8d18f20d0b4d0bed0bbd0b6d0bdd0b020d0b2d0b5d180d0bdd183d182d18c20d0b4d0bed0bfd0bed0bbd0bdd0b8d182d0b5d0bbd18cd0bdd18bd0b920d184d0b8d0bbd18cd182d18020d0ba20d0b7d0b0d0bfd180d0bed181d1832e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a72657475726e2066696c7465723b0a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74536574456e61626c656428656e61626c6564290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0b5d0b4d0bdd0b0d0b7d0bdd0b0d187d0b5d0bdd0be20d0b4d0bbd18f20d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d0b820d0b4d0bed181d182d183d0bfd0b020d0ba20d18dd0bbd0b5d0bcd0b5d0bdd182d0b0d0bc20d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18cd181d0bad0bed0b920d184d0bed180d0bcd18b0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74426172436f646552656164656428626172436f6465290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bfd180d0bed187d182d0b5d0bdd0b8d18f20d188d182d180d0b8d1852dd0bad0bed0b4d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265526f774368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b4d0be20d0bfd0b5d180d0b5d0bcd0b5d189d0b5d0bdd0b8d18f20d0bdd0b020d0b4d180d183d0b3d183d18e20d181d182d180d0bed0bad1830a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28666f726d290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a72657475726e20747275653b0a7d0a0a0a66756e6374696f6e204576656e7441667465724c696e655072696e74287374724e756d290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd0bed181d0bbd0b520d0bfd0b5d187d0b0d182d0b820d0bed187d0b5d180d0b5d0b4d0bdd0bed0b920d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd182d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726544656c657465537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b8d0b720d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a72657475726e20747275653b0a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744b657950726573736564286b65792c206d6f64696669657273290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b820d0bdd0b020d184d0bed180d0bcd0b52e20d094d0bed0bbd0b6d0bdd0be20d0b2d0b5d180d0bdd183d182d18c20d098d0a1d0a2d098d09dd0902c20d0b5d181d0bbd0b820d0bdd0b0d0b6d0b0d182d0b8d0b520d0bed0b1d180d0b0d0b1d0bed182d0b0d0bdd0be0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a72657475726e2066616c73653b0a7d0a0a0a66756e6374696f6e204576656e74416674657253686f774e657874446963747328290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bfd0bed0bad0b0d0b7d0b020d0b2d181d0b5d18520d0bdd0b5d0bed0b1d185d0bed0b4d0b8d0bcd18bd18520d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0bed0b220d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a72657475726e20747275653b0a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28666f726d290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7450686f746f4c6f6164656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0b3d180d183d0b7d0bad0b820d184d0bed182d0bed0b3d180d0b0d184d0b8d0b820d0b8d0b720d098d0bdd182d0b5d180d0bdd0b5d182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28666f726d290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744b657950726573736564286b65794576656e74290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bbd18ed0b1d0bed0b920d0bad0bdd0bed0bfd0bad0b820d0bdd0b020d184d0bed180d0bcd0b52e20d09fd0b0d180d0b0d0bcd0b5d182d180206b65794576656e7420d0b8d0bcd0b5d0b5d18220d182d0b8d0bf20514b65794576656e740a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e20507265706172655069637475726555726c286f626a656374290a7b202f2f20d092d18bd0b7d0bed0b220d18dd182d0bed0b920d184d183d0bdd0bad186d0b8d0b820d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e20d097d0b4d0b5d181d18c20d0b8d0bcd0b5d0b5d182d181d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d18c20d0b7d0b0d0b3d180d183d0b7d0b8d182d18c20d184d0bed182d0bed0b3d180d0b0d184d0b8d18e20d0b4d0bbd18f20d182d0b5d0bad183d189d0b5d0b3d0be20d0bed0b1d18ad0b5d0bad182d0b0206f626a65637420d0b8d0b720d098d0bdd182d0b5d180d0bdd0b5d182d0b02e20d0a4d183d0bdd0bad186d0b8d18f20d0b4d0bed0bbd0b6d0bdd0b020d0b2d0b5d180d0bdd183d182d18c2075726c20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74507265706172655072696e7456616c75657328290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d181d0bed0b7d0b4d0b0d0bdd0b8d0b5d0bc20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b020d0bfd0b5d187d0b0d182d0b820d0b820d0bfd180d0b5d0b4d0bdd0b0d0b7d0bdd0b0d187d0b5d0bdd0be20d0b4d0bbd18f20d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d0bdd0bed0b2d18bd18520d0b4d0b0d0bdd0bdd18bd18520d0b4d0bbd18f20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a', 'hex'), "КОНТРСУММА" = 658269019, "ДАТАВРЕМЯ" = now() WHERE "ИМЯ" = 'смс_отправленные.qs' AND "ТИП" = 0;
UPDATE "справочники" SET "ИМЯ_В_СПИСКЕ" = '', "ИМЯ_В_ФОРМЕ" = 'Отправленные СМС' WHERE trim("ИМЯ") = 'смс_отправленные';
DELETE FROM "столбцы" WHERE "КОД_VW_СПРАВОЧНИКИ_СО_СТОЛБЦАМИ" = 99;
INSERT INTO "столбцы" ("КОД_VW_СПРАВОЧНИКИ_СО_СТОЛБЦАМИ", "ИМЯ", "ЗАГОЛОВОК", "НОМЕР", "ТОЛЬКОЧТЕНИЕ", "КОДТАБЛИЦЫ") VALUES (99, 'ИМЯ', 'Телефон', 1, true, 99);
INSERT INTO "столбцы" ("КОД_VW_СПРАВОЧНИКИ_СО_СТОЛБЦАМИ", "ИМЯ", "ЗАГОЛОВОК", "НОМЕР", "ТОЛЬКОЧТЕНИЕ", "КОДТАБЛИЦЫ") VALUES (99, 'ДАТАВРЕМЯ', 'Дата, время', 2, true, 99);
INSERT INTO "столбцы" ("КОД_VW_СПРАВОЧНИКИ_СО_СТОЛБЦАМИ", "ИМЯ", "ЗАГОЛОВОК", "НОМЕР", "ТОЛЬКОЧТЕНИЕ", "КОДТАБЛИЦЫ") VALUES (99, 'ТЕКСТ', 'Текст', 3, true, 99);
UPDATE "файлы" SET "ЗНАЧЕНИЕ" = decode('66756e6374696f6e204576656e74416674657244656c657465537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d183d0b4d0b0d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b8d0b720d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a72657475726e20747275653b0a7d0a0a0a66756e6374696f6e204576656e74496e6974466f726d28666f726d290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d181d180d0b0d0b7d18320d0bfd0bed181d0bbd0b520d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a097461626c652e7365744f72646572436c617573652822d094d090d0a2d090d092d0a0d095d09cd0af204445534322293b0a7d0a0a0a66756e6374696f6e204576656e744265666f726548696465466f726d28666f726d290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b7d0b0d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f72654c696e655072696e74287374724e756d290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0b4d0be20d0bfd0b5d187d0b0d182d0b820d0bed187d0b5d180d0b5d0b4d0bdd0bed0b920d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd182d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744166746572526f774368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bfd0b5d180d0b5d0bcd0b5d189d0b5d0bdd0b8d18f20d0bdd0b020d0b4d180d183d0b3d183d18e20d181d182d180d0bed0bad1830a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7443617264436f64655265616465642863617264436f6465290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bfd180d0bed187d182d0b5d0bdd0b8d18f20d0bcd0b0d0b3d0bdd0b8d182d0bdd0bed0b920d0bad0b0d180d182d18b0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744166746572416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d18f20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a72657475726e20747275653b0a7d0a0a0a66756e6374696f6e204576656e74416674657253686f77466f726d28666f726d290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bed182d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74417070656e6446726f6d51756572792871756572794e616d652c207265636f7264290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d0bad0b0d0b6d0b4d0bed0b920d0bdd0bed0b2d0bed0b920d0b7d0b0d0bfd0b8d181d0b820d0b8d0b720d0b7d0b0d0bfd180d0bed181d0b02e20d095d181d0bbd0b820d0b3d0bed182d0bed0b2d0bed0b3d0be20d0b7d0b0d0bfd180d0bed181d0b020d0bdd0b020d181d0b5d180d0b2d0b5d180d0b520d0bdd0b5d1822c20d182d0be20d182d0bed0b3d0b4d0b020d0b2d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bed0b4d0b8d0bd20d180d0b0d0b720d0b820d181d0bad180d0b8d0bfd18220d181d0b0d0bc20d0b4d0bed0bbd0b6d0b5d0bd20d181d0bed0b7d0b4d0b0d182d18c20d0b820d0bed0b1d180d0b0d0b1d0bed182d0b0d182d18c20d0b7d0b0d0bfd180d0bed1812e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7443616c635461626c6528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d18fd187d0b5d0b9d0bad0b820d0b220d182d0b0d0b1d0bbd0b8d186d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e2047657446696c7465722866696c746572290a7b202f2f20d092d18bd0b7d0bed0b220d18dd182d0bed0b920d184d183d0bdd0bad186d0b8d0b820d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b7d0b0d0bfd180d0bed181d0bed0bc20d0ba20d091d0942e20d0a4d183d0bdd0bad186d0b8d18f20d0b4d0bed0bbd0b6d0bdd0b020d0b2d0b5d180d0bdd183d182d18c20d0b4d0bed0bfd0bed0bbd0bdd0b8d182d0b5d0bbd18cd0bdd18bd0b920d184d0b8d0bbd18cd182d18020d0ba20d0b7d0b0d0bfd180d0bed181d1832e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a72657475726e2066696c7465723b0a7d0a0a0a66756e6374696f6e204576656e74506172616d65746572734368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b220d0bcd0bed0bcd0b5d0bdd18220d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0bfd0bed181d182d0bed18fd0bdd0bdd0bed0b3d0be20d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0b020d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74536574456e61626c656428656e61626c6564290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0b5d0b4d0bdd0b0d0b7d0bdd0b0d187d0b5d0bdd0be20d0b4d0bbd18f20d0b8d0b7d0bcd0b5d0bdd0b5d0bdd0b8d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d0b820d0b4d0bed181d182d183d0bfd0b020d0ba20d18dd0bbd0b5d0bcd0b5d0bdd182d0b0d0bc20d0bfd0bed0bbd18cd0b7d0bed0b2d0b0d182d0b5d0bbd18cd181d0bad0bed0b920d184d0bed180d0bcd18b0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74426172436f646552656164656428626172436f6465290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bfd180d0bed187d182d0b5d0bdd0b8d18f20d188d182d180d0b8d1852dd0bad0bed0b4d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265526f774368616e67656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0b4d0be20d0bfd0b5d180d0b5d0bcd0b5d189d0b5d0bdd0b8d18f20d0bdd0b020d0b4d180d183d0b3d183d18e20d181d182d180d0bed0bad1830a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726553686f77466f726d28666f726d290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f7265416464537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a72657475726e20747275653b0a7d0a0a0a66756e6374696f6e204576656e7441667465724c696e655072696e74287374724e756d290a7b202f2f20d092d18bd0b7d18bd0b2d0b0d0b5d182d181d18f20d0bfd0bed181d0bbd0b520d0bfd0b5d187d0b0d182d0b820d0bed187d0b5d180d0b5d0b4d0bdd0bed0b920d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd182d0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744265666f726544656c657465537472696e6728290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d181d182d180d0bed0bad0b820d0b8d0b720d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a72657475726e20747275653b0a7d0a0a0a66756e6374696f6e204576656e74416674657243616c63756c61746528290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b2d18bd187d0b8d181d0bbd0b5d0bdd0b8d18f20d0b220d18fd187d0b5d0b9d0bad0b50a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744578706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd0add0bad181d0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744b657950726573736564286b65792c206d6f64696669657273290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b820d0bdd0b020d184d0bed180d0bcd0b52e20d094d0bed0bbd0b6d0bdd0be20d0b2d0b5d180d0bdd183d182d18c20d098d0a1d0a2d098d09dd0902c20d0b5d181d0bbd0b820d0bdd0b0d0b6d0b0d182d0b8d0b520d0bed0b1d180d0b0d0b1d0bed182d0b0d0bdd0be0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a72657475726e2066616c73653b0a7d0a0a0a66756e6374696f6e204576656e74416674657253686f774e657874446963747328290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0bfd0bed0bad0b0d0b7d0b020d0b2d181d0b5d18520d0bdd0b5d0bed0b1d185d0bed0b4d0b8d0bcd18bd18520d181d0bfd180d0b0d0b2d0bed187d0bdd0b8d0bad0bed0b220d0bfd180d0b820d0b4d0bed0b1d0b0d0b2d0bbd0b5d0bdd0b8d0b820d181d182d180d0bed0bad0b820d0b220d0b4d0bed0bad183d0bcd0b5d0bdd1820a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a72657475726e20747275653b0a7d0a0a0a66756e6374696f6e204576656e74436c6f7365466f726d28666f726d290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d183d0b4d0b0d0bbd0b5d0bdd0b8d0b5d0bc20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e7450686f746f4c6f6164656428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0b3d180d183d0b7d0bad0b820d184d0bed182d0bed0b3d180d0b0d184d0b8d0b820d0b8d0b720d098d0bdd182d0b5d180d0bdd0b5d182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74416674657248696465466f726d28666f726d290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0bed181d0bbd0b520d0b7d0b0d0bad180d18bd182d0b8d18f20d184d0bed180d0bcd18b20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e744b657950726573736564286b65794576656e74290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bbd18ed0b1d0bed0b920d0bad0bdd0bed0bfd0bad0b820d0bdd0b020d184d0bed180d0bcd0b52e20d09fd0b0d180d0b0d0bcd0b5d182d180206b65794576656e7420d0b8d0bcd0b5d0b5d18220d182d0b8d0bf20514b65794576656e740a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e20507265706172655069637475726555726c286f626a656374290a7b202f2f20d092d18bd0b7d0bed0b220d18dd182d0bed0b920d184d183d0bdd0bad186d0b8d0b820d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d0bed182d0bad180d18bd182d0b8d0b5d0bc20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e20d097d0b4d0b5d181d18c20d0b8d0bcd0b5d0b5d182d181d18f20d0b2d0bed0b7d0bcd0bed0b6d0bdd0bed181d182d18c20d0b7d0b0d0b3d180d183d0b7d0b8d182d18c20d184d0bed182d0bed0b3d180d0b0d184d0b8d18e20d0b4d0bbd18f20d182d0b5d0bad183d189d0b5d0b3d0be20d0bed0b1d18ad0b5d0bad182d0b0206f626a65637420d0b8d0b720d098d0bdd182d0b5d180d0bdd0b5d182d0b02e20d0a4d183d0bdd0bad186d0b8d18f20d0b4d0bed0bbd0b6d0bdd0b020d0b2d0b5d180d0bdd183d182d18c2075726c20d184d0bed182d0bed0b3d180d0b0d184d0b8d0b82e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74496d706f727428290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd180d0b820d0bdd0b0d0b6d0b0d182d0b8d0b820d0bad0bdd0bed0bfd0bad0b8203cd098d0bcd0bfd0bed180d1823e0a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a66756e6374696f6e204576656e74507265706172655072696e7456616c75657328290a7b202f2f20d0a1d0bed0b1d18bd182d0b8d0b520d0bfd180d0bed0b8d181d185d0bed0b4d0b8d18220d0bfd0b5d180d0b5d0b420d181d0bed0b7d0b4d0b0d0bdd0b8d0b5d0bc20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b020d0bfd0b5d187d0b0d182d0b820d0b820d0bfd180d0b5d0b4d0bdd0b0d0b7d0bdd0b0d187d0b5d0bdd0be20d0b4d0bbd18f20d181d0bed0b7d0b4d0b0d0bdd0b8d18f20d0bdd0bed0b2d18bd18520d0b4d0b0d0bdd0bdd18bd18520d0b4d0bbd18f20d0b4d0bed0bad183d0bcd0b5d0bdd182d0b00a2f2f20d097d0b4d0b5d181d18c20d092d18b20d0bcd0bed0b6d0b5d182d0b520d0b2d181d182d0b0d0b2d0b8d182d18c20d181d0b2d0bed0b920d0bad0bed0b40a7d0a0a0a', 'hex'), "КОНТРСУММА" = 658269019, "ДАТАВРЕМЯ" = now() WHERE "ИМЯ" = 'смс_отправленные.qs' AND "ТИП" = 0;
