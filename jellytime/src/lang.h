/*
 * -1 1 1 Albanian_AL
 * -2 25 2 Catalan_ES
 * -3 32 3 Croatian_HR
 * -4 34 4 Czech_CZ
 * -5 36 4 Danish_DK
 * -6 38 4 Dutch_BE_NL
 * -7 41 3 English_CA_PH_SG_US
 * -8 41 4 English_AU_IN_IE_MT_NZ_ZA_GB
 * -9 53 4 Estonian_EE
 * -10 55 4 Finnish_FI
 * -11 57 4 French_BE_CA_FR_LU_CH
 * -12 63 4 German_AT_DE_LU_CH
 * -13 74 3 Hungarian_HU
 * -14 76 4 Icelandic_IS
 * -15 78 4 Indonesian_ID
 * -16 80 4 Irish_IE
 * -17 82 4 Italian_IT_CH
 * -18 90 4 Latvian_LV
 * -19 92 3 Lithuanian_LT
 * -20 96 4 Malay_MY
 * -21 98 5 Maltese_MT
 * -22 100 4 Norwegian_NO_NO
 * -23 103 4 Polish_PL
 * -24 105 6 Portuguese_BR_PT
 * -25 108 4 Romanian_RO
 * -26 114 4 Serbian_BA_RS
 * -27 114 7 Serbian_ME
 * -28 121 3 Slovak_SK
 * -29 123 4 Slovenian_SI
 * -30 125 6 Spanish_AR_BO_CL_CO_CR_DO_EC_SV_GT_HN_MX_NI_PA_PY_PE_PR_ES_US_UY_VE
 * -31 146 4 Swedish_SE
 * -32 151 4 Turkish_TR
 * -33 155 8 Vietnamese_VN
 */
#if LANG == 1
// Albanian
static const char* const DAYS[] = {
"DIE", /* Die */
"HEN", /* Hën */
"MAR", /* Mar */
"MER", /* Mër */
"ENJ", /* Enj */
"PRE", /* Pre */
"SHT", /* Sht */
};

static const char* const MONTHS[] = {
"JANAR", /* janar */
"SHKURT", /* shkurt */
"MARS", /* mars */
"PRILL", /* prill */
"MAJ", /* maj */
"QERSHOR", /* qershor */
"KORRIK", /* korrik */
"GUSHT", /* gusht */
"SHTATOR", /* shtator */
"TETOR", /* tetor */
"NENTOR", /* nëntor */
"DHJETOR", /* dhjetor */
};
#endif 

#if LANG == 25
// Catalan
static const char* const DAYS[] = {
"DG.", /* dg. */
"DL.", /* dl. */
"DT.", /* dt. */
"DC.", /* dc. */
"DJ.", /* dj. */
"DV.", /* dv. */
"DS.", /* ds. */
};

static const char* const MONTHS[] = {
"GENER", /* gener */
"FEBRER", /* febrer */
"MARC", /* març */
"ABRIL", /* abril */
"MAIG", /* maig */
"JUNY", /* juny */
"JULIOL", /* juliol */
"AGOST", /* agost */
"SETEMBRE", /* setembre */
"OCTUBRE", /* octubre */
"NOVEMBRE", /* novembre */
"DESEMBRE", /* desembre */
};
#endif 

#if LANG == 32
// Croatian
static const char* const DAYS[] = {
"NED", /* ned */
"PON", /* pon */
"UTO", /* uto */
"SRI", /* sri */
"CET", /* čet */
"PET", /* pet */
"SUB", /* sub */
};

static const char* const MONTHS[] = {
"SIJECANJ", /* siječanj */
"VELJACA", /* veljača */
"OZUJAK", /* ožujak */
"TRAVANJ", /* travanj */
"SVIBANJ", /* svibanj */
"LIPANJ", /* lipanj */
"SRPANJ", /* srpanj */
"KOLOVOZ", /* kolovoz */
"RUJAN", /* rujan */
"LISTOPAD", /* listopad */
"STUDENI", /* studeni */
"PROSINAC", /* prosinac */
};
#endif 

