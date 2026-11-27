
----
### Instruments Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5228.96 | 0.0313635 | 2720.49ms | 108313 | 4890 | 187710 | 19754.5 | 0.120351 | 0.976875 | 5.3187 | 0.803782 | 0.000700734 | 6.19465e-06 | 4.31605e-06 | 1(Win) | true |
| simdjson (ondemand) | 4462.23 | 0.115042 | 3046.79ms | 108313 | 160 | 113472 | 23148.8 | 0.135341 | 1.14398 | 5.89738 | 0.716978 | 0.00144287 | 1.55798e-06 | 3.46219e-07 | 2(Loss) | true |
