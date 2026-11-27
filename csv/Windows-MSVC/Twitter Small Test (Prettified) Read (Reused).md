
----
### Twitter Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2027.8 | 0.31287 | 197.423ms | 3808 | 4890 | 153525 | 1790.9 | 0.122371 | 1.20164 | 1(Win) | true |
| Jsonifier (two-stage) | 1788.96 | 0.419194 | 229.212ms | 3808 | 30 | 2172.41 | 2030 | 0 | 1.35962 | 2(Loss) | true |
| Glaze | 1718.08 | 0.201698 | 237.406ms | 3808 | 80 | 1454.11 | 2113.75 | 0.535077 | 1.41888 | 3(Loss) | true |
| simdjson (ondemand) | 1664.2 | 0.104267 | 236.974ms | 3808 | 320 | 1656.64 | 2182.19 | 0.0429799 | 1.4687 | 4(Loss) | true |
