
----
### Instruments Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3167.55 | 0.129077 | 854.712ms | 4669 | 40 | 131.692 | 1405.72 | 0.145029 | 1.67183 | 7.48147 | 1.32255 | 0.00146177 | 1.07089e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2597.07 | 0.0525993 | 883.283ms | 4669 | 4890 | 3976.93 | 1714.51 | 0.469413 | 2.03028 | 9.47719 | 1.55151 | 0.0028399 | 1.78701e-05 | 3.41635e-06 | 2(Loss) | true |