#if LANG == 34
// Czech
static const char* const DAYS[] = {
"NE", /* Ne */
"PO", /* Po */
"UT", /* Út */
"ST", /* St */
"CT", /* Čt */
"PA", /* Pá */
"SO", /* So */
};

static const char* const MONTHS[] = {
"LEDEN", /* leden */
"UNOR", /* únor */
"BREZEN", /* březen */
"DUBEN", /* duben */
"KVETEN", /* květen */
"CERVEN", /* červen */
"CERVENEC", /* červenec */
"SRPEN", /* srpen */
"ZARI", /* září */
"RIJEN", /* říjen */
"LISTOPAD", /* listopad */
"PROSINEC", /* prosinec */
};
#endif 

#if LANG == 36
// Danish
static const char* const DAYS[] = {
"S", /* sø */
"MA", /* ma */
"TI", /* ti */
"ON", /* on */
"TO", /* to */
"FR", /* fr */
"L", /* lø */
};

static const char* const MONTHS[] = {
"JANUAR", /* januar */
"FEBRUAR", /* februar */
"MARTS", /* marts */
"APRIL", /* april */
"MAJ", /* maj */
"JUNI", /* juni */
"JULI", /* juli */
"AUGUST", /* august */
"SEPTEMBER", /* september */
"OKTOBER", /* oktober */
"NOVEMBER", /* november */
"DECEMBER", /* december */
};
#endif 

#if LANG == 38
// Dutch
static const char* const DAYS[] = {
"ZO", /* zo */
"MA", /* ma */
"DI", /* di */
"WO", /* wo */
"DO", /* do */
"VR", /* vr */
"ZA", /* za */
};

static const char* const MONTHS[] = {
"JANUARI", /* januari */
"FEBRUARI", /* februari */
"MAART", /* maart */
"APRIL", /* april */
"MEI", /* mei */
"JUNI", /* juni */
"JULI", /* juli */
"AUGUSTUS", /* augustus */
"SEPTEMBER", /* september */
"OKTOBER", /* oktober */
"NOVEMBER", /* november */
"DECEMBER", /* december */
};
#endif 

#if LANG == 41
// English
static const char* const DAYS[] = {
"SUN", /* Sun */
"MON", /* Mon */
"TUE", /* Tue */
"WED", /* Wed */
"THU", /* Thu */
"FRI", /* Fri */
"SAT", /* Sat */
};

static const char* const MONTHS[] = {
"JANUARY", /* January */
"FEBRUARY", /* February */
"MARCH", /* March */
"APRIL", /* April */
"MAY", /* May */
"JUNE", /* June */
"JULY", /* July */
"AUGUST", /* August */
"SEPTEMBER", /* September */
"OCTOBER", /* October */
"NOVEMBER", /* November */
"DECEMBER", /* December */
};
#endif 

#if LANG == 53
// Estonian
static const char* const DAYS[] = {
"P", /* P */
"E", /* E */
"T", /* T */
"K", /* K */
"N", /* N */
"R", /* R */
"L", /* L */
};

static const char* const MONTHS[] = {
"JAANUAR", /* jaanuar */
"VEEBRUAR", /* veebruar */
"MARTS", /* märts */
"APRILL", /* aprill */
"MAI", /* mai */
"JUUNI", /* juuni */
"JUULI", /* juuli */
"AUGUST", /* august */
"SEPTEMBER", /* september */
"OKTOOBER", /* oktoober */
"NOVEMBER", /* november */
"DETSEMBER", /* detsember */
};
#endif 

#if LANG == 55
// Finnish
static const char* const DAYS[] = {
"SU", /* su */
"MA", /* ma */
"TI", /* ti */
"KE", /* ke */
"TO", /* to */
"PE", /* pe */
"LA", /* la */
};

