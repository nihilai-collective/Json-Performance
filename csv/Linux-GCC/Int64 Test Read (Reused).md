
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 872.157 | 0.044793 | 432.643ms | 3862 | 30 | 107.344 | 4222.97 | 0.0386924 | 2.82256 | 1(Win) | true |
| simdjson (ondemand) | 597.155 | 0.0650146 | 624.984ms | 3862 | 40 | 643.179 | 6167.73 | 0.0231095 | 4.12785 | 2(Loss) | true |
