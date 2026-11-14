
----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7967.67 | 0.05215 | 5108.33ms | 360584 | 1280 | 648438 | 43159.4 | 0.324598 | 0.6392 | 3.05734 | 0.348088 | 0.00122561 | 8.49317e-07 | 1.81996e-07 | 1(Win) | true |
| simdjson (ondemand) | 7480.16 | 0.0269943 | 5391.87ms | 360584 | 1280 | 197126 | 45972.2 | 0.0976911 | 0.677062 | 3.25914 | 0.325421 | 0.000760882 | 1.52747e-06 | 3.3366e-07 | 2(Loss) | true |
