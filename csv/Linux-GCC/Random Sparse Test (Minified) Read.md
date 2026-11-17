
----
### Random Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2441.69 | 0.0292494 | 8550.05ms | 409725 | 1280 | 2.80444e+06 | 160030 | 0.0577266 | 2.08323 | 10.1568 | 1.7835 | 0.00548231 | 2.67233e-05 | 1.18525e-05 | 1(Win) | true |
| simdjson (ondemand) | 1916.16 | 0.0504709 | 5318.25ms | 409725 | 80 | 847410 | 203920 | 0.0504618 | 2.63737 | 10.8143 | 1.83904 | 0.0082372 | 0.000109159 | 4.14912e-06 | 2(Loss) | true |