static const char* const MONTHS[] = {
"TAMMIKUU", /* tammikuu */
"HELMIKUU", /* helmikuu */
"MAALISKUU", /* maaliskuu */
"HUHTIKUU", /* huhtikuu */
"TOUKOKUU", /* toukokuu */
"KESAKUU", /* kesäkuu */
"HEINAKUU", /* heinäkuu */
"ELOKUU", /* elokuu */
"SYYSKUU", /* syyskuu */
"LOKAKUU", /* lokakuu */
"MARRASKUU", /* marraskuu */
"JOULUKUU", /* joulukuu */
};
#endif 

#if LANG == 57
// French
static const char* const DAYS[] = {
"DIM.", /* dim. */
"LUN.", /* lun. */
"MAR.", /* mar. */
"MER.", /* mer. */
"JEU.", /* jeu. */
"VEN.", /* ven. */
"SAM.", /* sam. */
};

static const char* const MONTHS[] = {
"JANVIER", /* janvier */
"FEVRIER", /* février */
"MARS", /* mars */
"AVRIL", /* avril */
"MAI", /* mai */
"JUIN", /* juin */
"JUILLET", /* juillet */
"AOUT", /* août */
"SEPTEMBRE", /* septembre */
"OCTOBRE", /* octobre */
"NOVEMBRE", /* novembre */
"DECEMBRE", /* décembre */
};
#endif 

#if LANG == 63
// German
static const char* const DAYS[] = {
"SO", /* So */
"MO", /* Mo */
"DI", /* Di */
"MI", /* Mi */
"DO", /* Do */
"FR", /* Fr */
"SA", /* Sa */
};

static const char* const MONTHS[] = {
"JANUAR", /* Januar */
"FEBRUAR", /* Februar */
"MARZ", /* März */
"APRIL", /* April */
"MAI", /* Mai */
"JUNI", /* Juni */
"JULI", /* Juli */
"AUGUST", /* August */
"SEPTEMBER", /* September */
"OKTOBER", /* Oktober */
"NOVEMBER", /* November */
"DEZEMBER", /* Dezember */
};
#endif 

#if LANG == 74
// Hungarian
static const char* const DAYS[] = {
"V", /* V */
"H", /* H */
"K", /* K */
"SZE", /* Sze */
"CS", /* Cs */
"P", /* P */
"SZO", /* Szo */
};

static const char* const MONTHS[] = {
"JANUAR", /* január */
"FEBRUAR", /* február */
"MARCIUS", /* március */
"APRILIS", /* április */
"MAJUS", /* május */
"JUNIUS", /* június */
"JULIUS", /* július */
"AUGUSZTUS", /* augusztus */
"SZEPTEMBER", /* szeptember */
"OKTOBER", /* október */
"NOVEMBER", /* november */
"DECEMBER", /* december */
};
#endif 

#if LANG == 76
// Icelandic
static const char* const DAYS[] = {
"SUN.", /* sun. */
"MAN.", /* mán. */
"RI.", /* þri. */
"MI.", /* mið. */
"FIM.", /* fim. */
"FOS.", /* fös. */
"LAU.", /* lau. */
};

static const char* const MONTHS[] = {
"JANUAR", /* janúar */
"FEBRUAR", /* febrúar */
"MARS", /* mars */
"APRIL", /* apríl */
"MAI", /* maí */
"JUNI", /* júní */
"JULI", /* júlí */
"AGUST", /* ágúst */
"SEPTEMBER", /* september */
"OKTOBER", /* október */
"NOVEMBER", /* nóvember */
"DESEMBER", /* desember */
};
#endif 

#if LANG == 78
// Indonesian
static const char* const DAYS[] = {
"MIN", /* Min */
"SEN", /* Sen */
"SEL", /* Sel */
"RAB", /* Rab */
"KAM", /* Kam */
"JUM", /* Jum */
"SAB", /* Sab */
};

