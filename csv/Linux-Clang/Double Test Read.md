
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 2851.37 | 0.0959827 | 764.707ms | 1811 | 4890 | 1652.82 | 605.71 | 0.415337 | 1.9387 | 9.46107 | 2.46935 | 0.000557714 | 6.54939e-05 | 3.95222e-06 | 1(Win) | true |
| simdjson (stage-1) | 1336.14 | 0.094235 | 835.584ms | 1811 | 2560 | 3798.35 | 1292.6 | 0.00755557 | 3.98322 | 19.6405 | 4.73385 | 0.000855881 | 0.000120358 | 4.72374e-05 | 2(Loss) | true |
