
----
### Google Maps Response Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4106.56 | 0.0389711 | 943.231ms | 9378 | 640 | 461.03 | 2177.87 | 0.120743 | 1.2782 | 5.62945 | 0.913734 | 0.000982186 | 1.58283e-05 | 4.16533e-06 | 1(Win) | true |
| simdjson (ondemand) | 3894.85 | 0.175806 | 953.881ms | 9378 | 320 | 5215.05 | 2296.25 | 0.141872 | 1.34443 | 5.94519 | 0.871508 | 0.00148586 | 1.09965e-05 | 3.33227e-07 | 2(Loss) | true |
