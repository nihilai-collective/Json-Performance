
----
### Github Events Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3395.8 | 0.203542 | 761.344ms | 1691 | 40 | 37.3744 | 474.9 | 0.0210615 | 1.6465 | 6.5139 | 1.13779 | 0.0017741 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2664.73 | 0.0940185 | 777.825ms | 1691 | 4890 | 1583.13 | 605.188 | 0.508461 | 2.05165 | 8.31756 | 1.35423 | 0.00152497 | 3.12009e-05 | 4.95828e-06 | 2(Loss) | true |
