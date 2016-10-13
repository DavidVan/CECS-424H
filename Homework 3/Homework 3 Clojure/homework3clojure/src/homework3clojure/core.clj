(ns homework3clojure.core
  (:gen-class))

(defn third [coll]
  (first (next (next coll))))

(defn my-last [coll]
  (if (= (next coll) nil)
    (first coll)
    (my-last (next coll))))

(defn my-butlast [coll]
  (if (= (next coll) nil)
    nil
    (cons (first coll) (my-butlast (rest coll)))))

(defn get-at [coll i]
  (if (= i 0)
    (first coll)
    (get-at (next coll) (- i 1))))

(defn -main
  [& args]
  (println (third (list 1 2 3)))
  (println (third (list 1 2)))
  (println (my-last (list 1 2 3 4 5 6 7 8 9)))
  (println (my-last (list)))
  (println (my-butlast (list 1 2 3 4 5 6 7 8 9)))
  (println (my-butlast (list)))
  (println (get-at (list 1 2 3 4) 3))
  (println (get-at (list) 2)))