static const char* const MONTHS[] = {
"JANUARI", /* Januari */
"FEBRUARI", /* Februari */
"MARET", /* Maret */
"APRIL", /* April */
"MEI", /* Mei */
"JUNI", /* Juni */
"JULI", /* Juli */
"AGUSTUS", /* Agustus */
"SEPTEMBER", /* September */
"OKTOBER", /* Oktober */
"NOVEMBER", /* November */
"DESEMBER", /* Desember */
};
#endif 

#if LANG == 80
// Irish
static const char* const DAYS[] = {
"DOMH", /* Domh */
"LUAN", /* Luan */
"MAIRT", /* Máirt */
"CEAD", /* Céad */
"DEAR", /* Déar */
"AOINE", /* Aoine */
"SATH", /* Sath */
};

static const char* const MONTHS[] = {
"EANAIR", /* Eanáir */
"FEABHRA", /* Feabhra */
"MARTA", /* Márta */
"AIBREAN", /* Aibreán */
"BEALTAINE", /* Bealtaine */
"MEITHEAMH", /* Meitheamh */
"IUIL", /* Iúil */
"LUNASA", /* Lúnasa */
"MEAN FOMHAIR", /* Meán Fómhair */
"DEIREADH FOMHAIR", /* Deireadh Fómhair */
"SAMHAIN", /* Samhain */
"NOLLAIG", /* Nollaig */
};
#endif 

#if LANG == 82
// Italian
static const char* const DAYS[] = {
"DOM", /* dom */
"LUN", /* lun */
"MAR", /* mar */
"MER", /* mer */
"GIO", /* gio */
"VEN", /* ven */
"SAB", /* sab */
};

static const char* const MONTHS[] = {
"GENNAIO", /* gennaio */
"FEBBRAIO", /* febbraio */
"MARZO", /* marzo */
"APRILE", /* aprile */
"MAGGIO", /* maggio */
"GIUGNO", /* giugno */
"LUGLIO", /* luglio */
"AGOSTO", /* agosto */
"SETTEMBRE", /* settembre */
"OTTOBRE", /* ottobre */
"NOVEMBRE", /* novembre */
"DICEMBRE", /* dicembre */
};
#endif 

#if LANG == 90
// Latvian
static const char* const DAYS[] = {
"SV", /* Sv */
"P", /* P */
"O", /* O */
"T", /* T */
"C", /* C */
"PK", /* Pk */
"S", /* S */
};

static const char* const MONTHS[] = {
"JANVARIS", /* janvāris */
"FEBRUARIS", /* februāris */
"MARTS", /* marts */
"APRILIS", /* aprīlis */
"MAIJS", /* maijs */
"JUNIJS", /* jūnijs */
"JULIJS", /* jūlijs */
"AUGUSTS", /* augusts */
"SEPTEMBRIS", /* septembris */
"OKTOBRIS", /* oktobris */
"NOVEMBRIS", /* novembris */
"DECEMBRIS", /* decembris */
};
#endif 

#if LANG == 92
// Lithuanian
static const char* const DAYS[] = {
"SK", /* Sk */
"PR", /* Pr */
"AN", /* An */
"TR", /* Tr */
"KT", /* Kt */
"PN", /* Pn */
"ST", /* Št */
};

static const char* const MONTHS[] = {
"SAUSIO", /* Sausio */
"VASARIO", /* Vasario */
"KOVO", /* Kovo */
"BALANDZIO", /* Balandžio */
"GEGUZES", /* Gegužės */
"BIRZELIO", /* Birželio */
"LIEPOS", /* Liepos */
"RUGPJUCIO", /* Rugpjūčio */
"RUGSEJO", /* Rugsėjo */
"SPALIO", /* Spalio */
"LAPKRICIO", /* Lapkričio */
"GRUODZIO", /* Gruodžio */
};
#endif 

