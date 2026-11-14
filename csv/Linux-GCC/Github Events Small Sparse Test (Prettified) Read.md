
----
### Github Events Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5192.54 | 0.117356 | 750.084ms | 2158 | 640 | 138.464 | 396.344 | 0.0740601 | 1.08984 | 4.08434 | 0.569045 | 0.000466288 | 2.67899e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4923.49 | 0.0592116 | 749.738ms | 2158 | 4890 | 299.557 | 418.002 | 0.0166633 | 1.15777 | 4.27572 | 0.574606 | 0.000533043 | 2.00898e-05 | 1.0424e-05 | 2(Loss) | true |
