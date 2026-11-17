
----
### Apache Builds Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4091.14 | 0.069958 | 4158.7ms | 124597 | 1280 | 528457 | 29044.4 | 0.123037 | 1.24715 | 6.28651 | 0.987855 | 0.00233342 | 3.04105e-06 | 1.08475e-06 | 1(Win) | true |
| simdjson (ondemand) | 2935.78 | 0.0345845 | 5267.45ms | 124597 | 4890 | 958162 | 40474.7 | 0.104778 | 1.73378 | 6.78006 | 1.1308 | 0.00465579 | 1.35291e-05 | 1.0089e-05 | 2(Loss) | true |
