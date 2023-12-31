SELECT DISTINCT name
FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON movies.id = stars.movie_id
WHERE name != "Kevin Bacon"
AND movie_id IN (
    SELECT movie_id
    FROM stars
    JOIN people ON people.id = stars.person_id
    WHERE name = "Kevin Bacon" AND birth = 1958
);
