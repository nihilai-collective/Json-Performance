
----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1844.55 | 0.0284068 | 262.859ms | 4630 | 160 | 73.9858 | 2393.82 | 0.0524514 | 1.32727 | 1(Win) | true |
| Glaze | 1412.26 | 0.260732 | 316.475ms | 4630 | 2560 | 170123 | 3126.56 | 0.166178 | 1.73716 | 2(Loss) | true |
| simdjson (reflection) | 929.211 | 0.233933 | 480.412ms | 4630 | 1280 | 158171 | 4751.9 | 0.461247 | 2.64963 | 3(Loss) | true |
