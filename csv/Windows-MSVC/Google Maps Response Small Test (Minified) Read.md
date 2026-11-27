
----
### Google Maps Response Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1096.69 | 0.227583 | 413.202ms | 4390 | 40 | 3019.23 | 3817.5 | 0.0218341 | 2.2396 | 1(Win) | true |
| Jsonifier (two-stage) | 956.398 | 0.152751 | 456.293ms | 4390 | 40 | 1788.46 | 4377.5 | 0.0570776 | 2.57126 | 2(Loss) | true |
| Glaze | 816.107 | 0.2121 | 532.077ms | 4390 | 30 | 3551.72 | 5130 | 0.0649351 | 3.01753 | 3(Loss) | true |
| simdjson (ondemand) | 543.954 | 0.191837 | 794.583ms | 4390 | 30 | 6540.23 | 7696.67 | 0.259179 | 4.53588 | 4(Loss) | true |
