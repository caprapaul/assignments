;;;; 3.
;;;; Define a function to test the membership of a node in a n-tree represented as 
;;;; (root list_of_nodes_subtree1 ... list_of_nodes_subtreen) 
;;;; Eg. tree is (a (b (c)) (d) (E (f))) and the node is "b" => true

#|
    is_node(l, x) =
        1, l is atom AND l = x
        0, l is atom AND l != x
        SUM i=1,n is_node(l_i, x), if l=[l_1, l_2, ... ,l_n]

    is_node (tree, node)
    tree - the tree represented as (root list_of_nodes_subtree1 ... list_of_nodes_subtreen) 
    node - the node to search for
|#

(defun is_node (tree node)
    (cond
        ((and (atom tree) (equal tree node))
            1
        )
        ((atom tree)
            0
        )
        (t
            (apply '+ (mapcar #'(lambda (x) (is_node x node)) tree))
        )
    )
)

(is_node '(a (b (c)) (d) (E (f))) 'b)
(is_node '(a (b (c)) (d) (E (f))) 'a)
(is_node '(a (b (c)) (d) (E (f))) 'f)
(is_node '(a (b (c)) (d) (E (f))) 'g)
(is_node '() 'a)
