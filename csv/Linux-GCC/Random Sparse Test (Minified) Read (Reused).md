
----
### Random Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2825.81 | 0.0438085 | 8436.53ms | 409725 | 640 | 2.34854e+06 | 138277 | 0.17344 | 1.80745 | 9.16442 | 1.55542 | 0.00396833 | 3.25218e-05 | 2.12719e-05 | 1(Win) | true |
| simdjson (ondemand) | 2156.37 | 0.0307111 | 5305.4ms | 409725 | 1280 | 3.96406e+06 | 181205 | 0.0775174 | 2.36397 | 9.8274 | 1.60997 | 0.00704765 | 4.5751e-05 | 1.40433e-05 | 2(Loss) | true |
