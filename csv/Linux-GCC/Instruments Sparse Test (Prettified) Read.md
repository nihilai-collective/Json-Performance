
----
### Instruments Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6676.04 | 0.0486661 | 3369.64ms | 183677 | 640 | 104353 | 26238.3 | 0.00873084 | 0.764546 | 3.90216 | 0.507685 | 0.000683256 | 1.26751e-06 | 2.04163e-07 | 1(Win) | true |
| simdjson (ondemand) | 6547.62 | 0.0383174 | 3414.67ms | 183677 | 2560 | 269013 | 26752.9 | 0.113457 | 0.778911 | 4.08815 | 0.479957 | 0.000822385 | 2.02461e-06 | 7.99637e-07 | 2(Loss) | true |
