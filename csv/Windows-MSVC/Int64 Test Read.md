
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 581.158 | 0.122322 | 648.723ms | 3862 | 40 | 2403.85 | 6337.5 | 0.0657895 | 4.24245 | 1(Win) | true |
| simdjson (ondemand) | 307.983 | 0.0529988 | 1224.9ms | 3862 | 80 | 3213.61 | 11958.8 | 0.136069 | 8.01708 | 2(Loss) | true |
