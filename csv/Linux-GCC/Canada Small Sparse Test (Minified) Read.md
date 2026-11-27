
----
### Canada Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7870.03 | 0.0797618 | 768.304ms | 4630 | 4890 | 979.281 | 561.054 | 0.141575 | 0.699907 | 3.51188 | 0.492873 | 0.000432849 | 3.24195e-05 | 1.74906e-05 | 1(Win) | true |
| simdjson (ondemand) | 6486.68 | 0.0497653 | 780.363ms | 4630 | 4890 | 561.149 | 680.704 | 0.350037 | 0.836893 | 4.11512 | 0.493089 | 0.000432407 | 1.98757e-05 | 9.14283e-06 | 2(Loss) | true |
