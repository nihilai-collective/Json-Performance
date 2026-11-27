
----
### Instruments Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1742.46 | 0.0969894 | 7363.56ms | 4197495 | 160 | 7.94372e+08 | 2.29735e+06 | 0.0536922 | 1.42084 | 1(Win) | true |
| simdjson (ondemand) | 1275.32 | 0.135964 | 10171ms | 4197495 | 40 | 7.28526e+08 | 3.13884e+06 | 0.0994188 | 1.94128 | 2(Loss) | true |
