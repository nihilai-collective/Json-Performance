
----
### Marine IK Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2551.6 | 0.0450433 | 885.571ms | 4604 | 4890 | 2937.74 | 1720.77 | 0.132805 | 2.06703 | 9.16182 | 1.6503 | 0.00108774 | 2.03877e-05 | 1.33253e-06 | 1(Win) | true |
| simdjson (ondemand) | 1853.02 | 0.0370106 | 953.518ms | 4604 | 4890 | 3760.72 | 2369.49 | 0.108392 | 2.82461 | 13.2867 | 2.35426 | 0.00132183 | 1.97214e-05 | 2.13205e-06 | 2(Loss) | true |
