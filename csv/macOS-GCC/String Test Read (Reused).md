
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1884.25 | 3.11614 | 328.003ms | 4215 | 30 | 132579 | 2133.33 | 0 | 1(Win) | true |
| Glaze | 835.618 | 0.304132 | 569.904ms | 4215 | 4890 | 1.04668e+06 | 4810.5 | 0.675914 | 2(Loss) | true |
| simdjson (reflection) | 828.728 | 0.268696 | 587.651ms | 4215 | 4890 | 830619 | 4850.49 | 1.37508 | 3(Loss) | true |
| simdjson (ondemand) | 655.22 | 0.259206 | 715.736ms | 4215 | 4890 | 1.23658e+06 | 6134.94 | 0.445555 | 4(Loss) | true |
