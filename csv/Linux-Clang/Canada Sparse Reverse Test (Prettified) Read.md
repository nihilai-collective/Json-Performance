
----
### Canada Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8358.03 | 0.366367 | 7672.98ms | 5212421 | 160 | 7.59667e+08 | 594752 | 0.243184 | 0.603056 | 2.52183 | 0.327128 | 0.00216273 | 0.0590797 | 8.28909e-06 | 1(Win) | true |
| simdjson (ondemand) | 8018.38 | 0.235597 | 8045ms | 5212421 | 80 | 1.70662e+08 | 619945 | 0.0693869 | 0.631197 | 2.7744 | 0.33108 | 0.00188517 | 0.0591754 | 1.84511e-05 | 2(Loss) | true |
