
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1023.34 | 0.626864 | 363.638ms | 4215 | 640 | 388045 | 3928.05 | 0.0880306 | 1(Win) | true |
| Glaze | 840.146 | 0.212852 | 478.446ms | 4215 | 640 | 66377.7 | 4784.57 | 0.383745 | 2(Loss) | true |
| simdjson (ondemand) | 714.491 | 0.0494617 | 569.161ms | 4215 | 320 | 2477.94 | 5626.02 | 0.0655008 | 3(Loss) | true |
