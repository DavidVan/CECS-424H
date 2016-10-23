(ns lab3clojingtime.core
  (:gen-class))

(defn third [list]
  (second (next list)))

;; True if the form is a variable (symbol).
(defn variable? [form]
  (symbol? form))

;; True if the two forms are the same variable.
(defn same-variable? [form1 form2]
  (and (variable? form1) (variable? form2) (= form1 form2)))

;; True if the form represents a sum.
(defn sum? [form]
  (and (list? form) (= '+ (first form))))

;; Constructs a sum of a and b.
(defn make-sum [a b]
  (list '+ a b))

;; Selects the addend (first value) of a sum.
(defn addend [sum]
  (second sum))

;; Selects the augend (second value) of a sum.
(defn augend [sum]
  (third sum))

;; True if the form represents a difference.
(defn diff? [form]
  (and (list? form) (= '- (first form))))

;; Constructs a difference of a and b.
(defn make-diff [a b]
  (list '- a b))

;; Selects the subtrahend (first value) of a difference.
  (defn subtrahend [diff]
  (second diff))

;; Selects the minuend (second value) of a difference.
(defn minuend [diff]
  (third diff))

;; True if the form represents a product.
(defn prod? [form]
  (and (list? form) (= '* (first form))))

;; Constructs a product of a and b.
(defn make-prod [a b]
  (list '* a b))

;; Selects the multiplier (first value) of a product.
(defn multiplier [prod]
  (second prod))

;; Selects the multiplicand (second value) of a product.
(defn multiplicand [prod]
  (third prod))

;; True if the form represents a quotient.
(defn quot? [form]
  (and (list? form) (= '/ (first form))))

;; Constructs a quotient of a and b.
(defn make-quot [a b]
  (list '/ a b))

;; Selects the dividend (first value) of a quotient.
(defn dividend [quot]
  (second quot))

;; Selects the divisor (second value) of a quotient.
(defn divisor [quot]
  (third quot))

;; True if the form represents a power.
(defn power? [form]
  (and (list? form) (= '** (first form))))

;; Constructs a power of a and b.
(defn make-power [a b]
  (list '** a b))

;; Selects the base (first value) of a power.
(defn base [power]
  (second power))

;; Selects the exponent (second value) of a power.
(defn exponent [power]
  (third power))

;; True if the form represents a natural logarithm.
(defn ln? [form]
  (and (list? form) (= 'ln (first form))))

;; Constructs a ln of a.
(defn make-ln [a]
  (list 'ln a))

;; Selects the antilogarithm of a logarithm.
(defn log-of [antilog]
  (second antilog))

;; True if the form represents a sin.
(defn sin? [form]
  (and (list? form) (= 'sin (first form))))

;; Constructs a sin of a.
(defn make-sin [a]
  (list 'sin a))

;; True if the form represents a cos.
(defn cos? [form]
  (and (list? form) (= 'cos (first form))))

;; Constructs a cos of a.
(defn make-cos [a]
  (list 'cos a))

;; True if the form represents a tan.
(defn tan? [form]
  (and (list? form) (= 'tan (first form))))

;; Constructs a tan of a.
(defn make-tan [a]
  (list 'tan a))

;; True if the form represents a sec.
(defn sec? [form]
  (and (list? form) (= 'sec (first form))))

;; Constructs a sec of a.
(defn make-sec [a]
  (list 'sec a))

;; True if the form represents a csc.
(defn csc? [form]
  (and (list? form) (= 'csc (first form))))

;; Constructs a csc of a.
(defn make-csc [a]
  (list 'csc a))

;; True if the form represents a cot.
(defn cot? [form]
  (and (list? form) (= 'cot (first form))))

;; Constructs a cot of a.
(defn make-cot [a]
  (list 'cot a))

;; Selects the angle of a trigonometric function.
(defn angle [trig]
  (second trig))



;; Returns the derivative of a function expressed in Clojure notation, where variables are quoted.
;; The second parameter is the variable which the derivative is calculated with respect to.
(defn derivative [form var]
  (cond ; The derivative of a constant is 0
    (number? form) 0
    ; The derivative of a variable is 0 if the variable is not the one being derived; or 1, if it is.
    (variable? form) (if (same-variable? form var) 1 0)
    ; Sum rule
    (sum? form) (make-sum (derivative (addend form) var)
                          (derivative (augend form) var))
    ; Difference rule
    (diff? form) (make-diff (derivative (subtrahend form) var)
                            (derivative (minuend form) var))
    ; Product rule
    (prod? form) (make-sum (make-prod (multiplier form)
                                      (derivative (multiplicand form) var))
                           (make-prod (derivative (multiplier form) var)
                                      (multiplicand form)))
    ; Power rule
    (power? form) (make-prod (make-prod (exponent form)
                                        (make-power (base form) (- (exponent form) 1)))
                             (derivative (base form) var))
    ; Quotient rule
    (quot? form) (make-quot (make-diff (make-prod (divisor form) (derivative (dividend form) var))
                                      (make-prod (dividend form) (derivative (divisor form) var)))
                            (make-power (divisor form) 2))
    ; Natural logarithm
    (ln? form) (make-quot (derivative (log-of form) var) (log-of form))
    ; Sin
    (sin? form) (make-prod (make-cos (angle form)) (derivative (angle form) var))
    ; Cos
    (cos? form) (make-prod -1 (make-prod (make-sin (angle form)) (derivative (angle form) var)))
    ; Tan
    (tan? form) (make-prod (make-power (make-sec (angle form)) 2) (derivative (angle form) var))
    ; Sec
    (sec? form) (make-prod (make-prod (make-sec (angle form)) (make-tan (angle form)))
                           (derivative (angle form) var))
    ; Csc
    (csc? form) (make-prod -1 (make-prod (make-prod (make-csc (angle form)) (make-cot (angle form)))
                                         (derivative (angle form) var)))
    ; Cot
    (cot? form) (make-prod -1 (make-prod (make-power (make-csc (angle form)) 2) (derivative (angle form) var)))
    ))

(defn -main
  [& args]
  (println (derivative '(/ 2 (+ x 1)) 'x))
  (println (power? '(** x 1)))
  (println (make-power 'x 2))
  (println (make-prod 'x -2))
  (println (make-prod -1 -2))
  (println (derivative '(ln x) 'x))
  (println (derivative '(sin x) 'x))
  (println (derivative '(cos x) 'x))
  (println (derivative '(tan x) 'x))
  (println (derivative '(sec x) 'x))
  (println (derivative '(csc x) 'x))
  (println (derivative '(cot x) 'x)))
