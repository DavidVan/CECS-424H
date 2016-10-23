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

;; OLD VERSION
;; Constructs a sum of a and b.
;(defn make-sum [a b]
;  (list '+ a b))

;; Constructs a sum of a and b.
(defn make-sum [a b]
  (cond
    (= 0 b) a
    (= 0 a) b
    (and (number? a) (number? b)) (+ a b)
    :else (list '+ a b)))

;; Selects the addend (first value) of a sum.
(defn addend [sum]
  (second sum))

;; Selects the augend (second value) of a sum.
(defn augend [sum]
  (third sum))

;; True if the form represents a difference.
(defn diff? [form]
  (and (list? form) (= '- (first form))))

;; OLD VERSION
;; Constructs a difference of a and b.
;(defn make-diff [a b]
;  (list '- a b))

;; Constructs a difference of a and b.
(defn make-diff [a b]
  (cond
    (= a 0) (list '- b)
    (= b 0) a
    (and (number? a) (number? b)) (- a b)
    :else (list '- a b)))

;; Selects the subtrahend (first value) of a difference.
  (defn subtrahend [diff]
  (second diff))

;; Selects the minuend (second value) of a difference.
(defn minuend [diff]
  (third diff))

;; True if the form represents a product.
(defn prod? [form]
  (and (list? form) (= '* (first form))))

;; OLD VERSION
;; Constructs a product of a and b.
;(defn make-prod [a b]
;  (list '* a b))

;; Constructs a product of a and b.
(defn make-prod [a b]
  (cond
    (= a 0) 0
    (= b 0) 0
    (= a 1) b
    (= b 1) a
    (and (number? a) (number? b)) (* a b)
    :else (list '* a b)))

;; Selects the multiplier (first value) of a product.
(defn multiplier [prod]
  (second prod))

;; Selects the multiplicand (second value) of a product.
(defn multiplicand [prod]
  (third prod))

;; True if the form represents a quotient.
(defn quot? [form]
  (and (list? form) (= '/ (first form))))

;; OLD VERSION
;; Constructs a quotient of a and b.
;(defn make-quot [a b]
;  (list '/ a b))

;; Constructs a quotient of a and b.
(defn make-quot [a b]
  (cond
    (= a 0) 0
    (= b 1) a
    (and (number? a) (number? b)) (/ a b)
    :else (list '/ a b)))

;; Selects the dividend (first value) of a quotient.
(defn dividend [quot]
  (second quot))

;; Selects the divisor (second value) of a quotient.
(defn divisor [quot]
  (third quot))

;; True if the form represents a power.
(defn power? [form]
  (and (list? form) (= '** (first form))))

;; OLD VERSION
;; Constructs a power of a and b.
;(defn make-power [a b]
;  (list '** a b))

;; Constructs a power of a and b.
(defn make-power [a b]
  (cond
    (= b 0) 1
    (= b 1) a
    (and (number? a) (number? b)) (Math/pow a b)
    :else (list '** a b)))

;; Selects the base (first value) of a power.
(defn base [power]
  (second power))

;; Selects the exponent (second value) of a power.
(defn exponent [power]
  (third power))

;; True if the form represents a natural logarithm.
(defn ln? [form]
  (and (list? form) (= 'ln (first form))))

;; OLD VERSION
;; Constructs a ln of a.
;(defn make-ln [a]
;  (list 'ln a))

;; Constructs a ln of a.
(defn make-ln [a]
  (cond
    (number? a) (Math/log a)
    :else (list 'ln a)))

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

;; Constructs a sec of a.
(defn make-sec [a]
  (list 'sec a))

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
  (println (derivative '(cot x) 'x))
  (println "Sum Test")
  (println (make-sum 0 5))
  (println (make-sum 5 0))
  (println (make-sum 1 5))
  (println (make-sum 5 1))
  (println (make-sum 5 5))
  (println (make-sum 'x 5))
  (println (make-sum 5 'x))
  (println (make-sum 'x 'y))
  (println "Diff Test")
  (println (make-diff 0 5))
  (println (make-diff 5 0))
  (println (make-diff 1 5))
  (println (make-diff 5 1))
  (println (make-diff 5 5))
  (println (make-diff 'x 5))
  (println (make-diff 5 'x))
  (println (make-diff 'x 'y))
  (println "Prod Test")
  (println (make-prod 0 5))
  (println (make-prod 5 0))
  (println (make-prod 1 5))
  (println (make-prod 5 1))
  (println (make-prod 5 5))
  (println (make-prod 'x 5))
  (println (make-prod 5 'x))
  (println (make-prod 'x 'y))
  (println "Quot Test")
  (println (make-quot 0 5))
  ;(println (make-quot 5 0)) ; Should crash.
  (println (make-quot 1 5))
  (println (make-quot 5 1))
  (println (make-quot 5 5))
  (println (make-quot 'x 5))
  (println (make-quot 5 'x))
  (println (make-quot 'x 'y))
  (println "Power Test")
  (println (make-power 0 5))
  (println (make-power 5 0))
  (println (make-power 1 5))
  (println (make-power 5 1))
  (println (make-power 5 5))
  (println (make-power 'x 5))
  (println (make-power 5 'x))
  (println (make-power 'x 'y))
  (println "Natural Logarithm Test")
  (println (make-ln 0))
  (println (make-ln 1))
  (println (make-ln 5))
  (println (make-ln -1))
  (println (make-ln 'x))
  (println (make-ln 'y))
  (println (derivative '(+ (* x x) 5) 'x))
  )
