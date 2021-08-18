function [J, grad] = linearRegCostFunction(X, y, theta, lambda)
%LINEARREGCOSTFUNCTION Compute cost and gradient for regularized linear 
%regression with multiple variables
%   [J, grad] = LINEARREGCOSTFUNCTION(X, y, theta, lambda) computes the 
%   cost of using theta as the parameter for linear regression to fit the 
%   data points in X and y. Returns the cost in J and the gradient in grad

% Initialize some useful values
m = length(y); % number of training examples
n = length(size(X,2));
% You need to return the following variables correctly 

total = 0;
for i = 1:m,
  total += (sum(theta' .* X(i,:)) - y(i)) ^ 2;
endfor
J = (1/(2*m)) * total + (lambda / (2 * m)) * sum(theta(2:end) .^ 2);

grad = zeros(size(theta));

total = 0;
for i = 1:m;
  h = sum(theta' .* X(i,:));
  total += (h - y(i)) * X(i, 1);
endfor
grad(1) = 1 / m * total;

for j = 2:size(theta);
  total = 0;
  for i = 1:m;
    h = sum(theta' .* X(i,:));
    total += (h - y(i)) * X(i, j);
  endfor
  grad(j) = 1 / m * total;
  grad(j) += (lambda / m) * theta(j);
endfor

grad = grad(:);

end