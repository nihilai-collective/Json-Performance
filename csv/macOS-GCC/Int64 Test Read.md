
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1254.18 | 0.865452 | 110.55ms | 1313 | 80 | 5972.9 | 998.4 | 0 | 1(Win) | true |
| Glaze | 864.522 | 0.97366 | 157.388ms | 1313 | 1280 | 254567 | 1448.4 | 0.415973 | 2(Loss) | true |
| simdjson (reflection) | 611.264 | 0.790027 | 203.835ms | 1313 | 2560 | 670495 | 2048.5 | 1.03865 | 3(Loss) | true |
| simdjson (ondemand) | 295.845 | 1.68432 | 460.447ms | 1313 | 30 | 152465 | 4232.53 | 0 | 4(Loss) | true |
