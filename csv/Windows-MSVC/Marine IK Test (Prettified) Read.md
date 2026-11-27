
----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2021.12 | 0.947816 | 5278.31ms | 7351818 | 80 | 8.64858e+10 | 3.46899e+06 | 1.61545 | 1.5037 | 1(Win) | true |
| Jsonifier | 1954.53 | 1.17226 | 5467.73ms | 7351818 | 40 | 7.07312e+10 | 3.58718e+06 | 2.35395 | 1.55493 | 2(Loss) | true |
| simdjson (ondemand) | 1353.62 | 0.365263 | 7897.59ms | 7351818 | 80 | 2.86351e+10 | 5.17963e+06 | 0.590311 | 2.2453 | 3(Loss) | true |
| Glaze | 1105.17 | 0.504686 | 9797.97ms | 7351818 | 40 | 4.10049e+10 | 6.34405e+06 | 0.668526 | 2.75003 | 4(Loss) | true |
