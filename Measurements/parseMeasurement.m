close
clear

above = 0;
below = 0;

filename = uigetfile(pwd());
data = csvread(filename);
data = data(2:end);
Minimum = min(data)
Maximum = max(data)
Mean = mean(data)

hist(data, 1000);
upper = input("Pick upper bound: ")
lower = input("Pick lower bound: ")

for i = 1:length(data)
  if data(i,1) > upper;
    data(i, 1) = upper;
    above++;
  endif
endfor

for i = 1:length(data)
  if data(i,1) < lower;
    data(i, 1) = lower;
    below++;
  endif
endfor
bins = lower:10:upper;
plots = lower+5:10:upper+5;
dist = histc(data, bins);
bar(plots, dist);
grid on;
grid minor;
title(filename);
axis([lower, upper+10]);
title(sprintf("Filename: %s\nMax: %dus; Min: %dus; Mean: %dus; Above %d us: %d; Below %d us: %d\n", filename, Maximum, Minimum, Mean, upper, above, lower, below));