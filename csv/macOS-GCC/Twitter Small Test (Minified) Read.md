
----
### Twitter Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2389.98 | 0.649036 | 117.76ms | 2889 | 2560 | 143313 | 1152.8 | 0.121591 | 1(Win) | true |
| Glaze | 1945.58 | 0.524299 | 145.068ms | 2889 | 4890 | 269565 | 1416.11 | 0.0151507 | 2(Loss) | true |
| Jsonifier (two-stage) | 1860.59 | 1.35174 | 153.442ms | 2889 | 640 | 256426 | 1480.8 | 0.0539957 | 3(Loss) | true |
| simdjson (reflection) | 1396.43 | 0.403744 | 200.948ms | 2889 | 1280 | 81222.5 | 1973 | 0.19223 | 4(Loss) | true |
| simdjson (ondemand) | 1133.1 | 0.317388 | 247.438ms | 2889 | 4890 | 291239 | 2431.53 | 0.393428 | 5(Loss) | true |
