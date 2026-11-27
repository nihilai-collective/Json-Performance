
----
### Random Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1980.05 | 0.0288308 | 5232.74ms | 409725 | 1280 | 4.14338e+06 | 197340 | 0.0849922 | 2.5626 | 12.1662 | 2.33238 | 0.00891149 | 0.000183185 | 1.31605e-05 | 1(Win) | true |
| simdjson (ondemand) | 1440.1 | 0.0792789 | 7125.28ms | 409725 | 160 | 7.40351e+06 | 271332 | 0.00251082 | 3.547 | 14.7307 | 2.67462 | 0.0133326 | 0.00123758 | 3.3315e-05 | 2(Loss) | true |
