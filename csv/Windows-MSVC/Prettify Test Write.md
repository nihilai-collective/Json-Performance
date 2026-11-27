
----
### Prettify Test Write Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 2691.55 | 0.138826 | 6383.76ms | 699405 | 160 | 1.89371e+07 | 247814 | 0.0113505 | 1.12917 | 1(Win) | true |
| Jsonifier | 2591.75 | 0.071486 | 6796.92ms | 699405 | 1280 | 4.33234e+07 | 257357 | 0.219017 | 1.17211 | 2(Loss) | true |
| simdjson (ondemand) | 1480.35 | 0.313792 | 6630.61ms | 767297 | 320 | 7.69897e+08 | 494311 | 0.593625 | 2.05225 | 3(Loss) | true |
