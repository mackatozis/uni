s = .5; % Step

t1 = [0:s:5]; x1 = t1.*exp(cos(2*pi*t1));
t2 = [5.1:s:10]; x2 = zeros(size(t2));
t3 = [10.1:s:15]; x3 = -3 * ones(size(t3));

t=[t1 t2 t3]
x=[x1 x2 x3]

plot(t,x)


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
