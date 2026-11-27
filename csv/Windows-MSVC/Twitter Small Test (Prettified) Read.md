
----
### Twitter Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1897.75 | 0.100839 | 197.129ms | 3808 | 2560 | 9532.71 | 1913.63 | 0.148791 | 1.58629 | 1(Win) | true |
| simdjson (ondemand) | 1841.55 | 0.210234 | 205.834ms | 3808 | 640 | 11000.6 | 1972.03 | 0.825083 | 1.63725 | 2(Loss) | true |
| Glaze | 1807.78 | 0.11425 | 204.698ms | 3808 | 2560 | 13485.2 | 2008.87 | 0.337535 | 1.66665 | 3(Loss) | true |
| Jsonifier (two-stage) | 1743.16 | 0.332182 | 212.727ms | 3808 | 30 | 1436.78 | 2083.33 | 0.318979 | 1.71509 | 4(Loss) | true |
