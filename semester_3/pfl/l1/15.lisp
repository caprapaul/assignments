;;;; 15.
;;;; a) Write a function to insert an element E on the n-th position of a linear list.
;;;; b) Write a function to return the sum of all numerical atoms of a list, at any level.
;;;; c) Write a function to return the set of all sublists of a given linear list. 
;;;;    Ex. For list ((1 2 3) ((4 5) 6)) => ((1 2 3) (4 5) ((4 5) 6)) 
;;;; d) Write a function to test the equality of two sets, without using the difference of two sets

#|  
    a) Write a function to insert an element E on the n-th position of a linear list.

    insert_e(l0...lm, e, n)
        nil, n < 0 OR n > m - 1
        e U l0...lm, n = 0
        l0 U insert_e(l1...ln, e, n - 1), otherwise

    insert_e(l, e, n)
    l - a list
    e - element to insert
    n - position to insert on
|#
(defun insert_e (l e n)
    (cond
        ((or (< n 0) (> n (length l)))
            nil
        )
        ((equal n 0)
            (cons e l)
        )
        (t
            (cons (car l) (insert_e (cdr l) e (- n 1)))
        )
    )
)

(insert_e '(1 2 3 4) '5 '4)
(insert_e '(1 2 3 4) '5 '2)
(insert_e '() '5 '0)
(insert_e '(1 2 3 4) '5 '-1)
(insert_e '(1 2 3 4) '5 '6)

#|  
    b) Write a function to return the sum of all numerical atoms of a list, at any level.

    sum_all(l1...ln)
        0, n = 0
        l1 + sum_all(l2...ln), l1 is numerical atom
        sum_all(l1_1...l1_n) + sum_all(l2...ln), l1 is list
        sum_all(l2...ln), otherwise

        sum_all(l)
        l - a list
|#
(defun sum_all (l)
    (cond
        ((null l) 
            0
        )
        ((numberp (car l)) 
            (+ (car l) (sum_all (cdr l)))
        )
        ((listp (car l)) 
            (+ (sum_all (car l)) (sum_all (cdr l)))
        )
        (t 
            (sum_all (cdr l))
        )
    )
)

(sum_all '((1 2) 3 (4 (5 6))))
(sum_all '((1 B) 3 (4 (C A))))

#|  
    c) Write a function to return the set of all sublists of a given non-linear list. 
    Ex. For list ((1 2 3) ((4 5) 6)) => ((1 2 3) (4 5) ((4 5) 6))

    sublists(l1...ln)
        [], n = 0
        l1 U sublists(l1_1...l1_n) U sublists(l2...ln), l1 is a list
        sublists(l2...ln), otherwise

    sublists(l)
    l - a list
|#
(defun sublists (l)
    (cond
        ((null l)
            nil
        )
        ((listp (car l))
            (append (cons (car l) (sublists (car l))) (sublists (cdr l)))
        )
        (t 
            (sublists (cdr l))
        )
    )
)

(sublists '((1 2 3) ((4 5) 6)))
(sublists '())

#|  
    d) Write a function to test the equality of two sets, without using the difference of two sets

    remove_e(l1...ln, e)
        [], n = 0
        l2...ln, l1 = e
        l1 U remove_e(l2...ln), otherwise

    remove_e(l, e)
    l - a list
    e - element to remove
|#
(defun remove_e (l e)
    (cond
        ((null l)
            nil
        )
        ((equal (car l) e) 
            (cdr l)
        )
        (t 
            (cons (car l) (remove_e (cdr l) e))
        )
    )
)

(remove_e '(1 2 3) '2)
(remove_e '(1 (2) 3) '(2))
(remove_e '(1 2 3) '4)
(remove_e '() '2)

#|
    equal_sets(l1...ln, s1...sm)
        True, n = m = 0
        False, n != m
        equal_sets(l2...ln, r1...rn), where r = remove_e(s1...sn, l1), otherwise

    equal_sets(l, s)
    l - the first set
    s - the second set
|#
(defun equal_sets (l s)
    (cond
        ((and (null l) (null s)) 
            t
        )
        ((not (equal (length l) (length s)))
            nil
        )
        (t 
            (equal_sets (cdr l) (remove_e s (car l)))
        )
    )
)

(equal_sets '(1 2 3 4 5) '(5 4 1 2 3))
(equal_sets '(1 (2 3) 4 5) '(5 4 1 (2 3)))
(equal_sets '(1 2 3 4 5) '(1 2 3))
(equal_sets '(1 2 3 4 5) '(5 4 6 2 3))
