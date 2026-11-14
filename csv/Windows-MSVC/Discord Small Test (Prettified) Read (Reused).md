
----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1949.09 | 0.150493 | 400.21ms | 6701 | 80 | 1947.78 | 3278.75 | 0.719152 | 1.54621 | 1(Win) | true |
| Jsonifier (two-stage) | 1809.08 | 0.212314 | 439.962ms | 6701 | 40 | 2250 | 3532.5 | 0.586304 | 1.67462 | 2(Loss) | true |
| Jsonifier | 1691.75 | 0.876588 | 455.245ms | 6701 | 640 | 701746 | 3777.5 | 0.0248242 | 1.78613 | 3(Loss) | true |
| simdjson (ondemand) | 1399.14 | 0.100025 | 537.172ms | 6701 | 160 | 3339.62 | 4567.5 | 0.327332 | 2.16362 | 4(Loss) | true |
