function [J, grad] = costFunction(theta, X, y)
%COSTFUNCTION Compute cost and gradient for logistic regression
%   J = COSTFUNCTION(theta, X, y) computes the cost of using theta as the
%   parameter for logistic regression and the gradient of the cost
%   w.r.t. to the parameters.

% Initialize some useful values
m = length(y); % number of training examples
n = length(size(X,2));
% You need to return the following variables correctly
total = 0;

for i = 1:m;
  h = sigmoid(sum(theta' .* X(i,:)));
  total += -y(i) * log(h) - (1 - y(i)) * log(1 - h);
endfor

J = 1 / m * total;

grad = zeros(size(theta));

for j = 1:size(theta);
  total = 0;
  for i = 1:m;
    h = sigmoid(sum(theta' .* X(i,:)));
    total += (h - y(i)) * X(i, j);
  endfor
  grad(j) = 1 / m * total;
endfor
% ====================== YOUR CODE HERE ======================
% Instructions: Compute the cost of a particular choice of theta.
%               You should set J to the cost.
%               Compute the partial derivatives and set grad to the partial
%               derivatives of the cost w.r.t. each parameter in theta
%
% Note: grad should have the same dimensions as theta
%
% =============================================================

end
