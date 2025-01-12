SELECT
    name
FROM
    people p
    JOIN stars s ON s.person_id = p.id
WHERE
    s.movie_id = (
        SELECT
            id
        FROM
            movies
        WHERE
            title = 'Toy Story'
    );
