#ifndef IR_CODE_STRUCT_H
#define IR_CODE_STRUCT_H

struct ir_code_item {
    String name;
    const uint16_t* raw_data;
    uint8_t length;
    const uint64_t decoded;
};

#endif  // IR_CODE_STRUCT_H