
----
### Canada Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8656.81 | 0.0362155 | 7413.01ms | 5212421 | 640 | 2.76778e+07 | 574224 | 0.072266 | 0.591945 | 2.53319 | 0.311547 | 0.00196048 | 0.0590592 | 8.48334e-06 | 1(Win) | true |
| simdjson (ondemand) | 8025.21 | 0.118615 | 7978.33ms | 5212421 | 320 | 1.72741e+08 | 619417 | 0.132956 | 0.637391 | 2.77436 | 0.331072 | 0.00214824 | 0.0590751 | 8.12482e-06 | 2(Loss) | true |
