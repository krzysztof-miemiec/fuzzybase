--***************** tworzenie typu ftrapezium ****************

CREATE OR REPLACE FUNCTION ftrapezium_in( opaque ) RETURNS ftrapezium 
  AS '/fuzzy/ftrapezium/ftrapezium.so' LANGUAGE 'C';

CREATE OR REPLACE FUNCTION ftrapezium_out( ftrapezium ) RETURNS opaque
  AS '/fuzzy/ftrapezium/ftrapezium.so' LANGUAGE 'C';

CREATE TYPE ftrapezium( internallength = 32, input = ftrapezium_in, output = ftrapezium_out ) ;

-- **************************TYP FTRAPEZIUMEXT*****************************************************

-- tworzenie typu FTRAPEZIUMEXT

CREATE OR REPLACE FUNCTION ftrapeziumext_in( opaque ) RETURNS ftrapeziumext 
  AS '/fuzzy/ftrapezium/ftrapezium.so' LANGUAGE 'C';

CREATE OR REPLACE FUNCTION ftrapeziumext_out( ftrapeziumext ) RETURNS opaque
  AS '/fuzzy/ftrapezium/ftrapezium.so' LANGUAGE 'C';

CREATE TYPE ftrapeziumext( internallength = 44, input = ftrapeziumext_in, output = ftrapeziumext_out ) ;