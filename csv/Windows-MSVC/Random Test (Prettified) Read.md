
----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1268.03 | 0.308078 | 7100.7ms | 728486 | 320 | 9.11704e+08 | 547888 | 0.124471 | 2.3965 | 1(Win) | true |
| Jsonifier (two-stage) | 1083.93 | 0.369561 | 8352.03ms | 728486 | 640 | 3.59081e+09 | 640943 | 0.015263 | 2.80351 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 882.99 | 1.23896 | 9230.83ms | 728486 | 160 | 1.52042e+10 | 786802 | 0.409711 | 3.44133 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 874.674 | 0.166209 | 5035.91ms | 728486 | 320 | 5.57711e+08 | 794282 | 0.222269 | 3.47444 | 3(Tie) | true |
