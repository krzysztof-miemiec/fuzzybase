CREATE OR REPLACE FUNCTION prawie_zaden() RETURNS ftrapezium
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'prawie_zaden' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION prawie_wszystkie() RETURNS ftrapezium
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'prawie_wszystkie' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION okolo_jedna_czwarta() RETURNS ftrapezium
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'okolo_jedna_czwarta' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION okolo_jedna_trzecia() RETURNS ftrapezium
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'okolo_jedna_trzecia' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION okolo_polowa() RETURNS ftrapezium
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'okolo_polowa' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION okolo_dwie_trzecie() RETURNS ftrapezium
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'okolo_dwie_trzecie' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION okolo_trzy_czwarte() RETURNS ftrapezium
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'okolo_trzy_czwarte' LANGUAGE 'c' ;

CREATE OR REPLACE FUNCTION okolo_jeden() RETURNS ftrapezium
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'okolo_jeden' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION okolo_kilka() RETURNS ftrapezium
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'okolo_kilka' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION okolo_kilkanascie() RETURNS ftrapezium
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'okolo_kilkanascie' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION okolo_kilkadziesiat() RETURNS ftrapezium
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'okolo_kilkadziesiat' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION okolo_kilkaset() RETURNS ftrapezium
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'okolo_kilkaset' LANGUAGE 'c' ;

CREATE OR REPLACE FUNCTION okolo_minuta() RETURNS ftrapezium
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'okolo_minuta' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION okolo_kwadrans() RETURNS ftrapezium
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'okolo_kwadrans' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION okolo_godzina() RETURNS ftrapezium
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'okolo_godzina' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION okolo_tydzien() RETURNS ftrapezium
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'okolo_tydzien' LANGUAGE 'c' ;

CREATE OR REPLACE FUNCTION sekundy_to_str( ftrapezium ) RETURNS TEXT
  AS '/fuzzy/strzelcy/lingw.so', 'sekundy_to_str' LANGUAGE 'c' ;

CREATE OR REPLACE FUNCTION okolo_tydzien() RETURNS ftrapezium
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'okolo_tydzien' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION okolo_miesiac() RETURNS ftrapezium
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'okolo_miesiac' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION okolo_rok() RETURNS ftrapezium
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'okolo_rok' LANGUAGE 'c' ;

CREATE OR REPLACE FUNCTION dni_to_str( ftrapezium ) RETURNS TEXT
  AS '/fuzzy/strzelcy/lingw.so', 'dni_to_str' LANGUAGE 'c' ;
