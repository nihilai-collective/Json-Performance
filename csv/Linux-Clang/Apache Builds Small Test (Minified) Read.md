
----
### Apache Builds Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3013.38 | 0.219877 | 85.4641ms | 2632 | 40 | 134.179 | 832.975 | 0.0490451 | 0.7964 | 1(Win) | true |
| Jsonifier (two-stage) | 2481.53 | 0.197568 | 106.214ms | 2632 | 40 | 159.744 | 1011.5 | 0.102054 | 0.972245 | 2(Loss) | true |
| Glaze | 1995.45 | 0.177121 | 128.574ms | 2632 | 30 | 148.921 | 1257.9 | 0.0794344 | 1.21536 | 3(Loss) | true |
| simdjson (ondemand) | 1531.73 | 0.103249 | 168.66ms | 2632 | 80 | 229.018 | 1638.71 | 0.244259 | 1.58992 | 4(Loss) | true |
