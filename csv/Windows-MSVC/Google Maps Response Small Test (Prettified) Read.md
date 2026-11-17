
----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2027.88 | 0.0639312 | 444.267ms | 9378 | 4890 | 38875.1 | 4410.31 | 0.0530403 | 1.49189 | 1(Win) | true |
| Jsonifier | 1904.24 | 0.297337 | 474.522ms | 9378 | 30 | 5850.57 | 4696.67 | 0.212465 | 1.59002 | 2(Loss) | true |
| Glaze | 1414.95 | 0.0623005 | 637.488ms | 9378 | 4890 | 75828 | 6320.76 | 0.00455498 | 2.14014 | 3(Loss) | true |
| simdjson (ondemand) | 1110.31 | 0.0768955 | 816.765ms | 9378 | 160 | 6138.36 | 8055 | 0.13947 | 2.73142 | 4(Loss) | true |