#if LANG == 96
// Malay
static const char* const DAYS[] = {
"AHD", /* Ahd */
"ISN", /* Isn */
"SEL", /* Sel */
"RAB", /* Rab */
"KHA", /* Kha */
"JUM", /* Jum */
"SAB", /* Sab */
};

static const char* const MONTHS[] = {
"JANUARI", /* Januari */
"FEBRUARI", /* Februari */
"MAC", /* Mac */
"APRIL", /* April */
"MEI", /* Mei */
"JUN", /* Jun */
"JULAI", /* Julai */
"OGOS", /* Ogos */
"SEPTEMBER", /* September */
"OKTOBER", /* Oktober */
"NOVEMBER", /* November */
"DISEMBER", /* Disember */
};
#endif 

#if LANG == 98
// Maltese
static const char* const DAYS[] = {
"AD", /* Ħad */
"TNE", /* Tne */
"TLI", /* Tli */
"ERB", /* Erb */
"AM", /* Ħam */
"GIM", /* Ġim */
"SIB", /* Sib */
};

static const char* const MONTHS[] = {
"JANNAR", /* Jannar */
"FRAR", /* Frar */
"MARZU", /* Marzu */
"APRIL", /* April */
"MEJJU", /* Mejju */
"GUNJU", /* Ġunju */
"LULJU", /* Lulju */
"AWISSU", /* Awissu */
"SETTEMBRU", /* Settembru */
"OTTUBRU", /* Ottubru */
"NOVEMBRU", /* Novembru */
"DICEMBRU", /* Diċembru */
};
#endif 

#if LANG == 100
// Norwegian
static const char* const DAYS[] = {
"S", /* sø */
"MA", /* ma */
"TI", /* ti */
"ON", /* on */
"TO", /* to */
"FR", /* fr */
"L", /* lø */
};

static const char* const MONTHS[] = {
"JANUAR", /* januar */
"FEBRUAR", /* februar */
"MARS", /* mars */
"APRIL", /* april */
"MAI", /* mai */
"JUNI", /* juni */
"JULI", /* juli */
"AUGUST", /* august */
"SEPTEMBER", /* september */
"OKTOBER", /* oktober */
"NOVEMBER", /* november */
"DESEMBER", /* desember */
};
#endif 

#if LANG == 103
// Polish
static const char* const DAYS[] = {
"N", /* N */
"PN", /* Pn */
"WT", /* Wt */
"SR", /* Śr */
"CZ", /* Cz */
"PT", /* Pt */
"SO", /* So */
};

static const char* const MONTHS[] = {
"STYCZEN", /* styczeń */
"LUTY", /* luty */
"MARZEC", /* marzec */
"KWIECIEN", /* kwiecień */
"MAJ", /* maj */
"CZERWIEC", /* czerwiec */
"LIPIEC", /* lipiec */
"SIERPIEN", /* sierpień */
"WRZESIEN", /* wrzesień */
"PAZDZIERNIK", /* październik */
"LISTOPAD", /* listopad */
"GRUDZIEN", /* grudzień */
};
#endif 

#if LANG == 105
// Portuguese
static const char* const DAYS[] = {
"DOM", /* Dom */
"SEG", /* Seg */
"TER", /* Ter */
"QUA", /* Qua */
"QUI", /* Qui */
"SEX", /* Sex */
"SAB", /* Sáb */
};

static const char* const MONTHS[] = {
"JANEIRO", /* Janeiro */
"FEVEREIRO", /* Fevereiro */
"MARCO", /* Março */
"ABRIL", /* Abril */
"MAIO", /* Maio */
"JUNHO", /* Junho */
"JULHO", /* Julho */
"AGOSTO", /* Agosto */
"SETEMBRO", /* Setembro */
"OUTUBRO", /* Outubro */
"NOVEMBRO", /* Novembro */
"DEZEMBRO", /* Dezembro */
};
#endif 

