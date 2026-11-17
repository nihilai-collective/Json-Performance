
----
### Twitter Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5999.1 | 0.0463926 | 6471.73ms | 360584 | 320 | 226302 | 57321.9 | 0.0176549 | 0.844233 | 4.32163 | 0.651502 | 0.00134159 | 2.01063e-06 | 2.25329e-07 | 1(Win) | true |
| simdjson (ondemand) | 5031.22 | 0.0292387 | 7617.38ms | 360584 | 4890 | 1.95295e+06 | 68349.2 | 0.0479799 | 1.01352 | 4.97662 | 0.692143 | 0.00196254 | 5.15524e-06 | 3.03416e-06 | 2(Loss) | true |
