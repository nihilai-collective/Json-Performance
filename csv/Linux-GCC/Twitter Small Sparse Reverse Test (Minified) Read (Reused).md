
----
### Twitter Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4058.39 | 0.105027 | 783.134ms | 2821 | 4890 | 2370.32 | 662.903 | 0.15958 | 1.34468 | 5.43424 | 0.859625 | 0.00085098 | 1.70355e-05 | 4.05953e-06 | 1(Win) | true |
| simdjson (ondemand) | 3563.42 | 0.0669197 | 789.697ms | 2821 | 2560 | 653.462 | 754.982 | 0.00905362 | 1.52242 | 6.19213 | 0.900036 | 0.000762556 | 2.10475e-05 | 6.23117e-06 | 2(Loss) | true |
