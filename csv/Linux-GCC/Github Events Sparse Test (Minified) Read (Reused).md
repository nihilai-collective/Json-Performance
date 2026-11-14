
----
### Github Events Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8672.74 | 0.0395323 | 1325.6ms | 53331 | 2560 | 13759.1 | 5864.4 | 0.0960918 | 0.597196 | 2.86518 | 0.364422 | 0.000790113 | 3.32534e-06 | 2.71008e-07 | 1(Win) | true |
| simdjson (ondemand) | 7154.58 | 0.0612106 | 1443.35ms | 53331 | 80 | 1514.73 | 7108.79 | 0.021975 | 0.724381 | 3.25158 | 0.384936 | 0.000941057 | 4.68771e-06 | 3.28139e-06 | 2(Loss) | true |
