
----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5250.12 | 0.118885 | 792.922ms | 3770 | 2560 | 1696.84 | 684.814 | 0.0380319 | 1.03179 | 4.44403 | 0.679576 | 0.0009031 | 2.20698e-05 | 5.906e-06 | 1(Win) | true |
| simdjson (ondemand) | 4516.39 | 0.152992 | 798.965ms | 3770 | 1280 | 1898.66 | 796.067 | 0.0237439 | 1.18009 | 5.02308 | 0.692838 | 0.000806532 | 9.94695e-06 | 2.90119e-06 | 2(Loss) | true |
