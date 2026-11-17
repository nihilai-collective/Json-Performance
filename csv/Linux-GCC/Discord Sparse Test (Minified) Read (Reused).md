
----
### Discord Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3144.04 | 0.0605781 | 2728.9ms | 56369 | 640 | 68661.7 | 17098.3 | 0.0265357 | 1.63587 | 8.12345 | 1.36109 | 0.00256527 | 4.01927e-06 | 4.43506e-07 | 1(Win) | true |
| simdjson (ondemand) | 2677.9 | 0.0246424 | 3022.94ms | 56369 | 2560 | 62646.7 | 20074.6 | 0.0687412 | 1.92395 | 8.62093 | 1.36614 | 0.00279416 | 1.80798e-05 | 1.07827e-05 | 2(Loss) | true |
