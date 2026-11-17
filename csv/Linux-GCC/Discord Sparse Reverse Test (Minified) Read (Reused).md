
----
### Discord Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2201.97 | 0.0138317 | 3463.34ms | 56369 | 4890 | 55759 | 24413.4 | 0.00161065 | 2.34021 | 11.553 | 2.15384 | 0.00389525 | 1.5266e-05 | 7.9813e-06 | 1(Win) | true |
| simdjson (ondemand) | 1480.26 | 0.130102 | 4644.96ms | 56369 | 80 | 178592 | 36316.3 | 0.0304708 | 3.48088 | 15.1214 | 2.65902 | 0.0111021 | 3.7698e-06 | 0 | 2(Loss) | true |
