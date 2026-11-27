
----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6727.12 | 0.379223 | 58.375ms | 3808 | 640 | 2682.29 | 539.844 | 0.144928 | 0.433814 | 1(Win) | true |
| Jsonifier (two-stage) | 6580.46 | 0.307527 | 58.4716ms | 3808 | 1280 | 3686.86 | 551.875 | 0.312411 | 0.443406 | 2(Loss) | true |
| simdjson (ondemand) | 5178.74 | 0.178253 | 71.257ms | 3808 | 80 | 125 | 701.25 | 0.178571 | 0.569482 | 3(Loss) | true |
| Glaze | 3665.96 | 0.411741 | 109.035ms | 3808 | 640 | 10647.5 | 990.625 | 0.906533 | 0.806336 | 4(Loss) | true |
