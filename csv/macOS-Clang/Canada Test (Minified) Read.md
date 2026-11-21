
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 721.854 | 0.386541 | 9465.31ms | 2251027 | 160 | 2.11434e+10 | 2.97393e+06 | 1.75474 | 1(Win) | true |
| Jsonifier (two-stage) | 658.116 | 0.0649756 | 5083.86ms | 2251027 | 30 | 1.34765e+08 | 3.26196e+06 | 0.073399 | 2(Loss) | true |
| Glaze | 544.359 | 1.37285 | 5910.21ms | 2251027 | 30 | 8.7935e+10 | 3.94363e+06 | 3.26639 | 3(Loss) | true |
| simdjson (ondemand) | 508.78 | 0.867354 | 6250.19ms | 2251027 | 80 | 1.07148e+11 | 4.2194e+06 | 0.119554 | 4(Loss) | true |
