
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 208.095 | 0.211246 | 428.838ms | 905 | 40 | 3070.51 | 4147.5 | 0.261886 | 11.827 | 1(Win) | true |
| simdjson (ondemand) | 66.918 | 0.0518447 | 1303.36ms | 905 | 40 | 1788.46 | 12897.5 | 0.610069 | 36.8869 | 2(Loss) | true |
