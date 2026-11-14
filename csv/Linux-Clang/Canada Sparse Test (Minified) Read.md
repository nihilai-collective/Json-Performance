
----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7826.81 | 0.172449 | 6619.88ms | 2090234 | 30 | 5.7871e+06 | 254689 | 0.0561415 | 0.651958 | 3.25154 | 0.398873 | 0.0031207 | 0.0508947 | 3.42864e-06 | 1(Win) | true |
| simdjson (ondemand) | 7193.17 | 0.0935186 | 7282.55ms | 2090234 | 640 | 4.29858e+07 | 277124 | 0.00684495 | 0.710283 | 3.65784 | 0.418404 | 0.00242698 | 0.0497175 | 3.61802e-07 | 2(Loss) | true |
