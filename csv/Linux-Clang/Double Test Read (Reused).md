
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1496.3 | 0.0884908 | 118.581ms | 1811 | 40 | 41.7308 | 1154.25 | 0.0187677 | 1.61897 | 1(Win) | true |
| Glaze | 927.304 | 0.0494339 | 188.476ms | 1811 | 30 | 25.431 | 1862.5 | 0.103695 | 2.63481 | 2(Loss) | true |
| Jsonifier (two-stage) | 519.257 | 0.319299 | 338.894ms | 1811 | 640 | 72185.2 | 3326.11 | 0.111365 | 4.73027 | 3(Loss) | true |
| simdjson (ondemand) | 317.417 | 0.101779 | 546.601ms | 1811 | 4890 | 149970 | 5441.13 | 0.00534948 | 7.76232 | 4(Loss) | true |
