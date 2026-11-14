
----
### Canada Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9030.92 | 0.186972 | 7114.67ms | 5212421 | 40 | 4.2367e+07 | 550437 | 0.043684 | 0.5678 | 2.54442 | 0.309596 | 0.00224657 | 0.0590648 | 5.05044e-06 | 1(Win) | true |
| simdjson (ondemand) | 7813.52 | 0.134236 | 8134.98ms | 5212421 | 40 | 2.9173e+07 | 636198 | 0.0444949 | 0.650285 | 2.85495 | 0.331074 | 0.00213905 | 0.0590747 | 4.9641e-06 | 2(Loss) | true |
