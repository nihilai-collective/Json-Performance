
----
### Canada Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10874.9 | 0.0698041 | 5905.39ms | 5212421 | 160 | 1.62898e+07 | 457105 | 0.170278 | 0.467391 | 1.95582 | 0.183243 | 0.0019681 | 0.0394045 | 5.80464e-06 | 1(Win) | true |
| simdjson (ondemand) | 9946.79 | 0.0361625 | 6459.67ms | 5212421 | 640 | 2.09031e+07 | 499754 | 0.0225878 | 0.514869 | 2.19702 | 0.202777 | 0.00216785 | 0.0393847 | 1.84775e-06 | 2(Loss) | true |
