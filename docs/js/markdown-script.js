window.onload = function(){
jQuery.get("https://rawgit.com/jschmidtnj/MobileWeatherStation/master/FinalReport/README.md", function(data) {
    var text = data,
        target = document.getElementById('markdown'),
        converter = new showdown.Converter(),
        html = converter.makeHtml(text);

      target.innerHTML = html;
});
