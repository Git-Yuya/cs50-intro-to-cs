SELECT title
FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON people.id = stars.person_id
WHERE name = "Johnny Depp"
AND movie_id IN (
    SELECT movie_id
    FROM stars
    JOIN people ON people.id = stars.person_id
    WHERE name = "Helena Bonham Carter"
);
