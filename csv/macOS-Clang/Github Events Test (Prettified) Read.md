
----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1634.27 | 1.85742 | 4151.37ms | 65103 | 160 | 7.96697e+07 | 37990.7 | 1.91589 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE DID NOT CONVERGE | 1582.3 | 0.285157 | 4085.84ms | 65103 | 4890 | 6.12213e+07 | 39238.6 | 5.21306 | -(Tie) | false |
| Glaze | 1341.6 | 0.957264 | 4210.72ms | 65103 | 640 | 1.25603e+08 | 46278.4 | 0.702276 | 3(Loss) | true |
| simdjson (ondemand) | 1054.61 | 0.543835 | 6824.85ms | 65103 | 40 | 4.10026e+06 | 58872 | 0.664792 | 4(Loss) | true |
