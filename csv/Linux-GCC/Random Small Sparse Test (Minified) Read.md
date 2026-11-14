
----
### Random Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2520.74 | 0.0421366 | 903.427ms | 4926 | 4890 | 3015.51 | 1863.66 | 0.0605877 | 2.08478 | 9.33151 | 1.60495 | 0.00136312 | 2.28328e-05 | 2.98902e-06 | 1(Win) | true |
| simdjson (ondemand) | 2085.2 | 0.0694 | 940.8ms | 4926 | 2560 | 6258.23 | 2252.92 | 0.0628224 | 2.51291 | 9.98153 | 1.63865 | 0.00252304 | 4.29006e-05 | 1.98247e-05 | 2(Loss) | true |
