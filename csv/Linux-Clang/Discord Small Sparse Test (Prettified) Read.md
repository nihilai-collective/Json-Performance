
----
### Discord Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4936.9 | 0.162753 | 851.188ms | 6701 | 40 | 177.536 | 1294.45 | 0.109561 | 1.07578 | 4.51157 | 0.672885 | 0.000156693 | 1.11924e-05 | 1.11924e-05 | 1(Win) | true |
| simdjson (ondemand) | 4605.41 | 0.100029 | 854.256ms | 6701 | 320 | 616.518 | 1387.62 | 0.0250041 | 1.1514 | 4.74989 | 0.623787 | 0.000366083 | 4.0106e-05 | 2.1452e-05 | 2(Loss) | true |
