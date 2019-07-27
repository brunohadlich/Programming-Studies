function [J, grad] = costFunctionReg(theta, X, y, lambda)
%COSTFUNCTIONREG Compute cost and gradient for logistic regression with regularization
%   J = COSTFUNCTIONREG(theta, X, y, lambda) computes the cost of using
%   theta as the parameter for regularized logistic regression and the
%   gradient of the cost w.r.t. to the parameters. 

% Initialize some useful values
m = length(y); % number of training examples
n = length(size(X,2));
% You need to return the following variables correctly
total = 0;

for i = 1:m;
  h = sigmoid(sum(theta' .* X(i,:)));
  total += -y(i) * log(h) - (1 - y(i)) * log(1 - h);
  total += (lambda / (2 * m)) * sum(theta(2:length(theta), :) .^ 2);
endfor

J = 1 / m * total;

grad = zeros(size(theta));

total = 0;
for i = 1:m;
  h = sigmoid(sum(theta' .* X(i,:)));
  total += (h - y(i)) * X(i, 1);
endfor
grad(1) = 1 / m * total;

for j = 2:size(theta);
  total = 0;
  for i = 1:m;
    h = sigmoid(sum(theta' .* X(i,:)));
    total += (h - y(i)) * X(i, j);
  endfor
  grad(j) = 1 / m * total;
  grad(j) += (lambda / m) * theta(j);
endfor

% ====================== YOUR CODE HERE ======================
% Instructions: Compute the cost of a particular choice of theta.
%               You should set J to the cost.
%               Compute the partial derivatives and set grad to the partial
%               derivatives of the cost w.r.t. each parameter in theta
% =============================================================

end
