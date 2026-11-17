
----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1682.62 | 0.222023 | 433.835ms | 6701 | 4890 | 347707 | 3798 | 0.0907392 | 1.46071 | 1(Win) | true |
| Jsonifier (two-stage) | 1472.27 | 0.100688 | 486.24ms | 6701 | 160 | 3056.21 | 4340.62 | 0.21645 | 1.67061 | 2(Loss) | true |
| Jsonifier | 1418.55 | 0.110988 | 517.077ms | 6701 | 80 | 2000 | 4505 | 0.111111 | 1.73498 | 3(Loss) | true |
| simdjson (ondemand) | 1203.75 | 0.509165 | 577.966ms | 6701 | 640 | 467636 | 5308.91 | 0.290527 | 2.04569 | 4(Loss) | true |
