
----
### Discord Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1877.11 | 0.0283255 | 3595.42ms | 56369 | 2560 | 168461 | 28638.6 | 0.224455 | 2.7133 | 12.9149 | 2.46606 | 0.00371242 | 0.000119061 | 9.46331e-05 | 1(Win) | true |
| simdjson (ondemand) | 1355.88 | 0.0312959 | 4710.03ms | 56369 | 1280 | 197072 | 39647.9 | 0.00250059 | 3.76311 | 16.5755 | 2.96884 | 0.010824 | 1.02838e-05 | 4.39348e-06 | 2(Loss) | true |
