
----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1919.38 | 0.376994 | 719.041ms | 11579 | 640 | 301071 | 5753.2 | 0.188075 | 1(Win) | true |
| Jsonifier (two-stage) | 1687.33 | 0.739039 | 807.392ms | 11579 | 640 | 1.49711e+06 | 6544.4 | 1.02238 | 2(Loss) | true |
| simdjson (reflection) | 1399.64 | 1.40985 | 923.989ms | 11579 | 320 | 3.95917e+06 | 7889.6 | 0.584677 | 3(Loss) | true |
| Glaze | 1166.62 | 0.173235 | 1090.39ms | 11579 | 2560 | 688329 | 9465.5 | 0.265879 | 4(Loss) | true |
| simdjson (ondemand) | 1033.69 | 0.432723 | 1173.52ms | 11579 | 4890 | 1.04495e+07 | 10682.7 | 1.89369 | 5(Loss) | true |
