module alu(
    input logic [7:0] A,
    input logic [7:0] B,
    input logic [2:0] op,
    output logic [7:0] Y,
    output logic carry,
    output logic zero,
    output logic overflow
);
logic [8:0] result;
always_comb begin

    Y = 8'b0;
    carry = 1'b0;
    overflow = 1'b0;
    result = 9'b0;
    
    case (op)

        3'b000: begin
            result = A+B;
            Y=result[7:0];
            carry=result[8];
        end
        3'b001:
            Y=A-B;  
        3'b010:
            Y=A&B;
        3'b011:
            Y=A|B;
        3'b100:
            Y=A^B;
        3'b101:
            Y=~A;
        3'b110:
            Y=A<<1;
        3'b111:
            Y=A>>1;
        default:
            Y=A+B;

    endcase

    zero = (Y==0);
end

endmodule