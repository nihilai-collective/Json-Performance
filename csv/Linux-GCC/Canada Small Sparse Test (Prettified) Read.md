
----
### Canada Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 12930.6 | 0.0741696 | 802.199ms | 11579 | 320 | 128.382 | 853.987 | 0.046861 | 0.417261 | 2.09474 | 0.223681 | 0.000172726 | 4.04828e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 11015.3 | 0.0420133 | 816.893ms | 11579 | 320 | 56.7645 | 1002.48 | 0.00623492 | 0.486373 | 2.45177 | 0.232576 | 0.000172726 | 8.36644e-06 | 0 | 2(Loss) | true |
