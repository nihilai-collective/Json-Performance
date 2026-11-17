
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1954.38 | 0.216962 | 192.532ms | 3862 | 640 | 10699.3 | 1884.53 | 0.793916 | 1.52804 | 1(Win) | true |
| Glaze | 1100.02 | 0.119236 | 338.394ms | 3862 | 2560 | 40801.8 | 3348.2 | 0.107219 | 2.73702 | 2(Loss) | true |
| Jsonifier (two-stage) | 988.086 | 0.0681122 | 378.322ms | 3862 | 320 | 2062.7 | 3727.5 | 0.566856 | 3.04668 | 3(Loss) | true |
| simdjson (ondemand) | 617.968 | 0.152637 | 605.225ms | 3862 | 30 | 2482.76 | 5960 | 0.168067 | 4.89943 | 4(Loss) | true |
