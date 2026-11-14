
----
### Canada Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5435.82 | 0.0801743 | 791.628ms | 4630 | 4890 | 2074.01 | 812.3 | 0.288588 | 0.993907 | 5.11577 | 0.797192 | 0.000648169 | 1.77998e-05 | 7.24359e-06 | 1(Win) | true |
| simdjson (ondemand) | 5096.07 | 0.0325026 | 797.578ms | 4630 | 640 | 50.7585 | 866.455 | 0.0405584 | 1.05682 | 5.54752 | 0.809503 | 0.000647948 | 5.39957e-06 | 1.68737e-06 | 2(Loss) | true |
