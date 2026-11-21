
----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6693.18 | 0.103919 | 44.1967ms | 2889 | 80 | 14.6391 | 411.637 | 0.045529 | 0.344237 | 1(Win) | true |
| Jsonifier (two-stage) | 6237.09 | 0.0628049 | 46.8955ms | 2889 | 640 | 49.2604 | 441.739 | 0.123295 | 0.373819 | 2(Loss) | true |
| Jsonifier | 5951 | 0.148565 | 47.3934ms | 2889 | 80 | 37.8475 | 462.975 | 0.216462 | 0.392121 | 3(Loss) | true |
| Glaze | 3440.78 | 0.083028 | 83.7501ms | 2889 | 80 | 35.3606 | 800.737 | 0.1792 | 0.696738 | 4(Loss) | true |
