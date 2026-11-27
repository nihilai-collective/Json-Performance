
----
### Discord Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5449.25 | 0.0989971 | 841.583ms | 6701 | 2560 | 3450.57 | 1172.74 | 0.0566568 | 0.972406 | 4.2807 | 0.61752 | 0.000151155 | 1.17753e-05 | 2.33174e-06 | 1(Win) | true |
| simdjson (ondemand) | 4726.14 | 0.165895 | 866.463ms | 6701 | 40 | 201.276 | 1352.17 | 0.0154097 | 1.1032 | 4.72959 | 0.618266 | 0.00033204 | 1.11924e-05 | 3.73079e-06 | 2(Loss) | true |
