
----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1391.66 | 0.25703 | 971.892ms | 11579 | 2560 | 1.06484e+06 | 7934.84 | 0.0167407 | 1.7725 | 1(Win) | true |
| Jsonifier | 1360.34 | 0.115761 | 1008.92ms | 11579 | 40 | 3532.05 | 8117.5 | 0.2986 | 1.81504 | 2(Loss) | true |
| simdjson (ondemand) | 421.629 | 0.189503 | 2806.89ms | 11579 | 1280 | 3.15299e+06 | 26190.3 | 0.0107399 | 5.86581 | 3(Loss) | true |
| Glaze | 389.767 | 0.624475 | 2932.05ms | 11579 | 160 | 5.0082e+06 | 28331.2 | 0.0706433 | 6.34463 | 4(Loss) | true |
