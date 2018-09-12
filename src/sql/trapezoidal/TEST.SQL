----------------------TESTY-------------------------------------------------------------------
--drop table g;

create table ti (a integer, b twoint);
insert into ti values(1, '1,20');
insert into ti values(1, '7,-3');

create table g (a integer, b trapezoidal_function);
insert into g values(1, about(-81, -2, 3, 4));
insert into g values(1, about(10, 20, 30, 40));
insert into g values(3, about(5, 6, 7, 8));
insert into g values(3, about(1, 2, 3, 4));
insert into g values(5, about(1, 2, 3, 4));


--select id_oso, nazwisko, waga  from osoby;
--select id_oso, nazwisko, waga, about(60, 81, 81, 100) ~= waga 
--from osoby 
--where about(60, 81, 81, 100) *>= 0.1=waga;

--select * from osoby;
--select okolo_polowa(id_oso < 6) from osoby;
--select prawie_wszystkie(plec='M') from osoby;
--select prawie_wszystkie(true) from osoby;
select * from obecnosci;
create index indeksiur on obecnosci(zmeczenie);