% A)	
	% -10 ≤ Ω ≤ 10 rad/sec
	syms t w

	h = exp(-t).*heaviside(t);
	H = fourier(h, w);

	w2 = [-10:.001:10];
	H2 = subs(H, w, w2);

	figure(1)
	plot(w2, abs(H2))
	ylabel('Amplitude');
	figure(2)
	plot(w2, angle(H2))
	ylabel('Phase');

% B)
	syms f s t
	f = (s.^2 + 1) ./ ((s + 1) .^ 2);
	ilaplace(f)


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
