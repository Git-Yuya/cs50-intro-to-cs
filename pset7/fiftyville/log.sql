-- Keep a log of any SQL queries you execute as you solve the mystery.

--Crime scene reports
SELECT description
FROM crime_scene_reports
WHERE year = 2020 AND month = 7 AND day = 28 AND street = "Chamberlin Street";
/*
description
Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.
*/

--Interviews
SELECT transcript
FROM interviews
WHERE year = 2020 AND month = 7 AND day = 28 AND transcript LIKE "%thief%";
/*
transcript
Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
*/

--Courthouse security logs
SELECT license_plate
FROM courthouse_security_logs
WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = "exit";
/*
license_plate
5P2BI95
94KL13X
6P58WS2
4328GD8
G412CB7
L93JTIZ
322W7JE
0NTHK55
*/

--ATM transactions
SELECT account_number
FROM atm_transactions
WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw";
/*
account_number
28500762
28296815
76054385
49610011
16153065
25506511
81061156
26013199
*/

--Bank accounts
SELECT person_id
FROM bank_accounts
WHERE account_number IN (28500762, 28296815, 76054385, 49610011, 16153065, 25506511, 81061156, 26013199);
/*
person_id
686048
514354
458378
395717
396669
467400
449774
438727
*/

--Phone calls
SELECT caller, receiver
FROM phone_calls
WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60;
/*
caller | receiver
(130) 555-0289 | (996) 555-8899
(499) 555-9472 | (892) 555-8872
(367) 555-5533 | (375) 555-8161
(499) 555-9472 | (717) 555-1342
(286) 555-6063 | (676) 555-6554
(770) 555-1861 | (725) 555-3243
(031) 555-6622 | (910) 555-3251
(826) 555-1652 | (066) 555-9701
(338) 555-6650 | (704) 555-2131
*/

--Flights
SELECT flights.id, destination_airport_id
FROM flights
JOIN airports ON airports.id = flights.origin_airport_id
WHERE year = 2020 AND month = 7 AND day = 29 AND hour >= 0 AND city = "Fiftyville"
ORDER BY hour, minute DESC
LIMIT 1;
/*
id | destination_airport_id
36 | 4
*/

--Passengers
SELECT passport_number
FROM passengers
WHERE flight_id = 36;
/*
passport_number
7214083635
1695452385
5773159633
1540955065
8294398571
1988161715
9878712108
8496433585
*/

--Find the location that the thief escaped
SELECT city
FROM airports
WHERE id = 4;
/*
city
London
*/

--Find the thief
SELECT name
FROM people
WHERE id IN (686048, 514354, 458378, 395717, 396669, 467400, 449774, 438727)
    AND phone_number IN ("(130) 555-0289", "(499) 555-9472", "(367) 555-5533", "(499) 555-9472", "(286) 555-6063", "(770) 555-1861", "(031) 555-6622", "(826) 555-16521", "(338) 555-6650")
    AND passport_number IN (7214083635, 1695452385, 5773159633, 1540955065, 8294398571, 1988161715, 9878712108, 8496433585)
    AND license_plate IN ("5P2BI95", "94KL13X", "6P58WS2", "4328GD8", "G412CB7", "L93JTIZ", "322W7JE", "0NTHK55");
/*
name
Ernest
*/

--Find information about Ernest
SELECT *
FROM people
WHERE name = "Ernest";
/*
id | name | phone_number | passport_number | license_plate
686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X
*/

--Find the accomplice
SELECT name
FROM people
WHERE phone_number = "(375) 555-8161";
/*
name
Berthold
*/
