SELECT
    pb.name
FROM
    movies m
    JOIN stars skevin ON skevin.movie_id = m.id
    INNER JOIN people pk ON pk.id = skevin.person_id
    AND pk.name = 'Kevin Bacon'
    AND pk.birth = 1958
    JOIN stars sb ON sb.movie_id = m.id
    JOIN people pb ON pb.id = sb.person_id
    AND pb.name != 'Kevin Bacon';
