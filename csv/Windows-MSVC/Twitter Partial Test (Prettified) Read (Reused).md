
----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7746.34 | 0.145612 | 7916.92ms | 631514 | 80 | 1.02531e+06 | 77747.5 | 0.00964754 | 0.392249 | 1(Win) | true |
| Jsonifier (two-stage) | 7665.16 | 0.0588971 | 7982.96ms | 631514 | 1280 | 2.74108e+06 | 78570.9 | 0.141194 | 0.396381 | 2(Loss) | true |
| simdjson (ondemand) | 5284.36 | 0.111734 | 5904.65ms | 631514 | 320 | 5.18919e+06 | 113970 | 0.0137116 | 0.575035 | 3(Loss) | true |
| Glaze | 3621.96 | 0.0662625 | 8595.67ms | 631514 | 1280 | 1.5539e+07 | 166280 | 0.0471002 | 0.839009 | 4(Loss) | true |
