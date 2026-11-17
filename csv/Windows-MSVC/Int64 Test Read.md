
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1494.15 | 0.176949 | 253.767ms | 3862 | 160 | 3044.03 | 2465 | 0.101523 | 1.6415 | 1(Win) | true |
| Glaze | 880.069 | 0.136624 | 430.332ms | 3862 | 40 | 1307.69 | 4185 | 0.0398089 | 2.79336 | 2(Loss) | true |
| Jsonifier (two-stage) | 391.263 | 0.16687 | 662.218ms | 3862 | 30 | 7402.3 | 9413.33 | 0.641483 | 6.30432 | 3(Loss) | true |
| simdjson (ondemand) | 296.094 | 0.342953 | 1248.66ms | 3862 | 640 | 1.1647e+06 | 12438.9 | 0.585679 | 8.34484 | 4(Loss) | true |
