
----
### Discord Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2497.05 | 0.0220557 | 3934.51ms | 83958 | 4890 | 244580 | 32065.2 | 0.115618 | 2.05672 | 9.72625 | 1.73988 | 0.003309 | 7.99406e-06 | 3.0544e-06 | 1(Win) | true |
| simdjson (ondemand) | 1945.33 | 0.099534 | 4833.37ms | 83958 | 320 | 537069 | 41159.4 | 0.0260109 | 2.63718 | 12.0444 | 1.95048 | 0.0067734 | 3.98265e-06 | 1.11663e-06 | 2(Loss) | true |
