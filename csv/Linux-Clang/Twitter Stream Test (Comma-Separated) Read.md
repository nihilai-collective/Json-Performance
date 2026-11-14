
----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1820.37 | 0.123255 | 7643.25ms | 4219119 | 30 | 2.22667e+08 | 2.21036e+06 | 0.0390376 | 1.36003 | 1(Win) | true |
| simdjson (ondemand) | 1766.35 | 0.164274 | 8199.82ms | 4219119 | 30 | 4.20094e+08 | 2.27795e+06 | 1.26608 | 1.40163 | 2(Loss) | true |
