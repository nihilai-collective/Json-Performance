
----
### Marine IK Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8325.64 | 0.117439 | 932.952ms | 18245 | 1280 | 7710.61 | 2089.9 | 0.107027 | 0.627701 | 3.08627 | 0.474157 | 0.000267753 | 1.07906e-05 | 3.93944e-06 | 1(Win) | true |
| simdjson (ondemand) | 6754.08 | 0.0718113 | 980.49ms | 18245 | 640 | 2190.39 | 2576.19 | 0.0610527 | 0.76578 | 4.25629 | 0.629926 | 0.00028441 | 7.27939e-06 | 2.05536e-06 | 2(Loss) | true |
