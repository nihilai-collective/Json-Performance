
----
### Canada Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8542.65 | 0.12587 | 7598.02ms | 5212421 | 40 | 2.14586e+07 | 581898 | 0.441553 | 0.592014 | 2.53319 | 0.311547 | 0.00199956 | 0.0590664 | 2.87295e-06 | 1(Win) | true |
| simdjson (ondemand) | 7971.38 | 0.0917325 | 8078.02ms | 5212421 | 80 | 2.61788e+07 | 623600 | 0.0347078 | 0.637322 | 2.77436 | 0.331073 | 0.00216674 | 0.0591834 | 1.29762e-05 | 2(Loss) | true |
