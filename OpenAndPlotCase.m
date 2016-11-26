function [] = OpenAndPlotCase(file, col1, col2, com)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

if ~exist('com', 'var')
    com = 0;
end

fdata = importdata(file);

fig = figure;

if com == 1
    fig.Name='YAY';
    comet(fdata.data(:,col1), fdata.data(:,col2))
elseif com == 0
    plot(fdata.data(:,col1),fdata.data(:,col2))
    grid on;
end

end

