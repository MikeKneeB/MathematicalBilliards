function [  ] = Plota( file )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
fdata = importdata(file);

comet(fdata.data(:,1), fdata.data(:,5),0.9);

end

