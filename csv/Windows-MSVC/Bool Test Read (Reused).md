
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 580.707 | 0.260691 | 150.111ms | 905 | 80 | 1200.95 | 1486.25 | 0.422297 | 4.17751 | 1(Win) | true |
| Glaze | 554.364 | 0.504794 | 171.321ms | 905 | 320 | 19764.5 | 1556.88 | 0.280224 | 4.38834 | 2(Loss) | true |
| simdjson (ondemand) | 157.316 | 0.0706223 | 559.797ms | 905 | 80 | 1200.95 | 5486.25 | 0.022779 | 15.6197 | 3(Loss) | true |
