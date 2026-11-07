
----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2354.17 | 0.164169 | 72.636ms | 1691 | 40 | 50.5891 | 685.025 | 0.388978 | 1.01271 | 1(Win) | true |
| Jsonifier (two-stage) | 2185.67 | 0.208763 | 77.1289ms | 1691 | 30 | 71.1782 | 737.833 | 0.099489 | 1.09164 | 2(Loss) | true |
| Glaze | 1974.21 | 0.20474 | 85.7446ms | 1691 | 30 | 83.9126 | 816.867 | 0.368611 | 1.21206 | 3(Loss) | true |
| simdjson (ondemand) | 1368.04 | 0.340012 | 121.522ms | 1691 | 1280 | 20563.2 | 1178.82 | 0.0231906 | 1.76603 | 4(Loss) | true |
