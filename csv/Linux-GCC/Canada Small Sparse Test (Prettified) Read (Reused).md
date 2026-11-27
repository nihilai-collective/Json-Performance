
----
### Canada Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 13151.7 | 0.0512406 | 799.442ms | 11579 | 2560 | 473.858 | 839.634 | 0.088985 | 0.409289 | 2.08135 | 0.220572 | 0.000172828 | 8.87247e-06 | 3.60971e-06 | 1(Win) | true |
| simdjson (ondemand) | 11082.1 | 0.0932453 | 818.341ms | 11579 | 1280 | 1105 | 996.436 | 0.139835 | 0.482933 | 2.43778 | 0.229467 | 0.000172726 | 8.02908e-06 | 3.37356e-07 | 2(Loss) | true |
