
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3002.74 | 0.0700616 | 3435.67ms | 108313 | 4890 | 2.84051e+06 | 34400.4 | 0.462701 | 0.823868 | 1(Win) | true |
| Jsonifier (two-stage) | 2392.29 | 0.101757 | 4281.72ms | 108313 | 2560 | 4.94196e+06 | 43178.4 | 0.545565 | 1.03427 | 2(Loss) | true |
| Glaze | 1700.64 | 0.193198 | 6197.12ms | 108313 | 160 | 2.20324e+06 | 60739.2 | 0.277068 | 1.45518 | 3(Loss) | true |
| simdjson (reflection) | 1575.61 | 0.0876753 | 6558.62ms | 108313 | 2560 | 8.45781e+06 | 65558.9 | 0.34158 | 1.57071 | 4(Loss) | true |
| simdjson (ondemand) | 1064.57 | 0.279582 | 5035.27ms | 108313 | 640 | 4.7099e+07 | 97030 | 0.557991 | 2.32501 | 5(Loss) | true |
