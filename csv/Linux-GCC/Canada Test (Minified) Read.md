
----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 824.23 | 0.20704 | 8192.86ms | 2251027 | 160 | 4.65257e+09 | 2.60455e+06 | 0.296718 | 3.00374 | 1(Win) | true |
| Jsonifier (two-stage) | 779.411 | 0.242676 | 8642.82ms | 2251027 | 80 | 3.57414e+09 | 2.75432e+06 | 1.36005 | 3.17646 | 2(Loss) | true |
| Glaze | 744.482 | 0.134366 | 8939.51ms | 2251027 | 40 | 6.00475e+08 | 2.88354e+06 | 0.148314 | 3.3255 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 707.972 | 0.343512 | 9451.18ms | 2251027 | 160 | 1.73594e+10 | 3.03225e+06 | 0.253625 | 3.49699 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 705.325 | 0.214685 | 9602.13ms | 2251027 | 30 | 1.28088e+09 | 3.04363e+06 | 0.606301 | 3.51013 | 4(Tie) | true |
