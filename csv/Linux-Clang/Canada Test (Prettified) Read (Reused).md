
----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2088.49 | 0.0443444 | 8931.05ms | 5373214 | 80 | 9.47045e+07 | 2.45359e+06 | 0.024005 | 1.18544 | 1(Win) | true |
| Jsonifier | 2049.1 | 0.0628145 | 9299.26ms | 5373214 | 80 | 1.97401e+08 | 2.50075e+06 | 0.101426 | 1.20822 | 2(Loss) | true |
| simdjson (ondemand) | 2027.27 | 0.0376452 | 9225.07ms | 5373214 | 30 | 2.71635e+07 | 2.52768e+06 | 0.331433 | 1.22123 | 3(Loss) | true |
| Glaze | 1855.97 | 0.0792852 | 10018.1ms | 5373214 | 30 | 1.43758e+08 | 2.76098e+06 | 0.335964 | 1.33395 | 4(Loss) | true |
