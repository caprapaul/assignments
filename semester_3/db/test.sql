USE test;
SELECT S1.ID, COUNT(*) NR
FROM S S1 LEFT JOIN S S2 ON S1.K = S2.L
GROUP BY S1.ID
HAVING COUNT(*) > 1;

SELECT L, M, O, P
FROM
(
SELECT S1.K, S1.L, S1.M, S2.N, S2.O, S2.P
FROM
S S1 INNER JOIN
(SELECT N, O, P FROM S WHERE N > 4) S2
ON S1.K > S2.N
) S3;