
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3499.97 | 0.0845619 | 829.594ms | 3873 | 2560 | 2038.72 | 1055.32 | 0.0136936 | 1.5063 | 6.92332 | 0.830365 | 0.000266771 | 8.94615e-05 | 4.37726e-05 | 1(Win) | true |
| Glaze | 1906.5 | 0.0783578 | 920.146ms | 3873 | 30 | 69.1368 | 1937.37 | 0.0740384 | 2.70913 | 12.8533 | 1.7906 | 0.000516396 | 5.16396e-05 | 2.58198e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1611.49 | 0.13221 | 957.523ms | 3873 | 30 | 275.482 | 2292.03 | 0.0611185 | 3.19462 | 14.5771 | 1.55797 | 0.00129099 | 3.44264e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 722.346 | 0.0277986 | 1248.85ms | 3873 | 4890 | 9880.04 | 5113.31 | 0.00760074 | 7.04077 | 32.0147 | 3.66357 | 0.00477402 | 7.89906e-05 | 2.99383e-05 | 4(Loss) | true |
