
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1960.48 | 0.110934 | 9355.7ms | 5373214 | 160 | 1.34522e+09 | 2.61379e+06 | 0.10431 | 1.26286 | 1(Win) | true |
| Jsonifier | 1910.56 | 0.33913 | 9707.88ms | 5373214 | 80 | 6.61868e+09 | 2.6821e+06 | 0.0281846 | 1.29586 | 2(Loss) | true |
| simdjson (ondemand) | 1851.41 | 0.0778692 | 9986.23ms | 5373214 | 40 | 1.85803e+08 | 2.76778e+06 | 1.04275 | 1.33725 | 3(Loss) | true |
| simdjson (reflection) | 1785.43 | 0.0551476 | 10136.4ms | 5373214 | 40 | 1.00206e+08 | 2.87006e+06 | 0.511589 | 1.38667 | 4(Loss) | true |
| Glaze | 1753.66 | 0.10729 | 10361.1ms | 5373214 | 30 | 2.94859e+08 | 2.92206e+06 | 0.620344 | 1.4118 | 5(Loss) | true |
