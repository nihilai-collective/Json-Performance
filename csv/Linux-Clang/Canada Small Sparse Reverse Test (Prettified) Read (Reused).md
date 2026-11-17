
----
### Canada Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10408.6 | 0.0389028 | 820.159ms | 11579 | 320 | 54.509 | 1060.91 | 0.147356 | 0.516044 | 2.69661 | 0.342171 | 0.000309828 | 4.58805e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 8500.76 | 0.137807 | 847.521ms | 11579 | 80 | 256.367 | 1299.01 | 0.025988 | 0.624612 | 2.94723 | 0.359098 | 0.00025909 | 6.47724e-06 | 0 | 2(Loss) | true |
