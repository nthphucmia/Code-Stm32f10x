%=================================================================
% T?o ?? th? th?i gian th?c v? kho?ng c�ch nh?n ???c t? TIVA C
% D? li?u l� g�i tin bao g?m 1 byte duy nh?t
% Thay ??i c?ng COM trong h�m serial() tr??c khi ch?y script n�y
%=================================================================

% X�a h?t c?ng COM t? b? nh?
delete(instrfindall);

% Kh?i t?o v� m? COM v?i baud l� 115200
s = serial('COM4', 'baudrate', 115200);
fopen(s);

%?�ng h?t t?t c? c�c giao di?n
close ALL

points = 100;     %S? l??ng gi� tr? kho?ng c�ch hi?n th? tr�n ?? th?
data_period = 50; %Chu k? d? li?u (ms)
%x l� tr?c bi?u th? th?i gian
x = linspace(0,points*data_period, points);

%y l� tr?c bi?u th? gi� tr? c?a kho?ng c�ch
y = linspace(0,0,points);

% V? ?? th? v?i 2 tr?c x,y
figure;
lh = area(x,y);

% Set gi� tr? gi?i h?n c?a tr?c x l� [0, points*data_period] v� tr?c y l� [0, 255]
axis([0,points*data_period,0,500]);
shg;
 
    %Ch? t?i khi nh?n ???c 1 byte t? TIVA
    while s.BytesAvailable == 0 
    end
    
    %??a h?t d? li?u c? v? ph�a tr�i ?? th?
    for k = 1:1:points-1
       y(k) = y(k+1);
    end

    %??c v� hi?n th? d? li?u m?i nh?n v? ph�a b�n ph?i ?? th?
    y(points) = fread(s,1);
    
    %L?u gi� tr? v�o bi?n distance ?? hi?n th? l�n console
    distance = y(points)
 
    % Ch?nh s?a gi� tr? tr�n tr?c y
    set(lh, 'YData',y);   
    % C?p nh?t l?i bi?u ??
    drawnow;

    key = get(gcf,'CurrentKey'); %Ki?m tra l?i xem c� ?n n�t tr�n b�n ph�m kh�ng
    
close ALL   %T?t h?t ?? th?
fclose(s);  %T?t c?ng COM
delete(s);  %X�a c?ng COM t? b? nh?
clear s;    %X�a bi?n s