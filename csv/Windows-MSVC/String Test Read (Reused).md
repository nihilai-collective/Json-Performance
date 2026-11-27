
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1009.98 | 0.157393 | 547.277ms | 4215 | 80 | 3139.24 | 3980 | 0.125786 | 2.42996 | 1(Win) | true |
| Glaze | 789.926 | 0.17823 | 631.269ms | 4215 | 80 | 6580.7 | 5088.75 | 0.0737463 | 3.11714 | 2(Loss) | true |
| simdjson (ondemand) | 512.349 | 0.239943 | 920.812ms | 4215 | 1280 | 453617 | 7845.7 | 0.0408098 | 4.8153 | 3(Loss) | true |
