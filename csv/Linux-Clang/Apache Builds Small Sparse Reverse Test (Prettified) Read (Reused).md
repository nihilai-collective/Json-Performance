
----
### Apache Builds Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3249.22 | 0.0688955 | 818.326ms | 3370 | 320 | 148.605 | 989.125 | 0.17914 | 1.64854 | 7.04303 | 1.22463 | 0.00116469 | 1.57641e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3045.22 | 0.0898377 | 824.141ms | 3370 | 320 | 287.668 | 1055.39 | 0.0088822 | 1.75609 | 7.15282 | 1.11988 | 0.00104507 | 3.43101e-05 | 6.4911e-06 | 2(Loss) | true |
