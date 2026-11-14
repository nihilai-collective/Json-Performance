
----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1054.97 | 0.36119 | 5947.56ms | 4197495 | 30 | 5.63495e+09 | 3.79445e+06 | 0.140049 | 2.88066 | 1(Win) | true |
| simdjson (ondemand) | 790.807 | 0.118194 | 7872.89ms | 4197495 | 80 | 2.86363e+09 | 5.06197e+06 | 0.160056 | 3.84304 | 2(Loss) | true |
