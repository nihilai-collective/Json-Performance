
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 560.469 | 0.177563 | 675.419ms | 3873 | 2560 | 350540 | 6590.16 | 0.0367364 | 4.40023 | 1(Win) | true |
| simdjson (ondemand) | 305.496 | 0.154266 | 1236.52ms | 3873 | 2560 | 890557 | 12090.4 | 0.191958 | 8.08597 | 2(Loss) | true |
