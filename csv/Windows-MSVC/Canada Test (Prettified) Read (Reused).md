
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1498.84 | 1.12389 | 6228.5ms | 5373214 | 80 | 1.18112e+11 | 3.41885e+06 | 0.0393618 | 1.6518 | 1(Win) | true |
| Jsonifier | 1405.4 | 1.6872 | 6388.61ms | 5373214 | 80 | 3.02754e+11 | 3.64615e+06 | 1.99481 | 1.76158 | 2(Loss) | true |
| simdjson (ondemand) | 470.89 | 0.139975 | 8095.62ms | 5373214 | 40 | 9.28095e+09 | 1.08821e+07 | 0.171287 | 5.25765 | 3(Loss) | true |
| Glaze | 442.128 | 0.476306 | 8645.57ms | 5373214 | 30 | 9.14255e+10 | 1.15901e+07 | 0.4731 | 5.59976 | 4(Loss) | true |
