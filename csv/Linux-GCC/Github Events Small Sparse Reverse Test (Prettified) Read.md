
----
### Github Events Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3776.37 | 0.198963 | 766.688ms | 2158 | 160 | 188.113 | 544.975 | 0.0527269 | 1.46552 | 5.80816 | 0.979611 | 0.000535797 | 5.7924e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3237.02 | 0.0743791 | 774.251ms | 2158 | 320 | 71.5588 | 635.778 | 0.025074 | 1.68919 | 6.91149 | 1.14551 | 0.00048801 | 2.31696e-05 | 0 | 2(Loss) | true |
