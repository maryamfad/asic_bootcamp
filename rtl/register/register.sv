module register #(parameter WIDTH = 8)(
    input logic clk,
    input logic rst,
    input logic en,
    input logic [WIDTH-1:0] D,
    output logic [WIDTH-1:0] Q
);

always_ff @(posedge clk ) 
begin
    if(rst)
    begin
        Q <= '0;
    end

    else if (en)
    begin
        Q <= D;
    end
end

endmodule