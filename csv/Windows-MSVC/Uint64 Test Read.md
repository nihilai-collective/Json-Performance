
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 834.369 | 0.118158 | 456.44ms | 3873 | 1280 | 35020.2 | 4426.8 | 0.11106 | 3.62599 | 1(Win) | true |
| simdjson (ondemand) | 566.283 | 0.287727 | 662.028ms | 3873 | 640 | 225408 | 6522.5 | 0.0478881 | 5.34907 | 2(Loss) | true |
