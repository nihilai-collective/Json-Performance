
----
### Twitter Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7022.56 | 0.0675028 | 4370.67ms | 264040 | 4890 | 2.86485e+06 | 35857.1 | 0.00583553 | 0.723267 | 3.53548 | 0.450299 | 0.0013483 | 1.30062e-05 | 1.03768e-05 | 1(Win) | true |
| simdjson (ondemand) | 6218.19 | 0.052952 | 4835.46ms | 264040 | 320 | 147138 | 40495.4 | 0.0260147 | 0.814838 | 3.91861 | 0.421431 | 0.000969964 | 2.84048e-06 | 1.90549e-06 | 2(Loss) | true |
