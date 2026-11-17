
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1347.41 | 0.202048 | 282.085ms | 3873 | 80 | 2454.11 | 2741.25 | 0.0456204 | 1.81697 | 1(Win) | true |
| Glaze | 974.62 | 0.311708 | 388.445ms | 3873 | 1280 | 178621 | 3789.77 | 0.158986 | 2.52149 | 2(Loss) | true |
| Jsonifier (two-stage) | 547.806 | 0.0866052 | 702.102ms | 3873 | 80 | 2727.85 | 6742.5 | 0.037092 | 4.50281 | 3(Loss) | true |
| simdjson (ondemand) | 300.979 | 0.508033 | 1242.54ms | 3873 | 160 | 621908 | 12271.9 | 0.117275 | 8.20935 | 4(Loss) | true |
