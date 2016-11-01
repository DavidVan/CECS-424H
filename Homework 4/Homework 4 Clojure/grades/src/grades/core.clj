(ns grades.core
  (:gen-class))

(defn third [list]
  (second (next list)))

(defn make-course [name grade units]
  (list name grade units))

(defn course-name [course]
  (first course))

(defn course-grade [course]
  (second course))

(defn course-units [course]
  (third course))

(def ada-courses
  (list (make-course "CECS 174" "A" 3)
        (make-course "ENGR 101" "B" 1)
        (make-course "CECS 282" "D" 3)
        (make-course "EE 380" "C" 3)))

(defn grade-weight [grade]
  (cond
    (= "A" grade) 4
    (= "B" grade) 3
    (= "C" grade) 2
    (= "D" grade) 1
    (= "F" grade) 0
    :else 0))

(defn calculate-gpa [courses]
  (float (/ (reduce + (map #(* (course-units %) (grade-weight (course-grade %))) courses))
            (reduce + (map course-units courses)))))

(defn -main
  [& args]
  (println (filter #(.startsWith % "CECS") (map course-name ada-courses)))

  (println (reduce + (map course-units ada-courses)))

  (println (map course-name (filter #(or (= "A" (course-grade %)) (= "B" (course-grade %)) (= "C" (course-grade %))) ada-courses)))
  ; Alternative way of doing above...
  (println (map course-name (filter #(<= (.compareTo (course-grade %) "C") 0) ada-courses)))

  (println (calculate-gpa ada-courses)))
