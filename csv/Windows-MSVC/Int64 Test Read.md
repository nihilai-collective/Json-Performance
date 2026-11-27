
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 1920.88 | 0.607857 | 70.1901ms | 1313 | 160 | 2512.19 | 651.875 | 0.286807 | 1.23571 | 1(Win) | true |
| simdjson (stage-1) | 863.569 | 0.387961 | 149.721ms | 1313 | 80 | 2531.65 | 1450 | 0.172712 | 2.80343 | 2(Loss) | true |
