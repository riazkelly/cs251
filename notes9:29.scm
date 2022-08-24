(define fact
    (lambda (n partial)
        (if (= n 1)
            partial
            (fact (- n 1)
                (* n partial)))))
; version of factorial that utilizes Tail Call Optimization
