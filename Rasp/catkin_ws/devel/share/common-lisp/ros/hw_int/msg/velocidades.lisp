; Auto-generated. Do not edit!


(cl:in-package hw_int-msg)


;//! \htmlinclude velocidades.msg.html

(cl:defclass <velocidades> (roslisp-msg-protocol:ros-message)
  ((vel_esq
    :reader vel_esq
    :initarg :vel_esq
    :type cl:float
    :initform 0.0)
   (vel_dir
    :reader vel_dir
    :initarg :vel_dir
    :type cl:float
    :initform 0.0))
)

(cl:defclass velocidades (<velocidades>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <velocidades>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'velocidades)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hw_int-msg:<velocidades> is deprecated: use hw_int-msg:velocidades instead.")))

(cl:ensure-generic-function 'vel_esq-val :lambda-list '(m))
(cl:defmethod vel_esq-val ((m <velocidades>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hw_int-msg:vel_esq-val is deprecated.  Use hw_int-msg:vel_esq instead.")
  (vel_esq m))

(cl:ensure-generic-function 'vel_dir-val :lambda-list '(m))
(cl:defmethod vel_dir-val ((m <velocidades>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hw_int-msg:vel_dir-val is deprecated.  Use hw_int-msg:vel_dir instead.")
  (vel_dir m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <velocidades>) ostream)
  "Serializes a message object of type '<velocidades>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'vel_esq))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'vel_dir))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <velocidades>) istream)
  "Deserializes a message object of type '<velocidades>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vel_esq) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vel_dir) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<velocidades>)))
  "Returns string type for a message object of type '<velocidades>"
  "hw_int/velocidades")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'velocidades)))
  "Returns string type for a message object of type 'velocidades"
  "hw_int/velocidades")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<velocidades>)))
  "Returns md5sum for a message object of type '<velocidades>"
  "5827453567ecbdabddb68554148b9c0e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'velocidades)))
  "Returns md5sum for a message object of type 'velocidades"
  "5827453567ecbdabddb68554148b9c0e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<velocidades>)))
  "Returns full string definition for message of type '<velocidades>"
  (cl:format cl:nil "float64 vel_esq~%float64 vel_dir~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'velocidades)))
  "Returns full string definition for message of type 'velocidades"
  (cl:format cl:nil "float64 vel_esq~%float64 vel_dir~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <velocidades>))
  (cl:+ 0
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <velocidades>))
  "Converts a ROS message object to a list"
  (cl:list 'velocidades
    (cl:cons ':vel_esq (vel_esq msg))
    (cl:cons ':vel_dir (vel_dir msg))
))
