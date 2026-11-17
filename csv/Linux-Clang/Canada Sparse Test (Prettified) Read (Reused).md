
----
### Canada Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10737.6 | 0.18782 | 6016.73ms | 5212421 | 80 | 6.04842e+07 | 462949 | 0.106567 | 0.471564 | 1.95582 | 0.183243 | 0.00198395 | 0.0394079 | 4.73628e-06 | 1(Win) | true |
| simdjson (ondemand) | 9878.86 | 0.100134 | 6548.61ms | 5212421 | 320 | 8.12414e+07 | 503191 | 0.358767 | 0.516599 | 2.19702 | 0.202778 | 0.002168 | 0.0394054 | 1.4017e-06 | 2(Loss) | true |
