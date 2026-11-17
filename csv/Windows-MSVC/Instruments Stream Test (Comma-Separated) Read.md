
----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1153.58 | 0.624224 | 5488.16ms | 4197495 | 30 | 1.40763e+10 | 3.47011e+06 | 0.78193 | 2.14617 | 1(Win) | true |
| simdjson (ondemand) | 784.894 | 1.30989 | 7772.1ms | 4197495 | 80 | 3.57038e+11 | 5.1001e+06 | 2.31899 | 3.15431 | 2(Loss) | true |
