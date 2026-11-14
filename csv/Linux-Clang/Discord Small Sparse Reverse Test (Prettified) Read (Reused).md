
----
### Discord Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4151.7 | 0.0343498 | 876.99ms | 6701 | 640 | 178.918 | 1539.27 | 0.02579 | 1.27361 | 5.67348 | 0.92046 | 0.000875569 | 1.44568e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3014.37 | 0.0641748 | 931.532ms | 6701 | 1280 | 2369.33 | 2120.03 | 0.00641245 | 1.73973 | 7.61916 | 1.10939 | 0.00234573 | 1.09592e-05 | 9.32697e-07 | 2(Loss) | true |
