function [theta, J_history] = gradientDescentMulti(X, y, theta, alpha, num_iters)
%GRADIENTDESCENTMULTI Performs gradient descent to learn theta
%   theta = GRADIENTDESCENTMULTI(x, y, theta, alpha, num_iters) updates theta by
%   taking num_iters gradient steps with learning rate alpha

% Initialize some useful values
m = size(X, 1); % number of training examples
n = size(X, 2); % number of features
J_history = zeros(num_iters, 1);
temp = zeros(length(theta), 1);

for iter = 1:num_iters
  for f = 1:n,
    total = 0;
    for i = 1:m,
      total = total + (sum(theta' .* X(i,:)) - y(i)) * X(i, f);
    endfor
    temp(f) = theta(f) - alpha * (1 / m) * total;
  endfor
  for f = 1:n,
    theta(f) = temp(f);
  endfor

    % ====================== YOUR CODE HERE ======================
    % Instructions: Perform a single gradient step on the parameter vector
    %               theta. 
    %
    % Hint: While debugging, it can be useful to print out the values
    %       of the cost function (computeCostMulti) and gradient here.
    %
    % ============================================================

    % Save the cost J in every iteration    
    J_history(iter) = computeCostMulti(X, y, theta);

end

end
