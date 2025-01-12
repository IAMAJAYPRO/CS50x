SELECT
    title
FROM
    movies m
    JOIN stars s ON s.movie_id = m.id
    JOIN ratings r ON r.movie_id = m.id
WHERE
    s.person_id = (
        SELECT
            id
        FROM
            people
        WHERE
            name = 'Chadwick Boseman'
    )
ORDER BY
    r.rating desc
LIMIT
    5;
