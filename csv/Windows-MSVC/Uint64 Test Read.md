
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1398.75 | 0.154956 | 283.675ms | 3873 | 160 | 2678.85 | 2640.62 | 0.023663 | 1.75158 | 1(Win) | true |
| Jsonifier (two-stage) | 1366.73 | 0.247425 | 278.734ms | 3873 | 40 | 1788.46 | 2702.5 | 0.153941 | 1.79637 | 2(Loss) | true |
| Glaze | 1034.16 | 0.0789297 | 372.556ms | 3873 | 320 | 2543.01 | 3571.56 | 0.530896 | 2.37837 | 3(Loss) | true |
| simdjson (ondemand) | 663.12 | 0.175357 | 586.308ms | 3873 | 30 | 2862.07 | 5570 | 0.179856 | 3.71233 | 4(Loss) | true |
