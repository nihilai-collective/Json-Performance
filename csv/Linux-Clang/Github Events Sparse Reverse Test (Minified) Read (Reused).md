
----
### Github Events Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6124.36 | 0.0306012 | 1584.52ms | 53331 | 4890 | 31580.7 | 8304.6 | 0.0331847 | 0.836083 | 4.10969 | 0.676361 | 0.00164744 | 3.53927e-06 | 6.94049e-07 | 1(Win) | true |
| simdjson (ondemand) | 4292.06 | 0.0887857 | 1947.17ms | 53331 | 40 | 4427.65 | 11849.9 | 0.0245492 | 1.2047 | 5.73878 | 0.911609 | 0.00217697 | 4.21893e-06 | 0 | 2(Loss) | true |
