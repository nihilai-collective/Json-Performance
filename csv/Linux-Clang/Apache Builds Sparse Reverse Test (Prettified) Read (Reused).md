
----
### Apache Builds Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2839.38 | 0.0913944 | 5439.43ms | 124597 | 40 | 58515.1 | 41848.9 | 0.000577471 | 1.81517 | 8.97755 | 1.64264 | 0.00502721 | 4.61488e-06 | 1.60518e-06 | 1(Win) | true |
| simdjson (ondemand) | 2467.4 | 0.0741283 | 6006.87ms | 124597 | 320 | 407807 | 48158 | 0.0522096 | 2.07945 | 8.90509 | 1.49596 | 0.00540194 | 2.93446e-06 | 7.77507e-07 | 2(Loss) | true |
