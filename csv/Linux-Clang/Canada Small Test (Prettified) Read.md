
----
### Canada Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1798.45 | 0.177485 | 1352.81ms | 11579 | 320 | 38002.9 | 6140.06 | 0.0645769 | 2.87203 | 13.2513 | 2.60204 | 0.00478749 | 3.07669e-05 | 1.26846e-05 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 1789.32 | 0.0969337 | 1349.89ms | 11579 | 2560 | 91612.4 | 6171.38 | 0.0667017 | 2.86823 | 13.6301 | 2.32378 | 0.00172828 | 5.64735e-05 | 3.46802e-05 | 2(Tie) | true |
| Jsonifier STATISTICAL TIE | 1786.82 | 0.133193 | 1352.49ms | 11579 | 1280 | 86727.2 | 6180.02 | 0.0654375 | 2.89538 | 13.5569 | 2.90578 | 0.00485699 | 1.44389e-05 | 2.49644e-06 | 2(Tie) | true |
| Glaze | 1535.73 | 0.0557078 | 1439.63ms | 11579 | 4890 | 78460.9 | 7190.45 | 0.120124 | 3.3341 | 15.4061 | 3.01477 | 0.00654836 | 1.68841e-05 | 4.32699e-06 | 4(Loss) | true |
