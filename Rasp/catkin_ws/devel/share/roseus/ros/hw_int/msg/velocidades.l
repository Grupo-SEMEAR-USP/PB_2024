;; Auto-generated. Do not edit!


(when (boundp 'hw_int::velocidades)
  (if (not (find-package "HW_INT"))
    (make-package "HW_INT"))
  (shadow 'velocidades (find-package "HW_INT")))
(unless (find-package "HW_INT::VELOCIDADES")
  (make-package "HW_INT::VELOCIDADES"))

(in-package "ROS")
;;//! \htmlinclude velocidades.msg.html


(defclass hw_int::velocidades
  :super ros::object
  :slots (_vel_esq _vel_dir ))

(defmethod hw_int::velocidades
  (:init
   (&key
    ((:vel_esq __vel_esq) 0.0)
    ((:vel_dir __vel_dir) 0.0)
    )
   (send-super :init)
   (setq _vel_esq (float __vel_esq))
   (setq _vel_dir (float __vel_dir))
   self)
  (:vel_esq
   (&optional __vel_esq)
   (if __vel_esq (setq _vel_esq __vel_esq)) _vel_esq)
  (:vel_dir
   (&optional __vel_dir)
   (if __vel_dir (setq _vel_dir __vel_dir)) _vel_dir)
  (:serialization-length
   ()
   (+
    ;; float64 _vel_esq
    8
    ;; float64 _vel_dir
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _vel_esq
       (sys::poke _vel_esq (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _vel_dir
       (sys::poke _vel_dir (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _vel_esq
     (setq _vel_esq (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _vel_dir
     (setq _vel_dir (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get hw_int::velocidades :md5sum-) "5827453567ecbdabddb68554148b9c0e")
(setf (get hw_int::velocidades :datatype-) "hw_int/velocidades")
(setf (get hw_int::velocidades :definition-)
      "float64 vel_esq
float64 vel_dir
")



(provide :hw_int/velocidades "5827453567ecbdabddb68554148b9c0e")


