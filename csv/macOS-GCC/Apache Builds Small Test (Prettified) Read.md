
----
### Apache Builds Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1666.61 | 0.32246 | 196.171ms | 3370 | 2560 | 98988.9 | 1928.4 | 0.577439 | 1(Win) | true |
| Jsonifier | 1637.06 | 0.609324 | 212.629ms | 3370 | 320 | 45790.5 | 1963.2 | 0.327065 | 2(Loss) | true |
| Glaze | 1473.72 | 1.02605 | 226.511ms | 3370 | 320 | 160222 | 2180.8 | 1.16026 | 3(Loss) | true |
| simdjson (reflection) | 1290.3 | 0.91287 | 247.446ms | 3370 | 640 | 330884 | 2490.8 | 0.176963 | 4(Loss) | true |
| simdjson (ondemand) | 1109.03 | 0.203927 | 293.553ms | 3370 | 4890 | 170779 | 2897.93 | 0.418183 | 5(Loss) | true |
