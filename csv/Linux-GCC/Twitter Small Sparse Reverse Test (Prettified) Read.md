
----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5197.05 | 0.0310024 | 783.442ms | 3770 | 2560 | 117.761 | 691.807 | 0.109039 | 1.04609 | 4.387 | 0.66366 | 0.000795756 | 1.91686e-05 | 3.73011e-06 | 1(Win) | true |
| simdjson (ondemand) | 4538.9 | 0.0488938 | 796.453ms | 3770 | 640 | 95.9996 | 792.12 | 0.0297767 | 1.19263 | 5.05676 | 0.702653 | 0.000549983 | 1.40915e-05 | 8.28912e-07 | 2(Loss) | true |
