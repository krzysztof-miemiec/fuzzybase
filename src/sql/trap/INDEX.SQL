insert into pg_opclass (opcamid, opcname, opcintype, opcdefault, opckeytype)
  values(
      ( select oid from pg_am where amname = 'btree')
    , 'ftrapezium_abs_ops'
    , ( select oid from pg_type where typname = 'ftrapezium' )
    , true
    , 0
)  ;

select oid, * from pg_opclass where opcname = 'ftrapezium_abs_ops'  ;

-- operatory o argumentach ftrapezium obustronnych

select o.oid as opoid, o.oprname
into temp table ftrapezium_ops_tmp
from pg_operator o, pg_type t
where (o.oprleft = t.oid and o.oprright = t.oid)
 and t.typname = 'ftrapezium';

-- wstawienie  do tabeli access method operators
insert into pg_amop (amopclaid, amopstrategy, amopreqcheck, amopopr)
  select opcl.oid, 1, false, c.opoid
  from pg_opclass opcl, ftrapezium_ops_tmp c
  where opcamid = (select oid from pg_am where amname = 'btree')
    and opcname = 'ftrapezium_abs_ops' 
    and c.oprname = '<' ;

insert into pg_amop (amopclaid, amopstrategy, amopreqcheck, amopopr)
  select opcl.oid, 2, false, c.opoid
  from pg_opclass opcl, ftrapezium_ops_tmp c
  where opcamid = (select oid from pg_am where amname = 'btree')
    and opcname = 'ftrapezium_abs_ops' 
    and c.oprname = '<=' ;

insert into pg_amop (amopclaid, amopstrategy, amopreqcheck, amopopr)
  select opcl.oid, 3, false, c.opoid
  from pg_opclass opcl, ftrapezium_ops_tmp c
  where opcamid = (select oid from pg_am where amname = 'btree')
    and opcname = 'ftrapezium_abs_ops' 
    and c.oprname = '=' ;

insert into pg_amop (amopclaid, amopstrategy, amopreqcheck, amopopr)
  select opcl.oid, 4, false, c.opoid
  from pg_opclass opcl, ftrapezium_ops_tmp c
  where opcamid = (select oid from pg_am where amname = 'btree')
    and opcname = 'ftrapezium_abs_ops' 
    and c.oprname = '>=' ;

insert into pg_amop (amopclaid, amopstrategy, amopreqcheck, amopopr)
  select opcl.oid, 5, false, c.opoid
  from pg_opclass opcl, ftrapezium_ops_tmp c
  where opcamid = (select oid from pg_am where amname = 'btree')
    and opcname = 'ftrapezium_abs_ops' 
    and c.oprname = '>' ;


--select oid, proname from pg_proc
--  where proname = 'ftrapezium_abs_cmp'

insert into pg_amproc( amopclaid, amprocnum, amproc )
  select opcl.oid, 1, p.oid
    from pg_opclass opcl, pg_proc p
    where opcamid = (select oid from pg_am where amname = 'btree')
      and opcname = 'ftrapezium_abs_ops'
      and p.proname = 'ftrapezium_abs_cmp';
      