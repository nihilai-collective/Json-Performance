
----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 807.007 | 0.757813 | 7608.63ms | 65103 | 640 | 2.17546e+08 | 76935 | 0.346491 | 3.06638 | 1(Win) | true |
| simdjson (ondemand) | 652.554 | 0.305711 | 9353.66ms | 65103 | 4890 | 4.13714e+08 | 95144.7 | 0.24667 | 3.79258 | 2(Loss) | true |
