(defproject homework3clojure "0.1.0-SNAPSHOT"
  :description "CECS 424H - Homework 3"
  :url "http://davidvan.net"
  :license {:name "Eclipse Public License"
            :url "http://www.eclipse.org/legal/epl-v10.html"}
  :dependencies [[org.clojure/clojure "1.8.0"]]
  :main ^:skip-aot homework3clojure.core
  :target-path "target/%s"
  :profiles {:uberjar {:aot :all}})
