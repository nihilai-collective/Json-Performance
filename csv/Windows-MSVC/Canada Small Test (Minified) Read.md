
----
### Canada Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 555.672 | 0.107233 | 809.243ms | 4630 | 80 | 5808.54 | 7946.25 | 0.0785916 | 4.43817 | 1(Win) | true |
| Jsonifier (two-stage) | 516.864 | 0.417172 | 877.221ms | 4630 | 1280 | 1.62574e+06 | 8542.89 | 0.212626 | 4.77329 | 2(Loss) | true |
| simdjson (ondemand) | 172.443 | 0.177854 | 2633.26ms | 4630 | 1280 | 2.65467e+06 | 25605.7 | 0.5729 | 14.3401 | 3(Loss) | true |
| Glaze | 162.215 | 0.128506 | 2758.54ms | 4630 | 2560 | 3.13235e+06 | 27220.2 | 0.0837338 | 15.2454 | 4(Loss) | true |
