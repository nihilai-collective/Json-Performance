
----
### Google Maps Response Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1833.24 | 0.0383026 | 1349.66ms | 11812 | 2560 | 14181 | 6144.76 | 0.107839 | 2.82315 | 13.4944 | 2.54055 | 0.00684073 | 2.49349e-05 | 1.16738e-05 | 1(Win) | true |
| simdjson (ondemand) | 1691.92 | 0.0305359 | 1397.21ms | 11812 | 2560 | 10581.5 | 6658 | 0.0197875 | 3.06015 | 13.7635 | 2.38283 | 0.0072514 | 1.61382e-05 | 1.25667e-06 | 2(Loss) | true |
