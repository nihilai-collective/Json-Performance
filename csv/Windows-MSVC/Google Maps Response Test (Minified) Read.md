
----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1373.76 | 0.138083 | 866.356ms | 11812 | 40 | 5128.21 | 8200 | 0.243309 | 1.79641 | 1(Win) | true |
| Jsonifier (two-stage) | 1136.42 | 0.154048 | 1066.9ms | 11812 | 40 | 9326.92 | 9912.5 | 0.025227 | 2.17264 | 2(Loss) | true |
| Glaze | 824.281 | 0.17408 | 1369.98ms | 11812 | 2560 | 1.44888e+06 | 13666.2 | 0.0100051 | 2.99688 | 3(Loss) | true |
| simdjson (ondemand) | 621.106 | 0.15067 | 1930.02ms | 11812 | 30 | 22402.3 | 18136.7 | 0.0183756 | 3.98012 | 4(Loss) | true |
