
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 946.436 | 0.217663 | 5981.01ms | 461466 | 160 | 1.63903e+08 | 464995 | 0.196433 | 1(Win) | true |
| Jsonifier (two-stage) | 821.168 | 0.485173 | 7007.99ms | 461466 | 320 | 2.16351e+09 | 535930 | 2.25599 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 727.297 | 0.144347 | 7664.84ms | 461466 | 640 | 4.88259e+08 | 605101 | 0.0168595 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 722.43 | 1.30964 | 7872.08ms | 461466 | 40 | 2.54597e+09 | 609178 | 1.57511 | 3(Tie) | true |
| simdjson (ondemand) | 598.106 | 0.598228 | 9574.54ms | 461466 | 30 | 5.81271e+08 | 735804 | 0.884511 | 5(Loss) | true |
