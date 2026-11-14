
----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1303.24 | 0.1176 | 492.633ms | 6701 | 2560 | 85129.7 | 4903.59 | 0.0095584 | 2.32174 | 1(Win) | true |
| Jsonifier | 1202.35 | 0.160447 | 536.595ms | 6701 | 1280 | 93087.6 | 5315.08 | 0.0807778 | 2.51738 | 2(Loss) | true |
| Glaze | 1098.71 | 0.0786332 | 587.194ms | 6701 | 4890 | 102290 | 5816.44 | 0.353407 | 2.75466 | 3(Loss) | true |
| simdjson (ondemand) | 983.165 | 0.190485 | 661.118ms | 6701 | 160 | 24528.3 | 6500 | 0.0192271 | 3.07995 | 4(Loss) | true |
