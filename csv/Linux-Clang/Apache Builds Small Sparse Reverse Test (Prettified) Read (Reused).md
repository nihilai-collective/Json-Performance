
----
### Apache Builds Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3495.56 | 0.0401979 | 816.207ms | 3370 | 1280 | 174.841 | 919.418 | 0.113479 | 1.53892 | 6.75163 | 1.19347 | 0.000967637 | 1.62277e-05 | 6.95475e-07 | 1(Win) | true |
| simdjson (ondemand) | 3097.39 | 0.0781554 | 827.711ms | 3370 | 2560 | 1683.55 | 1037.61 | 0.130314 | 1.72024 | 7.14985 | 1.1181 | 0.000891946 | 1.44891e-05 | 3.24555e-06 | 2(Loss) | true |
