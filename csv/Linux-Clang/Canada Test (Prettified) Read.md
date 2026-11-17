
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1563.02 | 0.192041 | 10159ms | 5373214 | 80 | 3.17118e+09 | 3.27846e+06 | 0.558202 | 1.58391 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1562.48 | 0.464464 | 10093ms | 5373214 | 80 | 1.85623e+10 | 3.27959e+06 | 0.671208 | 1.58445 | 1(Tie) | true |
| simdjson (ondemand) | 1550.07 | 0.129768 | 5110.51ms | 5373214 | 30 | 5.52106e+08 | 3.30586e+06 | 1.71256 | 1.59718 | 3(Loss) | true |
| Glaze | 1439.85 | 0.622154 | 5403.09ms | 5373214 | 80 | 3.9221e+10 | 3.5589e+06 | 0.460783 | 1.71941 | 4(Loss) | true |
