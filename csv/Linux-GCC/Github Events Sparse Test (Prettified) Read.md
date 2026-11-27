
----
### Github Events Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9038.17 | 0.026186 | 1421.07ms | 65103 | 4890 | 15823 | 6869.43 | 0.00853674 | 0.566963 | 2.66803 | 0.335008 | 0.000545645 | 6.02789e-06 | 2.86788e-06 | 1(Win) | true |
| simdjson (ondemand) | 7533.66 | 0.0266854 | 1557.65ms | 65103 | 2560 | 12381.6 | 8241.29 | 0.744965 | 0.682126 | 3.04874 | 0.356451 | 0.000727015 | 3.79207e-06 | 1.14002e-06 | 2(Loss) | true |
