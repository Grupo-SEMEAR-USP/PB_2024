
(cl:in-package :asdf)

(defsystem "hw_int-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "velocidades" :depends-on ("_package_velocidades"))
    (:file "_package_velocidades" :depends-on ("_package"))
  ))