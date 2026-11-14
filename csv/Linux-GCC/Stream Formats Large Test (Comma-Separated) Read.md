
----
### Stream Formats Large Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 18752.7 | 0.0638871 | 5250.32ms | 16197085 | 160 | 4.43091e+07 | 823708 | 0.153256 | 0.269124 | 1.40268 | 0.0683635 | 9.31028e-05 | 0.0157372 | 0.00134383 | 1(Win) | true |
| simdjson (ondemand) | 15351.1 | 0.16763 | 6466.01ms | 16197085 | 320 | 9.10437e+08 | 1.00623e+06 | 0.0293135 | 0.33095 | 1.41968 | 0.0991874 | 9.52451e-05 | 0.0157491 | 0.00163846 | 2(Loss) | true |
