
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1258.69 | 0.694891 | 5518.77ms | 1151920 | 40 | 1.47129e+09 | 872775 | 0.728828 | 1.96684 | 1(Win) | true |
| simdjson (ondemand) | 1094.11 | 0.582301 | 6477.38ms | 1151920 | 80 | 2.73467e+09 | 1.00406e+06 | 0.708502 | 2.26273 | 2(Loss) | true |
