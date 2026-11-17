
----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4712.68 | 0.0432444 | 87.6265ms | 3862 | 320 | 36.5509 | 781.528 | 0.311658 | 0.50771 | 1(Win) | true |
| simdjson (reflection) | 3172.16 | 0.0739785 | 126.431ms | 3862 | 30 | 22.1333 | 1161.07 | 0.0574515 | 0.762515 | 2(Loss) | true |
| Glaze | 1700.78 | 0.0473175 | 222.463ms | 3862 | 30 | 31.4989 | 2165.53 | 0.0277145 | 1.43351 | 3(Loss) | true |
