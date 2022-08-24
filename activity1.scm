(define list-length
    (lambda (x)
        (if (equal? (cdr x) ()) 1 (+ 1 (list-length (cdr x))))))

(define nth
    (lambda (n x)
        (cond
            ((< n 1)
                '())
            ((equal? x '())
                '())
            ((= n 1)
                (car x))
            (else
                (nth (- n 1) (cdr x))))))

(define remove-first
    (lambda (n x)
        (cond
            ((equal? x '())
                '())
            ((= n (car x))
                (cdr x))
            (else
                (cons (car x) (remove-first n (cdr x)))))))

(define remove-all
    (lambda (n x)
        (cond
            ((equal? x '())
                '())
            ((= n (car x))
                (remove-all n (cdr x)))
            (else
                (cons (car x) (remove-all n (cdr x)))))))

(define cons-each
    (lambda (item lst)
        (if (null? lst)
            '()
            (cons (cons item (car lst))
                  (cons-each item (cdr lst))))))

(cons-each)
; cons-each will make lst a list of pairs in which the first number is item and the second
; number is each number in lst

; (define subset
;     (lambda (lst)
;         (cond
;             ((equal? lst '())
;                 '())
;             (else
;                 (cons (cons-each (car lst) (cdr lst)) (subset (cdr lst)))))))
;
; (subset '(1 2 3))












; blank
