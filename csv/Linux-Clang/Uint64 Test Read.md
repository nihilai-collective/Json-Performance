
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1610.91 | 0.569386 | 73.9638ms | 1213 | 1280 | 21399.5 | 718.109 | 0.0690357 | 1.48056 | 1(Win) | true |
| Glaze | 936.97 | 0.0968265 | 126.036ms | 1213 | 40 | 57.1635 | 1234.62 | 0.0195703 | 2.58601 | 2(Loss) | true |
| simdjson (ondemand) | 316.582 | 0.164079 | 368.916ms | 1213 | 4890 | 175779 | 3654.06 | 0.0829026 | 7.76591 | 3(Loss) | true |
