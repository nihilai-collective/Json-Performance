
----
### Canada Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 11284.6 | 0.776665 | 5704.28ms | 5212421 | 160 | 1.87281e+09 | 440508 | 0.117342 | 0.447269 | 1.96707 | 0.181297 | 0.0022839 | 0.0394066 | 1.71945e-06 | 1(Win) | true |
| simdjson (ondemand) | 9658.15 | 0.103707 | 6698.04ms | 5212421 | 640 | 1.82343e+08 | 514690 | 0.624121 | 0.526363 | 2.27766 | 0.202785 | 0.00212592 | 0.0394736 | 8.04269e-06 | 2(Loss) | true |
