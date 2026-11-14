
----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1721.07 | 0.425102 | 229.4ms | 3862 | 30 | 2482.76 | 2140 | 0.155521 | 1.75112 | 1(Win) | true |
| simdjson (stage-1) | 870.021 | 0.206782 | 445.731ms | 3862 | 30 | 2298.85 | 4233.33 | 1.3209 | 3.46997 | 2(Loss) | true |
