
----
### Canada Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 11506.4 | 0.144409 | 5597.54ms | 5212421 | 160 | 6.22741e+07 | 432016 | 0.0489442 | 0.442307 | 1.96704 | 0.18129 | 0.00223307 | 0.0393919 | 5.66555e-06 | 1(Win) | true |
| simdjson (ondemand) | 9749.32 | 0.0240402 | 6596.54ms | 5212421 | 640 | 9.61585e+06 | 509877 | 0.11233 | 0.527314 | 2.27762 | 0.202778 | 0.00216729 | 0.0393846 | 2.8013e-06 | 2(Loss) | true |
