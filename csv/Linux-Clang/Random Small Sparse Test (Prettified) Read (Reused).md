
----
### Random Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4011.62 | 0.0366498 | 923.779ms | 8150 | 2560 | 1290.8 | 1937.48 | 0.0947478 | 1.31033 | 5.66429 | 0.953129 | 0.00169613 | 1.8309e-05 | 1.38995e-06 | 1(Win) | true |
| simdjson (ondemand) | 3720.3 | 0.0989175 | 938.477ms | 8150 | 40 | 170.831 | 2089.2 | 0.0335169 | 1.41168 | 6.21043 | 0.89362 | 0.00111963 | 6.13497e-06 | 3.06748e-06 | 2(Loss) | true |
