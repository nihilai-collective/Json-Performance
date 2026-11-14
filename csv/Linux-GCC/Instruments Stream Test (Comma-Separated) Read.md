
----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1616.42 | 0.160929 | 7954.58ms | 4197495 | 160 | 2.54133e+09 | 2.47649e+06 | 0.831354 | 1.53165 | 1(Win) | true |
| simdjson (ondemand) | 1275.76 | 0.753424 | 9997.86ms | 4197495 | 160 | 8.9421e+10 | 3.13776e+06 | 0.0425978 | 1.94062 | 2(Loss) | true |
