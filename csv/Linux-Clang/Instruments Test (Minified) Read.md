
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2703.81 | 0.0567568 | 3866.1ms | 108313 | 4890 | 2.29908e+06 | 38203.6 | 0.222114 | 0.915058 | 1(Win) | true |
| Jsonifier (two-stage) | 2357.18 | 0.347261 | 4385.59ms | 108313 | 160 | 3.70517e+06 | 43821.5 | 0.0651217 | 1.04969 | 2(Loss) | true |
| Glaze | 1721.67 | 0.398871 | 6007.42ms | 108313 | 80 | 4.58161e+06 | 59997.2 | 0.0163784 | 1.43741 | 3(Loss) | true |
| simdjson (ondemand) | 654.021 | 0.230755 | 8216.58ms | 108313 | 30 | 3.98477e+06 | 157939 | 0.0587645 | 3.78496 | 4(Loss) | true |
