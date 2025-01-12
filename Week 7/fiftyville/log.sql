-- Keep a log of any SQL queries you execute as you solve the mystery.

-- select * from bakery_security_logs where year=2023 and month=7 and day=28;

-- theft took place on July 28, 2023 and that it took place on Humphrey Street
select * from crime_scene_reports where year=2023 and month=7 and day=28 and street='Humphrey Street';
-- crime_scene_report.id = 295 and time = 10:15 am

select name,transcript from interviews where year=2023 and month=7 and day=28 and lower(transcript) like '%bakery%';

-- Ruth: within 10 mins of theft, theif get into car in bakey and drove away
select hour,minute,license_plate,p.name from bakery_security_logs
join people p using(license_plate)
where year=2023 and month=7 and day=28 and
    activity='exit'and hour=10 and (minute-15)<=10 and (minute-15)>=0;

--  Eugene: Early morning, ATM on Leggett Street and saw the thief there withdrawing some money
select p.name,account_number,amount, passport_number as passport,license_plate from atm_transactions atm
join bank_accounts acc using(account_number)
join people p on acc.person_id=p.id
where year=2023 and month=7 and day=28 and atm_location='Leggett Street' and transaction_type='withdraw';


/*  Raymond: heard theif call someone to purchase flight ticket, earliest flight out of fiftyville tommorow (call last less than a minute)
        --when theif was leaving the bakery */
SELECT a_o.abbreviation AS origin, a_d.abbreviation as destination, day, hour,minute,
    a_o.full_name AS origin_full,a_d.full_name AS destination_full  FROM flights f
    JOIN airports a_o ON a_o.id=f.origin_airport_id
    JOIN airports a_d ON a_d.id=f.destination_airport_id
WHERE year=2023 AND month=7 AND day=29
ORDER BY hour,minute;
-- earliest flight time 8:20 fiftyville to LGA (LaGuardia Airport)

SELECT flight_id,a_o.abbreviation AS origin, a_d.abbreviation AS destination,a_d.full_name AS destination_full,seat,people.name,people.phone_number,license_plate FROM flights f
    JOIN passengers p ON f.id=p.flight_id
    JOIN people USING(passport_number)
    JOIN airports a_o ON a_o.id=f.origin_airport_id
    JOIN airports a_d ON a_d.id=f.destination_airport_id
WHERE f.year=2023 AND f.month=7 AND f.day=29 AND origin='CSF' AND destination='LGA';

select c.name as caller,r.name as receiver,duration,pc.caller,pc.receiver from phone_calls pc
    join people c on c.phone_number= pc.caller
    join people r on r.phone_number= pc.receiver
where year=2023 and month=7 and day=28 and duration <=60;

/*commons :
    plane and bakery: sofia bruce luca kelsey
    atm and bakey: bruce diana Iman Luca
    plane and atm: bruce kenny luca taylor
    phone and other : bruce
*/


-- sophia called Jack
select * from airports  where abbreviation ='LGA';


-- commons

SELECT name,license_plate,receiver FROM
    (SELECT hour,minute,license_plate FROM bakery_security_logs
        WHERE year=2023 AND month=7 AND day=28 AND
        activity='exit' AND hour=10 AND (minute-15)<=10 AND (minute-15)>=0)  AS bakery --bakery *
    JOIN people USING (license_plate) --people
    JOIN bank_accounts bank ON bank.person_id=people.id --bank
    JOIN (SELECT account_number,amount FROM atm_transactions atm
        WHERE year=2023 AND month=7 AND day=28 AND atm_location='Leggett Street' AND transaction_type='withdraw')
        AS atm USING(account_number) --atm *
    JOIN (SELECT duration,caller ,receiver FROM phone_calls pc
WHERE year=2023 AND month=7 AND day=28 AND duration <=60) AS phone ON people.phone_number=phone.caller --phone_calls *
;
