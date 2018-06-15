s=.01; % Step

t1 = [0:s:1]; x1 = ones(size(t1))
t2 = [1:s:2]; x2 = 2 * ones(size(t2))
t3 = [2:s:10]; x3 = zeros(size(t3))

t = [t1 t2 t3]
x = [x1 x2 x3]
ty = 0:s:20.04;

h = 2 * exp(-2*t) .* heaviside(t);
y = conv(x,h);

plot(ty,y)
legend('Output y(t)')


%================================================================================%
% The MIT License								 %
%										 %
% Copyright 2012 Alexandros Efthymiadis.					 %
%										 %
% Permission is hereby granted, free of charge, to any person obtaining a copy	 %
% of this software and associated documentation files (the "Software"), to deal	 %
% in the Software without restriction, including without limitation the rights	 %
% to use, copy, modify, merge, publish, distribute, sublicense, and/or sell	 %
% copies of the Software, and to permit persons to whom the Software is		 %
% furnished to do so, subject to the following conditions:			 %
%										 %
% The above copyright notice and this permission notice shall be included in	 %
% all copies or substantial portions of the Software.				 %
%										 %
% THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR	 %
% IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,	 %
% FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE	 %
% AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER	 %
% LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,	 %
% OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN	 %
% THE SOFTWARE.									 %
%================================================================================%
