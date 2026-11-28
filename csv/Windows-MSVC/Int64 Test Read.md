
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 840.209 | 0.389559 | 160.934ms | 1313 | 1280 | 43143 | 1490.31 | 0.74922 | 2.89368 | 1(Win) | true |
| Glaze | 343.532 | 0.218553 | 376.918ms | 1313 | 40 | 2538.46 | 3645 | 0.137363 | 7.10842 | 2(Loss) | true |
| simdjson (ondemand) | 262.993 | 0.132063 | 494.553ms | 1313 | 80 | 3162.97 | 4761.25 | 0.0788229 | 9.35388 | 3(Loss) | true |
