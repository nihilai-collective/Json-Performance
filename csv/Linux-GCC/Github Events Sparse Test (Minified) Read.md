
----
### Github Events Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8778.52 | 0.0422905 | 1310.86ms | 53331 | 2560 | 15368.9 | 5793.73 | 0.090184 | 0.586965 | 2.7349 | 0.380248 | 0.000613628 | 4.86349e-06 | 1.45026e-06 | 1(Win) | true |
| simdjson (ondemand) | 6678.67 | 0.0387832 | 1500.43ms | 53331 | 640 | 5582.74 | 7615.35 | 0.0618788 | 0.775097 | 3.396 | 0.4212 | 0.000866757 | 3.98455e-06 | 1.14263e-06 | 2(Loss) | true |