#if LANG == 108
// Romanian
static const char* const DAYS[] = {
"D", /* D */
"L", /* L */
"MA", /* Ma */
"MI", /* Mi */
"J", /* J */
"V", /* V */
"S", /* S */
};

static const char* const MONTHS[] = {
"IANUARIE", /* ianuarie */
"FEBRUARIE", /* februarie */
"MARTIE", /* martie */
"APRILIE", /* aprilie */
"MAI", /* mai */
"IUNIE", /* iunie */
"IULIE", /* iulie */
"AUGUST", /* august */
"SEPTEMBRIE", /* septembrie */
"OCTOMBRIE", /* octombrie */
"NOIEMBRIE", /* noiembrie */
"DECEMBRIE", /* decembrie */
};
#endif 

#if LANG == 114
// Serbian
static const char* const DAYS[] = {
"NED", /* ned */
"PON", /* pon */
"UTO", /* uto */
"SRE", /* sre */
"CET", /* čet */
"PET", /* pet */
"SUB", /* sub */
};

static const char* const MONTHS[] = {
"JANUAR", /* januar */
"FEBRUAR", /* februar */
"MART", /* mart */
"APRIL", /* april */
"MAJ", /* maj */
"JUN", /* jun */
"JUL", /* jul */
"AVGUST", /* avgust */
"SEPTEMBAR", /* septembar */
"OKTOBAR", /* oktobar */
"NOVEMBAR", /* novembar */
"DECEMBAR", /* decembar */
};
#endif 

#if LANG == 121
// Slovak
static const char* const DAYS[] = {
"NE", /* Ne */
"PO", /* Po */
"UT", /* Ut */
"ST", /* St */
"ST", /* Št */
"PI", /* Pi */
"SO", /* So */
};

static const char* const MONTHS[] = {
"JANUAR", /* január */
"FEBRUAR", /* február */
"MAREC", /* marec */
"APRIL", /* apríl */
"MAJ", /* máj */
"JUN", /* jún */
"JUL", /* júl */
"AUGUST", /* august */
"SEPTEMBER", /* september */
"OKTOBER", /* október */
"NOVEMBER", /* november */
"DECEMBER", /* december */
};
#endif 

#if LANG == 123
// Slovenian
static const char* const DAYS[] = {
"NED", /* Ned */
"PON", /* Pon */
"TOR", /* Tor */
"SRE", /* Sre */
"CET", /* Čet */
"PET", /* Pet */
"SOB", /* Sob */
};

static const char* const MONTHS[] = {
"JANUAR", /* januar */
"FEBRUAR", /* februar */
"MAREC", /* marec */
"APRIL", /* april */
"MAJ", /* maj */
"JUNIJ", /* junij */
"JULIJ", /* julij */
"AVGUST", /* avgust */
"SEPTEMBER", /* september */
"OKTOBER", /* oktober */
"NOVEMBER", /* november */
"DECEMBER", /* december */
};
#endif 

#if LANG == 125
// Spanish
static const char* const DAYS[] = {
"DOM", /* dom */
"LUN", /* lun */
"MAR", /* mar */
"MIE", /* mié */
"JUE", /* jue */
"VIE", /* vie */
"SAB", /* sáb */
};

static const char* const MONTHS[] = {
"ENERO", /* enero */
"FEBRERO", /* febrero */
"MARZO", /* marzo */
"ABRIL", /* abril */
"MAYO", /* mayo */
"JUNIO", /* junio */
"JULIO", /* julio */
"AGOSTO", /* agosto */
"SEPTIEMBRE", /* septiembre */
"OCTUBRE", /* octubre */
"NOVIEMBRE", /* noviembre */
"DICIEMBRE", /* diciembre */
};
#endif 

