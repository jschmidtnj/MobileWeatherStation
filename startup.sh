cd /home/pi/Desktop/MobileWeatherStation
git pull origin master
ip4=$(/sbin/ip -o -4 addr list wlan0 | awk '{print $4}' | cut -d/ -f1)
echo $ip4 >> ip-address.txt
git add -A
git commit -m "added ip-addresses"
git push origin master
python3 testdisplay.py
python3 app.py
