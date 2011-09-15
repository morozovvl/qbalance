COPY "группы" ("код", "имя", "цены_снижать") FROM stdin;
1	Запчасти ВАЗ	f
\.


--
-- TOC entry 2187 (class 0 OID 71374)
-- Dependencies: 1603
-- Data for Name: документы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "документы" ("код", "дата", "датавремя", "номер", "комментарий", "сумма", "описание", "опер", "авто", "переменные") FROM stdin;
3	2010-05-31	2010-07-03 19:36:05.175633	3		0.00	\N	1	0	\N
1	2010-05-17	2010-07-03 19:32:29	1		366.00	\N	1	0	\N
4	2010-06-30	2010-08-24 22:23:28	4		324.00	\N	1	0	\N
5	2010-06-30	2010-09-24 13:29:32	5		235.00	\N	1	0	\N
\.


--
-- TOC entry 2193 (class 0 OID 71482)
-- Dependencies: 1615
-- Data for Name: контрагенты; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "контрагенты" ("код", "имя", "адрес", "телефон", e_mail, "руководитель", "гл_бухгалтер", "инн", "кпп", "оконх", "окпо", "счет", "код_банки", "лимит", "код_vw_грузополучатели") FROM stdin;
1	ООО "АвтоОпт"	г.Москва, ул.Декабристов 15	(495)236-67-89		Сидоров Е.А.							\N	0.00	\N
2	ТД "Автодеталь"	г.Н.Новгород, ул.Социалистическая 77	(8312)45-97-65		Петров С.Н.							\N	0.00	\N
\.


--
-- TOC entry 2194 (class 0 OID 71507)
-- Dependencies: 1617
-- Data for Name: материалы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "материалы" ("код", "имя", "едизм") FROM stdin;
\.


--
-- TOC entry 2195 (class 0 OID 71519)
-- Dependencies: 1619
-- Data for Name: номенклатура; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "номенклатура" ("код", "имя", "едизм", "артикул", "код_группы", "цена_розн", "запас", "имя_на_ценнике", "тип_ценника", fts) FROM stdin;
34	ключ натяжения ремня ГРМ 2108	шт		1	26.00	0		3	\N
28	диск сцепления дв. 406 (ЗМЗ)	шт	40637-1601130	\N	770.00	0		3	\N
18	фильтр топливный (GUR-612)  дизель универсал	шт		\N	37.00	0		3	\N
2	паста притирочная алмазная (20гр)	шт		\N	56.00	0		3	\N
3	брелок оригинальный (хром)	шт		\N	47.00	0		3	\N
4	препарат "РЕМЕТАЛЛ" для двигателя (120мл)	шт		\N	165.00	0		3	\N
5	очиститель рук "Защитные перчатки" (40г)	шт		\N	27.00	0		3	\N
8	крестовина 2121 "Master-Sport" (Германия)	шт		1	178.00	0		3	\N
29	ремкомплект рулевой рейки М-2126 (полный)	к-т		\N	520.00	0		3	\N
27	ось верхнего рычага 2121	шт		1	97.00	0		3	\N
7	лампа H3 12В (55Вт) галогенн. (отеч.)	шт		\N	196.00	0		3	\N
21	свеча BERU Z21 ВАЗ-2110 8-клап.  (Германия)			\N	76.00	0		3	\N
9	стартер ГАЗ, УАЗ дв.406,405,409 (42.3708-10/11) БАТЭ	шт	42.3708-10 	\N	2440.00	0		3	\N
22	фара противотуманная CIRIE круглая (лазерная)	к-т		\N	422.00	0		3	\N
10	дезодорант "Mannol Eclipse"	шт		\N	55.00	0		3	\N
20	палец шаровый нижний с/п 2101 (FENOX)	шт	2101-2904082	1	188.00	0		3	\N
12	размораживатель замков "LUX-OIL" (50мл)	шт		\N	35.00	0		3	\N
13	крестовина М-412 "Master-Sport" (Германия)	шт		\N	167.00	0		3	\N
15	дезодорант "Русский лес"	шт		\N	21.00	0		3	\N
11	подшипник 256907 ступицы передний 2108, М-2126 "Herzog" (Германия)	шт	2108-3103020	1	193.00	0		3	\N
31	прокладка поддона дв.402	шт		\N	75.00	0		3	\N
14	пружина задней подвески 1111	шт		1	380.00	0		3	\N
30	реле-регулятор 2110, дв. 406 (611.3702-11) в сборе с ЩУ	шт		1	104.00	0		3	\N
19	ремень генератора 2108, Таврия (710) зубч. "Хорс"	шт	2108-3701720	1	52.00	0		3	\N
23	ремкомплект карбюратора 1111 (Челябинск)	к-т	1111-	1	71.00	0		3	\N
24	ремкомплект стоек 2108	к-т	2108-	1	22.00	0		3	\N
35	термостат 2101	шт	2101-1306010	1	263.00	0		3	\N
33	трубка сцепления 2101	шт		1	20.00	0		3	\N
17	фильтр топливный 2108 (инжектор) FRAM	шт		1	274.00	0		3	\N
1	цилиндр тормозной 2108 главный	шт		1	530.00	0		3	\N
6	бендикс 2101 "Master-Sport" (Германия)	шт		1	183.00	0		3	\N
16	вал и червяк 2105	шт	2101-3401035-20	1	410.00	0		3	\N
25	шатун 2108, 21099, 1111	шт	2108-1004045-00	1	470.00	0		3	\N
32	шестерня КПП 5-й передачи 2108, 2110	шт	2108-1701158/64	1	361.00	0		3	\N
\.


