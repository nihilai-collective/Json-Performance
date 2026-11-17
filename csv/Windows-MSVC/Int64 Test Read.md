
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1589.36 | 0.196473 | 239.344ms | 3862 | 640 | 13266.8 | 2317.34 | 0.208586 | 1.89482 | 1(Win) | true |
| Glaze | 946.05 | 0.104353 | 400.26ms | 3862 | 640 | 10563 | 3893.12 | 0.0320976 | 3.19546 | 2(Loss) | true |
| Jsonifier (two-stage) | 889.635 | 0.189484 | 430.386ms | 3862 | 40 | 2461.54 | 4140 | 0 | 3.39736 | 3(Loss) | true |
| simdjson (ondemand) | 565.216 | 0.256694 | 660.606ms | 3862 | 160 | 44765.7 | 6516.25 | 0 | 5.36255 | 4(Loss) | true |
