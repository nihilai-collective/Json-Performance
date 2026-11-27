
----
### Random Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3812.71 | 0.0670624 | 924.409ms | 8150 | 1280 | 2392.31 | 2038.56 | 0.0021844 | 1.37766 | 5.87926 | 0.992638 | 0.00133301 | 2.73198e-05 | 1.00652e-05 | 1(Win) | true |
| simdjson (ondemand) | 3351.36 | 0.0591984 | 952.851ms | 8150 | 2560 | 4825.38 | 2319.19 | 0.0623314 | 1.56174 | 6.55791 | 0.976197 | 0.00166147 | 1.9028e-05 | 4.36158e-06 | 2(Loss) | true |
