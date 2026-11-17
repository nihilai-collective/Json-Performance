
----
### Marine IK Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8290.52 | 0.0385946 | 937.404ms | 18245 | 4890 | 3208.38 | 2098.76 | 0.0295936 | 0.632879 | 3.28622 | 0.45618 | 0.000169786 | 1.03342e-05 | 9.52722e-07 | 1(Win) | true |
| simdjson (ondemand) | 6371.14 | 0.106443 | 993.901ms | 18245 | 640 | 5408.4 | 2731.03 | 0.151615 | 0.819898 | 4.25475 | 0.629543 | 0.000341532 | 4.71019e-06 | 8.56399e-07 | 2(Loss) | true |
