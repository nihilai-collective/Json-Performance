
----
### Apache Builds Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1978.18 | 0.06737 | 5343.07ms | 94653 | 80 | 75606.7 | 45631.9 | 0.129875 | 2.60469 | 12.3298 | 2.42524 | 0.00670753 | 6.07482e-06 | 2.24504e-06 | 1(Win) | true |
| simdjson (ondemand) | 1597.72 | 0.0154992 | 6393.06ms | 94653 | 4890 | 374970 | 56498.1 | 0.18563 | 3.20382 | 13.2188 | 2.51031 | 0.00919351 | 9.74607e-06 | 5.37103e-06 | 2(Loss) | true |
