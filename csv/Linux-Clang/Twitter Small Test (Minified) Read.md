
----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2228.66 | 0.275066 | 126.249ms | 2889 | 4890 | 56544.4 | 1236.24 | 0.000701543 | 1.08738 | 1(Win) | true |
| Jsonifier (two-stage) | 2200.63 | 0.0859072 | 128.963ms | 2889 | 80 | 92.5441 | 1251.99 | 0.00698938 | 1.10131 | 2(Loss) | true |
| Glaze | 2122.08 | 0.101022 | 135.065ms | 2889 | 30 | 51.6092 | 1298.33 | 0.0256805 | 1.14236 | 3(Loss) | true |
| simdjson (ondemand) | 1058.03 | 0.0301607 | 265.244ms | 2889 | 160 | 98.6962 | 2604.04 | 0.0386269 | 2.31696 | 4(Loss) | true |
