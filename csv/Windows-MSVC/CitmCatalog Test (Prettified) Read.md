
----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12578.3 | 0.0306797 | 8745.17ms | 1151920 | 4890 | 3.51083e+06 | 87337.3 | 0.0412966 | 0.241517 | 1(Win) | true |
| simdjson (stage-1) | 12025.8 | 0.150048 | 9127.42ms | 1151920 | 80 | 1.50304e+06 | 91350 | 0.0410678 | 0.252622 | 2(Loss) | true |
