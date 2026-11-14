
----
### Canada Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5977.38 | 0.0464295 | 8695.75ms | 2090234 | 640 | 1.53439e+07 | 333491 | 0.066141 | 0.847917 | 4.69125 | 0.718804 | 0.00261203 | 0.0762828 | 1.72902e-06 | 1(Win) | true |
| simdjson (ondemand) | 5529.75 | 0.101379 | 9364.9ms | 2090234 | 80 | 1.06848e+07 | 360487 | 0.0986924 | 0.919848 | 5.09747 | 0.738317 | 0.0024026 | 0.0758405 | 1.18408e-06 | 2(Loss) | true |
