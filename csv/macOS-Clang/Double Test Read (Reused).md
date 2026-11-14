
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 322.322 | 0.669031 | 559.854ms | 1811 | 320 | 411245 | 5358.32 | 0.710221 | 1(Win) | true |
| simdjson (ondemand) | 186.402 | 0.330891 | 958.219ms | 1811 | 2560 | 2.40627e+06 | 9265.46 | 2.6853 | 2(Loss) | true |