#if LANG == 146
// Swedish
static const char* const DAYS[] = {
"SO", /* sö */
"MA", /* må */
"TI", /* ti */
"ON", /* on */
"TO", /* to */
"FR", /* fr */
"LO", /* lö */
};

static const char* const MONTHS[] = {
"JANUARI", /* januari */
"FEBRUARI", /* februari */
"MARS", /* mars */
"APRIL", /* april */
"MAJ", /* maj */
"JUNI", /* juni */
"JULI", /* juli */
"AUGUSTI", /* augusti */
"SEPTEMBER", /* september */
"OKTOBER", /* oktober */
"NOVEMBER", /* november */
"DECEMBER", /* december */
};
#endif 

#if LANG == 151
// Turkish
static const char* const DAYS[] = {
"PAZ", /* Paz */
"PZT", /* Pzt */
"SAL", /* Sal */
"CAR", /* Çar */
"PER", /* Per */
"CUM", /* Cum */
"CMT", /* Cmt */
};

static const char* const MONTHS[] = {
"OCAK", /* Ocak */
"SUBAT", /* Şubat */
"MART", /* Mart */
"NISAN", /* Nisan */
"MAYS", /* Mayıs */
"HAZIRAN", /* Haziran */
"TEMMUZ", /* Temmuz */
"AGUSTOS", /* Ağustos */
"EYLUL", /* Eylül */
"EKIM", /* Ekim */
"KASM", /* Kasım */
"ARALK", /* Aralık */
};
#endif 

#if LANG == 155
// Vietnamese
static const char* const DAYS[] = {
"CN", /* CN */
"TH 2", /* Th 2 */
"TH 3", /* Th 3 */
"TH 4", /* Th 4 */
"TH 5", /* Th 5 */
"TH 6", /* Th 6 */
"TH 7", /* Th 7 */
};

static const char* const MONTHS[] = {
"THANG MOT", /* tháng một */
"THANG HAI", /* tháng hai */
"THANG BA", /* tháng ba */
"THANG TU", /* tháng tư */
"THANG NAM", /* tháng năm */
"THANG SAU", /* tháng sáu */
"THANG BAY", /* tháng bảy */
"THANG TAM", /* tháng tám */
"THANG CHIN", /* tháng chín */
"THANG MUOI", /* tháng mười */
"THANG MUOI MOT", /* tháng mười một */
"THANG MUOI HAI", /* tháng mười hai */
};
#endif 

#if ORDER == 1
// MD
void draw_date(PblTm* t) {
char day[] = "14";
string_format_time(day, sizeof(day), "%d", t);
size_t size = sizeof(date_text);
memset(date_text, 0, size);
strncat(date_text, DAYS[t->tm_wday], size);
size -= strlen(DAYS[t->tm_wday]);
strncat(date_text, ", ", size);
size -= strlen(", ");
strncat(date_text, MONTHS[t->tm_mon], size);
size -= strlen(MONTHS[t->tm_mon]);
strncat(date_text, "", size);
size -= strlen("");
strncat(date_text, day, size);
text_layer_set_text(&date_layer, date_text);
}
#endif 

#if ORDER == 2
// D / M
void draw_date(PblTm* t) {
char day[] = "14";
string_format_time(day, sizeof(day), "%d", t);
size_t size = sizeof(date_text);
memset(date_text, 0, size);
strncat(date_text, DAYS[t->tm_wday], size);
size -= strlen(DAYS[t->tm_wday]);
strncat(date_text, ", ", size);
size -= strlen(", ");
strncat(date_text, day, size);
size -= strlen("12");
strncat(date_text, " / ", size);
size -= strlen(" / ");
strncat(date_text, MONTHS[t->tm_mon], size);
text_layer_set_text(&date_layer, date_text);
}
#endif 

