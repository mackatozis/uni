syms Y t s
y0 = 0;	% y(0)
y01 = 0;	% y'(0)
Y1 = s*Y-y0;	% s*Y(s)-y(0)
Y2 = s*Y1-y01;	% s*Y1(s)-y'(0)
xt = 2*exp(-t);
X = laplace(xt,s);

D = Y2+4*Y1+13*Y-X;
sol = solve(D,Y);

yt = ilaplace(sol,t)


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
