
----
### Discord Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5827.2 | 0.0703476 | 832.615ms | 6701 | 4890 | 2910.49 | 1096.68 | 0.0683015 | 0.915423 | 3.99179 | 0.563797 | 0.000427522 | 3.51259e-05 | 1.82191e-05 | 1(Win) | true |
| simdjson (ondemand) | 5400.01 | 0.130091 | 841.315ms | 6701 | 80 | 189.616 | 1183.44 | 0.133963 | 1.00457 | 4.31771 | 0.523653 | 0.000693926 | 2.23847e-05 | 5.59618e-06 | 2(Loss) | true |
