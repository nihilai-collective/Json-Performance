
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 927.663 | 0.0455489 | 128.56ms | 1213 | 80 | 25.81 | 1247.01 | 0.0290779 | 2.61141 | 1(Win) | true |
| simdjson (ondemand) | 334.347 | 0.0307801 | 351.313ms | 1213 | 30 | 34.0241 | 3459.9 | 0.0105965 | 7.35045 | 2(Loss) | true |
