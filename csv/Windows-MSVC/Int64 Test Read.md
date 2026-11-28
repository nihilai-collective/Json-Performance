
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 866.557 | 0.551299 | 151.874ms | 1313 | 40 | 2538.46 | 1445 | 0.115207 | 2.79436 | 1(Win) | true |
| Glaze | 377.128 | 0.174539 | 335.209ms | 1313 | 4890 | 164227 | 3320.29 | 0.0537019 | 6.49265 | 2(Loss) | true |
| simdjson (ondemand) | 287.129 | 0.175085 | 440.737ms | 1313 | 4890 | 285091 | 4361.02 | 0.0812868 | 8.5574 | 3(Loss) | true |
