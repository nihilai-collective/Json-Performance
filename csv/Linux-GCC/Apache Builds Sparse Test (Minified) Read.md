
----
### Apache Builds Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2692.93 | 0.0491661 | 4090.81ms | 94653 | 640 | 173833 | 33520.4 | 0.0360405 | 1.88535 | 8.84308 | 1.64076 | 0.00533508 | 8.41891e-06 | 4.65516e-06 | 1(Win) | true |
| simdjson (ondemand) | 1900.84 | 0.0226157 | 5521.01ms | 94653 | 2560 | 295282 | 47488.6 | 0.14245 | 2.68075 | 10.6628 | 1.9762 | 0.0083572 | 1.31236e-05 | 8.87287e-06 | 2(Loss) | true |
