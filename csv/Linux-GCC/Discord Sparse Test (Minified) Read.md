
----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2476.62 | 0.0477579 | 2894.95ms | 56369 | 640 | 68775.3 | 21706.1 | 0.0309797 | 2.07481 | 9.7062 | 1.70636 | 0.00376359 | 4.98944e-06 | 1.41368e-06 | 1(Win) | true |
| simdjson (ondemand) | 2167.67 | 0.0895842 | 3204.78ms | 56369 | 80 | 39486.3 | 24799.7 | 0.0169328 | 2.37796 | 10.1608 | 1.6973 | 0.00454195 | 5.54383e-06 | 1.33052e-06 | 2(Loss) | true |
