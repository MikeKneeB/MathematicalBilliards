function [] = Plotxy( file )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
fdata = importdata(file);

comet(fdata.data(:,2), fdata.data(:,3),0.9);

end

