
----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 977.523 | 0.169292 | 8226.87ms | 4506446 | 30 | 1.66191e+09 | 4.3965e+06 | 1.9887 | 1(Win) | true |
| simdjson (ondemand) | 548.557 | 1.00166 | 6057.58ms | 4506446 | 30 | 1.84753e+11 | 7.83452e+06 | 1.72739 | 2(Loss) | true |
