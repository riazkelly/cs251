;9/24 Notes
((lambda () 99)) ;will produve 99, this is a function with no parameters that returns 99 every time
(lambda () 99) ;won't work because you need more parentheses
;Functions that don't take in parameters still need parentheses

;9/27 Notes
;Pascal is current popular functional language

;Currying is a different way to handle multiple parameters
(define mult
    (lambda (a b)
        (* a b)))

(define curry-mult
    (lambda (a)
        (lambda (b)
            (* a b))))

;(curry-mult 5) returns a procedure
;((curry-mult 5) 10) returns 50

(define mult-by-five (curry-mult 5))

(define add-one
    (lambda (x)
        (+ x 1)))
(map add-one '(1 2 3)) ;will apply the function add-one to each value in the list

(define my-map
    (lambda (f lst)
        (cond
            ((null? lst)
                '())
            (else
                (cons (f (car lst)) (my-map f (cdr lst)))))))

;(use-modules (rnrs)) ; will allow for new functions to be called
; (fold-left + 0 '(1 2 3)) ; returns 6

(define my-fold-left
    (lambda (f init lst)
        (cond
            ((null? lst)
                init)
            (else
                (my-fold-left f (f init (car lst)) (cdr lst))))))

(my-fold-left + 0 '(1 2 3))

(define my-fold-right
    (lambda (f init)))
