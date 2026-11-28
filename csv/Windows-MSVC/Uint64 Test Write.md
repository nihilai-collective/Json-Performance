
----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 596.869 | 0.140309 | 215.596ms | 1213 | 320 | 2366.38 | 1938.12 | 0.289389 | 4.08983 | 1(Win) | true |
| Glaze | 116.038 | 0.1862 | 1007.87ms | 1213 | 2560 | 882108 | 9969.22 | 0.172703 | 21.2578 | 2(Loss) | true |
