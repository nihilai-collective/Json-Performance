
----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 358.151 | 0.140267 | 353.608ms | 1313 | 4890 | 117602 | 3496.22 | 0.128507 | 6.85906 | 1(Win) | true |
| Jsonifier | 353.764 | 0.184275 | 355.527ms | 1313 | 2560 | 108912 | 3539.58 | 0.533964 | 6.94337 | 2(Loss) | true |
| Glaze | 311.816 | 0.0500328 | 413.871ms | 1313 | 40 | 161.474 | 4015.75 | 0.0344596 | 7.89 | 3(Loss) | true |
