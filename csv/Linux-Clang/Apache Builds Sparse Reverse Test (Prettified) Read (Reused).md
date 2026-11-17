
----
### Apache Builds Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2737.39 | 0.0441208 | 5539.35ms | 124597 | 320 | 117376 | 43408.2 | 0.153663 | 1.84724 | 8.97792 | 1.64285 | 0.00507311 | 6.01941e-06 | 1.58009e-06 | 1(Win) | true |
| simdjson (ondemand) | 2432.81 | 0.0187776 | 6128.84ms | 124597 | 4890 | 411325 | 48842.6 | 0.0960145 | 2.09795 | 8.93627 | 1.50539 | 0.00584346 | 1.8535e-05 | 1.46911e-05 | 2(Loss) | true |
