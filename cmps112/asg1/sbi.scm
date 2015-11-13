#!/afs/cats.ucsc.edu/courses/cmps112-wm/usr/racket/bin/mzscheme -qr
;;
;; NAME
;;    sbi.scm - silly basic interpreter
;;
;; AUTHOR
;;    Alix Feinsod
;;    ID#1436764
;;    afeinsod@ucsc.edu
;;
;; SYNOPSIS
;;    sbi.scm filename.sbir
;;
;; DESCRIPTION
;;    The file mentioned in argv[1] is read and assumed to be an
;;    SBIR program, which is the executed. 
;;

(define *stderr* (current-error-port))
 (define *run-file*
     (let-values
         (((dirpath basepath root?)
             (split-path (find-system-path 'run-file))))
         (path->string basepath))
 )

 (define (die list)
     (for-each (lambda (item) (display item *stderr*)) list)
     (newline *stderr*)
     (exit 1)
 )

 (define (usage-exit)
     (die '("Usage: " ,*run-file* " filename"))
 )

 (define (readlist-from-inputfile filename)
     (let ((inputfile (open-input-file filename)))
          (if (not (input-port? inputfile))
              (die '(,*run-file* ": " ,filename ": open failed"))
              (let ((program (read inputfile)))
                   (close-input-port inputfile)
                          program))))

;;this is just the definition of function-table, the hash table that holds all the functions
(define function-table (make-hash))

;;make-function-table: this function adds all of the necessary functions into the 
;;hash table function-table so that they can be used when executing the code.
;;no inputs, only output is putting elements in a hash table. 
(define (make-function-table)
    (hash-set! function-table 'dim (lambda (x) (hash-set! variable-table (car x) (make-vector (cadr x)))))
    (hash-set! function-table 'let (lambda (x) (hash-set! variable-table (car x) (cadr x))))
    (hash-set! function-table 'goto (lambda (x) (first (x))))
    (hash-set! function-table 'if (lambda (x) (when (car x) (cadr x))))
    (hash-set! function-table 'print (lambda (x) 
        (map (lambda (y) (print y)) x) (printf "~n")))

    (hash-set! function-table 'input (lambda (x) 
        (map (lambda (y) 
            (let ((z (read))) 
                (if
                    (not? (number? z)) 
                        ((print "Not a number ~n") ((hash-ref function-table 'input) x))
                        (hash-set! variable-table y z)))) x)
            (hash-set! variable-table inputcount (length(x)))
            ))
    (hash-set! function-table '+ (lambda (x) 
      (if (= (length x) 1)
        (first x)
        ;;else 
        (+ (first x) ((hash-ref function-table '+) (rest x)))
        )))
) 
        

;;this is just the definition of label-table, the hash table for holding labels
(define label-table (make-hash))

;;make-label-table: takes in a list of lines, and adds the lines with lables into a hash table 
;;so that they can be looked up when executing. No outputs.
(define (make-label-table list-of-lines)
    (map (lambda (line)
    (when (not (null? (cdr line)))
      (when (not (list? (second line)))
            (hash-set! label-table (cadr line) (car line))
        ))) list-of-lines)
)

;;this is just the definition of variable-table, the hash table for holding variables
(define variable-table (make-hash))

;;this function inializes some key variables in the variable-table
(define (make-variable-table)
    (hash-set! variable-table "pi" 3.14159265)
    (hash-set! variable-table "e" 2.71828)
    (hash-set! variable-table "inputcount" 0)
)

;;do-line: this recursive function takes in a line, evaluates inner expressions 
;;and then outer expressions
(define (do-line line)
  (if (list? line)
    (if (not (ormap (lambda (x) (list? x)) line))
      (eval-function line)
      ;;else
      (map (lambda (x) (do-line x)) line)
      )
    ;;else
    line
    )
)

;;eval-function: this function takes in a list that has no inner lists and 
;;calls the function on the rest of the list
(define (eval-function x)
    (when (not (null? x)) 
        (let ([func (first x)] [args (rest x)])
            ((hash-ref function-table func) args)
        )
    )
)


;;execute-line: takes in a list of lines and a line number
;;executes the line indicated by the number and then continues.
;;ouput is whatever the program is supposed to do. 
(define (execute-line list-of-lines line-num)
  (when (>= (length list-of-lines) line-num)
    (let ((line (list-ref list-of-lines (- line-num 1))))
        (let ((num (do-line (rest line))))
            (if (number? num)    
                (execute-line list-of-lines num)
                (execute-line list-of-lines (+ line-num 1))
            ))))
)

 (define (main arglist)
     (if (or (null? arglist) (not (null? (cdr arglist))))
         (usage-exit)
         (let* ((sbprogfile (car arglist))
                (program (readlist-from-inputfile sbprogfile)))
        (make-function-table)
        (make-label-table program)
        (make-variable-table)
        (execute-line program 1))))

 (main (vector->list (current-command-line-arguments)))
