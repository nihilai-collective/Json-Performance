
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 423.884 | 0.0959352 | 277.882ms | 1213 | 320 | 2193.48 | 2729.06 | 0.194286 | 5.77878 | 1(Win) | true |
| simdjson (ondemand) | 260.03 | 0.12641 | 455.556ms | 1213 | 80 | 2530.06 | 4448.75 | 0.0843645 | 9.45573 | 2(Loss) | true |
