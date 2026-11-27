
----
### Github Events Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1209.4 | 0.21154 | 147.177ms | 1691 | 320 | 2546.14 | 1333.44 | 0.163781 | 2.47423 | 1(Win) | true |
| Glaze | 1174.45 | 0.3078 | 149.616ms | 1691 | 160 | 2858.1 | 1373.12 | 2.09447 | 2.54448 | 2(Loss) | true |
| Jsonifier (two-stage) | 977.14 | 0.786961 | 180.775ms | 1691 | 1280 | 215919 | 1650.39 | 0.728383 | 3.07289 | 3(Loss) | true |
| simdjson (ondemand) | 774.388 | 0.280401 | 225.38ms | 1691 | 80 | 2727.85 | 2082.5 | 0 | 3.89162 | 4(Loss) | true |
