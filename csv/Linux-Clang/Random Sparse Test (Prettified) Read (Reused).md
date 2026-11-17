
----
### Random Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3928.98 | 0.0251759 | 9808.55ms | 676745 | 1280 | 2.18912e+06 | 164265 | 0.180172 | 1.30434 | 5.93439 | 1.00977 | 0.00341981 | 0.000591315 | 3.63181e-06 | 1(Win) | true |
| simdjson (ondemand) | 3380.57 | 0.0909112 | 5585.37ms | 676745 | 160 | 4.81976e+06 | 190913 | 0.097538 | 1.51353 | 6.49019 | 0.956718 | 0.00550282 | 0.00329341 | 3.90657e-06 | 2(Loss) | true |
