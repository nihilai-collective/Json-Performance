
----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5673.6 | 0.186518 | 763ms | 2821 | 160 | 125.156 | 474.181 | 0.265634 | 0.972521 | 3.64977 | 0.493442 | 0.000943814 | 4.65261e-05 | 1.99397e-05 | 1(Win) | true |
| simdjson (ondemand) | 5443.23 | 0.128845 | 769.015ms | 2821 | 80 | 32.443 | 494.25 | 0.192581 | 1.03635 | 3.91989 | 0.432116 | 0.00106345 | 0 | 0 | 2(Loss) | true |
