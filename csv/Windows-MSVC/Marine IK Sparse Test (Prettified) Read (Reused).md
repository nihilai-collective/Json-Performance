
----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9801.86 | 0.171448 | 9145.54ms | 7351818 | 30 | 4.5119e+07 | 715297 | 0.0651985 | 0.310014 | 1(Win) | true |
| simdjson (ondemand) | 8161.15 | 0.190189 | 5391.69ms | 7351818 | 160 | 4.27148e+08 | 859100 | 0.281169 | 0.372342 | 2(Loss) | true |
