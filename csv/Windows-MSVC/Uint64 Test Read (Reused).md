
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1458.83 | 0.925311 | 84.8688ms | 1213 | 2560 | 137825 | 792.969 | 0.664485 | 2.0141 | 1(Win) | true |
| Glaze | 383.049 | 0.245954 | 320.943ms | 1213 | 30 | 1655.17 | 3020 | 0.778643 | 7.79481 | 2(Loss) | true |
| simdjson (ondemand) | 324.832 | 0.153912 | 382.301ms | 1213 | 80 | 2403.48 | 3561.25 | 0.0351124 | 9.27876 | 3(Loss) | true |
