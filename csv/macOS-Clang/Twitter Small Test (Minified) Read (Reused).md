
----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2934.36 | 0.412485 | 129.973ms | 2889 | 30 | 449.995 | 938.933 | 0.131182 | 1(Win) | true |
| Jsonifier (two-stage) | 2116.81 | 0.190455 | 163.418ms | 2889 | 80 | 491.591 | 1301.56 | 0.284118 | 2(Loss) | true |
| Glaze | 2064 | 0.380307 | 163.403ms | 2889 | 30 | 773.154 | 1334.87 | 1.02079 | 3(Loss) | true |
| simdjson (ondemand) | 872.499 | 0.157009 | 355.618ms | 2889 | 80 | 1966.55 | 3157.79 | 0.513663 | 4(Loss) | true |
