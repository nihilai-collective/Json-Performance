
----
### Canada Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6730.32 | 0.321444 | 202.481ms | 14795 | 4890 | 222064 | 2096.43 | 0.393151 | 1(Win) | true |
| Glaze | 3682.01 | 0.181235 | 404.234ms | 14795 | 4890 | 235861 | 3832.04 | 0.644584 | 2(Loss) | true |
| simdjson (reflection) | 337.015 | 0.197371 | 4262.9ms | 14795 | 320 | 2.18497e+06 | 41866.4 | 0.0554451 | 3(Loss) | true |
