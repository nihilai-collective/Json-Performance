
----
### Github Events Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5381.09 | 0.158347 | 749.666ms | 1691 | 320 | 72.0639 | 299.691 | 0.00104275 | 1.0872 | 4.06682 | 0.633944 | 0.000591366 | 1.66322e-05 | 9.24009e-06 | 1(Win) | true |
| simdjson (ondemand) | 4466.82 | 0.188648 | 751.549ms | 1691 | 160 | 74.2191 | 361.031 | 0.025974 | 1.28313 | 4.77055 | 0.642224 | 0.000591366 | 1.10881e-05 | 0 | 2(Loss) | true |
