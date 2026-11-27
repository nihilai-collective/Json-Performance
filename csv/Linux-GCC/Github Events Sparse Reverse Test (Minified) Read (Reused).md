
----
### Github Events Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6388.56 | 0.107375 | 1549.38ms | 53331 | 30 | 2192.21 | 7961.17 | 0.0284796 | 0.81068 | 3.9835 | 0.655379 | 0.00168757 | 1.12505e-05 | 5.00022e-06 | 1(Win) | true |
| simdjson (ondemand) | 4245.29 | 0.0265679 | 1951.76ms | 53331 | 2560 | 25935.7 | 11980.4 | 0.235006 | 1.21159 | 5.70769 | 0.922147 | 0.00232495 | 4.84884e-06 | 9.96137e-07 | 2(Loss) | true |
