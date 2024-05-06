SELECT
    m.title
FROM
    movies m
    JOIN stars sa ON sa.movie_id = m.id
    JOIN stars sb ON sb.movie_id = m.id
    JOIN people pa ON pa.id = sa.person_id
    JOIN people pb ON pb.id = sb.person_id
WHERE
    pa.name = 'Bradley Cooper'
    AND pb.name = 'Jennifer Lawrence';
