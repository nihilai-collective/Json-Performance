
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 546.25 | 0.149143 | 684.442ms | 3862 | 40 | 4044.87 | 6742.5 | 0.406204 | 4.51985 | 1(Win) | true |
| simdjson (ondemand) | 306.074 | 0.0829431 | 1268.72ms | 3862 | 30 | 2988.51 | 12033.3 | 0.248687 | 8.07038 | 2(Loss) | true |
