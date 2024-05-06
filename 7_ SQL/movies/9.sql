SELECT
    name
FROM
    movies m
    JOIN stars s ON s.movie_id = m.id
    JOIN people p ON s.person_id = p.id
WHERE
    m.year = 2004
ORDER BY
    p.birth;
