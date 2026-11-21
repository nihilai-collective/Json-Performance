
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1092.97 | 0.103447 | 8405.14ms | 728486 | 160 | 6.91803e+07 | 635641 | 1.91355 | 2.26508 | 1(Win) | true |
| Jsonifier | 1001.14 | 0.960228 | 8778.18ms | 728486 | 80 | 3.55215e+09 | 693948 | 0.484708 | 2.47258 | 2(Loss) | true |
| Glaze | 925.318 | 0.257673 | 9701.05ms | 728486 | 320 | 1.1977e+09 | 750810 | 0.0515959 | 2.67551 | 3(Loss) | true |
| simdjson (ondemand) | 844.978 | 0.233327 | 5314.14ms | 728486 | 30 | 1.10409e+08 | 822197 | 0.020672 | 2.92998 | 4(Loss) | true |
