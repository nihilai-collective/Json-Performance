
----
### Canada Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1236.57 | 0.331628 | 940.865ms | 11579 | 30 | 26310.3 | 8930 | 0.0373134 | 1.99493 | 1(Win) | true |
| Jsonifier | 1167.43 | 0.297002 | 966.666ms | 11579 | 2560 | 2.0204e+06 | 9458.87 | 0.021066 | 2.11377 | 2(Loss) | true |
| simdjson (ondemand) | 425.21 | 0.1729 | 2651.4ms | 11579 | 1280 | 2.5807e+06 | 25969.8 | 0.000902484 | 5.8163 | 3(Loss) | true |
| Glaze | 386.714 | 0.0832309 | 2878.87ms | 11579 | 4890 | 2.7621e+06 | 28554.9 | 0.152411 | 6.39536 | 4(Loss) | true |
