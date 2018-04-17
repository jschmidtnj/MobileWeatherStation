use WeatherStationData;
select windSpeed,humidity,temp_1,temp_2,avg_temp,altitude,pressure
into outfile '/tmp/data.csv'
fields terminated by ','
enclosed by '"'
lines terminated by '\n';
exit
