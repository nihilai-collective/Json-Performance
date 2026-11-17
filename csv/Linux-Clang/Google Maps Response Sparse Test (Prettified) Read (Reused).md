
----
### Google Maps Response Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4185.76 | 0.0768672 | 1311.41ms | 25388 | 320 | 6326.17 | 5784.34 | 0.0231281 | 1.23874 | 5.62372 | 0.938475 | 0.00204612 | 6.76993e-06 | 2.46179e-07 | 1(Win) | true |
| simdjson (ondemand) | 4036.01 | 0.0203631 | 1332.62ms | 25388 | 4890 | 7297.08 | 5998.97 | 0.193552 | 1.28249 | 5.99657 | 0.883449 | 0.00179126 | 6.39563e-06 | 1.07131e-06 | 2(Loss) | true |
