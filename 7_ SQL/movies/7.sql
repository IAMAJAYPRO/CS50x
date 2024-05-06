SELECT
    title,
    r.rating
FROM
    movies m
    JOIN ratings r ON r.movie_id = m.id
WHERE
    m.year = 2010
ORDER BY
    r.rating desc,
    title;
