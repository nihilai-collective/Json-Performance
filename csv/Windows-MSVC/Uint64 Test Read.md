
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 994.301 | 0.150044 | 125.332ms | 1213 | 1280 | 3900.61 | 1163.44 | 0.242326 | 3.00461 | 1(Win) | true |
| Glaze | 340.613 | 0.152203 | 370.202ms | 1213 | 80 | 2137.66 | 3396.25 | 0.0367918 | 8.88511 | 2(Loss) | true |
| simdjson (ondemand) | 287.763 | 0.184771 | 436.52ms | 1213 | 30 | 1655.17 | 4020 | 0.248139 | 10.5053 | 3(Loss) | true |
