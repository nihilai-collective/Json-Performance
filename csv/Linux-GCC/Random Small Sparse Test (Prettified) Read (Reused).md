
----
### Random Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3898.86 | 0.0502097 | 925.914ms | 8150 | 2560 | 2564.82 | 1993.52 | 0.235795 | 1.34657 | 5.92282 | 0.921595 | 0.0015221 | 1.53854e-05 | 2.06097e-06 | 1(Win) | true |
| simdjson (ondemand) | 3604.65 | 0.0231072 | 943.251ms | 8150 | 4890 | 1213.93 | 2156.23 | 0.022026 | 1.45577 | 6.14061 | 0.911657 | 0.00113649 | 1.68868e-05 | 1.35496e-06 | 2(Loss) | true |
