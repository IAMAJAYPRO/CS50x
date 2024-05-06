SELECT
    p.name
FROM
    movies m
    JOIN ratings r ON r.movie_id = m.id
    AND r.rating >= 9
    JOIN directors d ON d.movie_id = m.id
    JOIN people p ON p.id = d.person_id;
