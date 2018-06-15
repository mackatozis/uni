t = [-10:.01:10];
u1 = heaviside(t-1);
u2 = heaviside(t+1);
% ramp = t*u(t)
r1 = t .* u1;
r2 = t .* u2 - t .* heaviside(t-2);

subplot(221)
plot(t,u1)
title('u(t-1)')
subplot(222)
plot(t,u2)
title('u(t+1)')
subplot(223)
stem(t,r1)
title('r(t-1)')
subplot(224)
stem(t,r2)
title('r(t+1) - r(t-2)')


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
