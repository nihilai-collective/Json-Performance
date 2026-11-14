
----
### Random Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2017.97 | 0.0347268 | 961.705ms | 4926 | 4890 | 3195.95 | 2327.99 | 0.0642496 | 2.59715 | 11.4367 | 2.14819 | 0.00459869 | 3.25056e-05 | 2.57388e-06 | 1(Win) | true |
| simdjson (ondemand) | 1660.59 | 0.0493476 | 1008.9ms | 4926 | 2560 | 4989.3 | 2829 | 0.106946 | 3.14573 | 13.9968 | 2.2974 | 0.00537684 | 2.41861e-05 | 2.14106e-06 | 2(Loss) | true |
