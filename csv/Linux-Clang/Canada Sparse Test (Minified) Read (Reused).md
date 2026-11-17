
----
### Canada Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8060.23 | 0.108494 | 6641.62ms | 2090234 | 80 | 5.75965e+06 | 247313 | 0.214515 | 0.632335 | 3.25146 | 0.398855 | 0.00258444 | 0.0508269 | 3.06186e-06 | 1(Win) | true |
| simdjson (ondemand) | 7062.8 | 0.0943638 | 7457.22ms | 2090234 | 160 | 1.13492e+07 | 282240 | 0.0134655 | 0.717482 | 3.65776 | 0.418387 | 0.00262242 | 0.0498835 | 9.68791e-07 | 2(Loss) | true |
