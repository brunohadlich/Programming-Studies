## Copyright (C) 2019 bruno
## 
## This program is free software: you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see
## <https://www.gnu.org/licenses/>.

## -*- texinfo -*- 
## @deftypefn {} {@var{retval} =} feedforward (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: bruno <bruno@DESKTOP-TEHHKQ2>
## Created: 2019-06-09

function h2 = feedforward(Theta1, Theta2, X)
  m = size(X, 1);
  num_labels = size(Theta2, 1);

  p = zeros(m, 1);

  h1 = sigmoid([ones(m, 1) X] * Theta1');
  h2 = sigmoid([ones(m, 1) h1] * Theta2');
  %[dummy, p] = max(h2, [], 2);
endfunction
