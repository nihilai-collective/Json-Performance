
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1064.38 | 0.294236 | 8479.15ms | 728486 | 30 | 1.10652e+08 | 652717 | 0.0954072 | 2.32597 | 1(Win) | true |
| Jsonifier | 1034.21 | 0.347105 | 8608.99ms | 728486 | 160 | 8.699e+08 | 671759 | 0.99346 | 2.39379 | 2(Loss) | true |
| Glaze | 963.011 | 0.1247 | 9328.22ms | 728486 | 160 | 1.29488e+08 | 721423 | 1.15122 | 2.57073 | 3(Loss) | true |
| simdjson (ondemand) | 787.439 | 0.153618 | 5612.97ms | 728486 | 320 | 5.87816e+08 | 882276 | 0.231921 | 3.14395 | 4(Loss) | true |
