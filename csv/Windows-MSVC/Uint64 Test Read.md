
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1406.77 | 0.240125 | 265.841ms | 3873 | 4890 | 194373 | 2625.58 | 0.0402721 | 1.74171 | 1(Win) | true |
| Glaze | 1017.17 | 0.104133 | 369.13ms | 3873 | 160 | 2287.74 | 3631.25 | 0.171821 | 2.41473 | 2(Loss) | true |
| Jsonifier (two-stage) | 573.514 | 0.149566 | 655.064ms | 3873 | 4890 | 453717 | 6440.27 | 0.022329 | 4.29845 | 3(Loss) | true |
| simdjson (ondemand) | 310.438 | 0.258043 | 1212.18ms | 3873 | 640 | 603267 | 11898 | 0.0800441 | 7.95841 | 4(Loss) | true |
