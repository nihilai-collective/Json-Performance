
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 765.147 | 0.22233 | 155.298ms | 1213 | 160 | 1807.78 | 1511.88 | 0.124172 | 3.18444 | 1(Win) | true |
| Glaze | 332.655 | 0.192284 | 357.765ms | 1213 | 40 | 1788.46 | 3477.5 | 0.0239693 | 7.35577 | 2(Loss) | true |
| simdjson (ondemand) | 254.383 | 0.175842 | 463.817ms | 1213 | 40 | 2557.69 | 4547.5 | 0.238795 | 9.67168 | 3(Loss) | true |
