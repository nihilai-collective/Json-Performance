
----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2168.55 | 0.23961 | 4246.52ms | 83958 | 4890 | 3.82741e+07 | 36922.6 | 1.86791 | 1(Win) | true |
| Jsonifier (two-stage) | 1977.98 | 0.978467 | 4970.23ms | 83958 | 40 | 6.27528e+06 | 40480 | 0.716561 | 2(Loss) | true |
| Glaze | 1901.27 | 0.323887 | 4717.56ms | 83958 | 2560 | 4.76284e+07 | 42113.3 | 1.44971 | 3(Loss) | true |
| simdjson (reflection) | 1611.17 | 0.809086 | 6124.64ms | 83958 | 40 | 6.46685e+06 | 49696 | 1.8083 | 4(Loss) | true |
| simdjson (ondemand) | 1456.68 | 0.194885 | 6215.32ms | 83958 | 2560 | 2.9376e+07 | 54966.6 | 1.57328 | 5(Loss) | true |
