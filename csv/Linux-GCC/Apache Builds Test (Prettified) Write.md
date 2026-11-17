
----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 23330.1 | 0.0339293 | 1282.28ms | 136037 | 4890 | 17407.6 | 5560.83 | 0.153317 | 0.220463 | 0.868551 | 0.125708 | 2.16409e-05 | 2.04744e-06 | 9.03459e-07 | 1(Win) | true |
| Glaze | 7234.49 | 0.0456133 | 2528.55ms | 136076 | 4890 | 327370 | 17938 | 0.154958 | 0.69785 | 3.79908 | 0.638224 | 7.87137e-05 | 5.71376e-06 | 4.247e-06 | 2(Loss) | true |
| simdjson (reflection) | 621.01 | 0.190225 | 5494.06ms | 136037 | 640 | 1.01073e+08 | 208910 | 0.0564019 | 8.13995 | 34.7252 | 7.11465 | 0.0269298 | 0.00481844 | 0.000294543 | 3(Loss) | true |
