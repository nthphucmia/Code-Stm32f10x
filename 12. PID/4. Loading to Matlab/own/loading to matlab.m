%=================================================================
% T?o ?? th? th?i gian th?c v? kho?ng cách nh?n ???c t? TIVA C
% D? li?u là gói tin bao g?m 1 byte duy nh?t
% Thay ??i c?ng COM trong hàm serial() tr??c khi ch?y script này
%=================================================================

% Xóa h?t c?ng COM t? b? nh?
delete(instrfindall);

% Kh?i t?o và m? COM v?i baud là 115200
s = serial('COM4', 'baudrate', 115200);
fopen(s);

%?óng h?t t?t c? các giao di?n
close ALL

points = 100;     %S? l??ng giá tr? kho?ng cách hi?n th? trên ?? th?
data_period = 50; %Chu k? d? li?u (ms)
%x là tr?c bi?u th? th?i gian
x = linspace(0,points*data_period, points);

%y là tr?c bi?u th? giá tr? c?a kho?ng cách
y = linspace(0,0,points);

% V? ?? th? v?i 2 tr?c x,y
figure;
lh = area(x,y);

% Set giá tr? gi?i h?n c?a tr?c x là [0, points*data_period] và tr?c y là [0, 255]
axis([0,points*data_period,0,500]);
shg;
 
    %Ch? t?i khi nh?n ???c 1 byte t? TIVA
    while s.BytesAvailable == 0 
    end
    
    %??a h?t d? li?u c? v? phía trái ?? th?
    for k = 1:1:points-1
       y(k) = y(k+1);
    end

    %??c và hi?n th? d? li?u m?i nh?n v? phía bên ph?i ?? th?
    y(points) = fread(s,1);
    
    %L?u giá tr? vào bi?n distance ?? hi?n th? lên console
    distance = y(points)
 
    % Ch?nh s?a giá tr? trên tr?c y
    set(lh, 'YData',y);   
    % C?p nh?t l?i bi?u ??
    drawnow;

    key = get(gcf,'CurrentKey'); %Ki?m tra l?i xem có ?n nút trên bàn phím không
    
close ALL   %T?t h?t ?? th?
fclose(s);  %T?t c?ng COM
delete(s);  %Xóa c?ng COM t? b? nh?
clear s;    %Xóa bi?n s