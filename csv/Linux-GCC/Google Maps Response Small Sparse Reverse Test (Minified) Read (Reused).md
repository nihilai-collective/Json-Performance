
----
### Google Maps Response Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1962.27 | 0.274455 | 937.603ms | 4390 | 30 | 1028.67 | 2133.57 | 0.0828721 | 2.62657 | 12.7706 | 2.38838 | 0.00331055 | 3.79651e-05 | 1.5186e-05 | 1(Win) | true |
| simdjson (ondemand) | 1709.59 | 0.0501632 | 974.854ms | 4390 | 320 | 482.911 | 2448.92 | 0.00497644 | 3.0628 | 13.5421 | 2.3262 | 0.00460706 | 4.98292e-06 | 7.11845e-07 | 2(Loss) | true |