--
-- TOC entry 2197 (class 0 OID 71551)
-- Dependencies: 1623
-- Data for Name: персонал; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "персонал" ("код", "имя", "инн", "паспорт_серия", "паспорт_номер", "паспорт_выдан", "паспорт_дата", "адрес", "день_рождения", "работает", "медстрах") FROM stdin;
\.


--
-- TOC entry 2198 (class 0 OID 71568)
-- Dependencies: 1625
-- Data for Name: предметы; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "предметы" ("код", "имя", "едизм") FROM stdin;
\.


--
-- TOC entry 2188 (class 0 OID 71392)
-- Dependencies: 1605
-- Data for Name: проводки; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "проводки" ("код", "дбсчет", "дбкод", "крсчет", "кркод", "кол", "цена", "сумма", "стр", "доккод", "опер", "номеропер") FROM stdin;
91	41.1 	6	60   	2	1.000	25.00	25.00	1	4	1	1
92	19.3 	0	60   	2	0.000	0.00	158.00	1	4	1	2
93	41.1 	6	42   	6	0.000	4.50	4.50	1	4	1	3
88	41.1 	6	60   	2	2.000	120.00	240.00	1	1	1	1
89	19.3 	0	60   	2	0.000	0.00	126.00	1	1	1	2
90	41.1 	6	42   	6	0.000	21.60	43.20	1	1	1	3
94	41.1 	3	60   	2	3.000	20.00	60.00	2	4	1	1
95	19.3 	0	60   	2	0.000	0.00	81.00	2	4	1	2
96	41.1 	3	42   	3	0.000	3.60	10.80	2	4	1	3
97	41.1 	3	60   	1	5.000	0.00	0.00	1	5	1	1
98	19.3 	0	60   	1	0.000	0.00	235.00	1	5	1	2
99	41.1 	3	42   	3	0.000	0.00	0.00	1	5	1	3
\.


--
-- TOC entry 2186 (class 0 OID 71361)
-- Dependencies: 1602
-- Data for Name: сальдо; Type: TABLE DATA; Schema: public; Owner: sa
--

COPY "сальдо" ("счет", "код", "кол", "сальдо", "дбкол", "дебет", "кркол", "кредит", "конкол", "консальдо", "концена") FROM stdin;
42   	3	0.000	0.00	0.000	0.00	0.000	10.80	0.000	-10.80	-10.80
42   	25	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
41.1 	24	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
41.1 	6	0.000	0.00	3.000	312.70	0.000	0.00	3.000	312.70	104.23
41.1 	4	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
41.1 	32	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
42   	32	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
42   	4	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
42   	6	0.000	0.00	0.000	0.00	0.000	47.70	0.000	-47.70	-47.70
42   	24	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
41.1 	15	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
42   	15	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
41.1 	35	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
42   	35	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
41.1 	1	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
42   	1	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
60   	0	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
41.1 	28	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
42   	28	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
41.1 	16	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
42   	16	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
41.1 	34	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
42   	34	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
60   	2	0.000	0.00	0.000	0.00	6.000	690.00	-6.000	-690.00	115.00
41.1 	27	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
42   	27	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
41.1 	33	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
42   	33	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
19.3 	0	0.000	0.00	0.000	600.00	0.000	0.00	0.000	600.00	600.00
41.1 	5	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
42   	5	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
60   	1	0.000	0.00	0.000	0.00	5.000	235.00	-5.000	-235.00	47.00
41.1 	7	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
42   	7	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
41.1 	25	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
41.1 	3	0.000	0.00	8.000	70.80	0.000	0.00	8.000	70.80	8.85
42   	2	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
41.1 	2	0.000	0.00	0.000	0.00	0.000	0.00	0.000	0.00	0.00
\.

