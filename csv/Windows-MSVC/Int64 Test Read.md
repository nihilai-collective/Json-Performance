
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 819.973 | 0.79979 | 468.798ms | 3862 | 640 | 825956 | 4491.72 | 0.0312978 | 3.68943 | 1(Win) | true |
| simdjson (ondemand) | 574.739 | 0.159907 | 654.218ms | 3862 | 2560 | 268818 | 6408.28 | 0.040215 | 5.26984 | 2(Loss) | true |
