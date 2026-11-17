
----
### Discord Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4615.37 | 0.0933039 | 822.347ms | 4857 | 1280 | 1122.36 | 1003.6 | 0.0759186 | 1.15933 | 4.96026 | 0.725345 | 0.000619113 | 1.02944e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4178.73 | 0.0389056 | 831.636ms | 4857 | 1280 | 238.057 | 1108.47 | 0.0307903 | 1.27811 | 5.43422 | 0.714639 | 0.000534988 | 1.84978e-05 | 3.86041e-06 | 2(Loss) | true |
