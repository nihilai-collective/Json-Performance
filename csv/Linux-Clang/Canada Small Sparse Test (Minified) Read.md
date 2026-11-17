
----
### Canada Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7480.43 | 0.0582516 | 772.891ms | 4630 | 4890 | 578.141 | 590.275 | 0.084261 | 0.735803 | 3.63391 | 0.469978 | 0.000432407 | 2.22166e-05 | 7.3761e-06 | 1(Win) | true |
| simdjson (ondemand) | 6612.35 | 0.0572147 | 780.25ms | 4630 | 4890 | 713.797 | 667.767 | 0.0375272 | 0.823917 | 4.10194 | 0.491577 | 0.00043254 | 1.38247e-05 | 9.27533e-07 | 2(Loss) | true |
