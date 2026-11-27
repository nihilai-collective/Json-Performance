
----
### Twitter Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5424.62 | 0.11978 | 784.362ms | 3770 | 320 | 201.681 | 662.784 | 0.026868 | 1.02327 | 4.33289 | 0.650398 | 0.000864556 | 2.40385e-05 | 7.46021e-06 | 1(Win) | true |
| simdjson (ondemand) | 4654.19 | 0.043351 | 795.639ms | 3770 | 1280 | 143.55 | 772.498 | 0.102755 | 1.16096 | 5.0008 | 0.689655 | 0.000602619 | 2.73541e-05 | 7.87467e-06 | 2(Loss) | true |
