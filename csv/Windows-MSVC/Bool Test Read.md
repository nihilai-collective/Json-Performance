
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 534.515 | 0.131606 | 165.16ms | 905 | 320 | 1445.04 | 1614.69 | 0.213344 | 4.54975 | 1(Win) | true |
| Glaze | 501.037 | 0.426242 | 177.014ms | 905 | 1280 | 69005.1 | 1722.58 | 0.176566 | 4.8621 | 2(Loss) | true |
| simdjson (ondemand) | 161.986 | 0.192556 | 544.072ms | 905 | 2560 | 269461 | 5328.09 | 0.125211 | 15.1879 | 3(Loss) | true |
