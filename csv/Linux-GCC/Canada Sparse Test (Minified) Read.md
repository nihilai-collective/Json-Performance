
----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10077.4 | 0.109338 | 5045ms | 2090234 | 1280 | 5.98746e+07 | 197809 | 0.0719423 | 0.245637 | 1(Win) | true |
| simdjson (ondemand) | 8265.15 | 0.0923976 | 6252.64ms | 2090234 | 640 | 3.17826e+07 | 241182 | 0.394502 | 0.299506 | 2(Loss) | true |
