
----
### Instruments Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6779.17 | 0.0396671 | 3309.2ms | 183677 | 1280 | 134471 | 25839.2 | 0.0338337 | 0.758742 | 3.90268 | 0.507816 | 0.000672823 | 2.29258e-06 | 9.9104e-07 | 1(Win) | true |
| simdjson (ondemand) | 6551.83 | 0.0637149 | 3408.6ms | 183677 | 160 | 46428.8 | 26735.8 | 0.00278193 | 0.786796 | 4.08647 | 0.479216 | 0.00095572 | 5.34226e-06 | 4.32144e-06 | 2(Loss) | true |
