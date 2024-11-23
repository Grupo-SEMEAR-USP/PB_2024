// Auto-generated. Do not edit!

// (in-package hw_int.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class velocidades {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.vel_esq = null;
      this.vel_dir = null;
    }
    else {
      if (initObj.hasOwnProperty('vel_esq')) {
        this.vel_esq = initObj.vel_esq
      }
      else {
        this.vel_esq = 0.0;
      }
      if (initObj.hasOwnProperty('vel_dir')) {
        this.vel_dir = initObj.vel_dir
      }
      else {
        this.vel_dir = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type velocidades
    // Serialize message field [vel_esq]
    bufferOffset = _serializer.float64(obj.vel_esq, buffer, bufferOffset);
    // Serialize message field [vel_dir]
    bufferOffset = _serializer.float64(obj.vel_dir, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type velocidades
    let len;
    let data = new velocidades(null);
    // Deserialize message field [vel_esq]
    data.vel_esq = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [vel_dir]
    data.vel_dir = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 16;
  }

  static datatype() {
    // Returns string type for a message object
    return 'hw_int/velocidades';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '5827453567ecbdabddb68554148b9c0e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 vel_esq
    float64 vel_dir
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new velocidades(null);
    if (msg.vel_esq !== undefined) {
      resolved.vel_esq = msg.vel_esq;
    }
    else {
      resolved.vel_esq = 0.0
    }

    if (msg.vel_dir !== undefined) {
      resolved.vel_dir = msg.vel_dir;
    }
    else {
      resolved.vel_dir = 0.0
    }

    return resolved;
    }
};

module.exports = velocidades;
