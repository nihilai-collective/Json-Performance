
----
### Discord Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4036.92 | 0.0527629 | 2990.25ms | 83958 | 640 | 70090.8 | 19834.1 | 0.0493698 | 1.26935 | 6.10439 | 0.980324 | 0.00197264 | 3.51738e-06 | 9.30525e-07 | 1(Win) | true |
| simdjson (ondemand) | 3421.66 | 0.0255299 | 3363.08ms | 83958 | 4890 | 174525 | 23400.5 | 0.142883 | 1.50032 | 6.34556 | 0.93007 | 0.00442575 | 3.97998e-06 | 8.91477e-07 | 2(Loss) | true |
