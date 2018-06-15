function [ w0, a ] = sas_07( w0,a )
	if a <= 0
		'ERROR'
	else
		t = [-10:.01:10];
		x1 = exp(-a*(t.^2));
		x2 = cos(w0*t);
		x3 = x1.*x2;
		x4 = cos(2*w0*t)+x2;
		subplot(221)
		plot(t,x1)
		title('exp(-a*(t^2))')
		subplot(222)
		plot(t,x2)
		title('cos(w0*t)')
		subplot(223)
		stem(t,x3)
		title('exp(-a*(t^2)) * cos(w0*t)')
		subplot(224)
		stem(t,x4)
		title('cos(2*w0*t) + cos(w0*t)')
	end	
end


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
