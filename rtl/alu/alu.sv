module alu #( parameter WIDTH = 8)(
    input logic [WIDTH-1:0] A,
    input logic [WIDTH-1:0] B,
    input logic [2:0] op,
    output logic [WIDTH-1:0] Y,
    output logic carry,
    output logic zero,
    output logic overflow
);
logic [WIDTH:0] result;
always_comb begin

    Y = '0;
    carry = '0;
    overflow = '0;
    result = '0;

    case (op)

        3'b000: begin
            result = A+B;
            Y=result[WIDTH-1:0];
            carry=result[WIDTH];
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

    zero = (Y=='0);
end

endmodule