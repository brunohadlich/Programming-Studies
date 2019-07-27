function H = hypothesis(X, theta)
  H = sum(theta' .* X);
endfunction