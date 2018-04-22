use WeatherStationData;
select the_time_and_date, windSpeed,humidity,temp_1,temp_2,avg_temp,altitude,pressure from data
into outfile '/tmp/data.csv'
fields terminated by ','
enclosed by '"'
lines terminated by '\n';
exit
