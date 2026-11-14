
----
### Github Events Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3879.23 | 0.0754105 | 765.022ms | 2158 | 1280 | 204.873 | 530.525 | 0.0800452 | 1.44076 | 5.52178 | 0.926784 | 0.000888047 | 3.22202e-05 | 1.30329e-05 | 1(Win) | true |
| simdjson (ondemand) | 3254.25 | 0.187308 | 774.441ms | 2158 | 160 | 224.508 | 632.413 | 0.0197617 | 1.68394 | 6.75394 | 1.06951 | 0.00168269 | 1.73772e-05 | 1.15848e-05 | 2(Loss) | true |
