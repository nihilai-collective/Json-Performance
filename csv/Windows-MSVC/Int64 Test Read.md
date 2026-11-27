
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 2254.9 | 0.438232 | 62.678ms | 1313 | 640 | 3790.2 | 555.312 | 0.168539 | 1.30284 | 1(Win) | true |
| simdjson (stage-1) | 919.027 | 0.568967 | 136.269ms | 1313 | 40 | 2403.85 | 1362.5 | 0.183824 | 3.26721 | 2(Loss) | true |
