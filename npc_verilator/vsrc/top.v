module top(
    input rst,
    input [7:0] init,
    input clk,
    output reg [7:0] num2,
    output reg [7:0] num1
);
    reg temp;
    reg [7:0] q;
    reg [3:0]temp1,temp2;
    always @(posedge rst or posedge clk) begin
        if (rst) q<=init;
        else if(q == 0) q<= 8'b00000001;
        else begin
          temp<=q[3]^q[2]^q[4]^q[0];
          q<={temp,q[7:1]};
        end
    end
    always @(*) begin
                temp2=q[7:4];
                temp1=q[3:0];
                case(temp1)
                    4'b0000:num1=~8'b11111101;
                    4'b0001:num1=~8'b01100000;
                    4'b0010:num1=~8'b11011010;
                    4'b0011:num1=~8'b11110010;
                    4'b0100:num1=~8'b01100110;
                    4'b0101:num1=~8'b10110110;
                    4'b0110:num1=~8'b10111110;
                    4'b0111:num1=~8'b11100000;
                    4'b1000:num1=~8'b11111110;
                    4'b1001:num1=~8'b11110110;
                    4'b1010:num1=~8'b11111010;
                    4'b1011:num1=~8'b00111110;
                    4'b1100:num1=~8'b10011100;
                    4'b1101:num1=~8'b01111010;
                    4'b1110:num1=~8'b10011110;
                    4'b1111:num1=~8'b10001110;
                endcase
                case(temp2)
                    4'b0000:num2=~8'b11111101;
                    4'b0001:num2=~8'b01100000;
                    4'b0010:num2=~8'b11011010;
                    4'b0011:num2=~8'b11110010;
                    4'b0100:num2=~8'b01100110;
                    4'b0101:num2=~8'b10110110;
                    4'b0110:num2=~8'b10111110;
                    4'b0111:num2=~8'b11100000;
                    4'b1000:num2=~8'b11111110;
                    4'b1001:num2=~8'b11110110;
                    4'b1010:num2=~8'b11111010;
                    4'b1011:num2=~8'b00111110;
                    4'b1100:num2=~8'b10011100;
                    4'b1101:num2=~8'b01111010;
                    4'b1110:num2=~8'b10011110;
                    4'b1111:num2=~8'b10001110;
                endcase
    end
endmodule