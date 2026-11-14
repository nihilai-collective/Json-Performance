
----
### Random Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2521.9 | 0.0553226 | 903.839ms | 4926 | 2560 | 2718.79 | 1862.8 | 0.01294 | 2.08625 | 8.92814 | 1.66565 | 0.00220133 | 3.67946e-05 | 5.07511e-06 | 1(Win) | true |
| simdjson (ondemand) | 2150.55 | 0.0612818 | 933.078ms | 4926 | 640 | 1146.92 | 2184.46 | 0.0227511 | 2.43878 | 10.2745 | 1.62525 | 0.00134015 | 2.09348e-05 | 0 | 2(Loss) | true |
