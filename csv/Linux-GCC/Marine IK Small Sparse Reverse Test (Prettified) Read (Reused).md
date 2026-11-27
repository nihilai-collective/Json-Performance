
----
### Marine IK Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7868.09 | 0.430655 | 948.037ms | 18245 | 80 | 7256.02 | 2211.44 | 0.0469372 | 0.666822 | 3.14853 | 0.463908 | 0.000303508 | 8.22143e-06 | 2.05536e-06 | 1(Win) | true |
| simdjson (ondemand) | 6687.26 | 0.0392519 | 981.115ms | 18245 | 2560 | 2670.26 | 2601.93 | 0.012249 | 0.782691 | 4.37775 | 0.631899 | 0.0002299 | 1.74919e-05 | 6.82978e-06 | 2(Loss) | true |
