
----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1083.71 | 1.83103 | 6006.26ms | 4197495 | 40 | 1.82982e+11 | 3.69384e+06 | 2.61981 | 1(Win) | true |
| simdjson (ondemand) | 625.457 | 0.701723 | 9458.13ms | 4197495 | 40 | 8.06819e+10 | 6.40019e+06 | 2.03989 | 2(Loss) | true |
