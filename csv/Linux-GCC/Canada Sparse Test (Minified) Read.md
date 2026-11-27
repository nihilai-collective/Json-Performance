
----
### Canada Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10759.8 | 0.179362 | 9552.84ms | 2090234 | 160 | 1.76668e+07 | 185263 | 0.0770849 | 0.230059 | 1(Win) | true |
| simdjson (ondemand) | 8570.11 | 0.0763312 | 6032.87ms | 2090234 | 640 | 2.01744e+07 | 232599 | 0.187631 | 0.288851 | 2(Loss) | true |
