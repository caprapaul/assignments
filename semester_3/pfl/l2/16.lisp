;;;; 16.
;;;; Determine if  a  tree  of  type  (2)  is  balanced  
;;;; (the  difference between  the  depth  of  two  subtrees  is equal to 1).
;;;;
;;;;    A
;;;;   / \
;;;;   B  C
;;;;     / \
;;;;     D   E
;;;;
;;;; (node (list-subtree-1) (list-subtree-2) ...)
;;;; (A (B) (C (D) (E)))

#|
    tree_depth(l1...ln) =
        -1, n = 0
        0, n = 1
        1 + depth(l2), n = 2
        1 + max(tree_depth(l2), tree_depth(l3)), otherwise
        
    tree_depth(tree)
    tree - the tree of type (2)
|#
(defun tree_depth (tree)
    (cond
        ((null tree)
            -1
        )
        ((null (cdr tree))
            0
        )
        ((null (cddr tree))
            (+ 1 (tree_depth (cadr tree)))
        )
        (t
            (+ 1 (max (tree_depth (cadr tree)) (tree_depth (caddr tree))))
        )
    )
)

(tree_depth '(A (B) (C (D) (E))))
(tree_depth '(A (B)))
(tree_depth '(A (B (G) (H (I))) (C (D) (E (F)))))

(tree_depth '(A (B (D) (E (H))) (C (F (I)) (G))))

#|
    is_balanced(l1...ln) = 
        True, n = 0
        tree_depth(l2) = 1 AND is_balanced(l2), n = 2
        -1 <= diff <= 1 AND is_balanced(l2) AND is_balanced(l3), where diff = tree_depth(l2) - tree_depth(l3),
        
    is_balanced(tree)
    tree - the tree of type (2)
|#
(defun is_balanced (tree)
    (cond
        ((null tree)
            t
        )
        ((null (cddr tree))
            (and (tree_depth (cdr tree)) (is_balanced (cdr tree)))
        )
        (t
            (and (<= -1 (- (tree_depth (cadr tree)) (tree_depth (caddr tree)))) (<= (- (tree_depth (cadr tree)) (tree_depth (caddr tree))) 1))
        )
    )
)

(is_balanced '(A (B) (C (D) (E))))
(is_balanced '(A (B (D (E))) (C)))
(is_balanced '(A (B)))
(is_balanced '(A (B (C))))

(is_balanced '(A (B (D) (E (H))) (C (F (I)) (G))))
