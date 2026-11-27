
----
### Google Maps Response Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2093.25 | 0.126638 | 1180.92ms | 25388 | 30 | 6436.78 | 11566.7 | 0.143885 | 1.18171 | 1(Win) | true |
| Jsonifier (two-stage) | 1991.42 | 0.249934 | 1227.53ms | 25388 | 1280 | 1.18194e+06 | 12158.1 | 0.0719166 | 1.24004 | 2(Loss) | true |
| Glaze | 1394.93 | 0.28957 | 1765.07ms | 25388 | 640 | 1.61673e+06 | 17357 | 0.171645 | 1.77184 | 3(Loss) | true |
| simdjson (ondemand) | 1157.99 | 0.142578 | 2109.37ms | 25388 | 2560 | 2.27507e+06 | 20908.6 | 0.282717 | 2.13501 | 4(Loss) | true |
