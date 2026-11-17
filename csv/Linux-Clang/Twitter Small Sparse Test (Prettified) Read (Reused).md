
----
### Twitter Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6811.55 | 0.0734631 | 777.467ms | 3770 | 2560 | 384.919 | 527.832 | 0.0383942 | 0.809088 | 3.19125 | 0.391777 | 0.000296336 | 1.41951e-05 | 1.96867e-06 | 1(Win) | true |
| simdjson (ondemand) | 6495.65 | 0.043465 | 780.777ms | 3770 | 1280 | 74.0844 | 553.502 | 0.168814 | 0.835913 | 3.2626 | 0.340053 | 0.000870151 | 8.0819e-06 | 6.21684e-07 | 2(Loss) | true |
