module alu(
    input logic [7:0] A,
    input logic [7:0] B,
    input logic [2:0] op,
    output logic [7:0] Y
);

always_comb begin
    case (op)

        3'b000:
            Y=A+B;
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
end

endmodule