#if ORDER == 3
// M D
void draw_date(PblTm* t) {
char day[] = "14";
string_format_time(day, sizeof(day), "%d", t);
size_t size = sizeof(date_text);
memset(date_text, 0, size);
strncat(date_text, DAYS[t->tm_wday], size);
size -= strlen(DAYS[t->tm_wday]);
strncat(date_text, ", ", size);
size -= strlen(", ");
strncat(date_text, MONTHS[t->tm_mon], size);
size -= strlen(MONTHS[t->tm_mon]);
strncat(date_text, " ", size);
size -= strlen(" ");
strncat(date_text, day, size);
text_layer_set_text(&date_layer, date_text);
}
#endif 

#if ORDER == 4
// D M
void draw_date(PblTm* t) {
char day[] = "14";
string_format_time(day, sizeof(day), "%d", t);
size_t size = sizeof(date_text);
memset(date_text, 0, size);
strncat(date_text, DAYS[t->tm_wday], size);
size -= strlen(DAYS[t->tm_wday]);
strncat(date_text, ", ", size);
size -= strlen(", ");
strncat(date_text, day, size);
size -= strlen("12");
strncat(date_text, " ", size);
size -= strlen(" ");
strncat(date_text, MONTHS[t->tm_mon], size);
text_layer_set_text(&date_layer, date_text);
}
#endif 

#if ORDER == 5
// D TA’ M
void draw_date(PblTm* t) {
char day[] = "14";
string_format_time(day, sizeof(day), "%d", t);
size_t size = sizeof(date_text);
memset(date_text, 0, size);
strncat(date_text, DAYS[t->tm_wday], size);
size -= strlen(DAYS[t->tm_wday]);
strncat(date_text, ", ", size);
size -= strlen(", ");
strncat(date_text, day, size);
size -= strlen("12");
strncat(date_text, " TA’ ", size);
size -= strlen(" TA’ ");
strncat(date_text, MONTHS[t->tm_mon], size);
text_layer_set_text(&date_layer, date_text);
}
#endif 

#if ORDER == 6
// D DE M
void draw_date(PblTm* t) {
char day[] = "14";
string_format_time(day, sizeof(day), "%d", t);
size_t size = sizeof(date_text);
memset(date_text, 0, size);
strncat(date_text, DAYS[t->tm_wday], size);
size -= strlen(DAYS[t->tm_wday]);
strncat(date_text, ", ", size);
size -= strlen(", ");
strncat(date_text, day, size);
size -= strlen("12");
strncat(date_text, " DE ", size);
size -= strlen(" DE ");
strncat(date_text, MONTHS[t->tm_mon], size);
text_layer_set_text(&date_layer, date_text);
}
#endif 

#if ORDER == 7
// DM
void draw_date(PblTm* t) {
char day[] = "14";
string_format_time(day, sizeof(day), "%d", t);
size_t size = sizeof(date_text);
memset(date_text, 0, size);
strncat(date_text, DAYS[t->tm_wday], size);
size -= strlen(DAYS[t->tm_wday]);
strncat(date_text, ", ", size);
size -= strlen(", ");
strncat(date_text, day, size);
size -= strlen("12");
strncat(date_text, "", size);
size -= strlen("");
strncat(date_text, MONTHS[t->tm_mon], size);
text_layer_set_text(&date_layer, date_text);
}
#endif 

#if ORDER == 8
// D THÁNG M
void draw_date(PblTm* t) {
char day[] = "14";
string_format_time(day, sizeof(day), "%d", t);
size_t size = sizeof(date_text);
memset(date_text, 0, size);
strncat(date_text, DAYS[t->tm_wday], size);
size -= strlen(DAYS[t->tm_wday]);
strncat(date_text, ", ", size);
size -= strlen(", ");
strncat(date_text, day, size);
size -= strlen("12");
strncat(date_text, " THÁNG ", size);
size -= strlen(" THÁNG ");
strncat(date_text, MONTHS[t->tm_mon], size);
text_layer_set_text(&date_layer, date_text);
}
#endif 
