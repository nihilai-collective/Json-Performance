
----
### Canada Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 11760.4 | 0.0530607 | 809.949ms | 11579 | 1280 | 317.725 | 938.961 | 0.007155 | 0.458198 | 2.07531 | 0.222385 | 0.000172794 | 1.65979e-05 | 7.2869e-06 | 1(Win) | true |
| simdjson (ondemand) | 11205.8 | 0.0414877 | 813.286ms | 11579 | 1280 | 213.948 | 985.438 | 0.128347 | 0.479205 | 2.35418 | 0.228344 | 0.000174886 | 1.55184e-05 | 6.67966e-06 | 2(Loss) | true |
