
----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2363.6 | 0.10406 | 7405.82ms | 183677 | 1280 | 7.61272e+06 | 74110.5 | 0.0658421 | 1.28534 | 1(Win) | true |
| Jsonifier | 2162.21 | 0.0880109 | 8085.96ms | 183677 | 320 | 1.62681e+06 | 81013.4 | 0.0212111 | 1.40522 | 2(Loss) | true |
| Glaze | 1799.24 | 0.120023 | 9720.35ms | 183677 | 640 | 8.73849e+06 | 97356.6 | 0.107735 | 1.68882 | 3(Loss) | true |
| simdjson (ondemand) | 1427.69 | 0.0916749 | 6295.34ms | 183677 | 1280 | 1.6194e+07 | 122694 | 0.067796 | 2.12845 | 4(Loss) | true |
