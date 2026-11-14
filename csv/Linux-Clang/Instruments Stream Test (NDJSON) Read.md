
----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1711.8 | 0.0754671 | 7564.09ms | 4197496 | 160 | 4.98321e+08 | 2.3385e+06 | 0.244649 | 2.96739 | 15.7559 | 3.07136 | 0.000545551 | 0.0815531 | 0.000298955 | 1(Win) | true |
| simdjson (ondemand) | 1464.42 | 0.0479718 | 8799.42ms | 4197496 | 160 | 2.75132e+08 | 2.73353e+06 | 0.0801344 | 3.46579 | 18.5331 | 2.75321 | 0.00468651 | 0.0806472 | 0.00164808 | 2(Loss) | true |
