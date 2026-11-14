
----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4635.13 | 0.0466942 | 200.883ms | 9578 | 30 | 25.4023 | 1970.67 | 0.0169176 | 0.526968 | 1(Win) | true |
| simdjson (stage-1) | 3209.52 | 0.070779 | 286.347ms | 9578 | 40 | 162.308 | 2846 | 0.0444871 | 0.764267 | 2(Loss) | true |
