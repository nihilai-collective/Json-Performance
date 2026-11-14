
----
### Canada Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8585.2 | 0.0537177 | 6139.73ms | 2090234 | 1280 | 1.99128e+07 | 232190 | 0.0631387 | 0.590893 | 3.18958 | 0.396895 | 0.00240418 | 0.0507874 | 1.43263e-06 | 1(Win) | true |
| simdjson (ondemand) | 7436.94 | 0.0391221 | 7056.14ms | 2090234 | 640 | 7.03762e+06 | 268041 | 0.0437362 | 0.687148 | 3.6662 | 0.418387 | 0.00231068 | 0.0493274 | 1.49505e-06 | 2(Loss) | true |
