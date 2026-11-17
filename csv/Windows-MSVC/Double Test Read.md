
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 793.463 | 0.360828 | 222.063ms | 1811 | 30 | 1850.57 | 2176.67 | 0.152905 | 3.77504 | 1(Win) | true |
| Jsonifier (two-stage) | 541.943 | 0.175271 | 336.701ms | 1811 | 320 | 9983.93 | 3186.88 | 0.472906 | 5.57065 | 2(Loss) | true |
| Glaze | 502.57 | 0.186348 | 350.89ms | 1811 | 4890 | 200540 | 3436.54 | 0.0425783 | 6.01225 | 3(Loss) | true |
| simdjson (ondemand) | 259.544 | 0.0650676 | 686.169ms | 1811 | 160 | 2999.61 | 6654.38 | 0.00939144 | 11.672 | 4(Loss) | true |
