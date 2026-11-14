
----
### Canada Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6322 | 0.0419455 | 8244.21ms | 2090234 | 1280 | 2.23904e+07 | 315312 | 0.0911348 | 0.800256 | 4.62939 | 0.716848 | 0.00241851 | 0.0760451 | 1.81686e-06 | 1(Win) | true |
| simdjson (ondemand) | 5581.2 | 0.312233 | 9266.56ms | 2090234 | 320 | 3.97963e+08 | 357164 | 0.204248 | 0.909435 | 5.10588 | 0.738319 | 0.00233985 | 0.0752324 | 6.95197e-07 | 2(Loss) | true |
