
----
### Discord Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2448.16 | 0.0399373 | 2972.43ms | 56369 | 4890 | 376068 | 21958.4 | 0.181449 | 2.07543 | 9.5231 | 1.70865 | 0.00529561 | 2.35049e-05 | 1.46928e-05 | 1(Win) | true |
| simdjson (ondemand) | 2104.81 | 0.0918451 | 3304.11ms | 56369 | 1280 | 704334 | 25540.4 | 0.148846 | 2.40948 | 10.0999 | 1.68715 | 0.0052921 | 8.349e-05 | 6.34768e-05 | 2(Loss) | true |
