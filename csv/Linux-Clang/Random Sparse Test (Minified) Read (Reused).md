
----
### Random Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2841.49 | 0.026635 | 8496ms | 409725 | 2560 | 3.43429e+06 | 137514 | 0.114384 | 1.78701 | 8.59049 | 1.52801 | 0.00467187 | 2.53018e-05 | 1.14492e-05 | 1(Win) | true |
| simdjson (ondemand) | 2249.09 | 0.0324219 | 5119.22ms | 409725 | 1280 | 4.06125e+06 | 173735 | 0.234784 | 2.25557 | 10.0158 | 1.56464 | 0.0060052 | 0.000151464 | 3.29337e-05 | 2(Loss) | true |
