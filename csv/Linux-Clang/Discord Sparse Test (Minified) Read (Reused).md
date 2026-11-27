
----
### Discord Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2873.23 | 0.0278954 | 2916.37ms | 56369 | 4890 | 133203 | 18709.8 | 0.207996 | 1.76997 | 8.34012 | 1.4148 | 0.00344246 | 1.78999e-05 | 1.03975e-05 | 1(Win) | true |
| simdjson (ondemand) | 2646 | 0.0630782 | 3072.04ms | 56369 | 40 | 6569.32 | 20316.6 | 0.244031 | 1.91533 | 8.8114 | 1.35119 | 0.00320167 | 7.98311e-06 | 3.99156e-06 | 2(Loss) | true |
