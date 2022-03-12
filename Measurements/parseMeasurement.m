close
clear

%Variables
above = 0;
below = 0;

%load file, remove text in first row
filename = uigetfile();
data = csvread(filename);
data = data(2:end);

%Get Min, Max, Mean
Minimum = min(data)
Maximum = max(data)
Mean = mean(data)

%Let user pick upper and lower bounds
hist(data, 1000);
upper = input("Pick upper bound: ")
lower = input("Pick lower bound: ")

%Values that are out of bounds will be set to boundary value
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

%Get data for histogram with 10us bins
bins = lower:10:upper;
plots = lower+5:10:upper+5;
dist = histc(data, bins);

%Plot resulting histogram
bar(plots, dist);
grid on;
grid minor;
title(filename);
axis([lower, upper+10]);
title(sprintf("Filename: %s\nMax: %dus; Min: %dus; Mean: %dus; Above %d us: %d; Below %d us: %d\n", filename, Maximum, Minimum, Mean, upper, above, lower, below));
